/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2209_H_
#define TMC_IC_TMC2209_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC2209_HW_Abstraction.h"

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#define TMC2209_CACHE	1
#define TMC2209_ENABLE_TMC_CACHE

// => TMC-API wrapper
extern bool tmc2209_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc2209_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc2209_readRegister(uint16_t icID, uint8_t address);
void tmc2209_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc2209_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc2209_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2209_readRegister(icID, field.address);

    return tmc2209_fieldExtract(value, field);
}

static inline uint32_t tmc2209_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2209_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2209_readRegister(icID, field.address);

    regValue = tmc2209_fieldUpdate(regValue, field, value);

    tmc2209_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/
#if TMC2209_CACHE == 1
#ifdef TMC2209_ENABLE_TMC_CACHE

// By default, support one IC in the cache
#ifndef TMC2209_IC_CACHE_COUNT
#define TMC2209_IC_CACHE_COUNT 1
#endif

typedef enum {
	TMC2209_CACHE_READ,
	TMC2209_CACHE_WRITE
} TMC2209CacheOp;

#define TMC2209_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC2209_ACCESS_READ        0x01
#define TMC2209_IS_READABLE(x)    ((x) & TMC2209_ACCESS_READ)

// Default Register values
#define R00 0x00000040  // GCONF
#define R10 0x00071703  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC10D0024  // PWMCONF

#define ____ 0x00

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x23: read/write, flag register (write to clear)
static const uint8_t tmc2209_defaultRegisterAccess[TMC2209_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x03, 0x23, 0x01, 0x02, 0x02, 0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
    0x02, 0x02, 0x01, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
    ____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
    0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, ____, ____, 0x01, // 0x60 - 0x6F
    0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2209_sampleRegisterPreset[TMC2209_REGISTER_COUNT] =
{
//  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
    R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
    R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R00
#undef R10
#undef R11
#undef R6C
#undef R70

extern uint8_t tmc2209_registerAccess[TMC2209_IC_CACHE_COUNT][TMC2209_REGISTER_COUNT];
extern int32_t tmc2209_shadowRegister[TMC2209_IC_CACHE_COUNT][TMC2209_REGISTER_COUNT];
extern bool tmc2209_cache(uint16_t icID, TMC2209CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC2209_H_ */
