/*******************************************************************************
* Copyright © 2024 Analog Devices, Inc.
*******************************************************************************/


#include "TMC5222.h"

static int32_t readRegisterI2C(uint16_t icID, uint8_t address);
static void writeRegisterI2C(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5222_readRegister(uint16_t icID, uint8_t address)
{
    TMC5222BusType bus = tmc5222_getBusType(icID);

    if(bus == IC_BUS_I2C)
    {
        return readRegisterI2C(icID, address);
    }
    //ToDo: Error handling
    return -1;
}

void tmc5222_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5222BusType bus = tmc5222_getBusType(icID);

    if(bus == IC_BUS_I2C)
    {
        return writeRegisterI2C(icID, address, value);
    }
}

int32_t readRegisterI2C(uint16_t icID, uint8_t address)
{
    uint8_t data[6] = { 0 };

    data[0] = tmc5222_getDeviceAddress(icID);
    data[1] = address;//register address

//    I2CMasterWrite(data[0], &data[1], 1);
//    I2CMasterRead(data[0], &data[2], 4);



    if(!tmc5222_readWriteI2C(icID, &data[0], 1,4))
        return 0;

    return ((int32_t)data[2] << 24) | ((int32_t) data[3] << 16) | ((int32_t) data[4] <<  8) | ((int32_t) data[5]);
}

void writeRegisterI2C(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[6] = { 0 };

    data[0] = tmc5222_getDeviceAddress(icID);
    data[1] = address;//register address
    data[2] = 0xFF & (value>>24);
    data[3] = 0xFF & (value>>16);
    data[4] = 0xFF & (value>>8);
    data[5] = 0xFF & (value>>0);

    // Send the write request
    tmc5222_readWriteI2C(icID, &data[0], 5, 0);
}

void tmc5222_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5222_MOTORS)
        return;

    tmc5222_writeRegister(icID, TMC5222_RGR_VMAX, (velocity < 0) ? -velocity : velocity);
    tmc5222_fieldWrite(icID, TMC5222_RAMPMODE_FIELD, (velocity >= 0) ? TMC5222_MODE_VELPOS : TMC5222_MODE_VELNEG);
}
