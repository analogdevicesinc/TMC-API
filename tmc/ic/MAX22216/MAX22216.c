/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "MAX22216.h"

static uint16_t readRegisterSPI(uint16_t icID, uint8_t address);
static uint16_t readRegisterSPI_CRC_EN(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, uint16_t value);
static void writeRegisterSPI_CRC_EN(uint16_t icID, uint8_t address, uint16_t value);

uint16_t max22216_readRegister(uint16_t icID, uint8_t address)
{
    if (max22216_getCRCEnState())
    {
        return readRegisterSPI_CRC_EN(icID, address);
    }
    else
    {
        return readRegisterSPI(icID, address);
    }
}

void max22216_writeRegister(uint16_t icID, uint8_t address, uint16_t value)
{
    if (max22216_getCRCEnState())
    {
        writeRegisterSPI_CRC_EN(icID, address, value);
    }
    else
    {
        writeRegisterSPI(icID, address, value);
    }
}

uint16_t readRegisterSPI_CRC_EN(uint16_t icID, uint8_t address)
{
    uint8_t data[4] = {0};

    // clear write bit
    data[0] = address & MAX22216_ADDRESS_MASK;

    // Generate the CRC value for comparison
    data[3] = max22216_CRC(&data[0], 27);

    // Send the read request
    max22216_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & MAX22216_ADDRESS_MASK;

    // Generate the CRC value for comparison
    data[3] = max22216_CRC(&data[0], 27);

    // Send another request to receive the read reply
    max22216_readWriteSPI(icID, &data[0], sizeof(data));

    return ((uint16_t) data[1] << 8) | ((uint16_t) data[2]);
}

uint16_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t data[3] = {0};

    // clear write bit
    data[0] = address & MAX22216_ADDRESS_MASK;

    // Send the read request
    max22216_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & MAX22216_ADDRESS_MASK;

    // Send another request to receive the read reply
    max22216_readWriteSPI(icID, &data[0], sizeof(data));

    return ((uint16_t) data[1] << 8) | ((uint16_t) data[2]);
}

void writeRegisterSPI_CRC_EN(uint16_t icID, uint8_t address, uint16_t value)
{
    uint8_t data[4] = {0};

    data[0] = address | MAX22216_WRITE_BIT;
    data[1] = ((value >> 8) & 0xFF);
    data[2] = value & 0xFF;
    data[3] = max22216_CRC(&data[0], 27);

    // Send the write request
    max22216_readWriteSPI(icID, &data[0], sizeof(data));
void max22216_init(MAX22216TypeDef *max22216, uint8_t channel)
{
    max22216->slaveAddress = channel;
    max22216->channel = channel;
    max22216->crc_en = 0;
}

void writeRegisterSPI(uint16_t icID, uint8_t address, uint16_t value)
uint8_t max22216_getSlaveAddress(const MAX22216TypeDef *max22216)
{
    uint8_t data[3] = {0};
    return max22216->slaveAddress;
}

    data[0] = address | MAX22216_WRITE_BIT;
    data[1] = ((value >> 8) & 0xFF);
    data[2] = value & 0xFF;

    // Send the write request
    max22216_readWriteSPI(icID, &data[0], sizeof(data));
void max22216_setSlaveAddress(MAX22216TypeDef *max22216, uint8_t slaveAddress)
{
    max22216->slaveAddress = slaveAddress;
}

// length in bits
uint8_t max22216_CRC(uint8_t *data, size_t length)
int16_t max22216_getS16CircleDifference(int16_t newValue, int16_t oldValue)
{
    uint8_t crc = 0b11111;
    uint8_t crc_old;

    for (size_t i = 0; i < length; i++)
    {

        crc_old = crc;

        // define the data field dynamically
        uint8_t data_SHIFT                = 7 - (i % 8);
        uint8_t data_MASK                 = (1 << data_SHIFT);
        RegisterField MAX22216_data_FIELD = (RegisterField){data_MASK, data_SHIFT, __None__, false};

        crc = max22216_fieldUpdate(crc, MAX22216_CRC5_FIELD, max22216_fieldExtract(crc_old, MAX22216_CRC4_FIELD));
        crc = max22216_fieldUpdate(crc, MAX22216_CRC4_FIELD, \
                                   max22216_fieldExtract(crc_old, MAX22216_CRC3_FIELD) ^ \
                                   max22216_fieldExtract(crc_old, MAX22216_CRC4_FIELD) ^ \
                                   max22216_fieldExtract(data[i / 8], MAX22216_data_FIELD));
        crc = max22216_fieldUpdate(crc, MAX22216_CRC3_FIELD, max22216_fieldExtract(crc_old, MAX22216_CRC2_FIELD));
        crc = max22216_fieldUpdate(crc, MAX22216_CRC2_FIELD, \
                                   max22216_fieldExtract(crc_old, MAX22216_CRC1_FIELD) ^ \
                                   max22216_fieldExtract(crc_old, MAX22216_CRC4_FIELD) ^ \
                                   max22216_fieldExtract(data[i / 8], MAX22216_data_FIELD));
        crc = max22216_fieldUpdate(crc, MAX22216_CRC1_FIELD, max22216_fieldExtract(crc_old, MAX22216_CRC0_FIELD));
        crc = max22216_fieldUpdate(crc, MAX22216_CRC0_FIELD, \
                                   max22216_fieldExtract(crc_old, MAX22216_CRC4_FIELD) ^ \
                                   max22216_fieldExtract(data[i / 8], MAX22216_data_FIELD));
    }
    return (crc & 0x1F);
    return (newValue - oldValue);
}
