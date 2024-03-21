/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
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
    uint32_t value = tmc5271_readRegister(icID, field.address);

    return field_extract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void field_write(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc5271_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc5271_writeRegister(icID, field.address, regValue);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

#include "tmc/helpers/API_Header.h"

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t oldX[TMC5271_MOTORS];
	int32_t velocity[TMC5271_MOTORS];
	uint32_t oldTick;
	int32_t registerResetState[TMC5271_REGISTER_COUNT];
	uint8_t registerAccess[TMC5271_REGISTER_COUNT];
	uint8_t slaveAddress;
} TMC5271TypeDef;

typedef void (*tmc5271_callback)(TMC5271TypeDef*, ConfigState);

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

//static const int32_t tmc5271_defaultRegisterResetState[TMC5271_REGISTER_COUNT] =
//{
////	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   A,   B,   C,   D,   E,   F
//	R00, 0,   0,   0,   0,   0,   0,   0,   0,   0,   R0A,   0,   0,   0,   0,   0, // 0x00 - 0x0F
//	R10, R11, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x10 - 0x1F
//	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R2A,   R2B, 0,   0,   0,   0, // 0x20 - 0x2F
//	R30,   0,   0,   0,   0,   0,   0,   0,   0,   0,   R3A, 0,   0,   0,   0,   0, // 0x30 - 0x3F
//	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x40 - 0x4F
//	0,   0,   R52,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x50 - 0x5F
//	R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, 0,   0,   R6C, 0,   0,   0, // 0x60 - 0x6F
//	R70, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, // 0x70 - 0x7F
//};

// Register access permissions:
//   0x00: none (reserved)
//   0x01: read
//   0x02: write
//   0x03: read/write
//   0x13: read/write, separate functions/values for reading or writing
//   0x23: read/write, flag register (write to clear)
//   0x42: write, has hardware presets on reset
//static const uint8_t tmc5271_defaultRegisterAccess[TMC5271_REGISTER_COUNT] =
//{
////	0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
//	0x03, 0x23, 0x01, 0x03, 0x03, 0x03, 0x03, ____, ____, ____, 0x03, 0x03, ____, ____, ____, ____, // 0x00 - 0x0F
//	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x10 - 0x1F
//	0x03, 0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, // 0x20 - 0x2F
//	0x03, 0x01, ____, 0x03, 0x03, 0x23, 0x01, ____, 0x03, 0x03, 0x03, 0x23, 0x01, 0x03, ____, ____, // 0x30 - 0x3F
//	____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x40 - 0x4F
//	0x01, 0x01, 0x03, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, // 0x50 - 0x5F
//	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x03, 0x01, // 0x60 - 0x6F
//	0x03, 0x01, 0x01, ____, 0x03, 0x01, 0x01, ____, ____, ____, ____, ____, ____, ____, ____, ____  // 0x70 - 0x7F
//};

// Register constants (only required for 0x42 registers, since we do not have
// any way to find out the content but want to hold the actual value in the
// shadow register so an application (i.e. the TMCL IDE) can still display
// the values. This only works when the register content is constant.
static const TMCRegisterConstant tmc5271_RegisterConstants[] =
{		// Use ascending addresses!
		///
};

//void tmc5271_writeDatagram(TMC5271TypeDef *tmc5271, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5271_writeInt(TMC5271TypeDef *tmc5271, uint8_t address, int32_t value);
int32_t tmc5271_readInt(TMC5271TypeDef *tmc5271, uint8_t address);

void tmc5271_init(TMC5271TypeDef *tmc5271, uint8_t channel, ConfigurationTypeDef *config);
//void tmc5271_fillShadowRegisters(TMC5271TypeDef *tmc5271);
uint8_t tmc5271_reset(TMC5271TypeDef *tmc5271);
uint8_t tmc5271_restore(TMC5271TypeDef *tmc5271);
uint8_t tmc5271_getSlaveAddress(TMC5271TypeDef *tmc5271);
void tmc5271_setSlaveAddress(TMC5271TypeDef *tmc5271, uint8_t slaveAddress);
void tmc5271_setRegisterResetState(TMC5271TypeDef *tmc5271, const int32_t *resetState);
void tmc5271_setCallback(TMC5271TypeDef *tmc5271, tmc5271_callback callback);
void tmc5271_periodicJob(TMC5271TypeDef *tmc5271, uint32_t tick);

void tmc5271_rotate(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity);
void tmc5271_right(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity);
void tmc5271_left(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t velocity);
void tmc5271_stop(TMC5271TypeDef *tmc5271, uint8_t motor);
void tmc5271_moveTo(TMC5271TypeDef *tmc5271, uint8_t motor, int32_t position, uint32_t velocityMax);
void tmc5271_moveBy(TMC5271TypeDef *tmc5271, uint8_t motor, uint32_t velocityMax, int32_t *ticks);


uint8_t tmc5271_consistencyCheck(TMC5271TypeDef *tmc5271);

#endif /* TMC_IC_TMC5271_H_ */
