/*
 * TMC4672.h
 *
 *  Created on: 09.11.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC4672_H_
#define TMC_IC_TMC4672_H_

#include "../../helpers/API_Header.h"
#include "TMC4672_Constants.h"
#include "TMC4672_Fields.h"
#include "TMC4672_Register.h"

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1

// Helper macros
#define TMC4672_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc4672_readInt(tdef, address), mask, shift)
#define TMC4672_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc4672_writeInt(tdef, address, FIELD_SET(tmc4672_readInt(tdef, address), mask, shift, value)))

int tmc4672_readInt(u8 motor, uint8 address);
void tmc4672_writeInt(u8 motor, uint8 address, int value);
u16 tmc4672_readRegister16BitValue(u8 motor, u8 address, u8 channel);
void tmc4672_writeRegister16BitValue(u8 motor, u8 address, u8 channel, u16 value);

// do cyclic tasks
void tmc4672_periodicJob(u8 motor, u32 actualSystick, u8 initMode, u8 *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage);

// initialization functions
void tmc4672_startEncoderInitialization(u8 mode, u8 *initMode, u8 *initState);
void tmc4672_updatePhiSelectionAndInitialize(u8 motor, u8 actualPhiESelection, u8 desiredPhiESelection, u8 initMode, u8 *initState);

// === modes of operation ===
void tmc4672_switchToMotionMode(u8 motor, u8 mode);

// torque mode
void tmc4672_setTargetTorque_raw(u8 motor, s32 targetTorque);
s32 tmc4672_getTargetTorque_raw(u8 motor);
s32 tmc4672_getActualTorque_raw(u8 motor);
s32 tmc4672_getActualRampTorque_raw(u8 motor);

void tmc4672_setTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetTorque);
s32 tmc4672_getTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4672_getActualTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4672_getTargetTorqueFluxSum_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4672_getActualTorqueFluxSum_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4672_getActualRampTorque_mA(u8 motor, u16 torqueMeasurementFactor);

// flux
void tmc4672_setTargetFlux_raw(u8 motor, s32 targetFlux);
s32 tmc4672_getTargetFlux_raw(u8 motor);
s32 tmc4672_getActualFlux_raw(u8 motor);

void tmc4672_setTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetFlux);
s32 tmc4672_getTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4672_getActualFlux_mA(u8 motor, u16 torqueMeasurementFactor);

// torque/flux limit
void tmc4672_setTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor, s32 max);
s32 tmc4672_getTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor);

// velocity mode
void tmc4672_setTargetVelocity(u8 motor, s32 targetVelocity);
s32 tmc4672_getTargetVelocity(u8 motor);
s32 tmc4672_getActualVelocity(u8 motor);
s32 tmc4672_getActualRampVelocity(u8 motor);

// position mode
void tmc4672_setAbsolutTargetPosition(u8 motor, s32 targetPosition);
void tmc4672_setRelativeTargetPosition(u8 motor, s32 relativePosition);
s32 tmc4672_getTargetPosition(u8 motor);
void tmc4672_setActualPosition(u8 motor, s32 actualPosition);
s32 tmc4672_getActualPosition(u8 motor);
s32 tmc4672_getActualRampPosition(u8 motor);

#endif /* TMC_IC_TMC4672_H_ */
