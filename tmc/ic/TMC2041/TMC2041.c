/*
 * TMC2041.c
 *
 *  Created on: 14.08.2017
 *      Author: LK
 */

#include "TMC2041.h"

// => SPI wrapper
extern void tmc2041_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

void tmc2041_writeDatagram(TMC2041TypeDef *tmc2041, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC2041_WRITE_BIT, x1, x2, x3, x4 };
	tmc2041_readWriteArray(tmc2041->config->channel, &data[0], 5);

	int value = ((uint32_t)x1 << 24) | ((uint32_t)x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = address & ~TMC2041_WRITE_BIT;
	tmc2041->config->shadowRegister[address] = value;
	tmc2041->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc2041_writeInt(TMC2041TypeDef *tmc2041, uint8_t address, int32_t value)
{
	tmc2041_writeDatagram(tmc2041, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32_t tmc2041_readInt(TMC2041TypeDef *tmc2041, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2041->registerAccess[address]))
		return tmc2041->config->shadowRegister[address];

	uint8_t data[5];

	data[0] = address;
	tmc2041_readWriteArray(tmc2041->config->channel, &data[0], 5);

	data[0] = address;
	tmc2041_readWriteArray(tmc2041->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

void tmc2041_init(TMC2041TypeDef *tmc2041, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc2041->config = config;

	tmc2041->config->callback     = NULL;
	tmc2041->config->channel      = channel;
	tmc2041->config->configIndex  = 0;
	tmc2041->config->state        = CONFIG_READY;

	int i;
	for(i = 0; i < TMC2041_REGISTER_COUNT; i++)
	{
		tmc2041->registerAccess[i]      = tmc2041_defaultRegisterAccess[i];
		tmc2041->registerResetState[i]  = registerResetState[i];
	}
}

uint8_t tmc2041_reset(TMC2041TypeDef *tmc2041)
{
	if(tmc2041->config->state != CONFIG_READY)
		return 0;

	int i;

	// Reset the dirty bits
	for(i = 0; i < TMC2041_REGISTER_COUNT; i++)
		tmc2041->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc2041->config->state        = CONFIG_RESET;
	tmc2041->config->configIndex  = 0;

	return 1;
}

uint8_t tmc2041_restore(TMC2041TypeDef *tmc2041)
{
	if(tmc2041->config->state != CONFIG_READY)
		return 0;

	tmc2041->config->state        = CONFIG_RESTORE;
	tmc2041->config->configIndex  = 0;

	return 1;
}

void tmc2041_setRegisterResetState(TMC2041TypeDef *tmc2041, const int32_t *resetState)
{
	uint32_t i;
	for(i = 0; i < TMC2041_REGISTER_COUNT; i++)
		tmc2041->registerResetState[i] = resetState[i];
}

void tmc2041_setCallback(TMC2041TypeDef *tmc2041, tmc2041_callback callback)
{
	tmc2041->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC2041TypeDef *tmc2041)
{
	uint8_t *ptr = &tmc2041->config->configIndex;
	const int32_t *settings;

	if(tmc2041->config->state == CONFIG_RESTORE)
	{
		settings = tmc2041->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2041_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2041->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc2041->registerResetState;
		// Find the next restorable register
		while((*ptr < TMC2041_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2041->registerAccess[*ptr]))
			(*ptr)++;
	}

	if(*ptr < TMC2041_REGISTER_COUNT)
	{
		tmc2041_writeInt(tmc2041, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2041->config->callback)
			((tmc2041_callback)tmc2041->config->callback)(tmc2041, tmc2041->config->state);

		tmc2041->config->state = CONFIG_READY;
	}
}

void tmc2041_periodicJob(TMC2041TypeDef *tmc2041, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2041->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2041);
		return;
	}
}

