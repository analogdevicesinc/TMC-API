/*
 * TMC6200.c
 *
 *  Created on: 14.03.2018
 *      Author: ED
 */

#include "TMC6200.h"

// => SPI wrapper
extern u8 tmc6200_readwriteByte(u8 motor, u8 data, u8 lastTransfer);
// <= SPI wrapper

// spi access
int tmc6200_readInt(u8 motor, uint8 address)
{
	// clear write bit
	address = TMC_ADDRESS(address);

	// write address
	tmc6200_readwriteByte(motor, address, FALSE);

	// read data
	int value = tmc6200_readwriteByte(motor, 0, FALSE);
	value <<= 8;
	value |= tmc6200_readwriteByte(motor, 0, FALSE);
	value <<= 8;
	value |= tmc6200_readwriteByte(motor, 0, FALSE);
	value <<= 8;
	value |= tmc6200_readwriteByte(motor, 0, TRUE);

	return value;
}

void tmc6200_writeInt(u8 motor, uint8 address, int value)
{
	// write address
	tmc6200_readwriteByte(motor, address | TMC6200_WRITE_BIT, FALSE);

	// write value
	tmc6200_readwriteByte(motor, 0xFF & (value>>24), FALSE);
	tmc6200_readwriteByte(motor, 0xFF & (value>>16), FALSE);
	tmc6200_readwriteByte(motor, 0xFF & (value>>8), FALSE);
	tmc6200_readwriteByte(motor, 0xFF & (value>>0), TRUE);
}
