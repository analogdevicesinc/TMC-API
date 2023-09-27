/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5062.h"

// => SPI wrapper
extern uint8_t tmc5062_readWrite(uint8_t motor, uint8_t data, uint8_t lastTransfer);
// <= SPI wrapper

static void measureVelocity(TMC5062TypeDef *tmc5062, uint32_t tick);
static void writeConfiguration(TMC5062TypeDef *tmc5062);

void tmc5062_writeInt(TMC5062TypeDef *tmc5062, uint8_t channel, uint8_t address, int32_t value)
{
	if(channel >= TMC5062_MOTORS)
		return;

	tmc5062_readWrite(tmc5062->motors[channel], address | TMC5062_WRITE_BIT, false);
	tmc5062_readWrite(tmc5062->motors[channel], value >> 24, false);
	tmc5062_readWrite(tmc5062->motors[channel], value >> 16, false);
	tmc5062_readWrite(tmc5062->motors[channel], value >>  8, false);
	tmc5062_readWrite(tmc5062->motors[channel], value,       true);

	tmc5062->config->shadowRegister[TMC_ADDRESS(address)] = value;
}

int32_t tmc5062_readInt(TMC5062TypeDef *tmc5062, uint8_t channel, uint8_t address)
{
	if(channel >= TMC5062_MOTORS)
		return 0;

	if(!TMC_IS_READABLE(tmc5062->registerAccess[TMC_ADDRESS(address)]))
		return tmc5062->config->shadowRegister[TMC_ADDRESS(address)];

	tmc5062_readWrite(tmc5062->motors[channel], address, false);
	tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	tmc5062_readWrite(tmc5062->motors[channel], 0, true);

	int32_t value = 0;

	tmc5062_readWrite(tmc5062->motors[channel], address, false);
	value |= tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	value <<= 8;
	value |= tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	value <<= 8;
	value |= tmc5062_readWrite(tmc5062->motors[channel], 0, false);
	value <<= 8;
	value |= tmc5062_readWrite(tmc5062->motors[channel], 0, true);

	return value;
}

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
		tmc5062_writeInt(tmc5062, 0, *ptr, settings[*ptr]);
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

	for(uint8_t channel = 0; channel < TMC5062_MOTORS; channel++)
	{
		if(dcStepActive(tmc5062, channel))
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

	tmc5062_writeInt(tmc5062, motor, TMC5062_VMAX(motor), abs(velocity));
	tmc5062_writeInt(tmc5062, motor, TMC5062_RAMPMODE(motor), (velocity >= 0) ? TMC5062_MODE_VELPOS : TMC5062_MODE_VELNEG);
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

	tmc5062_writeInt(tmc5062, motor, TMC5062_RAMPMODE(motor), TMC5062_MODE_POSITION);
	tmc5062_writeInt(tmc5062, motor, TMC5062_VMAX(motor), velocityMax);
	tmc5062_writeInt(tmc5062, motor, TMC5062_XTARGET(motor), position);
}

void tmc5062_moveBy(TMC5062TypeDef *tmc5062, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5062_readInt(tmc5062, motor, TMC5062_XACTUAL(motor));

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
uint8_t dcStepActive(TMC5062TypeDef *tmc5062, uint8_t channel)
{

	// vhighfs and vhighchm set?
	int32_t chopConf = tmc5062_readInt(tmc5062, channel, TMC5062_CHOPCONF(channel));
	if((chopConf & (TMC5062_VHIGHFS_MASK | TMC5062_VHIGHCHM_MASK)) != (TMC5062_VHIGHFS_MASK | TMC5062_VHIGHCHM_MASK))
		return 0;

	// Velocity above dcStep velocity threshold?
	int32_t vActual = tmc5062_readInt(tmc5062, channel, TMC5062_VACTUAL(channel));
	int32_t vDCMin  = tmc5062_readInt(tmc5062, channel, TMC5062_VDCMIN(channel));

	return vActual >= vDCMin;
}

static void measureVelocity(TMC5062TypeDef *tmc5062, uint32_t tick)
{
	int32_t xActual;
	uint32_t tickDiff;

	if((tickDiff = tick - tmc5062->oldTick) >= tmc5062->measurementInterval)
	{
		for(uint8_t channel = 0; channel < TMC5062_MOTORS; channel++)
		{
			xActual = tmc5062_readInt(tmc5062, channel, TMC5062_XACTUAL(channel));

			// Position difference gets multiplied by 1000 to compensate ticks being in milliseconds
			int32_t xDiff = (xActual - tmc5062->oldXActual[channel])* 1000;
			tmc5062->velocity[channel] = (xDiff) / ((float) tickDiff) * ((1<<24) / (float) tmc5062->chipFrequency);

			tmc5062->oldXActual[channel] = xActual;
		}
		tmc5062->oldTick = tick;
	}
}

// MSLUT
uint8_t setMicroStepTable(TMC5062TypeDef *tmc5062, uint8_t channel, TMC5062_MicroStepTable *table)
{
	if(channel >= TMC5062_MOTORS || table == 0 || tmc5062 == 0)
		return 0;

	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT0(channel), table->LUT_0);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT1(channel), table->LUT_1);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT2(channel), table->LUT_2);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT3(channel), table->LUT_3);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT4(channel), table->LUT_4);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT5(channel), table->LUT_5);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT6(channel), table->LUT_6);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUT7(channel), table->LUT_7);

	uint32_t tmp =   ((uint32_t)table->X3 << 24) | ((uint32_t)table->X2 << 16) | (table->X1 << 8)
			     | (table->W3 <<  6) | (table->W2 <<  4) | (table->W1 << 2) | (table->W0);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUTSEL(channel), tmp);

	tmp = ((uint32_t)table->START_SIN90 << 16) | (table->START_SIN);
	tmc5062_writeInt(tmc5062, channel, TMC5062_MSLUTSTART(channel), tmp);

	return 1;
}

// Encoder
/* Calculate and set the encoder factor. Returns the deviation to the theoretical factor in
 * either binary or decimal form. To get the actual error value, divide the return type:
 * Binary:   Error = retVal / (2^16  * encoderResolution)
 * Decimal:  Error = retVal / (10000 * encoderResolution)
 * (Check the enc_sel_decimal bit in the ENCMODE register to find out which mode is used)
 */
uint32_t setEncoderFactor(TMC5062TypeDef *tmc5062, uint8_t channel, uint32_t motorFullSteps, uint32_t microSteps, uint32_t encoderResolution)
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
	tmc5062_writeInt(tmc5062, channel, TMC5062_ENC_CONST(channel), tmp);
	TMC5062_FIELD_WRITE(tmc5062, channel, TMC5062_ENCMODE(channel), TMC5062_ENC_SEL_DECIMAL_MASK, TMC5062_ENC_SEL_DECIMAL_SHIFT, useDecimal);

	return remainder;
}

