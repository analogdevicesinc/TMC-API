/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC7300_H_
#define TMC_IC_TMC7300_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC7300_HW_Abstraction.h"

#include "tmc/helpers/API_Header.h"

/************************************************************* read / write Implementation *********************************************************************/

// => TMC-API wrapper
extern bool tmc7300_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern uint8_t tmc7300_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc7300_readRegister(uint16_t icID, uint8_t address);
void tmc7300_writeRegister(uint16_t icID, uint8_t address, int32_t value);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc7300_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc7300_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc7300_readRegister(icID, field.address);

    return tmc7300_fieldExtract(value, field);
}

static inline uint32_t tmc7300_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}
// Usage note: use 1 TypeDef per IC
typedef struct {
    ConfigurationTypeDef *config;

static inline void tmc7300_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc7300_readRegister(icID, field.address);
    int32_t registerResetState[TMC7300_REGISTER_COUNT];
    uint8_t registerAccess[TMC7300_REGISTER_COUNT];

    regValue = tmc7300_fieldUpdate(regValue, field, value);
    uint8_t slaveAddress;
    uint8_t standbyEnabled;
} TMC7300TypeDef;

    tmc7300_writeRegister(icID, field.address, regValue);
typedef void (*tmc7300_callback)(TMC7300TypeDef*, ConfigState);

#define R00 0x00000007 // GCONF

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x42: write, has hardware presets on reset
//   0x43: read/write, has hardware presets on reset
static const uint8_t tmc7300_defaultRegisterAccess[TMC7300_REGISTER_COUNT] =
{
        //  0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
        0x03, 0x23, 0x01, 0x02, ____, ____, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x00 - 0x0F
        0x42, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
        ____, ____, 0x02, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x20 - 0x2F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x30 - 0x3F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, 0x43, ____, ____, 0x01, // 0x60 - 0x6F
        0x43, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

static const int32_t tmc7300_defaultRegisterResetState[TMC7300_REGISTER_COUNT] =
{
        //    0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
        R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x00 - 0x0F
        N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x20 - 0x2F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x30 - 0x3F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   N_A, 0,   0,   0, // 0x60 - 0x6F
        N_A, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // 0x70 - 0x7F
};

// Undefine the default register values.
// This prevents warnings in case multiple TMC-API chip headers are included at once
#undef R00

// Register constants (only required for 0x42 and 0x43 registers)
// This allows us to fill the shadow registers with the register content in
// order to provide the TMCL-IDE with correct values to display.
static const TMCRegisterConstant tmc7300_registerConstants[] =
{        // Use ascending addresses!
        { 0x10, 0x00001F01 }, // CURRENT_LIMIT
        { 0x6C, 0x13008001 }, // CHOPCONF
        { 0x70, 0xC40D1024 }, // PWMCONF
};


void tmc7300_writeInt(TMC7300TypeDef *tmc7300, uint8_t address, int32_t value);
int32_t tmc7300_readInt(TMC7300TypeDef *tmc7300, uint8_t address);

void tmc7300_init(TMC7300TypeDef *tmc7300, uint8_t channel, ConfigurationTypeDef *tmc7300_config, const int32_t *registerResetState);
uint8_t tmc7300_reset(TMC7300TypeDef *tmc7300);
uint8_t tmc7300_restore(TMC7300TypeDef *tmc7300);
void tmc7300_setRegisterResetState(TMC7300TypeDef *tmc7300, const int32_t *resetState);
void tmc7300_setCallback(TMC7300TypeDef *tmc7300, tmc7300_callback callback);
void tmc7300_periodicJob(TMC7300TypeDef *tmc7300, uint32_t tick);

uint8_t tmc7300_get_slave(TMC7300TypeDef *tmc7300);
void tmc7300_set_slave(TMC7300TypeDef *tmc7300, uint8_t slaveAddress);

uint8_t tmc7300_getStandby(TMC7300TypeDef *tmc7300);
void tmc7300_setStandby(TMC7300TypeDef *tmc7300, uint8_t standbyState);

uint8_t tmc7300_consistencyCheck(TMC7300TypeDef *tmc7300);

#endif /* TMC_IC_TMC7300_H_ */
