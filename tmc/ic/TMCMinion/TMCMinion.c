/*
 * TMCMinion.c
 *
 *  Created on: 11.01.2019
 *      Author: LK
 */

#include "TMCMinion.h"

// Default Register values
#define R00 0x00000041  // GCONF
//#define R10 0x00001F00  // IHOLD_IRUN
#define R10 0x00071703  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x13008001  // CHOPCONF
#define R70 0xC40D1024  // PWMCONF

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (seperate functions/values)
 */
const u8 tmc_minion_defaultRegisterAccess[TMCMinion_REGISTER_COUNT] =
{
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	3, 3, 1, 2, 2, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00 - 0x0F
	2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x10 - 0x1F
	0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x20 - 0x2F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x30 - 0x3F
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x40 - 0x4F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x50 - 0x5F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 0, 1, // 0x60 - 0x6F
	3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 0x70 - 0x7F
};

const s32 tmc_minion_defaultRegisterResetState[TMCMinion_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// => SPI wrapper
extern void tmc_minion_writeRegister(uint8 motor, uint8 address, int32 value);
extern void tmc_minion_readRegister(uint8 motor, uint8 address, int32 *value);
// <= SPI wrapper

void tmc_minion_initConfig(TMCMinionTypeDef *tmc2224)
{
	tmc2224->velocity  = 0;
	tmc2224->oldTick   = 0;
	tmc2224->oldX      = 0;

	int i;
	for(i = 0; i < TMCMinion_REGISTER_COUNT; i++)
	{
		tmc2224->registerAccess[i]      = tmc_minion_defaultRegisterAccess[i];
		tmc2224->registerResetState[i]  = tmc_minion_defaultRegisterResetState[i];
	}
}

void tmc_minion_writeConfiguration(TMCMinionTypeDef *tmc_minion, ConfigurationTypeDef *TMCMinion_config)
{
	uint8 *ptr = &TMCMinion_config->configIndex;
	const int32 *settings = (TMCMinion_config->state == CONFIG_RESTORE) ? TMCMinion_config->shadowRegister : tmc_minion->registerResetState;

	while((*ptr < TMCMinion_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc_minion->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMCMinion_REGISTER_COUNT)
	{
		tmc_minion_writeRegister(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMCMinion_config->state = CONFIG_READY;
	}
}

void tmc_minion_periodicJob(u8 motor, uint32 tick, TMCMinionTypeDef *tmc_minion, ConfigurationTypeDef *TMCMinion_config)
{
	UNUSED(motor);

	if(TMCMinion_config->state != CONFIG_READY && (tick - tmc_minion->oldTick) > 2)
	{
		tmc_minion_writeConfiguration(tmc_minion, TMCMinion_config);
		tmc_minion->oldTick = tick;
	}
}

uint8 tmc_minion_reset(ConfigurationTypeDef *TMCMinion_config)
{
	if(TMCMinion_config->state != CONFIG_READY)
		return 0;

	TMCMinion_config->state        = CONFIG_RESET;
	TMCMinion_config->configIndex  = 0;

	return 1;
}

uint8 tmc_minion_restore(ConfigurationTypeDef *TMCMinion_config)
{
	if(TMCMinion_config->state != CONFIG_READY)
		return 0;

	TMCMinion_config->state        = CONFIG_RESTORE;
	TMCMinion_config->configIndex  = 0;

	return 1;
}

uint8 tmc_minion_get_slave(TMCMinionTypeDef *tmc_minion)
{
	return tmc_minion->slave;
}

void tmc_minion_set_slave(TMCMinionTypeDef *tmc_minion, uint8 slave)
{
	tmc_minion->slave = slave;
}
