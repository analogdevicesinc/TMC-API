/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5072.h"
TMC5072TypeDef TMC5072;

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


int32_t tmc5072_readRegister(uint16_t icID, uint8_t address)
{
	// register not readable -> shadow register copy
		if(!TMC_IS_READABLE(TMC5072.registerAccess[address]))
			return TMC5072.config->shadowRegister[address];

	TMC5072BusType bus = tmc5072_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		return readRegisterSPI(icID, address);
	}
	else if (bus == IC_BUS_UART)
	{
		return readRegisterUART(icID, address);
	}

	// ToDo: Error handling
	return -1;
}
void tmc5072_writeRegister(uint16_t icID, uint8_t address, int32_t value)
{
	TMC5072BusType bus = tmc5072_getBusType(icID);

	if(bus == IC_BUS_SPI)
	{
		writeRegisterSPI(icID, address, value);
	}
	else if(bus == IC_BUS_UART)
	{
		writeRegisterUART(icID, address, value);
	}
	//Write to the shadow register and mark the register dirty
	address = TMC_ADDRESS(address);
	TMC5072.config->shadowRegister[address] = value;
	TMC5072.registerAccess[address] |= TMC_ACCESS_DIRTY;
}

int32_t readRegisterSPI(uint16_t icID, uint8_t address)
{
	uint8_t data[5] = { 0 };

	// clear write bit
	data[0] = address & TMC5072_ADDRESS_MASK;

	// Send the read request
	tmc5072_readWriteSPI(icID, &data[0], sizeof(data));

	// Rewrite address and clear write bit
	data[0] = address & TMC5072_ADDRESS_MASK;

	// Send another request to receive the read reply
	tmc5072_readWriteSPI(icID, &data[0], sizeof(data));

	return ((int32_t)data[1] << 24) | ((int32_t) data[2] << 16) | ((int32_t) data[3] <<  8) | ((int32_t) data[4]);
}

void writeRegisterSPI(uint16_t icID, uint8_t address, int32_t value)
{
	uint8_t data[5] = { 0 };

	data[0] = address | TMC5072_WRITE_BIT;
	data[1] = 0xFF & (value>>24);
	data[2] = 0xFF & (value>>16);
	data[3] = 0xFF & (value>>8);
	data[4] = 0xFF & (value>>0);

	// Send the write request
	tmc5072_readWriteSPI(icID, &data[0], sizeof(data));
}

int32_t readRegisterUART(uint16_t icID, uint8_t registerAddress)
{
	uint8_t data[8] = { 0 };

	registerAddress = registerAddress & TMC5072_ADDRESS_MASK;

	data[0] = 0x05;
	data[1] = tmc5072_getNodeAddress(icID);
	data[2] = registerAddress;
	data[3] = CRC8(data, 3);

	if (!tmc5072_readWriteUART(icID, &data[0], 4, 8))
		return 0;

	// Byte 0: Sync nibble correct?
	if (data[0] != 0x05)
		return 0;

	// Byte 1: Master address correct?
	if (data[1] != 0xFF)
		return 0;

	// Byte 2: Address correct?
	if (data[2] != registerAddress)
		return 0;

	// Byte 7: CRC correct?
	if (data[7] != CRC8(data, 7))
		return 0;

	return ((uint32_t)data[3] << 24) | ((uint32_t)data[4] << 16) | (data[5] << 8) | data[6];
}

void writeRegisterUART(uint16_t icID, uint8_t registerAddress, int32_t value)
{
	uint8_t data[8];

	data[0] = 0x05;
	data[1] = tmc5072_getNodeAddress(icID);
	data[2] = registerAddress | TMC5072_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = CRC8(data, 7);

	tmc5072_readWriteUART(icID, &data[0], 8, 0);
}

void tmc5072_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity)
{
  if(motor >= TMC5072_MOTORS)
		return;

	tmc5072_writeRegister(icID, TMC5072_VMAX(motor), (velocity >= 0)? velocity : -velocity);
	field_write(icID, TMC5072_RAMPMODE_FIELD(motor), (velocity >= 0) ? TMC5072_MODE_VELPOS : TMC5072_MODE_VELNEG);
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
		tmc5072_writeRegister(tmc5072, *ptr, settings[*ptr]);
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
			x = tmc5072_readRegister(motor, TMC5072_XACTUAL(motor));
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

		tmc5072_writeRegister(motor, TMC5072_VMAX(motor), (velocity >= 0)? velocity : -velocity);
		field_write(motor, TMC5072_RAMPMODE_FIELD(motor), (velocity >= 0) ? TMC5072_MODE_VELPOS : TMC5072_MODE_VELNEG);
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

	tmc5072_writeRegister(motor, TMC5072_RAMPMODE(motor), TMC5072_MODE_POSITION);
	tmc5072_writeRegister(motor, TMC5072_VMAX(motor), velocityMax);
	tmc5072_writeRegister(motor, TMC5072_XTARGET(motor), position);
}

void tmc5072_moveBy(TMC5072TypeDef *tmc5072, uint8_t motor, uint32_t velocityMax, int32_t *ticks)
{
	// determine actual position and add numbers of ticks to move
	*ticks += tmc5072_readRegister(motor, TMC5072_XACTUAL(motor));

	return tmc5072_moveTo(tmc5072, motor, *ticks, velocityMax);
}
