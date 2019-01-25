/*
 * TMC5041.c
 *
 *  Created on: 07.07.2017
 *      Author: LK
 *    Based on: TMC562-MKL.h (26.01.2012 OK)
 */

#include "TMC5041.h"

#define R30 0x00071703  // IHOLD_IRUN (Motor 1)
#define R32 0x00FFFFFF  // VHIGH      (Motor 1)
#define R50 0x00071703  // IHOLD_IRUN (Motor 2)
#define R52 0x00FFFFFF  // VHIGH      (Motor 2)

#define R60 0xAAAAB554  // MSLUT[0]
#define R61 0x4A9554AA  // MSLUT[1]
#define R62 0x24492929  // MSLUT[2]
#define R63 0x10104222  // MSLUT[3]
#define R64 0xFBFFFFFF  // MSLUT[4]
#define R65 0xB5BB777D  // MSLUT[5]
#define R66 0x49295556  // MSLUT[6]
#define R67 0x00404222  // MSLUT[7]
#define R68 0xFFFF8056  // MSLUTSEL
#define R69 0x00F70000  // MSLUTSTART

#define R6C 0x000101D5  // CHOPCONF (Motor 1)
#define R7C 0x000101D5  // CHOPCONF (Motor 2)

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (seperate functions/values)
 */
const u8 tmc5041_defaultRegisterAccess[TMC5041_REGISTER_COUNT] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	3, 1, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 00 - 0F
	2, 1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, // 10 - 1F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 0, 0, // 20 - 2F
	2, 2, 2, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 30 - 3F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 0, 0, // 40 - 4F
	2, 2, 2, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 50 - 5F
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 0, 1, // 60 - 6F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 2, 0, 1  // 70 - 7F
};

const s32 tmc5041_defaultRegisterResetState[TMC5041_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 00 - 0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 10 - 1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 20 - 2F
	R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 30 - 3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 40 - 4F
	R50, 0,   R52, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 50 - 5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 60 - 6F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R7C, 0,   0,   0  // 70 - 7F
};

// => SPI wrapper
extern void tmc5041_writeDatagram(u8 motor, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4);
extern void tmc5041_writeInt(u8 motor, uint8 address, int value);
extern int tmc5041_readInt(u8 motor, uint8 address);
// <= SPI wrapper

void tmc5041_initConfig(TMC5041TypeDef *tmc5041)
{
	tmc5041->velocity[0]      = 0;
	tmc5041->velocity[1]      = 0;
	tmc5041->oldTick          = 0;
	tmc5041->oldX[0]          = 0;
	tmc5041->oldX[1]          = 0;
	tmc5041->vMaxModified[0]  = FALSE;
	tmc5041->vMaxModified[1]  = FALSE;

	int i;
	for(i = 0; i < TMC5041_REGISTER_COUNT; i++)
	{
		tmc5041->registerAccess[i]      = tmc5041_defaultRegisterAccess[i];
		tmc5041->registerResetState[i]  = tmc5041_defaultRegisterResetState[i];
	}
}

void tmc5041_writeConfiguration(TMC5041TypeDef *tmc5041, ConfigurationTypeDef *TMC5041_config)
{
	uint8 *ptr = &TMC5041_config->configIndex;
	const int32 *settings = (TMC5041_config->state == CONFIG_RESTORE) ? TMC5041_config->shadowRegister : tmc5041->registerResetState;

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

void tmc5041_periodicJob(u8 motor, uint32 tick, TMC5041TypeDef *tmc5041, ConfigurationTypeDef *TMC5041_config)
{
	int xActual;
	uint32 tickDiff;

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

uint8 tmc5041_reset(ConfigurationTypeDef *TMC5041_config)
{
	if(TMC5041_config->state != CONFIG_READY)
		return 0;

	TMC5041_config->state        = CONFIG_RESET;
	TMC5041_config->configIndex  = 0;

	return 1;
}

uint8 tmc5041_restore(ConfigurationTypeDef *TMC5041_config)
{
	if(TMC5041_config->state != CONFIG_READY)
		return 0;

	TMC5041_config->state        = CONFIG_RESTORE;
	TMC5041_config->configIndex  = 0;

	return 1;
}
