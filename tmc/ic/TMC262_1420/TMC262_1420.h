/*
 * TMC262_1420.h
 *
 *  Created on: 06.07.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC262_1420_H_
#define TMC_IC_TMC262_1420_H_

#include "../../helpers/API_Header.h"
#include "TMC262_1420_Constants.h"
#include "TMC262_1420_Fields.h"
#include "TMC262_1420_Macros.h"
#include "TMC262_1420_Register.h"

#define TMC262_1420_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc262_1420_readInt(tdef, address), mask, shift)
#define TMC262_1420_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc262_1420_writeInt(tdef, address, FIELD_SET(tmc262_1420_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;
	uint8 standStillCurrentScale;
	uint32 standStillTimeout;
	uint8 isStandStillOverCurrent;
	uint8 isStandStillCurrentLimit;
	uint8 continuousModeEnable;
	uint8 runCurrentScale;
	uint8 coolStepInactiveValue;
	uint8 coolStepActiveValue;
	uint32 coolStepThreshold;
	int velocity;
	int oldX;
	uint32 oldTick;
	u8 registerAccess[TMC262_1420_REGISTER_COUNT];
	int32 registerResetState[TMC262_1420_REGISTER_COUNT];
} TMC262_1420TypeDef;

static const uint8 tmc262_1420_defaultRegisterAccess[TMC262_1420_REGISTER_COUNT] =
{
	0x02,  // 0: DRVCTRL
	0x00,  // 1: UNUSED
	0x00,  // 2: UNUSED
	0x00,  // 3: UNUSED
	0x02,  // 4: CHOPCONF
	0x02,  // 5: SMARTEN
	0x02,  // 6: SGCSCONF
	0x02   // 7: DRVCONF
};

static const int32 tmc262_1420_defaultRegisterResetState[TMC262_1420_REGISTER_COUNT] =
{
	0x10000000,  // 0: DRVCTRL
	0x00000000,  // 1: UNUSED
	0x00000000,  // 2: UNUSED
	0x00000000,  // 3: UNUSED
	0x00091935,  // 4: CHOPCONF
	0x000A0000,  // 5: SMARTEN
	0x000D0505,  // 6: SGCSCONF
	0x000EF040   // 7: DRVCONF
};

void tmc262_1420_init(TMC262_1420TypeDef *tmc262_1420, uint8 channel, ConfigurationTypeDef *tmc262_1420_config, const int32 *registerResetState);
void tmc262_1420_periodicJob(TMC262_1420TypeDef *tmc262_1420, uint32 tick);
void tmc262_1420_writeInt(TMC262_1420TypeDef *tmc262_1420, uint8 address, int32 value);
uint32 tmc262_1420_readInt(TMC262_1420TypeDef *tmc262_1420, uint8 address);
uint8 tmc262_1420_reset(TMC262_1420TypeDef *tmc262_1420);
uint8 tmc262_1420_restore(TMC262_1420TypeDef *tmc262_1420);

#endif /* TMC_IC_TMC262_1420_H_ */
