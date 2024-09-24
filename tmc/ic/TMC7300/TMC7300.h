/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC7300_H_
#define TMC_IC_TMC7300_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC7300_HW_Abstraction.h"


/*******************************************************************************
 * API Configuration Defines
 * These control optional features of the TMC-API implementation.
 * These can be commented in/out here or defined from the build system.
 *******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

// To enable the cache mechanism in order to keep the copy of all registers, set TMC7300_CACHE to '1'.
// With this mechanism the value of write-only registers could be read from their shadow copies.
#ifndef TMC7300_CACHE
#define TMC7300_CACHE  1
//#define TMC7300_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC7300_ENABLE_TMC_CACHE to '1'.
// Set TMC7300_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC7300_ENABLE_TMC_CACHE
#define TMC7300_ENABLE_TMC_CACHE   1
//#define TMC7300_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/


/************************************************************* read / write Implementation *********************************************************************/

// => TMC-API wrapper
extern bool tmc7300_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc7300_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc7300_readRegister(uint16_t icID, uint8_t address);
void tmc7300_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc7300_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc7300_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc7300_readRegister(icID, field.address);

    return tmc7300_fieldExtract(value, field);
}

static inline uint32_t tmc7300_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc7300_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc7300_readRegister(icID, field.address);

    regValue = tmc7300_fieldUpdate(regValue, field, value);

    tmc7300_writeRegister(icID, field.address, regValue);
}
/**************************************************************** Cache Implementation *************************************************************************/
#if TMC7300_CACHE == 1
#ifdef TMC7300_ENABLE_TMC_CACHE

// By default, support one IC in the cache
#ifndef TMC7300_IC_CACHE_COUNT
#define TMC7300_IC_CACHE_COUNT 1
#endif

#define TMC7300_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC7300_ACCESS_READ        0x01
#define TMC7300_ACCESS_W_PRESET    0x42
#define TMC7300_ACCESS_RW_PRESET   0x43
#define TMC7300_IS_READABLE(x)     ((x) & TMC7300_ACCESS_READ)
#define ARRAY_SIZE(x)             (sizeof(x)/sizeof(x[0]))

typedef enum {
    TMC7300_CACHE_READ,
    TMC7300_CACHE_WRITE,
    // Special operation: Put content into the cache without marking the entry as dirty.
    // Only used to initialize the cache with hardware defaults. This will allow reading
    // from write-only registers that have a value inside them on reset. When using this
    // operation, a restore will *not* rewrite that filled register!
    TMC7300_CACHE_FILL_DEFAULT,
} TMC7300CacheOp;

typedef struct{
    uint8_t address;
    uint32_t value;
} TMC7300RegisterConstants;

// Helper define:
// Most register permission arrays are initialized with 128 values.
// In those fields its quite hard to have an easy overview of available
// registers. For that, ____ is defined to 0, since 4 underscores are
// very easy to distinguish from the 2-digit hexadecimal values.
// This way, the used registers (permission != ACCESS_NONE) are easily spotted
// amongst unused (permission == ACCESS_NONE) registers.
#define ____ 0x00

// Helper define:
// Default reset values are not used if the corresponding register has a
// hardware preset. Since this is not directly visible in the default
// register reset values array, N_A is used as an indicator for a preset
// value, where any value will be ignored anyways (N_A: not available).
#define N_A 0

#define R00 0x00000007 // GCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x42: write, has hardware presets on reset
//   0x43: read/write, has hardware presets on reset
static const uint8_t tmc7300_registerAccess[TMC7300_REGISTER_COUNT] =
{
        //  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
        0x03, 0x23, 0x01, 0x02, ____, ____, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
        0x42, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
        ____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x43, ____, ____, 0x01, // 0x60 - 0x6F
        0x43, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc7300_sampleRegisterPreset[TMC7300_REGISTER_COUNT] =
{
        //    0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
        R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
        N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   N_A, 0,   0,   0, // 0x60 - 0x6F
        N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R00

// Register constants (only required for 0x42 and 0x43 registers)
// This allows us to fill the shadow registers with the register content in
// order to provide the TMCL-IDE with correct values to display.
static const TMC7300RegisterConstants tmc7300_RegisterConstants[] =
{        // Use ascending addresses!
        { 0x10, 0x00001F01 }, // CURRENT_LIMIT
        { 0x6C, 0x13008001 }, // CHOPCONF
        { 0x70, 0xC40D1024 }, // PWMCONF
};

extern uint8_t tmc7300_dirtyBits[TMC7300_IC_CACHE_COUNT][TMC7300_REGISTER_COUNT/8];
extern int32_t tmc7300_shadowRegister[TMC7300_IC_CACHE_COUNT][TMC7300_REGISTER_COUNT];
bool tmc7300_cache(uint16_t icID, TMC7300CacheOp operation, uint8_t address, uint32_t *value);
void tmc7300_initCache(void);
void tmc7300_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc7300_getDirtyBit(uint16_t icID, uint8_t index);
#endif
#endif
/***************************************************************************************************************************************************/
#endif /* TMC_IC_TMC7300_H_ */
