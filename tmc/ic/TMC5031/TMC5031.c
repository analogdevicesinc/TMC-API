/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5031.h"

TMC5031TypeDef TMC5031;
ConfigurationTypeDef *TMC5031_config;

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5031_readRegister(uint16_t icID, uint8_t address)
{
		return readRegisterSPI(icID, address);

	// ToDo: Error handling
}
void tmc5031_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
		writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{

	address = TMC_ADDRESS(address);
	uint8_t data[5] = { 0 };

	if(!TMC_IS_READABLE(TMC5031.registerAccess[address]))
		return TMC5031_config->shadowRegister[address];

	// clear write bit
	data[0] = address;

	// Send the read request
	tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address;

	// Send another request to receive the read reply
	tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5031_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

	// Write to the shadow register
	address = TMC_ADDRESS(address);
	TMC5031_config->shadowRegister[address] = value;

}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/


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
 * 7: read^write (separate functions/values)
 */
const uint8_t tmc5031_defaultRegisterAccess[TMC5031_REGISTER_COUNT] = {
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

const int32_t tmc5031_defaultRegisterResetState[TMC5031_REGISTER_COUNT] = {
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

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R30
#undef R32
#undef R3A
#undef R60
#undef R61
#undef R62
#undef R63
#undef R64
#undef R65
#undef R66
#undef R67
#undef R68
#undef R69
#undef R6C

// => SPI wrapper
extern void tmc5031_writeDatagram(uint8_t motor, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
extern void tmc5031_writeInt(uint8_t motor, uint8_t address, int value);
extern int32_t tmc5031_readInt(uint8_t motor, uint8_t address);
// <= SPI wrapper

void tmc5031_initConfig(TMC5031TypeDef *tmc5031)
{
	tmc5031->velocity[0]      = 0;
	tmc5031->velocity[1]      = 0;
	tmc5031->oldTick          = 0;
	tmc5031->oldX[0]          = 0;
	tmc5031->oldX[1]          = 0;
	tmc5031->vMaxModified[0]  = false;
	tmc5031->vMaxModified[1]  = false;

	int32_t i;
	for(i = 0; i < TMC5031_REGISTER_COUNT; i++)
	{
		tmc5031->registerAccess[i]      = tmc5031_defaultRegisterAccess[i];
		tmc5031->registerResetState[i]  = tmc5031_defaultRegisterResetState[i];
	}
}

void tmc5031_writeConfiguration(TMC5031TypeDef *tmc5031, ConfigurationTypeDef *TMC5031_config)
{
	uint8_t *ptr = &TMC5031_config->configIndex;
	const int32_t *settings = (TMC5031_config->state == CONFIG_RESTORE) ? TMC5031_config->shadowRegister : tmc5031->registerResetState;

	while((*ptr < TMC5031_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5031->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC5031_REGISTER_COUNT)
	{
		tmc5031_writeRegister(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		TMC5031_config->state = CONFIG_READY;
	}
}

void tmc5031_periodicJob(uint8_t motor, uint32_t tick, TMC5031TypeDef *tmc5031, ConfigurationTypeDef *TMC5031_config)
{
	int32_t xActual;
	uint32_t tickDiff;

	if(TMC5031_config->state != CONFIG_READY)
	{
		tmc5031_writeConfiguration(tmc5031, TMC5031_config);
		return;
	}

	if((tickDiff = tick - tmc5031->oldTick) >= 5)
	{
		xActual = tmc5031_readRegister(0, TMC5031_XACTUAL(motor));
		TMC5031_config->shadowRegister[TMC5031_XACTUAL(motor)] = xActual;
		tmc5031->velocity[motor] = (int32_t) ((float) (abs(xActual-tmc5031->oldX[motor]) / (float) tickDiff) * (float) 1048.576);
		if(tmc5031_readRegister(0, TMC5031_VACTUAL(motor))<0) tmc5031->velocity[motor] *= -1;
		tmc5031->oldX[motor] = xActual;

		// Not per motor:
		/*xActual = tmc5031_readRegister(motor, TMC5031_XACTUAL_1);
		TMC562v3_config->shadowRegister[TMC5031_XACTUAL_1] = xActual;
		TMC562V3.velocityMotor1 = (int32_t) ((float) (abs(xActual-oldX[0]) / (float) t) * (float) 1048.576);
		tmc5031->oldX = xActual;

		xActual = readInt(TMC5031_XACTUAL_2);
		TMC562v3_config->shadowRegister[TMC5031_XACTUAL_2] = xActual;
		TMC562V3.velocityMotor2 = (int32_t) ((float) (abs(xActual-oldX[1]) / (float) t) * (float) 1048.576);
		tmc5031->oldX = xActual;*/

		tmc5031->oldTick = tick;
	}
}

uint8_t tmc5031_reset(ConfigurationTypeDef *TMC5031_config)
{
	if(TMC5031_config->state != CONFIG_READY)
		return 0;

	TMC5031_config->state        = CONFIG_READY;
	TMC5031_config->configIndex  = 0;

	return 1;
}

uint8_t tmc5031_restore(ConfigurationTypeDef *TMC5031_config)
{
	if(TMC5031_config->state != CONFIG_READY)
		return 0;

	TMC5031_config->state        = CONFIG_RESTORE;
	TMC5031_config->configIndex  = 0;

	return 1;
}
