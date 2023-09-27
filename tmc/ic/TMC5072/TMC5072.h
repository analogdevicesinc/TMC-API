/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5072_H_
#define TMC_IC_TMC5072_H_

#include "tmc/helpers/API_Header.h"
#include "TMC5072_Register.h"
#include "TMC5072_Constants.h"
#include "TMC5072_Fields.h"

// Helper macros
#define TMC5072_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5072_readInt(tdef, address), mask, shift)
#define TMC5072_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc5072_writeInt(tdef, address, FIELD_SET(tmc5072_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;
	int32_t oldX[TMC5072_MOTORS];
	uint32_t velocity[TMC5072_MOTORS];
	uint32_t oldTick;
	int32_t registerResetState[TMC5072_REGISTER_COUNT];
	uint8_t registerAccess[TMC5072_REGISTER_COUNT];
} TMC5072TypeDef;

typedef void (*tmc5072_callback)(TMC5072TypeDef*, ConfigState);

// Default Register Values
#define R30 0x00071703  // IHOLD_IRUN (Motor 1)
#define R32 0x00FFFFFF  // VHIGH      (Motor 1)
#define R3A 0x00010000  // ENC_CONST  (Motor 1)
#define R50 0x00071703  // IHOLD_IRUN (Motor 1)
#define R52 0x00FFFFFF  // VHIGH      (Motor 1)
#define R5A 0x00010000  // ENC_CONST  (Motor 1)
#define R6C 0x000101D5  // CHOPCONF (Motor 1)
#define R7C 0x000101D5  // CHOPCONF (Motor 2)

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5072_defaultRegisterAccess[TMC5072_REGISTER_COUNT] = {
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x01, 0x01, 0x02, 0x13, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x01, ____, ____, ____, ____, ____, ____, 0x02, 0x01, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
	0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x30 - 0x3F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x40 - 0x4F
	0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x50 - 0x5F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01  // 0x70 - 0x7F
};

static const int32_t tmc5072_defaultRegisterResetState[TMC5072_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	R50, 0,   R52, 0,   0,   0,   0,   0,   0,   0,   R5A, 0,   0,   0,   0,   0, // 0x50 - 0x5F
	N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R7C, 0,   0,   0  // 0x70 - 0x7F
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

static const TMCRegisterConstant tmc5072_RegisterConstants[] =
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
		{ 0x69, 0x00F70000 }  // MSLUTSTART
};

void tmc5072_writeDatagram(TMC5072TypeDef *tmc5072, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5072_writeInt(TMC5072TypeDef *tmc5072, uint8_t address, int32_t value);
int32_t tmc5072_readInt(TMC5072TypeDef *tmc5072, uint8_t address);

void tmc5072_init(TMC5072TypeDef *tmc5072, uint8_t channel, ConfigurationTypeDef *tmc5072_config, const int32_t *registerResetState);
void tmc5072_fillShadowRegisters(TMC5072TypeDef *tmc5072); // For constant registers with hardware preset we cant determine actual value
uint8_t tmc5072_reset(TMC5072TypeDef *tmc5072);
uint8_t tmc5072_restore(TMC5072TypeDef *tmc5072);
void tmc5072_setRegisterResetState(TMC5072TypeDef *tmc5072, const int32_t *resetState);
void tmc5072_setCallback(TMC5072TypeDef *tmc5072, tmc5072_callback callback);
void tmc5072_periodicJob(TMC5072TypeDef *tmc5072, uint32_t tick);

void tmc5072_rotate(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity);
void tmc5072_right(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity);
void tmc5072_left(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity);
void tmc5072_stop(TMC5072TypeDef *tmc5072, uint8_t motor);
void tmc5072_moveTo(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t position, uint32_t velocityMax);
void tmc5072_moveBy(TMC5072TypeDef *tmc5072, uint8_t motor, uint32_t velocityMax, int32_t *ticks);

#endif /* TMC_IC_TMC5072_H_ */
