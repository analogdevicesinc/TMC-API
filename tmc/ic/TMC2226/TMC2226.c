/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2226.h"

// => UART wrapper
extern void tmc2226_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc2226_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc2226_writeInt(TMC2226TypeDef *tmc2226, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = tmc2226->slaveAddress;
	data[2] = address | TMC_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = tmc2226_CRC8(data, 7);

	tmc2226_readWriteArray(tmc2226->config->channel, &data[0], 8, 0);

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2226->config->shadowRegister[address] = value;
	tmc2226->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc2226_readInt(TMC2226TypeDef *tmc2226, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	if (!TMC_IS_READABLE(tmc2226->registerAccess[address]))
		return tmc2226->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = tmc2226->slaveAddress;
	data[2] = address;
	data[3] = tmc2226_CRC8(data, 3);

	tmc2226_readWriteArray(tmc2226->config->channel, data, 4, 8);

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
	if (data[7] != tmc2226_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc2226_init(TMC2226TypeDef *tmc2226, uint8_t channel, uint8_t slaveAddress, ConfigurationTypeDef *tmc2226_config, const int32_t *registerResetState)
{
	tmc2226->slaveAddress = slaveAddress;

	tmc2226->config               = tmc2226_config;
	tmc2226->config->callback     = NULL;
	tmc2226->config->channel      = channel;
	tmc2226->config->configIndex  = 0;
	tmc2226->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC2226_REGISTER_COUNT; i++)
	{
		tmc2226->registerAccess[i]      = tmc2226_defaultRegisterAccess[i];
		tmc2226->registerResetState[i]  = registerResetState[i];
	}
}

static void writeConfiguration(TMC2226TypeDef *tmc2226)
{
	uint8_t *ptr = &tmc2226->config->configIndex;
	const int32_t *settings;

	if(tmc2226->config->state == CONFIG_RESTORE)
	{
		settings = tmc2226->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2226_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2226->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		settings = tmc2226->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2226_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2226->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2226_REGISTER_COUNT)
	{
		tmc2226_writeInt(tmc2226, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2226->config->callback)
		{
			((tmc2226_callback)tmc2226->config->callback)(tmc2226, tmc2226->config->state);
		}

		tmc2226->config->state = CONFIG_READY;
	}
}

void tmc2226_periodicJob(TMC2226TypeDef *tmc2226, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2226->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2226);
		return;
	}
}

void tmc2226_setRegisterResetState(TMC2226TypeDef *tmc2226, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC2226_REGISTER_COUNT; i++)
		tmc2226->registerResetState[i] = resetState[i];
}

void tmc2226_setCallback(TMC2226TypeDef *tmc2226, tmc2226_callback callback)
{
	tmc2226->config->callback = (tmc_callback_config) callback;
}

uint8_t tmc2226_reset(TMC2226TypeDef *tmc2226)
{
	if(tmc2226->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2226_REGISTER_COUNT; i++)
	{
		tmc2226->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2226->config->shadowRegister[i] = 0;
	}

	tmc2226->config->state        = CONFIG_RESET;
	tmc2226->config->configIndex  = 0;

	return true;
}

uint8_t tmc2226_restore(TMC2226TypeDef *tmc2226)
{
	if(tmc2226->config->state != CONFIG_READY)
		return false;

	tmc2226->config->state        = CONFIG_RESTORE;
	tmc2226->config->configIndex  = 0;

	return true;
}

uint8_t tmc2226_getSlaveAddress(TMC2226TypeDef *tmc2226)
{
	return tmc2226->slaveAddress;
}

void tmc2226_setSlaveAddress(TMC2226TypeDef *tmc2226, uint8_t slaveAddress)
{
	tmc2226->slaveAddress = slaveAddress;
}
