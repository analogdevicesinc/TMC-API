/*
 * TMC4330.c
 *
 *  Created on: 18.07.2017
 *      Author: LK
 */

#include "TMC4330.h"

// => SPI wrapper
// Send [length] bytes stored in the [data] array over SPI and overwrite [data]
// with the replies. data[0] is the first byte sent and received.
extern void tmc4330_readWriteArray(uint8 channel, uint8 *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc4330_writeDatagram(TMC4330TypeDef *tmc4330, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	int value;
	uint8 data[5] = { address | TMC4330_WRITE_BIT, x1, x2, x3, x4 };

	tmc4330_readWriteArray(tmc4330->config->channel, &data[0], 5);

	tmc4330->status = data[0];

	value = (x1 << 24) | (x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc4330->config->shadowRegister[address] = value;
	tmc4330->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc4330_writeInt(TMC4330TypeDef *tmc4330, uint8 address, int32 value)
{
	tmc4330_writeDatagram(tmc4330, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32 tmc4330_readInt(TMC4330TypeDef *tmc4330, uint8 address)
{
	int value;
	uint8 data[5];

	address = TMC_ADDRESS(address);

	if(!TMC_IS_READABLE(tmc4330->registerAccess[address]))
		return tmc4330->config->shadowRegister[address];

	data[0] = address;
	tmc4330_readWriteArray(tmc4330->config->channel, &data[0], 5);

	data[0] = address;
	tmc4330_readWriteArray(tmc4330->config->channel, &data[0], 5);

	tmc4330->status = data[0];
	value = (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];

	return value;
}

// Provide the init function with a channel index (sent back in the SPI callback), a pointer to a ConfigurationTypeDef struct
// and a pointer to a int32 array (size 128) holding the reset values that shall be used.
void tmc4330_init(TMC4330TypeDef *tmc4330, uint8 channel, ConfigurationTypeDef *config, const int32 *registerResetState)
{
	tmc4330->velocity  = 0;
	tmc4330->oldTick   = 0;
	tmc4330->oldX      = 0;
	tmc4330->config    = config;

	tmc4330->config->callback     = NULL;
	tmc4330->config->channel      = channel;
	tmc4330->config->configIndex  = 0;
	tmc4330->config->state        = CONFIG_READY;

	int i;
	for(i = 0; i < TMC4330_REGISTER_COUNT; i++)
	{
		tmc4330->registerAccess[i]      = tmc4330_defaultRegisterAccess[i];
		tmc4330->registerResetState[i]  = registerResetState[i];
	}
}

uint8 tmc4330_reset(TMC4330TypeDef *tmc4330)
{
	if(tmc4330->config->state != CONFIG_READY)
		return 0;

	int i;

	// Reset the dirty bits
	for(i = 0; i < TMC4330_REGISTER_COUNT; i++)
		tmc4330->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc4330->config->state        = CONFIG_RESET;
	tmc4330->config->configIndex  = 0;

	return 1;
}

uint8 tmc4330_restore(TMC4330TypeDef *tmc4330)
{
	if(tmc4330->config->state != CONFIG_READY)
		return 0;

	tmc4330->config->state        = CONFIG_RESTORE;
	tmc4330->config->configIndex  = 0;

	return 1;
}

void tmc4330_setRegisterResetState(TMC4330TypeDef *tmc4330, const int32 *resetState)
{
	uint32 i;
	for(i = 0; i < TMC4330_REGISTER_COUNT; i++)
		tmc4330->registerResetState[i] = resetState[i];
}

void tmc4330_setCallback(TMC4330TypeDef *tmc4330, tmc4330_callback callback)
{
	tmc4330->config->callback = (tmc_callback_config) callback;
}

static void tmc4330_writeConfiguration(TMC4330TypeDef *tmc4330)
{
	uint8 *ptr = &tmc4330->config->configIndex;
	const int32 *settings;

	if(tmc4330->config->state == CONFIG_RESTORE)
	{
		settings = &tmc4330->config->shadowRegister[0];
		// Find the next restorable register
		while((*ptr < TMC4330_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc4330->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = &tmc4330->registerResetState[0];
		// Find the next resettable register
		while((*ptr < TMC4330_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc4330->registerAccess[*ptr]))
			(*ptr)++;
	}

	if (*ptr < TMC4330_REGISTER_COUNT) {
		tmc4330_writeInt(tmc4330, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		if(tmc4330->config->callback)
		{
			((tmc4330_callback)tmc4330->config->callback)(tmc4330, tmc4330->config->state);
		}

		tmc4330->config->state = CONFIG_READY;
	}
}

void tmc4330_periodicJob(TMC4330TypeDef *tmc4330, uint32 tick)
{
	if(tmc4330->config->state != CONFIG_READY)
	{
		tmc4330_writeConfiguration(tmc4330);
		return;
	}

	if((tick - tmc4330->oldTick) != 0)
	{
		tmc4330_calibrateClosedLoop(tmc4330, 0);
		tmc4330->oldTick = tick;
	}
}

void tmc4330_rotate(TMC4330TypeDef *tmc4330, int32 velocity)
{
	// Disable Position Mode
	TMC4330_FIELD_UPDATE(tmc4330, TMC4330_RAMPMODE, TMC4330_OPERATION_MODE_MASK, TMC4330_OPERATION_MODE_SHIFT, 0);

	tmc4330_writeInt(tmc4330, TMC4330_VMAX, tmc4330_discardVelocityDecimals(velocity));
}

void tmc4330_right(TMC4330TypeDef *tmc4330, int32 velocity)
{
	tmc4330_rotate(tmc4330, velocity);
}

void tmc4330_left(TMC4330TypeDef *tmc4330, int32 velocity)
{
	tmc4330_rotate(tmc4330, -velocity);
}

void tmc4330_stop(TMC4330TypeDef *tmc4330)
{
	tmc4330_rotate(tmc4330, 0);
}

void tmc4330_moveTo(TMC4330TypeDef *tmc4330, int32 position, uint32 velocityMax)
{
	// Enable Position Mode
	TMC4330_FIELD_UPDATE(tmc4330, TMC4330_RAMPMODE, TMC4330_OPERATION_MODE_MASK, TMC4330_OPERATION_MODE_SHIFT, 1);

	tmc4330_writeInt(tmc4330, TMC4330_VMAX, tmc4330_discardVelocityDecimals(velocityMax));

	tmc4330_writeInt(tmc4330, TMC4330_X_TARGET, position);
}

// The function will write the absolute target position to *ticks
void tmc4330_moveBy(TMC4330TypeDef *tmc4330, int32 *ticks, uint32 velocityMax)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc4330_readInt(tmc4330, TMC4330_XACTUAL);

	tmc4330_moveTo(tmc4330, *ticks, velocityMax);
}

int32 tmc4330_discardVelocityDecimals(int32 value)
{
	if(abs(value) > 8000000)
	{
		value = (value < 0) ? -8000000 : 8000000;
	}
	return value << 8;
}

static uint8 tmc4330_moveToNextFullstep(TMC4330TypeDef *tmc4330)
{
	int32 stepCount;

	// Motor must be stopped
	if(tmc4330_readInt(tmc4330, TMC4330_VACTUAL) != 0)
	{
		// Not stopped
		return 0;
	}

	// Position mode, hold mode, low velocity
	tmc4330_writeInt(tmc4330, TMC4330_RAMPMODE, 4);
	tmc4330_writeInt(tmc4330, TMC4330_VMAX, 10000 << 8);

	// Current step count
	stepCount = TMC4330_FIELD_READ(tmc4330, TMC4330_MSCNT_RD, TMC4330_MSCNT_MASK, TMC4330_MSCNT_SHIFT);
	// Get microstep value of step count (lowest 8 bits)
	stepCount = stepCount % 256;
	// Assume: 256 microsteps -> Fullsteps are at 128 + n*256
	stepCount = 128 - stepCount;

	if(stepCount == 0)
	{
		// Fullstep reached
		return 1;
	}

	// Fullstep not reached -> calculate next fullstep position
	stepCount += tmc4330_readInt(tmc4330, TMC4330_XACTUAL);
	// Move to next fullstep position
	tmc4330_writeInt(tmc4330, TMC4330_X_TARGET, stepCount);

	return 0;
}

uint8 tmc4330_calibrateClosedLoop(TMC4330TypeDef *tmc4330, uint8 worker0master1)
{
	static uint8 state = 0;
	static uint32 oldRamp;

	uint32 amax = 0;
	uint32 dmax = 0;

	if(worker0master1 && state == 0)
		state = 1;

	switch(state)
	{
	case 1:
		amax = tmc4330_readInt(tmc4330, TMC4330_AMAX);
		dmax = tmc4330_readInt(tmc4330, TMC4330_DMAX);

		// Set ramp and motion parameters
		oldRamp = tmc4330_readInt(tmc4330, TMC4330_RAMPMODE);
		tmc4330_writeInt(tmc4330, TMC4330_RAMPMODE, TMC4330_RAMP_POSITION | TMC4330_RAMP_HOLD);
		tmc4330_writeInt(tmc4330, TMC4330_AMAX, MAX(amax, 1000));
		tmc4330_writeInt(tmc4330, TMC4330_DMAX, MAX(dmax, 1000));
		tmc4330_writeInt(tmc4330, TMC4330_VMAX, 0);

		state = 2;
		break;
	case 2:
		// Clear encoder calibration bit
		TMC4330_FIELD_UPDATE(tmc4330, TMC4330_ENC_IN_CONF, TMC4330_CL_CALIBRATION_EN_MASK, TMC4330_CL_CALIBRATION_EN_SHIFT, 0);

		// Disable internal data regulation for closed loop operation in encoder config
		TMC4330_FIELD_UPDATE(tmc4330, TMC4330_ENC_IN_CONF, TMC4330_REGULATION_MODUS_MASK, TMC4330_REGULATION_MODUS_SHIFT, 1);

		if(tmc4330_moveToNextFullstep(tmc4330)) // move to next fullstep, motor must be stopped, poll until finished
			state = 3;
		break;
	case 3:
		// Start encoder calibration
		TMC4330_FIELD_UPDATE(tmc4330, TMC4330_ENC_IN_CONF, TMC4330_CL_CALIBRATION_EN_MASK, TMC4330_CL_CALIBRATION_EN_SHIFT, 1);

		state = 4;
		break;
	case 4:
		if(worker0master1)
			break;

		// Stop encoder calibration
		TMC4330_FIELD_UPDATE(tmc4330, TMC4330_ENC_IN_CONF, TMC4330_CL_CALIBRATION_EN_MASK, TMC4330_CL_CALIBRATION_EN_SHIFT, 0);
		// Enable closed loop in encoder config
		TMC4330_FIELD_UPDATE(tmc4330, TMC4330_ENC_IN_CONF, TMC4330_REGULATION_MODUS_MASK, TMC4330_REGULATION_MODUS_SHIFT, 1);
		// Restore old ramp mode, enable position mode
		tmc4330_writeInt(tmc4330, TMC4330_RAMPMODE, TMC4330_RAMP_POSITION | oldRamp);

		state = 5;
		break;
	case 5:
		state = 0;
		return 1;
		break;
	default:
		break;
	}
	return 0;
}
