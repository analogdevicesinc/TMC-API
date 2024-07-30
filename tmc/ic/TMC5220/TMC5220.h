/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5220_H_
#define TMC_IC_TMC5220_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
	IC_BUS_SPI,
	IC_BUS_UART,
} TMC5220BusType;

// => TMC-API wrapper
extern void tmc5220_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern TMC5220BusType tmc5220_getBusType(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5220_readRegister(uint16_t icID, uint8_t address);
void tmc5220_writeRegister(uint16_t icID, uint8_t address, int32_t value);

#endif /* TMC_IC_TMC5220_H_ */
