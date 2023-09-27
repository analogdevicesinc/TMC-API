/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "MAX22216.h"

// => UART wrapper
extern void max22216_readWriteArray(uint8_t channel, uint8_t *data, size_t length);
// <= UART wrapper

// => CRC wrapper
//extern uint8_t max22216_CRC8(uint8_t *data, size_t length);
// <= CRC wrapper

// length in bits
uint8_t max22216_CRC(uint8_t *data, size_t length)
{
	uint8_t crc = 0b11111;
	uint8_t crc_old;
	for(size_t i = 0; i < length; i++) {
		crc_old = crc;
		crc = FIELD_SET(crc, (1 << 5), 5, FIELD_GET(crc_old, (1 << 4), 4));
		crc = FIELD_SET(crc, (1 << 4), 4, FIELD_GET(crc_old, (1 << 3), 3) ^ FIELD_GET(crc_old, (1 << 4), 4) ^ FIELD_GET(data[i / 8], (1 << (7 - (i % 8))), 7 - (i % 8)));
		crc = FIELD_SET(crc, (1 << 3), 3, FIELD_GET(crc_old, (1 << 2), 2));
		crc = FIELD_SET(crc, (1 << 2), 2, FIELD_GET(crc_old, (1 << 1), 1) ^ FIELD_GET(crc_old, (1 << 4), 4) ^ FIELD_GET(data[i / 8], (1 << (7 - (i % 8))), 7 - (i % 8)));
		crc = FIELD_SET(crc, (1 << 1), 1, FIELD_GET(crc_old, 1, 0));
		crc = FIELD_SET(crc, 1, 0, FIELD_GET(crc_old, (1 << 4), 4) ^ FIELD_GET(data[i / 8], (1 << (7 - (i % 8))), 7 - (i % 8)));
	}
	return (crc & 0x1F);
}

// Writes (x1 << 24) | (x2 << 16) | (x3 << 8) | x4 to the given address
void max22216_writeDatagram(MAX22216TypeDef *max22216, uint8_t address, uint8_t x1, uint8_t x2)
{
	uint8_t data[4];
	data[0] = address | TMC_WRITE_BIT;
	data[1] = x1;
	data[2] = x2;
	if(max22216->crc_en)
		data[3] = max22216_CRC(&data[0], 27);
	max22216_readWriteArray(max22216->channel, &data[0], (max22216->crc_en) ? 4 : 3);
}

void max22216_writeInt(MAX22216TypeDef *max22216, uint8_t address, int16_t value)
{
	max22216_writeDatagram(max22216, address, BYTE(value, 1), BYTE(value, 0));
}

int32_t max22216_readInt(MAX22216TypeDef *max22216, uint8_t address)
{
	address = TMC_ADDRESS(address);

	uint8_t data[4] = { 0, 0, 0, 0 };

	data[0] = address;
	if(max22216->crc_en)
		data[3] = max22216_CRC(&data[0], 27);
	max22216_readWriteArray(max22216->channel, &data[0], (max22216->crc_en) ? 4 : 3);

	data[0] = address;
	if(max22216->crc_en)
		data[3] = max22216_CRC(&data[0], 27);
	max22216_readWriteArray(max22216->channel, &data[0], (max22216->crc_en) ? 4 : 3);

	return _8_16(data[1], data[2]);
}

void max22216_writeInt_UART(MAX22216TypeDef *max22216, uint8_t address, int32_t value)
{
	uint8_t data[8];

	data[0] = MAX22216_SYNC_BYTE; // sync byte
	data[1] = max22216->slaveAddress;
	data[2] = address | TMC_WRITE_BIT;
	data[3] = (value >> 24) & 0xFF;
	data[4] = (value >> 16) & 0xFF;
	data[5] = (value >> 8 ) & 0xFF;
	data[6] = (value      ) & 0xFF;
	data[7] = max22216_CRC(data, 7);

	max22216_readWriteArray(max22216->channel, &data[0], 8);
}

int32_t max22216_readInt_UART(MAX22216TypeDef *max22216, uint8_t address)
{
	uint8_t data[8] = { 0 };

	data[0] = MAX22216_SYNC_BYTE;
	data[1] = max22216->slaveAddress;
	data[2] = address;
	data[7] = max22216_CRC(data, 3);

	max22216_readWriteArray(max22216->channel, &data[0], 8);

	// Byte 0: Sync byte correct?
	if (data[0] != MAX22216_SYNC_BYTE)
		return 0;

	// Byte 1: Master address correct?
	if (data[1] != MAX22216_MASTER_ADDRESS)
		return 0;

	// Byte 2: Address correct?
	if (data[2] != address)
		return 0;

	// Byte 7: CRC correct?
//	if (data[7] != max22216_CRC8(data, 7))
//		return 0;

	return _8_32(data[3], data[4], data[5], data[6]);
}

void max22216_writeIntDep(MAX22216TypeDef *max22216, uint8_t address, int32_t value, uint8_t dep_address, int32_t dep_value)
{
	int32_t old = max22216_readInt(max22216, dep_address);
	max22216_writeInt(max22216, dep_address, dep_value);
	max22216_writeInt(max22216, address, value);
	max22216_writeInt(max22216, dep_address, old);
}

int32_t max22216_readIntDep(MAX22216TypeDef *max22216, uint8_t address, uint8_t dep_address, int32_t dep_value)
{
	int32_t old = max22216_readInt(max22216, dep_address);
	max22216_writeInt(max22216, dep_address, dep_value);
	int32_t value = max22216_readInt(max22216, address);
	max22216_writeInt(max22216, dep_address, old);
	return value;
}

void max22216_init(MAX22216TypeDef *max22216, uint8_t channel)
{
	max22216->slaveAddress = channel;
	max22216->channel = channel;
	max22216->crc_en = 0;
}

uint8_t max22216_getSlaveAddress(const MAX22216TypeDef *max22216)
{
	return max22216->slaveAddress;
}

void max22216_setSlaveAddress(MAX22216TypeDef *max22216, uint8_t slaveAddress)
{
	max22216->slaveAddress = slaveAddress;
}

int16_t max22216_getS16CircleDifference(int16_t newValue, int16_t oldValue)
{
	return (newValue - oldValue);
}
