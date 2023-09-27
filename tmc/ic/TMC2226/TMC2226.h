/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2226_H_
#define TMC_IC_TMC2226_H_

#include "tmc/helpers/Constants.h"
#include "tmc/helpers/API_Header.h"
#include "TMC2226_Register.h"
#include "TMC2226_Constants.h"
#include "TMC2226_Fields.h"

// Helper macros
#define TMC2226_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2226_readInt(tdef, address), mask, shift)
#define TMC2226_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc2226_writeInt(tdef, address, FIELD_SET(tmc2226_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;

	int32_t registerResetState[TMC2226_REGISTER_COUNT];
	uint8_t registerAccess[TMC2226_REGISTER_COUNT];

	uint8_t slaveAddress;
} TMC2226TypeDef;

typedef void (*tmc2226_callback)(TMC2226TypeDef*, ConfigState);

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
static const uint8_t tmc2226_defaultRegisterAccess[TMC2226_REGISTER_COUNT] =
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

static const int32_t tmc2226_defaultRegisterResetState[TMC2226_REGISTER_COUNT] =
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
static const TMCRegisterConstant tmc2226_RegisterConstants[] =
{		// Use ascending addresses!
		{ 0x11, 0x00000014 }, // TPOWERDOWN
};

#undef R00
#undef R10
#undef R6C
#undef R70

// Communication
void tmc2226_writeInt(TMC2226TypeDef *tmc2226, uint8_t address, int32_t value);
int32_t tmc2226_readInt(TMC2226TypeDef *tmc2226, uint8_t address);

void tmc2226_init(TMC2226TypeDef *tmc2226, uint8_t channel, uint8_t slaveAddress, ConfigurationTypeDef *tmc2226_config, const int32_t *registerResetState);
uint8_t tmc2226_reset(TMC2226TypeDef *tmc2226);
uint8_t tmc2226_restore(TMC2226TypeDef *tmc2226);
void tmc2226_setRegisterResetState(TMC2226TypeDef *tmc2226, const int32_t *resetState);
void tmc2226_setCallback(TMC2226TypeDef *tmc2226, tmc2226_callback callback);
void tmc2226_periodicJob(TMC2226TypeDef *tmc2226, uint32_t tick);

uint8_t tmc2226_getSlaveAddress(TMC2226TypeDef *tmc2226);
void tmc2226_setSlaveAddress(TMC2226TypeDef *tmc2226, uint8_t slaveAddress);

#endif /* TMC_IC_TMC2226_H_ */
