/*******************************************************************************
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2262_H_
#define TMC_IC_TMC2262_H_

#include "tmc/helpers/API_Header.h"
#include "TMC2262_HW_Abstraction.h"

//NEW_CODE_BEGIN
#define DEFAULT_MOTOR  0

// => TMC-API wrapper
extern void tmc2262_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern uint8_t tmc2262_getNodeAddress(uint16_t icID);
// => TMC-API wrapper

int32_t tmc2262_readRegister(uint16_t icID, uint8_t address);
void tmc2262_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc2262_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);
///
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
    uint32_t value = tmc2262_readRegister(icID, field.address);

    return field_extract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void field_write(uint16_t icID, RegisterField field, uint32_t value)
{
    uint32_t regValue = tmc2262_readRegister(icID, field.address);

    regValue = field_update(regValue, field, value);

    tmc2262_writeRegister(icID, field.address, regValue);
}
/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

//NEW_CODE_END

// Helper macros
#define TMC2262_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc2262_readInt(tdef, address), mask, shift)
#define TMC2262_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc2262_writeInt(tdef, address, FIELD_SET(tmc2262_readInt(tdef, address), mask, shift, value)))

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t velocity, oldX;
	uint32_t oldTick;
	uint8_t slaveAddress;
} TMC2262TypeDef;

void tmc2262_writeDatagram(TMC2262TypeDef *tmc2262, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc2262_writeInt(TMC2262TypeDef *tmc2262, uint8_t address, int32_t value);
int32_t tmc2262_readInt(TMC2262TypeDef *tmc2262, uint8_t address);

void tmc2262_init(TMC2262TypeDef *tmc2262, uint8_t channel, ConfigurationTypeDef *config);
uint8_t tmc2262_reset(TMC2262TypeDef *tmc2262);
uint8_t tmc2262_restore(TMC2262TypeDef *tmc2262);
uint8_t tmc2262_getSlaveAddress(TMC2262TypeDef *tmc2262);
void tmc2262_setSlaveAddress(TMC2262TypeDef *tmc2262, uint8_t slaveAddress);
void tmc2262_periodicJob(TMC2262TypeDef *tmc2262, uint32_t tick);

uint8_t tmc2262_consistencyCheck(TMC2262TypeDef *tmc2262);

#endif /* TMC_IC_TMC2262_H_ */
