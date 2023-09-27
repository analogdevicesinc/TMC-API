/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2590.h"

// => SPI wrapper
extern void tmc2590_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

static void continousSync(TMC2590TypeDef *tmc2590);
static void readWrite(TMC2590TypeDef *tmc2590, uint32_t value);
static void readImmediately(TMC2590TypeDef *tmc2590, uint8_t rdsel);

static void standStillCurrentLimitation(TMC2590TypeDef *tmc2590, uint32_t tick)
{
	// Check if the motor is in standstill
	if (!TMC2590_GET_STST(tmc2590_readInt(tmc2590, TMC2590_RESPONSE_LATEST)))
	{
		// The standStillTick variable holds the tick counter where a standstill
		// started.
		// Not standing still -> standstill tick equals tick -> Time since
		// standstill == 0
		tmc2590->standStillTick = tick;
	}

	// Check if standstill timeout has been reached
	if (tick - tmc2590->standStillTick > tmc2590->standStillTimeout)
	{
		tmc2590->isStandStillCurrent = 1;
		// Change to standstill current
		TMC2590_FIELD_WRITE(tmc2590, TMC2590_SGCSCONF, TMC2590_CS_MASK, TMC2590_CS_SHIFT, tmc2590->standStillCurrentScale);
	}
	else
	{
		tmc2590->isStandStillCurrent = 0;
		// Change to run current
		TMC2590_FIELD_WRITE(tmc2590, TMC2590_SGCSCONF, TMC2590_CS_MASK, TMC2590_CS_SHIFT, tmc2590->runCurrentScale);
	}
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

	// Write settings from shadow register to chip.
	readWrite(tmc2590, tmc2590->config->shadowRegister[TMC2590_WRITE_BIT | write]);

	// Determine next write address while skipping unused addresses
	if (write == TMC2590_DRVCTRL)
	{
		// Skip over the unused addresses between DRVCTRL and CHOPCONF
		write = TMC2590_CHOPCONF;
	}
	else
	{
		// Increase the address
		write = (write + 1) & TMC2590_REGISTER_COUNT;
	}
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
	tmc2590->config               = tmc2590_config;
	tmc2590->config->callback     = NULL;
	tmc2590->config->channel      = channel;
	tmc2590->config->configIndex  = 0;
	tmc2590->config->state        = CONFIG_READY;

	tmc2590->continuousModeEnable      = 0;

	tmc2590->coolStepActiveValue       = 0;
	tmc2590->coolStepInactiveValue     = 0;
	tmc2590->coolStepThreshold         = 0;

	tmc2590->isStandStillCurrent       = 0;
	tmc2590->runCurrentScale           = 7;
	tmc2590->standStillCurrentScale    = 3;
	tmc2590->standStillTimeout         = 0;

	for(size_t i = 0; i < TMC2590_REGISTER_COUNT; i++)
	{
		tmc2590->registerAccess[i]      = tmc2590_defaultRegisterAccess[i];
		tmc2590->registerResetState[i]  = registerResetState[i];
	}
}

void tmc2590_periodicJob(TMC2590TypeDef *tmc2590, uint32_t tick)
{
	standStillCurrentLimitation(tmc2590, tick);

	if(tmc2590->continuousModeEnable)
	{ // continuously write settings to chip and rotate through all reply types to keep data up to date
		continousSync(tmc2590);
	}
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
