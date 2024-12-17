/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef API_IC_MAX22216_H
#define API_IC_MAX22216_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "MAX22216_HW_Abstraction.h"

extern void max22216_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern uint8_t max22216_getCRCEnState(void);
uint16_t max22216_readRegister(uint16_t icID, uint8_t address);
void max22216_writeRegister(uint16_t icID, uint8_t address, uint16_t value);
uint8_t max22216_CRC(uint8_t *data, size_t length);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint16_t max22216_fieldExtract(uint16_t data, RegisterField field)
{
    uint16_t value = (data & field.mask) >> field.shift;

    if (field.isSigned)
    {
        // Apply signedness conversion
        uint16_t baseMask = field.mask >> field.shift;
        uint16_t signMask = baseMask & (~baseMask >> 1);
        value             = (value ^ signMask) - signMask;
    }

    return value;
}

static inline uint16_t max22216_fieldRead(uint16_t icID, RegisterField field)
{
    uint16_t value = max22216_readRegister(icID, field.address);

    return max22216_fieldExtract(value, field);
}

static inline uint16_t max22216_fieldUpdate(uint16_t data, RegisterField field, uint16_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void max22216_fieldWrite(uint16_t icID, RegisterField field, uint16_t value)
{
    uint16_t regValue = max22216_readRegister(icID, field.address);

    regValue = max22216_fieldUpdate(regValue, field, value);

    max22216_writeRegister(icID, field.address, regValue);
}

#endif /* API_IC_MAX22216_H */
