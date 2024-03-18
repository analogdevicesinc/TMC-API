/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include <tmc/ic/TMC5271/TMC5271.h>


static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
static int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress);
static void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value);


int32_t tmc5271_readRegister(uint16_t icID, uint8_t address)
{
    TMC5271BusType bus = tmc5271_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        return readRegisterSPI(icID, address);
    }
    else if (bus == IC_BUS_UART)
    {
        return readRegisterUART(icID, address);
    }

    //ToDo: Error handling
    return -1;
}

void tmc5271_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5271BusType bus = tmc5271_getBusType(icID);

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
    data[0] = address & TMC_ADDRESS_MASK;

    // Send the read request
    tmc5271_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc5271_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc5271_readWriteSPI(icID, &data[0], sizeof(data));
}

int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress)
{
    uint8_t data[8] = { 0 };

    registerAddress = registerAddress & TMC_ADDRESS_MASK;

    data[0] = 0x05;
    data[1] = tmc5271_getNodeAddress(icID); //targetAddressUart;
    data[2] = registerAddress;
    data[3] = tmc_CRC8(data, 3, 1);

    if (!tmc5271_readWriteUART(icID, &data[0], 4, 8))
        return 0;

    // Byte 0: Sync nibble correct?
    if (data[0] != 0x05)
        return 0;

    // Byte 1: Master address correct?
    if (data[1] != 0xFF)
        return 0;

    // Byte 2: Address correct?
    if (data[2] != registerAddress)
        return 0;

    // Byte 7: CRC correct?
    if (data[7] != tmc_CRC8(data, 7, 1))
        return 0;

    return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value)
{
    uint8_t data[8];

    data[0] = 0x05;
    data[1] = (uint8_t)tmc5271_getNodeAddress(icID); //targetAddressUart;
    data[2] = registerAddress | TMC_WRITE_BIT;
    data[3] = (value >> 24) & 0xFF;
    data[4] = (value >> 16) & 0xFF;
    data[5] = (value >> 8 ) & 0xFF;
    data[6] = (value      ) & 0xFF;
    data[7] = tmc_CRC8(data, 7, 1);

    tmc5271_readWriteUART(icID, &data[0], 8, 0);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/
// Initialize a TMC5271 IC.
// This function requires:
//     - tmc5271: The pointer to a TMC5271TypeDef struct, which represents one IC
//     - channel: The channel index, which will be sent back in the SPI callback
//     - config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc5271_init(TMC5271TypeDef *tmc5271, uint8_t channel, ConfigurationTypeDef *config)
{
	for(uint8_t motor = 0; motor < TMC5271_MOTORS; motor++)
	{
		tmc5271->velocity[motor] = 0;
		tmc5271->oldX[motor] = 0;
	}

	tmc5271->config               = config;
	tmc5271->config->callback     = NULL;
	tmc5271->config->channel      = channel;
	tmc5271->config->configIndex  = 0;
	tmc5271->config->state        = CONFIG_READY;

}

// Reset the TMC5271.
uint8_t tmc5271_reset(TMC5271TypeDef *tmc5271)
{
	if(tmc5271->config->state != CONFIG_READY)
		return false;

	tmc5271->config->state        = CONFIG_RESET;
	tmc5271->config->configIndex  = 0;

	return true;
}

// Register a function to be called after completion of the configuration mechanism
void tmc5271_setCallback(TMC5271TypeDef *tmc5271, tmc5271_callback callback)
{
	tmc5271->config->callback = (tmc_callback_config) callback;
}
uint8_t tmc5271_getSlaveAddress(TMC5271TypeDef *tmc5271)
{
	return tmc5271->slaveAddress;
}

void tmc5271_setSlaveAddress(TMC5271TypeDef *tmc5271, uint8_t slaveAddress)
{
	tmc5271->slaveAddress = slaveAddress;
}
// Helper function: Configure the next register.
static void writeConfiguration(TMC5271TypeDef *tmc5271)
{
	UNUSED(tmc5271);
}

// Call this periodically
void tmc5271_periodicJob(TMC5271TypeDef *tmc5271, uint32_t tick)
{
	uint32_t tickDiff;

	if(tmc5271->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5271);
		return;
	}

	int32_t x;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5271->oldTick) >= 5)
	{
		for(uint8_t motor = 0; motor < TMC5271_MOTORS; motor++)
		{
			x = tmc5271_readRegister(motor, TMC5271_XACTUAL);
			tmc5271->velocity[motor] = (uint32_t) ((float32_t) (abs(x - tmc5271->oldX[motor]) / (float32_t) tickDiff) * (float32_t) 1048.576);
			tmc5271->oldX[motor] = x;
		}
		tmc5271->oldTick  = tick;
	}
}


void tmc5271_rotate(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5271_MOTORS)
		return;

	tmc5271_writeRegister(motor, TMC5271_VMAX, abs(velocity));
	field_write(motor, TMC5271_RAMPMODE_FIELD,  (velocity >= 0) ? TMC5271_MODE_VELPOS : TMC5271_MODE_VELNEG);

}

void tmc5271_right(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	return tmc5271_rotate(tmc5271, motor, velocity);
}

void tmc5271_left(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity)
{
	return tmc5271_rotate(tmc5271, motor, -velocity);
}

void tmc5271_stop(TMC5271TypeDef *tmc5271, uint8_t motor)
{
	return tmc5271_rotate(tmc5271, motor, 0);
}

void tmc5271_moveTo(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5271_MOTORS)
		return;

	field_write(motor, TMC5271_RAMPMODE_FIELD, TMC5271_MODE_POSITION);

	tmc5271_writeRegister(motor, TMC5271_VMAX, velocityMax);
	tmc5271_writeRegister(motor, TMC5271_XTARGET, position);
}

void tmc5271_moveBy(TMC5271TypeDef *tmc5271, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5271_readRegister(motor, TMC5271_XACTUAL);

	return tmc5271_moveTo(tmc5271, motor, *ticks, velocityMax);
}


uint8_t tmc5271_consistencyCheck(TMC5271TypeDef *tmc5271)
{
	if(tmc5271->config->state != CONFIG_READY)
		return 0;
	return 0;
}
