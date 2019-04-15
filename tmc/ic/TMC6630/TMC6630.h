/*
 * TMC6630.h
 *
 *  Created on: 27.01.2017
 *      Author: ed
 */

#ifndef TMC_IC_TMC6630_H_
#define TMC_IC_TMC6630_H_

#include "tmc/helpers/API_Header.h"
#include "TMC6630_Register.h"
#include "TMC6630_Constants.h"

// === modes of operation ===
uint8_t tmc6630_getMotionMode(uint8_t motor);
void tmc6630_setMotionMode(uint8_t motor, uint8_t mode);

// spi access
uint16_t tmc6630_spi_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel);
void tmc6630_spi_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value);

// pwm mode
int16_t tmc6630_getTargetPwmDuty(uint8_t motor);
void tmc6630_setTargetPwmDuty(uint8_t motor, int16_t targetPWM);
int16_t tmc6630_getActualPwmDuty(uint8_t motor);

uint16_t tmc6630_getMaxPwmDuty(uint8_t motor);
void tmc6630_setMaxPwmDuty(uint8_t motor, uint16_t maxPWM);

// torque mode
void tmc6630_setTargetTorque_raw(uint8_t motor, int32_t targetTorque);
int32_t tmc6630_getTargetTorque_raw(uint8_t motor);
int32_t tmc6630_getActualTorque_raw(uint8_t motor);

void tmc6630_setTargetTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t targetTorque);
int32_t tmc6630_getTargetTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor);
int32_t tmc6630_getActualTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor);

int16_t tmc6630_getMaxTorque_raw(uint8_t motor);
void tmc6630_setMaxTorque_raw(uint8_t motor, int16_t maxTorque);
int32_t tmc6630_getMaxTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor);
void tmc6630_setMaxTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t maxTorque);

int16_t tmc6630_getMinTorque_raw(uint8_t motor);
void tmc6630_setMinTorque_raw(uint8_t motor, int16_t minTorque);
int32_t tmc6630_getMinTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor);
void tmc6630_setMinTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t minTorque);

// velocity mode
void tmc6630_setTargetVelocity(uint8_t motor, int32_t targetVelocity);
int32_t tmc6630_getTargetVelocity(uint8_t motor);
int32_t tmc6630_getActualVelocity(uint8_t motor);

void tmc6630_setMaxVelocity(uint8_t motor, int32_t maxVelocity);
int32_t tmc6630_getMaxVelocity(uint8_t motor);

void tmc6630_setMinVelocity(uint8_t motor, int32_t minVelocity);
int32_t tmc6630_getMinVelocity(uint8_t motor);

#endif /* TMC_IC_TMC6630_H_ */
