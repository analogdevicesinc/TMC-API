/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "TMC5240.h"

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

/************************************************************** Register read / write Implementation ******************************************************************/

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
static int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress);
static void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value);
static uint8_t CRC8(uint8_t *data, uint32_t bytes);

int32_t tmc5240_readRegister(uint16_t icID, uint8_t address)
{
    TMC5240BusType bus = tmc5240_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        return readRegisterSPI(icID, address);
    }
    else if (bus == IC_BUS_UART)
    {
        return readRegisterUART(icID, address);
    }
    return -1;
}

void tmc5240_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5240BusType bus = tmc5240_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        writeRegisterSPI(icID, address, value);
    }
    else if (bus == IC_BUS_UART)
    {
        writeRegisterUART(icID,  address,  value);
    }
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t data[5] = { 0 };

    // clear write bit
    data[0] = address & TMC5240_ADDRESS_MASK;

    // Send the read request
    tmc5240_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC5240_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc5240_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC5240_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc5240_readWriteSPI(icID, &data[0], sizeof(data));
}

int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress)
{
    uint8_t data[8] = { 0 };

    registerAddress = registerAddress & TMC5240_ADDRESS_MASK;

    data[0] = 0x05;
    data[1] = tmc5240_getNodeAddress(icID); //targetAddressUart;
    data[2] = registerAddress;
    data[3] = CRC8(data, 3);

    if (!tmc5240_readWriteUART(icID, &data[0], 4, 8))
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

    return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | ((uint32_t)data[5] << 8) | data[6];
}

void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value)
{
    uint8_t data[8];

    data[0] = 0x05;
    data[1] = (uint8_t)tmc5240_getNodeAddress(icID); //targetAddressUart;
    data[2] = registerAddress | TMC5240_WRITE_BIT;
    data[3] = (value >> 24) & 0xFF;
    data[4] = (value >> 16) & 0xFF;
    data[5] = (value >> 8 ) & 0xFF;
    data[6] = (value      ) & 0xFF;
    data[7] = CRC8(data, 7);

    tmc5240_readWriteUART(icID, &data[0], 8, 0);
}

void tmc5240_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
    if(motor >= TMC5240_MOTORS)
        return;

    tmc5240_writeRegister(icID, TMC5240_VMAX, (velocity < 0) ? -velocity : velocity);
    tmc5240_fieldWrite(icID, TMC5240_RAMPMODE_FIELD, (velocity >= 0) ? TMC5240_MODE_VELPOS : TMC5240_MODE_VELNEG);
}

static uint8_t CRC8(uint8_t *data, uint32_t bytes)
{
    uint8_t result = 0;

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

