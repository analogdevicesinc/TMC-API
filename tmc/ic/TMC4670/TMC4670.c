/*
 * TMC4670.c
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */
#include "TMC4670.h"

#define STATE_NOTHING_TO_DO    0
#define STATE_START_INIT       1
#define STATE_WAIT_INIT_TIME   2
#define STATE_ESTIMATE_OFFSET  3

// => SPI wrapper
extern uint8_t tmc4670_readwriteByte(uint8_t motor, uint8_t data, uint8_t lastTransfer);
// <= SPI wrapper

// spi access
int32_t tmc4670_readInt(uint8_t motor, uint8_t address)
{
	// clear write bit
	address &= 0x7F;

	// write address
	tmc4670_readwriteByte(motor, address, false);

	// read data
	int32_t value = tmc4670_readwriteByte(motor, 0, false);
	value <<= 8;
	value |= tmc4670_readwriteByte(motor, 0, false);
	value <<= 8;
	value |= tmc4670_readwriteByte(motor, 0, false);
	value <<= 8;
	value |= tmc4670_readwriteByte(motor, 0, true);

	return value;
}

void tmc4670_writeInt(uint8_t motor, uint8_t address, int32_t value)
{
	// write address
	tmc4670_readwriteByte(motor, address|0x80, false);

	// write value
	tmc4670_readwriteByte(motor, 0xFF & (value>>24), false);
	tmc4670_readwriteByte(motor, 0xFF & (value>>16), false);
	tmc4670_readwriteByte(motor, 0xFF & (value>>8), false);
	tmc4670_readwriteByte(motor, 0xFF & (value>>0), true);
}

uint16_t tmc4670_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel)
{
	int32_t registerValue = tmc4670_readInt(motor, address);

	// read one channel
	switch(channel)
	{
	case BIT_0_TO_15:
		return (registerValue & 0xFFFF);
		break;
	case BIT_16_TO_31:
		return ((registerValue >> 16) & 0xFFFF);
		break;
	}
	return 0;
}

void tmc4670_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value)
{
	// read actual register content
	int32_t registerValue = tmc4670_readInt(motor, address);

	// update one channel
	switch(channel)
	{
	case BIT_0_TO_15:
		registerValue &= 0xFFFF0000;
		registerValue |= value;
		break;
	case BIT_16_TO_31:
		registerValue &= 0x0000FFFF;
		registerValue |= (value << 16);
		break;
	}
	// write the register
	tmc4670_writeInt(motor, address, registerValue);
}

void tmc4670_switchToMotionMode(uint8_t motor, uint8_t mode)
{
	// switch motion mode
	uint32_t actualModeRegister = tmc4670_readInt(motor, TMC4670_MODE_RAMP_MODE_MOTION);
	actualModeRegister &= 0xFFFFFF00;
	actualModeRegister |= mode;
	tmc4670_writeInt(motor, TMC4670_MODE_RAMP_MODE_MOTION, actualModeRegister);
}

void tmc4670_setTargetTorque_raw(uint8_t motor, int32_t targetTorque)
{
	tmc4670_switchToMotionMode(motor, TMC4670_MOTION_MODE_TORQUE);
	tmc4670_writeRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, targetTorque);
}

int32_t tmc4670_getTargetTorque_raw(uint8_t motor)
{
	tmc4670_writeInt(motor, TMC4670_INTERIM_ADDR, 0);
	return (int32_t) tmc4670_readInt(motor, TMC4670_INTERIM_DATA);
}

int32_t tmc4670_getActualTorque_raw(uint8_t motor)
{
	return (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_ACTUAL, BIT_16_TO_31);
}

int32_t tmc4670_getActualRampTorque_raw(uint8_t motor)
{
	// no ramp implemented
	UNUSED(motor);
	return 0;
}

void tmc4670_setTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetTorque)
{
	tmc4670_switchToMotionMode(motor, TMC4670_MOTION_MODE_TORQUE);
	tmc4670_writeRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, (targetTorque * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4670_getTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	return (tmc4670_getTargetTorque_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4670_getActualTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	return (tmc4670_getActualTorque_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4670_getActualRampTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	// no ramp implemented
	UNUSED(motor);
	UNUSED(torqueMeasurementFactor);
	return 0;
}

void tmc4670_setTargetFlux_raw(uint8_t motor, int32_t targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4670_writeRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, targetFlux);
}

int32_t tmc4670_getTargetFlux_raw(uint8_t motor)
{
	tmc4670_writeInt(motor, TMC4670_INTERIM_ADDR, 1);
	return (int32_t) tmc4670_readInt(motor, TMC4670_INTERIM_DATA);
}

int32_t tmc4670_getActualFlux_raw(uint8_t motor)
{
	return (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_ACTUAL, BIT_0_TO_15);
}

void tmc4670_setTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4670_writeRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, (targetFlux * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4670_getTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	return (tmc4670_getTargetFlux_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

int32_t tmc4670_getActualFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	return (tmc4670_getActualFlux_raw(motor) * (int32_t) torqueMeasurementFactor) / 256;
}

void tmc4670_setTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t max)
{
	tmc4670_writeRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15, (max * 256) / (int32_t) torqueMeasurementFactor);
}

int32_t tmc4670_getTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor)
{
	return ((int32_t) tmc4670_readRegister16BitValue(motor, TMC4670_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15) * (int32_t) torqueMeasurementFactor) / 256;
}

void tmc4670_setTargetVelocity(uint8_t motor, int32_t targetVelocity)
{
	tmc4670_switchToMotionMode(motor, TMC4670_MOTION_MODE_VELOCITY);
	tmc4670_writeInt(motor, TMC4670_PID_VELOCITY_TARGET, targetVelocity);
}

int32_t tmc4670_getTargetVelocity(uint8_t motor)
{
	tmc4670_writeInt(motor, TMC4670_INTERIM_ADDR, 2);
	return (int32_t) tmc4670_readInt(motor, TMC4670_INTERIM_DATA);
}

int32_t tmc4670_getActualVelocity(uint8_t motor)
{
	return (int32_t) tmc4670_readInt(motor, TMC4670_PID_VELOCITY_ACTUAL);
}

int32_t tmc4670_getActualRampVelocity(uint8_t motor)
{
	UNUSED(motor);
	// no ramp implemented
	return 0;
}

void tmc4670_setAbsolutTargetPosition(uint8_t motor, int32_t targetPosition)
{
	tmc4670_switchToMotionMode(motor, TMC4670_MOTION_MODE_POSITION);
	tmc4670_writeInt(motor, TMC4670_PID_POSITION_TARGET, targetPosition);
}

void tmc4670_setRelativeTargetPosition(uint8_t motor, int32_t relativePosition)
{
	tmc4670_switchToMotionMode(motor, TMC4670_MOTION_MODE_POSITION);
	// determine actual position and add relative position ticks
	tmc4670_writeInt(motor, TMC4670_PID_POSITION_TARGET, (int32_t) tmc4670_readInt(motor, TMC4670_PID_POSITION_ACTUAL) + relativePosition);
}

int32_t tmc4670_getTargetPosition(uint8_t motor)
{
	return (int32_t) tmc4670_readInt(motor, TMC4670_PID_POSITION_TARGET);
}

void tmc4670_setActualPosition(uint8_t motor, int32_t actualPosition)
{
	tmc4670_writeInt(motor, TMC4670_PID_POSITION_ACTUAL, actualPosition);
}

int32_t tmc4670_getActualPosition(uint8_t motor)
{
	return (int32_t) tmc4670_readInt(motor, TMC4670_PID_POSITION_ACTUAL);
}

int32_t tmc4670_getActualRampPosition(uint8_t motor)
{
	UNUSED(motor);
	// no ramp implemented
	return 0;
}

// encoder initialization
void tmc4670_doEncoderInitializationMode0(uint8_t motor, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage)
{
	static uint16_t last_Phi_E_Selection = 0;
	static uint32_t last_UQ_UD_EXT = 0;
	static int16_t last_PHI_E_EXT = 0;

	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState

		// save actual set values for PHI_E_SELECTION, UQ_UD_EXT, and PHI_E_EXT
		last_Phi_E_Selection = (uint16_t) tmc4670_readRegister16BitValue(motor, TMC4670_PHI_E_SELECTION, BIT_0_TO_15);
		last_UQ_UD_EXT = (uint32_t) tmc4670_readInt(motor, TMC4670_UQ_UD_EXT);
		last_PHI_E_EXT = (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_PHI_E_EXT, BIT_0_TO_15);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4670_writeRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, 0);

		// select phi_e_ext
		tmc4670_writeRegister16BitValue(motor, TMC4670_PHI_E_SELECTION, BIT_0_TO_15, 1);

		// set an initialization voltage on UD_EXT (to the flux, not the torque!)
		tmc4670_writeRegister16BitValue(motor, TMC4670_UQ_UD_EXT, BIT_16_TO_31, 0);
		tmc4670_writeRegister16BitValue(motor, TMC4670_UQ_UD_EXT, BIT_0_TO_15, startVoltage);

		// set the "zero" angle
		tmc4670_writeRegister16BitValue(motor, TMC4670_PHI_E_EXT, BIT_0_TO_15, 0);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// wait until initialization time is over (until no more vibration on the motor)
		(*actualInitWaitTime)++;
		if(*actualInitWaitTime >= initWaitTime)
		{
			// set internal encoder value to zero
			tmc4670_writeInt(motor, TMC4670_ABN_DECODER_COUNT, 0);

			// switch back to last used UQ_UD_EXT setting
			tmc4670_writeInt(motor, TMC4670_UQ_UD_EXT, last_UQ_UD_EXT);

			// set PHI_E_EXT back to last value
			tmc4670_writeRegister16BitValue(motor, TMC4670_PHI_E_EXT, BIT_0_TO_15, last_PHI_E_EXT);

			// switch back to last used PHI_E_SELECTION setting
			tmc4670_writeRegister16BitValue(motor, TMC4670_PHI_E_SELECTION, BIT_0_TO_15, last_Phi_E_Selection);

			// go to next state
			*initState = STATE_ESTIMATE_OFFSET;
		}
		break;
	case STATE_ESTIMATE_OFFSET:
		// you can do offset estimation here (wait for N-Channel if available and save encoder value)

		// go to ready state
		*initState = 0;
		break;
	default:
		*initState = 0;
		break;
	}
}

int16_t tmc4670_getS16CircleDifference(int16_t newValue, int16_t oldValue)
{
	return (newValue - oldValue);
}

void tmc4670_doEncoderInitializationMode2(uint8_t motor, uint8_t *initState, uint16_t *actualInitWaitTime)
{
	static int16_t hall_phi_e_old = 0;
	static int16_t hall_phi_e_new = 0;
	static int16_t actual_coarse_offset = 0;

	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState
		// turn hall_mode interpolation off (read, clear bit 8, write back)
		tmc4670_writeInt(motor, TMC4670_HALL_MODE, tmc4670_readInt(motor, TMC4670_HALL_MODE) & 0xFFFFFEFF);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4670_writeRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, 0);

		// read actual hall angle
		hall_phi_e_old = (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_HALL_PHI_E_INTERPOLATED_PHI_E, BIT_0_TO_15);

		// read actual abn_decoder angle and compute difference to actual hall angle
		actual_coarse_offset = tmc4670_getS16CircleDifference(hall_phi_e_old, (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31));

		// set ABN_DECODER_PHI_E_OFFSET to actual hall-abn-difference, to use the actual hall angle for coarse initialization
		tmc4670_writeRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, actual_coarse_offset);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// read actual hall angle
		hall_phi_e_new = (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_HALL_PHI_E_INTERPOLATED_PHI_E, BIT_0_TO_15);

		// wait until hall angle changed
		if(hall_phi_e_old != hall_phi_e_new)
		{
			// estimated value = old value + diff between old and new (handle int16_t overrun)
			int16_t hall_phi_e_estimated = hall_phi_e_old + tmc4670_getS16CircleDifference(hall_phi_e_new, hall_phi_e_old)/2;

			// read actual abn_decoder angle and consider last set abn_decoder_offset
			int16_t abn_phi_e_actual = (int16_t) tmc4670_readRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31) - actual_coarse_offset;

			// set ABN_DECODER_PHI_E_OFFSET to actual estimated angle - abn_phi_e_actual difference
			tmc4670_writeRegister16BitValue(motor, TMC4670_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, tmc4670_getS16CircleDifference(hall_phi_e_estimated, abn_phi_e_actual));

			// go to ready state
			*initState = 0;
		}
		break;
	default:
		*initState = 0;
		break;
	}
}

void tmc4670_checkEncderInitialization(uint8_t motor, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage)
{
	// use the systick as 1ms timer for encoder initialization
	static uint32_t lastSystick = 0;
	if(actualSystick != lastSystick)
	{
		// needs timer to use the wait time
		if(initMode == 0)
		{
			tmc4670_doEncoderInitializationMode0(motor, initState, initWaitTime, actualInitWaitTime, startVoltage);
		}
		lastSystick = actualSystick;
	}

	// needs no timer
	if(initMode == 2)
	{
		tmc4670_doEncoderInitializationMode2(motor, initState, actualInitWaitTime);
	}
}

void tmc4670_periodicJob(uint8_t motor, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage)
{
	tmc4670_checkEncderInitialization(motor, actualSystick, initMode, initState, initWaitTime, actualInitWaitTime, startVoltage);
}

void tmc4670_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState)
{
	// allow only a new initialization if no actual initialization is running
	if(*initState == STATE_NOTHING_TO_DO)
	{
		if(mode == 0) // estimate offset
		{
			// set mode
			*initMode = 0;

			// start initialization
			*initState = 1;
		}
		else if(mode == 2) // use hall sensor signals
		{
			// set mode
			*initMode = 2;

			// start initialization
			*initState = 1;
		}
	}
}

void tmc4670_disablePWM(uint8_t motor)
{
	tmc4670_writeInt(motor, TMC4670_PWM_SV_CHOP, 0);
}
