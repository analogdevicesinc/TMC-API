/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2660_H_
#define TMC_IC_TMC2660_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2660_Register.h"
#include "TMC2660_Constants.h"
#include "TMC2660_Fields.h"

#define TMC2660_FIELD_READ(motor, address, mask, shift)           FIELD_READ(tmc2660_readInt, motor, address, mask, shift)
#define TMC2660_FIELD_WRITE(motor, address, mask, shift, value)   FIELD_WRITE(tmc2660_writeInt, motor, address, mask, shift, value)
#define TMC2660_FIELD_UPDATE(motor, address, mask, shift, value)  FIELD_UPDATE(tmc2660_readInt, tmc2660_writeInt, motor, address | TMC2660_WRITE_BIT, mask, shift, value)

//-----------------------------------NEW CODE-----------------------------
// => TMC-API wrapper
extern unsigned char tmc2660_readWriteSPI(uint16_t icID, uint8_t data, uint8_t lastTransfer);
static const uint8_t tmc2660_defaultRegisterAccess[TMC2660_REGISTER_COUNT] =
{
    TMC_ACCESS_WRITE,  // 0: DRVCTRL
    TMC_ACCESS_NONE,   // 1: UNUSED
    TMC_ACCESS_NONE,   // 2: UNUSED
    TMC_ACCESS_NONE,   // 3: UNUSED
    TMC_ACCESS_WRITE,  // 4: CHOPCONF
    TMC_ACCESS_WRITE,  // 5: SMARTEN
    TMC_ACCESS_WRITE,  // 6: SGCSCONF
    TMC_ACCESS_WRITE   // 7: DRVCONF
};

static const int32_t tmc2660_defaultRegisterResetState[TMC2660_REGISTER_COUNT] =
{
    0x00000000,  // 0: DRVCTRL
    0x00000000,  // 1: UNUSED
    0x00000000,  // 2: UNUSED
    0x00000000,  // 3: UNUSED
    0x00091935,  // 4: CHOPCONF
    0x000A0000,  // 5: SMARTEN
    0x000D0505,  // 6: SGCSCONF
    0x000EF040   // 7: DRVCONF
};

typedef struct
{
    uint32_t mask;
    uint8_t shift;
    uint8_t address;
    bool isSigned;
} RegisterField;


static inline uint32_t tmc2660_fieldExtract(uint32_t data, RegisterField field)
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

static inline uint32_t tmc2660_fieldRead(uint16_t icID, RegisterField field)
{
    uint32_t value = tmc2660_readRegister(icID, field.address);

    return tmc2660_fieldExtract(value, field);
}

static inline uint32_t tmc2660_fieldUpdate(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void tmc2660_fieldWrite(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2660_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc2660_writeRegister(icID, field.address, regValue);
}
//-----------------------------------NEW CODE-----------------------------

// Usage note: use 1 TypeDef per IC
typedef struct {
    ConfigurationTypeDef *config;
	uint8_t standStillCurrentScale;
	uint32_t standStillTimeout;
	uint8_t isStandStillOverCurrent;
	uint8_t isStandStillCurrentLimit;
	uint8_t continuousModeEnable;
	uint8_t runCurrentScale;
	uint8_t coolStepInactiveValue;
	uint8_t coolStepActiveValue;
	uint32_t coolStepThreshold;
	int32_t velocity;
	int32_t oldX;
	uint32_t oldTick;
	uint8_t registerAccess[TMC2660_REGISTER_COUNT];
	int32_t registerResetState[TMC2660_REGISTER_COUNT];
} TMC2660TypeDef;
extern TMC2660TypeDef TMC2660;
void tmc2660_initConfig();
void tmc2660_periodicJob(uint32_t tick);
uint8_t tmc2660_reset();
uint8_t tmc2660_restore();
void tmc2660_writeInt(uint8_t motor, uint8_t address, int value);
uint32_t tmc2660_readInt(uint8_t motor, uint8_t address);

uint8_t tmx2660_getStatusBits();
void tmc2660_readWrite(uint8_t motor, uint32_t value);

#endif /* TMC_IC_TMC2660_H_ */
