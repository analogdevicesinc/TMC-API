/*******************************************************************************
* Copyright © 2026 Analog Devices, Inc.
*******************************************************************************/


#ifndef TMC_IC_TMC3241_H_
#define TMC_IC_TMC3241_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC3241_HW_Abstraction.h"

#define DEFAULT_MOTOR  0

// => TMC-API wrapper
extern void tmc3241_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc3241_readRegister(uint16_t icID, uint8_t address);
void tmc3241_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc3241_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc3241_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc3241_readRegister(icID, field.address);

    return tmc3241_fieldExtract(value, field);
}

static inline uint32_t tmc3241_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc3241_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc3241_readRegister(icID, field.address);

    regValue = tmc3241_fieldUpdate(regValue, field, value);

    tmc3241_writeRegister(icID, field.address, regValue);
}

#endif /* TMC_IC_TMC3241_H_ */
