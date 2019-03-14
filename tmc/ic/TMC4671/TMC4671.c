/*
 * TMC4671.c
 *
 *  Created on: 30.09.2016
 *      Author: ed
 *  Updated on: 15.11.2016 (bs)
 */
#include "TMC4671.h"

#define STATE_NOTHING_TO_DO    0
#define STATE_START_INIT       1
#define STATE_WAIT_INIT_TIME   2
#define STATE_ESTIMATE_OFFSET  3

// switch between external 8 and 32 bit SPI access
// #define USE_EXTERN_32BIT_ACCESS // (used for e.g. SmartFusion2)

// => SPI wrapper
#ifdef USE_EXTERN_32BIT_ACCESS
	extern int tmc4671_readIntExt(uint8_t motor, uint8 address);
	extern void tmc4671_writeIntExt(uint8_t motor, uint8 address, int value);
#else
	extern void tmc4671_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
#endif
// <= SPI wrapper

void tmc4671_writeDatagram(uint8_t motor, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	uint8 data[5] = { address | 0x80, x1, x2, x3, x4 };
	tmc4671_readWriteArray(motor, &data[0], 5);
}

// spi access
int32_t tmc4671_readInt(uint8_t motor, uint8 address)
{
#ifdef USE_EXTERN_32BIT_ACCESS
	return tmc4671_readIntExt(motor, address);
#else
	address = TMC_ADDRESS(address);

	uint8 data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc4671_readWriteArray(motor, &data[0], 5);

	data[0] = address;
	tmc4671_readWriteArray(motor, &data[0], 5);

	return (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
#endif
}

void tmc4671_writeInt(uint8_t motor, uint8 address, int32_t value)
{
#ifdef USE_EXTERN_32BIT_ACCESS
	tmc4671_writeIntExt(motor, address, value);
#else
	tmc4671_writeDatagram(motor, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
#endif
}

u16 tmc4671_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel)
{
	s32 registerValue = tmc4671_readInt(motor, address);

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

void tmc4671_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, u16 value)
{
	// read actual register content
	s32 registerValue = tmc4671_readInt(motor, address);

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
	tmc4671_writeInt(motor, address, registerValue);
}

void tmc4671_switchToMotionMode(uint8_t motor, uint8_t mode)
{
	// switch motion mode
	u32 actualModeRegister = tmc4671_readInt(motor,TMC4671_MODE_RAMP_MODE_MOTION);
	actualModeRegister &= 0xFFFFFF00;
	actualModeRegister |= mode;
	tmc4671_writeInt(motor, TMC4671_MODE_RAMP_MODE_MOTION, actualModeRegister);
}

void tmc4671_setTargetTorque_raw(uint8_t motor, s32 targetTorque)
{
	tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_TORQUE);
	tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, targetTorque);
}

s32 tmc4671_getTargetTorque_raw(uint8_t motor)
{
	// remember last set index
	u32 lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

	// get value
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 0);
	s32 value = (s32)tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);
	return value;
}

s32 tmc4671_getActualTorque_raw(uint8_t motor)
{
	return (s16)tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL, BIT_16_TO_31);
}

s32 tmc4671_getActualRampTorque_raw(uint8_t motor)
{
	// no ramp implemented
	UNUSED(motor);
	return 0;
}

void tmc4671_setTargetTorque_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 targetTorque)
{
	tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_TORQUE);
	tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_16_TO_31, (targetTorque * 256) / (s32) torqueMeasurementFactor);
}

s32 tmc4671_getTargetTorque_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	return (tmc4671_getTargetTorque_raw(motor) * (s32) torqueMeasurementFactor) / 256;
}

s32 tmc4671_getActualTorque_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	return (tmc4671_getActualTorque_raw(motor) * (s32) torqueMeasurementFactor) / 256;
}

s32 tmc4671_getTargetTorqueFluxSum_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	// remember last set index
	u32 lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

	// get target torque value
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 0);
	s32 torque = (s32) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

	// get target flux value
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 1);
	s32 flux = (s32) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);

	return (((s32)flux+(s32)torque) * (s32)torqueMeasurementFactor) / 256;
}

s32 tmc4671_getActualTorqueFluxSum_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	s32 registerValue = tmc4671_readInt(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL);
	s16 flux = (registerValue & 0xFFFF);
	s16 torque = ((registerValue >> 16) & 0xFFFF);
	return (((s32)flux+(s32)torque) * (s32)torqueMeasurementFactor) / 256;
}

s32 tmc4671_getActualRampTorque_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	// no ramp implemented
	UNUSED(motor);
	UNUSED(torqueMeasurementFactor);
	return 0;
}

void tmc4671_setTargetFlux_raw(uint8_t motor, s32 targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, targetFlux);
}

s32 tmc4671_getTargetFlux_raw(uint8_t motor)
{
	// remember last set index
	u32 lastIndex = tmc4671_readInt(motor, TMC4671_INTERIM_ADDR);

	// get value
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, 1);
	s32 value = (s32) tmc4671_readInt(motor, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeInt(motor, TMC4671_INTERIM_ADDR, lastIndex);
	return value;
}

s32 tmc4671_getActualFlux_raw(uint8_t motor)
{
	return (s16) tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_ACTUAL, BIT_0_TO_15);
}

void tmc4671_setTargetFlux_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_TARGET, BIT_0_TO_15, (targetFlux * 256) / (s32) torqueMeasurementFactor);
}

s32 tmc4671_getTargetFlux_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	return (tmc4671_getTargetFlux_raw(motor) * (s32) torqueMeasurementFactor) / 256;
}

s32 tmc4671_getActualFlux_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	return (tmc4671_getActualFlux_raw(motor) * (s32) torqueMeasurementFactor) / 256;
}

void tmc4671_setTorqueFluxLimit_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 max)
{
	tmc4671_writeRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15, (max * 256) / (s32) torqueMeasurementFactor);
}

s32 tmc4671_getTorqueFluxLimit_mA(uint8_t motor, u16 torqueMeasurementFactor)
{
	return ((s32) tmc4671_readRegister16BitValue(motor, TMC4671_PID_TORQUE_FLUX_LIMITS, BIT_0_TO_15) * (s32) torqueMeasurementFactor) / 256;
}

void tmc4671_setTargetVelocity(uint8_t motor, s32 targetVelocity)
{
	tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_VELOCITY);
	tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_TARGET, targetVelocity);
}

s32 tmc4671_getTargetVelocity(uint8_t motor)
{
	return (s32) tmc4671_readInt(motor, TMC4671_PID_VELOCITY_TARGET);
}

s32 tmc4671_getActualVelocity(uint8_t motor)
{
	return (s32) tmc4671_readInt(motor, TMC4671_PID_VELOCITY_ACTUAL);
}

s32 tmc4671_getActualRampVelocity(uint8_t motor)
{
	UNUSED(motor);
	// no ramp implemented
	return 0;
}

void tmc4671_setAbsolutTargetPosition(uint8_t motor, s32 targetPosition)
{
	tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_POSITION);
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_TARGET, targetPosition);
}

void tmc4671_setRelativeTargetPosition(uint8_t motor, s32 relativePosition)
{
	tmc4671_switchToMotionMode(motor, TMC4671_MOTION_MODE_POSITION);
	// determine actual position and add relative position ticks
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_TARGET, (s32) tmc4671_readInt(motor, TMC4671_PID_POSITION_ACTUAL) + relativePosition);
}

s32 tmc4671_getTargetPosition(uint8_t motor)
{
	return (s32) tmc4671_readInt(motor, TMC4671_PID_POSITION_TARGET);
}

void tmc4671_setActualPosition(uint8_t motor, s32 actualPosition)
{
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_ACTUAL, actualPosition);
}

s32 tmc4671_getActualPosition(uint8_t motor)
{
	return (s32) tmc4671_readInt(motor, TMC4671_PID_POSITION_ACTUAL);
}

s32 tmc4671_getActualRampPosition(uint8_t motor)
{
	UNUSED(motor);
	// no ramp implemented
	return 0;
}

// encoder initialization
void tmc4671_doEncoderInitializationMode0(uint8_t motor, uint8_t *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage)
{
	static uint16 last_Phi_E_Selection = 0;
	static uint32 last_UQ_UD_EXT = 0;
	static s16 last_PHI_E_EXT = 0;

	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState

		// save actual set values for PHI_E_SELECTION, UQ_UD_EXT, and PHI_E_EXT
		last_Phi_E_Selection = (u16) tmc4671_readRegister16BitValue(motor, TMC4671_PHI_E_SELECTION, BIT_0_TO_15);
		last_UQ_UD_EXT = (u32) tmc4671_readInt(motor, TMC4671_UQ_UD_EXT);
		last_PHI_E_EXT = (s16) tmc4671_readRegister16BitValue(motor, TMC4671_PHI_E_EXT, BIT_0_TO_15);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4671_writeRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, 0);

		// select phi_e_ext
		tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_SELECTION, BIT_0_TO_15, 1);

		// set an initialization voltage on UD_EXT (to the flux, not the torque!)
		tmc4671_writeRegister16BitValue(motor, TMC4671_UQ_UD_EXT, BIT_16_TO_31, 0);
		tmc4671_writeRegister16BitValue(motor, TMC4671_UQ_UD_EXT, BIT_0_TO_15, startVoltage);

		// set the "zero" angle
		tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_EXT, BIT_0_TO_15, 0);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// wait until initialization time is over (until no more vibration on the motor)
		(*actualInitWaitTime)++;
		if(*actualInitWaitTime >= initWaitTime)
		{
			// set internal encoder value to zero
			tmc4671_writeInt(motor, TMC4671_ABN_DECODER_COUNT, 0);

			// switch back to last used UQ_UD_EXT setting
			tmc4671_writeInt(motor, TMC4671_UQ_UD_EXT, last_UQ_UD_EXT);

			// set PHI_E_EXT back to last value
			tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_EXT, BIT_0_TO_15, last_PHI_E_EXT);

			// switch back to last used PHI_E_SELECTION setting
			tmc4671_writeRegister16BitValue(motor, TMC4671_PHI_E_SELECTION, BIT_0_TO_15, last_Phi_E_Selection);

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

s16 tmc4671_getS16CircleDifference(s16 newValue, s16 oldValue)
{
	return (newValue - oldValue);
}

void tmc4671_doEncoderInitializationMode2(uint8_t motor, uint8_t *initState, u16 *actualInitWaitTime)
{
	static s16 hall_phi_e_old = 0;
	static s16 hall_phi_e_new = 0;
	static s16 actual_coarse_offset = 0;

	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState
		// turn hall_mode interpolation off (read, clear bit 8, write back)
		tmc4671_writeInt(motor, TMC4671_HALL_MODE, tmc4671_readInt(motor, TMC4671_HALL_MODE) & 0xFFFFFEFF);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4671_writeRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, 0);

		// read actual hall angle
		hall_phi_e_old = (s16) tmc4671_readRegister16BitValue(motor, TMC4671_HALL_PHI_E_INTERPOLATED_PHI_E, BIT_0_TO_15);

		// read actual abn_decoder angle and compute difference to actual hall angle
		actual_coarse_offset = tmc4671_getS16CircleDifference(hall_phi_e_old, (s16) tmc4671_readRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31));

		// set ABN_DECODER_PHI_E_OFFSET to actual hall-abn-difference, to use the actual hall angle for coarse initialization
		tmc4671_writeRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, actual_coarse_offset);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// read actual hall angle
		hall_phi_e_new = (s16) tmc4671_readRegister16BitValue(motor, TMC4671_HALL_PHI_E_INTERPOLATED_PHI_E, BIT_0_TO_15);

		// wait until hall angle changed
		if(hall_phi_e_old != hall_phi_e_new)
		{
			// estimated value = old value + diff between old and new (handle s16 overrun)
			s16 hall_phi_e_estimated = hall_phi_e_old + tmc4671_getS16CircleDifference(hall_phi_e_new, hall_phi_e_old)/2;

			// read actual abn_decoder angle and consider last set abn_decoder_offset
			s16 abn_phi_e_actual = (s16) tmc4671_readRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M, BIT_16_TO_31) - actual_coarse_offset;

			// set ABN_DECODER_PHI_E_OFFSET to actual estimated angle - abn_phi_e_actual difference
			tmc4671_writeRegister16BitValue(motor, TMC4671_ABN_DECODER_PHI_E_PHI_M_OFFSET, BIT_16_TO_31, tmc4671_getS16CircleDifference(hall_phi_e_estimated, abn_phi_e_actual));

			// go to ready state
			*initState = 0;
		}
		break;
	default:
		*initState = 0;
		break;
	}
}

void tmc4671_checkEncderInitialization(uint8_t motor, u32 actualSystick, uint8_t initMode, uint8_t *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage)
{
	// use the systick as 1ms timer for encoder initialization
	static uint32 lastSystick = 0;
	if(actualSystick != lastSystick)
	{
		// needs timer to use the wait time
		if(initMode == 0)
		{
			tmc4671_doEncoderInitializationMode0(motor, initState, initWaitTime, actualInitWaitTime, startVoltage);
		}
		lastSystick = actualSystick;
	}

	// needs no timer
	if(initMode == 2)
	{
		tmc4671_doEncoderInitializationMode2(motor, initState, actualInitWaitTime);
	}
}

void tmc4671_periodicJob(uint8_t motor, u32 actualSystick, uint8_t initMode, uint8_t *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage)
{
	tmc4671_checkEncderInitialization(motor, actualSystick, initMode, initState, initWaitTime, actualInitWaitTime, startVoltage);
}

void tmc4671_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState)
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

void tmc4671_updatePhiSelectionAndInitialize(uint8_t motor, uint8_t actualPhiESelection, uint8_t desiredPhiESelection, uint8_t initMode, uint8_t *initState)
{
	if (actualPhiESelection != desiredPhiESelection)
	{
		tmc4671_writeInt(motor, TMC4671_PHI_E_SELECTION, desiredPhiESelection);

		switch(desiredPhiESelection)
		{
			case 3:
				tmc4671_startEncoderInitialization(initMode, &initMode, initState);
				break;
		}
	}
}

// =====

void tmc4671_disablePWM(uint8_t motor)
{
	tmc4671_writeInt(motor, TMC4671_PWM_SV_CHOP, 0);
}

uint8_t tmc4671_getPolePairs(uint8_t motor)
{
	return FIELD_GET(tmc4671_readInt(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS), TMC4671_N_POLE_PAIRS_MASK, TMC4671_N_POLE_PAIRS_SHIFT);
}

void tmc4671_setPolePairs(uint8_t motor, uint8_t polePairs)
{
	TMC4671_FIELD_UPDATE(motor, TMC4671_MOTOR_TYPE_N_POLE_PAIRS, TMC4671_N_POLE_PAIRS_MASK, TMC4671_N_POLE_PAIRS_SHIFT, polePairs);
}

u16 tmc4671_getAdcI0Offset(uint8_t motor)
{
	return FIELD_GET(tmc4671_readInt(motor, TMC4671_ADC_I0_SCALE_OFFSET), TMC4671_ADC_I0_OFFSET_MASK, TMC4671_ADC_I0_OFFSET_SHIFT);
}

void tmc4671_setAdcI0Offset(uint8_t motor, u16 offset)
{
	TMC4671_FIELD_UPDATE(motor, TMC4671_ADC_I0_SCALE_OFFSET, TMC4671_ADC_I0_OFFSET_MASK, TMC4671_ADC_I0_OFFSET_SHIFT, offset);
}

u16 tmc4671_getAdcI1Offset(uint8_t motor)
{
	return FIELD_GET(tmc4671_readInt(motor, TMC4671_ADC_I1_SCALE_OFFSET), TMC4671_ADC_I1_OFFSET_MASK, TMC4671_ADC_I1_OFFSET_SHIFT);
}

void tmc4671_setAdcI1Offset(uint8_t motor, u16 offset)
{
	TMC4671_FIELD_UPDATE(motor, TMC4671_ADC_I1_SCALE_OFFSET, TMC4671_ADC_I1_OFFSET_MASK, TMC4671_ADC_I1_OFFSET_SHIFT, offset);
}

void tmc4671_setTorqueFluxPI(uint8_t motor, u16 pParameter, u16 iParameter)
{
	tmc4671_writeInt(motor, TMC4671_PID_FLUX_P_FLUX_I, ((u32)pParameter << 16) | (u32)iParameter);
	tmc4671_writeInt(motor, TMC4671_PID_TORQUE_P_TORQUE_I, ((u32)pParameter << 16) | (u32)iParameter);
}

void tmc4671_setVelocityPI(uint8_t motor, u16 pParameter, u16 iParameter)
{
	tmc4671_writeInt(motor, TMC4671_PID_VELOCITY_P_VELOCITY_I, ((u32)pParameter << 16) | (u32)iParameter);
}

void tmc4671_setPositionPI(uint8_t motor, u16 pParameter, u16 iParameter)
{
	tmc4671_writeInt(motor, TMC4671_PID_POSITION_P_POSITION_I, ((u32)pParameter << 16) | (u32)iParameter);
}

int tmc4671_readFieldWithDependency(uint8_t motor, uint8_t reg, uint8_t dependsReg, u32 dependsValue, u32 mask, uint8_t shift)
{
	// remember old depends value
	u32 lastDependsValue = tmc4671_readInt(motor, dependsReg);

	// set needed depends value
	tmc4671_writeInt(motor, dependsReg, dependsValue);
	u32 value = FIELD_GET(tmc4671_readInt(motor, reg), mask, shift);

	// set old depends value
	tmc4671_writeInt(motor, dependsReg, lastDependsValue);
	return value;
}
