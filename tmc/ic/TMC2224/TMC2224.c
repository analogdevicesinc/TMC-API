/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2224.h"

};




void tmc2224_initConfig(TMC2224TypeDef *tmc2224)
{
	tmc2224->velocity      = 0;
	tmc2224->oldTick       = 0;
	tmc2224->oldX          = 0;
	tmc2224->vMaxModified  = false;

	int32_t i;
	for(i = 0; i < TMC2224_REGISTER_COUNT; i++)
	{
		tmc2224->registerAccess[i]      = tmc2224_defaultRegisterAccess[i];
		tmc2224->registerResetState[i]  = tmc2224_defaultRegisterResetState[i];
	}
}

void tmc2224_writeConfiguration(TMC2224TypeDef *tmc2224, ConfigurationTypeDef *TMC2224_config)
{
	uint8_t *ptr = &TMC2224_config->configIndex;
	const int32_t *settings = (TMC2224_config->state == CONFIG_RESTORE) ? TMC2224_config->shadowRegister : tmc2224->registerResetState;

	while((*ptr < TMC2224_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc2224->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC2224_REGISTER_COUNT)
	{
		tmc2224_writeRegister(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMC2224_config->state = CONFIG_READY;
	}
}

void tmc2224_periodicJob(uint8_t motor, uint32_t tick, TMC2224TypeDef *tmc2224, ConfigurationTypeDef *TMC2224_config)
{
	UNUSED(motor);

	if(TMC2224_config->state != CONFIG_READY && (tick - tmc2224->oldTick) > 2)
	{
		tmc2224_writeConfiguration(tmc2224, TMC2224_config);
		tmc2224->oldTick = tick;
	}
}

uint8_t tmc2224_reset(TMC2224TypeDef *tmc2224, ConfigurationTypeDef *TMC2224_config)
{
	if(TMC2224_config->state != CONFIG_READY)
		return 0;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC2224_REGISTER_COUNT; i++)
	{
		tmc2224->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		TMC2224_config->shadowRegister[i] = 0;
	}
	TMC2224_config->state        = CONFIG_RESET;
	TMC2224_config->configIndex  = 0;

	return 1;
}

uint8_t tmc2224_restore(ConfigurationTypeDef *TMC2224_config)
{
	if(TMC2224_config->state != CONFIG_READY)
		return 0;

	TMC2224_config->state        = CONFIG_RESTORE;
	TMC2224_config->configIndex  = 0;

	return 1;
}

uint8_t tmc2224_get_slave(TMC2224TypeDef *tmc2224)
{
	return tmc2224->slave;
}

void tmc2224_set_slave(TMC2224TypeDef *tmc2224, uint8_t slave)
{
	tmc2224->slave = slave;
}
