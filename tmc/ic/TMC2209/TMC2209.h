/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2209_H_
#define TMC_IC_TMC2209_H_

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC2209_HW_Abstraction.h"

// Amount of CRC tables available
// Each table takes ~260 bytes (257 bytes, one bool and structure padding)
#define CRC_TABLE_COUNT 2

// => TMC-API wrapper
extern bool tmc2209_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc2209_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc2209_readRegister(uint16_t icID, uint8_t address);
void tmc2209_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc2209_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t field_extract(uint32_t data, RegisterField field)
{
    uint32_t value = (data & field.mask) >> field.shift;

    if (field.isSigned)
    {
        // Apply signedness conversion
        uint32_t baseMask = field.mask >> field.shift;
        uint32_t signMask = baseMask & (~baseMask >> 1);
        value = (value ^ signMask) - signMask;
    }

    return value;
}

static inline uint32_t field_read(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2209_readRegister(icID, field.address);

    return field_extract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void field_write(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2209_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc2209_writeRegister(icID, field.address, regValue);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

#include "tmc/helpers/API_Header.h"

// Usage note: use 1 TypeDef per IC
typedef struct {
    ConfigurationTypeDef *config;

    int32_t registerResetState[TMC2209_REGISTER_COUNT];
    uint8_t registerAccess[TMC2209_REGISTER_COUNT];

    uint8_t slaveAddress;
} TMC2209TypeDef;
extern TMC2209TypeDef TMC2209;

typedef void (*tmc2209_callback)(TMC2209TypeDef*, ConfigState);

// Default Register values
#define R00 0x00000040  // GCONF
#define R10 0x00071703  // IHOLD_IRUN
#define R11 0x00000014  // TPOWERDOWN
#define R6C 0x10000053  // CHOPCONF
#define R70 0xC10D0024  // PWMCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc2209_defaultRegisterAccess[TMC2209_REGISTER_COUNT] =
{
//  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
    0x03, 0x23, 0x01, 0x02, 0x02, 0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
    0x02, 0x02, 0x01, 0x02, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
    ____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
    0x02, 0x01, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x01, 0x01, 0x03, ____, ____, 0x01, // 0x60 - 0x6F
    0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc2209_defaultRegisterResetState[TMC2209_REGISTER_COUNT] =
{
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

// Communication
void tmc2209_init(TMC2209TypeDef *tmc2209, uint8_t channel, uint8_t slaveAddress, ConfigurationTypeDef *tmc2209_config, const int32_t *registerResetState);
uint8_t tmc2209_reset(TMC2209TypeDef *tmc2209);
uint8_t tmc2209_restore(TMC2209TypeDef *tmc2209);
void tmc2209_setRegisterResetState(TMC2209TypeDef *tmc2209, const int32_t *resetState);
void tmc2209_setCallback(TMC2209TypeDef *tmc2209, tmc2209_callback callback);
void tmc2209_periodicJob(TMC2209TypeDef *tmc2209, uint32_t tick);

uint8_t tmc2209_get_slave(TMC2209TypeDef *tmc2209);
void tmc2209_set_slave(TMC2209TypeDef *tmc2209, uint8_t slaveAddress);

#endif /* TMC_IC_TMC2209_H_ */
