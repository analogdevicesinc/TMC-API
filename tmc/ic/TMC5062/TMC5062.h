/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5062_H_
#define TMC_IC_TMC5062_H_

#include "tmc/helpers/API_Header.h"
#include "TMC5062_Register.h"
#include "TMC5062_Constants.h"
#include "TMC5062_Fields.h"

#define TMC5062_FIELD_READ(tmc5062_ptr, channel, address, mask, shift) \
	FIELD_GET(tmc5062_readInt(tmc5062_ptr, channel, address), (mask), (shift))

#define TMC5062_FIELD_WRITE(tmc5062_ptr, channel, address, mask, shift, value) \
	tmc5062_writeInt((tmc5062_ptr), (channel), (address), FIELD_SET(tmc5062_readInt((tmc5062_ptr), (channel), (address)), (mask), (shift), (value)))

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

typedef void (*tmc5062_callback)(TMC5062TypeDef*, ConfigState);

// Default Register Values
#define R30 0x00071703  // IHOLD_IRUN
#define R32 0x00FFFFFF  // VHIGH
#define R3A 0x00010000  // ENC_CONST
#define R50 R30
#define R52 R32
#define R5A R3A
#define R6C 0x000101D5  // CHOPCONF
#define R7C R6C

static const int32_t tmc5062_defaultRegisterResetState[TMC5062_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
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

static const uint8_t tmc5062_defaultRegisterAccess[TMC5062_REGISTER_COUNT] = {
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x01, 0x01, 0x02, 0x07, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x01, ____, ____, ____, ____, ____, ____, 0x02, 0x01, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
	0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x30 - 0x3F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x40 - 0x4F
	0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x01, ____, 0x03, 0x03, 0x02, 0x01, 0x01, ____, ____, ____, // 0x50 - 0x5F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01  // 0x70 - 0x7F
};

static const TMCRegisterConstant tmc5062_RegisterConstants[] =
{		// Use ascending addresses!
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

void tmc5062_writeInt(TMC5062TypeDef *tmc5062, uint8_t channel, uint8_t address, int32_t value);
int32_t tmc5062_readInt(TMC5062TypeDef *tmc5062, uint8_t channel, uint8_t address);

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
uint8_t dcStepActive(TMC5062TypeDef *tmc5062, uint8_t channel);
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

uint8_t setMicroStepTable(TMC5062TypeDef *tmc5062, uint8_t channel, TMC5062_MicroStepTable *table);

// Encoder
uint32_t setEncoderFactor(TMC5062TypeDef *tmc5062, uint8_t channel, uint32_t motorFullSteps, uint32_t microSteps, uint32_t encoderResolution);

#endif /* TMC_IC_TMC5062_H_ */
