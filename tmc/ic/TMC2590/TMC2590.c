/*
 * TMC2590.c
 *
 *  Created on: 09.01.2019
 *      Author: LK
 */

#include "TMC2590.h"

// => SPI wrapper
extern void tmc2590_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

static void continousSync(TMC2590TypeDef *tmc2590);
static void readWrite(TMC2590TypeDef *tmc2590, uint32_t value);
static void readImmediately(TMC2590TypeDef *tmc2590, uint8_t rdsel);

static void standStillCurrentLimitation(TMC2590TypeDef *TMC2590)
{ // mark if current should be reduced in stand still if too high
	static uint32_t errorTimer = 0;

	// check the standstill flag
	if(TMC2590_GET_STST(tmc2590_readInt(0, TMC2590_RESPONSE_LATEST)))
	{
		// check if current reduction is neccessary
		if(TMC2590->runCurrentScale > TMC2590->standStillCurrentScale)
		{
			TMC2590->isStandStillOverCurrent = 1;

			// count timeout
			if(errorTimer++ > TMC2590->standStillTimeout/10)
			{
				// set current limitation flag
				TMC2590->isStandStillCurrentLimit = 1;
				errorTimer = 0;
			}
			return;
		}
	}

	// No standstill or overcurrent -> reset flags & error timer
	TMC2590->isStandStillOverCurrent  = 0;
	TMC2590->isStandStillCurrentLimit = 0;
	errorTimer = 0;
}

static void continousSync(TMC2590TypeDef *tmc2590)
{ // refreshes settings to prevent chip from loosing settings on brownout
	static uint8_t write  = 0;
	static uint8_t read   = 0;
	static uint8_t rdsel  = 0;

	// rotational reading all replys to keep values up to date
	uint32_t value, drvConf;

	// additional reading to keep all replies up to date
	value = drvConf = tmc2590_readInt(0, TMC2590_WRITE_BIT | TMC2590_DRVCONF);  // buffer value amd  drvConf to write back later
	value &= ~TMC2590_SET_RDSEL(-1);                                        // clear RDSEL bits
	value |= TMC2590_SET_RDSEL(rdsel % 3);                                  // clear set rdsel
	readWrite(tmc2590, value);
	readWrite(tmc2590, drvConf);

	// determine next read address
	read = (read + 1) % 3;

	// write settings from shadow register to chip.
	//readWrite(TMC2590_config->shadowRegister[TMC2590_WRITE_BIT | write]);
	readWrite(tmc2590, tmc2590->config->shadowRegister[TMC2590_WRITE_BIT | write]);

	// determine next write address - skip unused addresses
	write = (write == TMC2590_DRVCTRL) ? TMC2590_CHOPCONF : ((write + 1) % TMC2590_REGISTER_COUNT);
}

static void readWrite(TMC2590TypeDef *tmc2590, uint32_t value)
{	// sending data (value) via spi to TMC262, coping written and received data to shadow register
	static uint8_t rdsel = 0; // number of expected read response

	uint8_t data[] = { BYTE(value, 2), BYTE(value, 1), BYTE(value, 0) };

	tmc2590_readWriteArray(tmc2590->config->channel, &data[0], 3);

	tmc2590->config->shadowRegister[rdsel] = _8_32(data[0], data[1], data[2], 0) >> 12;
	tmc2590->config->shadowRegister[TMC2590_RESPONSE_LATEST] = tmc2590->config->shadowRegister[rdsel];

// set virtual read address for next reply given by RDSEL, can only change by setting RDSEL in DRVCONF
	if(TMC2590_GET_ADDRESS(value) == TMC2590_DRVCONF)
		rdsel = TMC2590_GET_RDSEL(value);

// write store written value to shadow register
	tmc2590->config->shadowRegister[TMC2590_GET_ADDRESS(value)] = value;
}

static void readImmediately(TMC2590TypeDef *tmc2590, uint8_t rdsel)
{ // sets desired reply in DRVCONF register, resets it to previous settings whilst reading desired reply
	uint32_t value, drvConf;

// additional reading to keep all replies up to date

	value = tmc2590_readInt(tmc2590, TMC2590_WRITE_BIT | TMC2590_DRVCONF);  // buffer value amd  drvConf to write back later
	drvConf = value;
	value &= ~TMC2590_SET_RDSEL(-1);                              // clear RDSEL bits
	value |= TMC2590_SET_RDSEL(rdsel%3);                          // set rdsel
	readWrite(tmc2590, value);                                    // write to chip and readout reply
	readWrite(tmc2590, drvConf);
}

void tmc2590_writeInt(TMC2590TypeDef *tmc2590, uint8_t address, int32_t value)
{
	value = TMC2590_VALUE(value);
	tmc2590->config->shadowRegister[TMC_ADDRESS(address) | TMC2590_WRITE_BIT] = value;
	if(!tmc2590->continuousModeEnable)
		readWrite(tmc2590, value);
}

uint32_t tmc2590_readInt(TMC2590TypeDef *tmc2590, uint8_t address)
{
	if(!tmc2590->continuousModeEnable && !(address & TMC2590_WRITE_BIT))
		readImmediately(tmc2590, address);

	return tmc2590->config->shadowRegister[TMC_ADDRESS(address)];
}

void tmc2590_init(TMC2590TypeDef *tmc2590, uint8_t channel, ConfigurationTypeDef *tmc2590_config, const int32_t *registerResetState)
{
	tmc2590->config                    = tmc2590_config;
	tmc2590->velocity                  = 0;
	tmc2590->oldTick                   = 0;
	tmc2590->oldX                      = 0;
	tmc2590->continuousModeEnable      = 0;
	tmc2590->isStandStillCurrentLimit  = 0;
	tmc2590->isStandStillOverCurrent   = 0;
	tmc2590->runCurrentScale           = 7;
	tmc2590->coolStepActiveValue       = 0;
	tmc2590->coolStepInactiveValue     = 0;
	tmc2590->coolStepThreshold         = 0;
	tmc2590->standStillCurrentScale    = 3;
	tmc2590->standStillTimeout         = 0;

	tmc2590->config->callback     = NULL;
	tmc2590->config->channel      = channel;
	tmc2590->config->configIndex  = 0;
	tmc2590->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC2590_REGISTER_COUNT; i++)
	{
		tmc2590->registerAccess[i]      = tmc2590_defaultRegisterAccess[i];
		tmc2590->registerResetState[i]  = registerResetState[i];
	}
}

void tmc2590_periodicJob(TMC2590TypeDef *tmc2590, uint32_t tick)
{
	if(tmc2590->continuousModeEnable)
	{ // continuously write settings to chip and rotate through all reply types to keep data up to date
		continousSync(tmc2590);
		if(tick - tmc2590->oldTick >= 10)
		{
			standStillCurrentLimitation(tmc2590);
			tmc2590->oldTick = tick;
		}
	}
}

// Currently unused, we write the whole configuration as part of the reset/restore functions
void tmc2590_writeConfiguration(TMC2590TypeDef *tmc2590, ConfigurationTypeDef *TMC2590_config)
{
	// write one writeable register at a time - backwards to hit DRVCONF before DRVCTRL
	UNUSED(tmc2590);
	UNUSED(TMC2590_config);

	//uint8_t *ptr = &TMC2590_config->configIndex;
	//const int32_t *settings = (TMC2590_config->state == CONFIG_RESTORE) ? TMC2590_config->shadowRegister : tmc2590->registerResetState;

	//while((*ptr >= 0) && !IS_WRITEABLE(tmc2590->registerAccess[*ptr]))
		//(*ptr)--;

	//if(*ptr >= 0)
	//{
		//tmc2590_writeInt(0, *ptr, settings[*ptr]);
		//(*ptr)--;
	//}
	//else
	//{
		//TMC2590_config->state = CONFIG_READY;
	//}
}

uint8_t tmc2590_reset(TMC2590TypeDef *tmc2590)
{
	tmc2590_writeInt(tmc2590, TMC2590_DRVCONF,  tmc2590->registerResetState[TMC2590_DRVCONF]);
	tmc2590_writeInt(tmc2590, TMC2590_DRVCTRL,  tmc2590->registerResetState[TMC2590_DRVCTRL]);
	tmc2590_writeInt(tmc2590, TMC2590_CHOPCONF, tmc2590->registerResetState[TMC2590_CHOPCONF]);
	tmc2590_writeInt(tmc2590, TMC2590_SMARTEN,  tmc2590->registerResetState[TMC2590_SMARTEN]);
	tmc2590_writeInt(tmc2590, TMC2590_SGCSCONF, tmc2590->registerResetState[TMC2590_SGCSCONF]);

	return 1;
}

uint8_t tmc2590_restore(TMC2590TypeDef *tmc2590)
{
	tmc2590_writeInt(tmc2590, TMC2590_DRVCONF,  tmc2590->config->shadowRegister[TMC2590_DRVCONF | TMC2590_WRITE_BIT]);
	tmc2590_writeInt(tmc2590, TMC2590_DRVCTRL,  tmc2590->config->shadowRegister[TMC2590_DRVCTRL | TMC2590_WRITE_BIT]);
	tmc2590_writeInt(tmc2590, TMC2590_CHOPCONF, tmc2590->config->shadowRegister[TMC2590_CHOPCONF | TMC2590_WRITE_BIT]);
	tmc2590_writeInt(tmc2590, TMC2590_SMARTEN,  tmc2590->config->shadowRegister[TMC2590_SMARTEN | TMC2590_WRITE_BIT]);
	tmc2590_writeInt(tmc2590, TMC2590_SGCSCONF, tmc2590->config->shadowRegister[TMC2590_SGCSCONF | TMC2590_WRITE_BIT]);

	return 1;
}
