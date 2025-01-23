/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC_IC_TMC5240_H_
#define TMC_IC_TMC5240_H_

#include "TMC5240_HW_Abstraction.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

/******************************************************************************/

typedef enum {
    IC_BUS_SPI,
    IC_BUS_UART,
    IC_BUS_WLAN
} TMC5240BusType;

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;


// => TMC-API wrapper
extern void tmc5240_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc5240_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);
extern TMC5240BusType tmc5240_getBusType(uint16_t icID);
extern uint8_t tmc5240_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc5240_readRegister(uint16_t icID, uint8_t address);
void tmc5240_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5240_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);


static inline uint32_t tmc5240_fieldExtract(uint32_t data, RegisterField field)
{
    uint32_t value = (data & field.mask) >> field.shift;

    if (field.isSigned)
    {
        // Apply sign conversion
        uint32_t baseMask = field.mask >> field.shift;
        uint32_t signMask = baseMask & (~baseMask >> 1);
        value = (value ^ signMask) - signMask;
    }

    return value;
}

static inline uint32_t tmc5240_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc5240_readRegister(icID, field.address);
    return tmc5240_fieldExtract(value, field);
}

static inline uint32_t tmc5240_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc5240_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5240_readRegister(icID, field.address);

    regValue = tmc5240_fieldUpdate(regValue, field, value);

    tmc5240_writeRegister(icID, field.address, regValue);
}

/**************************************************************** DEFAULT REGISTER VALUES *************************************************************************/

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

#ifndef ____
    #define ____ 0x00
#endif
#ifndef N_A
    #define N_A 0x00
#endif

#define TMC5240_ACCESS_DIRTY       0x08  // Register has been written since reset -> shadow register is valid for restore
#define TMC5240_ACCESS_READ        0x01
#define TMC5240_IS_READABLE(x)     ((x) & TMC5240_ACCESS_READ)
#define ARRAY_SIZE(x)              (sizeof(x)/sizeof(x[0]))


static const int32_t tmc5240_sampleRegisterPreset[TMC5240_REGISTER_COUNT] =
{
//	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R0A,   0,   0,   0,   0,   0, // 0x00 - 0x0F
	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R2A,   R2B, 0,   0,   0,   0, // 0x20 - 0x2F
	R30,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
	0,   0,   R52,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
};

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
static const uint8_t tmc5240_registerAccess[TMC5240_REGISTER_COUNT] =
{
//	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
	0x03, 0x23, 0x01, 0x03, 0x03, 0x03, 0x03, ____, ____, ____, 0x03, 0x03, ____, ____, ____, ____, // 0x00 - 0x0F
	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x20 - 0x2F
	0x03, 0x01, ____, 0x03, 0x03, 0x23, 0x01, ____, 0x03, 0x03, 0x03, 0x23, 0x01, 0x03, ____, ____, // 0x30 - 0x3F
	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
	0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, // 0x60 - 0x6F
	0x03, 0x01, 0x01, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
};

/*******************************************************************************************************************************************************************/

#endif /* TMC_IC_TMC5240_H_ */
