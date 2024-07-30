/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5220.h"

#define TMC5220_WRITE_BIT 0x80
#define TMC5220_ADDRESS_MASK 0x7F

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5220_readRegister(uint16_t icID, uint8_t address)
{
	TMC5220BusType bus = tmc5220_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		return readRegisterSPI(icID, address);
	}

	// ToDo: Error handling
	return -1;
}
void tmc5220_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	TMC5220BusType bus = tmc5220_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		writeRegisterSPI(icID, address, value);
	}

}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC5220_ADDRESS_MASK;

	// Send the read request
	tmc5220_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC5220_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc5220_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5220_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5220_readWriteSPI(icID, &data[0], sizeof(data));
}
