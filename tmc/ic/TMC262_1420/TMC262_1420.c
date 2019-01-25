/*
 * TMC262_1420.c
 *
 *  Created on: 11.07.2017
 *      Author: LK
 */

#include "../TMC262_1420/TMC262_1420.h"

// => SPI wrapper
extern void tmc262_1420_readWriteArray(uint8 channel, uint8 *data, size_t length);
//extern void tmc262_1420_writeInt(uint8 motor, uint8 address, int value);
//extern uint32 tmc262_1420_readInt(uint8 motor, uint8 address);
//extern void tmc262_1420_readWrite(uint8 motor, uint32 value);
//extern void tmc262_1420_setField(uint8 motor, uint8 address, uint32 clearMask, uint32 field);
// <= SPI wrapper

static void continousSync(TMC262_1420TypeDef *tmc262_1420);
static void readWrite(TMC262_1420TypeDef *tmc262_1420, uint32 value);
static void readImmediately(TMC262_1420TypeDef *tmc262_1420, uint8 rdsel);

static void standStillCurrentLimitation(TMC262_1420TypeDef *TMC262_1420)
{ // mark if current should be reduced in stand still if too high
	static uint32 errorTimer = 0;

	// check the standstill flag
	if(TMC262_1420_GET_STST(tmc262_1420_readInt(0, TMC262_1420_RESPONSE_LATEST)))
	{
		// check if current reduction is neccessary
		if(TMC262_1420->runCurrentScale > TMC262_1420->standStillCurrentScale)
		{
			TMC262_1420->isStandStillOverCurrent = 1;

			// count timeout
			if(errorTimer++ > TMC262_1420->standStillTimeout/10)
			{
				// set current limitation flag
				TMC262_1420->isStandStillCurrentLimit = 1;
				errorTimer = 0;
			}
			return;
		}
	}

	// No standstill or overcurrent -> reset flags & error timer
	TMC262_1420->isStandStillOverCurrent  = 0;
	TMC262_1420->isStandStillCurrentLimit = 0;
	errorTimer = 0;
}

static void continousSync(TMC262_1420TypeDef *tmc262_1420)
{ // refreshes settings to prevent chip from loosing settings on brownout
	static uint8 write  = 0;
	static uint8 read   = 0;
	static uint8 rdsel  = 0;

	// rotational reading all replys to keep values up to date
	uint32 value, drvConf;

	// additional reading to keep all replies up to date
	value = drvConf = tmc262_1420_readInt(0, TMC262_1420_WRITE_BIT | TMC262_1420_DRVCONF);  // buffer value amd  drvConf to write back later
	value &= ~TMC262_1420_SET_RDSEL(-1);                                        // clear RDSEL bits
	value |= TMC262_1420_SET_RDSEL(rdsel % 3);                                  // clear set rdsel
	readWrite(tmc262_1420, value);
	readWrite(tmc262_1420, drvConf);

	// determine next read address
	read = (read + 1) % 3;

	// write settings from shadow register to chip.
	//readWrite(TMC262_1420_config->shadowRegister[TMC262_1420_WRITE_BIT | write]);
	readWrite(tmc262_1420, tmc262_1420->config->shadowRegister[TMC262_1420_WRITE_BIT | write]);

	// determine next write address - skip unused addresses
	write = (write == TMC262_1420_DRVCTRL) ? TMC262_1420_CHOPCONF : ((write + 1) % TMC262_1420_REGISTER_COUNT);
}

static void readWrite(TMC262_1420TypeDef *tmc262_1420, uint32 value)
{	// sending data (value) via spi to TMC262, coping written and received data to shadow register
	static uint8 rdsel = 0; // number of expected read response

	uint8 data[] = { BYTE(value, 2), BYTE(value, 1), BYTE(value, 0) };

	tmc262_1420_readWriteArray(tmc262_1420->config->channel, &data[0], 3);

	tmc262_1420->config->shadowRegister[rdsel] = _8_32(data[0], data[1], data[2], 0) >> 12;
	tmc262_1420->config->shadowRegister[TMC262_1420_RESPONSE_LATEST] = tmc262_1420->config->shadowRegister[rdsel];

// set virtual read address for next reply given by RDSEL, can only change by setting RDSEL in DRVCONF
	if(TMC262_1420_GET_ADDRESS(value) == TMC262_1420_DRVCONF)
		rdsel = TMC262_1420_GET_RDSEL(value);

// write store written value to shadow register
	tmc262_1420->config->shadowRegister[TMC262_1420_GET_ADDRESS(value)] = value;
}

static void readImmediately(TMC262_1420TypeDef *tmc262_1420, uint8 rdsel)
{ // sets desired reply in DRVCONF register, resets it to previous settings whilst reading desired reply
	uint32 value, drvConf;

// additional reading to keep all replies up to date

	value = tmc262_1420_readInt(tmc262_1420, TMC262_1420_WRITE_BIT | TMC262_1420_DRVCONF);  // buffer value amd  drvConf to write back later
	drvConf = value;
	value &= ~TMC262_1420_SET_RDSEL(-1);                              // clear RDSEL bits
	value |= TMC262_1420_SET_RDSEL(rdsel%3);                          // set rdsel
	readWrite(tmc262_1420, value);                                    // write to chip and readout reply
	readWrite(tmc262_1420, drvConf);
}

void tmc262_1420_writeInt(TMC262_1420TypeDef *tmc262_1420, uint8 address, int32 value)
{
	value = TMC262_1420_VALUE(value);
	tmc262_1420->config->shadowRegister[TMC_ADDRESS(address) | TMC262_1420_WRITE_BIT] = value;
	if(!tmc262_1420->continuousModeEnable)
		readWrite(tmc262_1420, value);
}

uint32 tmc262_1420_readInt(TMC262_1420TypeDef *tmc262_1420, uint8 address)
{
	if(!tmc262_1420->continuousModeEnable && !(address & TMC262_1420_WRITE_BIT))
		readImmediately(tmc262_1420, address);

	return tmc262_1420->config->shadowRegister[TMC_ADDRESS(address)];
}

void tmc262_1420_init(TMC262_1420TypeDef *tmc262_1420, uint8 channel, ConfigurationTypeDef *tmc262_1420_config, const int32 *registerResetState)
{
	tmc262_1420->config                    = tmc262_1420_config;
	tmc262_1420->velocity                  = 0;
	tmc262_1420->oldTick                   = 0;
	tmc262_1420->oldX                      = 0;
	tmc262_1420->continuousModeEnable      = 0;
	tmc262_1420->isStandStillCurrentLimit  = 0;
	tmc262_1420->isStandStillOverCurrent   = 0;
	tmc262_1420->runCurrentScale           = 0;
	tmc262_1420->coolStepActiveValue       = 0;
	tmc262_1420->coolStepInactiveValue     = 0;
	tmc262_1420->coolStepThreshold         = 0;
	tmc262_1420->standStillCurrentScale    = 0;
	tmc262_1420->standStillTimeout         = 0;

	tmc262_1420->config->callback     = NULL;
	tmc262_1420->config->channel      = channel;
	tmc262_1420->config->configIndex  = 0;
	tmc262_1420->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC262_1420_REGISTER_COUNT; i++)
	{
		tmc262_1420->registerAccess[i]      = tmc262_1420_defaultRegisterAccess[i];
		tmc262_1420->registerResetState[i]  = registerResetState[i];
	}
}

void tmc262_1420_periodicJob(TMC262_1420TypeDef *tmc262_1420, uint32 tick)
{
	if(tmc262_1420->continuousModeEnable)
	{ // continuously write settings to chip and rotate through all reply types to keep data up to date
		continousSync(tmc262_1420);
		if(tick - tmc262_1420->oldTick >= 10)
		{
			standStillCurrentLimitation(tmc262_1420);
			tmc262_1420->oldTick = tick;
		}
	}
}

// Currently unused, we write the whole configuration as part of the reset/restore functions
void tmc262_1420_writeConfiguration(TMC262_1420TypeDef *tmc262_1420, ConfigurationTypeDef *TMC262_1420_config)
{
	// write one writeable register at a time - backwards to hit DRVCONF before DRVCTRL
	UNUSED(tmc262_1420);
	UNUSED(TMC262_1420_config);

	//uint8 *ptr = &TMC262_1420_config->configIndex;
	//const int32 *settings = (TMC262_1420_config->state == CONFIG_RESTORE) ? TMC262_1420_config->shadowRegister : tmc262_1420->registerResetState;

	//while((*ptr >= 0) && !IS_WRITEABLE(tmc262_1420->registerAccess[*ptr]))
		//(*ptr)--;

	//if(*ptr >= 0)
	//{
		//tmc262_1420_writeInt(0, *ptr, settings[*ptr]);
		//(*ptr)--;
	//}
	//else
	//{
		//TMC262_1420_config->state = CONFIG_READY;
	//}
}

uint8 tmc262_1420_reset(TMC262_1420TypeDef *tmc262_1420)
{
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_DRVCONF,  tmc262_1420->registerResetState[TMC262_1420_DRVCONF]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_DRVCTRL,  tmc262_1420->registerResetState[TMC262_1420_DRVCTRL]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_CHOPCONF, tmc262_1420->registerResetState[TMC262_1420_CHOPCONF]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_SMARTEN,  tmc262_1420->registerResetState[TMC262_1420_SMARTEN]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_SGCSCONF, tmc262_1420->registerResetState[TMC262_1420_SGCSCONF]);

	return 1;
}

uint8 tmc262_1420_restore(TMC262_1420TypeDef *tmc262_1420)
{
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_DRVCONF,  tmc262_1420->config->shadowRegister[TMC262_1420_DRVCONF | TMC262_1420_WRITE_BIT]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_DRVCTRL,  tmc262_1420->config->shadowRegister[TMC262_1420_DRVCTRL | TMC262_1420_WRITE_BIT]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_CHOPCONF, tmc262_1420->config->shadowRegister[TMC262_1420_CHOPCONF | TMC262_1420_WRITE_BIT]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_SMARTEN,  tmc262_1420->config->shadowRegister[TMC262_1420_SMARTEN | TMC262_1420_WRITE_BIT]);
	tmc262_1420_writeInt(tmc262_1420, TMC262_1420_SGCSCONF, tmc262_1420->config->shadowRegister[TMC262_1420_SGCSCONF | TMC262_1420_WRITE_BIT]);

	return 1;
}
