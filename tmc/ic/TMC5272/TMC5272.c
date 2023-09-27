/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5272.h"


// Initialize a TMC5272 IC.
// This function requires:
//     - tmc5272: The pointer to a TMC5272TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc5272_init(TMC5272TypeDef *tmc5272, uint8_t channel, ConfigurationTypeDef *config)
{
	for(uint8_t motor = 0; motor < TMC5272_MOTORS; motor++)
	{
		tmc5272->velocity[motor] = 0;
		tmc5272->oldX[motor] = 0;
	}

	tmc5272->config               = config;
	tmc5272->config->callback     = NULL;
	tmc5272->config->channel      = channel;
	tmc5272->config->configIndex  = 0;
	tmc5272->config->state        = CONFIG_READY;

}

// Reset the TMC5272.
uint8_t tmc5272_reset(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return false;


	tmc5272->config->state        = CONFIG_RESET;
	tmc5272->config->configIndex  = 0;

	return true;
}

// Restore the TMC5272 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc5272_restore(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return false;

	tmc5272->config->state        = CONFIG_RESTORE;
	tmc5272->config->configIndex  = 0;

	return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc5272_setRegisterResetState(TMC5272TypeDef *tmc5272, const int32_t *resetState)
{
	UNUSED(tmc5272);
	UNUSED(resetState);
}

// Register a function to be called after completion of the configuration mechanism
void tmc5272_setCallback(TMC5272TypeDef *tmc5272, tmc5272_callback callback)
{
	tmc5272->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc5272_getSlaveAddress(TMC5272TypeDef *tmc5272)
{
	return tmc5272->slaveAddress;
}

void tmc5272_setSlaveAddress(TMC5272TypeDef *tmc5272, uint8_t slaveAddress)
{
	tmc5272->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC5272TypeDef *tmc5272)
{
	UNUSED(tmc5272);
}

// Call this periodically
void tmc5272_periodicJob(TMC5272TypeDef *tmc5272, uint32_t tick)
{
	uint32_t tickDiff;

	if(tmc5272->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5272);
		return;
	}

	int32_t x;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5272->oldTick) >= 5)
	{
		for(uint8_t motor = 0; motor < TMC5272_MOTORS; motor++)
		{
			x = tmc5272_readInt(tmc5272, TMC5272_XACTUAL(motor));
			tmc5272->velocity[motor] = (uint32_t) ((float32_t) (abs(x - tmc5272->oldX[motor]) / (float32_t) tickDiff) * (float32_t) 1048.576);
			tmc5272->oldX[motor] = x;
		}
		tmc5272->oldTick  = tick;
	}
}


void tmc5272_rotate(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5272_MOTORS)
		return;

	tmc5272_writeInt(tmc5272, TMC5272_VMAX(motor), abs(velocity));
	if (motor == 0)
			TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M0_RAMPMODE_MASK, TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT,  (velocity >= 0) ? TMC5272_MODE_VELPOS : TMC5272_MODE_VELNEG);
	else if(motor == 1)
			TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M1_RAMPMODE_MASK, TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT,  (velocity >= 0) ? TMC5272_MODE_VELPOS : TMC5272_MODE_VELNEG);

}

void tmc5272_right(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	return tmc5272_rotate(tmc5272, motor, velocity);
}

void tmc5272_left(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	return tmc5272_rotate(tmc5272, motor, -velocity);
}

void tmc5272_stop(TMC5272TypeDef *tmc5272, uint8_t motor)
{
	return tmc5272_rotate(tmc5272, motor, 0);
}

void tmc5272_moveTo(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5272_MOTORS)
		return;

	if (motor == 0)
			TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M0_RAMPMODE_MASK, TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT, TMC5272_MODE_POSITION);
	else if (motor == 1)
			TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M1_RAMPMODE_MASK, TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT, TMC5272_MODE_POSITION);

	tmc5272_writeInt(tmc5272, TMC5272_VMAX(motor), velocityMax);
	tmc5272_writeInt(tmc5272, TMC5272_XTARGET(motor), position);
}

void tmc5272_moveBy(TMC5272TypeDef *tmc5272, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5272_readInt(tmc5272, TMC5272_XACTUAL(motor));

	return tmc5272_moveTo(tmc5272, motor, *ticks, velocityMax);
}


uint8_t tmc5272_consistencyCheck(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return 0;
	return 0;
}
