/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5271_H_
#define TMC_IC_TMC5271_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5271_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1
/******************************************************************************/

// Default Register values
#define R00 0x00000008  // GCONF
#define R0A 0x00000020  // DRVCONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2A 0x0000000A  // D1
#define R2B 0x0000000A  // VSTOP
#define R30 0x0000000A  // D2

#define R3A 0x00010000  // ENC_CONST

#define R52 0x0B920F25  // OTW_OV_VTH
#define R60 0xAAAAB554  // MSLUT[0]
#define R61 0x4A9554AA  // MSLUT[1]
#define R62 0x24492929  // MSLUT[2]
#define R63 0x10104222  // MSLUT[3]
#define R64 0xFBFFFFFF  // MSLUT[4]
#define R65 0xB5BB777D  // MSLUT[5]
#define R66 0x49295556  // MSLUT[6]
#define R67 0x00404222  // MSLUT[7]
#define R68 0xFFFF8056  // MSLUT[8]
#define R69 0x00F70000  // MSLUT[9]

#define R6C 0x00410153  // CHOPCONF
#define R70 0xC44C001E  // PWMCONF
#define R74 0x00000000  // PWMCONF


typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
    IC_BUS_WLAN,
} TMC5271BusType;

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;

// => TMC-API wrapper
extern void tmc5271_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5271_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5271BusType tmc5271_getBusType(uint16_t icID);
extern uint8_t tmc5271_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5271_readRegister(uint16_t icID, uint8_t address);
void tmc5271_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5271_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);


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
