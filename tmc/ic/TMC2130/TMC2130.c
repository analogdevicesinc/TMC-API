/*
 * TMC2130.c
 *
 *  Created on: 26.01.2017
 *      Author: BS / ED
 */

#include "TMC2130.h"

// => SPI wrapper
// Send [length] bytes stored in the [data] array over SPI and overwrite [data]
// with the reply. The first byte sent/received is data[0].
extern void tmc2130_readWriteArray(uint8_t *data, size_t length, void *userData);
// <= SPI wrapper

// Write an integer to the given address
void tmc2130_writeInt(TMC2130TypeDef *tmc2130, uint8_t address, int32_t value)
{
	uint8_t data[5];
	data[0] = address | TMC2130_WRITE_BIT;
	data[1] = BYTE(value, 3);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 1);
	data[4] = BYTE(value, 0);

	tmc2130_readWriteArray(&data[0], 5, tmc2130->config.userData);

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2130->config.shadowRegister[address] = value;
	tmc2130->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

// Read an integer from the given address
int32_t tmc2130_readInt(TMC2130TypeDef *tmc2130, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2130->registerAccess[address]))
		return tmc2130->config.shadowRegister[address];

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc2130_readWriteArray(&data[0], 5, tmc2130->config.userData);

	data[0] = address;
	tmc2130_readWriteArray(&data[0], 5, tmc2130->config.userData);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

// Initialize a TMC2130 IC.
// This function requires:
//     - tmc2130: A pointer to a TMC2130TypeDef struct to be initialized.
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
//     - userData: A pointer to be freely used. This pointer gets passed in the tmc2130_readWriteArray callback.
void tmc2130_init(TMC2130TypeDef *tmc2130, const int32_t *registerResetState, void *userData)
{
	tmc2130->config.callback     = NULL;
	tmc2130->config.userData     = userData;
	tmc2130->config.configIndex  = 0;
	tmc2130->config.state        = CONFIG_READY;

	size_t i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		tmc2130->registerAccess[i]      = tmc2130_defaultRegisterAccess[i];
		tmc2130->registerResetState[i]  = registerResetState[i];
	}
}

// Fill the shadow registers of hardware preset non-readable registers
// Only needed if you want to 'read' those registers e.g to display the value
// in the TMCL IDE register browser
void tmc2130_fillShadowRegisters(TMC2130TypeDef *tmc2130)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc2130_RegisterConstants) == 0)
		return;

	size_t i, j;
	for(i = 0, j = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc2130->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc2130_RegisterConstants) && (tmc2130_RegisterConstants[j].address < i))
			j++;

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc2130_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if(tmc2130_RegisterConstants[j].address == i)
		{
			tmc2130->config.shadowRegister[i] = tmc2130_RegisterConstants[j].value;
		}
	}
}

// Reset the TMC5130
uint8_t tmc2130_reset(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config.state != CONFIG_READY)
		return false;

	// Reset the dirty bits
	size_t i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		tmc2130->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2130->config.shadowRegister[i] = 0;
	}

	tmc2130->config.state        = CONFIG_RESET;
	tmc2130->config.configIndex  = 0;

	return true;
}

// Restore the TMC5130 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc2130_restore(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config.state != CONFIG_READY)
		return false;

	tmc2130->config.state        = CONFIG_RESTORE;
	tmc2130->config.configIndex  = 0;

	return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc2130_setRegisterResetState(TMC2130TypeDef *tmc2130, const int32_t *resetState)
{
	size_t i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		tmc2130->registerResetState[i] = resetState[i];
	}
}

// Register a function to be called after completion of the configuration mechanism
void tmc2130_setCallback(TMC2130TypeDef *tmc2130, tmc2130_callback callback)
{
	tmc2130->config.callback = (tmc_callback_config) callback;
}

// Helper function: Configure the next register.
static void writeConfiguration(TMC2130TypeDef *tmc2130)
{
	uint8_t *ptr = &tmc2130->config.configIndex;
	const int32_t *settings;

	if(tmc2130->config.state == CONFIG_RESTORE)
	{
		settings = tmc2130->config.shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2130->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}
	else
	{
		settings = tmc2130->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2130->registerAccess[*ptr]))
		{
			(*ptr)++;
		}
	}

	if(*ptr < TMC2130_REGISTER_COUNT)
	{
		tmc2130_writeInt(tmc2130, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc2130->config.callback)
		{
			((tmc2130_callback)tmc2130->config.callback)(tmc2130, tmc2130->config.state);
		}

		tmc2130->config.state = CONFIG_READY;
	}
}

// Call this periodically
uint8_t tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2130->config.state != CONFIG_READY)
	{
		writeConfiguration(tmc2130);
	}

	return tmc2130->config.state != CONFIG_READY;
}
