/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2226_H_
#define TMC_IC_TMC2226_H_

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "TMC2226_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/
// => TMC-API wrapper
extern bool tmc2226_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc2226_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#ifndef TMC2226_CACHE
#define TMC2226_CACHE   1
//#define TMC2226_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC2226_ENABLE_TMC_CACHE to '1'.
// Set TMC2226_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC2226_ENABLE_TMC_CACHE
#define TMC2226_ENABLE_TMC_CACHE   1
//#define TMC2226_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/
int32_t tmc2226_readRegister(uint16_t icID, uint8_t address);
void tmc2226_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc2226_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc2226_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2226_readRegister(icID, field.address);

    return tmc2226_fieldExtract(value, field);
}

static inline uint32_t tmc2226_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2226_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2226_readRegister(icID, field.address);

    regValue = tmc2226_fieldUpdate(regValue, field, value);

    tmc2226_writeRegister(icID, field.address, regValue);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

#if TMC2226_CACHE == 1
#if TMC2226_ENABLE_TMC_CACHE == 1
#include "tmc/helpers/API_Header.h"

// By default, support one IC in the cache
#ifndef TMC2226_IC_CACHE_COUNT
#define TMC2226_IC_CACHE_COUNT 1
#endif

typedef enum
{
   TMC2226_CACHE_READ,
   TMC2226_CACHE_WRITE,

   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC2226_CACHE_FILL_DEFAULT

} TMC2226CacheOp;



// Default Register values
#define R00 0x000001C1  // GCONF
#define R10 0x00071703  // IHOLD_IRUN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC10D0024  // PWMCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
//   0x42: read/write, has hardware presets on reset
static const uint8_t tmc2226_registerAccess[TMC2226_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x02, 0x02, 0x01, 0x01, 0x43, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x42, 0x01, 0x42, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x43, ____, ____, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2226_sampleRegisterPreset[TMC2226_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
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
#undef R6C
#undef R70

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMC2226RegisterConstants tmc2226_RegisterConstants[] =
{		// Use ascending addresses!
		{ 0x11, 0x00000014 }, // TPOWERDOWN
};

#undef R10
#undef R6C
#undef R70

extern uint8_t tmc2226_dirtyBits[TMC2226_IC_CACHE_COUNT][TMC2226_REGISTER_COUNT/8];
extern int32_t tmc2226_shadowRegister[TMC2226_IC_CACHE_COUNT][TMC2226_REGISTER_COUNT];
void tmc2226_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc2226_getDirtyBit(uint16_t icID, uint8_t index);
extern bool tmc2226_cache(uint16_t icID, TMC2226CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

#endif /* TMC_IC_TMC2226_H_ */
