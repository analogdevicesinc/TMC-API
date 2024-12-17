/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef API_IC_MAX22216_H
#define API_IC_MAX22216_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "MAX22216_HW_Abstraction.h"

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;
// Usage note: use 1 TypeDef per IC
typedef struct {
    uint8_t channel;
    uint8_t slaveAddress;
    uint8_t crc_en;
} MAX22216TypeDef;

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
uint8_t max22216_CRC(uint8_t *data, size_t length);

    return value;
}

static inline uint16_t max22216_fieldRead(uint16_t icID, RegisterField field)
{
    uint16_t value = max22216_readRegister(icID, field.address);

    return max22216_fieldExtract(value, field);
}
void max22216_writeDatagram(MAX22216TypeDef *max22216, uint8_t address, uint8_t x1, uint8_t x2);
void max22216_writeInt(MAX22216TypeDef *max22216, uint8_t address, int16_t value);
int32_t max22216_readInt(MAX22216TypeDef *max22216, uint8_t address);

static inline uint16_t max22216_fieldUpdate(uint16_t data, RegisterField field, uint16_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}
void max22216_writeIntDep(MAX22216TypeDef *max22216, uint8_t address, int32_t value, uint8_t dep_address, int32_t dep_value);
int32_t max22216_readIntDep(MAX22216TypeDef *max22216, uint8_t address, uint8_t dep_address, int32_t dep_value);

static inline void max22216_fieldWrite(uint16_t icID, RegisterField field, uint16_t value)
{
    uint16_t regValue = max22216_readRegister(icID, field.address);

    regValue = max22216_fieldUpdate(regValue, field, value);
void max22216_init(MAX22216TypeDef *max22216, uint8_t channel);

    max22216_writeRegister(icID, field.address, regValue);
}
uint8_t max22216_getSlaveAddress(const MAX22216TypeDef *max22216);
void max22216_setSlaveAddress(MAX22216TypeDef *max22216, uint8_t slaveAddress);

#endif /* API_IC_MAX22216_H */
