/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5130_H_
#define TMC_IC_TMC5130_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5130_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1


// To enable the cache mechanism in order to keep the copy of all registers, set TMC5130_CACHE to '1'.
// With this mechanism the value of write-only registers could be read from their shadow copies.
#ifndef TMC5130_CACHE
#define TMC5130_CACHE	1
//#define TMC5130_CACHE   0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC5130_ENABLE_TMC_CACHE to '1'.
// Set TMC5130_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC5130_ENABLE_TMC_CACHE
#define TMC5130_ENABLE_TMC_CACHE   1
//#define TMC5130_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/

typedef enum {
	IC_BUS_SPI,
	IC_BUS_UART,
} TMC5130BusType;

typedef struct{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

// => TMC-API wrapper
extern void tmc5130_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5130_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5130BusType tmc5130_getBusType(uint16_t icID);
extern uint8_t tmc5130_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5130_readRegister(uint16_t icID, uint8_t address);
void tmc5130_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5130_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

static inline uint32_t tmc5130_field_extract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc5130_field_read(uint16_t icID, RegisterField field)
{
	uint32_t value = tmc5130_readRegister(icID, field.address);

    return tmc5130_field_extract(value, field);
}

static inline uint32_t tmc5130_field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5130_field_write(uint16_t icID, RegisterField field, uint32_t value)
{
	uint32_t regValue = tmc5130_readRegister(icID, field.address);

	regValue = tmc5130_field_update(regValue, field, value);

    tmc5130_writeRegister(icID, field.address, regValue);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino *****************************/

/**************************************************************** Cache Implementation *************************************************************************/
#if TMC5130_CACHE == 1
#ifdef TMC5130_ENABLE_TMC_CACHE
#include "tmc/helpers/API_Header.h"

// By default, support one IC in the cache
#ifndef TMC5130_IC_CACHE_COUNT
#define TMC5130_IC_CACHE_COUNT 1
#endif

typedef enum {
	TMC5130_CACHE_READ,
	TMC5130_CACHE_WRITE,

	// Special operation: Put content into the cache without marking the entry as dirty.
	// Only used to initialize the cache with hardware defaults. This will allow reading
	// from write-only registers that have a value inside them on reset. When using this
	// operation, a restore will *not* rewrite that filled register!
	TMC5130_CACHE_FILL_DEFAULT,
} TMC5130CacheOp;

typedef struct{
    uint8_t address;
    uint32_t value;
} TMC5130RegisterConstants;

#define TMC5130_ACCESS_READ        0x01
#define TMC5130_ACCESS_W_PRESET        0x42
#define TMC5130_IS_READABLE(x)    ((x) & TMC5130_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))
// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	int32_t registerResetState[TMC5130_REGISTER_COUNT];
	uint8_t registerAccess[TMC5130_REGISTER_COUNT];
} TMC5130TypeDef;
extern TMC5130TypeDef TMC5130;
typedef void (*tmc5130_callback)(TMC5130TypeDef*, ConfigState);

// Default Register values
#define R10 0x00071703  // IHOLD_IRUN
#define R3A 0x00010000  // ENC_CONST
#define R6C 0x000101D5  // CHOPCONF

// Helper define:
// Default reset values are not used if the corresponding register has a
// hardware preset. Since this is not directly visible in the default
// register reset values array, N_A is used as an indicator for a preset
// value, where any value will be ignored anyways (N_A: not available).
#define N_A 0

// Helper define:
// Most register permission arrays are initialized with 128 values.
// In those fields its quite hard to have an easy overview of available
// registers. For that, ____ is defined to 0, since 4 underscores are
// very easy to distinguish from the 2-digit hexadecimal values.
// This way, the used registers (permission != ACCESS_NONE) are easily spotted
// amongst unused (permission == ACCESS_NONE) registers.
#define ____ 0x00

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5130_registerAccess[TMC5130_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x21, 0x01, 0x02, 0x13, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x02, 0x01, 0x02, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
	____, ____, ____, 0x02, 0x03, 0x21, 0x01, ____, 0x03, 0x03, 0x02, 0x21, 0x01, ____, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
	0x42, 0x01, 0x02, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc5130_sampleRegisterPreset[TMC5130_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R10
#undef R3A
#undef R6C

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMC5130RegisterConstants tmc5130_RegisterConstants[] =
{		// Use ascending addresses!
		{ 0x60, 0xAAAAB554 }, // MSLUT[0]
		{ 0x61, 0x4A9554AA }, // MSLUT[1]
		{ 0x62, 0x24492929 }, // MSLUT[2]
		{ 0x63, 0x10104222 }, // MSLUT[3]
		{ 0x64, 0xFBFFFFFF }, // MSLUT[4]
		{ 0x65, 0xB5BB777D }, // MSLUT[5]
		{ 0x66, 0x49295556 }, // MSLUT[6]
		{ 0x67, 0x00404222 }, // MSLUT[7]
		{ 0x68, 0xFFFF8056 }, // MSLUTSEL
		{ 0x69, 0x00F70000 }, // MSLUTSTART
		{ 0x70, 0x00050480 }  // PWMCONF
};

extern uint8_t tmc5130_dirtyBits[TMC5130_IC_CACHE_COUNT][TMC5130_REGISTER_COUNT/8];
extern int32_t tmc5130_shadowRegister[TMC5130_IC_CACHE_COUNT][TMC5130_REGISTER_COUNT];
extern bool tmc5130_cache(uint16_t icID, TMC5130CacheOp operation, uint8_t address, uint32_t *value);
void tmc5130_setDirtyBit(uint16_t icID, uint8_t index, bool value);
bool tmc5130_getDirtyBit(uint16_t icID, uint8_t index);
void tmc5130_initCache(void);
#endif
#endif
// API Functions
// All functions act on one IC identified by the TMC5130TypeDef pointer

void tmc5130_init(TMC5130TypeDef *tmc5130, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
void tmc5130_fillShadowRegisters(TMC5130TypeDef *tmc5130);
uint8_t tmc5130_reset(TMC5130TypeDef *tmc5130);
uint8_t tmc5130_restore(TMC5130TypeDef *tmc5130);
void tmc5130_setRegisterResetState(TMC5130TypeDef *tmc5130, const int32_t *resetState);
void tmc5130_setCallback(TMC5130TypeDef *tmc5130, tmc5130_callback callback);
void tmc5130_periodicJob(TMC5130TypeDef *tmc5130, uint32_t tick);

void tmc5130_rotate(TMC5130TypeDef *tmc5130, uint8_t motor, int32_t velocity);
void tmc5130_right(TMC5130TypeDef *tmc5130, uint8_t motor, uint32_t velocity);
void tmc5130_left(TMC5130TypeDef *tmc5130, uint8_t motor, uint32_t velocity);
void tmc5130_stop(TMC5130TypeDef *tmc5130,uint8_t motor);
void tmc5130_moveTo(TMC5130TypeDef *tmc5130, uint8_t motor, int32_t position, uint32_t velocityMax);
void tmc5130_moveBy(TMC5130TypeDef *tmc5130, uint8_t motor, int32_t *ticks, uint32_t velocityMax);

/***************************************************************************************************************************************************/
#endif /* TMC_IC_TMC5130_H_ */
