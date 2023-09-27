/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2240.h"
extern void tmc2240_writeInt(TMC2240TypeDef *tmc2240, uint8_t address, int32_t value);


// Initialize a TMC2240 IC.
// This function requires:
//     - tmc2240: The pointer to a TMC2240TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc2240_init(TMC2240TypeDef *tmc2240, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc2240->velocity  = 0;
	tmc2240->oldTick   = 0;
	tmc2240->oldX      = 0;

	tmc2240->config               = config;
	tmc2240->config->callback     = NULL;
	tmc2240->config->channel      = channel;
	tmc2240->config->configIndex  = 0;
	tmc2240->config->state        = CONFIG_READY;

	size_t i;
	for(i = 0; i < TMC2240_REGISTER_COUNT; i++)
	{
		tmc2240->registerAccess[i]      = tmc2240_defaultRegisterAccess[i];
		tmc2240->registerResetState[i]  = registerResetState[i];
	}
}

// Reset the TMC2240.
uint8_t tmc2240_reset(TMC2240TypeDef *tmc2240)
{
	if(tmc2240->config->state != CONFIG_READY)
		return false;

	tmc2240->config->state        = CONFIG_RESET;
	tmc2240->config->configIndex  = 0;

	return true;
}

// Restore the TMC2240 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc2240_restore(TMC2240TypeDef *tmc2240)
{
	if(tmc2240->config->state != CONFIG_READY)
		return false;

	tmc2240->config->state        = CONFIG_RESTORE;
	tmc2240->config->configIndex  = 0;

	return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc2240_setRegisterResetState(TMC2240TypeDef *tmc2240, const int32_t *resetState)
{
	size_t i;
	for(i = 0; i < TMC2240_REGISTER_COUNT; i++)
	{
		tmc2240->registerResetState[i] = resetState[i];
	}
}

// Register a function to be called after completion of the configuration mechanism
void tmc2240_setCallback(TMC2240TypeDef *tmc2240, tmc2240_callback callback)
{
	tmc2240->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc2240_getSlaveAddress(TMC2240TypeDef *tmc2240)
{
	return tmc2240->slaveAddress;
}

void tmc2240_setSlaveAddress(TMC2240TypeDef *tmc2240, uint8_t slaveAddress)
{
	tmc2240->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC2240TypeDef *tmc2240)
{
	uint8_t *ptr = &tmc2240->config->configIndex;
	const int32_t *settings;

	settings = tmc2240->registerResetState;
	// Find the next resettable register
	while((*ptr < TMC2240_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2240->registerAccess[*ptr]))
		{
		(*ptr)++;
		}
//	}

	if(*ptr < TMC2240_REGISTER_COUNT)
	{
		tmc2240_writeInt(tmc2240, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2240->config->callback)
		{
			((tmc2240_callback)tmc2240->config->callback)(tmc2240, tmc2240->config->state);
		}

		tmc2240->config->state = CONFIG_READY;
	}
}

// Call this periodically
void tmc2240_periodicJob(TMC2240TypeDef *tmc2240, uint32_t tick)
{
	UNUSED(tick);
	if(tmc2240->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2240);
		return;
	}
}


