/*
 * TMC5161.h
 *
 *  Created on: 13.06.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC5161_H_
#define TMC_IC_TMC5161_H_

#include "../../helpers/Constants.h"
#include "../../helpers/API_Header.h"
#include "TMC5161_Register.h"
#include "TMC5161_Constants.h"
#include "TMC5161_Fields.h"

// Helper macros
#define TMC5161_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5161_readInt(tdef, address), mask, shift)
#define TMC5161_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc5161_writeInt(tdef, address, FIELD_SET(tmc5161_readInt(tdef, address), mask, shift, value)))

// Factor between 10ms units and internal units for 16MHz
//#define TPOWERDOWN_FACTOR (4.17792*100.0/255.0)
// TPOWERDOWN_FACTOR = k * 100 / 255 where k = 2^18 * 255 / fClk for fClk = 16000000)

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, seperate functions/values for reading or writing
//   0x21: read, flag register (read to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5161_defaultRegisterAccess[TMC5161_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x13, 0x01, 0x02, 0x13, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, ____, ____, ____, // 0x00 - 0x0F
	0x02, 0x02, 0x01, 0x02, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, ____, 0x02, 0x02, 0x02, 0x03, ____, ____, // 0x20 - 0x2F
	____, ____, ____, 0x02, 0x03, 0x13, 0x01, ____, 0x03, 0x03, 0x02, 0x13, 0x01, 0x02, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x01, // 0x60 - 0x6F
	0x42, 0x01, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

// todo ADD API 3: Some Registers have default hardware configuration from OTP, we shouldnt overwrite those - add the weak write register permission and use it here (LH)
// Default Register Values
#define R00 0x00000008  // GCONF
#define R09 0x00010C0C  // SHORT_CONF
#define R0A 0x00080200  // DRV_CONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2B 0x00000001  // VSTOP
#define R3A 0x00010000  // ENC_CONST
#define R6C 0x00410153  // CHOPCONF
#define R70 0xC40C001E  // PWMCONF

static const int32_t tmc5161_defaultRegisterResetState[TMC5161_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   R09, R0A, 0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R2B, 0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

#undef R00
#undef R09
#undef R0A
#undef R10
#undef R11
#undef R2B
#undef R3A
#undef R6C
#undef R70

typedef struct
{
	ConfigurationTypeDef *config;
	int velocity, oldX;
	uint32_t oldTick;
	int32_t registerResetState[TMC5161_REGISTER_COUNT];
	uint8_t registerAccess[TMC5161_REGISTER_COUNT];
} TMC5161TypeDef;

typedef void (*tmc5161_callback)(TMC5161TypeDef*, ConfigState);

void tmc5161_writeDatagram(TMC5161TypeDef *tmc5161, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5161_writeInt(TMC5161TypeDef *tmc5161, uint8_t address, int32_t value);
int32_t tmc5161_readInt(TMC5161TypeDef *tmc5161, uint8_t address);

void tmc5161_init(TMC5161TypeDef *tmc5161, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);

uint8_t tmc5161_reset(TMC5161TypeDef *tmc5161);
uint8_t tmc5161_restore(TMC5161TypeDef *tmc5161);

void tmc5161_setRegisterResetState(TMC5161TypeDef *tmc5161, const int32_t *resetState);
void tmc5161_setCallback(TMC5161TypeDef *tmc5161, tmc5161_callback callback);
void tmc5161_periodicJob(TMC5161TypeDef *tmc5161, uint32_t tick);
void tmc5161_rotate(TMC5161TypeDef *tmc5161, int32_t velocity);
void tmc5161_right(TMC5161TypeDef *tmc5161, uint32_t velocity);
void tmc5161_left(TMC5161TypeDef *tmc5161, uint32_t velocity);
void tmc5161_stop(TMC5161TypeDef *tmc5161);
void tmc5161_moveTo(TMC5161TypeDef *tmc5161, int32_t position, uint32_t velocity);
void tmc5161_moveBy(TMC5161TypeDef *tmc5161, int32_t *ticks, uint32_t velocity);

#endif /* TMC_IC_TMC5161_H_ */
