/*
 * TMC2130.c
 *
 *  Created on: 26.01.2017
 *      Author: BS / ED
 */

#include "TMC2130.h"

// => SPI wrapper
extern void tmc2130_readWriteArray(uint8 channel, uint8 *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc2130_writeDatagram(TMC2130TypeDef *tmc2130, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	uint8 data[5] = { address | TMC2130_WRITE_BIT, x1, x2, x3, x4 };
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	int value = (x1 << 24) | (x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2130->config->shadowRegister[address] = value;
	tmc2130->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc2130_writeInt(TMC2130TypeDef *tmc2130, uint8 address, int32 value)
{
	tmc2130_writeDatagram(tmc2130, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32 tmc2130_readInt(TMC2130TypeDef *tmc2130, uint8 address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2130->registerAccess[address]))
		return tmc2130->config->shadowRegister[address];

	uint8 data[5];

	data[0] = address;
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	data[0] = address;
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	return (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
}

void tmc2130_init(TMC2130TypeDef *tmc2130, uint8 channel, ConfigurationTypeDef *config, const int32 *registerResetState)
{
	tmc2130->config = config;

	tmc2130->config->callback     = NULL;
	tmc2130->config->channel      = channel;
	tmc2130->config->configIndex  = 0;
	tmc2130->config->state        = CONFIG_READY;

	int i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		tmc2130->registerAccess[i]      = tmc2130_defaultRegisterAccess[i];
		tmc2130->registerResetState[i]  = registerResetState[i];
	}
}

uint8 tmc2130_reset(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config->state != CONFIG_READY)
		return FALSE;

	int i;

	// Reset the dirty bits
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
		tmc2130->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc2130->config->state        = CONFIG_RESET;
	tmc2130->config->configIndex  = 0;

	return TRUE;
}

uint8 tmc2130_restore(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config->state != CONFIG_READY)
		return FALSE;

	tmc2130->config->state        = CONFIG_RESTORE;
	tmc2130->config->configIndex  = 0;

	return TRUE;
}

void tmc2130_setRegisterResetState(TMC2130TypeDef *tmc2130, const int32 *resetState)
{
	uint32 i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
		tmc2130->registerResetState[i] = resetState[i];
}

void tmc2130_setCallback(TMC2130TypeDef *tmc2130, tmc2130_callback callback)
{
	tmc2130->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC2130TypeDef *tmc2130)
{
	uint8 *ptr = &tmc2130->config->configIndex;
	const int32 *settings;

	if(tmc2130->config->state == CONFIG_RESTORE)
	{
		settings = tmc2130->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2130->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc2130->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2130->registerAccess[*ptr]))
			(*ptr)++;
	}

	if(*ptr < TMC2130_REGISTER_COUNT)
	{
		tmc2130_writeInt(tmc2130, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2130->config->callback)
			((tmc2130_callback)tmc2130->config->callback)(tmc2130, tmc2130->config->state);

		tmc2130->config->state = CONFIG_READY;
	}
}

void tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32 tick)
{
	UNUSED(tick);

	if(tmc2130->config->state != CONFIG_READY)
		writeConfiguration(tmc2130);
}

