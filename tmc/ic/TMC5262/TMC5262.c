/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5262.h"


static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc5262_readRegister(uint16_t icID, uint8_t address)
{
	return readRegisterSPI(icID, address);
}

void tmc5262_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC5262_ADDRESS_MASK;

	// Send the read request
	tmc5262_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC5262_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc5262_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5262_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5262_readWriteSPI(icID, &data[0], sizeof(data));
}

void tmc5262_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5262_MOTORS)
        return;

    tmc5262_writeRegister(icID, TMC5262_VMAX, (velocity < 0) ? -velocity : velocity);
    tmc5262_fieldWrite(icID, TMC5262_RAMPMODE_FIELD, (velocity >= 0) ? TMC5262_MODE_VELPOS : TMC5262_MODE_VELNEG);
}
