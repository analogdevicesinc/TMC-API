/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC_IC_TMC429_H_
#define TMC_IC_TMC429_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC429_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// => TMC-API wrapper
extern void tmc429_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc429_readRegister(uint16_t icID, uint8_t address);
void tmc429_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc429_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc429_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc429_fieldRead(uint16_t icID, RegisterField field)
{
	uint32_t value = tmc429_readRegister(icID, field.address);

    return tmc429_fieldExtract(value, field);
}

static inline uint32_t tmc429_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc429_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
	uint32_t regValue = tmc429_readRegister(icID, field.address);

	regValue = tmc429_fieldUpdate(regValue, field, value);

    tmc429_writeRegister(icID, field.address, regValue);
}


#endif /* TMC_IC_TMC429_H_ */