/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include <tmc/ic/MAX22200/MAX22200.h>

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t max22200_readRegister(uint16_t icID, uint8_t address)
{
    return readRegisterSPI(icID, address);
}

void max22200_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    writeRegisterSPI(icID, address, value);
}
int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t cmd = 0;
    uint8_t data[4] = {0};

    // Send the read request
    cmd &= ~(1 << 7); // read
    cmd &= ~((1 << 5)|(1 << 6));
    cmd |= (address << 1);
    cmd &= ~(1 << 0);

    max22200_readWriteSPI(icID, &cmd, sizeof(cmd), true);

    // Send request to read reply
    max22200_readWriteSPI(icID, &data[0], sizeof(data), false);

    return ((int32_t)data[0] << 24) | ((int32_t) data[1] << 16) | ((int32_t) data[2] <<  8) | ((int32_t) data[3]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t cmd = 0;
    uint8_t data[4] = {0};

    // Send the write request
    cmd |= (1 << 7);    //write
    cmd &= ~((1 << 5)|(1 << 6));
    cmd |= ((address << 1));
    cmd &= ~(1 << 0);

    max22200_readWriteSPI(icID, &cmd, sizeof(cmd), true);

    data[0] = 0xFF & (value>>0);
    data[1] = 0xFF & (value>>8);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>24);

    // Send another request to send data
    max22200_readWriteSPI(icID, &data[0], sizeof(data), false);
}
