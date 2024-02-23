/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5262_H_
#define TMC_IC_TMC5262_H_

#include "tmc/helpers/API_Header.h"
#include "tmc/helpers/Constants.h"
#include "TMC5262_Constants.h"
#include "TMC5262_fields.h"
#include "TMC5262_registers.h"

// Helper macros
#define TMC5262_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5262_readInt(tdef, address), mask, shift)
#define TMC5262_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc5262_writeInt(tdef, address, FIELD_SET(tmc5262_readInt(tdef, address), mask, shift, value)))

// Factor between 10ms units and internal units for 16MHz
//#define TPOWERDOWN_FACTOR (4.17792*100.0/255.0)
// TPOWERDOWN_FACTOR = k * 100 / 255 where k = 2^18 * 255 / fClk for fClk = 16000000)

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	uint8_t slaveAddress;
} TMC5262TypeDef;

// Default Register values
#define R0B 0x65FF  // PLL

void tmc5262_writeDatagram(TMC5262TypeDef *tmc5262, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5262_writeInt(TMC5262TypeDef *tmc5262, uint8_t address, int32_t value);
int32_t tmc5262_readInt(TMC5262TypeDef *tmc5262, uint8_t address);

void tmc5262_init(TMC5262TypeDef *tmc5262, uint8_t channel, ConfigurationTypeDef *config);
//void tmc5262_fillShadowRegisters(TMC5262TypeDef *tmc5262);
uint8_t tmc5262_reset(TMC5262TypeDef *tmc5262);
uint8_t tmc5262_restore(TMC5262TypeDef *tmc5262);
uint8_t tmc5262_getSlaveAddress(TMC5262TypeDef *tmc5262);
void tmc5262_setSlaveAddress(TMC5262TypeDef *tmc5262, uint8_t slaveAddress);
void tmc5262_periodicJob(TMC5262TypeDef *tmc5262, uint32_t tick);

void tmc5262_rotate(TMC5262TypeDef *tmc5262, int32_t velocity);
void tmc5262_right(TMC5262TypeDef *tmc5262, uint32_t velocity);
void tmc5262_left(TMC5262TypeDef *tmc5262, uint32_t velocity);
void tmc5262_stop(TMC5262TypeDef *tmc5262);
void tmc5262_moveTo(TMC5262TypeDef *tmc5262, int32_t position, uint32_t velocityMax);
void tmc5262_moveBy(TMC5262TypeDef *tmc5262, int32_t *ticks, uint32_t velocityMax);

#endif /* TMC_IC_TMC5262_H_ */
