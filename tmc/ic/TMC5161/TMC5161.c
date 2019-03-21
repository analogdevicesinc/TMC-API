/*
 * TMC5161.c
 *
 *  Created on: 13.06.2017
 *      Author: LK
 */

#include "TMC5161.h"

// => SPI wrapper
extern void tmc5161_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

void tmc5161_writeDatagram(TMC5161TypeDef *tmc5161, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC5161_WRITE_BIT, x1, x2, x3, x4 };
	tmc5161_readWriteArray(tmc5161->config->channel, &data[0], 5);

	int value = x1;
	value <<= 8;
	value |= x2;
	value <<= 8;
	value |= x3;
	value <<= 8;
	value |= x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc5161->config->shadowRegister[address] = value;
	tmc5161->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc5161_writeInt(TMC5161TypeDef *tmc5161, uint8_t address, int32_t value)
{
	tmc5161_writeDatagram(tmc5161, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32_t tmc5161_readInt(TMC5161TypeDef *tmc5161, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc5161->registerAccess[address]))
		return tmc5161->config->shadowRegister[address];

	uint8_t data[5];

	data[0] = address;
	tmc5161_readWriteArray(tmc5161->config->channel, &data[0], 5);

	data[0] = address;
	tmc5161_readWriteArray(tmc5161->config->channel, &data[0], 5);

	return _8_32(data[1], data[2], data[3], data[4]);
}

void tmc5161_init(TMC5161TypeDef *tmc5161, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc5161->velocity  = 0;
	tmc5161->oldTick   = 0;
	tmc5161->oldX      = 0;
	tmc5161->config    = config;

	tmc5161->config->callback     = NULL;
	tmc5161->config->channel      = channel;
	tmc5161->config->configIndex  = 0;
	tmc5161->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC5161_REGISTER_COUNT; i++)
	{
		tmc5161->registerAccess[i]      = tmc5161_defaultRegisterAccess[i];
		tmc5161->registerResetState[i]  = registerResetState[i];
	}
}

static void writeConfiguration(TMC5161TypeDef *tmc5161)
{
	uint8_t *ptr = &tmc5161->config->configIndex;
	const int32_t *settings;

	if(tmc5161->config->state == CONFIG_RESTORE)
	{
		settings = tmc5161->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC5161_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc5161->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc5161->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC5161_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc5161->registerAccess[*ptr]))
			(*ptr)++;

	}

	if(*ptr < TMC5161_REGISTER_COUNT)
	{
		tmc5161_writeInt(tmc5161, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc5161->config->callback)
		{
			((tmc5161_callback)tmc5161->config->callback)(tmc5161, tmc5161->config->state);
		}

		tmc5161->config->state = CONFIG_READY;
	}
}

void tmc5161_periodicJob(TMC5161TypeDef *tmc5161, uint32_t tick)
{
	if(tmc5161->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5161);
		return;
	}

	int XActual;
	uint32_t tickDiff;

	if((tickDiff = tick-tmc5161->oldTick) >= 5) // measured speed dx/dt
	{
		XActual = tmc5161_readInt(tmc5161, TMC5161_XACTUAL);
		tmc5161->velocity = (int) ((float32_t) ((XActual-tmc5161->oldX) / (float32_t) tickDiff) * (float32_t) 1048.576);

		tmc5161->oldX     = XActual;
		tmc5161->oldTick  = tick;
	}
}

uint8_t tmc5161_reset(TMC5161TypeDef *tmc5161)
{
	if(tmc5161->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits
	for(size_t i = 0; i < TMC5161_REGISTER_COUNT; i++)
		tmc5161->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc5161->config->state        = CONFIG_RESET;
	tmc5161->config->configIndex  = 0;

	return true;
}

uint8_t tmc5161_restore(TMC5161TypeDef *tmc5161)
{
	if(tmc5161->config->state != CONFIG_READY)
		return false;

	tmc5161->config->state        = CONFIG_RESTORE;
	tmc5161->config->configIndex  = 0;

	return true;
}

void tmc5161_setRegisterResetState(TMC5161TypeDef *tmc5161, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC5161_REGISTER_COUNT; i++)
		tmc5161->registerResetState[i] = resetState[i];
}

void tmc5161_setCallback(TMC5161TypeDef *tmc5130, tmc5161_callback callback)
{
	tmc5130->config->callback = (tmc_callback_config) callback;
}

void tmc5161_rotate(TMC5161TypeDef *tmc5161, int32_t velocity)
{
	// set absolute velocity, independent from direction
	tmc5161_writeInt(tmc5161, TMC5161_VMAX, abs(velocity));
	// signdedness defines velocity mode direction bit in rampmode register
	tmc5161_writeInt(tmc5161, TMC5161_RAMPMODE, (velocity >= 0) ? TMC5161_MODE_VELPOS : TMC5161_MODE_VELNEG);
}

void tmc5161_right(TMC5161TypeDef *tmc5161, uint32_t velocity)
{
	return tmc5161_rotate(tmc5161, velocity);
}

void tmc5161_left(TMC5161TypeDef *tmc5161, uint32_t velocity)
{
	return tmc5161_rotate(tmc5161, -velocity);
}

void tmc5161_stop(TMC5161TypeDef *tmc5161)
{
	return tmc5161_rotate(tmc5161, 0);
}

void tmc5161_moveTo(TMC5161TypeDef *tmc5161, int32_t position, uint32_t velocity)
{
	tmc5161_writeInt(tmc5161, TMC5161_RAMPMODE, TMC5161_MODE_POSITION);
	tmc5161_writeInt(tmc5161, TMC5161_VMAX, velocity); // Not written to register while in rampVelocity mode -> write copy when switching
	tmc5161_writeInt(tmc5161, TMC5161_XTARGET, position);
}

void tmc5161_moveBy(TMC5161TypeDef *tmc5161, int32_t *ticks, uint32_t velocity)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5161_readInt(tmc5161, TMC5161_XACTUAL);

	tmc5161_moveTo(tmc5161, *ticks, velocity);
}
