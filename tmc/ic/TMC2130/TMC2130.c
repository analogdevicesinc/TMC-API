/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2130.h"

TMC2130TypeDef TMC2130;

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc2130_readRegister(uint16_t icID, uint8_t address)
{
	return readRegisterSPI(icID, address);
}
void tmc2130_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{

	uint8_t data[5] = { 0 };

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(TMC2130.registerAccess[address]))
	return TMC2130.config->shadowRegister[address];


	// clear write bit
	data[0] = address & TMC2130_ADDRESS_MASK;

	// Send the read request
	tmc2130_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC2130_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc2130_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC2130_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc2130_readWriteSPI(icID, &data[0], sizeof(data));

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	TMC2130.config->shadowRegister[address] = value;
	TMC2130.registerAccess[address] |= TMC_ACCESS_DIRTY;
}
/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

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

// Reset the TMC2130
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

// Restore the TMC2130 to the state stored in the shadow registers.
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
		tmc2130_writeRegister(DEFAULT_MOTOR, *ptr, settings[*ptr]);
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
