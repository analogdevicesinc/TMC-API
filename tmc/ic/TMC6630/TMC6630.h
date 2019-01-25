/*
 * TMC6630.h
 *
 *  Created on: 27.01.2017
 *      Author: ed
 */

#ifndef TMC_IC_TMC6630_H_
#define TMC_IC_TMC6630_H_

#include "../../helpers/API_Header.h"
#include "TMC6630_Register.h"
#include "TMC6630_Constants.h"

// === modes of operation ===
u8 tmc6630_getMotionMode(u8 motor);
void tmc6630_setMotionMode(u8 motor, u8 mode);

// spi access
u16 tmc6630_spi_readRegister16BitValue(u8 motor, u8 address, u8 channel);
void tmc6630_spi_writeRegister16BitValue(u8 motor, u8 address, u8 channel, u16 value);

// pwm mode
s16 tmc6630_getTargetPwmDuty(u8 motor);
void tmc6630_setTargetPwmDuty(u8 motor, s16 targetPWM);
s16 tmc6630_getActualPwmDuty(u8 motor);

u16 tmc6630_getMaxPwmDuty(u8 motor);
void tmc6630_setMaxPwmDuty(u8 motor, u16 maxPWM);

// torque mode
void tmc6630_setTargetTorque_raw(u8 motor, s32 targetTorque);
s32 tmc6630_getTargetTorque_raw(u8 motor);
s32 tmc6630_getActualTorque_raw(u8 motor);

void tmc6630_setTargetTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 targetTorque);
s32 tmc6630_getTargetTorque_mA(u8 motor, s16 torqueMeasurementFactor);
s32 tmc6630_getActualTorque_mA(u8 motor, s16 torqueMeasurementFactor);

s16 tmc6630_getMaxTorque_raw(u8 motor);
void tmc6630_setMaxTorque_raw(u8 motor, s16 maxTorque);
s32 tmc6630_getMaxTorque_mA(u8 motor, s16 torqueMeasurementFactor);
void tmc6630_setMaxTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 maxTorque);

s16 tmc6630_getMinTorque_raw(u8 motor);
void tmc6630_setMinTorque_raw(u8 motor, s16 minTorque);
s32 tmc6630_getMinTorque_mA(u8 motor, s16 torqueMeasurementFactor);
void tmc6630_setMinTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 minTorque);

// velocity mode
void tmc6630_setTargetVelocity(u8 motor, s32 targetVelocity);
s32 tmc6630_getTargetVelocity(u8 motor);
s32 tmc6630_getActualVelocity(u8 motor);

void tmc6630_setMaxVelocity(u8 motor, s32 maxVelocity);
s32 tmc6630_getMaxVelocity(u8 motor);

void tmc6630_setMinVelocity(u8 motor, s32 minVelocity);
s32 tmc6630_getMinVelocity(u8 motor);

#endif /* TMC_IC_TMC6630_H_ */
