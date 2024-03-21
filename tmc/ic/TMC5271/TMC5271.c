/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include <tmc/ic/TMC5271/TMC5271.h>


#ifdef TMC_API_EXTERNAL_CRC_TABLE
extern const uint8_t tmcCRCTable_Poly7Reflected[256];
#else
const uint8_t tmcCRCTable_Poly7Reflected[256] = {
            0x00, 0x91, 0xE3, 0x72, 0x07, 0x96, 0xE4, 0x75, 0x0E, 0x9F, 0xED, 0x7C, 0x09, 0x98, 0xEA, 0x7B,
            0x1C, 0x8D, 0xFF, 0x6E, 0x1B, 0x8A, 0xF8, 0x69, 0x12, 0x83, 0xF1, 0x60, 0x15, 0x84, 0xF6, 0x67,
            0x38, 0xA9, 0xDB, 0x4A, 0x3F, 0xAE, 0xDC, 0x4D, 0x36, 0xA7, 0xD5, 0x44, 0x31, 0xA0, 0xD2, 0x43,
            0x24, 0xB5, 0xC7, 0x56, 0x23, 0xB2, 0xC0, 0x51, 0x2A, 0xBB, 0xC9, 0x58, 0x2D, 0xBC, 0xCE, 0x5F,
            0x70, 0xE1, 0x93, 0x02, 0x77, 0xE6, 0x94, 0x05, 0x7E, 0xEF, 0x9D, 0x0C, 0x79, 0xE8, 0x9A, 0x0B,
            0x6C, 0xFD, 0x8F, 0x1E, 0x6B, 0xFA, 0x88, 0x19, 0x62, 0xF3, 0x81, 0x10, 0x65, 0xF4, 0x86, 0x17,
            0x48, 0xD9, 0xAB, 0x3A, 0x4F, 0xDE, 0xAC, 0x3D, 0x46, 0xD7, 0xA5, 0x34, 0x41, 0xD0, 0xA2, 0x33,
            0x54, 0xC5, 0xB7, 0x26, 0x53, 0xC2, 0xB0, 0x21, 0x5A, 0xCB, 0xB9, 0x28, 0x5D, 0xCC, 0xBE, 0x2F,
            0xE0, 0x71, 0x03, 0x92, 0xE7, 0x76, 0x04, 0x95, 0xEE, 0x7F, 0x0D, 0x9C, 0xE9, 0x78, 0x0A, 0x9B,
            0xFC, 0x6D, 0x1F, 0x8E, 0xFB, 0x6A, 0x18, 0x89, 0xF2, 0x63, 0x11, 0x80, 0xF5, 0x64, 0x16, 0x87,
            0xD8, 0x49, 0x3B, 0xAA, 0xDF, 0x4E, 0x3C, 0xAD, 0xD6, 0x47, 0x35, 0xA4, 0xD1, 0x40, 0x32, 0xA3,
            0xC4, 0x55, 0x27, 0xB6, 0xC3, 0x52, 0x20, 0xB1, 0xCA, 0x5B, 0x29, 0xB8, 0xCD, 0x5C, 0x2E, 0xBF,
            0x90, 0x01, 0x73, 0xE2, 0x97, 0x06, 0x74, 0xE5, 0x9E, 0x0F, 0x7D, 0xEC, 0x99, 0x08, 0x7A, 0xEB,
            0x8C, 0x1D, 0x6F, 0xFE, 0x8B, 0x1A, 0x68, 0xF9, 0x82, 0x13, 0x61, 0xF0, 0x85, 0x14, 0x66, 0xF7,
            0xA8, 0x39, 0x4B, 0xDA, 0xAF, 0x3E, 0x4C, 0xDD, 0xA6, 0x37, 0x45, 0xD4, 0xA1, 0x30, 0x42, 0xD3,
            0xB4, 0x25, 0x57, 0xC6, 0xB3, 0x22, 0x50, 0xC1, 0xBA, 0x2B, 0x59, 0xC8, 0xBD, 0x2C, 0x5E, 0xCF,
};
#endif

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
static int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress);
static void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value);
static uint8_t CRC8(uint8_t *data, uint32_t bytes);


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
    data[3] = CRC8(data, 3);

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
    if (data[7] != CRC8(data, 7))
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
    data[7] = CRC8(data, 7);

    tmc5271_readWriteUART(icID, &data[0], 8, 0);
}

void tmc5271_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5271_MOTORS)
        return;

    tmc5271_writeRegister(icID, TMC5271_VMAX, (velocity < 0) ? -velocity : velocity);
    field_write(icID, TMC5271_RAMPMODE_FIELD, (velocity >= 0) ? TMC5271_MODE_VELPOS : TMC5271_MODE_VELNEG);
}

static uint8_t CRC8(uint8_t *data, uint32_t bytes)
{
    uint8_t result = 0;
    uint8_t *table;

    while(bytes--)
        result = tmcCRCTable_Poly7Reflected[result ^ *data++];

    // Flip the result around
    // swap odd and even bits
    result = ((result >> 1) & 0x55) | ((result & 0x55) << 1);
    // swap consecutive pairs
    result = ((result >> 2) & 0x33) | ((result & 0x33) << 2);
    // swap nibbles ...
    result = ((result >> 4) & 0x0F) | ((result & 0x0F) << 4);

    return result;
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
	tmc5271->config->state = CONFIG_READY;
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
