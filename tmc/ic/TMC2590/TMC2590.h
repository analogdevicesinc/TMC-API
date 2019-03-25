/*
 * TMC2590.h
 *
 *  Created on: 09.01.2019
 *      Author: LK
 */

#ifndef TMC_IC_TMC2590_H_
#define TMC_IC_TMC2590_H_

#include "../../../TMC-API/tmc/helpers/API_Header.h"
#include "TMC2590_Constants.h"
#include "TMC2590_Fields.h"
#include "TMC2590_Macros.h"
#include "TMC2590_Register.h"

#define TMC2590_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2590_readInt(tdef, address), mask, shift)
#define TMC2590_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc2590_writeInt(tdef, address, FIELD_SET(tmc2590_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	ConfigurationTypeDef *config;
	uint8_t standStillCurrentScale;
	uint32_t standStillTimeout;
	uint8_t isStandStillOverCurrent;
	uint8_t isStandStillCurrentLimit;
	uint8_t continuousModeEnable;
	uint8_t runCurrentScale;
	uint8_t coolStepInactiveValue;
	uint8_t coolStepActiveValue;
	uint32_t coolStepThreshold;
	int velocity;
	int oldX;
	uint32_t oldTick;
	uint8_t registerAccess[TMC2590_REGISTER_COUNT];
	int32_t registerResetState[TMC2590_REGISTER_COUNT];
} TMC2590TypeDef;

static const uint8_t tmc2590_defaultRegisterAccess[TMC2590_REGISTER_COUNT] =
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

static const int32_t tmc2590_defaultRegisterResetState[TMC2590_REGISTER_COUNT] =
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

void tmc2590_init(TMC2590TypeDef *tmc2590, uint8_t channel, ConfigurationTypeDef *tmc2590_config, const int32_t *registerResetState);
void tmc2590_periodicJob(TMC2590TypeDef *tmc2590, uint32_t tick);
void tmc2590_writeInt(TMC2590TypeDef *tmc2590, uint8_t address, int32_t value);
uint32_t tmc2590_readInt(TMC2590TypeDef *tmc2590, uint8_t address);
uint8_t tmc2590_reset(TMC2590TypeDef *tmc2590);
uint8_t tmc2590_restore(TMC2590TypeDef *tmc2590);

#endif /* TMC_IC_TMC2590_H_ */
