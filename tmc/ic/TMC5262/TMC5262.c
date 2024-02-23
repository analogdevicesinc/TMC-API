/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5262.h"

extern void tmc5262_readWriteArray(uint8_t channel, uint8_t *data, size_t length);

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void tmc5262_writeDatagram(TMC5262TypeDef *tmc5262, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC5262_WRITE_BIT, x1, x2, x3, x4 };
	tmc5262_readWriteArray(tmc5262->config->channel, &data[0], 5);
}

// Write an integer to the given address
void tmc5262_writeInt(TMC5262TypeDef *tmc5262, uint8_t address, int32_t value)
{
	tmc5262_writeDatagram(tmc5262, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

// Read an integer from the given address
int32_t tmc5262_readInt(TMC5262TypeDef *tmc5262, uint8_t address)
{
	address = TMC_ADDRESS(address);

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc5262_readWriteArray(tmc5262->config->channel, &data[0], 5);

	data[0] = address;
	tmc5262_readWriteArray(tmc5262->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}


// Initialize a tmc5262 IC.
// This function requires:
//     - tmc5262: The pointer to a TMC5262TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
void tmc5262_init(TMC5262TypeDef *tmc5262, uint8_t channel, ConfigurationTypeDef *config)
{
	tmc5262->velocity  = 0;
	tmc5262->oldTick   = 0;
	tmc5262->oldX      = 0;

	tmc5262->config               = config;
	tmc5262->config->channel = channel;
	tmc5262->config->configIndex  = 0;
	tmc5262->config->state        = CONFIG_READY;
}

// Reset the tmc5262.
uint8_t tmc5262_reset(TMC5262TypeDef *tmc5262)
{
	if(tmc5262->config->state != CONFIG_READY)
		return false;

	tmc5262->config->state        = CONFIG_RESET;
	tmc5262->config->configIndex  = 0;
	return true;
}

// Restore the tmc5262 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc5262_restore(TMC5262TypeDef *tmc5262)
{
	if(tmc5262->config->state != CONFIG_READY)
		return false;

	tmc5262->config->state        = CONFIG_RESTORE;
	tmc5262->config->configIndex  = 0;
	return true;
}


uint8_t tmc5262_getSlaveAddress(TMC5262TypeDef *tmc5262)
{
	return tmc5262->slaveAddress;
}

void tmc5262_setSlaveAddress(TMC5262TypeDef *tmc5262, uint8_t slaveAddress)
{
	tmc5262->slaveAddress = slaveAddress;
}

// Helper function: Configure the next register.
static void writeConfiguration(TMC5262TypeDef *tmc5262, uint32_t tick)
{
	uint8_t *ptr = &tmc5262->config->configIndex;
	static int32_t prevTick;
	int32_t readData;

	switch(*ptr){
	case 0:
		// Set PLL register to enable all the clocks and external oscillator
		tmc5262_writeInt(tmc5262, TMC5262_PLL, 0x65FF);
		(*ptr)++;
		prevTick = tick;
		break;
	case 1:
		if(tick - prevTick >= 1000)
		{
			// Clear the all the error flags by the PLL in [15:12]
			tmc5262_writeInt(tmc5262, TMC5262_PLL, 0xF5FE);
			// Read PLL back
			readData = tmc5262_readInt(tmc5262, TMC5262_PLL);
			readData = tmc5262_readInt(tmc5262, TMC5262_PLL);
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
		readData = tmc5262_readInt(tmc5262, TMC5262_CHOPCONF);
		// Set TOFF field to enable the driver
		tmc5262_writeInt(tmc5262, TMC5262_CHOPCONF, (readData & 0xFFFFFFF0) | 0x3);
		(*ptr)++;
		break;
	case 3:
		// Write to GSTAT register to clear the flags
		tmc5262_writeInt(tmc5262, TMC5262_GSTAT, 0x3F);
		tmc5262->config->state = CONFIG_READY;
		*ptr = 0;
		break;
	}
}

// Call this periodically
void tmc5262_periodicJob(TMC5262TypeDef *tmc5262, uint32_t tick)
{
	if(tmc5262->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5262, tick);
		return;
	}

	int32_t XActual;
	uint32_t tickDiff;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5262->oldTick) >= 5)
	{
		XActual = tmc5262_readInt(tmc5262, TMC5262_XACTUAL);
		// ToDo CHECK 2: API Compatibility - write alternative algorithm w/o floating point? (LH)
		tmc5262->velocity = (int32_t) ((float32_t) ((XActual - tmc5262->oldX) / (float32_t) tickDiff) * (float32_t) 1048.576);

		tmc5262->oldX     = XActual;
		tmc5262->oldTick  = tick;
	}
}

// Rotate with a given velocity (to the right)
void tmc5262_rotate(TMC5262TypeDef *tmc5262, int32_t velocity)
{
	// Set absolute velocity
	tmc5262_writeInt(tmc5262, TMC5262_VMAX, abs(velocity));
	// Set direction
	tmc5262_writeInt(tmc5262, TMC5262_RAMPMODE, (velocity >= 0) ? TMC5262_MODE_VELPOS : TMC5262_MODE_VELNEG);
}

// Rotate to the right
void tmc5262_right(TMC5262TypeDef *tmc5262, uint32_t velocity)
{
	tmc5262_rotate(tmc5262, velocity);
}

// Rotate to the left
void tmc5262_left(TMC5262TypeDef *tmc5262, uint32_t velocity)
{
	tmc5262_rotate(tmc5262, -velocity);
}

// Stop moving
void tmc5262_stop(TMC5262TypeDef *tmc5262)
{
	tmc5262_rotate(tmc5262, 0);
}

// Move to a specified position with a given velocity
void tmc5262_moveTo(TMC5262TypeDef *tmc5262, int32_t position, uint32_t velocityMax)
{
	tmc5262_writeInt(tmc5262, TMC5262_RAMPMODE, TMC5262_MODE_POSITION);

	// VMAX also holds the target velocity in velocity mode.
	// Re-write the position mode maximum velocity here.
	tmc5262_writeInt(tmc5262, TMC5262_VMAX, velocityMax);

	tmc5262_writeInt(tmc5262, TMC5262_XTARGET, position);
}

// Move by a given amount with a given velocity
// This function will write the absolute target position to *ticks
void tmc5262_moveBy(TMC5262TypeDef *tmc5262, int32_t *ticks, uint32_t velocityMax)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5262_readInt(tmc5262, TMC5262_XACTUAL);

	tmc5262_moveTo(tmc5262, *ticks, velocityMax);
}

