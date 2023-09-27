/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2208_H_
#define TMC_IC_TMC2208_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2208_Register.h"
#include "TMC2208_Constants.h"

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;
	int32_t registerResetState[TMC2208_REGISTER_COUNT];
	uint8_t registerAccess[TMC2208_REGISTER_COUNT];
} TMC2208TypeDef;

typedef void (*tmc2208_callback)(TMC2208TypeDef*, ConfigState);

// Default Register values
#define R00 0x00000041  // GCONF
#define R10 0x00071703  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC10D0024  // PWMCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc2208_defaultRegisterAccess[TMC2208_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x02, 0x02, 0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, ____, ____, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2208_defaultRegisterResetState[TMC2208_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
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
#undef R11
#undef R6C
#undef R70

void tmc2208_writeInt(TMC2208TypeDef *tmc2208, uint8_t address, int32_t value);
int32_t tmc2208_readInt(TMC2208TypeDef *tmc2208, uint8_t address);

void tmc2208_init(TMC2208TypeDef *tmc2208, uint8_t channel, ConfigurationTypeDef *tmc2208_config, const int32_t *registerResetState);
uint8_t tmc2208_reset(TMC2208TypeDef *tmc2208);
uint8_t tmc2208_restore(TMC2208TypeDef *tmc2208);
void tmc2208_setRegisterResetState(TMC2208TypeDef *tmc2208, const int32_t *resetState);
void tmc2208_setCallback(TMC2208TypeDef *tmc2208, tmc2208_callback callback);
void tmc2208_periodicJob(TMC2208TypeDef *tmc2208, uint32_t tick);

uint8_t tmc2208_get_slave(TMC2208TypeDef *tmc2208);
void tmc2208_set_slave(TMC2208TypeDef *tmc2208, uint8_t slave);

#endif /* TMC_IC_TMC2208_H_ */
