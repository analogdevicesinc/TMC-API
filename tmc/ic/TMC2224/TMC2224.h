/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2224_H_
#define TMC_IC_TMC2224_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC2224_HW_Abstraction.h"
#include "tmc/helpers/API_Header.h"

int32_t tmc2224_readRegister(uint16_t icID, uint8_t address);
void tmc2224_writeRegister(uint16_t icID, uint8_t address, int32_t value);
// Default Register values
#define R00 0x00000141  // GCONF
#define R10 0x00001F00  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC10D0024  // PWMCONF

// Usage note: use 1 TypeDef per IC
typedef struct {
    ConfigurationTypeDef *config;
    int32_t velocity;
    int32_t oldX;
    uint32_t oldTick;
    int32_t registerResetState[TMC2224_REGISTER_COUNT];
    uint8_t registerAccess[TMC2224_REGISTER_COUNT];
    bool vMaxModified;
    uint8_t slave;
} TMC2224TypeDef;
extern TMC2224TypeDef TMC2224;

/* Register access permissions:
 * 0: none (reserved)
 * 1: read
 * 2: write
 * 3: read/write
 * 7: read^write (separate functions/values)
 */
static const uint8_t tmc2224_defaultRegisterAccess[TMC2224_REGISTER_COUNT] =
{
//  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    3, 3, 1, 2, 2, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, // 0x00 - 0x0F
    2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x10 - 0x1F
    0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x20 - 0x2F
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x30 - 0x3F
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x40 - 0x4F
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0x50 - 0x5F
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 0, 0, 1, // 0x60 - 0x6F
    3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 0x70 - 0x7F
};

static const int32_t tmc2224_defaultRegisterResetState[TMC2224_REGISTER_COUNT] = {
//  0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
    R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
    R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
    R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R00
#undef R10
#undef R11
#undef R6C
#undef R70

void tmc2224_initConfig(TMC2224TypeDef *TMC2224);
void tmc2224_periodicJob(uint8_t motor, uint32_t tick, TMC2224TypeDef *TMC2224, ConfigurationTypeDef *TMC2224_config);
uint8_t tmc2224_reset(TMC2224TypeDef *tmc2224, ConfigurationTypeDef *TMC2224_config);
uint8_t tmc2224_restore(ConfigurationTypeDef *TMC2224_config);

uint8_t tmc2224_get_slave(TMC2224TypeDef *tmc2224);
void tmc2224_set_slave(TMC2224TypeDef *tmc2224, uint8_t slave);

#endif /* TMC_IC_TMC2224_H_ */
