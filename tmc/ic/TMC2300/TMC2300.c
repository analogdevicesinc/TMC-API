/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2300.h"

// => UART wrapper
extern void tmc2300_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc2300_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc2300_writeInt(TMC2300TypeDef *tmc2300, uint8_t address, int32_t value)
{
	// When we are in standby or in the reset procedure we do not actually write
	// to the IC - we only update the shadow registers. After exiting standby or
	// completing a reset we transition into a restore, which pushes the shadow
	// register contents into the chip.
	if (!tmc2300->standbyEnabled || tmc2300->config->state != CONFIG_RESET)
	{
		uint8_t data[8];

		data[0] = 0x05;
		data[1] = tmc2300->slaveAddress;
		data[2] = address | TMC_WRITE_BIT;
		data[3] = (value >> 24) & 0xFF;
		data[4] = (value >> 16) & 0xFF;
		data[5] = (value >> 8 ) & 0xFF;
		data[6] = (value      ) & 0xFF;
		data[7] = tmc2300_CRC8(data, 7);

		tmc2300_readWriteArray(tmc2300->config->channel, &data[0], 8, 0);
	}

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2300->config->shadowRegister[address] = value;
	tmc2300->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc2300_readInt(TMC2300TypeDef *tmc2300, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	// When the chip is in standby or when accessing a write-only register
	// use the shadow register content instead.
	if (tmc2300->standbyEnabled || !TMC_IS_READABLE(tmc2300->registerAccess[address]))
		return tmc2300->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = tmc2300->slaveAddress;
	data[2] = address;
	data[3] = tmc2300_CRC8(data, 3);

	tmc2300_readWriteArray(tmc2300->config->channel, data, 4, 8);

	// Byte 0: Sync nibble correct?
	if (data[0] != 0x05)
		return 0;

	// Byte 1: Master address correct?
	if (data[1] != 0xFF)
		return 0;

	// Byte 2: Address correct?
	if (data[2] != address)
		return 0;

	// Byte 7: CRC correct?
	if (data[7] != tmc2300_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc2300_init(TMC2300TypeDef *tmc2300, uint8_t channel, ConfigurationTypeDef *tmc2300_config, const int32_t *registerResetState)
{
	tmc2300->config               = tmc2300_config;
	tmc2300->config->callback     = NULL;
	tmc2300->config->channel      = channel;
	tmc2300->config->configIndex  = 0;
	tmc2300->config->state        = CONFIG_READY;

	// Default slave address: 0
	tmc2300->slaveAddress = 0;

	// Start in standby
	tmc2300->standbyEnabled = 1;

	int32_t i;
	for(i = 0; i < TMC2300_REGISTER_COUNT; i++)
	{
		tmc2300->registerAccess[i]      = tmc2300_defaultRegisterAccess[i];
		tmc2300->registerResetState[i]  = registerResetState[i];
	}
}

// Fill the shadow registers of hardware preset registers
// Only needed if you want to read out those registers to display the value
// (e.g. for the TMCL IDE register browser)
static void fillShadowRegisters(TMC2300TypeDef *tmc2300)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc2300_RegisterConstants) == 0)
		return;

	size_t i, j = 0;
	for(i = 0; i < TMC2300_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset registers
		// that have not yet been written (no dirty bit) here.
		if(!TMC_IS_PRESET(tmc2300->registerAccess[i]) || TMC_IS_DIRTY(tmc2300->registerAccess[i]))
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while (j < ARRAY_SIZE(tmc2300_RegisterConstants) && (tmc2300_RegisterConstants[j].address < i))
		{
			j++;
		}

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc2300_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if (tmc2300_RegisterConstants[j].address == i)
		{
			tmc2300->config->shadowRegister[i] = tmc2300_RegisterConstants[j].value;
		}
	}
}

void writeConfiguration(TMC2300TypeDef *tmc2300)
{
	uint8_t *ptr = &tmc2300->config->configIndex;
	const int32_t *settings;

	if (tmc2300->config->state == CONFIG_RESET)
	{
		settings = tmc2300->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2300_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2300->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		// Do not restore while in standby
		if (tmc2300->standbyEnabled)
			return;

		settings = tmc2300->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2300_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2300->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2300_REGISTER_COUNT)
	{
		// Reset/restore the found register
		tmc2300_writeInt(tmc2300, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		fillShadowRegisters(tmc2300);

		// Reset/restore complete -> call the callback if set
		if (tmc2300->config->callback)
		{
			((tmc2300_callback)tmc2300->config->callback)(tmc2300, tmc2300->config->state);
		}

		if (tmc2300->config->state == CONFIG_RESET)
		{
			// Reset done -> Perform a restore
			tmc2300->config->state        = CONFIG_RESTORE;
			tmc2300->config->configIndex  = 0;
		}
		else
		{
			// Restore done -> configuration complete
			tmc2300->config->state = CONFIG_READY;
		}
	}
}

void tmc2300_setRegisterResetState(TMC2300TypeDef *tmc2300, const int32_t *resetState)
{
	size_t i;
	for (i = 0; i < TMC2300_REGISTER_COUNT; i++)
	{
		tmc2300->registerResetState[i] = resetState[i];
	}
}

void tmc2300_setCallback(TMC2300TypeDef *tmc2300, tmc2300_callback callback)
{
	tmc2300->config->callback = (tmc_callback_config) callback;
}

void tmc2300_periodicJob(TMC2300TypeDef *tmc2300, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2300->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2300);
		return;
	}
}

uint8_t tmc2300_reset(TMC2300TypeDef *tmc2300)
{
	// A reset can always happen - even during another reset or restore

	// Reset the dirty bits and wipe the shadow registers
	size_t i;
	for(i = 0; i < TMC2300_REGISTER_COUNT; i++)
	{
		tmc2300->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2300->config->shadowRegister[i] = 0;
	}

	// Activate the reset config mechanism
	tmc2300->config->state        = CONFIG_RESET;
	tmc2300->config->configIndex  = 0;

	return 1;
}

uint8_t tmc2300_restore(TMC2300TypeDef *tmc2300)
{
	// Do not interrupt a reset
	// A reset will transition into a restore anyways
	if(tmc2300->config->state == CONFIG_RESET)
		return 0;

	tmc2300->config->state        = CONFIG_RESTORE;
	tmc2300->config->configIndex  = 0;

	return 1;
}

uint8_t tmc2300_getSlaveAddress(TMC2300TypeDef *tmc2300)
{
	return tmc2300->slaveAddress;
}

void tmc2300_setSlaveAddress(TMC2300TypeDef *tmc2300, uint8_t slaveAddress)
{
	tmc2300->slaveAddress = slaveAddress;
}

uint8_t tmc2300_getStandby(TMC2300TypeDef *tmc2300)
{
	return tmc2300->standbyEnabled;
}

void tmc2300_setStandby(TMC2300TypeDef *tmc2300, uint8_t standbyState)
{
	if (tmc2300->standbyEnabled && !standbyState)
	{
		// Just exited standby -> call the restore
		tmc2300_restore(tmc2300);
	}
	tmc2300->standbyEnabled = standbyState;
}
