/*
 * TMC2224.h
 *
 *  Created on: 07.07.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC2224_H_
#define TMC_IC_TMC2224_H_

#include "tmc/helpers/API_Header.h"
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
	uint32_t oldTick;
	int32_t registerResetState[TMC2224_REGISTER_COUNT];
	uint8_t registerAccess[TMC2224_REGISTER_COUNT];
	bool vMaxModified;
	uint8_t slave;
} TMC2224TypeDef;

void tmc2224_initConfig(TMC2224TypeDef *TMC2224);
void tmc2224_periodicJob(uint8_t motor, uint32_t tick, TMC2224TypeDef *TMC2224, ConfigurationTypeDef *TMC2224_config);
uint8_t tmc2224_reset(ConfigurationTypeDef *TMC2224_config);
uint8_t tmc2224_restore(ConfigurationTypeDef *TMC2224_config);

uint8_t tmc2224_get_slave(TMC2224TypeDef *tmc2224);
void tmc2224_set_slave(TMC2224TypeDef *tmc2224, uint8_t slave);

#endif /* TMC_IC_TMC2224_H_ */
