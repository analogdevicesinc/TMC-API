/*
 * TMC2208.c
 *
 *  Created on: 07.07.2017
 *      Author: LK
 */

#include "TMC2208.h"

// => SPI wrapper
extern void tmc2208_writeRegister(uint8 motor, uint8 address, int32 value);
extern void tmc2208_readRegister(uint8 motor, uint8 address, int32 *value);
// <= SPI wrapper

void tmc2208_init(TMC2208TypeDef *tmc2208, uint8 channel, ConfigurationTypeDef *tmc2208_config, const int32 *registerResetState)
{
	tmc2208->velocity  = 0;
	tmc2208->oldTick   = 0;
	tmc2208->oldX      = 0;
	tmc2208->slave     = 0;
	tmc2208->config    = tmc2208_config;

	/*
	 * TODO: Config initialization
	 * We can either explicitly initialize in each IC's init respectively,
	 * or do that with a seperate function config_init where also the channel is set.
	 */
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
	uint8 *ptr = &tmc2208->config->configIndex;
	const int32 *settings;

	if(tmc2208->config->state == CONFIG_RESTORE)
	{
		settings = tmc2208->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2208_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2208->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc2208->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2208_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2208->registerAccess[*ptr]))
			(*ptr)++;

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

void tmc2208_periodicJob(TMC2208TypeDef *tmc2208, uint32 tick)
{
	if(tmc2208->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2208);
		return;
	}

	// Calculate velocity v = dx/dt
	if((tick - tmc2208->oldTick) >= 5)
	{
		tmc2208->oldTick  = tick;
	}
}


void tmc2208_setRegisterResetState(TMC2208TypeDef *tmc2208, const int32 *resetState)
{
	for(size_t i = 0; i < TMC2208_REGISTER_COUNT; i++)
		tmc2208->registerResetState[i] = resetState[i];
}

void tmc2208_setCallback(TMC2208TypeDef *tmc2208, tmc2208_callback callback)
{
	tmc2208->config->callback = (tmc_callback_config) callback;
}

uint8 tmc2208_reset(TMC2208TypeDef *tmc2208)
{
	if(tmc2208->config->state != CONFIG_READY)
		return FALSE;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2208_REGISTER_COUNT; i++)
	{
		tmc2208->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2208->config->shadowRegister[i] = 0;
	}

	tmc2208->config->state        = CONFIG_RESET;
	tmc2208->config->configIndex  = 0;

	return TRUE;
}

uint8 tmc2208_restore(TMC2208TypeDef *tmc2208)
{
	if(tmc2208->config->state != CONFIG_READY)
		return FALSE;

	tmc2208->config->state        = CONFIG_RESTORE;
	tmc2208->config->configIndex  = 0;

	return TRUE;
}

uint8 tmc2208_get_slave(TMC2208TypeDef *tmc2208)
{
	return tmc2208->slave;
}

void tmc2208_set_slave(TMC2208TypeDef *tmc2208, uint8 slave)
{
	tmc2208->slave = slave;
}
