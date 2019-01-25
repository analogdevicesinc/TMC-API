/*
 * TMCMinion.h
 *
 *  Created on: 11.01.2019
 *      Author: LK
 */

#ifndef TMC_IC_TMCMinion_H_
#define TMC_IC_TMCMinion_H_

#include "../../helpers/Constants.h"
#include "../../helpers/API_Header.h"
#include "TMCMinion_Register.h"
#include "TMCMinion_Constants.h"

// Usage note: use 1 TypeDef per IC
typedef struct {
	int velocity;
	int oldX;
	uint32 oldTick;
	int32 registerResetState[TMCMinion_REGISTER_COUNT];
	uint8 registerAccess[TMCMinion_REGISTER_COUNT];
	uint8 slave;
} TMCMinionTypeDef;

void tmc_minion_initConfig(TMCMinionTypeDef *TMCMinion);
void tmc_minion_periodicJob(u8 motor, uint32 tick, TMCMinionTypeDef *TMCMinion, ConfigurationTypeDef *TMCMinion_config);
u8 tmc_minion_reset(ConfigurationTypeDef *TMCMinion_config);
u8 tmc_minion_restore(ConfigurationTypeDef *TMCMinion_config);

uint8 tmc_minion_get_slave(TMCMinionTypeDef *tmc_minion);
void tmc_minion_set_slave(TMCMinionTypeDef *tmc_minion, uint8 slave);

#endif /* TMC_IC_TMCMinion_H_ */
