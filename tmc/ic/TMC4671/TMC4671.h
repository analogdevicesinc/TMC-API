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

int32_t tmc4671_readRegister(uint16_t icID, uint8_t address);
void tmc4671_writeRegister(uint16_t icID, uint8_t address, int32_t value);

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
void tmc4671_periodicJob(uint16_t icID, uint32_t actualSystick, uint8_t initMode, uint8_t *initState, uint16_t initWaitTime, uint16_t *actualInitWaitTime, uint16_t startVoltage,
		int16_t *hall_phi_e_old, int16_t *hall_phi_e_new, int16_t *hall_actual_coarse_offset,
		uint16_t *last_Phi_E_Selection, uint32_t *last_UQ_UD_EXT, int16_t *last_PHI_E_EXT);

// Encoder initialization functions
void tmc4671_startEncoderInitialization(uint8_t mode, uint8_t *initMode, uint8_t *initState);

// Modes of operation
void tmc4671_switchToMotionMode(uint16_t icID, uint8_t mode);

// Torque mode
void tmc4671_setTargetTorque_raw(uint16_t icID, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_raw(uint16_t icID);
int32_t tmc4671_getActualTorque_raw(uint16_t icID);

// Torque mode real world unit scaling
void tmc4671_setTargetTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t targetTorque);
int32_t tmc4671_getTargetTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorque_mA(uint16_t icID, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getTargetTorqueFluxSum_mA(uint16_t icID, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualTorqueFluxSum_mA(uint16_t icID, uint16_t torqueMeasurementFactor);

// Flux
void tmc4671_setTargetFlux_raw(uint16_t icID, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_raw(uint16_t icID);
int32_t tmc4671_getActualFlux_raw(uint16_t icID);

// Flux regulation real world unit scaling
void tmc4671_setTargetFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t targetFlux);
int32_t tmc4671_getTargetFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor);
int32_t tmc4671_getActualFlux_mA(uint16_t icID, uint16_t torqueMeasurementFactor);

// Torque/flux limit in real world units
void tmc4671_setTorqueFluxLimit_mA(uint16_t icID, uint16_t torqueMeasurementFactor, int32_t max);
int32_t tmc4671_getTorqueFluxLimit_mA(uint16_t icID, uint16_t torqueMeasurementFactor);

// Velocity mode
void tmc4671_setTargetVelocity(uint16_t icID, int32_t targetVelocity);
int32_t tmc4671_getTargetVelocity(uint16_t icID);
int32_t tmc4671_getActualVelocity(uint16_t icID);

// Position mode
void tmc4671_setAbsolutTargetPosition(uint16_t icID, int32_t targetPosition);
void tmc4671_setRelativeTargetPosition(uint16_t icID, int32_t relativePosition);
int32_t tmc4671_getTargetPosition(uint16_t icID);
void tmc4671_setActualPosition(uint16_t icID, int32_t actualPosition);
int32_t tmc4671_getActualPosition(uint16_t icID);

// Access for register with dependency register
int32_t tmc4671_readFieldWithDependency(uint16_t icID, RegisterField field, uint8_t dependsReg, uint32_t dependsValue);

#endif /* TMC_IC_TMC4671_H_ */
