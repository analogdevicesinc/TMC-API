/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef API_IC_MAX22216_H
#define API_IC_MAX22216_H

#include "tmc/helpers/API_Header.h"
#include "MAX22216_Fields.h"
#include "MAX22216_Register.h"
#include "MAX22216_Constants.h"

// Helper macros
#define MAX22216_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(max22216_readInt(tdef, address), mask, shift)
#define MAX22216_FIELD_WRITE(tdef, address, mask, shift, value) \
	(max22216_writeInt(tdef, address, FIELD_SET(max22216_readInt(tdef, address), mask, shift, value)))

// Usage note: use 1 TypeDef per IC
typedef struct {
	uint8_t channel;
	uint8_t slaveAddress;
	uint8_t crc_en;
} MAX22216TypeDef;

uint8_t max22216_CRC(uint8_t *data, size_t length);

void max22216_writeDatagram(MAX22216TypeDef *max22216, uint8_t address, uint8_t x1, uint8_t x2);
void max22216_writeInt(MAX22216TypeDef *max22216, uint8_t address, int16_t value);
int32_t max22216_readInt(MAX22216TypeDef *max22216, uint8_t address);

void max22216_writeIntDep(MAX22216TypeDef *max22216, uint8_t address, int32_t value, uint8_t dep_address, int32_t dep_value);
int32_t max22216_readIntDep(MAX22216TypeDef *max22216, uint8_t address, uint8_t dep_address, int32_t dep_value);

void max22216_init(MAX22216TypeDef *max22216, uint8_t channel);

uint8_t max22216_getSlaveAddress(const MAX22216TypeDef *max22216);
void max22216_setSlaveAddress(MAX22216TypeDef *max22216, uint8_t slaveAddress);

#endif /* API_IC_MAX22216_H */
