/*
 * TMC2209.c
 *
 *  Created on: 18.01.2019
 *      Author: LK
 */

#include "TMC2209.h"

// => SPI wrapper
extern void tmc2209_writeRegister(uint8_t motor, uint8_t address, int32_t value);
extern void tmc2209_readRegister(uint8_t motor, uint8_t address, int32_t *value);
// <= SPI wrapper

void tmc2209_init(TMC2209TypeDef *tmc2209, uint8_t channel, ConfigurationTypeDef *tmc2209_config, const int32_t *registerResetState)
{
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
		tmc2209_writeRegister(tmc2209->config->channel, *ptr, settings[*ptr]);
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
