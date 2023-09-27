/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5240_H_
#define TMC_IC_TMC5240_H_

#include "tmc/helpers/API_Header.h"
#include "tmc/helpers/Constants.h"
#include "../TMC5240/TMC5240_Register.h"
#include "TMC5240_Constants.h"
#include "../TMC5240/TMC5240_Fields.h"

// Helper macros
#define TMC5240_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5240_readInt(tdef, address), mask, shift)
#define TMC5240_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc5240_writeInt(tdef, address, FIELD_SET(tmc5240_readInt(tdef, address), mask, shift, value)))

// Factor between 10ms units and internal units for 16MHz
//#define TPOWERDOWN_FACTOR (4.17792*100.0/255.0)
// TPOWERDOWN_FACTOR = k * 100 / 255 where k = 2^18 * 255 / fClk for fClk = 16000000)

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	int32_t registerResetState[TMC5240_REGISTER_COUNT];
	uint8_t registerAccess[TMC5240_REGISTER_COUNT];
	uint8_t slaveAddress;
} TMC5240TypeDef;

typedef void (*tmc5240_callback)(TMC5240TypeDef*, ConfigState);

// Default Register values
#define R00 0x00000008  // GCONF
#define R0A 0x00000020  // DRVCONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2A 0x0000000A  // D1
#define R2B 0x0000000A  // VSTOP
#define R30 0x0000000A  // D2

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
#define R74 0x00000000  // PWMCONF

static const int32_t tmc5240_defaultRegisterResetState[TMC5240_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R0A,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R2A,   R2B, 0,   0,   0,   0, // 0x20 - 0x2F
	R30,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   R52,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
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
static const uint8_t tmc5240_defaultRegisterAccess[TMC5240_REGISTER_COUNT] =
{
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x03, 0x03, 0x03, 0x03, ____, ____, ____, 0x03, 0x03, ____, ____, ____, ____, // 0x00 - 0x0F
	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x20 - 0x2F
	0x03, 0x01, ____, 0x03, 0x03, 0x23, 0x01, ____, 0x03, 0x03, 0x03, 0x23, 0x01, 0x03, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMCRegisterConstant tmc5240_RegisterConstants[] =
{		// Use ascending addresses!
		///
};

//void tmc5240_writeDatagram(TMC5240TypeDef *tmc5240, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5240_writeInt(TMC5240TypeDef *tmc5240, uint8_t address, int32_t value);
int32_t tmc5240_readInt(TMC5240TypeDef *tmc5240, uint8_t address);

void tmc5240_init(TMC5240TypeDef *tmc5240, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
//void tmc5240_fillShadowRegisters(TMC5240TypeDef *tmc5240);
uint8_t tmc5240_reset(TMC5240TypeDef *tmc5240);
uint8_t tmc5240_restore(TMC5240TypeDef *tmc5240);
uint8_t tmc5240_getSlaveAddress(TMC5240TypeDef *tmc5240);
void tmc5240_setSlaveAddress(TMC5240TypeDef *tmc5240, uint8_t slaveAddress);
void tmc5240_setRegisterResetState(TMC5240TypeDef *tmc5240, const int32_t *resetState);
void tmc5240_setCallback(TMC5240TypeDef *tmc5240, tmc5240_callback callback);
void tmc5240_periodicJob(TMC5240TypeDef *tmc5240, uint32_t tick);

void tmc5240_rotate(TMC5240TypeDef *tmc5240, int32_t velocity);
void tmc5240_right(TMC5240TypeDef *tmc5240, uint32_t velocity);
void tmc5240_left(TMC5240TypeDef *tmc5240, uint32_t velocity);
void tmc5240_stop(TMC5240TypeDef *tmc5240);
void tmc5240_moveTo(TMC5240TypeDef *tmc5240, int32_t position, uint32_t velocityMax);
void tmc5240_moveBy(TMC5240TypeDef *tmc5240, int32_t *ticks, uint32_t velocityMax);

#endif /* TMC_IC_TMC5240_H_ */
