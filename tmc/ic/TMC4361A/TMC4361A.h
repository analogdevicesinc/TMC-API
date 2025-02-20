/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC4361A_H_
#define TMC_IC_TMC4361A_H_

#include "TMC4361A_HW_Abstraction.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#ifndef TMC4361A_CACHE
#define TMC4361A_CACHE   1
//#define TMC4361A_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC4361A_ENABLE_TMC_CACHE to '1'.
// Set TMC4361A_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC4361A_ENABLE_TMC_CACHE
#define TMC4361A_ENABLE_TMC_CACHE   1
//#define TMC4361A_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

// => TMC-API wrapper
extern void tmc4361A_setStatus(uint16_t icID, uint8_t *data);
extern void tmc4361A_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc4361A_readRegister(uint16_t icID, uint8_t address);
void tmc4361A_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc4361A_readWriteCover(uint16_t icID, uint8_t *data, size_t length);


static inline uint32_t tmc4361A_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc4361A_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc4361A_readRegister(icID, field.address);

    return tmc4361A_fieldExtract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc4361A_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc4361A_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc4361A_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/

#if TMC4361A_CACHE == 1
#if TMC4361A_ENABLE_TMC_CACHE == 1

// By default, support one IC in the cache
#ifndef TMC4361A_IC_CACHE_COUNT
#define TMC4361A_IC_CACHE_COUNT 1
#endif

typedef enum {
   TMC4361A_CACHE_READ,
   TMC4361A_CACHE_WRITE,

   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC4361A_CACHE_FILL_DEFAULT

} TMC4361ACacheOp;

typedef struct
{
    uint8_t address;
    uint32_t value;
} TMC4361ARegisterConstant;

#define TMC4361A_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC4361A_ACCESS_READ        0x01
#define TMC_ACCESS_WRITE            0x02
#define TMC4361A_ACCESS_W_PRESET    0x42
#define TMC_IS_RESETTABLE(x)        (((x) & (TMC_ACCESS_W_PRESET)) == TMC_ACCESS_WRITE) // Write bit set, Hardware preset bit not set
#define TMC4361A_IS_READABLE(x)     ((x) & TMC4361A_ACCESS_READ)
#define TMC_IS_WRITABLE(x)          ((x) & TMC_ACCESS_WRITE)
#define ARRAY_SIZE(x)               (sizeof(x)/sizeof(x[0]))
// Memory access helpers
// Force the compiler to access a location exactly once
#define ACCESS_ONCE(x) *((volatile typeof(x) *) (&x))

#ifndef MAX
    #define MAX(a,b) (((a)>(b)) ? (a) : (b))
#endif

// Default Register Values
#define R10 0x00040001 // STP_LENGTH_ADD
#define R20 0x00000001 // RAMPMODE
#define R28 0x00013880 // AMAX
#define R29 0x00013880 // DMAX
#define R2D 0x000003E8 // BOW1
#define R2E 0x000003E8 // BOW2
#define R2F 0x000003E8 // BOW3
#define R30 0x000003E8 // BOW4
#define R54 0x00009C40 // ENC_IN_RES
#define ____ 0x00

#ifndef N_A
#define N_A 0x00
#endif



static const int32_t tmc4361A_sampleRegisterPreset[TMC4361A_REGISTER_COUNT] =
{
//  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
    0,   0,   0,   0,   0,   0,   N_A, N_A, 0,   0,   N_A, N_A, 0,   0,   0,   0,   // 0x00 - 0x0F
    R10, 0,   N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   N_A, 0,   0,   N_A, // 0x10 - 0x1F
    R20, 0,   0,   0,   0,   0,   0,   0,   R28, R29, 0,   0,   0,   R2D, R2E, R2F, // 0x20 - 0x2F
    R30, N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x30 - 0x3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x40 - 0x4F
    0,   0,   0,   N_A, R54, 0,   N_A, N_A, N_A, 0,   0,   0,   0,   0,   0,   0,   // 0x50 - 0x5F
    0,   0,   N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x60 - 0x6F
    N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   N_A, N_A, 0,   N_A, 0    // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R10
#undef R20
#undef R24
#undef R28
#undef R29
#undef R2D
#undef R2E
#undef R2F
#undef R30
#undef R54

// Register access permissions:
//     0x00: none (reserved)
//     0x01: read
//     0x02: write
//     0x03: read/write
//     0x13: read/write, separate functions/values for reading or writing
//     0x23: read/write, holds read or write to clear flags
//     0x42: write, has hardware presets on reset
//     0x43: read/write, has hardware presets on reset
//     0x53: read/write, has hardware presets on reset, separate functions/values for reading or writing
static const uint8_t tmc4361A_registerAccess[TMC4361A_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x43, 0x03, 0x03, 0x03, 0x03, 0x03, 0x43, 0x43, 0x03, 0x03, 0x43, 0x43, 0x03, 0x03, 0x23, 0x01, // 0x00 - 0x0F
	0x03, 0x03, 0x43, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x43, 0x03, 0x03, 0x43, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x20 - 0x2F
	0x03, 0x43, 0x03, 0x03, 0x03, 0x03, 0x13, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x30 - 0x3F
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x40 - 0x4F
	0x03, 0x13, 0x13, 0x42, 0x13, 0x02, 0x42, 0x42, 0x42, 0x03, 0x13, 0x13, 0x02, 0x13, 0x02, 0x02, // 0x50 - 0x5F
	0x02, 0x02, 0x42, 0x02, ____, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x01, 0x13, 0x13, 0x01, 0x01, // 0x60 - 0x6F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x13, 0x01, 0x13, 0x13, 0x02, 0x42, 0x01  // 0x70 - 0x7F
};


// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMC4361ARegisterConstant tmc4361A_RegisterConstants[] =
{		// Use ascending addresses!
		{ 0x53, 0xFFFFFFFF }, // ENC_POS_DEV_TOL
		{ 0x56, 0x00A000A0 }, // SER_CLK_IN_HIGH, SER_CLK_IN_LOW
		{ 0x57, 0x00F00000 }, // SSI_IN_CLK_DELAY, SSI_IN_WTIME
		{ 0x58, 0x00000190 }, // SER_PTIME
		{ 0x62, 0x00FFFFFF }, // ENC_VEL_ZERO
		{ 0x70, 0xAAAAB554 }, // MSLUT[0]
		{ 0x71, 0x4A9554AA }, // MSLUT[1]
		{ 0x72, 0x24492929 }, // MSLUT[2]
		{ 0x73, 0x10104222 }, // MSLUT[3]
		{ 0x74, 0xFBFFFFFF }, // MSLUT[4]
		{ 0x75, 0xB5BB777D }, // MSLUT[5]
		{ 0x76, 0x49295556 }, // MSLUT[6]
		{ 0x77, 0x00404222 }, // MSLUT[7]
		{ 0x78, 0xFFFF8056 }, // MSLUTSEL
		{ 0x7E, 0x00F70000 }, // START_SIN, START_SIN_90_120, DAC_OFFSET
};


extern uint8_t tmc4361A_dirtyBits[TMC4361A_IC_CACHE_COUNT][TMC4361A_REGISTER_COUNT/8];
extern int32_t tmc4361A_shadowRegister[TMC4361A_IC_CACHE_COUNT][TMC4361A_REGISTER_COUNT];
void tmc4361A_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc4361A_getDirtyBit(uint16_t icID, uint8_t index);
extern bool tmc4361A_cache(uint16_t icID, TMC4361ACacheOp operation, uint8_t address, uint32_t *value);
void tmc4361A_initCache(void);
#endif
#endif

/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC4361A_H_ */
