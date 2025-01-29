/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "TMC429.h"
#include "TMC429_HW_Abstraction.h"

void tmc429_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
    if(motor >= TMC429_MOTORS)
        return;

	writeRegisterSPI(icID, TMC429_V_TARGET(motor), (velocity >= 0)? velocity : -velocity);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[4] = { 0 };

	// Set the address for reading
    // Set bit 0 to 1 to indicate a read operation
    data[0] = (address & TMC429_ADDRESS_MASK) | TMC429_WRITE_READ_BIT;

	// Send the read request
	tmc429_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite the address and set the read bit
	data[0] = (address & TMC429_ADDRESS_MASK) | TMC429_WRITE_READ_BIT;

	// Send another request to receive the read reply
	tmc429_readWriteSPI(icID, &data[0], sizeof(data));

	return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[4] = { 0 };

	// Set bit 0 to 0 to indicate a write operation
	data[0] = address & TMC429_ADDRESS_MASK;
	data[1] = 0xFF & (value >> 16);
	data[2] = 0xFF & (value >> 8);
	data[3] = 0xFF & value;

	// Send the write request
	tmc429_readWriteSPI(icID, &data[0], sizeof(data));
}

int32_t tmc429_readRegister(uint16_t icID, uint8_t address)
{
    return readRegisterSPI(icID, address);
}

void tmc429_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    writeRegisterSPI(icID, address, value);
}
