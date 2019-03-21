/*
 * TMC6630.c
 *
 *  Created on: 27.01.2017
 *      Author: ED
 */

#include "TMC6630.h"

// => SPI wrapper
extern int32_t tmc6630_spi_readInt(uint8_t motor, uint8_t address);
extern void tmc6630_spi_writeInt(uint8_t motor, uint8_t address, int32_t value);
// <= SPI wrapper

#define BIT_0_TO_15		0
#define BIT_16_TO_31	1

uint8_t tmc6630_getMotionMode(uint8_t motor)
{
	return tmc6630_spi_readInt(motor, TMC6630_OP_MODE) & 0xFF;
}

void tmc6630_setMotionMode(uint8_t motor, uint8_t mode)
{
	// switch motion mode
	uint32_t actualModeRegister = tmc6630_spi_readInt(motor, TMC6630_OP_MODE);
	actualModeRegister &= 0xFFFFFF00;
	actualModeRegister |= mode;
	tmc6630_spi_writeInt(motor, TMC6630_OP_MODE, actualModeRegister);
}

uint16_t tmc6630_spi_readRegister16BitValue(uint8_t motor, uint8_t registerAddress, uint8_t channel)
{
	int tmp = tmc6630_spi_readInt(motor, registerAddress);

	// read one channel
	switch(channel)
	{
	case 0:
		return tmp & 0xFFFF;
		break;
	case 1:
		return (tmp >> 16) & 0xFFFF;
		break;
	}
	return 0;
}

void tmc6630_spi_writeRegister16BitValue(uint8_t motor, uint8_t address, uint8_t channel, uint16_t value)
{
	// read actual register content
	int tmp = tmc6630_spi_readInt(motor, address);

	// update one channel
	switch(channel)
	{
	case 0:
		tmp &= 0xFFFF0000;
		tmp |= value;
		break;
	case 1:
		tmp &= 0x0000FFFF;
		tmp |= (value << 16);
		break;
	}

	// Write the register
	tmc6630_spi_writeInt(motor, address, tmp);
}

// ===== pwm mode ===
int16_t tmc6630_getTargetPwmDuty(uint8_t motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_VALUE_RELATIV, BIT_0_TO_15);
}

void tmc6630_setTargetPwmDuty(uint8_t motor, int16_t targetPWM)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_PWM_EXT);
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_PWM_VALUE, BIT_0_TO_15, targetPWM);
}

int16_t tmc6630_getActualPwmDuty(uint8_t motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_VALUE_RELATIV, BIT_0_TO_15);
}

uint16_t tmc6630_getMaxPwmDuty(uint8_t motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_LIMIT_HIGH_LOW, BIT_16_TO_31);
}

void tmc6630_setMaxPwmDuty(uint8_t motor, uint16_t maxPWM)
{
	return tmc6630_spi_writeRegister16BitValue(motor, TMC6630_PWM_LIMIT_HIGH_LOW, BIT_16_TO_31, maxPWM);
}

// ===== torque mode ===
void tmc6630_setTargetTorque_raw(uint8_t motor, int32_t targetTorque)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_TORQUE);
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_TARGET_LIMIT_DDT, BIT_16_TO_31, targetTorque);
}

int32_t tmc6630_getTargetTorque_raw(uint8_t motor)
{
	return (int16_t)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_TARGET_LIMIT_DDT, BIT_16_TO_31);
}

int32_t tmc6630_getActualTorque_raw(uint8_t motor)
{
	return (int16_t)tmc6630_spi_readRegister16BitValue(motor, TMC6630_DIR_HALL_ACTUAL_ADC_IB, BIT_0_TO_15);
}

void tmc6630_setTargetTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t targetTorque)
{
	tmc6630_setTargetTorque_raw(motor, (targetTorque * 256) / (int32_t)torqueMeasurementFactor);
}

int32_t tmc6630_getTargetTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor)
{
	return (tmc6630_getTargetTorque_raw(motor) * (int32_t)torqueMeasurementFactor) / 256;
}

int32_t tmc6630_getActualTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor)
{
	return (tmc6630_getActualTorque_raw(motor) * (int32_t)torqueMeasurementFactor) / 256;
}

int16_t tmc6630_getMaxTorque_raw(uint8_t motor)
{
	return (int16_t)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_16_TO_31);
}

void tmc6630_setMaxTorque_raw(uint8_t motor, int16_t maxTorque)
{
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_16_TO_31, maxTorque);
}

int32_t tmc6630_getMaxTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor)
{
	return (tmc6630_getMaxTorque_raw(motor) * (int32_t)torqueMeasurementFactor) / 256;
}

void tmc6630_setMaxTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t maxTorque)
{
	tmc6630_setMaxTorque_raw(motor, (maxTorque * 256) / (int32_t)torqueMeasurementFactor);
}

int16_t tmc6630_getMinTorque_raw(uint8_t motor)
{
	return (int16_t)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_0_TO_15);
}

void tmc6630_setMinTorque_raw(uint8_t motor, int16_t minTorque)
{
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_0_TO_15, minTorque);
}

int32_t tmc6630_getMinTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor)
{
	return (tmc6630_getMinTorque_raw(motor) * (int32_t)torqueMeasurementFactor) / 256;
}

void tmc6630_setMinTorque_mA(uint8_t motor, int16_t torqueMeasurementFactor, int32_t minTorque)
{
	tmc6630_setMinTorque_raw(motor, (minTorque * 256) / (int32_t)torqueMeasurementFactor);
}

// velocity mode
void tmc6630_setTargetVelocity(uint8_t motor, int32_t targetVelocity)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_VELOCITY);
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_TARGET, targetVelocity);
}

int32_t tmc6630_getTargetVelocity(uint8_t motor)
{
	return (int32_t)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_TARGET);
}

int32_t tmc6630_getActualVelocity(uint8_t motor)
{
	return (int32_t)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_ACTUAL);
}

void tmc6630_setMaxVelocity(uint8_t motor, int32_t maxVelocity)
{
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_MAX, maxVelocity);
}

int32_t tmc6630_getMaxVelocity(uint8_t motor)
{
	return (int32_t)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_MAX);
}

void tmc6630_setMinVelocity(uint8_t motor, int32_t minVelocity)
{
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_MIN, minVelocity);
}

int32_t tmc6630_getMinVelocity(uint8_t motor)
{
	return (int32_t)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_MIN);
}
