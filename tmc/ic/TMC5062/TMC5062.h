/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5062_H_
#define TMC_IC_TMC5062_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5062_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#ifndef TMC5062_CACHE
#define TMC5062_CACHE  1
//#define TMC5062_CACHE 0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC5062_ENABLE_TMC_CACHE to '1'.
// Set TMC5062_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC5062_ENABLE_TMC_CACHE
#define TMC5062_ENABLE_TMC_CACHE   1
//#define TMC5062_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/

typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
} TMC5062BusType;

typedef struct {
    uint32_t LUT_0;  // Bits   0 -  31
    uint32_t LUT_1;  // Bits  32 -  63
    uint32_t LUT_2;  // Bits  64 -  95
    uint32_t LUT_3;  // Bits  96 - 127
    uint32_t LUT_4;  // Bits 128 - 159
    uint32_t LUT_5;  // Bits 160 - 191
    uint32_t LUT_6;  // Bits 192 - 223
    uint32_t LUT_7;  // Bits 224 - 255

    uint8_t X1;     // Segment 1
    uint8_t X2;     // Segment 2
    uint8_t X3;     // Segment 3
    // Segment width. Determines bit meaning (Actual bit value = (Wn - 1) + bit)
    uint8_t W0 : 2; // Segment [ 0 : X1-1]
    uint8_t W1 : 2; // Segment [X1 : X2-1]
    uint8_t W2 : 2; // Segment [X2 : X3-1]
    uint8_t W3 : 2; // Segment [X3 :  255]

    uint8_t  START_SIN;    // Absolute current at MSLUT[0]
    uint8_t  START_SIN90;  // Absolute current at MSLUT[256]
} TMC5062_MicroStepTable;

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

// => TMC-API wrapper
extern void tmc5062_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5062_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5062BusType tmc5062_getBusType(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5062_readRegister(uint16_t icID, uint8_t address);
void tmc5062_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5062_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

static inline uint32_t tmc5062_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc5062_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc5062_readRegister(icID, field.address);

    return tmc5062_fieldExtract(value, field);
}

static inline uint32_t tmc5062_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5062_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5062_readRegister(icID, field.address);

    regValue = tmc5062_fieldUpdate(regValue, field, value);

    tmc5062_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/

#if TMC5062_CACHE == 1
#if TMC5062_ENABLE_TMC_CACHE == 1

// By default, support one IC in the cache
#ifndef TMC5062_IC_CACHE_COUNT
#define TMC5062_IC_CACHE_COUNT 1
#endif

typedef enum {
   TMC5062_CACHE_READ,
   TMC5062_CACHE_WRITE,

   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC5062_CACHE_FILL_DEFAULT
} TMC5062CacheOp;

typedef struct
{
    uint8_t address;
    uint32_t value;
} TMC5062RegisterConstants;

#define TMC5062_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC5062_ACCESS_READ        0x01
#define TMC5062_ACCESS_W_PRESET    0x42
#define TMC5062_IS_READABLE(x)    ((x) & TMC5062_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))

// Default Register Values
#define R30 0x00071703  // IHOLD_IRUN
#define R32 0x00FFFFFF  // VHIGH
#define R3A 0x00010000  // ENC_CONST
#define R50 R30
#define R52 R32
#define R5A R3A
#define R6C 0x000101D5  // CHOPCONF
#define R7C R6C

#define ____ 0x00
#ifndef N_A
    #define N_A 0x00
#endif

static const int32_t tmc5062_sampleRegisterPreset[TMC5062_REGISTER_COUNT] = {
//  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
    R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
    R50, 0,   R52, 0,   0,   0,   0,   0,   0,   0,   R5A, 0,   0,   0,   0,   0, // 0x50 - 0x5F
    N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
    N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R7C, 0,   0,   0  // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R30
#undef R32
#undef R3A
#undef R50
#undef R52
#undef R5A
#undef R6C
#undef R7C

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5062_registerAccess[TMC5062_REGISTER_COUNT] = {
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x03, 0x01, 0x01, 0x02, 0x07, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
    0x02, 0x01, ____, ____, ____, ____, ____, ____, 0x02, 0x01, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
    0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
    0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x30 - 0x3F
    0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x40 - 0x4F
    0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x50 - 0x5F
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01  // 0x70 - 0x7F
};


static const TMC5062RegisterConstants tmc5062_RegisterConstants[] =
{       // Use ascending addresses!
        { 0x60, 0xAAAAB554 }, // MSLUT[0]_M1
        { 0x61, 0x4A9554AA }, // MSLUT[1]_M1
        { 0x62, 0x24492929 }, // MSLUT[2]_M1
        { 0x63, 0x10104222 }, // MSLUT[3]_M1
        { 0x64, 0xFBFFFFFF }, // MSLUT[4]_M1
        { 0x65, 0xB5BB777D }, // MSLUT[5]_M1
        { 0x66, 0x49295556 }, // MSLUT[6]_M1
        { 0x67, 0x00404222 }, // MSLUT[7]_M1
        { 0x68, 0xFFFF8056 }, // MSLUTSEL_M1
        { 0x69, 0x00F70000 }, // MSLUTSTART_M1
        { 0x70, 0xAAAAB554 }, // MSLUT[0]_M2
        { 0x71, 0x4A9554AA }, // MSLUT[1]_M2
        { 0x72, 0x24492929 }, // MSLUT[2]_M2
        { 0x73, 0x10104222 }, // MSLUT[3]_M2
        { 0x74, 0xFBFFFFFF }, // MSLUT[4]_M2
        { 0x75, 0xB5BB777D }, // MSLUT[5]_M2
        { 0x76, 0x49295556 }, // MSLUT[6]_M2
        { 0x77, 0x00404222 }, // MSLUT[7]_M2
        { 0x78, 0xFFFF8056 }, // MSLUTSEL_M2
        { 0x79, 0x00F70000 }  // MSLUTSTART_M2
};

extern uint8_t tmc5062_dirtyBits[TMC5062_IC_CACHE_COUNT][TMC5062_REGISTER_COUNT/8];
extern int32_t tmc5062_shadowRegister[TMC5062_IC_CACHE_COUNT][TMC5062_REGISTER_COUNT];
void tmc5062_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc5062_getDirtyBit(uint16_t icID, uint8_t index);
void tmc5062_initCache(void);
extern bool tmc5062_cache(uint16_t icID, TMC5062CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif
// => TMC-API wrapper

/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC5062_H_ */
