/*
 * TMC5160.c
 *
 *  Created on: 04.07.2017
 *      Author: LK based on ED based on BS
 */

#include "TMC5160.h"

// todo ADD API 3: Some Registers have default hardware configuration from OTP, we shouldnt overwrite those - add the weak write register permission and use it here (LH)
// Default Register Values
#define R00 0x00000008  // GCONF
#define R09 0x00010606  // SHORT_CONF
#define R0A 0x00080400  // DRV_CONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2B 0x00000001  // VSTOP
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
#define R6C 0x00410153  // CHOPCONF
#define R70 0xC40C001E  // PWMCONF

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (seperate functions/values)
 */
const u8 tmc5160_defaultRegisterAccess[TMC5160_REGISTER_COUNT] =
{
//	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	3, 7, 1, 2, 7, 2, 2, 1, 1, 2, 2, 2, 1, 0, 0, 0, // 0x00 - 0x0F
	2, 2, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x10 - 0x1F
	3, 3, 1, 2, 2, 2, 2, 2, 2, 0, 2, 2, 2, 3, 0, 0, // 0x20 - 0x2F
	0, 0, 0, 2, 3, 7, 1, 0, 3, 3, 2, 7, 1, 2, 0, 0, // 0x30 - 0x3F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x40 - 0x4F
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x50 - 0x5F
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 3, 2, 2, 1, // 0x60 - 0x6F
	2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 0x70 - 0x7F
};

const s32 tmc5160_defaultRegisterResetState[TMC5160_REGISTER_COUNT] =
{
//	0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   R09, R0A, 0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R2B, 0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// => SPI wrapper
extern void tmc5160_writeDatagram(uint8 motor, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4);
extern void tmc5160_writeInt(uint8 motor, uint8 address, int value);
extern int tmc5160_readInt(u8 motor, uint8 address);
// <= SPI wrapper

void tmc5160_initConfig(TMC5160TypeDef *tmc5160)
{
	tmc5160->velocity  = 0;
	tmc5160->oldTick   = 0;
	tmc5160->oldX      = 0;

	int i;
	for(i = 0; i < TMC5160_REGISTER_COUNT; i++)
	{
		tmc5160->registerAccess[i]      = tmc5160_defaultRegisterAccess[i];
		tmc5160->registerResetState[i]  = tmc5160_defaultRegisterResetState[i];
	}
}

void tmc5160_writeConfiguration(u8 motor, TMC5160TypeDef *tmc5160, ConfigurationTypeDef *TMC5160_config)
{
	uint8 *ptr = &TMC5160_config->configIndex;
	const int32 *settings = (TMC5160_config->state == CONFIG_RESTORE) ? TMC5160_config->shadowRegister : tmc5160->registerResetState;

	while((*ptr < TMC5160_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5160->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC5160_REGISTER_COUNT)
	{
		tmc5160_writeInt(motor, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMC5160_config->state = CONFIG_READY;
	}
}

void tmc5160_periodicJob(u8 motor, uint32 tick, TMC5160TypeDef *tmc5160, ConfigurationTypeDef *TMC5160_config)
{
	if(TMC5160_config->state != CONFIG_READY)
	{
		tmc5160_writeConfiguration(motor, tmc5160, TMC5160_config);
		return;
	}

	int XActual;
	uint32 tickDiff;

	if((tickDiff = tick-tmc5160->oldTick) >= 5) // measured speed dx/dt
	{
		XActual = tmc5160_readInt(motor, TMC5160_XACTUAL);
		TMC5160_config->shadowRegister[TMC5160_XACTUAL] = XActual;
		tmc5160->velocity = (int) ((float) ((XActual-tmc5160->oldX) / (float) tickDiff) * (float) 1048.576);

		tmc5160->oldX     = XActual;
		tmc5160->oldTick  = tick;
	}
}

uint8 tmc5160_reset(ConfigurationTypeDef *TMC5160_config)
{
	if(TMC5160_config->state != CONFIG_READY)
		return 0;

	TMC5160_config->state        = CONFIG_RESET;
	TMC5160_config->configIndex  = 0;

	return 1;
}

uint8 tmc5160_restore(ConfigurationTypeDef *TMC5160_config)
{
	if(TMC5160_config->state != CONFIG_READY)
		return 0;

	TMC5160_config->state        = CONFIG_RESTORE;
	TMC5160_config->configIndex  = 0;

	return 1;
}
