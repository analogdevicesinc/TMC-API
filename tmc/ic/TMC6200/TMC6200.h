/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC6200_H_
#define TMC_IC_TMC6200_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC6200_HW_Abstraction.h"

// => TMC-API wrapper
extern void tmc6200_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc6200_readRegister(uint16_t icID, uint8_t address);
void tmc6200_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc6200_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc6200_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc6200_readRegister(icID, field.address);

    return tmc6200_fieldExtract(value, field);
}

static inline uint32_t tmc6200_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc6200_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc6200_readRegister(icID, field.address);

    regValue = tmc6200_fieldUpdate(regValue, field, value);

    tmc6200_writeRegister(icID, field.address, regValue);
}

#endif /* TMC_IC_TMC6200_H_ */
