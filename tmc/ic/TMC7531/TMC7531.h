/*
 * TMC7531.h
 *
 *  Created on: 04.09.2018
 *      Author: LK
 */

#ifndef API_IC_TMC7531_H
#define API_IC_TMC7531_H

#include "../../helpers/API_Header.h"
#include "TMC7531_Fields.h"
#include "TMC7531_Register.h"

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1
int tmc7531_readInt(u8 motor, uint8 address);
void tmc7531_writeInt(u8 motor, uint8 address, int value);
u16 tmc7531_readRegister16BitValue(u8 motor, u8 address, u8 channel);
void tmc7531_writeRegister16BitValue(u8 motor, u8 address, u8 channel, u16 value);

// do cyclic tasks
void tmc7531_periodicJob(u8 motor, u32 actualSystick, u8 initMode, u8 *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage);

// initialization functions
void tmc7531_startEncoderInitialization(u8 mode, u8 *initMode, u8 *initState);
void tmc7531_updatePhiSelectionAndInitialize(u8 motor, u8 actualPhiESelection, u8 desiredPhiESelection, u8 initMode, u8 *initState);

// === modes of operation ===
void tmc7531_switchToMotionMode(u8 motor, u8 mode);

// torque mode
void tmc7531_setTargetTorque_raw(u8 motor, s32 targetTorque);
s32 tmc7531_getTargetTorque_raw(u8 motor);
s32 tmc7531_getActualTorque_raw(u8 motor);
s32 tmc7531_getActualRampTorque_raw(u8 motor);

void tmc7531_setTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetTorque);
s32 tmc7531_getTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc7531_getActualTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc7531_getActualRampTorque_mA(u8 motor, u16 torqueMeasurementFactor);

// flux
void tmc7531_setTargetFlux_raw(u8 motor, s32 targetFlux);
s32 tmc7531_getTargetFlux_raw(u8 motor);
s32 tmc7531_getActualFlux_raw(u8 motor);

void tmc7531_setTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetFlux);
s32 tmc7531_getTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc7531_getActualFlux_mA(u8 motor, u16 torqueMeasurementFactor);

// torque/flux limit
void tmc7531_setTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor, s32 max);
s32 tmc7531_getTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor);

// velocity mode
void tmc7531_setTargetVelocity(u8 motor, s32 targetVelocity);
s32 tmc7531_getTargetVelocity(u8 motor);
s32 tmc7531_getActualVelocity(u8 motor);
s32 tmc7531_getActualRampVelocity(u8 motor);

// position mode
void tmc7531_setAbsolutTargetPosition(u8 motor, s32 targetPosition);
void tmc7531_setRelativeTargetPosition(u8 motor, s32 relativePosition);
s32 tmc7531_getTargetPosition(u8 motor);
void tmc7531_setActualPosition(u8 motor, s32 actualPosition);
s32 tmc7531_getActualPosition(u8 motor);
s32 tmc7531_getActualRampPosition(u8 motor);

// pwm control
void tmc7531_disablePWM(u8 motor);

#endif /* API_IC_TMC7531_H */
