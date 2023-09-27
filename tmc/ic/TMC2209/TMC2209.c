/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2209.h"

// => UART wrapper
extern void tmc2209_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc2209_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc2209_writeInt(TMC2209TypeDef *tmc2209, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = tmc2209->slaveAddress;
	data[2] = address | TMC_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = tmc2209_CRC8(data, 7);

	tmc2209_readWriteArray(tmc2209->config->channel, &data[0], 8, 0);

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2209->config->shadowRegister[address] = value;
	tmc2209->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc2209_readInt(TMC2209TypeDef *tmc2209, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	if (!TMC_IS_READABLE(tmc2209->registerAccess[address]))
		return tmc2209->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = tmc2209->slaveAddress;
	data[2] = address;
	data[3] = tmc2209_CRC8(data, 3);

	tmc2209_readWriteArray(tmc2209->config->channel, data, 4, 8);

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
	if (data[7] != tmc2209_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc2209_init(TMC2209TypeDef *tmc2209, uint8_t channel, uint8_t slaveAddress, ConfigurationTypeDef *tmc2209_config, const int32_t *registerResetState)
{
	tmc2209->slaveAddress = slaveAddress;

	tmc2209->config               = tmc2209_config;
	tmc2209->config->callback     = NULL;
	tmc2209->config->channel      = channel;
	tmc2209->config->configIndex  = 0;
	tmc2209->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC2209_REGISTER_COUNT; i++)
	{
		tmc2209->registerAccess[i]      = tmc2209_defaultRegisterAccess[i];
		tmc2209->registerResetState[i]  = registerResetState[i];
	}
}

static void writeConfiguration(TMC2209TypeDef *tmc2209)
{
	uint8_t *ptr = &tmc2209->config->configIndex;
	const int32_t *settings;

	if(tmc2209->config->state == CONFIG_RESTORE)
	{
		settings = tmc2209->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2209_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2209->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		settings = tmc2209->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2209_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2209->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2209_REGISTER_COUNT)
	{
		tmc2209_writeInt(tmc2209, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2209->config->callback)
		{
			((tmc2209_callback)tmc2209->config->callback)(tmc2209, tmc2209->config->state);
		}

		tmc2209->config->state = CONFIG_READY;
	}
}

void tmc2209_periodicJob(TMC2209TypeDef *tmc2209, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2209->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2209);
		return;
	}
}

void tmc2209_setRegisterResetState(TMC2209TypeDef *tmc2209, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC2209_REGISTER_COUNT; i++)
		tmc2209->registerResetState[i] = resetState[i];
}

void tmc2209_setCallback(TMC2209TypeDef *tmc2209, tmc2209_callback callback)
{
	tmc2209->config->callback = (tmc_callback_config) callback;
}

uint8_t tmc2209_reset(TMC2209TypeDef *tmc2209)
{
	if(tmc2209->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2209_REGISTER_COUNT; i++)
	{
		tmc2209->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2209->config->shadowRegister[i] = 0;
	}

	tmc2209->config->state        = CONFIG_RESET;
	tmc2209->config->configIndex  = 0;

	return true;
}

uint8_t tmc2209_restore(TMC2209TypeDef *tmc2209)
{
	if(tmc2209->config->state != CONFIG_READY)
		return false;

	tmc2209->config->state        = CONFIG_RESTORE;
	tmc2209->config->configIndex  = 0;

	return true;
}

uint8_t tmc2209_get_slave(TMC2209TypeDef *tmc2209)
{
	return tmc2209->slaveAddress;
}

void tmc2209_set_slave(TMC2209TypeDef *tmc2209, uint8_t slaveAddress)
{
	tmc2209->slaveAddress = slaveAddress;
}
