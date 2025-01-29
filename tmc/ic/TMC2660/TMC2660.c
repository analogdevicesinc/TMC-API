/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "TMC2660.h"

/**************************************************************** Cache Implementation *************************************************************************/

#if TMC2660_CACHE == 0
static inline bool tmc2660_cache(uint16_t icID, TMC2660CacheOp operation, uint8_t address, uint32_t *value)
{
    UNUSED(icID);
    UNUSED(address);
    UNUSED(operation);
    return false;
}
#else
#if TMC2660_ENABLE_TMC_CACHE == 1
int32_t tmc2660_shadowRegister[TMC2660_IC_CACHE_COUNT][TMC2660_REGISTER_COUNT];

/*
 * This function is used to cache the value written to the Write-Only registers in the form of shadow array.
 * The shadow copy is then used to read these kinds of registers.
 */
bool tmc2660_cache(uint16_t icID, TMC2660CacheOp operation, uint8_t address, uint32_t *value)
{
    if (operation == TMC2660_CACHE_READ)
    {
        // Check if the value should come from cache

        // Only supported chips have a cache
        if (icID >= TMC2660_IC_CACHE_COUNT)
            return false;

        // Only non-readable registers care about caching
        // Note: This could also be used to cache i.e. RW config registers to reduce bus accesses
        if (TMC2660_IS_READABLE(tmc2660_registerAccess[address]))
            return false;

        // Grab the value from the cache
        *value = tmc2660_shadowRegister[icID][address];
        return true;
    }
    else if (operation == TMC2660_CACHE_WRITE || operation == TMC2660_CACHE_FILL_DEFAULT)
    {
        // Fill the cache

        // only supported chips have a cache
        if (icID >= TMC2660_IC_CACHE_COUNT)
            return false;

        // Write to the shadow register
        tmc2660_shadowRegister[icID][address] = *value;

        return true;
    }
    return false;
}

#else
// User must implement their own cache
extern bool tmc2660_cache(uint16_t icID, TMC2660CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/************************************************************** Register read / write Implementation ******************************************************************/

void readWrite(uint8_t icID, uint32_t datagram)
{
    uint8_t data[3] = {0};
    uint32_t reply;
    uint8_t rdsel = TMC2660_GET_RDSEL(datagram);

    data[0] = 0xFF & (datagram >> 16);
    data[1] = 0xFF & (datagram >> 8);
    data[2] = 0xFF & (datagram >> 0);

    // Send 24 bytes of data and receive reply
    tmc2660_readWriteSPI(icID, &data[0], sizeof(data));

    reply = (data[0] << 16 | data[1] << 8 | data[2]) >> 4;

    // write value to response shadow register
    tmc2660_shadowRegister[icID][rdsel] = reply;

    // Store the latest response value to extract status bits in tmc2660_getStatusBits()
    tmc2660_shadowRegister[icID][TMC2660_RESPONSE_LATEST] = reply;

    // write value to response shadow register
    if (TMC2660_GET_ADDRESS(datagram) == TMC2660_DRVCONF)
        rdsel = TMC2660_GET_RDSEL(datagram);

    // write value to shadow register
    tmc2660_shadowRegister[icID][TMC2660_GET_ADDRESS(datagram) | TMC2660_WRITE_BIT] = datagram;
}

void readImmediately(uint8_t icID, uint8_t rdsel)
{
    // sets desired reply in DRVCONF register, resets it to previous settings whilst reading desired reply
    uint32_t value;

    // additional reading to keep all replies up to date
    value   = tmc2660_readRegister(0, TMC2660_DRVCONF); // buffer (value and drvConf) to write back later
    value &= ~TMC2660_SET_RDSEL(-1);       // clear RDSEL bits
    value |= TMC2660_SET_RDSEL(rdsel % 3); // set rdsel
    readWrite(icID, value);                // write to chip and readout reply
    readWrite(icID, value);              // write to chip and return desired reply
}

void tmc2660_writeRegister(uint8_t icID, uint8_t address, uint32_t value)
{
    // Don't write to read-only registers
    if (TMC2660_IS_READONLY_REGISTER(address))
        return;

    // Extract 20 bits of valid data
    value &= 0x0FFFFF;

    //Cache the registers with write-only access
    tmc2660_cache(icID, TMC2660_CACHE_WRITE, address, &value);

    // 0XF7 to mask the write bit
    if (!tmc2660_getcontinuousModeEnable(icID))
        readWrite(icID, TMC2660_DATAGRAM((address & 0xF7), value));
}

uint32_t tmc2660_readRegister(uint8_t icID, uint8_t address)
{
    uint32_t value;

    // Read from cache for registers with write-only access
    if (tmc2660_cache(icID, TMC2660_CACHE_READ, address, &value))
        return value;

    if (!tmc2660_getcontinuousModeEnable(icID))
    {
        // Read the read-only register, refreshing the cache
        readImmediately(icID, address);
    }

    // Return the read-only register from cache
    return tmc2660_shadowRegister[icID][address];
}

uint8_t tmc2660_getStatusBits(uint8_t icID)
{
    // Grab the status bits from the last request
    return tmc2660_shadowRegister[icID][TMC2660_RESPONSE_LATEST] & TMC2660_STATUS_MASK;
}
