/*
 * TMC5130.c
 *
 *  Created on: 03.07.2017
 *      Author: LK
 */

#include "TMC5130.h"

// => SPI wrapper
// Send [length] bytes stored in the [data] array over SPI and overwrite [data]
// with the replies. data[0] is the first byte sent and received.
extern void tmc5130_readWriteArray(uint8 channel, uint8 *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc5130_writeDatagram(TMC5130TypeDef *tmc5130, uint8 address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	uint8 data[5] = { address | TMC5130_WRITE_BIT, x1, x2, x3, x4 };
	tmc5130_readWriteArray(tmc5130->config->channel, &data[0], 5);

	int32 value = (x1 << 24) | (x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc5130->config->shadowRegister[address] = value;
	tmc5130->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc5130_writeInt(TMC5130TypeDef *tmc5130, uint8 address, int32 value)
{
	tmc5130_writeDatagram(tmc5130, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32 tmc5130_readInt(TMC5130TypeDef *tmc5130, uint8 address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc5130->registerAccess[address]))
		return tmc5130->config->shadowRegister[address];

	uint8 data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc5130_readWriteArray(tmc5130->config->channel, &data[0], 5);

	data[0] = address;
	tmc5130_readWriteArray(tmc5130->config->channel, &data[0], 5);

	return (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
}

// Provide the init function with a channel index (sent back in the SPI callback), a pointer to a ConfigurationTypeDef struct
// and a pointer to a int32 array (size 128) holding the reset values that shall be used.
void tmc5130_init(TMC5130TypeDef *tmc5130, uint8 channel, ConfigurationTypeDef *tmc5130_config, const int32 *registerResetState)
{
	tmc5130->velocity  = 0;
	tmc5130->oldTick   = 0;
	tmc5130->oldX      = 0;
	tmc5130->config    = tmc5130_config;

	/*
	 * TODO: Config initialization
	 * We can either explicitly initialize in each IC's init respectively,
	 * or do that with a seperate function config_init where also the channel is set.
	 */
	tmc5130->config->callback     = NULL;
	tmc5130->config->channel      = channel;
	tmc5130->config->configIndex  = 0;
	tmc5130->config->state        = CONFIG_READY;

	for(size_t i = 0; i < TMC5130_REGISTER_COUNT; i++)
	{
		tmc5130->registerAccess[i]      = tmc5130_defaultRegisterAccess[i];
		tmc5130->registerResetState[i]  = registerResetState[i];
	}
}

// Fill the shadow registers of hardware preset non-readable registers
// Only needed if you want to read out those registers to display the value
// (e.g. for the TMCL IDE register browser)
void tmc5130_fillShadowRegisters(TMC5130TypeDef *tmc5130)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc5130_RegisterConstants) == 0)
		return;

	for(size_t i = 0, j = 0; i < TMC5130_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc5130->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc5130_RegisterConstants) && (tmc5130_RegisterConstants[j].address < i))
			j++;

		// If we have an entry for our current address, write the constant
		if(tmc5130_RegisterConstants[j].address == i)
			tmc5130->config->shadowRegister[i] = tmc5130_RegisterConstants[j].value;
	}
}

uint8 tmc5130_reset(TMC5130TypeDef *tmc5130)
{
	if(tmc5130->config->state != CONFIG_READY)
		return FALSE;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC5130_REGISTER_COUNT; i++)
	{
		tmc5130->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc5130->config->shadowRegister[i] = 0;
	}

	tmc5130->config->state        = CONFIG_RESET;
	tmc5130->config->configIndex  = 0;

	return TRUE;
}

uint8 tmc5130_restore(TMC5130TypeDef *tmc5130)
{
	if(tmc5130->config->state != CONFIG_READY)
		return FALSE;

	tmc5130->config->state        = CONFIG_RESTORE;
	tmc5130->config->configIndex  = 0;

	return TRUE;
}

void tmc5130_setRegisterResetState(TMC5130TypeDef *tmc5130, const int32 *resetState)
{
	for(size_t i = 0; i < TMC5130_REGISTER_COUNT; i++)
		tmc5130->registerResetState[i] = resetState[i];
}

void tmc5130_setCallback(TMC5130TypeDef *tmc5130, tmc5130_callback callback)
{
	tmc5130->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC5130TypeDef *tmc5130)
{
	uint8 *ptr = &tmc5130->config->configIndex;
	const int32 *settings;

	if(tmc5130->config->state == CONFIG_RESTORE)
	{
		settings = tmc5130->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC5130_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc5130->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc5130->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC5130_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc5130->registerAccess[*ptr]))
			(*ptr)++;

	}

	if(*ptr < TMC5130_REGISTER_COUNT)
	{
		tmc5130_writeInt(tmc5130, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc5130->config->callback)
		{
			((tmc5130_callback)tmc5130->config->callback)(tmc5130, tmc5130->config->state);
		}

		tmc5130->config->state = CONFIG_READY;
	}
}

void tmc5130_periodicJob(TMC5130TypeDef *tmc5130, uint32 tick)
{
	if(tmc5130->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5130);
		return;
	}

	int XActual;
	uint32 tickDiff;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5130->oldTick) >= 5)
	{
		XActual = tmc5130_readInt(tmc5130, TMC5130_XACTUAL);
		// ToDo CHECK 2: API Compatibility - write alternative algorithm w/o floating point? (LH)
		tmc5130->velocity = (uint32) ((f32) ((XActual - tmc5130->oldX) / (f32) tickDiff) * (f32) 1048.576);

		tmc5130->oldX     = XActual;
		tmc5130->oldTick  = tick;
	}
}

void tmc5130_rotate(TMC5130TypeDef *tmc5130, int32 velocity)
{
	// Set absolute velocity
	tmc5130_writeInt(tmc5130, TMC5130_VMAX, abs(velocity));
	// Set direction
	tmc5130_writeInt(tmc5130, TMC5130_RAMPMODE, (velocity >= 0) ? TMC5130_MODE_VELPOS : TMC5130_MODE_VELNEG);
}

void tmc5130_right(TMC5130TypeDef *tmc5130, uint32 velocity)
{
	tmc5130_rotate(tmc5130, velocity);
}

void tmc5130_left(TMC5130TypeDef *tmc5130, uint32 velocity)
{
	tmc5130_rotate(tmc5130, -velocity);
}

void tmc5130_stop(TMC5130TypeDef *tmc5130)
{
	tmc5130_rotate(tmc5130, 0);
}

void tmc5130_moveTo(TMC5130TypeDef *tmc5130, int32 position, uint32 velocityMax)
{
	tmc5130_writeInt(tmc5130, TMC5130_RAMPMODE, TMC5130_MODE_POSITION);

	// VMAX also holds the target velocity in velocity mode.
	// Re-write the position mode maximum velocity here.
	tmc5130_writeInt(tmc5130, TMC5130_VMAX, velocityMax);

	tmc5130_writeInt(tmc5130, TMC5130_XTARGET, position);
}

// The function will write the absolute target position to *ticks
void tmc5130_moveBy(TMC5130TypeDef *tmc5130, int32 *ticks, uint32 velocityMax)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5130_readInt(tmc5130, TMC5130_XACTUAL);

	tmc5130_moveTo(tmc5130, *ticks, velocityMax);
}
