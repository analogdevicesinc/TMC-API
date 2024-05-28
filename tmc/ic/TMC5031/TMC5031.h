/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5031_H_
#define TMC_IC_TMC5031_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "TMC5031_HW_Abstraction.h"

// => TMC-API wrapper
extern void tmc5031_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
// => TMC-API wrapper

int32_t tmc5031_readRegister(uint16_t icID, uint8_t address);
void tmc5031_writeRegister(uint16_t icID, uint8_t address, int32_t value);
void tmc5031_rotateMotor(uint16_t icID, uint8_t motor, int32_t velocity);


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
uint32_t value = tmc5031_readRegister(icID, field.address);

    return field_extract(value, field);
}

static inline uint32_t field_update(uint32_t data, RegisterField field, uint32_t value)
{
    return (data & (~field.mask)) | ((value << field.shift) & field.mask);
}

static inline void field_write(uint16_t icID, RegisterField field, uint32_t value)
{
	uint32_t regValue = tmc5031_readRegister(icID, field.address);

	regValue = field_update(regValue, field, value);

    tmc5031_writeRegister(icID, field.address, regValue);
}

/***************** The following code is TMC-EvalSystem specific and needs to be commented out when working with other MCUs e.g Arduino*****************************/

#include "tmc/helpers/API_Header.h"
extern ConfigurationTypeDef *TMC5031_config;

// Usage note: use 1 TypeDef per IC
typedef struct {
	int32_t velocity[2], oldX[2];
	uint32_t oldTick;
	int32_t registerResetState[TMC5031_REGISTER_COUNT];
	uint8_t registerAccess[TMC5031_REGISTER_COUNT];
	bool vMaxModified[2];
} TMC5031TypeDef;

extern TMC5031TypeDef TMC5031;

void tmc5031_initConfig(TMC5031TypeDef *TMC5031);
void tmc5031_periodicJob(uint8_t motor, uint32_t tick, TMC5031TypeDef *TMC5031, ConfigurationTypeDef *TMC5031_config);
uint8_t tmc5031_reset(ConfigurationTypeDef *TMC5031_config);
uint8_t tmc5031_restore(ConfigurationTypeDef *TMC5031_config);

#endif /* TMC_IC_TMC5031_H_ */
