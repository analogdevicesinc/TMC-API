/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2225_H_
#define TMC_IC_TMC2225_H_


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC2225_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#ifndef TMC2225_CACHE
#define TMC2225_CACHE  1
//#define TMC2225_CACHE 0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC2225_ENABLE_TMC_CACHE to '1'.
// Set TMC2225_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC2225_ENABLE_TMC_CACHE
#define TMC2225_ENABLE_TMC_CACHE   1
//#define TMC2225_ENABLE_TMC_CACHE   0
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
extern bool tmc2225_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc2225_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc2225_readRegister(uint16_t icID, uint8_t address);
void tmc2225_writeRegister(uint16_t icID, uint8_t address, int32_t value);


static inline uint32_t tmc2225_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc2225_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2225_readRegister(icID, field.address);

    return tmc2225_fieldExtract(value, field);
}

static inline uint32_t tmc2225_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2225_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2225_readRegister(icID, field.address);

    regValue = tmc2225_fieldUpdate(regValue, field, value);

    tmc2225_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/

#if TMC2225_CACHE == 1
#if TMC2225_ENABLE_TMC_CACHE == 1

// By default, support one IC in the cache
#ifndef TMC2225_IC_CACHE_COUNT
#define TMC2225_IC_CACHE_COUNT 1
#endif

typedef enum {
   TMC2225_CACHE_READ,
   TMC2225_CACHE_WRITE,

   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC2225_CACHE_FILL_DEFAULT
} TMC2225CacheOp;

#define TMC2225_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC2225_ACCESS_READ        0x01
#define TMC2225_IS_READABLE(x)    ((x) & TMC2225_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))
#define ____ 0x00

// Default Register values
#define R00 0x000000C1  // GCONF
#define R10 0x00071703  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC00D0024  // PWMCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc2225_registerAccess[TMC2225_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x02, 0x02, 0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, ____, ____, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2225_sampleRegisterPreset[TMC2225_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
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

extern uint8_t tmc2225_dirtyBits[TMC2225_IC_CACHE_COUNT][TMC2225_REGISTER_COUNT/8];
extern int32_t tmc2225_shadowRegister[TMC2225_IC_CACHE_COUNT][TMC2225_REGISTER_COUNT];
void tmc2225_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc2225_getDirtyBit(uint16_t icID, uint8_t index);
extern bool tmc2225_cache(uint16_t icID, TMC2225CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC2225_H_ */
