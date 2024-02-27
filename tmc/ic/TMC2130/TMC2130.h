/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2130_H_
#define TMC_IC_TMC2130_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2130_Register.h"
#include "TMC2130_Constants.h"
#include "TMC2130_Mask_Shift.h"

// Helper macros
#define TMC2130_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2130_readInt(tdef, address), mask, shift)
#define TMC2130_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc2130_writeInt(tdef, address, FIELD_SET(tmc2130_readInt(tdef, address), mask, shift, value)))

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t registerResetState[TMC2130_REGISTER_COUNT];
	uint8_t registerAccess[TMC2130_REGISTER_COUNT];
} TMC2130TypeDef;

typedef void (*tmc2130_callback)(TMC2130TypeDef*, ConfigState);

// Default Register values
#define R10 0x00071703  // IHOLD_IRUN
#define R6C 0x000101D5  // CHOPCONF

static const int32_t tmc2130_defaultRegisterResetState[TMC2130_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R10
#undef R6C

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc2130_defaultRegisterAccess[TMC2130_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x21, ____, ____, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x02, 0x01, 0x02, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x03, ____, ____, // 0x20 - 0x2F
	____, ____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
	0x42, 0x01, 0x02, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMCRegisterConstant tmc2130_RegisterConstants[] =
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

#undef R10
#undef R6C

#ifdef __cplusplus
extern "C" {
#endif

// API Functions
// All functions act on one IC identified by the TMC2130TypeDef pointer

void tmc2130_writeDatagram(TMC2130TypeDef *tmc2130, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc2130_writeInt(TMC2130TypeDef *tmc2130, uint8_t address, int32_t value);
int32_t tmc2130_readInt(TMC2130TypeDef *tmc2130, uint8_t address);

void tmc2130_init(TMC2130TypeDef *tmc2130, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
void tmc2130_fillShadowRegisters(TMC2130TypeDef *tmc2130);
uint8_t tmc2130_reset(TMC2130TypeDef *tmc2130);
uint8_t tmc2130_restore(TMC2130TypeDef *tmc2130);
void tmc2130_setRegisterResetState(TMC2130TypeDef *tmc2130, const int32_t *resetState);
void tmc2130_setCallback(TMC2130TypeDef *tmc2130, tmc2130_callback callback);
void tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32_t tick);

#ifdef __cplusplus
}
#endif

#endif /* TMC_IC_TMC2130_H_ */
