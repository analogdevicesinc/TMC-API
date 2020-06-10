/*
 * TMC2225.c
 *
 *  Created on: 16.07.2017
 *      Author: LH
 */

#include "TMC2225.h"

// => UART wrapper
extern void tmc2225_readWriteArray(uint8_t channel, uint8_t *data, size_t writeLength, size_t readLength);
// <= UART wrapper

// => CRC wrapper
extern uint8_t tmc2225_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

void tmc2225_writeInt(TMC2225TypeDef *tmc2225, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = 0;
	data[2] = address | TMC_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = tmc2225_CRC8(data, 7);

	tmc2225_readWriteArray(tmc2225->config->channel, &data[0], 8, 0);

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2225->config->shadowRegister[address] = value;
	tmc2225->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t tmc2225_readInt(TMC2225TypeDef *tmc2225, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = TMC_ADDRESS(address);

	if (!TMC_IS_READABLE(tmc2225->registerAccess[address]))
		return tmc2225->config->shadowRegister[address];

	data[0] = 0x05;
	data[1] = 0;
	data[2] = address;
	data[3] = tmc2225_CRC8(data, 3);

	tmc2225_readWriteArray(tmc2225->config->channel, data, 4, 8);

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
	if (data[7] != tmc2225_CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void tmc2225_init(TMC2225TypeDef *tmc2225, uint8_t channel, ConfigurationTypeDef *tmc2225_config, const int32_t *registerResetState)
{
	tmc2225->config               = tmc2225_config;
	tmc2225->config->callback     = NULL;
	tmc2225->config->channel      = channel;
	tmc2225->config->configIndex  = 0;
	tmc2225->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC2225_REGISTER_COUNT; i++)
	{
		tmc2225->registerAccess[i]      = tmc2225_defaultRegisterAccess[i];
		tmc2225->registerResetState[i]  = registerResetState[i];
	}
}

static void writeConfiguration(TMC2225TypeDef *tmc2225)
{
	uint8_t *ptr = &tmc2225->config->configIndex;
	const int32_t *settings;

	if(tmc2225->config->state == CONFIG_RESTORE)
	{
		settings = tmc2225->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2225_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2225->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		settings = tmc2225->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2225_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2225->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2225_REGISTER_COUNT)
	{
		tmc2225_writeInt(tmc2225, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2225->config->callback)
		{
			((tmc2225_callback)tmc2225->config->callback)(tmc2225, tmc2225->config->state);
		}

		tmc2225->config->state = CONFIG_READY;
	}
}

void tmc2225_periodicJob(TMC2225TypeDef *tmc2225, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2225->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2225);
		return;
	}
}

void tmc2225_setRegisterResetState(TMC2225TypeDef *tmc2225, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC2225_REGISTER_COUNT; i++)
	{
		tmc2225->registerResetState[i] = resetState[i];
	}
}

void tmc2225_setCallback(TMC2225TypeDef *tmc2225, tmc2225_callback callback)
{
	tmc2225->config->callback = (tmc_callback_config) callback;
}

uint8_t tmc2225_reset(TMC2225TypeDef *tmc2225)
{
	if(tmc2225->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2225_REGISTER_COUNT; i++)
	{
		tmc2225->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2225->config->shadowRegister[i] = 0;
	}

	tmc2225->config->state        = CONFIG_RESET;
	tmc2225->config->configIndex  = 0;

	return true;
}

uint8_t tmc2225_restore(TMC2225TypeDef *tmc2225)
{
	if(tmc2225->config->state != CONFIG_READY)
		return false;

	tmc2225->config->state        = CONFIG_RESTORE;
	tmc2225->config->configIndex  = 0;

	return true;
}

void tmc2225_set_slave(TMC2225TypeDef *tmc2225, uint8_t slave)
{
	tmc2225->slave_address = slave;
}

uint8_t tmc2225_get_slave(TMC2225TypeDef *tmc2225)
{
	return tmc2225->slave_address;
}
