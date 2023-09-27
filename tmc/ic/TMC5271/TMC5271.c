/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include <tmc/ic/TMC5271/TMC5271.h>


// Initialize a TMC5271 IC.
// This function requires:
//     - tmc5271: The pointer to a TMC5271TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc5271_init(TMC5271TypeDef *tmc5271, uint8_t channel, ConfigurationTypeDef *config)
{
	for(uint8_t motor = 0; motor < TMC5271_MOTORS; motor++)
	{
		tmc5271->velocity[motor] = 0;
		tmc5271->oldX[motor] = 0;
	}

	tmc5271->config               = config;
	tmc5271->config->callback     = NULL;
	tmc5271->config->channel      = channel;
	tmc5271->config->configIndex  = 0;
	tmc5271->config->state        = CONFIG_READY;

}

// Reset the TMC5271.
uint8_t tmc5271_reset(TMC5271TypeDef *tmc5271)
{
	if(tmc5271->config->state != CONFIG_READY)
		return false;

	tmc5271->config->state        = CONFIG_RESET;
	tmc5271->config->configIndex  = 0;

	return true;
}

// Register a function to be called after completion of the configuration mechanism
void tmc5271_setCallback(TMC5271TypeDef *tmc5271, tmc5271_callback callback)
{
	tmc5271->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc5271_getSlaveAddress(TMC5271TypeDef *tmc5271)
{
	return tmc5271->slaveAddress;
}

void tmc5271_setSlaveAddress(TMC5271TypeDef *tmc5271, uint8_t slaveAddress)
{
	tmc5271->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC5271TypeDef *tmc5271)
{
	UNUSED(tmc5271);
}

// Call this periodically
void tmc5271_periodicJob(TMC5271TypeDef *tmc5271, uint32_t tick)
{
	uint32_t tickDiff;

	if(tmc5271->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5271);
		return;
	}

	int32_t x;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5271->oldTick) >= 5)
	{
		for(uint8_t motor = 0; motor < TMC5271_MOTORS; motor++)
		{
			x = tmc5271_readInt(tmc5271, TMC5271_XACTUAL);
			tmc5271->velocity[motor] = (uint32_t) ((float32_t) (abs(x - tmc5271->oldX[motor]) / (float32_t) tickDiff) * (float32_t) 1048.576);
			tmc5271->oldX[motor] = x;
		}
		tmc5271->oldTick  = tick;
	}
}


void tmc5271_rotate(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5271_MOTORS)
		return;

	tmc5271_writeInt(tmc5271, TMC5271_VMAX, abs(velocity));
	TMC5271_FIELD_WRITE(tmc5271, TMC5271_RAMPMODE, TMC5271_RAMPMODE_MASK, TMC5271_RAMPMODE_SHIFT,  (velocity >= 0) ? TMC5271_MODE_VELPOS : TMC5271_MODE_VELNEG);

}

void tmc5271_right(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	return tmc5271_rotate(tmc5271, motor, velocity);
}

void tmc5271_left(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	return tmc5271_rotate(tmc5271, motor, -velocity);
}

void tmc5271_stop(TMC5271TypeDef *tmc5271, uint8_t motor)
{
	return tmc5271_rotate(tmc5271, motor, 0);
}

void tmc5271_moveTo(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5271_MOTORS)
		return;

	TMC5271_FIELD_WRITE(tmc5271, TMC5271_RAMPMODE, TMC5271_RAMPMODE_MASK, TMC5271_RAMPMODE_SHIFT, TMC5271_MODE_POSITION);

	tmc5271_writeInt(tmc5271, TMC5271_VMAX, velocityMax);
	tmc5271_writeInt(tmc5271, TMC5271_XTARGET, position);
}

void tmc5271_moveBy(TMC5271TypeDef *tmc5271, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5271_readInt(tmc5271, TMC5271_XACTUAL);

	return tmc5271_moveTo(tmc5271, motor, *ticks, velocityMax);
}


uint8_t tmc5271_consistencyCheck(TMC5271TypeDef *tmc5271)
{
	if(tmc5271->config->state != CONFIG_READY)
		return 0;
	return 0;
}
