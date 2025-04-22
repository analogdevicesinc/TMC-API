/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5031.h"
/**************************************************************** Cache Implementation *************************************************************************/

#if TMC5031_CACHE == 0
static inline bool tmc5031_cache(uint16_t icID, TMC5031CacheOp operation, uint8_t address, uint32_t *value)
{
    UNUSED(icID);
    UNUSED(address);
    UNUSED(operation);
    return false;
}
#else
#if TMC5031_ENABLE_TMC_CACHE == 1

uint8_t tmc5031_dirtyBits[TMC5031_IC_CACHE_COUNT][TMC5031_REGISTER_COUNT/8]= {0};
int32_t tmc5031_shadowRegister[TMC5031_IC_CACHE_COUNT][TMC5031_REGISTER_COUNT];

void tmc5031_setDirtyBit(uint16_t icID, uint8_t index, bool value)
 {
    if(index >= TMC5031_REGISTER_COUNT)
        return;

    uint8_t *tmp = &tmc5031_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    uint8_t mask = 1 << shift;
    *tmp = (((*tmp) & (~(mask))) | (((value) << (shift)) & (mask)));
}

bool tmc5031_getDirtyBit(uint16_t icID, uint8_t index)
{
    if(index >= TMC5031_REGISTER_COUNT)
        return false;

    uint8_t *tmp = &tmc5031_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    return ((*tmp) >> shift) & 1;
}
/*
 * This function is used to cache the value written to the Write-Only registers in the form of shadow array.
 * The shadow copy is then used to read these kinds of registers.
 */

bool tmc5031_cache(uint16_t icID, TMC5031CacheOp operation, uint8_t address, uint32_t *value)
{
    if (operation == TMC5031_CACHE_READ)
    {
        // Check if the value should come from cache

        // Only supported chips have a cache
        if (icID >= TMC5031_IC_CACHE_COUNT)
            return false;

        // Only non-readable registers care about caching
        // Note: This could also be used to cache i.e. RW config registers to reduce bus accesses
        if (TMC5031_IS_READABLE(tmc5031_registerAccess[address]))
            return false;

        // Grab the value from the cache
        *value = tmc5031_shadowRegister[icID][address];
        return true;
    }
    else if (operation == TMC5031_CACHE_WRITE || operation == TMC5031_CACHE_FILL_DEFAULT)
    {
        // Fill the cache

        // only supported chips have a cache
        if (icID >= TMC5031_IC_CACHE_COUNT)
            return false;

        // Write to the shadow register.
        tmc5031_shadowRegister[icID][address] = *value;
        // For write operations, mark the register dirty
        if (operation == TMC5031_CACHE_WRITE)
        {
            tmc5031_setDirtyBit(icID, address, true);
        }

        return true;
    }
    return false;
}

void tmc5031_initCache()
{
    // Check if we have constants defined
    if(ARRAY_SIZE(tmc5031_RegisterConstants) == 0)
        return;

    size_t i, j, id;

    for(i = 0, j = 0; i < TMC5031_REGISTER_COUNT; i++)
    {
        // We only need to worry about hardware preset, write-only registers
        // that have not yet been written (no dirty bit) here.
        if(tmc5031_registerAccess[i] != TMC5031_ACCESS_W_PRESET)
            continue;

        // Search the constant list for the current address. With the constant
        // list being sorted in ascended order, we can walk through the list
        // until the entry with an address equal or greater than i
        while(j < ARRAY_SIZE(tmc5031_RegisterConstants) && (tmc5031_RegisterConstants[j].address < i))
            j++;

        // Abort when we reach the end of the constant list
        if (j == ARRAY_SIZE(tmc5031_RegisterConstants))
            break;

        // If we have an entry for our current address, write the constant
        if(tmc5031_RegisterConstants[j].address == i)
        {
            for (id = 0; id < TMC5031_IC_CACHE_COUNT; id++)
            {
                uint32_t temp = tmc5031_RegisterConstants[j].value;
                tmc5031_cache(id, TMC5031_CACHE_FILL_DEFAULT, i, &temp);
            }
        }
    }
}
#else
// User must implement their own cache
extern bool tmc5031_cache(uint16_t icID, TMC5031CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif


/************************************************************* read / write Implementation *********************************************************************/


static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc5031_readRegister(uint16_t icID, uint8_t address)
{
    return readRegisterSPI(icID, address);
    // ToDo: Error handling
}

void tmc5031_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint32_t value;
    uint8_t data[5] = { 0 };

     // Read from cache for registers with write-only access
     if (tmc5031_cache(icID, TMC5031_CACHE_READ, address, &value))
         return value;

    // clear write bit
    data[0] = address & TMC5031_ADDRESS_MASK;

    // Send the read request
    tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC5031_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC5031_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc5031_readWriteSPI(icID, &data[0], sizeof(data));

    //Cache the registers with write-only access
    tmc5031_cache(icID, TMC5031_CACHE_WRITE, address, (uint32_t *)&value);
}
