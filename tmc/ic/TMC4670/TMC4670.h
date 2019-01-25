/*
 * TMC4670.h
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMC4670_H_
#define TMC_IC_TMC4670_H_

#include "../../helpers/API_Header.h"
#include "TMC4670_Register.h"
#include "TMC4670_Constants.h"
#include "TMC4670_Fields.h"

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1
int tmc4670_readInt(u8 motor, uint8 address);
void tmc4670_writeInt(u8 motor, uint8 address, int value);
u16 tmc4670_readRegister16BitValue(u8 motor, u8 address, u8 channel);
void tmc4670_writeRegister16BitValue(u8 motor, u8 address, u8 channel, u16 value);

// do cyclic tasks
void tmc4670_periodicJob(u8 motor, u32 actualSystick, u8 initMode, u8 *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage);

// encoder functions
void tmc4670_startEncoderInitialization(u8 mode, u8 *initMode, u8 *initState);

// === modes of operation ===
void tmc4670_switchToMotionMode(u8 motor, u8 mode);

// torque mode
void tmc4670_setTargetTorque_raw(u8 motor, s32 targetTorque);
s32 tmc4670_getTargetTorque_raw(u8 motor);
s32 tmc4670_getActualTorque_raw(u8 motor);
s32 tmc4670_getActualRampTorque_raw(u8 motor);

void tmc4670_setTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetTorque);
s32 tmc4670_getTargetTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4670_getActualTorque_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4670_getActualRampTorque_mA(u8 motor, u16 torqueMeasurementFactor);

// flux
void tmc4670_setTargetFlux_raw(u8 motor, s32 targetFlux);
s32 tmc4670_getTargetFlux_raw(u8 motor);
s32 tmc4670_getActualFlux_raw(u8 motor);

void tmc4670_setTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor, s32 targetFlux);
s32 tmc4670_getTargetFlux_mA(u8 motor, u16 torqueMeasurementFactor);
s32 tmc4670_getActualFlux_mA(u8 motor, u16 torqueMeasurementFactor);

// torque/flux limit
void tmc4670_setTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor, s32 max);
s32 tmc4670_getTorqueFluxLimit_mA(u8 motor, u16 torqueMeasurementFactor);

// velocity mode
void tmc4670_setTargetVelocity(u8 motor, s32 targetVelocity);
s32 tmc4670_getTargetVelocity(u8 motor);
s32 tmc4670_getActualVelocity(u8 motor);
s32 tmc4670_getActualRampVelocity(u8 motor);

// position mode
void tmc4670_setAbsolutTargetPosition(u8 motor, s32 targetPosition);
void tmc4670_setRelativeTargetPosition(u8 motor, s32 relativePosition);
s32 tmc4670_getTargetPosition(u8 motor);
void tmc4670_setActualPosition(u8 motor, s32 actualPosition);
s32 tmc4670_getActualPosition(u8 motor);
s32 tmc4670_getActualRampPosition(u8 motor);

// pwm control
void tmc4670_disablePWM(u8 motor);

#endif /* TMC_IC_TMC4670_H_ */
