/*
 * TMC6630.c
 *
 *  Created on: 27.01.2017
 *      Author: ED
 */

#include "TMC6630.h"

// => SPI wrapper
extern s32 tmc6630_spi_readInt(u8 motor, u8 address);
extern void tmc6630_spi_writeInt(u8 motor, u8 address, s32 value);
// <= SPI wrapper

#define BIT_0_TO_15		0
#define BIT_16_TO_31	1

u8 tmc6630_getMotionMode(u8 motor)
{
	return tmc6630_spi_readInt(motor, TMC6630_OP_MODE) & 0xFF;
}

void tmc6630_setMotionMode(u8 motor, u8 mode)
{
	// switch motion mode
	u32 actualModeRegister = tmc6630_spi_readInt(motor, TMC6630_OP_MODE);
	actualModeRegister &= 0xFFFFFF00;
	actualModeRegister |= mode;
	tmc6630_spi_writeInt(motor, TMC6630_OP_MODE, actualModeRegister);
}

u16 tmc6630_spi_readRegister16BitValue(u8 motor, u8 registerAddress, u8 channel)
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

void tmc6630_spi_writeRegister16BitValue(u8 motor, u8 address, u8 channel, u16 value)
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
s16 tmc6630_getTargetPwmDuty(u8 motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_VALUE_RELATIV, BIT_0_TO_15);
}

void tmc6630_setTargetPwmDuty(u8 motor, s16 targetPWM)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_PWM_EXT);
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_PWM_VALUE, BIT_0_TO_15, targetPWM);
}

s16 tmc6630_getActualPwmDuty(u8 motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_VALUE_RELATIV, BIT_0_TO_15);
}

u16 tmc6630_getMaxPwmDuty(u8 motor)
{
	return tmc6630_spi_readRegister16BitValue(motor, TMC6630_PWM_LIMIT_HIGH_LOW, BIT_16_TO_31);
}

void tmc6630_setMaxPwmDuty(u8 motor, u16 maxPWM)
{
	return tmc6630_spi_writeRegister16BitValue(motor, TMC6630_PWM_LIMIT_HIGH_LOW, BIT_16_TO_31, maxPWM);
}

// ===== torque mode ===
void tmc6630_setTargetTorque_raw(u8 motor, s32 targetTorque)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_TORQUE);
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_TARGET_LIMIT_DDT, BIT_16_TO_31, targetTorque);
}

s32 tmc6630_getTargetTorque_raw(u8 motor)
{
	return (s16)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_TARGET_LIMIT_DDT, BIT_16_TO_31);
}

s32 tmc6630_getActualTorque_raw(u8 motor)
{
	return (s16)tmc6630_spi_readRegister16BitValue(motor, TMC6630_DIR_HALL_ACTUAL_ADC_IB, BIT_0_TO_15);
}

void tmc6630_setTargetTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 targetTorque)
{
	tmc6630_setTargetTorque_raw(motor, (targetTorque * 256) / (s32)torqueMeasurementFactor);
}

s32 tmc6630_getTargetTorque_mA(u8 motor, s16 torqueMeasurementFactor)
{
	return (tmc6630_getTargetTorque_raw(motor) * (s32)torqueMeasurementFactor) / 256;
}

s32 tmc6630_getActualTorque_mA(u8 motor, s16 torqueMeasurementFactor)
{
	return (tmc6630_getActualTorque_raw(motor) * (s32)torqueMeasurementFactor) / 256;
}

s16 tmc6630_getMaxTorque_raw(u8 motor)
{
	return (s16)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_16_TO_31);
}

void tmc6630_setMaxTorque_raw(u8 motor, s16 maxTorque)
{
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_16_TO_31, maxTorque);
}

s32 tmc6630_getMaxTorque_mA(u8 motor, s16 torqueMeasurementFactor)
{
	return (tmc6630_getMaxTorque_raw(motor) * (s32)torqueMeasurementFactor) / 256;
}

void tmc6630_setMaxTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 maxTorque)
{
	tmc6630_setMaxTorque_raw(motor, (maxTorque * 256) / (s32)torqueMeasurementFactor);
}

s16 tmc6630_getMinTorque_raw(u8 motor)
{
	return (s16)tmc6630_spi_readRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_0_TO_15);
}

void tmc6630_setMinTorque_raw(u8 motor, s16 minTorque)
{
	tmc6630_spi_writeRegister16BitValue(motor, TMC6630_TORQUE_MAX_MIN, BIT_0_TO_15, minTorque);
}

s32 tmc6630_getMinTorque_mA(u8 motor, s16 torqueMeasurementFactor)
{
	return (tmc6630_getMinTorque_raw(motor) * (s32)torqueMeasurementFactor) / 256;
}

void tmc6630_setMinTorque_mA(u8 motor, s16 torqueMeasurementFactor, s32 minTorque)
{
	tmc6630_setMinTorque_raw(motor, (minTorque * 256) / (s32)torqueMeasurementFactor);
}

// velocity mode
void tmc6630_setTargetVelocity(u8 motor, s32 targetVelocity)
{
	tmc6630_setMotionMode(motor, TMC6630_MOTION_MODE_VELOCITY);
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_TARGET, targetVelocity);
}

s32 tmc6630_getTargetVelocity(u8 motor)
{
	return (s32)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_TARGET);
}

s32 tmc6630_getActualVelocity(u8 motor)
{
	return (s32)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_ACTUAL);
}

void tmc6630_setMaxVelocity(u8 motor, s32 maxVelocity)
{
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_MAX, maxVelocity);
}

s32 tmc6630_getMaxVelocity(u8 motor)
{
	return (s32)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_MAX);
}

void tmc6630_setMinVelocity(u8 motor, s32 minVelocity)
{
	tmc6630_spi_writeInt(motor, TMC6630_VELOCITY_MIN, minVelocity);
}

s32 tmc6630_getMinVelocity(u8 motor)
{
	return (s32)tmc6630_spi_readInt(motor, TMC6630_VELOCITY_MIN);
}
