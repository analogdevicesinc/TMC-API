/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5240.h"


// Initialize a TMC5240 IC.
// This function requires:
//     - tmc5240: The pointer to a TMC5240TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc5240_init(TMC5240TypeDef *tmc5240, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc5240->velocity  = 0;
	tmc5240->oldTick   = 0;
	tmc5240->oldX      = 0;

	tmc5240->config               = config;
	tmc5240->config->callback     = NULL;
	tmc5240->config->channel      = channel;
	tmc5240->config->configIndex  = 0;
	tmc5240->config->state        = CONFIG_READY;

	size_t i;
	for(i = 0; i < TMC5240_REGISTER_COUNT; i++)
	{
		tmc5240->registerAccess[i]      = tmc5240_defaultRegisterAccess[i];
		tmc5240->registerResetState[i]  = registerResetState[i];
	}
}

// Reset the TMC5240.
uint8_t tmc5240_reset(TMC5240TypeDef *tmc5240)
{
	if(tmc5240->config->state != CONFIG_READY)
		return false;


	tmc5240->config->state        = CONFIG_RESET;
	tmc5240->config->configIndex  = 0;

	return true;
}

// Restore the TMC5240 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc5240_restore(TMC5240TypeDef *tmc5240)
{
	if(tmc5240->config->state != CONFIG_READY)
		return false;

	tmc5240->config->state        = CONFIG_RESTORE;
	tmc5240->config->configIndex  = 0;

	return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc5240_setRegisterResetState(TMC5240TypeDef *tmc5240, const int32_t *resetState)
{
	size_t i;
	for(i = 0; i < TMC5240_REGISTER_COUNT; i++)
	{
		tmc5240->registerResetState[i] = resetState[i];
	}
}

// Register a function to be called after completion of the configuration mechanism
void tmc5240_setCallback(TMC5240TypeDef *tmc5240, tmc5240_callback callback)
{
	tmc5240->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc5240_getSlaveAddress(TMC5240TypeDef *tmc5240)
{
	return tmc5240->slaveAddress;
}

void tmc5240_setSlaveAddress(TMC5240TypeDef *tmc5240, uint8_t slaveAddress)
{
	tmc5240->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC5240TypeDef *tmc5240)
{
	uint8_t *ptr = &tmc5240->config->configIndex;
	const int32_t *settings;

	settings = tmc5240->registerResetState;
	// Find the next resettable register
	while((*ptr < TMC5240_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc5240->registerAccess[*ptr]))
		{
		(*ptr)++;
		}
//	}

	if(*ptr < TMC5240_REGISTER_COUNT)
	{
		tmc5240_writeInt(tmc5240, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc5240->config->callback)
		{
			((tmc5240_callback)tmc5240->config->callback)(tmc5240, tmc5240->config->state);
		}

		tmc5240->config->state = CONFIG_READY;
	}
}

// Call this periodically
void tmc5240_periodicJob(TMC5240TypeDef *tmc5240, uint32_t tick)
{
	if(tmc5240->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5240);
		return;
	}

	int32_t XActual;
	uint32_t tickDiff;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5240->oldTick) >= 5)
	{
		XActual = tmc5240_readInt(tmc5240, TMC5240_XACTUAL);
		// ToDo CHECK 2: API Compatibility - write alternative algorithm w/o floating point? (LH)
		tmc5240->velocity = (uint32_t) ((float32_t) ((XActual - tmc5240->oldX) / (float32_t) tickDiff) * (float32_t) 1048.576);

		tmc5240->oldX     = XActual;
		tmc5240->oldTick  = tick;
	}
}

// Rotate with a given velocity (to the right)
void tmc5240_rotate(TMC5240TypeDef *tmc5240, int32_t velocity)
{
	// Set absolute velocity
	tmc5240_writeInt(tmc5240, TMC5240_VMAX, abs(velocity));
	// Set direction
	tmc5240_writeInt(tmc5240, TMC5240_RAMPMODE, (velocity >= 0) ? TMC5240_MODE_VELPOS : TMC5240_MODE_VELNEG);
}

// Rotate to the right
void tmc5240_right(TMC5240TypeDef *tmc5240, uint32_t velocity)
{
	tmc5240_rotate(tmc5240, velocity);
}

// Rotate to the left
void tmc5240_left(TMC5240TypeDef *tmc5240, uint32_t velocity)
{
	tmc5240_rotate(tmc5240, -velocity);
}

// Stop moving
void tmc5240_stop(TMC5240TypeDef *tmc5240)
{
	tmc5240_rotate(tmc5240, 0);
}

// Move to a specified position with a given velocity
void tmc5240_moveTo(TMC5240TypeDef *tmc5240, int32_t position, uint32_t velocityMax)
{
	tmc5240_writeInt(tmc5240, TMC5240_RAMPMODE, TMC5240_MODE_POSITION);

	// VMAX also holds the target velocity in velocity mode.
	// Re-write the position mode maximum velocity here.
	tmc5240_writeInt(tmc5240, TMC5240_VMAX, velocityMax);

	tmc5240_writeInt(tmc5240, TMC5240_XTARGET, position);
}

// Move by a given amount with a given velocity
// This function will write the absolute target position to *ticks
void tmc5240_moveBy(TMC5240TypeDef *tmc5240, int32_t *ticks, uint32_t velocityMax)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5240_readInt(tmc5240, TMC5240_XACTUAL);

	tmc5240_moveTo(tmc5240, *ticks, velocityMax);
}

