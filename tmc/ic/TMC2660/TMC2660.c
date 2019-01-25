/*
 * TMC2660.c
 *
 *  Created on: 11.07.2017
 *      Author: LK
 */

#include "TMC2660.h"

const u8 tmc2660_defaultRegisterAccess[TMC2660_REGISTER_COUNT] =
{
	TMC_ACCESS_WRITE,  // 0: DRVCTRL
	TMC_ACCESS_NONE,   // 1: UNUSED
	TMC_ACCESS_NONE,   // 2: UNUSED
	TMC_ACCESS_NONE,   // 3: UNUSED
	TMC_ACCESS_WRITE,  // 4: CHOPCONF
	TMC_ACCESS_WRITE,  // 5: SMARTEN
	TMC_ACCESS_WRITE,  // 6: SGCSCONF
	TMC_ACCESS_WRITE   // 7: DRVCONF
};

const s32 tmc2660_defaultRegisterResetState[TMC2660_REGISTER_COUNT] =
{
	0x00000000,  // 0: DRVCTRL
	0x00000000,  // 1: UNUSED
	0x00000000,  // 2: UNUSED
	0x00000000,  // 3: UNUSED
	0x00091935,  // 4: CHOPCONF
	0x000A0000,  // 5: SMARTEN
	0x000D0505,  // 6: SGCSCONF
	0x000EF040   // 7: DRVCONF
};

// => SPI wrapper
extern void tmc2660_writeInt(uint8 motor, uint8 address, int value);
extern uint32 tmc2660_readInt(uint8 motor, uint8 address);
extern void tmc2660_readWrite(uint8 motor, uint32 value);
//extern void tmc2660_setField(uint8 motor, uint8 address, uint32 clearMask, uint32 field);
// <= SPI wrapper

static void standStillCurrentLimitation(TMC2660TypeDef *TMC2660)
{ // mark if current should be reduced in stand still if too high
	static uint32 errorTimer = 0;

	// check the standstill flag
	if(TMC2660_GET_STST(tmc2660_readInt(0, TMC2660_RESPONSE_LATEST)))
	{
		// check if current reduction is neccessary
		if(TMC2660->runCurrentScale > TMC2660->standStillCurrentScale)
		{
			TMC2660->isStandStillOverCurrent = 1;

			// count timeout
			if(errorTimer++ > TMC2660->standStillTimeout/10)
			{
				// set current limitation flag
				TMC2660->isStandStillCurrentLimit = 1;
				errorTimer = 0;
			}
			return;
		}
	}

	// No standstill or overcurrent -> reset flags & error timer
	TMC2660->isStandStillOverCurrent  = 0;
	TMC2660->isStandStillCurrentLimit = 0;
	errorTimer = 0;
}

static void continousSync(ConfigurationTypeDef *TMC2660_config)
{ // refreshes settings to prevent chip from loosing settings on brownout
	static uint8 write  = 0;
	static uint8 read   = 0;
	static uint8 rdsel  = 0;

	// rotational reading all replys to keep values up to date
	uint32 value, drvConf;

	// additional reading to keep all replies up to date
	value = drvConf = tmc2660_readInt(0, TMC2660_WRITE_BIT | TMC2660_DRVCONF);  // buffer value amd  drvConf to write back later
	value &= ~TMC2660_SET_RDSEL(-1);                                        // clear RDSEL bits
	value |= TMC2660_SET_RDSEL(rdsel % 3);                                  // clear set rdsel
	tmc2660_readWrite(0, value);
	tmc2660_readWrite(0, drvConf);

	// determine next read address
	read = (read + 1) % 3;

	// write settings from shadow register to chip.
	//readWrite(TMC2660_config->shadowRegister[TMC2660_WRITE | write]);
	tmc2660_readWrite(0, TMC2660_config->shadowRegister[TMC2660_WRITE_BIT | write]);

	// determine next write address - skip unused addresses
	write = (write == TMC2660_DRVCTRL) ? TMC2660_CHOPCONF : ((write + 1) % TMC2660_REGISTER_COUNT);
}

void tmc2660_initConfig(TMC2660TypeDef *tmc2660)
{
	tmc2660->velocity                  = 0;
	tmc2660->oldTick                   = 0;
	tmc2660->oldX                      = 0;
	tmc2660->continuousModeEnable      = 0;
	tmc2660->isStandStillCurrentLimit  = 0;
	tmc2660->isStandStillOverCurrent   = 0;
	tmc2660->runCurrentScale           = 0;
	tmc2660->coolStepActiveValue       = 0;
	tmc2660->coolStepInactiveValue     = 0;
	tmc2660->coolStepThreshold         = 0;
	tmc2660->standStillCurrentScale    = 0;
	tmc2660->standStillTimeout         = 0;

	int i;
	for(i = 0; i < TMC2660_REGISTER_COUNT; i++)
	{
		tmc2660->registerAccess[i]      = tmc2660_defaultRegisterAccess[i];
		tmc2660->registerResetState[i]  = tmc2660_defaultRegisterResetState[i];
	}
}

// Currently unused, we write the whole configuration as part of the reset/restore functions
void tmc2660_writeConfiguration(TMC2660TypeDef *tmc2660, ConfigurationTypeDef *TMC2660_config)
{
	// write one writeable register at a time - backwards to hit DRVCONF before DRVCTRL
	UNUSED(tmc2660);
	UNUSED(TMC2660_config);

	//uint8 *ptr = &TMC2660_config->configIndex;
	//const int32 *settings = (TMC2660_config->state == CONFIG_RESTORE) ? TMC2660_config->shadowRegister : tmc2660->registerResetState;

	//while((*ptr >= 0) && !IS_WRITEABLE(tmc2660->registerAccess[*ptr]))
		//(*ptr)--;

	//if(*ptr >= 0)
	//{
		//tmc2660_writeInt(0, *ptr, settings[*ptr]);
		//(*ptr)--;
	//}
	//else
	//{
		//TMC2660_config->state = CONFIG_READY;
	//}
}

void tmc2660_periodicJob(u8 motor, uint32 tick, TMC2660TypeDef *tmc2660, ConfigurationTypeDef *TMC2660_config)
{
	UNUSED(motor);

	if(tick - tmc2660->oldTick >= 10)
	{
		standStillCurrentLimitation(tmc2660);
		tmc2660->oldTick = tick;
	}

	if(tmc2660->continuousModeEnable)
	{ // continuously write settings to chip and rotate through all reply types to keep data up to date
		continousSync(TMC2660_config);
	}
}

uint8 tmc2660_reset(TMC2660TypeDef *TMC2660, ConfigurationTypeDef *TMC2660_config)
{
	UNUSED(TMC2660_config);

	tmc2660_writeInt(0, TMC2660_DRVCONF,  TMC2660->registerResetState[TMC2660_DRVCONF]);
	tmc2660_writeInt(0, TMC2660_DRVCTRL,  TMC2660->registerResetState[TMC2660_DRVCTRL]);
	tmc2660_writeInt(0, TMC2660_CHOPCONF, TMC2660->registerResetState[TMC2660_CHOPCONF]);
	tmc2660_writeInt(0, TMC2660_SMARTEN,  TMC2660->registerResetState[TMC2660_SMARTEN]);
	tmc2660_writeInt(0, TMC2660_SGCSCONF, TMC2660->registerResetState[TMC2660_SGCSCONF]);

	return 1;
}

uint8 tmc2660_restore(ConfigurationTypeDef *TMC2660_config)
{
	tmc2660_writeInt(0, TMC2660_DRVCONF,  TMC2660_config->shadowRegister[TMC2660_DRVCONF | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_DRVCTRL,  TMC2660_config->shadowRegister[TMC2660_DRVCTRL | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_CHOPCONF, TMC2660_config->shadowRegister[TMC2660_CHOPCONF | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_SMARTEN,  TMC2660_config->shadowRegister[TMC2660_SMARTEN | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_SGCSCONF, TMC2660_config->shadowRegister[TMC2660_SGCSCONF | TMC2660_WRITE_BIT]);

	return 1;
}
