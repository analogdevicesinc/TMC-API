/*******************************************************************************
* Copyright © 2016 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC_IC_TMC4671_H_
#define TMC_IC_TMC4671_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC4671_HW_Abstraction.h"

int32_t tmc4671_readRegister(uint16_t motor, uint8_t address);
void tmc4671_writeRegister(uint16_t motor, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc4671_fieldExtract(uint32_t data, RegisterField field)
{
    uint32_t value = (data & field.mask) >> field.shift;

    if (field.isSigned)
    {
        // Apply signedness conversion
        uint32_t baseMask = field.mask >> field.shift;
        uint32_t signMask = baseMask & (~baseMask >> 1);
        value = (value ^ signMask) - signMask;
    }

    return value;
}

static inline uint32_t tmc4671_fieldRead(uint16_t icID, RegisterField field)
{
	uint32_t value = tmc4671_readRegister(icID, field.address);

    return tmc4671_fieldExtract(value, field);
}

static inline uint32_t tmc4671_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc4671_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
	uint32_t regValue = tmc4671_readRegister(icID, field.address);

	regValue = tmc4671_fieldUpdate(regValue, field, value);

    tmc4671_writeRegister(icID, field.address, regValue);
}

// Do cyclic tasks
void tmc4671_periodicJob(uint8_t motor, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		int16_t *hall_phi_e_old, int16_t *hall_phi_e_new, int16_t *hall_actual_coarse_offset,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT);

// Initialization functions
void tmc4671_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState);
void tmc4671_updatePhiSelectionAndInitialize(uint8_t motor, uint8_t actualPhiESelection, uint8_t desiredPhiESelection, uint8_t initMode, uint8_t *initState);

// Modes of operation
void tmc4671_switchToMotionMode(uint8_t motor, uint8_t mode);

// Torque mode
void tmc4671_setTargetTorque_raw(uint8_t motor, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_raw(uint8_t motor);
int32_t tmc4671_getActualTorque_raw(uint8_t motor);

void tmc4671_setTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorque_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getTargetTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorqueFluxSum_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// Flux
void tmc4671_setTargetFlux_raw(uint8_t motor, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_raw(uint8_t motor);
int32_t tmc4671_getActualFlux_raw(uint8_t motor);

void tmc4671_setTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualFlux_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// Torque/flux limit
void tmc4671_setTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor, int32_t max);
int32_t tmc4671_getTorqueFluxLimit_mA(uint8_t motor, uint16_t torqueMeasurementFactor);

// Velocity mode
void tmc4671_setTargetVelocity(uint8_t motor, int32_t targetVelocity);
int32_t tmc4671_getTargetVelocity(uint8_t motor);
int32_t tmc4671_getActualVelocity(uint8_t motor);

// Position mode
void tmc4671_setAbsolutTargetPosition(uint8_t motor, int32_t targetPosition);
void tmc4671_setRelativeTargetPosition(uint8_t motor, int32_t relativePosition);
int32_t tmc4671_getTargetPosition(uint8_t motor);
void tmc4671_setActualPosition(uint8_t motor, int32_t actualPosition);
int32_t tmc4671_getActualPosition(uint8_t motor);

// PWM control
void tmc4671_disablePWM(uint8_t motor);

// Motor settings
uint8_t tmc4671_getMotorType(uint8_t motor);
void tmc4671_setMotorType(uint8_t motor, uint8_t motorType);

uint8_t tmc4671_getPolePairs(uint8_t motor);
void tmc4671_setPolePairs(uint8_t motor, uint8_t polePairs);

uint16_t tmc4671_getAdcI0Offset(uint8_t motor);
void tmc4671_setAdcI0Offset(uint8_t motor, uint16_t offset);

uint16_t tmc4671_getAdcI1Offset(uint8_t motor);
void tmc4671_setAdcI1Offset(uint8_t motor, uint16_t offset);

void tmc4671_setTorqueFluxPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);
void tmc4671_setVelocityPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);
void tmc4671_setPositionPI(uint8_t motor, uint16_t pParameter, uint16_t iParameter);

int32_t tmc4671_readFieldWithDependency(uint8_t motor, RegisterField field, uint8_t dependsReg, uint32_t dependsValue);

#endif /* TMC_IC_TMC4671_H_ */
