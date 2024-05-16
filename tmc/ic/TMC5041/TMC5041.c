/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5041.h"

TMC5041TypeDef TMC5041;

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5041_readRegister(uint16_t icID, uint8_t address)
{
		return readRegisterSPI(icID, address);
		// ToDo: Error handling
}

void tmc5041_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
		writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(TMC5041.registerAccess[address]))
		return TMC5041.config->shadowRegister[address];

	// clear write bit
	data[0] = address & TMC5041_ADDRESS_MASK;

	// Send the read request
	tmc5041_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC5041_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc5041_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5041_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5041_readWriteSPI(icID, &data[0], sizeof(data));

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	TMC5041.config->shadowRegister[address] = value;
	TMC5041.registerAccess[address] |= TMC_ACCESS_DIRTY;
}

/*
void tmc5041_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5041_MOTORS)
		return;

	tmc5041_writeRegister(icID, TMC5041_VMAX(motor), (velocity >= 0)? velocity : -velocity);
	field_write(icID, TMC5041_RAMPMODE_FIELD(motor), (velocity >= 0) ? TMC5041_MODE_VELPOS : TMC5041_MODE_VELNEG);
}

*/

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/


// => SPI wrapper
extern void tmc5041_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

void tmc5041_writeDatagram(TMC5041TypeDef *tmc5041, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = {address | TMC5041_WRITE_BIT, x1, x2, x3, x4 };
	tmc5041_readWriteArray(tmc5041->config->channel, &data[0], 5);

	int32_t value = ((uint32_t)x1 << 24) | ((uint32_t)x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc5041->config->shadowRegister[address] = value;
	tmc5041->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc5041_writeInt(TMC5041TypeDef *tmc5041, uint8_t address, int32_t value)
{
	tmc5041_writeDatagram(tmc5041, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32_t tmc5041_readInt(TMC5041TypeDef *tmc5041, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc5041->registerAccess[address]))
		return tmc5041->config->shadowRegister[address];

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc5041_readWriteArray(tmc5041->config->channel, &data[0], 5);

	data[0] = address;
	tmc5041_readWriteArray(tmc5041->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

void tmc5041_init(TMC5041TypeDef *tmc5041, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc5041->velocity[0]      = 0;
	tmc5041->velocity[1]      = 0;
	tmc5041->oldTick          = 0;
	tmc5041->oldX[0]          = 0;
	tmc5041->oldX[1]          = 0;
	tmc5041->vMaxModified[0]  = false;
	tmc5041->vMaxModified[1]  = false;

	tmc5041->config               = config;
	tmc5041->config->callback     = NULL;
	tmc5041->config->channel      = channel;
	tmc5041->config->configIndex  = 0;
	tmc5041->config->state        = CONFIG_READY;

	int32_t i;
	for(i = 0; i < TMC5041_REGISTER_COUNT; i++)
	{
		tmc5041->registerAccess[i]      = tmc5041_defaultRegisterAccess[i];
		tmc5041->registerResetState[i]  = registerResetState[i];
	}
}

static void tmc5041_writeConfiguration(TMC5041TypeDef *tmc5041)
{
	uint8_t *ptr = &tmc5041->config->configIndex;
	const int32_t *settings = (tmc5041->config->state == CONFIG_RESTORE) ? tmc5041->config->shadowRegister : tmc5041->registerResetState;

	while((*ptr < TMC5041_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5041->registerAccess[*ptr]))
		(*ptr)++;

	if(*ptr < TMC5041_REGISTER_COUNT)
	{
		tmc5041_writeRegister(tmc5041, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		tmc5041->config->state = CONFIG_READY;
	}
}

void tmc5041_periodicJob(TMC5041TypeDef *tmc5041, uint32_t tick)
{
	int32_t xActual;
	uint32_t tickDiff;

	if(tmc5041->config->state != CONFIG_READY)
	{
		tmc5041_writeConfiguration(tmc5041);
		return;
	}

	if((tickDiff = tick - tmc5041->oldTick) >= 5)
	{
		int32_t i;
		for (i = 0; i < TMC5041_MOTORS; i++)
		{
			xActual = tmc5041_readRegister(tmc5041, TMC5041_XACTUAL(i));
			tmc5041->config->shadowRegister[TMC5041_XACTUAL(i)] = xActual;
			tmc5041->velocity[i] = (int32_t) ((float) (abs(xActual-tmc5041->oldX[i]) / (float) tickDiff) * (float) 1048.576);
			tmc5041->oldX[i] = xActual;
		}
		tmc5041->oldTick = tick;
	}
}

uint8_t tmc5041_reset(TMC5041TypeDef *tmc5041)
{
	if(tmc5041->config->state != CONFIG_READY)
		return 0;

	tmc5041->config->state        = CONFIG_RESET;
	tmc5041->config->configIndex  = 0;

	return 1;
}

uint8_t tmc5041_restore(TMC5041TypeDef *tmc5041)
{
	if(tmc5041->config->state != CONFIG_READY)
		return 0;

	tmc5041->config->state        = CONFIG_RESTORE;
	tmc5041->config->configIndex  = 0;

	return 1;
}
