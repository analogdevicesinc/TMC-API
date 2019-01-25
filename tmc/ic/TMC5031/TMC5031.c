/*
 * TMC5031.c
 *
 *  Created on: 06.07.2017
 *      Author: LK
 *    Based on: TMC562-MKL.h (26.01.2012 OK)
 */

#include "TMC5031.h"

// Default Register Values
#define R30 0x00071703  // IHOLD_IRUN
#define R32 0x00FFFFFF  // VHIGH
#define R3A 0x00010000  // ENC_CONST
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
#define R6C 0x000101D5  // CHOPCONF

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (seperate functions/values)
 */
const u8 tmc5031_defaultRegisterAccess[TMC5031_REGISTER_COUNT] = {
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	3, 1, 1, 2, 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00 - 0x0F
	2, 1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, // 0x10 - 0x1F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, // 0x20 - 0x2F
	2, 2, 2, 2, 3, 1, 1, 0, 3, 3, 2, 1, 1, 0, 0, 0, // 0x30 - 0x3F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 0, // 0x40 - 0x4F
	2, 2, 2, 2, 3, 1, 1, 0, 3, 3, 2, 1, 1, 0, 0, 0, // 0x50 - 0x5F
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 2, 1, // 0x60 - 0x6F
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 2, 1  // 0x70 - 0x7F
};

const s32 tmc5031_defaultRegisterResetState[TMC5031_REGISTER_COUNT] = {
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	R30, 0,   R32, 0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x50 - 0x5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0  // 0x70 - 0x7F
};

// => SPI wrapper
extern void tmc5031_writeDatagram(u8 motor, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4);
extern void tmc5031_writeInt(u8 motor, uint8 address, int value);
extern int tmc5031_readInt(u8 motor, uint8 address);
// <= SPI wrapper

void tmc5031_initConfig(TMC5031TypeDef *tmc5031)
{
	tmc5031->velocity[0]      = 0;
	tmc5031->velocity[1]      = 0;
	tmc5031->oldTick          = 0;
	tmc5031->oldX[0]          = 0;
	tmc5031->oldX[1]          = 0;
	tmc5031->vMaxModified[0]  = FALSE;
	tmc5031->vMaxModified[1]  = FALSE;

	int i;
	for(i = 0; i < TMC5031_REGISTER_COUNT; i++)
	{
		tmc5031->registerAccess[i]      = tmc5031_defaultRegisterAccess[i];
		tmc5031->registerResetState[i]  = tmc5031_defaultRegisterResetState[i];
	}
}

void tmc5031_writeConfiguration(TMC5031TypeDef *tmc5031, ConfigurationTypeDef *TMC5031_config)
{
	uint8 *ptr = &TMC5031_config->configIndex;
	const int32 *settings = (TMC5031_config->state == CONFIG_RESTORE) ? TMC5031_config->shadowRegister : tmc5031->registerResetState;

	while((*ptr < TMC5031_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5031->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC5031_REGISTER_COUNT)
	{
		tmc5031_writeInt(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMC5031_config->state = CONFIG_READY;
	}
}

void tmc5031_periodicJob(u8 motor, uint32 tick, TMC5031TypeDef *tmc5031, ConfigurationTypeDef *TMC5031_config)
{
	int xActual;
	uint32 tickDiff;

	if(TMC5031_config->state != CONFIG_READY)
	{
		tmc5031_writeConfiguration(tmc5031, TMC5031_config);
		return;
	}

	if((tickDiff = tick - tmc5031->oldTick) >= 5)
	{
		xActual = tmc5031_readInt(0, TMC5031_XACTUAL(motor));
		TMC5031_config->shadowRegister[TMC5031_XACTUAL(motor)] = xActual;
		tmc5031->velocity[motor] = (int) ((float) (abs(xActual-tmc5031->oldX[motor]) / (float) tickDiff) * (float) 1048.576);
		if(tmc5031_readInt(0, TMC5031_VACTUAL(motor))<0) tmc5031->velocity[motor] *= -1;
		tmc5031->oldX[motor] = xActual;

		// Not per motor:
		/*xActual = tmc5031_readInt(motor, TMC5031_XACTUAL_1);
		TMC562v3_config->shadowRegister[TMC5031_XACTUAL_1] = xActual;
		TMC562V3.velocityMotor1 = (int) ((float) (abs(xActual-oldX[0]) / (float) t) * (float) 1048.576);
		tmc5031->oldX = xActual;

		xActual = readInt(TMC5031_XACTUAL_2);
		TMC562v3_config->shadowRegister[TMC5031_XACTUAL_2] = xActual;
		TMC562V3.velocityMotor2 = (int) ((float) (abs(xActual-oldX[1]) / (float) t) * (float) 1048.576);
		tmc5031->oldX = xActual;*/

		tmc5031->oldTick = tick;
	}
}

uint8 tmc5031_reset(ConfigurationTypeDef *TMC5031_config)
{
	if(TMC5031_config->state != CONFIG_READY)
		return 0;

	TMC5031_config->state        = CONFIG_READY;
	TMC5031_config->configIndex  = 0;

	return 1;
}

uint8 tmc5031_restore(ConfigurationTypeDef *TMC5031_config)
{
	if(TMC5031_config->state != CONFIG_READY)
		return 0;

	TMC5031_config->state        = CONFIG_RESTORE;
	TMC5031_config->configIndex  = 0;

	return 1;
}
