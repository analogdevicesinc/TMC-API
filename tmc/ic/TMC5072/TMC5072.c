/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5072.h"

// => SPI wrapper
extern void tmc5072_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= SPI wrapper

void tmc5072_writeDatagram(TMC5072TypeDef *tmc5072, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
{
	uint8_t data[5] = { address | TMC5072_WRITE_BIT, x1, x2, x3, x4 };
	tmc5072_readWriteArray(tmc5072->config->channel, &data[0], 5);

	int32_t value = ((uint32_t)x1 << 24) | ((uint32_t)x2 << 16) | (x3 << 8) | x4;

	// Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	tmc5072->config->shadowRegister[address] = value;
	tmc5072->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void tmc5072_writeInt(TMC5072TypeDef *tmc5072, uint8_t address, int32_t value)
{
	tmc5072_writeDatagram(tmc5072, address, BYTE(value, 3), BYTE(value, 2), BYTE(value, 1), BYTE(value, 0));
}

int32_t tmc5072_readInt(TMC5072TypeDef *tmc5072, uint8_t address)
{
	address = TMC_ADDRESS(address);

	// register not readable -> shadow register copy
	if(!TMC_IS_READABLE(tmc5072->registerAccess[address]))
		return tmc5072->config->shadowRegister[address];

	uint8_t data[5] = { 0, 0, 0, 0, 0 };

	data[0] = address;
	tmc5072_readWriteArray(tmc5072->config->channel, &data[0], 5);

	data[0] = address;
	tmc5072_readWriteArray(tmc5072->config->channel, &data[0], 5);

	return ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | (data[3] << 8) | data[4];
}

//void tmc5072_writeDatagram(TMC5072TypeDef *tmc5072, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4)
//{
//	tmc5072_readWrite(tmc5072->channel, address | TMC5072_WRITE_BIT, false);
//	tmc5072_readWrite(tmc5072->channel, x1, false);
//	tmc5072_readWrite(tmc5072->channel, x2, false);
//	tmc5072_readWrite(tmc5072->channel, x3, false);
//	tmc5072_readWrite(tmc5072->channel, x4, true);
//
//	int32_t value = x1;
//	value <<= 8;
//	value |= x2;
//	value <<= 8;
//	value |= x3;
//	value <<= 8;
//	value |= x4;
//
//	tmc5072->shadowRegister[address & 0x7F] = value;
//}
//
//void tmc5072_writeInt(TMC5072TypeDef *tmc5072, uint8_t address, int32_t value)
//{
//	tmc5072_writeDatagram(tmc5072,  address, 0xFF & (value>>24), 0xFF & (value>>16), 0xFF & (value>>8), 0xFF & (value>>0));
//}
//
//int32_t tmc5072_readInt(TMC5072TypeDef *tmc5072, uint8_t address)
//{
//	address &= 0x7F;
//
//	// register not readable -> shadow register copy
//	if(!TMC_IS_READABLE(tmc5072->registerAccess[address]))
//		return tmc5072->shadowRegister[address];
//
//	tmc5072_readWrite(tmc5072->channel, address, false);
//	tmc5072_readWrite(tmc5072->channel, 0, false);
//	tmc5072_readWrite(tmc5072->channel, 0, false);
//	tmc5072_readWrite(tmc5072->channel ,0, false);
//	tmc5072_readWrite(tmc5072->channel, 0, true);
//
//	tmc5072_readWrite(tmc5072->channel, address, false);
//	int32_t value = tmc5072_readWrite(tmc5072->channel, 0, false);
//	value <<= 8;
//	value |= tmc5072_readWrite(tmc5072->channel, 0, false);
//	value <<= 8;
//	value |= tmc5072_readWrite(tmc5072->channel, 0, false);
//	value <<= 8;
//	value |= tmc5072_readWrite(tmc5072->channel, 0, true);
//
//	return value;
//}

// Provide the init function with a channel index (sent back in the SPI callback), a pointer to a ConfigurationTypeDef struct
// and a pointer to a int32_t array (size 128) holding the reset values that shall be used.
void tmc5072_init(TMC5072TypeDef *tmc5072, uint8_t channel, ConfigurationTypeDef *tmc5072_config, const int32_t *registerResetState)
{
	for(uint8_t motor = 0; motor < TMC5072_MOTORS; motor++)
	{
		tmc5072->velocity[motor] = 0;
		tmc5072->oldX[motor] = 0;
	}

	tmc5072->oldTick     = 0;
	tmc5072->config   = tmc5072_config;

	/*
	 * TODO: Config initialization
	 * We can either explicitly initialize in each IC's init respectively,
	 * or do that with a separate function config_init where also the channel is set.
	 */
	tmc5072->config->callback     = NULL;
	tmc5072->config->channel      = channel;
	tmc5072->config->configIndex  = 0;
	tmc5072->config->state        = CONFIG_READY;

	uint32_t i;
	for(i = 0; i < TMC5072_REGISTER_COUNT; i++)
	{
		tmc5072->registerAccess[i]      = tmc5072_defaultRegisterAccess[i];
		tmc5072->registerResetState[i]  = registerResetState[i];
	}
}

//void tmc5072_initConfig(TMC5072TypeDef *tmc5072)
//{
//	tmc5072->velocity[0]      = 0;
//	tmc5072->velocity[1]      = 0;
//	tmc5072->oldTick          = 0;
//	tmc5072->oldX[0]          = 0;
//	tmc5072->oldX[1]          = 0;
//	tmc5072->vMaxModified[0]  = false;
//	tmc5072->vMaxModified[1]  = false;
//
//	int32_t i;
//	for(i=0; i < TMC5072_REGISTER_COUNT; i++)
//	{
//		tmc5072->registerAccess[i]      = tmc5072_defaultRegisterAccess[i];
//		tmc5072->registerResetState[i]  = tmc5072_defaultRegisterResetState[i];
//	}
//}

void tmc5072_fillShadowRegisters(TMC5072TypeDef *tmc5072)
{
	// Check if we have constants defined
	if(ARRAY_SIZE(tmc5072_RegisterConstants) == 0)
		return;

	size_t i, j;
	for(i = 0, j = 0; i < TMC5072_REGISTER_COUNT; i++)
	{
		// We only need to worry about hardware preset, write-only registers
		// that have not yet been written (no dirty bit) here.
		if(tmc5072->registerAccess[i] != TMC_ACCESS_W_PRESET)
			continue;

		// Search the constant list for the current address. With the constant
		// list being sorted in ascended order, we can walk through the list
		// until the entry with an address equal or greater than i
		while(j < ARRAY_SIZE(tmc5072_RegisterConstants) && (tmc5072_RegisterConstants[j].address < i))
			j++;

		// Abort when we reach the end of the constant list
		if (j == ARRAY_SIZE(tmc5072_RegisterConstants))
			break;

		// If we have an entry for our current address, write the constant
		if(tmc5072_RegisterConstants[j].address == i)
			tmc5072->config->shadowRegister[i] = tmc5072_RegisterConstants[j].value;
	}
}

static void writeConfiguration(TMC5072TypeDef *tmc5072)
{
	uint8_t *ptr = &tmc5072->config->configIndex;
	const int32_t *settings;

	if(tmc5072->config->state == CONFIG_RESTORE)
	{
		settings = tmc5072->config->shadowRegister;
		// Find the next restorable register
		while((*ptr < TMC5072_REGISTER_COUNT) && !TMC_IS_RESTORABLE(tmc5072->registerAccess[*ptr]))
			(*ptr)++;
	}
	else
	{
		settings = tmc5072->registerResetState;
		// Find the next resettable register
		while((*ptr < TMC5072_REGISTER_COUNT) && !TMC_IS_RESETTABLE(tmc5072->registerAccess[*ptr]))
			(*ptr)++;

	}

	if(*ptr < TMC5072_REGISTER_COUNT)
	{
		tmc5072_writeInt(tmc5072, *ptr, settings[*ptr]);
		(*ptr)++;
	}
	else // Finished configuration
	{
		if(tmc5072->config->callback)
		{
			((tmc5072_callback)tmc5072->config->callback)(tmc5072, tmc5072->config->state);
		}

		tmc5072->config->state = CONFIG_READY;
	}
}

//void tmc5072_writeConfiguration(TMC5072TypeDef *tmc5072, ConfigurationTypeDef *TMC5072_config)
//{
//	uint8_t *ptr = &TMC5072_config->configIndex;
//	const int32_t *settings = (TMC5072_config->state == CONFIG_RESTORE) ? TMC5072_config->shadowRegister : tmc5072->registerResetState;
//	tmc5072->shadowRegister = TMC5072_config->shadowRegister; // TODO API 2: Find better position (LK)
//
//	while((*ptr < TMC5072_REGISTER_COUNT) && !TMC_IS_WRITABLE(tmc5072->registerAccess[*ptr]))
//		(*ptr)++;
//
//	if(*ptr < TMC5072_REGISTER_COUNT)
//	{
//		tmc5072_writeInt(tmc5072, *ptr, settings[*ptr]);
//		(*ptr)++;
//	}
//	else
//	{
//		TMC5072_config->state = CONFIG_READY;
//	}
//}

void tmc5072_periodicJob(TMC5072TypeDef *tmc5072, uint32_t tick)
{
	uint32_t tickDiff;

	if(tmc5072->config->state != CONFIG_READY)
	{
		writeConfiguration(tmc5072);
		return;
	}

	int32_t x;

	// Calculate velocity v = dx/dt
	if((tickDiff = tick - tmc5072->oldTick) >= 5)
	{
		for(uint8_t motor = 0; motor < TMC5072_MOTORS; motor++)
		{
			x = tmc5072_readInt(tmc5072, TMC5072_XACTUAL(motor));
			tmc5072->velocity[motor] = (uint32_t) ((float32_t) (abs(x - tmc5072->oldX[motor]) / (float32_t) tickDiff) * (float32_t) 1048.576);
			tmc5072->oldX[motor] = x;
		}
		tmc5072->oldTick  = tick;
	}
}

//void tmc5072_periodicJob(uint8_t motor, uint32_t tick, TMC5072TypeDef *tmc5072, ConfigurationTypeDef *TMC5072_config)
//{
//	int32_t xActual;
//	uint32_t tickDiff;
//
//	if(TMC5072_config->state != CONFIG_READY)
//	{
//		tmc5072_writeConfiguration(tmc5072, TMC5072_config);
//		return;
//	}
//
//	if((tickDiff = tick - tmc5072->oldTick) >= 5)
//	{
//
//		xActual = tmc5072_readInt(0, TMC5072_XACTUAL(motor));
//		TMC5072_config->shadowRegister[TMC5072_XACTUAL(motor)] = xActual;
//		tmc5072->velocity[motor] = (int32_t) ((float) (abs(xActual-tmc5072->oldX[motor]) / (float) tickDiff) * (float) 1048.576);
//		tmc5072->oldX[motor] = xActual;
//
//		// Not per motor:
//		/*xActual = tmc5072_readInt(motor, TMC5072_XACTUAL_1);
//		TMC562v3_config->shadowRegister[TMC5072_XACTUAL_1] = xActual;
//		TMC562V3.velocityMotor1 = (int32_t) ((float) (abs(xActual-oldX[0]) / (float) t) * (float) 1048.576);
//		tmc5072->oldX = xActual;
//
//		xActual = readInt(TMC5072_XACTUAL_2);
//		TMC562v3_config->shadowRegister[TMC5072_XACTUAL_2] = xActual;
//		TMC562V3.velocityMotor2 = (int32_t) ((float) (abs(xActual-oldX[1]) / (float) t) * (float) 1048.576);
//		tmc5072->oldX = xActual;*/
//
//		tmc5072->oldTick = tick;
//	}
//}

uint8_t tmc5072_reset(TMC5072TypeDef *tmc5072)
{
	if(tmc5072->config->state != CONFIG_READY)
		return false;

	// Reset the dirty bits and wipe the shadow registers
	for(size_t i = 0; i < TMC5072_REGISTER_COUNT; i++)
	{
		tmc5072->registerAccess[i] &= ~TMC_ACCESS_DIRTY;
		tmc5072->config->shadowRegister[i] = 0;
	}

	tmc5072->config->state        = CONFIG_RESET;
	tmc5072->config->configIndex  = 0;

	return true;
}

//uint8_t tmc5072_reset(ConfigurationTypeDef *TMC5072_config)
//{
//	if(TMC5072_config->state != CONFIG_READY)
//		return 0;
//
//	TMC5072_config->state        = CONFIG_RESET;
//	TMC5072_config->configIndex  = 0;
//
//	return 1;
//}

uint8_t tmc5072_restore(TMC5072TypeDef *tmc5072)
{
	if(tmc5072->config->state != CONFIG_READY)
		return 0;

	tmc5072->config->state        = CONFIG_RESTORE;
	tmc5072->config->configIndex  = 0;

	return 1;
}

void tmc5072_setRegisterResetState(TMC5072TypeDef *tmc5072, const int32_t *resetState)
{
	for(size_t i = 0; i < TMC5072_REGISTER_COUNT; i++)
		tmc5072->registerResetState[i] = resetState[i];
}

void tmc5072_setCallback(TMC5072TypeDef *tmc5072, tmc5072_callback callback)
{
	tmc5072->config->callback = (tmc_callback_config) callback;
}

void tmc5072_rotate(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity)
{
	if(motor >= TMC5072_MOTORS)
		return;

	tmc5072_writeInt(tmc5072, TMC5072_VMAX(motor), abs(velocity));
	tmc5072_writeDatagram(tmc5072, TMC5072_RAMPMODE(motor), 0, 0, 0, (velocity >= 0) ? TMC5072_MODE_VELPOS : TMC5072_MODE_VELNEG);
}

void tmc5072_right(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity)
{
	return tmc5072_rotate(tmc5072, motor, velocity);
}

void tmc5072_left(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t velocity)
{
	return tmc5072_rotate(tmc5072, motor, -velocity);
}

void tmc5072_stop(TMC5072TypeDef *tmc5072, uint8_t motor)
{
	return tmc5072_rotate(tmc5072, motor, 0);
}

void tmc5072_moveTo(TMC5072TypeDef *tmc5072, uint8_t motor, int32_t position, uint32_t velocityMax)
{
	if(motor >= TMC5072_MOTORS)
		return;

	tmc5072_writeInt(tmc5072, TMC5072_RAMPMODE(motor), TMC5072_MODE_POSITION);
	tmc5072_writeInt(tmc5072, TMC5072_VMAX(motor), velocityMax);
	tmc5072_writeInt(tmc5072, TMC5072_XTARGET(motor), position);
}

void tmc5072_moveBy(TMC5072TypeDef *tmc5072, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5072_readInt(tmc5072, TMC5072_XACTUAL(motor));

	return tmc5072_moveTo(tmc5072, motor, *ticks, velocityMax);
}
