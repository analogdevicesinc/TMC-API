/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "MAX22215.h"

static int32_t readRegisterIIC(uint16_t icID, uint8_t address);
static void writeRegisterIIC(uint16_t icID, uint8_t address, int32_t value);

int32_t max22215_readRegister(uint16_t icID, uint8_t address)
{
    MAX22215BusType bus = max22215_getBusType(icID);

    if(bus == IC_BUS_IIC)
    {
        return readRegisterIIC(icID, address);
    }
    //ToDo: Error handling
    return -1;
}

void max22215_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    MAX22215BusType bus = max22215_getBusType(icID);

    if(bus == IC_BUS_IIC)
    {
        return writeRegisterIIC(icID, address, value);
    }
}

int32_t readRegisterIIC(uint16_t icID, uint8_t address)
{
    uint8_t data[6] = { 0 };

    data[0] = max22215_getDeviceAddress(icID);
    data[1] = address;//register address

//    IICMasterWrite(data[0], &data[1], 1);
//    IICMasterRead(data[0], &data[2], 4);



    if(!max22215_readWriteIIC(icID, &data[0], 1,1))
        return 0;

    return ((int32_t)data[2] << 24) | ((int32_t) data[3] << 16) | ((int32_t) data[4] <<  8) | ((int32_t) data[5]);
}

void writeRegisterIIC(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[6] = { 0 };

    data[0] = max22215_getDeviceAddress(icID);
    data[1] = address;//register address
    data[2] = 0xFF & (value>>24);
    data[3] = 0xFF & (value>>16);
    data[4] = 0xFF & (value>>8);
    data[5] = 0xFF & (value>>0);

    // Send the write request
    //max22215_readWriteIIC(icID, &data[0], 5, 0);
    IICMasterWrite(data[0], &data[1], 5);
}
