/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2300_H_
#define TMC_IC_TMC2300_H_

#include "tmc/helpers/Constants.h"
#include "tmc/helpers/API_Header.h"
#include "TMC2300_Constants.h"
#include "TMC2300_Register.h"
#include "TMC2300_Fields.h"

// Helper macros
#define TMC2300_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2300_readInt(tdef, address), mask, shift)
#define TMC2300_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc2300_writeInt(tdef, address, FIELD_SET(tmc2300_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;

	int32_t registerResetState[TMC2300_REGISTER_COUNT];
	uint8_t registerAccess[TMC2300_REGISTER_COUNT];

	uint8_t slaveAddress;
	uint8_t standbyEnabled;
} TMC2300TypeDef;

typedef void (*tmc2300_callback)(TMC2300TypeDef*, ConfigState);

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
//   0x43: read/write, has hardware presets on reset
static const uint8_t tmc2300_defaultRegisterAccess[TMC2300_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x43, 0x23, 0x01, 0x02, ____, ____, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	0x42, 0x42, 0x01, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, ____, 0x43, ____, ____, 0x01, // 0x60 - 0x6F
	0x43, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

void writeConfiguration(TMC2300TypeDef *tmc2300);
static const int32_t tmc2300_defaultRegisterResetState[TMC2300_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	N_A, N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   N_A, 0,   0,   0, // 0x60 - 0x6F
	N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// Register constants. These are required for 0x42 registers, since we do not have
// any way to find out the content. For 0x43 registers, it is not necessary to
// load the constant values this way, but this allows users to directly see the
// contents while still in standby.
static const TMCRegisterConstant tmc2300_RegisterConstants[] =
{		// Use ascending addresses!
		{ 0x00, 0x00000040 }, // GCONF
		{ 0x10, 0x00011F08 }, // IHOLD_IRUN
		{ 0x11, 0x00000014 }, // TPOWERDOWN
		{ 0x6C, 0x13008001 }, // CHOPCONF
		{ 0x70, 0xC40D1024 }, // PWMCONF
};


void tmc2300_writeInt(TMC2300TypeDef *tmc2300, uint8_t address, int32_t value);
int32_t tmc2300_readInt(TMC2300TypeDef *tmc2300, uint8_t address);

void tmc2300_init(TMC2300TypeDef *tmc2300, uint8_t channel, ConfigurationTypeDef *tmc2300_config, const int32_t *registerResetState);
uint8_t tmc2300_reset(TMC2300TypeDef *tmc2300);
uint8_t tmc2300_restore(TMC2300TypeDef *tmc2300);
void tmc2300_setRegisterResetState(TMC2300TypeDef *tmc2300, const int32_t *resetState);
void tmc2300_setCallback(TMC2300TypeDef *tmc2300, tmc2300_callback callback);
void tmc2300_periodicJob(TMC2300TypeDef *tmc2300, uint32_t tick);

uint8_t tmc2300_getSlaveAddress(TMC2300TypeDef *tmc2300);
void tmc2300_setSlaveAddress(TMC2300TypeDef *tmc2300, uint8_t slaveAddress);

uint8_t tmc2300_getStandby(TMC2300TypeDef *tmc2300);
void tmc2300_setStandby(TMC2300TypeDef *tmc2300, uint8_t standbyState);

#endif /* TMC_IC_TMC2300_H_ */
