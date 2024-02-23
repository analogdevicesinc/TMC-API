/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2262.h"

extern void tmc2262_readWriteArray(uint8_t channel, uint8_t *data, size_t length);

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc2262_writeDatagram(TMC2262TypeDef *tmc2262, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC2262_WRITE_BIT, x1, x2, x3, x4 };
	tmc2262_readWriteArray(tmc2262->config->channel, &data[0], 5);
}

// Write an integer to the given address
void tmc2262_writeInt(TMC2262TypeDef *tmc2262, uint8_t address, int32_t value)
{
	tmc2262_writeDatagram(tmc2262, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

// Read an integer from the given address
int32_t tmc2262_readInt(TMC2262TypeDef *tmc2262, uint8_t address)
{
	address = TMC_ADDRESS(address);

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc2262_readWriteArray(tmc2262->config->channel, &data[0], 5);

	data[0] = address;
	tmc2262_readWriteArray(tmc2262->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}


// Initialize a tmc2262 IC.
// This function requires:
//     - tmc2262: The pointer to a TMC2262TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
void tmc2262_init(TMC2262TypeDef *tmc2262, uint8_t channel, ConfigurationTypeDef *config)
{
	tmc2262->velocity  = 0;
	tmc2262->oldTick   = 0;
	tmc2262->oldX      = 0;

	tmc2262->config               = config;
	tmc2262->config->channel = channel;
	tmc2262->config->configIndex  = 0;
	tmc2262->config->state        = CONFIG_READY;
}

// Reset the tmc2262.
uint8_t tmc2262_reset(TMC2262TypeDef *tmc2262)
{
	if(tmc2262->config->state != CONFIG_READY)
		return false;

	tmc2262->config->state        = CONFIG_RESET;
	tmc2262->config->configIndex  = 0;
	return true;
}

// Restore the tmc2262 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc2262_restore(TMC2262TypeDef *tmc2262)
{
	if(tmc2262->config->state != CONFIG_READY)
		return false;

	tmc2262->config->state        = CONFIG_RESTORE;
	tmc2262->config->configIndex  = 0;
	return true;
}


uint8_t tmc2262_getSlaveAddress(TMC2262TypeDef *tmc2262)
{
	return tmc2262->slaveAddress;
}

void tmc2262_setSlaveAddress(TMC2262TypeDef *tmc2262, uint8_t slaveAddress)
{
	tmc2262->slaveAddress = slaveAddress;
}

// Helper function: Configure the next register.
static void writeConfiguration(TMC2262TypeDef *tmc2262, uint32_t tick)
{
	uint8_t *ptr = &tmc2262->config->configIndex;
	static int32_t prevTick;
	int32_t readData;

	switch(*ptr){
	case 0:
		// Set PLL register to enable all the clocks and external oscillator
		tmc2262_writeInt(tmc2262, TMC2262_PLL, 0x65FF);
		(*ptr)++;
		prevTick = tick;
		break;
	case 1:
		if(tick - prevTick >= 1000)
		{
			// Clear the all the error flags by the PLL in [15:12]
			tmc2262_writeInt(tmc2262, TMC2262_PLL, 0xF5FE);
			// Read PLL back
			readData = tmc2262_readInt(tmc2262, TMC2262_PLL);
			readData = tmc2262_readInt(tmc2262, TMC2262_PLL);
			if((readData & 0xF000) != 0)
			{
				*ptr = 0;
				break;
			}
			(*ptr)++;
		}
		break;
	case 2:
		//Reading ChopConf register
		readData = tmc2262_readInt(tmc2262, TMC2262_CHOPCONF);
		// Set TOFF field to enable the driver
		tmc2262_writeInt(tmc2262, TMC2262_CHOPCONF, (readData & 0xFFFFFFF0) | 0x3);
		(*ptr)++;
		break;
	case 3:
		// Write to GSTAT register to clear the flags
		tmc2262_writeInt(tmc2262, TMC2262_GSTAT, 0x3F);
		tmc2262->config->state = CONFIG_READY;
		*ptr = 0;
		break;
	}
}

// Call this periodically
void tmc2262_periodicJob(TMC2262TypeDef *tmc2262, uint32_t tick)
{
	if(tmc2262->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc2262, tick);
		return;
	}
}


