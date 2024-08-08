/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5271_H_
#define TMC_IC_TMC5271_H_

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5271_HW_Abstraction.h"

// Amount of CRC tables available
// Each table takes ~260 bytes (257 bytes, one bool and structure padding)
#define CRC_TABLE_COUNT 2

typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
    IC_BUS_WLAN,
} TMC5271BusType;

// => TMC-API wrapper
extern void tmc5271_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5271_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5271BusType tmc5271_getBusType(uint16_t icID);
extern uint8_t tmc5271_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5271_readRegister(uint16_t icID, uint8_t address);
void tmc5271_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5271_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

static inline uint32_t tmc5271_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc5271_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc5271_readRegister(icID, field.address);

    return tmc5271_fieldExtract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5271_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5271_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc5271_writeRegister(icID, field.address, regValue);
}


#endif /* TMC_IC_TMC5271_H_ */
