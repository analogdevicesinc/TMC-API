/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5262_H_
#define TMC_IC_TMC5262_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5262_HW_Abstraction.h"

// Default Register values
#define R0B 0x65FF  // PLLs

// => TMC-API wrapper
extern void tmc5262_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc5262_readRegister(uint16_t icID, uint8_t address);
void tmc5262_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5262_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);
///
typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc5262_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc5262_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc5262_readRegister(icID, field.address);

    return tmc5262_fieldExtract(value, field);
}

static inline uint32_t tmc5262_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5262_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5262_readRegister(icID, field.address);

    regValue = tmc5262_fieldUpdate(regValue, field, value);

    tmc5262_writeRegister(icID, field.address, regValue);
}


#endif /* TMC_IC_TMC5262_H_ */
