/*
 * TMC2041.h
 *
 *  Created on: 14.08.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC5072_H_
#define TMC_IC_TMC5072_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2041_Register.h"
#include "TMC2041_Constants.h"
#include "TMC2041_Fields.h"

// Helper macros
#define TMC2041_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2041_readInt(tdef, address), mask, shift)
#define TMC2041_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc2041_writeInt(tdef, address, FIELD_SET(tmc2041_readInt(tdef, address), mask, shift, value)))

typedef struct
{
	ConfigurationTypeDef *config;
	int32_t registerResetState[TMC2041_REGISTER_COUNT];
	uint8_t registerAccess[TMC2041_REGISTER_COUNT];
} TMC2041TypeDef;

typedef void (*tmc2041_callback)(TMC2041TypeDef*, ConfigState);

// Default Register values
#define R00 0x00000006  // GCONF

#define R30 0x00071703  // IHOLD_IRUN (Motor 1)
#define R50 0x00071703  // IHOLD_IRUN (Motor 2)

#define R6C 0x000101D5  // CHOPCONF   (Motor 1)
#define R7C 0x000101D5  // CHOPCONF   (Motor 2)

// Register access permissions:
// 0x00: none (reserved)
// 0x01: read
// 0x02: write
// 0x03: read/write
// 0x13: read/write, separate functions/values for reading or writing
// 0x21: read to clear
static const uint8_t tmc2041_defaultRegisterAccess[TMC2041_REGISTER_COUNT] = {
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x21, 0x01, 0x02, 0x13, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
	0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, 0x02, ____, 0x01, // 0x60 - 0x6F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, 0x02, ____, 0x01  // 0x70 - 0x7F
};

static const int32_t tmc2041_defaultRegisterResetState[TMC2041_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	R30, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	R50, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R7C, 0,   0,   0  // 0x70 - 0x7F
};

void tmc2041_writeDatagram(TMC2041TypeDef *tmc2041, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc2041_writeInt(TMC2041TypeDef *tmc2041, uint8_t address, int32_t value);
int32_t tmc2041_readInt(TMC2041TypeDef *tmc2041, uint8_t address);

void tmc2041_init(TMC2041TypeDef *tmc2041, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
uint8_t tmc2041_reset(TMC2041TypeDef *tmc2041);
uint8_t tmc2041_restore(TMC2041TypeDef *tmc2041);
void tmc2041_setRegisterResetState(TMC2041TypeDef *tmc2041, const int32_t *resetState);
void tmc2041_setCallback(TMC2041TypeDef *tmc2041, tmc2041_callback callback);
void tmc2041_periodicJob(TMC2041TypeDef *tmc2041, uint32_t tick);

#endif /* TMC_IC_TMC5072_H_ */
