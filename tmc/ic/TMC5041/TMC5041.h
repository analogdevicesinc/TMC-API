/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5041_H_
#define TMC_IC_TMC5041_H_

#include "tmc/helpers/API_Header.h"
#include "TMC5041_Register.h"
#include "TMC5041_Constants.h"
#include "TMC5041_Fields.h"

#define TMC5041_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5041_readInt(tdef, address), mask, shift)
#define TMC5041_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc5041_writeInt(tdef, address, FIELD_SET(tmc5041_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;

	int32_t velocity[2], oldX[2];
	uint32_t oldTick;

	int32_t registerResetState[TMC5041_REGISTER_COUNT];
	uint8_t registerAccess[TMC5041_REGISTER_COUNT];
	bool vMaxModified[2];
} TMC5041TypeDef;

#define R30 0x00071703  // IHOLD_IRUN (Motor 1)
#define R32 0x00FFFFFF  // VHIGH      (Motor 1)
#define R50 0x00071703  // IHOLD_IRUN (Motor 2)
#define R52 0x00FFFFFF  // VHIGH      (Motor 2)

#define R60 0xAAAAB554  // MSLUT[0]
#define R61 0x4A9554AA  // MSLUT[1]
#define R62 0x24492929  // MSLUT[2]
#define R63 0x10104222  // MSLUT[3]
#define R64 0xFBFFFFFF  // MSLUT[4]
#define R65 0xB5BB777D  // MSLUT[5]
#define R66 0x49295556  // MSLUT[6]
#define R67 0x00404222  // MSLUT[7]
#define R68 0xFFFF8056  // MSLUTSEL
#define R69 0x00F70000  // MSLUTSTART

#define R6C 0x000101D5  // CHOPCONF (Motor 1)
#define R7C 0x000101D5  // CHOPCONF (Motor 2)

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (separate functions/values)
 */
static const uint8_t tmc5041_defaultRegisterAccess[TMC5041_REGISTER_COUNT] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	3, 1, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 00 - 0F
	2, 1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, // 10 - 1F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 0, 0, // 20 - 2F
	2, 2, 2, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 30 - 3F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 0, 0, // 40 - 4F
	2, 2, 2, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 50 - 5F
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 0, 1, // 60 - 6F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 2, 0, 1  // 70 - 7F
};

static const int32_t tmc5041_defaultRegisterResetState[TMC5041_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 00 - 0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 10 - 1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 20 - 2F
	R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 30 - 3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 40 - 4F
	R50, 0,   R52, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 50 - 5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 60 - 6F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R7C, 0,   0,   0  // 70 - 7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R30
#undef R32
#undef R50
#undef R52
#undef R60
#undef R61
#undef R62
#undef R63
#undef R64
#undef R65
#undef R66
#undef R67
#undef R68
#undef R69
#undef R6C
#undef R7C

void tmc5041_writeDatagram(TMC5041TypeDef *tmc5041, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5041_writeInt(TMC5041TypeDef *tmc5041, uint8_t address, int32_t value);
int32_t tmc5041_readInt(TMC5041TypeDef *tmc5041, uint8_t address);

void tmc5041_init(TMC5041TypeDef *tmc5041, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
void tmc5041_periodicJob(TMC5041TypeDef *tmc5041, uint32_t tick);
uint8_t tmc5041_reset(TMC5041TypeDef *tmc5041);
uint8_t tmc5041_restore(TMC5041TypeDef *tmc5041);

#endif /* TMC_IC_TMC5041_H_ */
