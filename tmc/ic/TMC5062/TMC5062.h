/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5062_H_
#define TMC_IC_TMC5062_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5062_HW_Abstraction.h"
#include "tmc/helpers/API_Header.h"

// Amount of CRC tables available
// Each table takes ~260 bytes (257 bytes, one bool and structure padding)
#define CRC_TABLE_COUNT 2

typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
} TMC5062BusType;

#define TMC5062_CACHE  1
#define TMC5062_ENABLE_TMC_CACHE

// By default, support one IC in the cache
#ifndef TMC5062_IC_CACHE_COUNT
#define TMC5062_IC_CACHE_COUNT 1
#endif

#ifdef TMC5062_ENABLE_TMC_CACHE
typedef enum {
   TMC5062_CACHE_READ,
   TMC5062_CACHE_WRITE
} TMC5062CacheOp;

typedef struct
{
    uint8_t address;
    uint32_t value;
} TMCRegisterConstants;

#define TMC5062_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC5062_ACCESS_READ        0x01
#define TMC_ACCESS_W_PRESET        0x42
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
static const uint8_t tmc5062_defaultRegisterAccess[TMC5062_REGISTER_COUNT] = {
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

static const TMCRegisterConstants tmc5062_RegisterConstants[] =
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

extern uint8_t tmc5062_registerAccess[TMC5062_IC_CACHE_COUNT][TMC5062_REGISTER_COUNT];
extern int32_t tmc5062_shadowRegister[TMC5062_IC_CACHE_COUNT][TMC5062_REGISTER_COUNT];
extern bool tmc5062_cache(uint16_t icID, TMC5062CacheOp operation, uint8_t address, uint32_t *value);
#endif
// => TMC-API wrapper
extern void tmc5062_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5062_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5062BusType tmc5062_getBusType(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5062_readRegister(uint16_t icID, uint8_t address);
void tmc5062_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5062_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

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

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

// Usage note: use one TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;
	uint8_t motors[TMC5062_MOTORS];

	// External frequency supplied to the IC (or 16MHz for internal frequency)
	uint32_t chipFrequency;

	// Velocity estimation (for dcStep)
	uint32_t measurementInterval;
	uint32_t oldTick;
	int32_t oldXActual[TMC5062_MOTORS];
	int32_t velocity[TMC5062_MOTORS];

	int32_t registerResetState[TMC5062_REGISTER_COUNT];
	uint8_t registerAccess[TMC5062_REGISTER_COUNT];
} TMC5062TypeDef;

extern TMC5062TypeDef TMC5062;

typedef void (*tmc5062_callback)(TMC5062TypeDef*, ConfigState);



void tmc5062_init(TMC5062TypeDef *tmc5062, ConfigurationTypeDef *tmc5062_config, const int32_t *registerResetState, uint8_t motorIndex0, uint8_t motorIndex1, uint32_t chipFrequency);
void tmc5062_fillShadowRegisters(TMC5062TypeDef *tmc5062);
void tmc5062_setRegisterResetState(TMC5062TypeDef *tmc5062, const int32_t *resetState);
void tmc5062_setCallback(TMC5062TypeDef *tmc5062, tmc5062_callback callback);
void tmc5062_periodicJob(TMC5062TypeDef *tmc5072, uint32_t tick);
uint8_t tmc5062_reset(TMC5062TypeDef *tmc5062);
uint8_t tmc5062_restore(TMC5062TypeDef *tmc5062);

void tmc5062_rotate(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity);
void tmc5062_right(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity);
void tmc5062_left(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity);
void tmc5062_stop(TMC5062TypeDef *tmc5062, uint8_t motor);
void tmc5062_moveTo(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t position, uint32_t velocityMax);
void tmc5062_moveBy(TMC5062TypeDef *tmc5062, uint8_t motor, uint32_t velocityMax, int32_t *ticks);

// Chopper settings
uint8_t calculateTOFF(uint32_t chopFreq, uint32_t clkFreq);
// Diagnostics

// Stallguard
// Coolstep
// dcStep
uint8_t dcStepActive(TMC5062TypeDef *tmc5062, uint8_t motor);
// MSLUT
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

uint8_t setMicroStepTable(TMC5062TypeDef *tmc5062, uint8_t motor, TMC5062_MicroStepTable *table);

// Encoder
uint32_t setEncoderFactor(TMC5062TypeDef *tmc5062, uint8_t motor, uint32_t motorFullSteps, uint32_t microSteps, uint32_t encoderResolution);

#endif /* TMC_IC_TMC5062_H_ */
