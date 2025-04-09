/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef API_IC_MAX22215_H
#define API_IC_MAX22215_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "MAX22215_HW_Abstraction.h"

typedef enum {
    IC_BUS_SPI,
    IC_BUS_IIC,
} MAX22215BusType;

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

// => TMC-API wrapper
extern bool max22215_readWriteIIC(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern MAX22215BusType max22215_getBusType(uint16_t icID);
extern uint8_t max22215_getDeviceAddress(uint16_t icID);
// => TMC-API wrapper

int32_t max22215_readRegister(uint16_t icID, uint8_t address);
void max22215_writeRegister(uint16_t icID, uint8_t address, int32_t value);

static inline uint32_t max22215_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t max22215_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = max22215_readRegister(icID, field.address);

    return max22215_fieldExtract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void max22215_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = max22215_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    max22215_writeRegister(icID, field.address, regValue);
}


#endif /* API_IC_MAX22215_H */
