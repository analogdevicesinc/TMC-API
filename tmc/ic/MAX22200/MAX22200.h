/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "MAX22200_HW_Abstraction.h"

int32_t max22200_readRegister(uint16_t icID, uint8_t address);
void max22200_writeRegister(uint16_t icID, uint8_t address, int32_t value);

extern void max22200_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength, bool cmd_mode);
