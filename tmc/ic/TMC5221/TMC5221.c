/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include <tmc/ic/TMC5221/TMC5221.h>

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);\

int32_t tmc5221_readRegister(uint16_t icID, uint8_t address)
{
    TMC5221BusType bus = tmc5221_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        return readRegisterSPI(icID, address);
    }
    //ToDo: Error handling
    return -1;
}

void tmc5221_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5221BusType bus = tmc5221_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        writeRegisterSPI(icID, address, value);
    }
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t data[5] = { 0 };

    // clear write bit
    data[0] = address & TMC5221_ADDRESS_MASK;

    // Send the read request
    tmc5221_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC5221_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc5221_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC5221_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc5221_readWriteSPI(icID, &data[0], sizeof(data));
}

void tmc5221_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5221_MOTORS)
        return;

    tmc5221_writeRegister(icID, TMC5221_RGR_VMAX, (velocity < 0) ? -velocity : velocity);
    tmc5221_fieldWrite(icID, TMC5221_RAMPMODE_FIELD, (velocity >= 0) ? TMC5221_MODE_VELPOS : TMC5221_MODE_VELNEG);
}
