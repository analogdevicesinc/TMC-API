/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
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

}

{




}

// Send [length] bytes stored in the [data] array to a driver attached to the TMC4361A
// and overwrite [data] with the replies. data[0] is the first byte sent and received.
void tmc4361A_readWriteCover(TMC4361ATypeDef *tmc4361A, uint8_t *data, size_t length)
{
	// Buffering old values to not interrupt manual covering
	int32_t old_high = tmc4361A->config->shadowRegister[TMC4361A_COVER_HIGH_WR];
	int32_t old_low = tmc4361A->config->shadowRegister[TMC4361A_COVER_LOW_WR];

	// Check if datagram length is valid
	if(length == 0 || length > 8)
		return;

	uint8_t bytes[8] = { 0 };
	uint32_t tmp;
	size_t i;

	// Copy data into buffer of maximum cover datagram length (8 bytes)
	for(i = 0; i < length; i++)
		bytes[i] = data[length-i-1];

	// Send the datagram
	if(length > 4)
		tmc4361A_writeDatagram(tmc4361A, TMC4361A_COVER_HIGH_WR, bytes[7], bytes[6], bytes[5], bytes[4]);

	tmc4361A_writeDatagram(tmc4361A, TMC4361A_COVER_LOW_WR, bytes[3], bytes[2], bytes[1], bytes[0]);

	// Wait for datagram completion
	// TODO CHECK 3: Get the waiting for cover completion done properly (LH)
	for(i = 0; i < 100; i++)
		tmp = ACCESS_ONCE(i);

	// Read the reply
	if(length > 4)
	{
		tmp = tmc4361A_readInt(tmc4361A, TMC4361A_COVER_DRV_HIGH_RD);
		bytes[4] = BYTE(tmp, 0);
		bytes[5] = BYTE(tmp, 1);
		bytes[6] = BYTE(tmp, 2);
		bytes[7] = BYTE(tmp, 3);
	}
	tmp = tmc4361A_readInt(tmc4361A, TMC4361A_COVER_DRV_LOW_RD);
	bytes[0] = BYTE(tmp, 0);
	bytes[1] = BYTE(tmp, 1);
	bytes[2] = BYTE(tmp, 2);
	bytes[3] = BYTE(tmp, 3);

	// Write the reply to the data array
	for(i = 0; i < length; i++)
	{
		data[length-i-1] = bytes[i];
	}

	// Rewriting old values to prevent interrupting manual covering. Imitating unchanged values and state.
	tmc4361A_writeInt(tmc4361A, TMC4361A_COVER_HIGH_WR, old_high);
	tmc4361A->config->shadowRegister[TMC4361A_COVER_LOW_WR] = old_low;
}

// Provide the init function with a channel index (sent back in the SPI callback), a pointer to a ConfigurationTypeDef struct
// and a pointer to a int32_t array (size 128) holding the reset values that shall be used.
void tmc4361A_init(TMC4361ATypeDef *tmc4361A, uint8_t channel, ConfigurationTypeDef *config, const int32_t *registerResetState)
{
	tmc4361A->velocity  = 0;
	tmc4361A->oldTick   = 0;
	tmc4361A->oldX      = 0;
	tmc4361A->config    = config;

	tmc4361A->config->callback     = NULL;
	tmc4361A->config->channel      = channel;
	tmc4361A->config->configIndex  = 0;
	tmc4361A->config->state        = CONFIG_READY;

	int32_t i;
	for(i = 0; i < TMC4361A_REGISTER_COUNT; i++)
	{
		tmc4361A->registerAccess[i]      = tmc4361A_defaultRegisterAccess[i];
		tmc4361A->registerResetState[i]  = registerResetState[i];
	}
}

// Fill the shadow registers of hardware preset non-readable registers
// Only needed if you want to read out those registers to display the value
// (e.g. for the TMCL IDE register browser)
void tmc4361A_fillShadowRegisters(TMC4361ATypeDef *tmc4361A)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc4361A_RegisterConstants) == 0)
		return;

	size_t i, j;
	for(i = 0, j = 0; i < TMC4361A_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc4361A->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc4361A_RegisterConstants) && (tmc4361A_RegisterConstants[j].address < i))
			j++;

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc4361A_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if(tmc4361A_RegisterConstants[j].address == i)
			tmc4361A->config->shadowRegister[i] = tmc4361A_RegisterConstants[j].value;
	}
}

uint8_t tmc4361A_reset(TMC4361ATypeDef *tmc4361A)
{
	if(tmc4361A->config->state != CONFIG_READY)
		return 0;

	int32_t i;

	// Reset the dirty bits
	for(i = 0; i < TMC4361A_REGISTER_COUNT; i++)
		tmc4361A->registerAccess[i] &= ~TMC_ACCESS_DIRTY;

	tmc4361A->config->state        = CONFIG_RESET;
	tmc4361A->config->configIndex  = 0;

	return 1;
}

uint8_t tmc4361A_restore(TMC4361ATypeDef *tmc4361A)
{
	if(tmc4361A->config->state != CONFIG_READY)
		return 0;
/************************************************************** Register read / write Implementation ******************************************************************/

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
	tmc4361A->config->state        = CONFIG_RESTORE;
	tmc4361A->config->configIndex  = 0;

int32_t tmc4361A_readRegister(uint16_t icID, uint8_t address)
	return 1;
}

void tmc4361A_setRegisterResetState(TMC4361ATypeDef *tmc4361A, const int32_t *resetState)
{
    uint32_t value;
	uint32_t i;
	for(i = 0; i < TMC4361A_REGISTER_COUNT; i++)
		tmc4361A->registerResetState[i] = resetState[i];
}

    // Read from cache for registers with write-only access
    if (tmc4361A_cache(icID, TMC4361A_CACHE_READ, address, &value))
        return value;
void tmc4361A_setCallback(TMC4361ATypeDef *tmc4361A, tmc4361A_callback callback)
{
	tmc4361A->config->callback = (tmc_callback_config) callback;
}

    return readRegisterSPI(icID, address);

    //ToDo: Error handling
    return -1;
static void tmc4361A_writeConfiguration(TMC4361ATypeDef *tmc4361A)
{
	uint8_t *ptr = &tmc4361A->config->configIndex;
	const int32_t *settings;

	if(tmc4361A->config->state == CONFIG_RESTORE)
	{
		settings = &tmc4361A->config->shadowRegister[0];
		// Find the next restorable register
		while((*ptr < TMC4361A_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc4361A->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = &tmc4361A->registerResetState[0];
		// Find the next resettable register
		while((*ptr < TMC4361A_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc4361A->registerAccess[*ptr]))
			(*ptr)++;
	}

	if (*ptr < TMC4361A_REGISTER_COUNT) {
		tmc4361A_writeInt(tmc4361A, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else
	{
		if(tmc4361A->config->callback)
		{
			((tmc4361A_callback)tmc4361A->config->callback)(tmc4361A, tmc4361A->config->state);
		}

		tmc4361A->config->state = CONFIG_READY;
	}
}

void tmc4361A_writeRegister(uint16_t icID, uint8_t address, int32_t value)
void tmc4361A_periodicJob(TMC4361ATypeDef *tmc4361A, uint32_t tick)
{
    writeRegisterSPI(icID, address, value);
	if(tmc4361A->config->state != CONFIG_READY)
	{
		tmc4361A_writeConfiguration(tmc4361A);
		return;
	}

	if((tick - tmc4361A->oldTick) != 0)
	{
		tmc4361A_calibrateClosedLoop(tmc4361A, 0);
		tmc4361A->oldTick = tick;
	}
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
void tmc4361A_rotate(TMC4361ATypeDef *tmc4361A, int32_t velocity)
{
    uint8_t data[5] = {0};
	// Disable Position Mode
	TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_RAMPMODE, TMC4361A_OPERATION_MODE_MASK, TMC4361A_OPERATION_MODE_SHIFT, 0);

    data[0] = address | TMC4361A_WRITE_BIT;
    data[1] = 0xFF & (value >> 24);
    data[2] = 0xFF & (value >> 16);
    data[3] = 0xFF & (value >> 8);
    data[4] = 0xFF & (value >> 0);
	tmc4361A_writeInt(tmc4361A, TMC4361A_VMAX, tmc4361A_discardVelocityDecimals(velocity));
}

    // Send the write request
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));
void tmc4361A_right(TMC4361ATypeDef *tmc4361A, int32_t velocity)
{
	tmc4361A_rotate(tmc4361A, velocity);
}

    tmc4361A_setStatus(icID, &data[0]);
void tmc4361A_left(TMC4361ATypeDef *tmc4361A, int32_t velocity)
{
	tmc4361A_rotate(tmc4361A, -velocity);
}

    //Cache the registers with write-only access
    tmc4361A_cache(icID, TMC4361A_CACHE_WRITE, address, (uint32_t*)&value);
void tmc4361A_stop(TMC4361ATypeDef *tmc4361A)
{
	tmc4361A_rotate(tmc4361A, 0);
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
void tmc4361A_moveTo(TMC4361ATypeDef *tmc4361A, int32_t position, uint32_t velocityMax)
{
    uint8_t data[5] = {0};
	// Enable Position Mode
	TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_RAMPMODE, TMC4361A_OPERATION_MODE_MASK, TMC4361A_OPERATION_MODE_SHIFT, 1);

    // clear write bit
    address = address & TMC4361A_ADDRESS_MASK;
	tmc4361A_writeInt(tmc4361A, TMC4361A_VMAX, tmc4361A_discardVelocityDecimals(velocityMax));

    data[0] = address;
    // Send the read request
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));
	tmc4361A_writeInt(tmc4361A, TMC4361A_X_TARGET, position);
}

// The function will write the absolute target position to *ticks
void tmc4361A_moveBy(TMC4361ATypeDef *tmc4361A, int32_t *ticks, uint32_t velocityMax)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc4361A_readInt(tmc4361A, TMC4361A_XACTUAL);

    data[0] = address;
    // Send another request to receive the read reply
    tmc4361A_readWriteSPI(icID, &data[0], sizeof(data));
	tmc4361A_moveTo(tmc4361A, *ticks, velocityMax);
}

    tmc4361A_setStatus(icID, &data[0]);
int32_t tmc4361A_discardVelocityDecimals(int32_t value)
{
	if(abs(value) > 8000000)
	{
		value = (value < 0) ? -8000000 : 8000000;
	}
	return value << 8;
}

    return ((int32_t) data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] << 8) | ((int32_t) data[4]);
static uint8_t tmc4361A_moveToNextFullstep(TMC4361ATypeDef *tmc4361A)
{
	int32_t stepCount;

	// Motor must be stopped
	if(tmc4361A_readInt(tmc4361A, TMC4361A_VACTUAL) != 0)
	{
		// Not stopped
		return 0;
	}

	// Position mode, hold mode, low velocity
	tmc4361A_writeInt(tmc4361A, TMC4361A_RAMPMODE, 4);
	tmc4361A_writeInt(tmc4361A, TMC4361A_VMAX, 10000 << 8);

	// Current step count
	stepCount = TMC4361A_FIELD_READ(tmc4361A, TMC4361A_MSCNT_RD, TMC4361A_MSCNT_MASK, TMC4361A_MSCNT_SHIFT);
	// Get microstep value of step count (lowest 8 bits)
	stepCount = stepCount % 256;
	// Assume: 256 microsteps -> Fullsteps are at 128 + n*256
	stepCount = 128 - stepCount;

	if(stepCount == 0)
	{
		// Fullstep reached
		return 1;
	}

	// Fullstep not reached -> calculate next fullstep position
	stepCount += tmc4361A_readInt(tmc4361A, TMC4361A_XACTUAL);
	// Move to next fullstep position
	tmc4361A_writeInt(tmc4361A, TMC4361A_X_TARGET, stepCount);

	return 0;
}

uint8_t tmc4361A_calibrateClosedLoop(TMC4361ATypeDef *tmc4361A, uint8_t worker0master1)
{
	static uint8_t state = 0;
	static uint32_t oldRamp;

	uint32_t amax = 0;
	uint32_t dmax = 0;

	if(worker0master1 && state == 0)
		state = 1;

	switch(state)
	{
	case 1:
		amax = tmc4361A_readInt(tmc4361A, TMC4361A_AMAX);
		dmax = tmc4361A_readInt(tmc4361A, TMC4361A_DMAX);

		// Set ramp and motion parameters
		oldRamp = tmc4361A_readInt(tmc4361A, TMC4361A_RAMPMODE);
		tmc4361A_writeInt(tmc4361A, TMC4361A_RAMPMODE, TMC4361A_RAMP_POSITION | TMC4361A_RAMP_HOLD);
		tmc4361A_writeInt(tmc4361A, TMC4361A_AMAX, MAX(amax, 1000));
		tmc4361A_writeInt(tmc4361A, TMC4361A_DMAX, MAX(dmax, 1000));
		tmc4361A_writeInt(tmc4361A, TMC4361A_VMAX, 0);

		state = 2;
		break;
	case 2:
		// Clear encoder calibration bit
		TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_ENC_IN_CONF, TMC4361A_CL_CALIBRATION_EN_MASK, TMC4361A_CL_CALIBRATION_EN_SHIFT, 0);

		// Disable internal data regulation for closed loop operation in encoder config
		TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_ENC_IN_CONF, TMC4361A_REGULATION_MODUS_MASK, TMC4361A_REGULATION_MODUS_SHIFT, 1);

		if(tmc4361A_moveToNextFullstep(tmc4361A)) // move to next fullstep, motor must be stopped, poll until finished
			state = 3;
		break;
	case 3:
		// Start encoder calibration
		TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_ENC_IN_CONF, TMC4361A_CL_CALIBRATION_EN_MASK, TMC4361A_CL_CALIBRATION_EN_SHIFT, 1);

		state = 4;
		break;
	case 4:
		if(worker0master1)
			break;

		// Stop encoder calibration
		TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_ENC_IN_CONF, TMC4361A_CL_CALIBRATION_EN_MASK, TMC4361A_CL_CALIBRATION_EN_SHIFT, 0);
		// Enable closed loop in encoder config
		TMC4361A_FIELD_WRITE(tmc4361A, TMC4361A_ENC_IN_CONF, TMC4361A_REGULATION_MODUS_MASK, TMC4361A_REGULATION_MODUS_SHIFT, 1);
		// Restore old ramp mode, enable position mode
		tmc4361A_writeInt(tmc4361A, TMC4361A_RAMPMODE, TMC4361A_RAMP_POSITION | oldRamp);

		state = 5;
		break;
	case 5:
		state = 0;
		return 1;
		break;
	default:
		break;
	}
	return 0;
}
