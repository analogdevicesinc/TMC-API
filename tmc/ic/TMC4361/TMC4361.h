/*
 * TMC4361.h
 *
 *  Created on: 18.07.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC4361_H_
#define TMC_IC_TMC4361_H_

#include "tmc/helpers/API_Header.h"
#include "TMC4361_Register.h"
#include "TMC4361_Constants.h"
#include "TMC4361_Fields.h"

// Helper macros
#define TMC4361_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc4361_readInt(tdef, address), mask, shift)
#define TMC4361_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc4361_writeInt(tdef, address, FIELD_SET(tmc4361_readInt(tdef, address), mask, shift, value)))

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int velocity;
	int oldX;
	uint32_t oldTick;
	int32_t registerResetState[TMC4361_REGISTER_COUNT];
	uint8_t registerAccess[TMC4361_REGISTER_COUNT];
	//TMotorConfig motorConfig;
	//TClosedLoopConfig closedLoopConfig;
	uint8_t status;
	bool cover_hold;
} TMC4361TypeDef;

typedef void (*tmc4361_callback)(TMC4361TypeDef*, ConfigState);

// Default Register Values
#define R10 0x00040001  // STP_LENGTH_ADD
#define R20 0x00000001  // RAMPMODE

static const int32_t tmc4361_defaultRegisterResetState[TMC4361_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	N_A, 0,   0,   0,   0,   0,   N_A, N_A, 0,   0,   N_A, N_A, 0,   0,   0,   0,   // 0x00 - 0x0F
	R10, 0,   N_A, 0,   0,   0,   0,   N_A, 0,   0,   0,   0,   N_A, 0,   0,   N_A, // 0x10 - 0x1F
	R20, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x20 - 0x2F
	0,   N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x40 - 0x4F
	0,   0,   0,   N_A, 0,   0,   N_A, N_A, N_A, 0,   0,   0,   0,   0,   0,   0,   // 0x50 - 0x5F
	0,   0,   N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 0x60 - 0x6F
	N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, N_A, 0,   0,   N_A, N_A, 0,   N_A, 0    // 0x70 - 0x7F
};

#undef R10
#undef R20

// Register access permissions:
//     0x00: none (reserved)
//     0x01: read
//     0x02: write
//     0x03: read/write
//     0x13: read/write, separate functions/values for reading or writing
//     0x42: write, has hardware presets on reset
//     0x43: read/write, has hardware presets on reset
//     0x53: read/write, has hardware presets on reset, separate functions/values for reading or writing
static const uint8_t tmc4361_defaultRegisterAccess[TMC4361_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x43, 0x03, 0x03, 0x03, 0x03, 0x03, 0x43, 0x43, 0x03, 0x03, 0x43, 0x43, 0x03, 0x03, 0x13, 0x01, // 0x00 - 0x0F
	0x03, 0x03, 0x43, 0x03, 0x03, 0x03, 0x03, 0x43, 0x03, 0x03, 0x03, 0x03, 0x43, 0x03, 0x03, 0x43, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x20 - 0x2F
	0x03, 0x43, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x30 - 0x3F
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x40 - 0x4F
	0x03, 0x13, 0x13, 0x42, 0x13, 0x02, 0x42, 0x42, 0x42, 0x03, 0x13, 0x13, 0x02, 0x13, 0x02, 0x02, // 0x50 - 0x5F
	0x02, 0x02, 0x42, 0x02, ____, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, // 0x60 - 0x6F
	0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x01, 0x01, 0x53, 0x53, 0x02, 0x42, 0x01  // 0x70 - 0x7F
};


// API Functions
// All functions act on one IC given by the TMC4361TypeDef struct

// SPI Communication
void tmc4361_writeDatagram(TMC4361TypeDef *tmc4361, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc4361_writeInt(TMC4361TypeDef *tmc4361, uint8_t address, int32_t value);
int32_t tmc4361_readInt(TMC4361TypeDef *tmc4361, uint8_t address);
void tmc4361_readWriteCover(TMC4361TypeDef *tmc4361, uint8_t *data, size_t length);

// Configuration
void tmc4361_init(TMC4361TypeDef *tmc4361, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState);
uint8_t tmc4361_reset(TMC4361TypeDef *tmc4361);
uint8_t tmc4361_restore(TMC4361TypeDef *tmc4361);
void tmc4361_setRegisterResetState(TMC4361TypeDef *tmc4361, const int32_t *resetState);
void tmc4361_setCallback(TMC4361TypeDef *tmc4361, tmc4361_callback callback);
void tmc4361_periodicJob(TMC4361TypeDef *tmc4361, uint32_t tick);

// Motion
void tmc4361_rotate(TMC4361TypeDef *tmc4361, int32_t velocity);
void tmc4361_right(TMC4361TypeDef *tmc4361, int32_t velocity);
void tmc4361_left(TMC4361TypeDef *tmc4361, int32_t velocity);
void tmc4361_stop(TMC4361TypeDef *tmc4361);
void tmc4361_moveTo(TMC4361TypeDef *tmc4361, int32_t position, uint32_t velocityMax);
void tmc4361_moveBy(TMC4361TypeDef *tmc4361, int32_t *ticks, uint32_t velocityMax);

// Helper functions
int32_t tmc4361_discardVelocityDecimals(int32_t value);
uint8_t tmc4361_calibrateClosedLoop(TMC4361TypeDef *tmc4361, uint8_t worker0master1);

#endif /* TMC_IC_TMC4361_H_ */
