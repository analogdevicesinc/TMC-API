/*******************************************************************************
* Copyright © 2026 Analog Devices, Inc.
*******************************************************************************/


#include "TMC3241.h"


static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc3241_readRegister(uint16_t icID, uint8_t address)
{
	return readRegisterSPI(icID, address);
}

void tmc3241_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC3241_ADDRESS_MASK;

	// Send the read request
	tmc3241_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC3241_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc3241_readWriteSPI(icID, &data[0], sizeof(data));

	return ((uint32_t)data[1] << 24) | ((uint32_t) data[2] << 16) | ((uint32_t) data[3] <<  8) | ((uint32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC3241_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc3241_readWriteSPI(icID, &data[0], sizeof(data));
}
