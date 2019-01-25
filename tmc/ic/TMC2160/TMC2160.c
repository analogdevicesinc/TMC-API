/*
 * TMC2160.c
 *
 *  Created on: 13.08.2018
 *      Author: LK
 */

#include "TMC2160.h"

// => SPI wrapper
extern void tmc2160_readWriteArray(uint8 channel, uint8 *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc2160_writeDatagram(TMC2160TypeDef *tmc2160, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	uint8 data[5] = { address | TMC2160_WRITE_BIT, x1, x2, x3, x4 };
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	int value = (x1 << 24) | (x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2160->config->shadowRegister[address] = value;
	tmc2160->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc2160_writeInt(TMC2160TypeDef *tmc2160, uint8 address, int32 value)
{
	tmc2160_writeDatagram(tmc2160, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32 tmc2160_readInt(TMC2160TypeDef *tmc2160, uint8 address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2160->registerAccess[address]))
		return tmc2160->config->shadowRegister[address];

	uint8 data[5];

	data[0] = address;
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	data[0] = address;
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	return (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
}

void tmc2160_init(TMC2160TypeDef *tmc2160, uint8 channel, ConfigurationTypeDef *config, const int32 *registerResetState)
{
	tmc2160->config = config;

	tmc2160->config->callback     = NULL;
	tmc2160->config->channel      = channel;
	tmc2160->config->configIndex  = 0;
	tmc2160->config->state        = CONFIG_READY;

	int i;
	for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
	{
		tmc2160->registerAccess[i]      = tmc2160_defaultRegisterAccess[i];
		tmc2160->registerResetState[i]  = registerResetState[i];
	}
}

void tmc2160_fillShadowRegisters(TMC2160TypeDef *tmc2160)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc2160_RegisterConstants) == 0)
		return;

	for(size_t i = 0, j = 0; i < TMC2160_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc2160->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc2160_RegisterConstants) && (tmc2160_RegisterConstants[j].address < i))
			j++;

		// If we have an entry for our current address, write the constant
		if(tmc2160_RegisterConstants[j].address == i)
			tmc2160->config->shadowRegister[i] = tmc2160_RegisterConstants[j].value;
	}
}

uint8 tmc2160_reset(TMC2160TypeDef *tmc2160)
{
	if(tmc2160->config->state != CONFIG_READY)
		return FALSE;

	int i;

	// Reset the dirty bits
	for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
		tmc2160->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc2160->config->state        = CONFIG_RESET;
	tmc2160->config->configIndex  = 0;

	return TRUE;
}

uint8 tmc2160_restore(TMC2160TypeDef *tmc2160)
{
	if(tmc2160->config->state != CONFIG_READY)
		return FALSE;

	tmc2160->config->state        = CONFIG_RESTORE;
	tmc2160->config->configIndex  = 0;

	return TRUE;
}

void tmc2160_setRegisterResetState(TMC2160TypeDef *tmc2160, const int32 *resetState)
{
	uint32 i;
	for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
		tmc2160->registerResetState[i] = resetState[i];
}

void tmc2160_setCallback(TMC2160TypeDef *tmc2160, tmc2160_callback callback)
{
	tmc2160->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC2160TypeDef *tmc2160)
{
	uint8 *ptr = &tmc2160->config->configIndex;
	const int32 *settings;

	if(tmc2160->config->state == CONFIG_RESTORE)
	{
		settings = tmc2160->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2160_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2160->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc2160->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2160_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2160->registerAccess[*ptr]))
			(*ptr)++;
	}

	if(*ptr < TMC2160_REGISTER_COUNT)
	{
		tmc2160_writeInt(tmc2160, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2160->config->callback)
			((tmc2160_callback)tmc2160->config->callback)(tmc2160, tmc2160->config->state);

		tmc2160->config->state = CONFIG_READY;
	}
}

void tmc2160_periodicJob(TMC2160TypeDef *tmc2160, uint32 tick)
{
	UNUSED(tick);

	if(tmc2160->config->state != CONFIG_READY)
		writeConfiguration(tmc2160);
}

