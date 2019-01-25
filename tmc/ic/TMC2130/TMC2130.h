/*
* TMC2130.h
*
*  Created on: 26.01.2017
*      Author: BS / ED
*/

#ifndef TMC_IC_TMC2130_H_
#define TMC_IC_TMC2130_H_

#include "../../helpers/API_Header.h"
#include "TMC2130_Register.h"
#include "TMC2130_Mask_Shift.h"

#define TMC2130_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC2130_MOTORS           1
#define TMC2130_WRITE_BIT        TMC_WRITE_BIT
#define TMC2130_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC2130_MAX_VELOCITY     s32_MAX
#define TMC2130_MAX_ACCELERATION u24_MAX

// Helper macros
#define TMC2130_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2130_readInt(tdef, address), mask, shift)
#define TMC2130_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc2130_writeInt(tdef, address, FIELD_SET(tmc2130_readInt(tdef, address), mask, shift, value)))

typedef struct
{
	ConfigurationTypeDef *config;
	int32 registerResetState[TMC2130_REGISTER_COUNT];
	uint8 registerAccess[TMC2130_REGISTER_COUNT];
} TMC2130TypeDef;

typedef void (*tmc2130_callback)(TMC2130TypeDef*, ConfigState);

// Default Register values
#define R10 0x00071703  // IHOLD_IRUN
#define R6C 0x000101D5  // CHOPCONF

// Register access permissions:
// 0x00: none (reserved)
// 0x01: read
// 0x02: write
// 0x03: read/write
// 0x21: read to clear
// 0x42: write, has hardware presets on reset
static const uint8 tmc2130_defaultRegisterAccess[TMC2130_REGISTER_COUNT] = {
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

static const int32 tmc2130_defaultRegisterResetState[TMC2130_REGISTER_COUNT] =
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

void tmc2130_writeDatagram(TMC2130TypeDef *tmc2130, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4);
void tmc2130_writeInt(TMC2130TypeDef *tmc2130, uint8 address, int32 value);
int32 tmc2130_readInt(TMC2130TypeDef *tmc2130, uint8 address);

void tmc2130_init(TMC2130TypeDef *tmc2130, uint8 channel, ConfigurationTypeDef *config, const int32 *registerResetState);
uint8 tmc2130_reset(TMC2130TypeDef *tmc2130);
uint8 tmc2130_restore(TMC2130TypeDef *tmc2130);
void tmc2130_setRegisterResetState(TMC2130TypeDef *tmc2130, const int32 *resetState);
void tmc2130_setCallback(TMC2130TypeDef *tmc2130, tmc2130_callback callback);
void tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32 tick);

#endif /* TMC_IC_TMC2130_H_ */
