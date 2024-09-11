/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2160_H_
#define TMC_IC_TMC2160_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC2160_HW_Abstraction.h"

/******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

// To enable the cache mechanism in order to keep the copy of all registers, set TMC2160_CACHE to '1'.
// With this mechanism the value of write-only registers could be read from their shadow copies.
#ifndef TMC2160_CACHE
#define TMC2160_CACHE  1
//#define TMC2160_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC2160_ENABLE_TMC_CACHE to '1'.
// Set TMC2160_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC2160_ENABLE_TMC_CACHE
#define TMC2160_ENABLE_TMC_CACHE   1
//#define TMC2160_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/


/************************************************************* read / write Implementation *********************************************************************/

// => TMC-API wrapper
extern void tmc2160_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc2160_readRegister(uint16_t icID, uint8_t address);
void tmc2160_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} TMC2160RegisterField;

static inline uint32_t tmc2160_fieldExtract(uint32_t data, TMC2160RegisterField field)
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

static inline uint32_t tmc2160_fieldRead(uint16_t icID, TMC2160RegisterField field)
{
    uint32_t value = tmc2160_readRegister(icID, field.address);

    return tmc2160_fieldExtract(value, field);
}

static inline uint32_t tmc2160_fieldUpdate(uint32_t data, TMC2160RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2160_fieldWrite(uint16_t icID, TMC2160RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2160_readRegister(icID, field.address);

    regValue = tmc2160_fieldUpdate(regValue, field, value);

    tmc2160_writeRegister(icID, field.address, regValue);
}


/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/


/**************************************************************** Cache Implementation *************************************************************************/
#if TMC2160_CACHE == 1
#ifdef TMC2160_ENABLE_TMC_CACHE

// By default, support one IC in the cache
#ifndef TMC2160_IC_CACHE_COUNT
#define TMC2160_IC_CACHE_COUNT 1
#endif

typedef enum {
   TMC2160_CACHE_READ,
   TMC2160_CACHE_WRITE,
   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC2160_CACHE_FILL_DEFAULT,
} TMC2160CacheOp;

typedef struct{
    uint8_t address;
    uint32_t value;
} TMC2160RegisterConstants;


#define TMC2160_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC2160_ACCESS_READ        0x01
#define TMC2160_ACCESS_W_PRESET    0x42
#define TMC2160_IS_READABLE(x)     ((x) & TMC2160_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))

// Default Register values
#define R10 0x00070A03  // IHOLD_IRUN
#define R6C 0x10410153  // CHOPCONF
#define R70 0xC40C001E  // PWMCONF


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

// Register access permissions:
// 0x00: none (reserved)
// 0x01: read
// 0x02: write
// 0x03: read/write
// 0x11: read to clear
// 0x42: write, has hardware presets on reset
static const uint8_t tmc2160_registerAccess[TMC2160_REGISTER_COUNT] =
{
//    0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x03, 0x23, 0x01, 0x02, 0x23, 0x02, 0x02, 0x01, 0x42, 0x42, 0x42, 0x02, 0x01, ____, ____, ____, // 0x00 - 0x0F
    0x02, 0x02, 0x01, 0x02, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
    0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
    ____, ____, ____, 0x02, 0x03, 0x23, 0x01, ____, 0x03, 0x03, 0x02, 0x23, 0x01, 0x02, ____, ____, // 0x30 - 0x3F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
    0x02, 0x01, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2160_sampleRegisterPreset[TMC2160_REGISTER_COUNT] =
{
//    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
    R10, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
    N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
    R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R10
#undef R6C
#undef R70

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMC2160RegisterConstants tmc2160_RegisterConstants[] =
{        // Use ascending addresses!
        { 0x08, 0x00000000 }, // FACTORY_CONF
        { 0x09, 0x00000000 }, // SHORT_CONF
        { 0x0A, 0x00000000 }, // DRV_CONF
        { 0x60, 0xAAAAB554 }, // MSLUT[0]
        { 0x61, 0x4A9554AA }, // MSLUT[1]
        { 0x62, 0x24492929 }, // MSLUT[2]
        { 0x63, 0x10104222 }, // MSLUT[3]
        { 0x64, 0xFBFFFFFF }, // MSLUT[4]
        { 0x65, 0xB5BB777D }, // MSLUT[5]
        { 0x66, 0x49295556 }, // MSLUT[6]
        { 0x67, 0x00404222 }, // MSLUT[7]
        { 0x68, 0xFFFF8056 }, // MSLUTSEL
        { 0x69, 0x00F70000 }  // MSLUTSTART
};

extern uint8_t tmc2160_dirtyBits[TMC2160_IC_CACHE_COUNT][TMC2160_REGISTER_COUNT/8];
extern int32_t tmc2160_shadowRegister[TMC2160_IC_CACHE_COUNT][TMC2160_REGISTER_COUNT];
extern bool tmc2160_cache(uint16_t icID, TMC2160CacheOp operation, uint8_t address, uint32_t *value);
extern void tmc2160_initCache(void);
void tmc2160_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc2160_getDirtyBit(uint16_t icID, uint8_t index);
#endif
#endif
/***************************************************************************************************************************************************/
#endif /* TMC_IC_TMC2160_H_ */
