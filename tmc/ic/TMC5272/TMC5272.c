/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5272.h"

#define TMC5272_WRITE_BIT 0x80
#define TMC5272_ADDRESS_MASK 0x7F

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
static int32_t readRegisterUART(uint16_t icID, uint8_t address);
static void writeRegisterUART(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc5272_readRegister(uint16_t icID, uint8_t address)
{
	TMC5272BusType bus = tmc5272_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		return readRegisterSPI(icID, address);
	}
	else if (bus == IC_BUS_UART)
	{
		return readRegisterUART(icID, address);
	}

	// ToDo: Error handling
	return -1;
}
void tmc5272_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	TMC5272BusType bus = tmc5272_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		writeRegisterSPI(icID, address, value);
	}
	else if(bus == IC_BUS_UART)
	{
		writeRegisterUART(icID, address, value);
	}
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC5272_ADDRESS_MASK;

	// Send the read request
	tmc5272_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC5272_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc5272_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5272_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5272_readWriteSPI(icID, &data[0], sizeof(data));
}

int32_t readRegisterUART(uint16_t icID, uint8_t address)
{
	uint8_t data[8] = { 0 };

	address = address & TMC5272_ADDRESS_MASK;

	data[0] = 0x05;
	data[1] = tmc5272_getNodeAddress(icID);
	data[2] = address;
	data[3] = tmc_CRC8(data, 3, 1);

	if (!tmc5272_readWriteUART(icID, &data[0], 4, 8))
		return 0;

	// Byte 0: Sync nibble correct?
	if (data[0] != 0x05)
		return 0;

	// Byte 1: Master address correct?
	if (data[1] != 0xFF)
		return 0;

	// Byte 2: Address correct?
	if (data[2] != address)
		return 0;

	// Byte 7: CRC correct?
	if (data[7] != tmc_CRC8(data, 7, 1))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void writeRegisterUART(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = tmc5272_getNodeAddress(icID);
	data[2] = address | TMC5272_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = tmc_CRC8(data, 7, 1);

	tmc5272_readWriteUART(icID, &data[0], 8, 0);
}




// Initialize a TMC5272 IC.
// This function requires:
//     - tmc5272: The pointer to a TMC5272TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc5272_init(TMC5272TypeDef *tmc5272, uint8_t channel, ConfigurationTypeDef *config)
{
	for(uint8_t motor = 0; motor < TMC5272_MOTORS; motor++)
	{
		tmc5272->velocity[motor] = 0;
		tmc5272->oldX[motor] = 0;
	}

	tmc5272->config               = config;
	tmc5272->config->callback     = NULL;
	tmc5272->config->channel      = channel;
	tmc5272->config->configIndex  = 0;
	tmc5272->config->state        = CONFIG_READY;

}

// Reset the TMC5272.
uint8_t tmc5272_reset(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return false;


	tmc5272->config->state        = CONFIG_RESET;
	tmc5272->config->configIndex  = 0;

	return true;
}

// Restore the TMC5272 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc5272_restore(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return false;

	tmc5272->config->state        = CONFIG_RESTORE;
	tmc5272->config->configIndex  = 0;

	return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc5272_setRegisterResetState(TMC5272TypeDef *tmc5272, const int32_t *resetState)
{
	UNUSED(tmc5272);
	UNUSED(resetState);
}

// Register a function to be called after completion of the configuration mechanism
void tmc5272_setCallback(TMC5272TypeDef *tmc5272, tmc5272_callback callback)
{
	tmc5272->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc5272_getSlaveAddress(TMC5272TypeDef *tmc5272)
{
	return tmc5272->slaveAddress;
}

void tmc5272_setSlaveAddress(TMC5272TypeDef *tmc5272, uint8_t slaveAddress)
{
	tmc5272->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC5272TypeDef *tmc5272)
{
	UNUSED(tmc5272);
}

// Call this periodically
void tmc5272_periodicJob(TMC5272TypeDef *tmc5272, uint32_t tick)
{
	uint32_t tickDiff;

	if(tmc5272->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5272);
		return;
	}

	int32_t x;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5272->oldTick) >= 5)
	{
		for(uint8_t motor = 0; motor < TMC5272_MOTORS; motor++)
		{
			x = tmc5272_readInt(tmc5272, TMC5272_XACTUAL(motor));
			tmc5272->velocity[motor] = (uint32_t) ((float32_t) (abs(x - tmc5272->oldX[motor]) / (float32_t) tickDiff) * (float32_t) 1048.576);
			tmc5272->oldX[motor] = x;
		}
		tmc5272->oldTick  = tick;
	}
}


void tmc5272_rotate(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5272_MOTORS)
		return;

	tmc5272_writeInt(tmc5272, TMC5272_VMAX(motor), abs(velocity));
	if (motor == 0)
		TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M0_RAMPMODE_MASK, TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT,  (velocity >= 0) ? TMC5272_MODE_VELPOS : TMC5272_MODE_VELNEG);
	else if(motor == 1)
		TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M1_RAMPMODE_MASK, TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT,  (velocity >= 0) ? TMC5272_MODE_VELPOS : TMC5272_MODE_VELNEG);

}

void tmc5272_right(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	return tmc5272_rotate(tmc5272, motor, velocity);
}

void tmc5272_left(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity)
{
	return tmc5272_rotate(tmc5272, motor, -velocity);
}

void tmc5272_stop(TMC5272TypeDef *tmc5272, uint8_t motor)
{
	return tmc5272_rotate(tmc5272, motor, 0);
}

void tmc5272_moveTo(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5272_MOTORS)
		return;

	if (motor == 0)
		TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M0_RAMPMODE_MASK, TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT, TMC5272_MODE_POSITION);
	else if (motor == 1)
		TMC5272_FIELD_WRITE(tmc5272, TMC5272_RAMPMODE, TMC5272_RAMPMODE_M1_RAMPMODE_MASK, TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT, TMC5272_MODE_POSITION);

	tmc5272_writeInt(tmc5272, TMC5272_VMAX(motor), velocityMax);
	tmc5272_writeInt(tmc5272, TMC5272_XTARGET(motor), position);
}

void tmc5272_moveBy(TMC5272TypeDef *tmc5272, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5272_readInt(tmc5272, TMC5272_XACTUAL(motor));

	return tmc5272_moveTo(tmc5272, motor, *ticks, velocityMax);
}


uint8_t tmc5272_consistencyCheck(TMC5272TypeDef *tmc5272)
{
	if(tmc5272->config->state != CONFIG_READY)
		return 0;
	return 0;
}
