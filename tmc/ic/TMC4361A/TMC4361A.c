/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include "TMC4361A.h"

/**************************************************************** Cache Implementation *************************************************************************/
#if TMC4361A_CACHE == 0
static inline bool tmc4361A_cache(uint16_t icID, TMC4361ACacheOp operation, uint8_t address, uint32_t *value)
{
    UNUSED(icID);
    UNUSED(address);
    UNUSED(operation);
    return false;
}
#else
#if TMC4361A_ENABLE_TMC_CACHE == 1
uint8_t tmc4361A_dirtyBits[TMC4361A_IC_CACHE_COUNT][TMC4361A_REGISTER_COUNT / 8] = {0};
int32_t tmc4361A_shadowRegister[TMC4361A_IC_CACHE_COUNT][TMC4361A_REGISTER_COUNT];

void tmc4361A_setDirtyBit(uint16_t icID, uint8_t index, bool value)
{
    if (index >= TMC4361A_REGISTER_COUNT)
        return;

    uint8_t *tmp  = &tmc4361A_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    uint8_t mask  = 1 << shift;
    *tmp          = (((*tmp) & (~(mask))) | (((value) << (shift)) & (mask)));
}

bool tmc4361A_getDirtyBit(uint16_t icID, uint8_t index)
{
    if (index >= TMC4361A_REGISTER_COUNT)
        return false;

    uint8_t *tmp  = &tmc4361A_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    return ((*tmp) >> shift) & 1;
}

/*
 * This function is used to cache the value written to the Write-Only registers in the form of shadow array.
 * The shadow copy is then used to read these kinds of registers.
 */
bool tmc4361A_cache(uint16_t icID, TMC4361ACacheOp operation, uint8_t address, uint32_t *value)
{
    if (operation == TMC4361A_CACHE_READ)
    {
        // Check if the value should come from cache

        // Only supported chips have a cache
        if (icID >= TMC4361A_IC_CACHE_COUNT)
            return false;

        // Only non-readable registers care about caching
        // Note: This could also be used to cache i.e. RW config registers to reduce bus accesses
        if (TMC4361A_IS_READABLE(tmc4361A_registerAccess[address]))
            return false;

        // Grab the value from the cache
        *value = tmc4361A_shadowRegister[icID][address];
        return true;
    }
    else if (operation == TMC4361A_CACHE_WRITE || operation == TMC4361A_CACHE_FILL_DEFAULT)
    {
        // Fill the cache

        // only supported chips have a cache
        if (icID >= TMC4361A_IC_CACHE_COUNT)
            return false;

        // Write to the shadow register and mark the register dirty
        tmc4361A_shadowRegister[icID][address] = *value;
        if (operation == TMC4361A_CACHE_WRITE)
        {
            tmc4361A_setDirtyBit(icID, address, true);
        }
        return true;
    }
    return false;
}
void tmc4361A_initCache()
{
    // Check if we have constants defined
    if (ARRAY_SIZE(tmc4361A_RegisterConstants) == 0)
        return;

    size_t i, j, id;

    for (i = 0, j = 0; i < TMC4361A_REGISTER_COUNT; i++)
    {
        // We only need to worry about hardware preset, write-only registers
        // that have not yet been written (no dirty bit) here.
        if (tmc4361A_registerAccess[i] != TMC4361A_ACCESS_W_PRESET)
            continue;

        // Search the constant list for the current address. With the constant
        // list being sorted in ascended order, we can walk through the list
        // until the entry with an address equal or greater than i
        while (j < ARRAY_SIZE(tmc4361A_RegisterConstants) && (tmc4361A_RegisterConstants[j].address < i)) j++;

        // Abort when we reach the end of the constant list
        if (j == ARRAY_SIZE(tmc4361A_RegisterConstants))
            break;

        // If we have an entry for our current address, write the constant
        if (tmc4361A_RegisterConstants[j].address == i)
        {
            for (id = 0; id < TMC4361A_IC_CACHE_COUNT; id++)
            {
                uint32_t temp = tmc4361A_RegisterConstants[j].value;
                tmc4361A_cache(id, TMC4361A_CACHE_FILL_DEFAULT, i, &temp);
            }
        }
    }
}
#else
// User must implement their own cache
extern bool tmc4361A_cache(uint16_t icID, TMC4361ACacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/************************************************************** Register read / write Implementation ******************************************************************/

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);

int32_t tmc4361A_readRegister(uint16_t icID, uint8_t address)
{
    uint32_t value;

    // Read from cache for registers with write-only access
    if (tmc4361A_cache(icID, TMC4361A_CACHE_READ, address, &value))
        return value;

    return readRegisterSPI(icID, address);

    //ToDo: Error handling
    return -1;
}

void tmc4361A_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    writeRegisterSPI(icID, address, value);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = {0};

    data[0] = address | TMC4361A_WRITE_BIT;
    data[1] = 0xFF & (value >> 24);
    data[2] = 0xFF & (value >> 16);
    data[3] = 0xFF & (value >> 8);
    data[4] = 0xFF & (value >> 0);

    // Send the write request
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));

    tmc4361A_setStatus(icID, &data[0]);

    //Cache the registers with write-only access
    tmc4361A_cache(icID, TMC4361A_CACHE_WRITE, address, (uint32_t *)&value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t data[5] = {0};

    // clear write bit
    address = address & TMC4361A_ADDRESS_MASK;

    data[0] = address;
    // Send the read request
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));

    data[0] = address;
    // Send another request to receive the read reply
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));

    tmc4361A_setStatus(icID, &data[0]);

    return ((int32_t) data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] << 8) | ((int32_t) data[4]);
}
