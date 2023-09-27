/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2660_H_
#define TMC_IC_TMC2660_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2660_Register.h"
#include "TMC2660_Constants.h"
#include "TMC2660_Fields.h"

#define TMC2660_FIELD_READ(motor, address, mask, shift)           FIELD_READ(tmc2660_readInt, motor, address, mask, shift)
#define TMC2660_FIELD_WRITE(motor, address, mask, shift, value)   FIELD_WRITE(tmc2660_writeInt, motor, address, mask, shift, value)
#define TMC2660_FIELD_UPDATE(motor, address, mask, shift, value)  FIELD_UPDATE(tmc2660_readInt, tmc2660_writeInt, motor, address | TMC2660_WRITE_BIT, mask, shift, value)

// Usage note: use 1 TypeDef per IC
typedef struct {
	uint8_t standStillCurrentScale;
	uint32_t standStillTimeout;
	uint8_t isStandStillOverCurrent;
	uint8_t isStandStillCurrentLimit;
	uint8_t continuousModeEnable;
	uint8_t runCurrentScale;
	uint8_t coolStepInactiveValue;
	uint8_t coolStepActiveValue;
	uint32_t coolStepThreshold;
	int32_t velocity;
	int32_t oldX;
	uint32_t oldTick;
	uint8_t registerAccess[TMC2660_REGISTER_COUNT];
	int32_t registerResetState[TMC2660_REGISTER_COUNT];
} TMC2660TypeDef;

void tmc2660_initConfig(TMC2660TypeDef *TMC2660);
void tmc2660_periodicJob(uint8_t motor, uint32_t tick, TMC2660TypeDef *TMC2660, ConfigurationTypeDef *TMC2660_config);
uint8_t tmc2660_reset(TMC2660TypeDef *TMC2660, ConfigurationTypeDef *TMC2660_config);
uint8_t tmc2660_restore(ConfigurationTypeDef *TMC2660_config);

#endif /* TMC_IC_TMC2660_H_ */
