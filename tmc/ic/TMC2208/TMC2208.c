/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2208.h"

// => UART wrapper
extern void tmc2208_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc2208_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc2208_writeInt(TMC2208TypeDef *tmc2208, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = 0;
	data[2] = address | TMC_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = tmc2208_CRC8(data, 7);

	tmc2208_readWriteArray(tmc2208->config->channel, &data[0], 8, 0);

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2208->config->shadowRegister[address] = value;
	tmc2208->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc2208_readInt(TMC2208TypeDef *tmc2208, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	if (!TMC_IS_READABLE(tmc2208->registerAccess[address]))
		return tmc2208->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = 0;
	data[2] = address;
	data[3] = tmc2208_CRC8(data, 3);

	tmc2208_readWriteArray(tmc2208->config->channel, data, 4, 8);

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
	if (data[7] != tmc2208_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc2208_init(TMC2208TypeDef *tmc2208, uint8_t channel, ConfigurationTypeDef *tmc2208_config, const int32_t *registerResetState)
{
	tmc2208->config               = tmc2208_config;
	tmc2208->config->callback     = NULL;
	tmc2208->config->channel      = channel;
	tmc2208->config->configIndex  = 0;
	tmc2208->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC2208_REGISTER_COUNT; i++)
	{
		tmc2208->registerAccess[i]      = tmc2208_defaultRegisterAccess[i];
		tmc2208->registerResetState[i]  = registerResetState[i];
	}
}

static void writeConfiguration(TMC2208TypeDef *tmc2208)
{
	uint8_t *ptr = &tmc2208->config->configIndex;
	const int32_t *settings;

	if(tmc2208->config->state == CONFIG_RESTORE)
	{
		settings = tmc2208->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2208_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2208->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		settings = tmc2208->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2208_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2208->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2208_REGISTER_COUNT)
	{
		tmc2208_writeInt(tmc2208, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2208->config->callback)
		{
			((tmc2208_callback)tmc2208->config->callback)(tmc2208, tmc2208->config->state);
		}

		tmc2208->config->state = CONFIG_READY;
	}
}

void tmc2208_periodicJob(TMC2208TypeDef *tmc2208, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2208->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2208);
		return;
	}
}

void tmc2208_setRegisterResetState(TMC2208TypeDef *tmc2208, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC2208_REGISTER_COUNT; i++)
	{
		tmc2208->registerResetState[i] = resetState[i];
	}
}

void tmc2208_setCallback(TMC2208TypeDef *tmc2208, tmc2208_callback callback)
{
	tmc2208->config->callback = (tmc_callback_config) callback;
}

uint8_t tmc2208_reset(TMC2208TypeDef *tmc2208)
{
	if(tmc2208->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2208_REGISTER_COUNT; i++)
	{
		tmc2208->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2208->config->shadowRegister[i] = 0;
	}

	tmc2208->config->state        = CONFIG_RESET;
	tmc2208->config->configIndex  = 0;

	return true;
}

uint8_t tmc2208_restore(TMC2208TypeDef *tmc2208)
{
	if(tmc2208->config->state != CONFIG_READY)
		return false;

	tmc2208->config->state        = CONFIG_RESTORE;
	tmc2208->config->configIndex  = 0;

	return true;
}

uint8_t tmc2208_get_slave(TMC2208TypeDef *tmc2208)
{
	UNUSED(tmc2208);

	// The TMC2208 has a hardcoded slave address 0
	return 0;
}
