/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2160.h"

/**************************************************************** Cache Implementation *************************************************************************/
#if TMC2160_CACHE == 0
static inline bool tmc2160_cache(uint16_t icID, TMC2160CacheOp operation, uint8_t address, uint32_t *value)
{
   UNUSED(icID);
   UNUSED(address);
   UNUSED(operation);
   return false;
}
#else
#if TMC2160_ENABLE_TMC_CACHE == 1

uint8_t tmc2160_dirtyBits[TMC2160_IC_CACHE_COUNT][TMC2160_REGISTER_COUNT/8]= {0};
int32_t tmc2160_shadowRegister[TMC2160_IC_CACHE_COUNT][TMC2160_REGISTER_COUNT];

void tmc2160_setDirtyBit(uint16_t icID, uint8_t index, bool value)
 {
    if(index >= TMC2160_REGISTER_COUNT)
        return;

    uint8_t *tmp = &tmc2160_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    uint8_t mask = 1 << shift;
    *tmp = (((*tmp) & (~(mask))) | (((value) << (shift)) & (mask)));
}

bool tmc2160_getDirtyBit(uint16_t icID, uint8_t index)
{
    if(index >= TMC2160_REGISTER_COUNT)
        return false;

    uint8_t *tmp = &tmc2160_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    return ((*tmp) >> shift) & 1;
}
/*
 * This function is used to cache the value written to the Write-Only registers in the form of shadow array.
 * The shadow copy is then used to read these kinds of registers.
 */

bool tmc2160_cache(uint16_t icID, TMC2160CacheOp operation, uint8_t address, uint32_t *value)
{
   if (operation == TMC2160_CACHE_READ)
   {
       // Check if the value should come from cache

       // Only supported chips have a cache
       if (icID >= TMC2160_IC_CACHE_COUNT)
           return false;

       // Only non-readable registers care about caching
       // Note: This could also be used to cache i.e. RW config registers to reduce bus accesses
       if (TMC2160_IS_READABLE(tmc2160_registerAccess[address]))
           return false;

       // Grab the value from the cache
       *value = tmc2160_shadowRegister[icID][address];
       return true;
   }
   else if (operation == TMC2160_CACHE_WRITE || operation == TMC2160_CACHE_FILL_DEFAULT)
   {
       // Fill the cache

       // only supported chips have a cache
       if (icID >= TMC2160_IC_CACHE_COUNT)
           return false;

       // Write to the shadow register.
       tmc2160_shadowRegister[icID][address] = *value;
       // For write operations, mark the register dirty
       if (operation == TMC2160_CACHE_WRITE)
       {
           tmc2160_setDirtyBit(icID, address, true);
       }

       return true;
   }
   return false;
}

void tmc2160_initCache()
{
   // Check if we have constants defined
   if(ARRAY_SIZE(tmc2160_RegisterConstants) == 0)
       return;

   size_t i, j, id, motor;

   for(i = 0, j = 0; i < TMC2160_REGISTER_COUNT; i++)
   {
       // We only need to worry about hardware preset, write-only registers
       // that have not yet been written (no dirty bit) here.
       if(tmc2160_registerAccess[i] != TMC2160_ACCESS_W_PRESET)
           continue;

       // Search the constant list for the current address. With the constant
       // list being sorted in ascended order, we can walk through the list
       // until the entry with an address equal or greater than i
       while(j < ARRAY_SIZE(tmc2160_RegisterConstants) && (tmc2160_RegisterConstants[j].address < i))
           j++;

      // Abort when we reach the end of the constant list
       if (j == ARRAY_SIZE(tmc2160_RegisterConstants))
           break;

       // If we have an entry for our current address, write the constant
      if(tmc2160_RegisterConstants[j].address == i)
       {
           for (id = 0; id < TMC2160_IC_CACHE_COUNT; id++)
           {
               tmc2160_cache(id, TMC2160_CACHE_FILL_DEFAULT, i, &tmc2160_RegisterConstants[j].value);
           }
      }
   }
}
#else
// User must implement their own cache
extern bool tmc2160_cache(uint16_t icID, TMC2160CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/************************************************************* read / write Implementation *********************************************************************/

TMC2160TypeDef TMC2160;

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc2160_readRegister(uint16_t icID, uint8_t address)
{
        return readRegisterSPI(icID, address);

    // ToDo: Error handling
}
void tmc2160_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
        writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    uint8_t data[5] = { 0 };
    uint32_t value;

    // Read from cache for registers with write-only access
    if (tmc2160_cache(icID, TMC2160_CACHE_READ, address, &value))
        return value;


    // Send the read request
    tmc2160_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC2160_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc2160_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC2160_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc2160_readWriteSPI(icID, &data[0], sizeof(data));

    //Cache the registers with write-only access
    tmc2160_cache(icID, TMC2160_CACHE_WRITE, address, &value);


/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

void tmc2160_init(TMC2160TypeDef *tmc2160, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
    tmc2160->config = config;

    tmc2160->config->callback     = NULL;
    tmc2160->config->channel      = channel;
    tmc2160->config->configIndex  = 0;
    tmc2160->config->state        = CONFIG_READY;

    int32_t i;
    for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
    {
        tmc2160->registerAccess[i]      = tmc2160_defaultRegisterAccess[i];
        tmc2160->registerResetState[i]  = registerResetState[i];
    }
}

void tmc2160_fillShadowRegisters(TMC2160TypeDef *tmc2160)
{
    // Check if we have constants defined
    if(ARRAY_SIZE(tmc2160_RegisterConstants) == 0)
        return;

    size_t i, j;
    for (i = 0, j = 0; i < TMC2160_REGISTER_COUNT; i++)
    {
        // We only need to worry about hardware preset, write-only registers
        // that have not yet been written (no dirty bit) here.
        if(tmc2160->registerAccess[i] != TMC_ACCESS_W_PRESET)
            continue;

        // Search the constant list for the current address. With the constant
        // list being sorted in ascended order, we can walk through the list
        // until the entry with an address equal or greater than i
        while(j < ARRAY_SIZE(tmc2160_RegisterConstants) && (tmc2160_RegisterConstants[j].address < i))
            j++;

        // Abort when we reach the end of the constant list
        if (j == ARRAY_SIZE(tmc2160_RegisterConstants))
            break;

        // If we have an entry for our current address, write the constant
        if(tmc2160_RegisterConstants[j].address == i)
            tmc2160->config->shadowRegister[i] = tmc2160_RegisterConstants[j].value;
    }
}

uint8_t tmc2160_reset(TMC2160TypeDef *tmc2160)
{
    if(tmc2160->config->state != CONFIG_READY)
        return false;

    int32_t i;

    // Reset the dirty bits
    for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
        tmc2160->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

    tmc2160->config->state        = CONFIG_RESET;
    tmc2160->config->configIndex  = 0;

    return true;
}

uint8_t tmc2160_restore(TMC2160TypeDef *tmc2160)
{
    if(tmc2160->config->state != CONFIG_READY)
        return false;

    tmc2160->config->state        = CONFIG_RESTORE;
    tmc2160->config->configIndex  = 0;

    return true;
}

void tmc2160_setRegisterResetState(TMC2160TypeDef *tmc2160, const int32_t *resetState)
{
    uint32_t i;
    for(i = 0; i < TMC2160_REGISTER_COUNT; i++)
        tmc2160->registerResetState[i] = resetState[i];
}

void tmc2160_setCallback(TMC2160TypeDef *tmc2160, tmc2160_callback callback)
{
    tmc2160->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC2160TypeDef *tmc2160)
{
    uint8_t *ptr = &tmc2160->config->configIndex;
    const int32_t *settings;

    if(tmc2160->config->state == CONFIG_RESTORE)
    {
        settings = tmc2160->config->shadowRegister;
        // Find the next restorable register
        while((*ptr < TMC2160_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2160->registerAccess[*ptr]))
            (*ptr)++;
    }
    else
    {
        settings = tmc2160->registerResetState;
        // Find the next resettable register
        while((*ptr < TMC2160_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2160->registerAccess[*ptr]))
            (*ptr)++;
    }

    if(*ptr < TMC2160_REGISTER_COUNT)
    {
        tmc2160_writeRegister(tmc2160, *ptr, settings[*ptr]);
        (*ptr)++;
    }
    else // Finished configuration
    {
        if(tmc2160->config->callback)
            ((tmc2160_callback)tmc2160->config->callback)(tmc2160, tmc2160->config->state);

        tmc2160->config->state = CONFIG_READY;
    }
}

void tmc2160_periodicJob(TMC2160TypeDef *tmc2160, uint32_t tick)
{
    UNUSED(tick);

    if(tmc2160->config->state != CONFIG_READY)
        writeConfiguration(tmc2160);
}

