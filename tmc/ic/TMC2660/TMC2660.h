/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2660_H_
#define TMC_IC_TMC2660_H_

#include "TMC2660_HW_Abstraction.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

#ifndef TMC2660_CACHE
#define TMC2660_CACHE  1
//#define TMC2660_CACHE 0
#endif

// To use the caching mechanism already implemented by the TMC-API, set TMC2660_ENABLE_TMC_CACHE to '1'.
// Set TMC2660_ENABLE_TMC_CACHE to '0' if one wants to have their own cache implementation.
#ifndef TMC2660_ENABLE_TMC_CACHE
#define TMC2660_ENABLE_TMC_CACHE   1
//#define TMC2660_ENABLE_TMC_CACHE   0
#endif

/******************************************************************************/

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} TMC2660RegisterField;

//TMC-API wrapper
extern uint8_t tmc2660_getcontinuousModeEnable(uint8_t icID);
extern void tmc2660_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
//TMC-API wrapper

void tmc2660_writeRegister(uint8_t icID, uint8_t address, uint32_t value);
uint32_t tmc2660_readRegister(uint8_t icID, uint8_t address);
uint8_t tmc2660_getStatusBits(uint8_t icID);
void readWrite(uint8_t icID, uint32_t value);
void readImmediately(uint8_t icID, uint8_t rdsel);

static inline uint32_t tmc2660_fieldExtract(uint32_t data, TMC2660RegisterField field)
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

static inline uint32_t tmc2660_fieldRead(uint16_t icID, TMC2660RegisterField field)
{
    uint32_t value = tmc2660_readRegister(icID, field.address);

    return tmc2660_fieldExtract(value, field);
}

static inline uint32_t tmc2660_fieldUpdate(uint32_t data, TMC2660RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2660_fieldWrite(uint16_t icID, TMC2660RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2660_readRegister(icID, field.address);

    regValue = tmc2660_fieldUpdate(regValue, field, value);

    tmc2660_writeRegister(icID, field.address, regValue);
}

/**************************************************************** Cache Implementation *************************************************************************/

#if TMC2660_CACHE == 1
#if TMC2660_ENABLE_TMC_CACHE == 1

// By default, support one IC in the cache
#ifndef TMC2660_IC_CACHE_COUNT
#define TMC2660_IC_CACHE_COUNT 1
#endif

typedef enum {
   TMC2660_CACHE_READ,
   TMC2660_CACHE_WRITE,

   // Special operation: Put content into the cache without marking the entry as dirty.
   // Only used to initialize the cache with hardware defaults. This will allow reading
   // from write-only registers that have a value inside them on reset. When using this
   // operation, a restore will *not* rewrite that filled register!
   TMC2660_CACHE_FILL_DEFAULT
} TMC2660CacheOp;

#define TMC_ACCESS_READ       0x01
#define TMC2660_IS_READABLE(x)    ((x) & TMC_ACCESS_READ)
#define TMC_ACCESS_NONE        0x00
#define TMC_ACCESS_WRITE       0x02

static const uint8_t tmc2660_registerAccess[TMC2660_REGISTER_COUNT] =
{
    TMC_ACCESS_READ,   // 0: RESPONSE 0
    TMC_ACCESS_READ,   // 1: RESPONSE 1
    TMC_ACCESS_READ,   // 2: RESPONSE 2
    TMC_ACCESS_READ,   // 3: RESPONSE_LATEST
    TMC_ACCESS_NONE,   // 4: UNUSED
    TMC_ACCESS_NONE,   // 5: UNUSED
    TMC_ACCESS_NONE,   // 6: UNUSED
    TMC_ACCESS_NONE,   // 7: UNUSED
    TMC_ACCESS_WRITE,  // 8: DRVCTRL
    TMC_ACCESS_NONE,   // 9: UNUSED
    TMC_ACCESS_NONE,   // A: UNUSED
    TMC_ACCESS_NONE,   // B: UNUSED
    TMC_ACCESS_WRITE,  // C: CHOPCONF
    TMC_ACCESS_WRITE,  // D: SMARTEN
    TMC_ACCESS_WRITE,  // E: SGCSCONF
    TMC_ACCESS_WRITE   // F: DRVCONF
};

static const int32_t tmc2660_sampleRegisterPreset[TMC2660_REGISTER_COUNT] =
{
    0x00000000,  // 0: UNUSED
    0x00000000,  // 1: UNUSED
    0x00000000,  // 2: UNUSED
    0x00000000,  // 3: UNUSED
    0x00000000,  // 4: UNUSED
    0x00000000,  // 5: UNUSED
    0x00000000,  // 6: UNUSED
    0x00000000,  // 7: UNUSED
    0x00000000,  // 8: DRVCTRL
    0x00000000,  // 9: UNUSED
    0x00000000,  // A: UNUSED
    0x00000000,  // B: UNUSED
    0x00091935,  // C: CHOPCONF
    0x000A0000,  // D: SMARTEN
    0x000D0505,  // E: SGCSCONF
    0x000EF040   // F: DRVCONF
};


extern bool tmc2660_cache(uint16_t icID, TMC2660CacheOp operation, uint8_t address, uint32_t *value);
extern int32_t tmc2660_shadowRegister[TMC2660_IC_CACHE_COUNT][TMC2660_REGISTER_COUNT];

#endif
#endif

/***************************************************************************************************************************************************/

#endif /* TMC_IC_TMC2660_H_ */
