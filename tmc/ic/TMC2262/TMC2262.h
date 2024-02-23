/*******************************************************************************
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2262_H_
#define TMC_IC_TMC2262_H_

#include "tmc/helpers/API_Header.h"
#include "tmc/helpers/Constants.h"
#include "TMC2262_Constants.h"
#include "TMC2262_fields.h"
#include "TMC2262_registers.h"

// Helper macros
#define TMC2262_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2262_readInt(tdef, address), mask, shift)
#define TMC2262_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc2262_writeInt(tdef, address, FIELD_SET(tmc2262_readInt(tdef, address), mask, shift, value)))

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	uint8_t slaveAddress;
} TMC2262TypeDef;

void tmc2262_writeDatagram(TMC2262TypeDef *tmc2262, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc2262_writeInt(TMC2262TypeDef *tmc2262, uint8_t address, int32_t value);
int32_t tmc2262_readInt(TMC2262TypeDef *tmc2262, uint8_t address);

void tmc2262_init(TMC2262TypeDef *tmc2262, uint8_t channel, ConfigurationTypeDef *config);
uint8_t tmc2262_reset(TMC2262TypeDef *tmc2262);
uint8_t tmc2262_restore(TMC2262TypeDef *tmc2262);
uint8_t tmc2262_getSlaveAddress(TMC2262TypeDef *tmc2262);
void tmc2262_setSlaveAddress(TMC2262TypeDef *tmc2262, uint8_t slaveAddress);
void tmc2262_periodicJob(TMC2262TypeDef *tmc2262, uint32_t tick);

uint8_t tmc2262_consistencyCheck(TMC2262TypeDef *tmc2262);

#endif /* TMC_IC_TMC2262_H_ */
