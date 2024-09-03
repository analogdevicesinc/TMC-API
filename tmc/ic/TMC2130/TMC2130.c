/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2130.h"


/**************************************************************** Cache Implementation *************************************************************************/

#if TMC2130_CACHE == 0
static inline bool tmc2130_cache(uint16_t icID, TMC2130CacheOp operation, uint8_t address, uint32_t *value)
{
   UNUSED(icID);
   UNUSED(address);
   UNUSED(operation);
   return false;
}
#else
#if TMC2130_ENABLE_TMC_CACHE == 1

uint8_t tmc2130_dirtyBits[TMC2130_IC_CACHE_COUNT][TMC2130_REGISTER_COUNT/8]= {0};
int32_t tmc2130_shadowRegister[TMC2130_IC_CACHE_COUNT][TMC2130_REGISTER_COUNT];

void tmc2130_setDirtyBit(uint16_t icID, uint8_t index, bool value)
 {
    if(index >= TMC2130_REGISTER_COUNT)
        return;

    uint8_t *tmp = &tmc2130_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    uint8_t mask = 1 << shift;
    *tmp = (((*tmp) & (~(mask))) | (((value) << (shift)) & (mask)));
}

bool tmc2130_getDirtyBit(uint16_t icID, uint8_t index)
{
    if(index >= TMC2130_REGISTER_COUNT)
        return false;

    uint8_t *tmp = &tmc2130_dirtyBits[icID][index / 8];
    uint8_t shift = (index % 8);
    return ((*tmp) >> shift) & 1;
}
/*
 * This function is used to cache the value written to the Write-Only registers in the form of shadow array.
 * The shadow copy is then used to read these kinds of registers.
 */

bool tmc2130_cache(uint16_t icID, TMC2130CacheOp operation, uint8_t address, uint32_t *value)
{
   if (operation == TMC2130_CACHE_READ)
   {
       // Check if the value should come from cache

       // Only supported chips have a cache
       if (icID >= TMC2130_IC_CACHE_COUNT)
           return false;

       // Only non-readable registers care about caching
       // Note: This could also be used to cache i.e. RW config registers to reduce bus accesses
       if (TMC2130_IS_READABLE(tmc2130_registerAccess[address]))
           return false;

       // Grab the value from the cache
       *value = tmc2130_shadowRegister[icID][address];
       return true;
   }
   else if (operation == TMC2130_CACHE_WRITE || operation == TMC2130_CACHE_FILL_DEFAULT)
   {
       // Fill the cache

       // only supported chips have a cache
       if (icID >= TMC2130_IC_CACHE_COUNT)
           return false;

       // Write to the shadow register.
       tmc2130_shadowRegister[icID][address] = *value;
       // For write operations, mark the register dirty
       if (operation == TMC2130_CACHE_WRITE)
       {
           tmc2130_setDirtyBit(icID, address, true);
       }

       return true;
   }
   return false;
}

void tmc2130_initCache()
{
   // Check if we have constants defined
   if(ARRAY_SIZE(tmc2130_RegisterConstants) == 0)
       return;

   size_t i, j, id, motor;

   for(i = 0, j = 0; i < TMC2130_REGISTER_COUNT; i++)
   {
       // We only need to worry about hardware preset, write-only registers
       // that have not yet been written (no dirty bit) here.
       if(tmc2130_registerAccess[i] != TMC2130_ACCESS_W_PRESET)
           continue;

       // Search the constant list for the current address. With the constant
       // list being sorted in ascended order, we can walk through the list
       // until the entry with an address equal or greater than i
       while(j < ARRAY_SIZE(tmc2130_RegisterConstants) && (tmc2130_RegisterConstants[j].address < i))
           j++;

       // Abort when we reach the end of the constant list
       if (j == ARRAY_SIZE(tmc2130_RegisterConstants))
           break;

       // If we have an entry for our current address, write the constant
       if(tmc2130_RegisterConstants[j].address == i)
       {
           for (id = 0; id < TMC2130_IC_CACHE_COUNT; id++)
           {
               tmc2130_cache(id, TMC2130_CACHE_FILL_DEFAULT, i, &tmc2130_RegisterConstants[j].value);
           }
       }
   }
}
#else
// User must implement their own cache
extern bool tmc2130_cache(uint16_t icID, TMC2130CacheOp operation, uint8_t address, uint32_t *value);
#endif
#endif

/************************************************************* read / write Implementation *********************************************************************/
TMC2130TypeDef TMC2130;

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);


int32_t tmc2130_readRegister(uint16_t icID, uint8_t address)
{
    return readRegisterSPI(icID, address);
}
void tmc2130_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    writeRegisterSPI(icID, address, value);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{

    uint8_t data[5] = { 0 };
    uint32_t value;


    // Read from cache for registers with write-only access
    if (tmc2130_cache(icID, TMC2130_CACHE_READ, address, &value))
        return value;

    // clear write bit
    data[0] = address & TMC2130_ADDRESS_MASK;

    // Send the read request
    tmc2130_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address & TMC2130_ADDRESS_MASK;

    // Send another request to receive the read reply
    tmc2130_readWriteSPI(icID, &data[0], sizeof(data));

    return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC2130_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc2130_readWriteSPI(icID, &data[0], sizeof(data));
    //Cache the registers with write-only access
    tmc2130_cache(icID, TMC2130_CACHE_WRITE, address, &value);
}
/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

// Initialize a TMC2130 IC.
// This function requires:
//     - channel: The channel index, which will be sent back in the SPI callback
//     - tmc2130_config: A ConfigurationTypeDef struct, which will be used by the IC
//     - registerResetState: An int32_t array with 128 elements. This holds the values to be used for a reset.
void tmc2130_init(TMC2130TypeDef *tmc2130, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
    tmc2130->config               = config;
    tmc2130->config->callback     = NULL;
    tmc2130->config->channel      = channel;
    tmc2130->config->configIndex  = 0;
    tmc2130->config->state        = CONFIG_READY;

    size_t i;
    for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
    {
        tmc2130->registerAccess[i]      = tmc2130_defaultRegisterAccess[i];
        tmc2130->registerResetState[i]  = registerResetState[i];
    }
}

// Fill the shadow registers of hardware preset non-readable registers
// Only needed if you want to 'read' those registers e.g to display the value
// in the TMCL IDE register browser
void tmc2130_fillShadowRegisters(TMC2130TypeDef *tmc2130)
{
    // Check if we have constants defined
    if(ARRAY_SIZE(tmc2130_RegisterConstants) == 0)
        return;

    size_t i, j;
    for(i = 0, j = 0; i < TMC2130_REGISTER_COUNT; i++)
    {
        // We only need to worry about hardware preset, write-only registers
        // that have not yet been written (no dirty bit) here.
        if(tmc2130->registerAccess[i] != TMC_ACCESS_W_PRESET)
            continue;

        // Search the constant list for the current address. With the constant
        // list being sorted in ascended order, we can walk through the list
        // until the entry with an address equal or greater than i
        while(j < ARRAY_SIZE(tmc2130_RegisterConstants) && (tmc2130_RegisterConstants[j].address < i))
            j++;

        // Abort when we reach the end of the constant list
        if (j == ARRAY_SIZE(tmc2130_RegisterConstants))
            break;

        // If we have an entry for our current address, write the constant
        if(tmc2130_RegisterConstants[j].address == i)
        {
            tmc2130->config->shadowRegister[i] = tmc2130_RegisterConstants[j].value;
        }
    }
}

// Reset the TMC2130
uint8_t tmc2130_reset(TMC2130TypeDef *tmc2130)
{
    if(tmc2130->config->state != CONFIG_READY)
        return false;

    // Reset the dirty bits
    size_t i;
    for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
    {
        tmc2130->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
        tmc2130->config->shadowRegister[i] = 0;
    }

    tmc2130->config->state        = CONFIG_RESET;
    tmc2130->config->configIndex  = 0;

    return true;
}

// Restore the TMC2130 to the state stored in the shadow registers.
// This can be used to recover the IC configuration after a VM power loss.
uint8_t tmc2130_restore(TMC2130TypeDef *tmc2130)
{
    if(tmc2130->config->state != CONFIG_READY)
        return false;

    tmc2130->config->state        = CONFIG_RESTORE;
    tmc2130->config->configIndex  = 0;

    return true;
}

// Change the values the IC will be configured with when performing a reset.
void tmc2130_setRegisterResetState(TMC2130TypeDef *tmc2130, const int32_t *resetState)
{
    size_t i;
    for(i = 0; i < TMC2130_REGISTER_COUNT; i++)
    {
        tmc2130->registerResetState[i] = resetState[i];
    }
}

// Register a function to be called after completion of the configuration mechanism
void tmc2130_setCallback(TMC2130TypeDef *tmc2130, tmc2130_callback callback)
{
    tmc2130->config->callback = (tmc_callback_config) callback;
}

// Helper function: Configure the next register.
static void writeConfiguration(TMC2130TypeDef *tmc2130)
{
    uint8_t *ptr = &tmc2130->config->configIndex;
    const int32_t *settings;

    if(tmc2130->config->state == CONFIG_RESTORE)
    {
        settings = tmc2130->config->shadowRegister;
        // Find the next restorable register
        while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc2130->registerAccess[*ptr]))
        {
            (*ptr)++;
        }
    }
    else
    {
        settings = tmc2130->registerResetState;
        // Find the next resettable register
        while((*ptr < TMC2130_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc2130->registerAccess[*ptr]))
        {
            (*ptr)++;
        }
    }

    if(*ptr < TMC2130_REGISTER_COUNT)
    {
        tmc2130_writeRegister(DEFAULT_MOTOR, *ptr, settings[*ptr]);
        (*ptr)++;
    }
    else // Finished configuration
    {
        if(tmc2130->config->callback)
        {
            ((tmc2130_callback)tmc2130->config->callback)(tmc2130, tmc2130->config->state);
        }

        tmc2130->config->state = CONFIG_READY;
    }
}

// Call this periodically
void tmc2130_periodicJob(TMC2130TypeDef *tmc2130, uint32_t tick)
{
    UNUSED(tick);

    if(tmc2130->config->state != CONFIG_READY)
    {
        writeConfiguration(tmc2130);
    }
}
/***************************************************************************************************************************************************************/
