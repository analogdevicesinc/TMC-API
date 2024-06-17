/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5062.h"

TMC5062TypeDef TMC5062;

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

static int32_t readRegisterSPI(uint16_t icID, uint8_t address);
static void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value);
static int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress);
static void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value);
static uint8_t CRC8(uint8_t *data, uint32_t bytes);


int32_t tmc5062_readRegister(uint16_t icID, uint8_t address)
{
    TMC5062BusType bus = tmc5062_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        return readRegisterSPI(icID, address);
    }
    else if (bus == IC_BUS_UART)
    {
        return readRegisterUART(icID, address);
    }

    //ToDo: Error handling
    return -1;
}

void tmc5062_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
    TMC5062BusType bus = tmc5062_getBusType(icID);

    if(bus == IC_BUS_SPI)
    {
        writeRegisterSPI(icID, address, value);
    }
    else if(bus == IC_BUS_UART)
    {
        writeRegisterUART(icID, address, value);
    }
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
    address = TMC_ADDRESS(address);


    // register not readable -> shadow register copy
    if(!TMC_IS_READABLE(TMC5062.registerAccess[address]))
        return TMC5062.config->shadowRegister[address];

    uint8_t data[5] = { 0 };

    // clear write bit
    data[0] = address;

    // Send the read request
    tmc5062_readWriteSPI(icID, &data[0], sizeof(data));

    // Rewrite address and clear write bit
    data[0] = address;

    // Send another request to receive the read reply
    tmc5062_readWriteSPI(icID, &data[0], sizeof(data));

    return ((uint32_t)data[1] << 24) | ((uint32_t) data[2] << 16) | ( data[3] <<  8) | ( data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[5] = { 0 };

    data[0] = address | TMC5062_WRITE_BIT;
    data[1] = 0xFF & (value>>24);
    data[2] = 0xFF & (value>>16);
    data[3] = 0xFF & (value>>8);
    data[4] = 0xFF & (value>>0);

    // Send the write request
    tmc5062_readWriteSPI(icID, &data[0], sizeof(data));

    // Write to the shadow register and mark the register dirty
    address = TMC_ADDRESS(address);
    TMC5062.config->shadowRegister[address] = value;
    TMC5062.registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t readRegisterUART(uint16_t icID, uint8_t address)
{
    uint8_t data[7] = { 0 };

    address = address & TMC5062_ADDRESS_MASK;

    if (!TMC_IS_READABLE(TMC5062.registerAccess[address]))
        return TMC5062.config->shadowRegister[address];

    data[0] = 0x05;
    data[1] = address;
    data[2] = CRC8(data, 2);

    if (!tmc5062_readWriteUART(icID, &data[0], 3, 7))
        return 0;

    // Byte 0: Sync nibble correct?
    if (data[0] != 0xF5)
        return 0;

    // Byte 1: Master address correct?
    if (data[1] != address)
        return 0;

    // Byte 7: CRC correct?
    if (data[6] != CRC8(data, 6))
        return 0;

    return ((uint32_t)data[2] << 24) | ((uint32_t)data[3] << 16) | (data[4] << 8) | data[5];
}

void writeRegisterUART(uint16_t icID, uint8_t address, int32_t value)
{
    uint8_t data[7];

    data[0] = 0x05;
    data[1] = address | TMC5062_WRITE_BIT;
    data[2] = (value >> 24) & 0xFF;
    data[3] = (value >> 16) & 0xFF;
    data[4] = (value >> 8 ) & 0xFF;
    data[5] = (value      ) & 0xFF;
    data[6] = CRC8(data, 6);

    tmc5062_readWriteUART(icID, &data[0], 7, 0);
    // Write to the shadow register and mark the register dirty
    address = TMC_ADDRESS(address);
    TMC5062.config->shadowRegister[address] = value;
    TMC5062.registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc5062_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5062_MOTORS)
        return;

    tmc5062_writeRegister(icID, TMC5062_VMAX(motor), (velocity < 0) ? -velocity : velocity);
    tmc5062_fieldWrite(icID, TMC5062_RAMPMODE_FIELD(motor), (velocity >= 0) ? TMC5062_MODE_VELPOS : TMC5062_MODE_VELNEG);
}

static uint8_t CRC8(uint8_t *data, uint32_t bytes)
{
    uint8_t result = 0;
    uint8_t *table;

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

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

static void measureVelocity(TMC5062TypeDef *tmc5062, uint32_t tick);
static void writeConfiguration(TMC5062TypeDef *tmc5062);

void tmc5062_init(TMC5062TypeDef *tmc5062, ConfigurationTypeDef *tmc5062_config, const int32_t *registerResetState, uint8_t motorIndex0, uint8_t motorIndex1, uint32_t chipFrequency)
{
	tmc5062->motors[0] = motorIndex0;
	tmc5062->motors[1] = motorIndex1;

	tmc5062->chipFrequency  = chipFrequency;
	tmc5062->config = tmc5062_config;

	tmc5062->measurementInterval = 25; // Default: 25 ms
	tmc5062->oldTick        = 0;
	tmc5062->oldXActual[0]  = 0;
	tmc5062->oldXActual[1]  = 0;
	tmc5062->velocity[0]    = 0;
	tmc5062->velocity[1]    = 0;

	tmc5062->config->callback     = NULL;
	tmc5062->config->channel      = 0;
	tmc5062->config->configIndex  = 0;
	tmc5062->config->state        = CONFIG_READY;

	for(int32_t i = 0; i < TMC5062_REGISTER_COUNT; i++)
	{
		tmc5062->registerAccess[i] = tmc5062_defaultRegisterAccess[i];
		tmc5062->registerResetState[i]  = registerResetState[i];
	}
}

void tmc5062_fillShadowRegisters(TMC5062TypeDef *tmc5062)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc5062_RegisterConstants) == 0)
		return;

	size_t i, j;
	for(i = 0, j = 0; i < TMC5062_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc5062->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc5062_RegisterConstants) && (tmc5062_RegisterConstants[j].address < i))
			j++;

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc5062_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if(tmc5062_RegisterConstants[j].address == i)
			tmc5062->config->shadowRegister[i] = tmc5062_RegisterConstants[j].value;
	}
}

void tmc5062_setRegisterResetState(TMC5062TypeDef *tmc5062, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC5062_REGISTER_COUNT; i++)
		tmc5062->registerResetState[i] = resetState[i];
}

void tmc5062_setCallback(TMC5062TypeDef *tmc5062, tmc5062_callback callback)
{
	tmc5062->config->callback = (tmc_callback_config) callback;
}

static void writeConfiguration(TMC5062TypeDef *tmc5062)
{
	uint8_t *ptr = &tmc5062->config->configIndex;
	const int32_t *settings;

	if(tmc5062->config->state == CONFIG_RESTORE)
	{
		settings = tmc5062->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC5062_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc5062->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc5062->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC5062_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc5062->registerAccess[*ptr]))
			(*ptr)++;

	}

	if(*ptr < TMC5062_REGISTER_COUNT)
	{
		tmc5062_writeRegister(0, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc5062->config->callback)
		{
			((tmc5062_callback)tmc5062->config->callback)(tmc5062, tmc5062->config->state);
		}

		tmc5062->config->state = CONFIG_READY;
	}
}

void tmc5062_periodicJob(TMC5062TypeDef *tmc5062, uint32_t tick)
{
	if(tmc5062->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5062);
		return;
	}

	for(uint8_t motor = 0; motor < TMC5062_MOTORS; motor++)
	{
		if(dcStepActive(tmc5062, motor))
		{
			// Measure if any channel has active dcStep
			measureVelocity(tmc5062, tick);
			break;
		}
	}
}

uint8_t tmc5062_reset(TMC5062TypeDef *tmc5062)
{
	if(tmc5062->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC5062_REGISTER_COUNT; i++)
	{
		tmc5062->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc5062->config->shadowRegister[i] = 0;
	}

	tmc5062->config->state        = CONFIG_RESET;
	tmc5062->config->configIndex  = 0;

	return true;
}

uint8_t tmc5062_restore(TMC5062TypeDef *tmc5062)
{
	if(tmc5062->config->state != CONFIG_READY)
		return 0;

	tmc5062->config->state        = CONFIG_RESTORE;
	tmc5062->config->configIndex  = 0;

	return 1;
}

void tmc5062_rotate(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5062_MOTORS)
		return;

	tmc5062_writeRegister(motor, TMC5062_VMAX(motor), abs(velocity));
	tmc5062_writeRegister(motor, TMC5062_RAMPMODE(motor), (velocity >= 0) ? TMC5062_MODE_VELPOS : TMC5062_MODE_VELNEG);
}

void tmc5062_right(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity)
{
	return tmc5062_rotate(tmc5062, motor, velocity);
}

void tmc5062_left(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t velocity)
{
	return tmc5062_rotate(tmc5062, motor, -velocity);
}

void tmc5062_stop(TMC5062TypeDef *tmc5062, uint8_t motor)
{
	return tmc5062_rotate(tmc5062, motor, 0);
}

void tmc5062_moveTo(TMC5062TypeDef *tmc5062, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5062_MOTORS)
		return;

	tmc5062_writeRegister(motor, TMC5062_RAMPMODE(motor), TMC5062_MODE_POSITION);
	tmc5062_writeRegister(motor, TMC5062_VMAX(motor), velocityMax);
	tmc5062_writeRegister(motor, TMC5062_XTARGET(motor), position);
}

void tmc5062_moveBy(TMC5062TypeDef *tmc5062, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5062_readRegister(motor, TMC5062_XACTUAL(motor));

	return tmc5062_moveTo(tmc5062, motor, *ticks, velocityMax);
}

// Chopper settings
uint8_t calculateTOFF(uint32_t chopFreq, uint32_t clkFreq)
{
	// Calculate TOff from the clock and chopper frequencies (see documentation
	// for details). We add 16 before dividing by 32 to have rounding instead of flooring.
	uint8_t result = (((clkFreq / chopFreq / 4) - 12) + 16) / 32;

	result = MIN(15, result);
	result = MAX(1, result);

	return result;
}

// Diagnostics

// Stallguard

// Coolstep

// dcStep
uint8_t dcStepActive(TMC5062TypeDef *tmc5062, uint8_t motor)
{

	// vhighfs and vhighchm set?
	int32_t chopConf = tmc5062_readRegister(motor, TMC5062_CHOPCONF(motor));
	if((chopConf & (TMC5062_VHIGHFS_MASK | TMC5062_VHIGHCHM_MASK)) != (TMC5062_VHIGHFS_MASK | TMC5062_VHIGHCHM_MASK))
		return 0;

	// Velocity above dcStep velocity threshold?
	int32_t vActual = tmc5062_readRegister(motor, TMC5062_VACTUAL(motor));
	int32_t vDCMin  = tmc5062_readRegister(motor, TMC5062_VDCMIN(motor));

	return vActual >= vDCMin;
}

static void measureVelocity(TMC5062TypeDef *tmc5062, uint32_t tick)
{
	int32_t xActual;
	uint32_t tickDiff;

	if((tickDiff = tick - tmc5062->oldTick) >= tmc5062->measurementInterval)
	{
		for(uint8_t motor = 0; motor < TMC5062_MOTORS; motor++)
		{
			xActual = tmc5062_readRegister(motor, TMC5062_XACTUAL(motor));

			// Position difference gets multiplied by 1000 to compensate ticks being in milliseconds
			int32_t xDiff = (xActual - tmc5062->oldXActual[motor])* 1000;
			tmc5062->velocity[motor] = (xDiff) / ((float) tickDiff) * ((1<<24) / (float) tmc5062->chipFrequency);

			tmc5062->oldXActual[motor] = xActual;
		}
		tmc5062->oldTick = tick;
	}
}

// MSLUT
uint8_t setMicroStepTable(TMC5062TypeDef *tmc5062, uint8_t motor, TMC5062_MicroStepTable *table)
{
	if(motor >= TMC5062_MOTORS || table == 0 || tmc5062 == 0)
		return 0;

	tmc5062_writeRegister(motor, TMC5062_MSLUT0(motor), table->LUT_0);
	tmc5062_writeRegister(motor, TMC5062_MSLUT1(motor), table->LUT_1);
	tmc5062_writeRegister(motor, TMC5062_MSLUT2(motor), table->LUT_2);
	tmc5062_writeRegister(motor, TMC5062_MSLUT3(motor), table->LUT_3);
	tmc5062_writeRegister(motor, TMC5062_MSLUT4(motor), table->LUT_4);
	tmc5062_writeRegister(motor, TMC5062_MSLUT5(motor), table->LUT_5);
	tmc5062_writeRegister(motor, TMC5062_MSLUT6(motor), table->LUT_6);
	tmc5062_writeRegister(motor, TMC5062_MSLUT7(motor), table->LUT_7);

	uint32_t tmp =   ((uint32_t)table->X3 << 24) | ((uint32_t)table->X2 << 16) | (table->X1 << 8)
			     | (table->W3 <<  6) | (table->W2 <<  4) | (table->W1 << 2) | (table->W0);
	tmc5062_writeRegister(motor, TMC5062_MSLUTSEL(motor), tmp);

	tmp = ((uint32_t)table->START_SIN90 << 16) | (table->START_SIN);
	tmc5062_writeRegister(motor, TMC5062_MSLUTSTART(motor), tmp);

	return 1;
}

// Encoder
/* Calculate and set the encoder factor. Returns the deviation to the theoretical factor in
 * either binary or decimal form. To get the actual error value, divide the return type:
 * Binary:   Error = retVal / (2^16  * encoderResolution)
 * Decimal:  Error = retVal / (10000 * encoderResolution)
 * (Check the enc_sel_decimal bit in the ENCMODE register to find out which mode is used)
 */
uint32_t setEncoderFactor(TMC5062TypeDef *tmc5062, uint8_t motor, uint32_t motorFullSteps, uint32_t microSteps, uint32_t encoderResolution)
{
	int32_t numerator, denominator, remainder;
	int32_t binaryError, decimalError;
	uint8_t useDecimal, binaryRounded = false, decimalRounded = false;

	// Check for divisor 0
	// Return value here is inaccurate, this is just a protection against runtime/usage error.
	if(encoderResolution == 0)
		return 0;

	numerator = (motorFullSteps * microSteps) / encoderResolution;
	remainder = (motorFullSteps * microSteps) % encoderResolution;

	if((binaryError = (remainder << 16) % encoderResolution) == 0)
	{
		useDecimal = 0;
		denominator = (remainder << 16) / encoderResolution;
		remainder = 0;
	}
	else if((decimalError = (remainder * 10000) % encoderResolution) == 0)
	{
		useDecimal = 1;
		denominator = (remainder * 10000) / encoderResolution;
		remainder = 0;
	}
	else // No exact fraction possible -> calculate nearest value
	{
		// The integer division/modulo calculation results in flooring.
		// Compensate here to achieve rounding instead (smaller error)
		// (Cast to uint32_t to avoid compiler warning - variable is positive anyways)
		if((uint32_t) binaryError > (encoderResolution/2))
		{
			binaryError -= encoderResolution;
			binaryRounded = true;
		}

		if((uint32_t) decimalError > (encoderResolution/2))
		{
			decimalError -= encoderResolution;
			decimalRounded = true;
		}

		if((abs(binaryError) * 10000) <= (abs(decimalError) << 16))
		{
			// Binary error smaller -> use binary
			useDecimal = 0;
			denominator = (remainder << 16) / encoderResolution + ((binaryRounded)? 1:0);
			remainder = binaryRounded;
		}
		else
		{
			// Decimal error smaller -> use decimal
			useDecimal = 1;
			denominator = (remainder * 10000) / encoderResolution + ((decimalRounded)? 1:0);
			remainder = decimalRounded;
		}
	}

	uint32_t tmp = (numerator << 16) | (denominator & 0xFFFF);
	tmc5062_writeRegister(motor, TMC5062_ENC_CONST(motor), tmp);
	tmc5062_fieldWrite(motor, TMC5062_ENC_SEL_DECIMAL_FIELD(motor), useDecimal);

	return remainder;
}

