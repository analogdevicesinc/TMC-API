/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2660.h"
//-----------------------------------NEW CODE----------------------------------------------//
TMC2660TypeDef TMC2660;
#define DEFAULT_ICID 0

static void readWrite(uint32_t value);
static void readImmediately(uint8_t rdsel);

void readWrite(uint32_t datagram)
{
    uint8_t data[3]= {0};
    uint32_t reply;
    static uint8_t rdsel = 0;

    data[0] = datagram >> 16;
    data[1] = datagram >> 8;
    data[2] = datagram >> 0;

    // send 24 bytes of data and receive reply
    reply = tmc2660_readWriteSPI(DEFAULT_ICID, data[0], 0);
    reply <<= 8;
    reply = tmc2660_readWriteSPI(DEFAULT_ICID, data[1], 0);
    reply <<= 8;
    reply = tmc2660_readWriteSPI(DEFAULT_ICID, data[2], 1);
    reply >>= 4;

    // write value to response shadow register
    TMC2660.config->shadowRegister[rdsel] = reply;

    // Store the latest response value to extract status bits in tmc2660_getStatusBits()
    TMC2660.config->shadowRegister[TMC2660_RESPONSE_LATEST] = reply;

    // write value to shadow register
    TMC2660.config->shadowRegister[TMC2660_GET_ADDRESS(datagram) | TMC2660_WRITE_BIT ] = datagram;

    // write value to response shadow register
    if(TMC2660_GET_ADDRESS(datagram) == TMC2660_DRVCONF)
        rdsel = TMC2660_GET_RDSEL(datagram);
}

void readImmediately(uint8_t rdsel)
{
    // sets desired reply in DRVCONF register, resets it to previous settings whilst reading desired reply
    uint32_t value, drvConf;

    // additional reading to keep all replies up to date
    value = tmc2660_readInt(0, TMC2660_DRVCONF);                  // buffer (value and drvConf) to write back later
    drvConf = value;
    value &= ~TMC2660_SET_RDSEL(-1);                              // clear RDSEL bits
    value |= TMC2660_SET_RDSEL(rdsel%3);                          // set rdsel
    readWrite(value);                                             // write to chip and readout reply
    readWrite(drvConf);                                           // write to chip and return desired reply
}

// => SPI wrapper
void tmc2660_writeInt(uint8_t motor, uint8_t address, int value)
{
    UNUSED(motor);
static void standStillCurrentLimitation(TMC2660TypeDef *TMC2660)
{ // mark if current should be reduced in stand still if too high
	static uint32_t errorTimer = 0;

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

    // Don't write to read-only registers
    if (!TMC2660_IS_WRITEONLY_REGISTER(address))
        return;
static void continousSync(ConfigurationTypeDef *TMC2660_config)
{ // refreshes settings to prevent chip from loosing settings on brownout
	static uint8_t write  = 0;
	static uint8_t read   = 0;
	static uint8_t rdsel  = 0;

	// rotational reading all replys to keep values up to date
	uint32_t value, drvConf;

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
    // tmc2660_writeDatagram(address, 0xFF & (value>>24), 0xFF & (value>>16), 0xFF & (value>>8), 0xFF & (value>>0));
    value &= 0x0FFFFF;

    // ANDing with 0x7F to avoid buffer overflow, Shadow register is 128 entries large
    TMC2660.config->shadowRegister[0x7F & address] = value;

    if(!TMC2660.continuousModeEnable)
        readWrite(TMC2660_DATAGRAM(address, value));
}

uint32_t tmc2660_readInt(uint8_t motor, uint8_t address)
void tmc2660_initConfig(TMC2660TypeDef *tmc2660)
{
    UNUSED(motor);

    if (TMC2660_IS_WRITEONLY_REGISTER(address))
    {
        // Write-only registers can only be read from cache
        return TMC2660.config->shadowRegister[0x7F & address];
    }

    if(!TMC2660.continuousModeEnable)
    {
        // Read the read-only register, refreshing the cache
        readImmediately(address);
    }

    // Return the read-only register from cache
    return TMC2660.config->shadowRegister[0x7F & address];
}

uint8_t tmc2660_getStatusBits()
{
    // Grab the status bits from the last request
    return TMC2660.config->shadowRegister[TMC2660_RESPONSE_LATEST] & TMC2660_STATUS_MASK; // Todo update rdsel register bits in the cache
	tmc2660->velocity                  = 0;
	tmc2660->oldTick                   = 0;
	tmc2660->oldX                      = 0;
	tmc2660->continuousModeEnable      = 0;
	tmc2660->isStandStillCurrentLimit  = 0;
	tmc2660->isStandStillOverCurrent   = 0;
	tmc2660->runCurrentScale           = 5;
	tmc2660->coolStepActiveValue       = 0;
	tmc2660->coolStepInactiveValue     = 0;
	tmc2660->coolStepThreshold         = 0;
	tmc2660->standStillCurrentScale    = 5;
	tmc2660->standStillTimeout         = 0;

	int32_t i;
	for(i = 0; i < TMC2660_REGISTER_COUNT; i++)
	{
		tmc2660->registerAccess[i]      = tmc2660_defaultRegisterAccess[i];
		tmc2660->registerResetState[i]  = tmc2660_defaultRegisterResetState[i];
	}
}

void tmc2660_readWrite(uint8_t motor, uint32_t value)
{
    UNUSED(motor);

    static uint8_t rdsel = 0; // number of expected read response

    // if SGCONF should be written, check whether stand still, or run current should be used
//  if(TMC2660_GET_ADDRESS(value) == TMC2660_SGCSCONF)
//  {
//      value &= ~TMC2660_SET_CS(-1); // clear CS field
//      value |= (TMC2660.isStandStillCurrentLimit) ?  TMC2660_SET_CS(TMC2660.standStillCurrentScale) : TMC2660_SET_CS(TMC2660.runCurrentScale); // set current
//  }

    // write value and read reply to shadow register
    TMC2660.config->shadowRegister[rdsel] = tmc2660_readWriteSPI(DEFAULT_ICID, value>>16, 0);
    TMC2660.config->shadowRegister[rdsel] <<= 8;
    TMC2660.config->shadowRegister[rdsel] |= tmc2660_readWriteSPI(DEFAULT_ICID, value>>8, 0);
    TMC2660.config->shadowRegister[rdsel] <<= 8;
    TMC2660.config->shadowRegister[rdsel] |= tmc2660_readWriteSPI(DEFAULT_ICID, value & 0xFF, 1);
    TMC2660.config->shadowRegister[rdsel] >>= 4;

    TMC2660.config->shadowRegister[TMC2660_RESPONSE_LATEST] = TMC2660.config->shadowRegister[rdsel]; // copy value to latest field
    // set virtual read address for next reply given by RDSEL, can only change by setting RDSEL in DRVCONF
    if(TMC2660_GET_ADDRESS(value) == TMC2660_DRVCONF)
        rdsel = TMC2660_GET_RDSEL(value);

    // write store written value to shadow register
    TMC2660.config->shadowRegister[TMC2660_GET_ADDRESS(value) | TMC2660_WRITE_BIT ] = value;
}
//------------------------------------------------------------NEW CODE-----------------------------------//

// Currently unused, we write the whole configuration as part of the reset/restore functions
void tmc2660_writeConfiguration(TMC2660TypeDef *tmc2660, ConfigurationTypeDef *TMC2660_config)
{
	// write one writeable register at a time - backwards to hit DRVCONF before DRVCTRL
	UNUSED(tmc2660);
	UNUSED(TMC2660_config);

	//uint8_t *ptr = &TMC2660.config->configIndex;
	//const int32_t *settings = (TMC2660.config->state == CONFIG_RESTORE) ? TMC2660.config->shadowRegister : tmc2660->registerResetState;

	//while((*ptr >= 0) && !IS_WRITEABLE(tmc2660->registerAccess[*ptr]))
		//(*ptr)--;

	//if(*ptr >= 0)
	//{
		//tmc2660_writeInt(0, *ptr, settings[*ptr]);
		//(*ptr)--;
	//}
	//else
	//{
		//TMC2660.config->state = CONFIG_READY;
	//}
}

void tmc2660_periodicJob(uint8_t motor, uint32_t tick, TMC2660TypeDef *tmc2660, ConfigurationTypeDef *TMC2660_config)
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

uint8_t tmc2660_reset(TMC2660TypeDef *TMC2660, ConfigurationTypeDef *TMC2660_config)
{
	UNUSED(TMC2660_config);

	tmc2660_writeInt(0, TMC2660_DRVCONF,  TMC2660->registerResetState[TMC2660_DRVCONF]);
	tmc2660_writeInt(0, TMC2660_DRVCTRL,  TMC2660->registerResetState[TMC2660_DRVCTRL]);
	tmc2660_writeInt(0, TMC2660_CHOPCONF, TMC2660->registerResetState[TMC2660_CHOPCONF]);
	tmc2660_writeInt(0, TMC2660_SMARTEN,  TMC2660->registerResetState[TMC2660_SMARTEN]);
	tmc2660_writeInt(0, TMC2660_SGCSCONF, TMC2660->registerResetState[TMC2660_SGCSCONF]);

	return 1;
}

uint8_t tmc2660_restore(ConfigurationTypeDef *TMC2660_config)
{
	tmc2660_writeInt(0, TMC2660_DRVCONF,  TMC2660_config->shadowRegister[TMC2660_DRVCONF | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_DRVCTRL,  TMC2660_config->shadowRegister[TMC2660_DRVCTRL | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_CHOPCONF, TMC2660_config->shadowRegister[TMC2660_CHOPCONF | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_SMARTEN,  TMC2660_config->shadowRegister[TMC2660_SMARTEN | TMC2660_WRITE_BIT]);
	tmc2660_writeInt(0, TMC2660_SGCSCONF, TMC2660_config->shadowRegister[TMC2660_SGCSCONF | TMC2660_WRITE_BIT]);

	return 1;
}
