/*
 * TMC2208.c
 *
 *  Created on: 07.07.2017
 *      Author: LK
 */

#include "TMC2208.h"

// => SPI wrapper
extern void tmc2208_writeRegister(uint8_t motor, uint8_t address, int32_t value);
extern void tmc2208_readRegister(uint8_t motor, uint8_t address, int32_t *value);
// <= SPI wrapper

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
		tmc2208_writeRegister(tmc2208->config->channel, *ptr, settings[*ptr]);
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
