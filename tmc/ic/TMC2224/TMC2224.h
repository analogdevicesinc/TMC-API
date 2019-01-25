/*
 * TMC2224.h
 *
 *  Created on: 07.07.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC2224_H_
#define TMC_IC_TMC2224_H_

#include "../../helpers/API_Header.h"
#include "TMC2224_Register.h"

#define TMC2224_MOTORS           1
#define TMC2224_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC2224_WRITE_BIT        TMC_WRITE_BIT
#define TMC2224_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC2224_MAX_VELOCITY     s32_MAX
#define TMC2224_MAX_ACCELERATION u24_MAX

// Usage note: use 1 TypeDef per IC
typedef struct {
	int velocity;
	int oldX;
	uint32 oldTick;
	int32 registerResetState[TMC2224_REGISTER_COUNT];
	uint8 registerAccess[TMC2224_REGISTER_COUNT];
	bool vMaxModified;
	uint8 slave;
} TMC2224TypeDef;

void tmc2224_initConfig(TMC2224TypeDef *TMC2224);
void tmc2224_periodicJob(u8 motor, uint32 tick, TMC2224TypeDef *TMC2224, ConfigurationTypeDef *TMC2224_config);
u8 tmc2224_reset(ConfigurationTypeDef *TMC2224_config);
u8 tmc2224_restore(ConfigurationTypeDef *TMC2224_config);

uint8 tmc2224_get_slave(TMC2224TypeDef *tmc2224);
void tmc2224_set_slave(TMC2224TypeDef *tmc2224, uint8 slave);

#endif /* TMC_IC_TMC2224_H_ */
