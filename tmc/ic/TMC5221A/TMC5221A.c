/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include <tmc/ic/TMC5221A/TMC5221A.h>

static int32_t readRegisterIIC(uint16_t icID, uint8_t address);
static void writeRegisterIIC(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5221A_readRegister(uint16_t icID, uint8_t address)
{
    TMC5221ABusType bus = tmc5221A_getBusType(icID);

    if(bus == IC_BUS_IIC)
    {
        return readRegisterIIC(icID, address);
    }
    //ToDo: Error handling
    return -1;
}

void tmc5221A_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5221ABusType bus = tmc5221A_getBusType(icID);

    if(bus == IC_BUS_IIC)
    {
        return writeRegisterIIC(icID, address, value);
    }
}

int32_t readRegisterIIC(uint16_t icID, uint8_t address)
{
    uint8_t data[6] = { 0 };

    data[0] = tmc5221A_getDeviceAddress(icID);
    data[1] = address;//register address

//    IICMasterWrite(data[0], &data[1], 1);
//    IICMasterRead(data[0], &data[2], 4);



    if(!tmc5221A_readWriteIIC(icID, &data[0], 1,4))
        return 0;

    return ((int32_t)data[2] << 24) | ((int32_t) data[3] << 16) | ((int32_t) data[4] <<  8) | ((int32_t) data[5]);
}

void writeRegisterIIC(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[6] = { 0 };

    data[0] = tmc5221A_getDeviceAddress(icID);
    data[1] = address;//register address
    data[2] = 0xFF & (value>>24);
    data[3] = 0xFF & (value>>16);
    data[4] = 0xFF & (value>>8);
    data[5] = 0xFF & (value>>0);

    // Send the write request
    //tmc5221A_readWriteIIC(icID, &data[0], 5, 0);
    IICMasterWrite(data[0], &data[1], 5);
}

void tmc5221A_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5221A_MOTORS)
        return;

    tmc5221A_writeRegister(icID, TMC5221A_RGR_VMAX, (velocity < 0) ? -velocity : velocity);
    tmc5221A_fieldWrite(icID, TMC5221A_RAMPMODE_FIELD, (velocity >= 0) ? TMC5221A_MODE_VELPOS : TMC5221A_MODE_VELNEG);
}
