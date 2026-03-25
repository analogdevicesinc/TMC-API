/*******************************************************************************
* Copyright © 2026 Analog Devices, Inc.
*******************************************************************************/


#include "TMC6460.h"

#include <string.h> // For memcpy

// Internal bus implementations
static int32_t readRegisterSPI(uint16_t icID, uint16_t address, uint32_t *readValue);
static int32_t writeRegisterSPI(uint16_t icID, uint16_t address, uint32_t writeValue);
static int32_t readRegisterUART(uint16_t icID, uint16_t address, uint32_t *readValue);
static int32_t writeRegisterUART(uint16_t icID, uint16_t address, uint32_t writeValue);

// Internal helper functions
static bool isRTMIDatagramHeader(uint8_t byte_value);
static bool handleRTMIDatagram(uint16_t icID, uint8_t *data);
static uint8_t CRC8(uint8_t *data, uint32_t bytes);

// Constants
#define SPI_WRITE_BIT     0x80
#define UART_SYNC_BITS    0x42
#define UART_STREAM_WRITE 0x41
#define UART_WRITE_BIT    0x08

#ifdef TMC_API_EXTERNAL_CRC_TABLE
extern const uint8_t tmcCRCTable_Poly100011011Reflected[256];
#else
static const uint8_t tmcCRCTable_Poly100011011Reflected[256] = {
        0x00, 0x64, 0xC8, 0xAC, 0xE1, 0x85, 0x29, 0x4D, 0xB3, 0xD7, 0x7B, 0x1F, 0x52, 0x36, 0x9A, 0xFE,
        0x17, 0x73, 0xDF, 0xBB, 0xF6, 0x92, 0x3E, 0x5A, 0xA4, 0xC0, 0x6C, 0x08, 0x45, 0x21, 0x8D, 0xE9,
        0x2E, 0x4A, 0xE6, 0x82, 0xCF, 0xAB, 0x07, 0x63, 0x9D, 0xF9, 0x55, 0x31, 0x7C, 0x18, 0xB4, 0xD0,
        0x39, 0x5D, 0xF1, 0x95, 0xD8, 0xBC, 0x10, 0x74, 0x8A, 0xEE, 0x42, 0x26, 0x6B, 0x0F, 0xA3, 0xC7,
        0x5C, 0x38, 0x94, 0xF0, 0xBD, 0xD9, 0x75, 0x11, 0xEF, 0x8B, 0x27, 0x43, 0x0E, 0x6A, 0xC6, 0xA2,
        0x4B, 0x2F, 0x83, 0xE7, 0xAA, 0xCE, 0x62, 0x06, 0xF8, 0x9C, 0x30, 0x54, 0x19, 0x7D, 0xD1, 0xB5,
        0x72, 0x16, 0xBA, 0xDE, 0x93, 0xF7, 0x5B, 0x3F, 0xC1, 0xA5, 0x09, 0x6D, 0x20, 0x44, 0xE8, 0x8C,
        0x65, 0x01, 0xAD, 0xC9, 0x84, 0xE0, 0x4C, 0x28, 0xD6, 0xB2, 0x1E, 0x7A, 0x37, 0x53, 0xFF, 0x9B,
        0xB8, 0xDC, 0x70, 0x14, 0x59, 0x3D, 0x91, 0xF5, 0x0B, 0x6F, 0xC3, 0xA7, 0xEA, 0x8E, 0x22, 0x46,
        0xAF, 0xCB, 0x67, 0x03, 0x4E, 0x2A, 0x86, 0xE2, 0x1C, 0x78, 0xD4, 0xB0, 0xFD, 0x99, 0x35, 0x51,
        0x96, 0xF2, 0x5E, 0x3A, 0x77, 0x13, 0xBF, 0xDB, 0x25, 0x41, 0xED, 0x89, 0xC4, 0xA0, 0x0C, 0x68,
        0x81, 0xE5, 0x49, 0x2D, 0x60, 0x04, 0xA8, 0xCC, 0x32, 0x56, 0xFA, 0x9E, 0xD3, 0xB7, 0x1B, 0x7F,
        0xE4, 0x80, 0x2C, 0x48, 0x05, 0x61, 0xCD, 0xA9, 0x57, 0x33, 0x9F, 0xFB, 0xB6, 0xD2, 0x7E, 0x1A,
        0xF3, 0x97, 0x3B, 0x5F, 0x12, 0x76, 0xDA, 0xBE, 0x40, 0x24, 0x88, 0xEC, 0xA1, 0xC5, 0x69, 0x0D,
        0xCA, 0xAE, 0x02, 0x66, 0x2B, 0x4F, 0xE3, 0x87, 0x79, 0x1D, 0xB1, 0xD5, 0x98, 0xFC, 0x50, 0x34,
        0xDD, 0xB9, 0x15, 0x71, 0x3C, 0x58, 0xF4, 0x90, 0x6E, 0x0A, 0xA6, 0xC2, 0x8F, 0xEB, 0x47, 0x23,
};
#endif

#if TMC_API_TMC6460_RTMI_SUPPORT == 0
static inline bool tmc6460_RTMIDataCallback(uint16_t icID, uint8_t status, uint32_t data)
{
    // Unused
    (void)icID;
    (void)status;
    (void)data;

    return false;
}

static inline bool tmc6460_isRTMIEnabled(uint16_t icID)
{
    // Unused
    (void)icID;

    return false;
}
#endif

#if TMC_API_TMC6460_CRC_SUPPORT == 0
static inline bool tmc6460_isNormalCRCEnabled(uint16_t icID)
{
    // Unused
    (void)icID;

    return false;
}

static inline bool tmc6460_isRTMICRCEnabled(uint16_t icID)
{
    // Unused
    (void)icID;

    return false;
}
#endif

// Register access functions
int32_t tmc6460_readRegister(uint16_t icID, uint16_t address, uint32_t *readValue)
{
    enum TMC6460BusType bus = tmc6460_getBusType(icID);

    if (bus == TMC6460_BUS_SPI)
    {
        return readRegisterSPI(icID, address, readValue);
    }
    else if (bus == TMC6460_BUS_UART)
    {
        return readRegisterUART(icID, address, readValue);
    }
    else
    {
        return -1;
    }

    return 0;
}

int32_t tmc6460_writeRegister(uint16_t icID, uint16_t address, uint32_t writeValue)
{
    enum TMC6460BusType bus = tmc6460_getBusType(icID);

    if (bus == TMC6460_BUS_SPI)
    {
        return writeRegisterSPI(icID, address, writeValue);
    }
    else if (bus == TMC6460_BUS_UART)
    {
        return writeRegisterUART(icID, address, writeValue);
    }
    else
    {
        return -1;
    }

    return 0;
}

int32_t tmc6460_writeRTMIStreamedRegister(uint16_t icID, uint8_t rtmi_index, uint32_t value)
{
    bool isRTMICRCEnabled = tmc6460_isRTMICRCEnabled(icID);
    size_t writeSize = isRTMICRCEnabled? 6:5;

    uint8_t data[6] = { 0 };

    data[0] = UART_STREAM_WRITE | ((rtmi_index << 1) & 0x0E);
    data[1] = (value >> 24) & 0xFF;
    data[2] = (value >> 16) & 0xFF;
    data[3] = (value >>  8) & 0xFF;
    data[4] = (value      ) & 0xFF;

    if (isRTMICRCEnabled)
    {
        data[5] = CRC8(&data[0], 5);
    }

    if (!tmc6460_readWriteUART(icID, &data[0], writeSize, 0))
    {
        return -2;
    }

    return 0;
}

// SPI communication
static int32_t readRegisterSPI(uint16_t icID, uint16_t address, uint32_t *readValue)
{
    uint8_t data[6] = { 0 };

    // Write address, writeNRead bit cleared
    data[0] = (address >> 8) & 0x03;
    data[1] = address & 0xFF;

    // Send the read request
    tmc6460_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address, writeNRead bit
    data[0] = (address >> 8) & 0x03;
    data[1] = address & 0xFF;

    // Send another request to receive the read reply
    tmc6460_readWriteSPI(icID, &data[0], sizeof(data));

    *readValue = ((uint32_t) data[2] << 24)
               | ((uint32_t) data[3] << 16)
               | ((uint32_t) data[4] <<  8)
               | ((uint32_t) data[5]);

    return 0;
}

static int32_t writeRegisterSPI(uint16_t icID, uint16_t address, uint32_t writeValue)
{
    uint8_t data[6] = { 0 };

    // Write address, writeNRead bit set
    data[0] = SPI_WRITE_BIT | ((address >> 8) & 0x03);
    data[1] = address & 0xFF;
    data[2] = writeValue >> 24;
    data[3] = writeValue >> 16;
    data[4] = writeValue >>  8;
    data[5] = writeValue & 0xFF;

    // Send the write request
    tmc6460_readWriteSPI(icID, &data[0], sizeof(data));

    return 0;
}

// UART communication
static int32_t readRegisterUART(uint16_t icID, uint16_t address, uint32_t *readValue)
{
    bool isNormalCRCEnabled = tmc6460_isNormalCRCEnabled(icID);
    bool isRTMICRCEnabled   = tmc6460_isRTMICRCEnabled(icID);

    // Determine data sizes based on CRC settings
    size_t writeSize = isNormalCRCEnabled? 3:2;
    size_t readSize  = isNormalCRCEnabled? 7:6;
    size_t rtmiSize  = isRTMICRCEnabled? 6:5;

    uint8_t data[7] = { 0 };

    data[0] = UART_SYNC_BITS | ((address >> 4) & 0x30);
    data[1] = address & 0xFF;
    if (isNormalCRCEnabled)
    {
        data[2] = CRC8(&data[0], 2);
    }

    if (!tmc6460_readWriteUART(icID, &data[0], writeSize, readSize))
        return -2;

    // Check if we got a read response or an RTMI packet
    while (isRTMIDatagramHeader(data[0]))
    {
        if (isRTMICRCEnabled)
        {
            if (data[5] != CRC8(&data[0], 5))
                return -5;
        }

        // Write response -> We have an RTMI packet
        // Hand it over to the application layer
        handleRTMIDatagram(icID, &data[0]);

        // Move leftover bytes after the RTMI packet to the start of the buffer...
        memcpy(&data[0], &data[rtmiSize], readSize - rtmiSize);

        // ...then receive more bytes
        if (!tmc6460_readWriteUART(icID, &data[1], 0, rtmiSize))
            return -2;
    }

    if (isNormalCRCEnabled)
    {
        if (data[6] != CRC8(&data[0], 6))
        {
            return -5;
        }
    }

    *readValue = ((uint32_t) data[2] << 24)
               | ((uint32_t) data[3] << 16)
               | ((uint32_t) data[4] <<  8)
               | ((uint32_t) data[5]);

    return 0;
}

static int32_t writeRegisterUART(uint16_t icID, uint16_t address, uint32_t writeValue)
{
    bool isNormalCRCEnabled = tmc6460_isNormalCRCEnabled(icID);
    bool isRTMICRCEnabled   = tmc6460_isRTMICRCEnabled(icID);

    // Determine data sizes based on CRC settings
    // Note: Write replies depend on the RTMI CRC setting!
    size_t writeSize = isNormalCRCEnabled? 7:6;
    size_t readSize  = isRTMICRCEnabled? 6:5;

    uint8_t data[7] = { 0 };

    data[0] = UART_SYNC_BITS | UART_WRITE_BIT | ((address >> 4) & 0x30);
    data[1] = address & 0xFF;
    data[2] = (writeValue >> 24) & 0xFF;
    data[3] = (writeValue >> 16) & 0xFF;
    data[4] = (writeValue >>  8) & 0xFF;
    data[5] = (writeValue      ) & 0xFF;
    if (isNormalCRCEnabled)
    {
        data[6] = CRC8(&data[0], 6);
    }

    // If RTMI is enabled, don't expect a response
    uint8_t responseBytes = (tmc6460_isRTMIEnabled(icID))? 0 : readSize;

    if (!tmc6460_readWriteUART(icID, &data[0], writeSize, responseBytes))
    {
        return -2;
    }

    return 0;
}

static bool isRTMIDatagramHeader(uint8_t byte_value)
{
    return (byte_value & 0x81) == 0x01;
}

static bool handleRTMIDatagram(uint16_t icID, uint8_t *data)
{
    uint8_t rtmiStatus = data[0];
    uint32_t rtmiValue = ((uint32_t) data[1] << 24) | ((uint32_t) data[2] << 16) | ((uint32_t) data[3] << 8) | data[4];
    return tmc6460_RTMIDataCallback(icID, rtmiStatus, rtmiValue);
}

#if TMC_API_TMC6460_RTMI_SUPPORT == 1

bool tmc6460_processRTMI(uint16_t icID, uint32_t packetLimit)
{
    bool isRTMICRCEnabled = tmc6460_isRTMICRCEnabled(icID);
    size_t readSize = isRTMICRCEnabled? 6:5;

    uint8_t data[6] = { 0 };
    bool countPackets = (packetLimit != 0);

    while (!countPackets || ((packetLimit--) > 0))
    {
        // Exit early if we don't have data
        if (tmc6460_availableBytes(icID) < readSize)
            return true;

        // Receive a packet - report an error if we failed to get data
        if (!tmc6460_readWriteUART(icID, &data[0], 0, readSize))
            return false;

        // Sanity check: We should have received an RTMI packet
        // If not, report error
        if (!isRTMIDatagramHeader(data[0]))
            return false;

        // Check the RTMI CRC
        if (isRTMICRCEnabled && data[5] != CRC8(&data[0], 5))
            return false;

        // Hand over the packet to the application layer
        if (handleRTMIDatagram(icID, &data[0]))
            return true;
    }

    return true;
}
#endif

// CRC
static uint8_t CRC8(uint8_t *data, uint32_t bytes)
{
    uint8_t result = 0;
    while(bytes--)
        result = tmcCRCTable_Poly100011011Reflected[result ^ *data++];

    // Flip the result around
    // swap odd and even bits
    result = ((result >> 1) & 0x55) | ((result & 0x55) << 1);
    // swap consecutive pairs
    result = ((result >> 2) & 0x33) | ((result & 0x33) << 2);
    // swap nibbles ...
    result = ((result >> 4) & 0x0F) | ((result & 0x0F) << 4);

    return result;
}
