/*
 * TMC5041.c
 *
 *  Created on: 07.07.2017
 *      Author: LK
 *    Based on: TMC562-MKL.h (26.01.2012 OK)
 */

#include "TMC5041.h"

// => SPI wrapper
extern void tmc5041_writeDatagram(uint8_t motor, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
extern void tmc5041_writeInt(uint8_t motor, uint8_t address, int value);
extern int tmc5041_readInt(uint8_t motor, uint8_t address);
// <= SPI wrapper

void tmc5041_initConfig(TMC5041TypeDef *tmc5041)
{
	tmc5041->velocity[0]      = 0;
	tmc5041->velocity[1]      = 0;
	tmc5041->oldTick          = 0;
	tmc5041->oldX[0]          = 0;
	tmc5041->oldX[1]          = 0;
	tmc5041->vMaxModified[0]  = false;
	tmc5041->vMaxModified[1]  = false;

	int i;
	for(i = 0; i < TMC5041_REGISTER_COUNT; i++)
	{
		tmc5041->registerAccess[i]      = tmc5041_defaultRegisterAccess[i];
		tmc5041->registerResetState[i]  = tmc5041_defaultRegisterResetState[i];
	}
}

void tmc5041_writeConfiguration(TMC5041TypeDef *tmc5041, ConfigurationTypeDef *TMC5041_config)
{
	uint8_t *ptr = &TMC5041_config->configIndex;
	const int32_t *settings = (TMC5041_config->state == CONFIG_RESTORE) ? TMC5041_config->shadowRegister : tmc5041->registerResetState;

	while((*ptr < TMC5041_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5041->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC5041_REGISTER_COUNT)
	{
		tmc5041_writeInt(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMC5041_config->state = CONFIG_READY;
	}
}

void tmc5041_periodicJob(uint8_t motor, uint32_t tick, TMC5041TypeDef *tmc5041, ConfigurationTypeDef *TMC5041_config)
{
	int xActual;
	uint32_t tickDiff;

	if(TMC5041_config->state != CONFIG_READY)
	{
		tmc5041_writeConfiguration(tmc5041, TMC5041_config);
		return;
	}

	if((tickDiff = tick - tmc5041->oldTick) >= 5)
	{
		xActual = tmc5041_readInt(0, TMC5041_XACTUAL(motor));
		TMC5041_config->shadowRegister[TMC5041_XACTUAL(motor)] = xActual;
		tmc5041->velocity[motor] = (int) ((float) (abs(xActual-tmc5041->oldX[motor]) / (float) tickDiff) * (float) 1048.576);
		tmc5041->oldX[motor] = xActual;

		// Not per motor:
		//xActual = tmc5041_readInt(motor, TMC5041_XACTUAL_1);
		//TMC562v3_config->shadowRegister[TMC5041_XACTUAL_1] = xActual;
		//TMC562V3.velocityMotor1 = (int) ((float) (abs(xActual-oldX[0]) / (float) t) * (float) 1048.576);
		//tmc5041->oldX = xActual;

		//xActual = readInt(TMC5041_XACTUAL_2);
		//TMC562v3_config->shadowRegister[TMC5041_XACTUAL_2] = xActual;
		//TMC562V3.velocityMotor2 = (int) ((float) (abs(xActual-oldX[1]) / (float) t) * (float) 1048.576);
		//tmc5041->oldX = xActual;

		tmc5041->oldTick = tick;
	}
}

uint8_t tmc5041_reset(ConfigurationTypeDef *TMC5041_config)
{
	if(TMC5041_config->state != CONFIG_READY)
		return 0;

	TMC5041_config->state        = CONFIG_RESET;
	TMC5041_config->configIndex  = 0;

	return 1;
}

uint8_t tmc5041_restore(ConfigurationTypeDef *TMC5041_config)
{
	if(TMC5041_config->state != CONFIG_READY)
		return 0;

	TMC5041_config->state        = CONFIG_RESTORE;
	TMC5041_config->configIndex  = 0;

	return 1;
}
