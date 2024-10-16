/*******************************************************************************
* Copyright © 2016 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "TMC4671.h"

#define TMC4671_WRITE_BIT 0x80
#define TMC4671_ADDRESS_MASK 0x7F

#define STATE_NOTHING_TO_DO    0
#define STATE_START_INIT       1
#define STATE_WAIT_INIT_TIME   2
#define STATE_ESTIMATE_OFFSET  3

// => SPI wrapper
extern void tmc4671_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// <= SPI wrapper

// spi access
int32_t tmc4671_readRegister(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC4671_ADDRESS_MASK;

	// Send the read request
	tmc4671_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void tmc4671_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC4671_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc4671_readWriteSPI(icID, &data[0], sizeof(data));
}

void tmc4671_switchToMotionMode(uint16_t icID, uint8_t mode)
{
	// switch motion mode
	tmc4671_fieldWrite(icID, TMC4671_MODE_MOTION_FIELD, mode);
}

void tmc4671_setTargetTorque_raw(uint16_t icID, int32_t targetTorque)
{
	tmc4671_switchToMotionMode(icID, TMC4671_MOTION_MODE_TORQUE);
	tmc4671_fieldWrite(icID, TMC4671_PID_TORQUE_TARGET_FIELD, targetTorque);
}

int32_t tmc4671_getTargetTorque_raw(uint16_t icID)
{
	// remember last set index
	uint32_t lastIndex = tmc4671_readRegister(icID, TMC4671_INTERIM_ADDR);

	// get value
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, 0);
	int32_t value = (int32_t)tmc4671_readRegister(icID, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, lastIndex);
	return value;
}

int32_t tmc4671_getActualTorque_raw(uint16_t icID)
{
	return tmc4671_fieldRead(icID, TMC4671_PID_TORQUE_ACTUAL_FIELD);
}

void tmc4671_setTargetTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t targetTorque)
{
	tmc4671_switchToMotionMode(icID, TMC4671_MOTION_MODE_TORQUE);
	tmc4671_fieldWrite(icID, TMC4671_PID_TORQUE_TARGET_FIELD, (targetTorque * 256) / (int32_t)torqueMeasurementFactor);
}

int32_t tmc4671_getTargetTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	return (tmc4671_getTargetTorque_raw(icID) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	return (tmc4671_getActualTorque_raw(icID) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getTargetTorqueFluxSum_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	// remember last set index
	uint32_t lastIndex = tmc4671_readRegister(icID, TMC4671_INTERIM_ADDR);

	// get target torque value
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, 0);
	int32_t torque = (int32_t)tmc4671_readRegister(icID, TMC4671_INTERIM_DATA);

	// get target flux value
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, 1);
	int32_t flux = (int32_t)tmc4671_readRegister(icID, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, lastIndex);

	return (((int32_t)flux+(int32_t)torque) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualTorqueFluxSum_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	int32_t registerValue = tmc4671_readRegister(icID, TMC4671_PID_TORQUE_FLUX_ACTUAL);
	int16_t flux = (registerValue & 0xFFFF);
	int16_t torque = ((registerValue >> 16) & 0xFFFF);
	return (((int32_t)flux+(int32_t)torque) * (int32_t)torqueMeasurementFactor) / 256;
}

void tmc4671_setTargetFlux_raw(uint16_t icID, int32_t targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4671_fieldWrite(icID, TMC4671_PID_FLUX_TARGET_FIELD, targetFlux);
}

int32_t tmc4671_getTargetFlux_raw(uint16_t icID)
{
	// remember last set index
	uint32_t lastIndex = tmc4671_readRegister(icID, TMC4671_INTERIM_ADDR);

	// get value
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, 1);
	int32_t value = (int32_t)tmc4671_readRegister(icID, TMC4671_INTERIM_DATA);

	// reset last set index
	tmc4671_writeRegister(icID, TMC4671_INTERIM_ADDR, lastIndex);
	return value;
}

int32_t tmc4671_getActualFlux_raw(uint16_t icID)
{
	return tmc4671_fieldRead(icID, TMC4671_PID_FLUX_ACTUAL_FIELD);
}

void tmc4671_setTargetFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t targetFlux)
{
	// do not change the MOTION_MODE here! target flux can also be used during velocity and position modes
	tmc4671_fieldWrite(icID, TMC4671_PID_FLUX_TARGET_FIELD, (targetFlux * 256) / (int32_t)torqueMeasurementFactor);
}

int32_t tmc4671_getTargetFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	return (tmc4671_getTargetFlux_raw(icID) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc4671_getActualFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	return (tmc4671_getActualFlux_raw(icID) * (int32_t)torqueMeasurementFactor) / 256;
}

void tmc4671_setTorqueFluxLimit_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t max)
{
	tmc4671_fieldWrite(icID, TMC4671_PID_TORQUE_FLUX_LIMITS_FIELD, (max * 256) / (int32_t)torqueMeasurementFactor);
}

int32_t tmc4671_getTorqueFluxLimit_mA(uint16_t icID, uint16_t torqueMeasurementFactor)
{
	return ((int32_t)tmc4671_fieldRead(icID, TMC4671_PID_TORQUE_FLUX_LIMITS_FIELD) * (int32_t)torqueMeasurementFactor) / 256;
}

void tmc4671_setTargetVelocity(uint16_t icID, int32_t targetVelocity)
{
	tmc4671_switchToMotionMode(icID, TMC4671_MOTION_MODE_VELOCITY);
	tmc4671_writeRegister(icID, TMC4671_PID_VELOCITY_TARGET, targetVelocity);
}

int32_t tmc4671_getTargetVelocity(uint16_t icID)
{
	return (int32_t)tmc4671_readRegister(icID, TMC4671_PID_VELOCITY_TARGET);
}

int32_t tmc4671_getActualVelocity(uint16_t icID)
{
	return (int32_t)tmc4671_readRegister(icID, TMC4671_PID_VELOCITY_ACTUAL);
}

void tmc4671_setAbsolutTargetPosition(uint16_t icID, int32_t targetPosition)
{
	tmc4671_switchToMotionMode(icID, TMC4671_MOTION_MODE_POSITION);
	tmc4671_writeRegister(icID, TMC4671_PID_POSITION_TARGET, targetPosition);
}

void tmc4671_setRelativeTargetPosition(uint16_t icID, int32_t relativePosition)
{
	tmc4671_switchToMotionMode(icID, TMC4671_MOTION_MODE_POSITION);
	// determine actual position and add relative position ticks
	tmc4671_writeRegister(icID, TMC4671_PID_POSITION_TARGET, (int32_t)tmc4671_readRegister(icID, TMC4671_PID_POSITION_ACTUAL) + relativePosition);
}

int32_t tmc4671_getTargetPosition(uint16_t icID)
{
	return (int32_t)tmc4671_readRegister(icID, TMC4671_PID_POSITION_TARGET);
}

void tmc4671_setActualPosition(uint16_t icID, int32_t actualPosition)
{
	tmc4671_writeRegister(icID, TMC4671_PID_POSITION_ACTUAL, actualPosition);
}

int32_t tmc4671_getActualPosition(uint16_t icID)
{
	return (int32_t)tmc4671_readRegister(icID, TMC4671_PID_POSITION_ACTUAL);
}

// ABN encoder initialization
void tmc4671_doEncoderInitializationMode0(uint16_t icID, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT)
{
	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState

		// save actual set values for PHI_E_SELECTION, UQ_UD_EXT, and PHI_E_EXT
		*last_Phi_E_Selection = (uint16_t)tmc4671_fieldRead(icID, TMC4671_PHI_E_SELECTION_FIELD);
		*last_UQ_UD_EXT = (uint32_t)tmc4671_readRegister(icID, TMC4671_UQ_UD_EXT);
		*last_PHI_E_EXT = (int16_t)tmc4671_fieldRead(icID, TMC4671_PHI_E_EXT_FIELD);

		//switch motion mode for running icID in open loop
		tmc4671_writeRegister(icID, TMC4671_MODE_RAMP_MODE_MOTION, TMC4671_MOTION_MODE_UQ_UD_EXT);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4671_fieldWrite(icID, TMC4671_ABN_DECODER_PHI_E_OFFSET_FIELD, 0);

		// select phi_e_ext
		tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, 1);

		// set an initialization voltage on UD_EXT (to the flux, not the torque!)
		tmc4671_fieldWrite(icID, TMC4671_UQ_EXT_FIELD, 0);
		tmc4671_fieldWrite(icID, TMC4671_UD_EXT_FIELD, startVoltage);

		// set the "zero" angle
		tmc4671_fieldWrite(icID, TMC4671_PHI_E_EXT_FIELD, 0);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// wait until initialization time is over (until no more vibration on the icID)
		(*actualInitWaitTime)++;
		if(*actualInitWaitTime >= initWaitTime)
		{
			// set internal encoder value to zero
			tmc4671_writeRegister(icID, TMC4671_ABN_DECODER_COUNT, 0);

			// switch back to last used UQ_UD_EXT setting
			tmc4671_writeRegister(icID, TMC4671_UQ_UD_EXT, *last_UQ_UD_EXT);

			// set PHI_E_EXT back to last value
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_EXT_FIELD, *last_PHI_E_EXT);

			// switch back to last used PHI_E_SELECTION setting
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, *last_Phi_E_Selection);

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

int16_t tmc4671_getS16CircleDifference(int16_t newValue, int16_t oldValue)
{
	return (newValue - oldValue);
}

void tmc4671_doEncoderInitializationMode2(uint16_t icID, uint8_t *initState, uint16_t *actualInitWaitTime,
		int16_t *hall_phi_e_old, int16_t *hall_phi_e_new, int16_t *hall_actual_coarse_offset, uint16_t *last_Phi_E_Selection)
{
	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState
		// save actual set value for PHI_E_SELECTION
		*last_Phi_E_Selection = (uint16_t)tmc4671_fieldRead(icID, TMC4671_PHI_E_SELECTION_FIELD);

		// turn hall_mode interpolation off (read, clear bit 8, write back)
		tmc4671_writeRegister(icID, TMC4671_HALL_MODE, tmc4671_readRegister(icID, TMC4671_HALL_MODE) & 0xFFFFFEFF);

		// set ABN_DECODER_PHI_E_OFFSET to zero
		tmc4671_fieldWrite(icID, TMC4671_ABN_DECODER_PHI_E_OFFSET_FIELD, 0);

		// read actual hall angle
		*hall_phi_e_old = tmc4671_fieldRead(icID, TMC4671_HALL_PHI_E_FIELD);

		// read actual abn_decoder angle and compute difference to actual hall angle
		*hall_actual_coarse_offset = tmc4671_getS16CircleDifference(*hall_phi_e_old, (int16_t)tmc4671_fieldRead(icID, TMC4671_ABN_DECODER_PHI_E_FIELD));

		// set ABN_DECODER_PHI_E_OFFSET to actual hall-abn-difference, to use the actual hall angle for coarse initialization
		tmc4671_fieldWrite(icID, TMC4671_ABN_DECODER_PHI_E_OFFSET_FIELD, *hall_actual_coarse_offset);

		// normally MOTION_MODE_UQ_UD_EXT is only used by e.g. a wizard, not in normal operation
		if (tmc4671_fieldRead(icID, TMC4671_MODE_MOTION_FIELD) != TMC4671_MOTION_MODE_UQ_UD_EXT)
		{
			// select the use of phi_e_hall to start icID with hall signals
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, TMC4671_PHI_E_HALL);
		}

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// read actual hall angle
		*hall_phi_e_new = tmc4671_fieldRead(icID, TMC4671_HALL_PHI_E_FIELD);

		// wait until hall angle changed
		if(*hall_phi_e_old != *hall_phi_e_new)
		{
			// estimated value = old value + diff between old and new (handle int16_t overrun)
			int16_t hall_phi_e_estimated = *hall_phi_e_old + tmc4671_getS16CircleDifference(*hall_phi_e_new, *hall_phi_e_old)/2;

			// read actual abn_decoder angle and consider last set abn_decoder_offset
			int16_t abn_phi_e_actual = (int16_t)tmc4671_fieldRead(icID, TMC4671_ABN_DECODER_PHI_E_FIELD) - *hall_actual_coarse_offset;

			// set ABN_DECODER_PHI_E_OFFSET to actual estimated angle - abn_phi_e_actual difference
			tmc4671_fieldWrite(icID, TMC4671_ABN_DECODER_PHI_E_OFFSET_FIELD, tmc4671_getS16CircleDifference(hall_phi_e_estimated, abn_phi_e_actual));

			// switch back to last used PHI_E_SELECTION setting
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, *last_Phi_E_Selection);

			// go to ready state
			*initState = 0;
		}
		break;
	default:
		*initState = 0;
		break;
	}
}

// analog encoder initialization
void tmc4671_doEncoderInitializationMode3(uint16_t icID, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT)
{
	switch (*initState)
	{
	case STATE_NOTHING_TO_DO:
		*actualInitWaitTime = 0;
		break;
	case STATE_START_INIT: // started by writing 1 to initState

		// save actual set values for PHI_E_SELECTION, UQ_UD_EXT, and PHI_E_EXT
		*last_Phi_E_Selection = (uint16_t)tmc4671_fieldRead(icID, TMC4671_PHI_E_SELECTION_FIELD);
		*last_UQ_UD_EXT = (uint32_t)tmc4671_readRegister(icID, TMC4671_UQ_UD_EXT);
		*last_PHI_E_EXT = (int16_t)tmc4671_fieldRead(icID, TMC4671_PHI_E_EXT_FIELD);

		// switch motion mode for running motor in open loop
		tmc4671_writeRegister(icID, TMC4671_MODE_RAMP_MODE_MOTION, TMC4671_MOTION_MODE_UQ_UD_EXT);

		// set AENC_DECODER_PHI_E_PHI_M_OFFSET and AENC_DECODER_PHI_A_OFFSET to zero
		tmc4671_writeRegister(icID, TMC4671_AENC_DECODER_PHI_E_PHI_M_OFFSET, 0);
		tmc4671_fieldWrite(icID, TMC4671_AENC_DECODER_PHI_A_OFFSET_FIELD, 0);

		// select phi_e_ext
		tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, 1);

		// set an initialization voltage on UD_EXT (to the flux, not the torque!)
		tmc4671_fieldWrite(icID, TMC4671_UQ_EXT_FIELD, 0);
		tmc4671_fieldWrite(icID, TMC4671_UD_EXT_FIELD, startVoltage);

		// set the "zero" angle
		tmc4671_fieldWrite(icID, TMC4671_PHI_E_EXT_FIELD, 0);

		*initState = STATE_WAIT_INIT_TIME;
		break;
	case STATE_WAIT_INIT_TIME:
		// wait until initialization time is over (until no more vibration on the motor)
		(*actualInitWaitTime)++;
		if(*actualInitWaitTime >= initWaitTime)
		{
            // save actual DECODER_PHI_M as -DECODER_PHI_M_OFFSET
			int16_t offset_raw = tmc4671_fieldRead(icID, TMC4671_AENC_DECODER_PHI_M_FIELD);

            // update PHI_M and keep PHI_E and PH_A at zero
            tmc4671_fieldWrite(icID, TMC4671_AENC_DECODER_PHI_E_OFFSET_FIELD, 0);

            tmc4671_fieldWrite(icID, TMC4671_AENC_DECODER_PHI_M_OFFSET_FIELD, -offset_raw);
            tmc4671_fieldWrite(icID, TMC4671_AENC_DECODER_PHI_A_OFFSET_FIELD, 0);

			// switch back to last used UQ_UD_EXT setting
			tmc4671_writeRegister(icID, TMC4671_UQ_UD_EXT, *last_UQ_UD_EXT);

			// set PHI_E_EXT back to last value
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_EXT_FIELD, *last_PHI_E_EXT);

			// switch back to last used PHI_E_SELECTION setting
			tmc4671_fieldWrite(icID, TMC4671_PHI_E_SELECTION_FIELD, *last_Phi_E_Selection);

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

void tmc4671_checkEncderInitialization(uint16_t icID, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		int16_t *hall_phi_e_old, int16_t *hall_phi_e_new, int16_t *hall_actual_coarse_offset,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT)
{
	// use the systick as 1ms timer for encoder initialization
	static uint32_t lastSystick = 0;
	if(actualSystick != lastSystick)
	{
		// needs timer to use the wait time
		if(initMode == 0)
		{
			tmc4671_doEncoderInitializationMode0(icID, initState, initWaitTime, actualInitWaitTime, startVoltage, last_Phi_E_Selection, last_UQ_UD_EXT, last_PHI_E_EXT);
		}
		else if (initMode == 3)	// analog encoder initialization
		{
			tmc4671_doEncoderInitializationMode3(icID, initState, initWaitTime, actualInitWaitTime, startVoltage, last_Phi_E_Selection, last_UQ_UD_EXT, last_PHI_E_EXT);
		}
		lastSystick = actualSystick;
	}

	// needs no timer
	if(initMode == 2)
	{
		tmc4671_doEncoderInitializationMode2(icID, initState, actualInitWaitTime, hall_phi_e_old, hall_phi_e_new, hall_actual_coarse_offset, last_Phi_E_Selection);
	}
}

void tmc4671_periodicJob(uint16_t icID, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		int16_t *hall_phi_e_old, int16_t *hall_phi_e_new, int16_t *hall_actual_coarse_offset,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT)
{
	tmc4671_checkEncderInitialization(icID, actualSystick, initMode, initState, initWaitTime, actualInitWaitTime, startVoltage,
			hall_phi_e_old, hall_phi_e_new, hall_actual_coarse_offset, last_Phi_E_Selection, last_UQ_UD_EXT, last_PHI_E_EXT);
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
		else if (mode == 3) // use analog encoder initialization
		{
			// set mode
			*initMode = 3;

			// start initialization
			*initState = 1;
		}
	}
}

int32_t tmc4671_readFieldWithDependency(uint16_t icID, RegisterField field, uint8_t dependsReg, uint32_t dependsValue)
{
	// remember old depends value
	uint32_t lastDependsValue = tmc4671_readRegister(icID, dependsReg);

	// set needed depends value
	tmc4671_writeRegister(icID, dependsReg, dependsValue);
	uint32_t value = tmc4671_fieldRead(icID, field);

	// set old depends value
	tmc4671_writeRegister(icID, dependsReg, lastDependsValue);
	return value;
}
