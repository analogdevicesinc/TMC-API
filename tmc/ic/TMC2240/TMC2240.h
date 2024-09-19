/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2240_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tmc/helpers/API_Header.h"
#include "TMC2240_HW_Abstraction.h"


// Typedefs
typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
    IC_BUS_WLAN,
} TMC2240BusType;

// => TMC-API wrapper
extern void tmc2240_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc2240_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC2240BusType tmc2240_getBusType(uint16_t icID);
extern uint8_t tmc2240_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc2240_readRegister(uint16_t icID, uint8_t address);
void tmc2240_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	int32_t registerResetState[TMC2240_REGISTER_COUNT];
	uint8_t registerAccess[TMC2240_REGISTER_COUNT];
	uint8_t slaveAddress;
} TMC2240TypeDef;

typedef void (*tmc2240_callback)(TMC2240TypeDef*, ConfigState);
static inline uint32_t tmc2240_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc2240_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2240_readRegister(icID, field.address);

    return tmc2240_fieldExtract(value, field);
}

static inline uint32_t tmc2240_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2240_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2240_readRegister(icID, field.address);

    regValue = tmc2240_fieldUpdate(regValue, field, value);

    tmc2240_writeRegister(icID, field.address, regValue);
}

// Default Register values
#define R00 0x00002108  // GCONF
#define R0A 0x00000020  // DRVCONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2B 0x00000001  // VSTOP
#define R3A 0x00010000  // ENC_CONST

#define R52 0x0B920F25  // OTW_OV_VTH
#define R60 0xAAAAB554  // MSLUT[0]
#define R61 0x4A9554AA  // MSLUT[1]
#define R62 0x24492929  // MSLUT[2]
#define R63 0x10104222  // MSLUT[3]
#define R64 0xFBFFFFFF  // MSLUT[4]
#define R65 0xB5BB777D  // MSLUT[5]
#define R66 0x49295556  // MSLUT[6]
#define R67 0x00404222  // MSLUT[7]
#define R68 0xFFFF8056  // MSLUT[8]
#define R69 0x00F70000  // MSLUT[9]

#define R6C 0x00410153  // CHOPCONF
#define R70 0xC44C001E  // PWMCONF

static const int32_t tmc2240_defaultRegisterResetState[TMC2240_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R0A, 0,   0,   0,   0,   0, // 0x00 - 0x0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   R52, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
};

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc2240_defaultRegisterAccess[TMC2240_REGISTER_COUNT] =
{
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x03, 0x03, ____, ____, ____, ____, ____, 0x03, 0x03, ____, ____, ____, ____, // 0x00 - 0x0F
	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x03, ____, ____, // 0x20 - 0x2F
	____, ____, ____, ____, ____, ____, ____, ____, 0x03, 0x03, 0x03, 0x23, 0x01, ____, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, ____, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMCRegisterConstant tmc2240_RegisterConstants[] =
{		// Use ascending addresses!
		///
};

void tmc2240_init(TMC2240TypeDef *tmc2240, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
//void tmc2240_fillShadowRegisters(TMC2240TypeDef *tmc2240);
uint8_t tmc2240_reset(TMC2240TypeDef *tmc2240);
uint8_t tmc2240_restore(TMC2240TypeDef *tmc2240);
uint8_t tmc2240_getSlaveAddress(TMC2240TypeDef *tmc2240);
void tmc2240_setSlaveAddress(TMC2240TypeDef *tmc2240, uint8_t slaveAddress);
void tmc2240_setRegisterResetState(TMC2240TypeDef *tmc2240, const int32_t *resetState);
void tmc2240_setCallback(TMC2240TypeDef *tmc2240, tmc2240_callback callback);
void tmc2240_periodicJob(TMC2240TypeDef *tmc2240, uint32_t tick);

uint8_t tmc2240_consistencyCheck(TMC2240TypeDef *tmc2240);

#endif /* TMC_IC_TMC2240_H_ */
