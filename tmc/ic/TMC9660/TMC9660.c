/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC9660.h"

// Helper functions
static int32_t tmc9660_param_sendCommand_UART(uint16_t icID, uint8_t cmd, uint16_t type, uint8_t index, uint32_t writeValue, uint32_t *readValue);
static uint8_t calcParamChecksum(uint8_t *data, uint32_t bytes);

/*** Command sending implementation *******************************************/


int32_t tmc9660_param_sendCommand(uint16_t icID, uint8_t cmd, uint16_t type, uint8_t index, uint32_t writeValue, uint32_t *readValue)
{
    TMC9660BusType bus = tmc9660_getBusType(icID);

    if(bus == TMC9660_BUS_SPI)
    {
        // ToDo: SPI support
    }
    else if(bus == TMC9660_BUS_UART)
    {
        return tmc9660_param_sendCommand_UART(icID, cmd, type, index, writeValue, readValue);
    }

    return -1;
}

static int32_t tmc9660_param_sendCommand_UART(uint16_t icID, uint8_t cmd, uint16_t type, uint8_t index, uint32_t writeValue, uint32_t *readValue)
{
    // ToDo: GetVersion ASCII special case - custom reply format
    // ToDo: ReturnToBootloader special case - no reply

    uint8_t data[9] = { 0 };
    TMC9660BusAddresses addresses = tmc9660_getBusAddresses(icID);

    // Create the request datagram
    uint8_t syncByte = 0x01 | (addresses.device);
    data[0] = syncByte; // Module Address & sync bit
    data[1] = cmd;
    data[2] = type & 0xFF;
    data[3] = (type >> 8) << 4 | (index & 0x0F); // ToDo: Do we wanna do the 4/12 split at this function's arguments?
    data[4] = (writeValue >> 24) & 0xFF;
    data[5] = (writeValue >> 16) & 0xFF;
    data[6] = (writeValue >> 8) & 0xFF;
    data[7] = (writeValue) & 0xFF;
    data[8] = calcParamChecksum(&data[0], 8);

    if (!tmc9660_readWriteUART(icID, &data[0], 9, 9))
        return -2;

    // Unpack the reply
    if (data[0] != addresses.host)
        return -3;
    if (data[1] != syncByte)
        return -4;
    if (data[8] != calcParamChecksum(&data[0], 8))
        return -5;

    if (readValue)
    {
        *readValue = ((uint32_t)data[4] << 24) | ((uint32_t)data[5] << 16) | (data[6] << 8) | data[7];
    }

    return data[2];
}

static uint8_t calcParamChecksum(uint8_t *data, uint32_t bytes)
{
    uint8_t checksum = 0;

    for (uint32_t i = 0; i < bytes; i++)
    {
        checksum += data[i];
    }

    return checksum;
}

/*******************************************************************************************************************************************************************/

uint32_t tmc9660_param_getParameter(uint16_t icID, uint16_t type)
{
    uint32_t value = 0;

    tmc9660_param_sendCommand(icID, TMC9660_CMD_GAP, type, 0, value, &value);

    return value;
}

bool tmc9660_param_setParameter(uint16_t icID, uint16_t type, uint32_t value)
{
    int32_t result = tmc9660_param_sendCommand(icID, TMC9660_CMD_SAP, type, 0, value, &value);

    return result == TMC9660_PARAMSTATUS_OK;
}

uint32_t tmc9660_param_getGlobalParameter(uint16_t icID, uint16_t index)
{
    uint32_t value = 0;

    tmc9660_param_sendCommand(icID, TMC9660_CMD_GGP, index, 0, value, &value);

    return value;
}

bool tmc9660_param_setGlobalParameter(uint16_t icID, uint16_t index, uint32_t value)
{
    int32_t result = tmc9660_param_sendCommand(icID, TMC9660_CMD_SGP, index, 0, value, &value);

    return result == TMC9660_PARAMSTATUS_OK;
}
