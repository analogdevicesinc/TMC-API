/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2130.h"

// => SPI wrapper
// Send [length] bytes stored in the [data] array over SPI and overwrite [data]
// with the reply. The first byte sent/received is data[0].
extern void tmc2130_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc2130_writeDatagram(TMC2130TypeDef *tmc2130, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC2130_WRITE_BIT, x1, x2, x3, x4 };
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	int32_t value = ((uint32_t)x1 << 24) | ((uint32_t)x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc2130->config->shadowRegister[address] = value;
	tmc2130->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

// Write an integer to the given address
void tmc2130_writeInt(TMC2130TypeDef *tmc2130, uint8_t address, int32_t value)
{
	tmc2130_writeDatagram(tmc2130, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

// Read an integer from the given address
int32_t tmc2130_readInt(TMC2130TypeDef *tmc2130, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc2130->registerAccess[address]))
		return tmc2130->config->shadowRegister[address];

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	data[0] = address;
	tmc2130_readWriteArray(tmc2130->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

// Initialize a TMC2130 IC.
// This function requires:
//     - channel: The channel index, which will be sent back in the SPI callback
//     - tmc2130_config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc2130_init(TMC2130TypeDef *tmc2130, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc2130->config               = config;
	tmc2130->config->callback     = NULL;
	tmc2130->config->channel      = channel;
	tmc2130->config->configIndex  = 0;
	tmc2130->config->state        = CONFIG_READY;

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
			tmc2130->config->shadowRegister[i] = tmc2130_RegisterConstants[j].value;
		}
	}
}

// Reset the TMC5130
uint8_t tmc2130_reset(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits
	size_t i;
	for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
	{
		tmc2130->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc2130->config->shadowRegister[i] = 0;
	}

	tmc2130->config->state        = CONFIG_RESET;
	tmc2130->config->configIndex  = 0;

	return true;
}

// Restore the TMC5130 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc2130_restore(TMC2130TypeDef *tmc2130)
{
	if(tmc2130->config->state != CONFIG_READY)
		return false;

	tmc2130->config->state        = CONFIG_RESTORE;
	tmc2130->config->configIndex  = 0;

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
	tmc2130->config->callback = (tmc_callback_config) callback;
}

// Helper function: Configure the next register.
static void writeConfiguration(TMC2130TypeDef *tmc2130)
{
	uint8_t *ptr = &tmc2130->config->configIndex;
	const int32_t *settings;

	if(tmc2130->config->state == CONFIG_RESTORE)
	{
		settings = tmc2130->config->shadowRegister;
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
		if(tmc2130->config->callback)
		{
			((tmc2130_callback)tmc2130->config->callback)(tmc2130, tmc2130->config->state);
		}

		tmc2130->config->state = CONFIG_READY;
	}
}

// Call this periodically
void tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32_t tick)
{
	UNUSED(tick);

	if(tmc2130->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2130);
	}
}
