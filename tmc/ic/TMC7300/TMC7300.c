/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC7300.h"

// => UART wrapper
extern void tmc7300_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc7300_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc7300_writeInt(TMC7300TypeDef *tmc7300, uint8_t address, int32_t value)
{
	// When we are in standby or in the reset procedure we do not actually write
	// to the IC - we only update the shadow registers. After exiting standby or
	// completing a reset we transition into a restore, which pushes the shadow
	// register contents into the chip.
	if (!tmc7300->standbyEnabled || tmc7300->config->state == CONFIG_RESET)
	{
		uint8_t data[8];

		data[0] = 0x05;
		data[1] = tmc7300->slaveAddress;
		data[2] = address | TMC_WRITE_BIT;
		data[3] = (value >> 24) & 0xFF;
		data[4] = (value >> 16) & 0xFF;
		data[5] = (value >> 8 ) & 0xFF;
		data[6] = (value      ) & 0xFF;
		data[7] = tmc7300_CRC8(data, 7);

		tmc7300_readWriteArray(tmc7300->config->channel, &data[0], 8, 0);
	}

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc7300->config->shadowRegister[address] = value;
	tmc7300->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc7300_readInt(TMC7300TypeDef *tmc7300, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	// When the chip is in standby or when accessing a write-only register
	// use the shadow register content instead.
	if (tmc7300->standbyEnabled || !TMC_IS_READABLE(tmc7300->registerAccess[address]))
		return tmc7300->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = tmc7300->slaveAddress;
	data[2] = address;
	data[3] = tmc7300_CRC8(data, 3);

	tmc7300_readWriteArray(tmc7300->config->channel, data, 4, 8);

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
	if (data[7] != tmc7300_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc7300_init(TMC7300TypeDef *tmc7300, uint8_t channel, ConfigurationTypeDef *tmc7300_config, const int32_t *registerResetState)
{
	tmc7300->config               = tmc7300_config;
	tmc7300->config->callback     = NULL;
	tmc7300->config->channel      = channel;
	tmc7300->config->configIndex  = 0;
	tmc7300->config->state        = CONFIG_RESET;

	// Default slave address: 0
	tmc7300->slaveAddress = 0;

	// Start in standby
	tmc7300->standbyEnabled = 1;

	int32_t i;
	for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
	{
		tmc7300->registerAccess[i]      = tmc7300_defaultRegisterAccess[i];
		tmc7300->registerResetState[i]  = registerResetState[i];
	}
}

// Fill the shadow registers of hardware preset registers.
// Only needed if you want to read out those registers to display the value
// (e.g. for the TMCL IDE register browser)
static void fillShadowRegisters(TMC7300TypeDef *tmc7300)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc7300_registerConstants) == 0)
		return;

	size_t i, j = 0;
	for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset registers
		// that have not yet been written (no dirty bit) here.
		if(!TMC_IS_PRESET(tmc7300->registerAccess[i]) || TMC_IS_DIRTY(tmc7300->registerAccess[i]))
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while (j < ARRAY_SIZE(tmc7300_registerConstants) && (tmc7300_registerConstants[j].address < i))
		{
			j++;
		}

		// If we have an entry for our current address, write the constant
		if (tmc7300_registerConstants[j].address == i)
		{
			tmc7300->config->shadowRegister[i] = tmc7300_registerConstants[j].value;
		}
	}
}

static void writeConfiguration(TMC7300TypeDef *tmc7300)
{
	uint8_t *ptr = &tmc7300->config->configIndex;
	const int32_t *settings;

	// Find the next register to reset/restore
	if (tmc7300->config->state == CONFIG_RESET)
	{
		settings = tmc7300->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC7300_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc7300->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		// Do not restore while in standby
		if (tmc7300->standbyEnabled)
			return;

		settings = tmc7300->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC7300_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc7300->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC7300_REGISTER_COUNT)
	{
		// Reset/restore the found register
		tmc7300_writeInt(tmc7300, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		fillShadowRegisters(tmc7300);

		// Reset/restore complete -> call the callback if set
		if (tmc7300->config->callback)
		{
			((tmc7300_callback)tmc7300->config->callback)(tmc7300, tmc7300->config->state);
		}

		if (tmc7300->config->state == CONFIG_RESET)
		{
			// Reset done -> Perform a restore
			tmc7300->config->state        = CONFIG_RESTORE;
			tmc7300->config->configIndex  = 0;
		}
		else
		{
			// Restore done -> configuration complete
			tmc7300->config->state = CONFIG_READY;
		}
	}
}

void tmc7300_setRegisterResetState(TMC7300TypeDef *tmc7300, const int32_t *resetState)
{
	size_t i;
	for (i = 0; i < TMC7300_REGISTER_COUNT; i++)
	{
		tmc7300->registerResetState[i] = resetState[i];
	}
}

void tmc7300_setCallback(TMC7300TypeDef *tmc7300, tmc7300_callback callback)
{
	tmc7300->config->callback = (tmc_callback_config) callback;
}

void tmc7300_periodicJob(TMC7300TypeDef *tmc7300, uint32_t tick)
{
	UNUSED(tick);

	if(tmc7300->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc7300);
		return;
	}
}

uint8_t tmc7300_reset(TMC7300TypeDef *tmc7300)
{
	// A reset can always happen - even during another reset or restore

	// Reset the dirty bits and wipe the shadow registers
	size_t i;
	for(i = 0; i < TMC7300_REGISTER_COUNT; i++)
	{
		tmc7300->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc7300->config->shadowRegister[i] = 0;
	}

	// Activate the reset config mechanism
	tmc7300->config->state        = CONFIG_RESET;
	tmc7300->config->configIndex  = 0;

	return 1;
}

uint8_t tmc7300_restore(TMC7300TypeDef *tmc7300)
{
	// Do not interrupt a reset
	// A reset will transition into a restore anyways
	if(tmc7300->config->state == CONFIG_RESET)
		return 0;

	tmc7300->config->state        = CONFIG_RESTORE;
	tmc7300->config->configIndex  = 0;

	return 1;
}

uint8_t tmc7300_get_slave(TMC7300TypeDef *tmc7300)
{
	return tmc7300->slaveAddress;
}

void tmc7300_set_slave(TMC7300TypeDef *tmc7300, uint8_t slaveAddress)
{
	tmc7300->slaveAddress = slaveAddress;
}

uint8_t tmc7300_getStandby(TMC7300TypeDef *tmc7300)
{
	return tmc7300->standbyEnabled;
}

void tmc7300_setStandby(TMC7300TypeDef *tmc7300, uint8_t standbyState)
{
	if (tmc7300->standbyEnabled && !standbyState)
	{
		// Just exited standby -> call the restore
		tmc7300_restore(tmc7300);
	}
	tmc7300->standbyEnabled = standbyState;
}

uint8_t tmc7300_consistencyCheck(TMC7300TypeDef *tmc7300)
{
	// Config has not yet been written -> it can't be consistent
	if(tmc7300->config->state != CONFIG_READY)
		return 0;

	// Standby is enabled -> registers can't be accessed
	if(tmc7300_getStandby(tmc7300))
		return 0;

	// If the PWM_DIRECT bit is no longer set, report an error
	if (TMC7300_FIELD_READ(tmc7300, TMC7300_GCONF, TMC7300_PWM_DIRECT_MASK, TMC7300_PWM_DIRECT_SHIFT) == 0)
		return 1;

	// No inconsistency detected
	return 0;
}
