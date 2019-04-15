/*
 * TMC4670.h
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMC4670_H_
#define TMC_IC_TMC4670_H_

#include "tmc/helpers/API_Header.h"
#include "TMC4670_Register.h"
#include "TMC4670_Constants.h"
#include "TMC4670_Fields.h"

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1

int32_t tmc4670_readInt(uint8_t motor, uint8_t address);
void tmc4670_writeInt(uint8_t motor, uint8_t address, int32_t value);
uint16_t tmc4670_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel);
void tmc4670_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value);

// do cyclic tasks
void tmc4670_periodicJob(uint8_t motor, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage);

// encoder functions
void tmc4670_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState);

// === modes of operation ===
void tmc4670_switchToMotionMode(uint8_t motor, uint8_t mode);

// torque mode
void tmc4670_setTargetTorque_raw(uint8_t motor, int32_t targetTorque);
int32_t tmc4670_getTargetTorque_raw(uint8_t motor);
int32_t tmc4670_getActualTorque_raw(uint8_t motor);
int32_t tmc4670_getActualRampTorque_raw(uint8_t motor);

void tmc4670_setTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetTorque);
int32_t tmc4670_getTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4670_getActualTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4670_getActualRampTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// flux
void tmc4670_setTargetFlux_raw(uint8_t motor, int32_t targetFlux);
int32_t tmc4670_getTargetFlux_raw(uint8_t motor);
int32_t tmc4670_getActualFlux_raw(uint8_t motor);

void tmc4670_setTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetFlux);
int32_t tmc4670_getTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4670_getActualFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// torque/flux limit
void tmc4670_setTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t max);
int32_t tmc4670_getTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// velocity mode
void tmc4670_setTargetVelocity(uint8_t motor, int32_t targetVelocity);
int32_t tmc4670_getTargetVelocity(uint8_t motor);
int32_t tmc4670_getActualVelocity(uint8_t motor);
int32_t tmc4670_getActualRampVelocity(uint8_t motor);

// position mode
void tmc4670_setAbsolutTargetPosition(uint8_t motor, int32_t targetPosition);
void tmc4670_setRelativeTargetPosition(uint8_t motor, int32_t relativePosition);
int32_t tmc4670_getTargetPosition(uint8_t motor);
void tmc4670_setActualPosition(uint8_t motor, int32_t actualPosition);
int32_t tmc4670_getActualPosition(uint8_t motor);
int32_t tmc4670_getActualRampPosition(uint8_t motor);

// pwm control
void tmc4670_disablePWM(uint8_t motor);

#endif /* TMC_IC_TMC4670_H_ */
