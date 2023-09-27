/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2160.h"

// => SPI wrapper
extern void tmc2160_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc2160_writeDatagram(TMC2160TypeDef *tmc2160, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC2160_WRITE_BIT, x1, x2, x3, x4 };
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	int32_t value = ((uint32_t)x1 << 24) | ((uint32_t)x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2160->config->shadowRegister[address] = value;
	tmc2160->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc2160_writeInt(TMC2160TypeDef *tmc2160, uint8_t address, int32_t value)
{
	tmc2160_writeDatagram(tmc2160, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32_t tmc2160_readInt(TMC2160TypeDef *tmc2160, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2160->registerAccess[address]))
		return tmc2160->config->shadowRegister[address];

	uint8_t data[5];

	data[0] = address;
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	data[0] = address;
	tmc2160_readWriteArray(tmc2160->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

void tmc2160_init(TMC2160TypeDef *tmc2160, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc2160->config = config;

	tmc2160->config->callback     = NULL;
	tmc2160->config->channel      = channel;
	tmc2160->config->configIndex  = 0;
	tmc2160->config->state        = CONFIG_READY;

	int32_t i;
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

	size_t i, j;
	for (i = 0, j = 0; i < TMC2160_REGISTER_COUNT; i++)
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

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc2160_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if(tmc2160_RegisterConstants[j].address == i)
			tmc2160->config->shadowRegister[i] = tmc2160_RegisterConstants[j].value;
	}
}

uint8_t tmc2160_reset(TMC2160TypeDef *tmc2160)
{
	if(tmc2160->config->state != CONFIG_READY)
		return false;

	int32_t i;

	// Reset the dirty bits
	for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
		tmc2160->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc2160->config->state        = CONFIG_RESET;
	tmc2160->config->configIndex  = 0;

	return true;
}

uint8_t tmc2160_restore(TMC2160TypeDef *tmc2160)
{
	if(tmc2160->config->state != CONFIG_READY)
		return false;

	tmc2160->config->state        = CONFIG_RESTORE;
	tmc2160->config->configIndex  = 0;

	return true;
}

void tmc2160_setRegisterResetState(TMC2160TypeDef *tmc2160, const int32_t *resetState)
{
	uint32_t i;
	for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
		tmc2160->registerResetState[i] = resetState[i];
}

void tmc2160_setCallback(TMC2160TypeDef *tmc2160, tmc2160_callback callback)
{
	tmc2160->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC2160TypeDef *tmc2160)
{
	uint8_t *ptr = &tmc2160->config->configIndex;
	const int32_t *settings;

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

void tmc2160_periodicJob(TMC2160TypeDef *tmc2160, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2160->config->state != CONFIG_READY)
		writeConfiguration(tmc2160);
}

