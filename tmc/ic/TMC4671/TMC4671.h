/*
 * TMC4671.h
 *
 *  Created on: 30.09.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMC4671_H_
#define TMC_IC_TMC4671_H_

#include "../../helpers/API_Header.h"
#include "TMC4671_Register.h"
#include "TMC4671_Constants.h"
#include "TMC4671_Fields.h"

// spi access
#define BIT_0_TO_15   0
#define BIT_16_TO_31  1

// Helper macros
#define TMC4671_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc4671_readInt(tdef, address), mask, shift)
#define TMC4671_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc4671_writeInt(tdef, address, FIELD_SET(tmc4671_readInt(tdef, address), mask, shift, value)))

int tmc4671_readInt(uint8_t motor, uint8 address);
void tmc4671_writeInt(uint8_t motor, uint8 address, int value);
u16 tmc4671_readRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel);
void tmc4671_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, u16 value);

// do cyclic tasks
void tmc4671_periodicJob(uint8_t motor, u32 actualSystick, uint8_t initMode, uint8_t *initState, u16 initWaitTime, u16 *actualInitWaitTime, u16 startVoltage);

// initialization functions
void tmc4671_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState);
void tmc4671_updatePhiSelectionAndInitialize(uint8_t motor, uint8_t actualPhiESelection, uint8_t desiredPhiESelection, uint8_t initMode, uint8_t *initState);

// === modes of operation ===
void tmc4671_switchToMotionMode(uint8_t motor, uint8_t mode);

// torque mode
void tmc4671_setTargetTorque_raw(uint8_t motor, s32 targetTorque);
s32 tmc4671_getTargetTorque_raw(uint8_t motor);
s32 tmc4671_getActualTorque_raw(uint8_t motor);
s32 tmc4671_getActualRampTorque_raw(uint8_t motor);

void tmc4671_setTargetTorque_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 targetTorque);
s32 tmc4671_getTargetTorque_mA(uint8_t motor, u16 torqueMeasurementFactor);
s32 tmc4671_getActualTorque_mA(uint8_t motor, u16 torqueMeasurementFactor);
s32 tmc4671_getTargetTorqueFluxSum_mA(uint8_t motor, u16 torqueMeasurementFactor);
s32 tmc4671_getActualTorqueFluxSum_mA(uint8_t motor, u16 torqueMeasurementFactor);
s32 tmc4671_getActualRampTorque_mA(uint8_t motor, u16 torqueMeasurementFactor);

// flux
void tmc4671_setTargetFlux_raw(uint8_t motor, s32 targetFlux);
s32 tmc4671_getTargetFlux_raw(uint8_t motor);
s32 tmc4671_getActualFlux_raw(uint8_t motor);

void tmc4671_setTargetFlux_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 targetFlux);
s32 tmc4671_getTargetFlux_mA(uint8_t motor, u16 torqueMeasurementFactor);
s32 tmc4671_getActualFlux_mA(uint8_t motor, u16 torqueMeasurementFactor);

// torque/flux limit
void tmc4671_setTorqueFluxLimit_mA(uint8_t motor, u16 torqueMeasurementFactor, s32 max);
s32 tmc4671_getTorqueFluxLimit_mA(uint8_t motor, u16 torqueMeasurementFactor);

// velocity mode
void tmc4671_setTargetVelocity(uint8_t motor, s32 targetVelocity);
s32 tmc4671_getTargetVelocity(uint8_t motor);
s32 tmc4671_getActualVelocity(uint8_t motor);
s32 tmc4671_getActualRampVelocity(uint8_t motor);

// position mode
void tmc4671_setAbsolutTargetPosition(uint8_t motor, s32 targetPosition);
void tmc4671_setRelativeTargetPosition(uint8_t motor, s32 relativePosition);
s32 tmc4671_getTargetPosition(uint8_t motor);
void tmc4671_setActualPosition(uint8_t motor, s32 actualPosition);
s32 tmc4671_getActualPosition(uint8_t motor);
s32 tmc4671_getActualRampPosition(uint8_t motor);

// pwm control
void tmc4671_disablePWM(uint8_t motor);

uint8_t tmc4671_getPolePairs(uint8_t motor);
void tmc4671_setPolePairs(uint8_t motor, uint8_t polePairs);

u16 tmc4671_getAdcI0Offset(uint8_t motor);
void tmc4671_setAdcI0Offset(uint8_t motor, u16 offset);

u16 tmc4671_getAdcI1Offset(uint8_t motor);
void tmc4671_setAdcI1Offset(uint8_t motor, u16 offset);

void tmc4671_setTorqueFluxPI(uint8_t motor, u16 pParameter, u16 iParameter);
void tmc4671_setVelocityPI(uint8_t motor, u16 pParameter, u16 iParameter);
void tmc4671_setPositionPI(uint8_t motor, u16 pParameter, u16 iParameter);

int tmc4671_readFieldWithDependency(uint8_t motor, uint8_t reg, uint8_t dependsReg, u32 dependsValue, u32 mask, uint8_t shift);

#endif /* TMC_IC_TMC4671_H_ */
