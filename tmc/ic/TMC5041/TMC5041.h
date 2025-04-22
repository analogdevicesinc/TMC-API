/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5041_H_
#define TMC_IC_TMC5041_H_
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5041_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

// To enable the cache mechanism in order to keep the copy of all registers, set TMC5041_CACHE to '1'.
// With this mechanism the value of write-only registers could be read from their shadow copies.
#ifndef TMC5041_CACHE
#define TMC5041_CACHE  1
//#define TMC5041_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC5041_ENABLE_TMC_CACHE to '1'.
// Set TMC5041_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC5041_ENABLE_TMC_CACHE
#define TMC5041_ENABLE_TMC_CACHE   1
//#define TMC5041_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/
extern void tmc5041_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);

/************************************************************* read / write Implementation *********************************************************************/
int32_t tmc5041_readRegister(uint16_t icID, uint8_t address);
void tmc5041_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc5041_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc5041_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc5041_readRegister(icID, field.address);

    return tmc5041_fieldExtract(value, field);
}

static inline uint32_t tmc5041_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5041_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5041_readRegister(icID, field.address);

    regValue = tmc5041_fieldUpdate(regValue, field, value);

    tmc5041_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/
#if TMC5041_CACHE == 1
#ifdef TMC5041_ENABLE_TMC_CACHE
// By default, support one IC in the cache
#ifndef TMC5041_IC_CACHE_COUNT
#define TMC5041_IC_CACHE_COUNT 1
#endif

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

typedef enum {
   TMC5041_CACHE_READ,
   TMC5041_CACHE_WRITE,
   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC5041_CACHE_FILL_DEFAULT,
} TMC5041CacheOp;

typedef struct{
    uint8_t address;
    uint32_t value;
} TMC5041RegisterConstants;

#define TMC5041_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC5041_ACCESS_READ        0x01
#define TMC5041_ACCESS_W_PRESET    0x42
#define TMC5041_IS_READABLE(x)     ((x) & TMC5041_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))

#define R30 0x00071703  // IHOLD_IRUN (Motor 1)
#define R32 0x00FFFFFF  // VHIGH      (Motor 1)
#define R50 0x00071703  // IHOLD_IRUN (Motor 2)
#define R52 0x00FFFFFF  // VHIGH      (Motor 2)

#define R6C 0x000101D5  // CHOPCONF (Motor 1)
#define R7C 0x000101D5  // CHOPCONF (Motor 2)

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
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5041_registerAccess[TMC5041_REGISTER_COUNT] = {
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x03, 0x01, ____, 0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
    0x02, 0x01, ____, ____, ____, ____, ____, ____, 0x02, 0x01, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
    0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
    0x02, 0x02, 0x02, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
    0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x40 - 0x4F
    0x02, 0x02, 0x02, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x03, 0x02, ____, 0x01, // 0x60 - 0x6F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, 0x02, ____, 0x01  // 0x70 - 0x7F
};

static const int32_t tmc5041_sampleRegisterPreset[TMC5041_REGISTER_COUNT] = {
//    0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 00 - 0F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 10 - 1F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 20 - 2F
    R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 30 - 3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 40 - 4F
    R50, 0,   R52, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 50 - 5F
    N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 60 - 6F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R7C, 0,   0,   0  // 70 - 7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R30
#undef R32
#undef R50
#undef R52
#undef R6C
#undef R7C

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMC5041RegisterConstants tmc5041_RegisterConstants[] =
 {      // Use ascending addresses!
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


extern uint8_t tmc5041_dirtyBits[TMC5041_IC_CACHE_COUNT][TMC5041_REGISTER_COUNT/8];
extern int32_t tmc5041_shadowRegister[TMC5041_IC_CACHE_COUNT][TMC5041_REGISTER_COUNT];
extern bool tmc5041_cache(uint16_t icID, TMC5041CacheOp operation, uint8_t address, uint32_t *value);
extern void tmc5041_initCache(void);
void tmc5041_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc5041_getDirtyBit(uint16_t icID, uint8_t index);
#endif
#endif
/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC5041_H_ */
