/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5031_H_
#define TMC_IC_TMC5031_H_

#include "tmc/helpers/API_Header.h"
#include "TMC5031_Register.h"
#include "TMC5031_Constants.h"
#include "TMC5031_Fields.h"

#define TMC5031_FIELD_READ(motor, address, mask, shift) \
	FIELD_READ(tmc5031_readInt, motor, address, mask, shift)
#define TMC5031_FIELD_WRITE(motor, address, mask, shift, value) \
	FIELD_WRITE(tmc5031_writeInt, motor, address, mask, shift, value)
#define TMC5031_FIELD_UPDATE(motor, address, mask, shift, value) \
	FIELD_UPDATE(tmc5031_readInt, tmc5031_writeInt, motor, address, mask, shift, value)

// Usage note: use 1 TypeDef per IC
typedef struct {
	int32_t velocity[2], oldX[2];
	uint32_t oldTick;
	int32_t registerResetState[TMC5031_REGISTER_COUNT];
	uint8_t registerAccess[TMC5031_REGISTER_COUNT];
	bool vMaxModified[2];
} TMC5031TypeDef;

void tmc5031_initConfig(TMC5031TypeDef *TMC5031);
void tmc5031_periodicJob(uint8_t motor, uint32_t tick, TMC5031TypeDef *TMC5031, ConfigurationTypeDef *TMC5031_config);
uint8_t tmc5031_reset(ConfigurationTypeDef *TMC5031_config);
uint8_t tmc5031_restore(ConfigurationTypeDef *TMC5031_config);

#endif /* TMC_IC_TMC5031_H_ */
