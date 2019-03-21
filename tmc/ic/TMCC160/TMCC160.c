/*
 * TMCC160.c
 *
 *  Created on: 06.10.2016
 *      Author: ed
 */
#include "TMCC160.h"

#define __NOP asm volatile ("nop")

// => SPI wrapper
extern uint8_t tmcc160_spi_readwriteByte(uint8_t data, uint8_t lastTransfer);
// <= SPI wrapper

void tmcc160_init()
{
	// nothing to do here
}

void tmcc160_periodicJob(uint32_t actualSystick)
{
	// nothing to do here
	UNUSED(actualSystick);
}

void tmcc160_delay(uint32_t nCount)
{
	while(nCount--)
	{
		__NOP;
	}
}

void tmcc160_default_spi_delay()
{
	tmcc160_delay(1550);
}

void tmcc160_writeInt(uint8_t address, int value)
{
	tmcc160_spi_readwriteByte(address | 0x80, false);
	tmcc160_spi_readwriteByte(0xFF & (value>>24), false);
	tmcc160_spi_readwriteByte(0xFF & (value>>16), false);
	tmcc160_spi_readwriteByte(0xFF & (value>>8), false);
	tmcc160_spi_readwriteByte(0xFF & (value>>0), true);
}

int tmcc160_readInt(uint8_t address)
{
	// clear write bit
	address &= 0x7F;

	tmcc160_spi_readwriteByte(address, false);
	tmcc160_spi_readwriteByte(0, false);
	tmcc160_spi_readwriteByte(0, false);
	tmcc160_spi_readwriteByte(0, false);
	tmcc160_spi_readwriteByte(0, true);

	// delay needed!
	tmcc160_default_spi_delay();

	tmcc160_spi_readwriteByte(address, false);

	int value = tmcc160_spi_readwriteByte(0, false);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, false);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, false);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, true);

	return value;
}

void tmcc160_setTargetTorque_raw(int32_t targetTorque)
{
	tmcc160_writeInt(CURRENT_TARGET_REG_ADDR | 0x80, targetTorque);
}

int32_t tmcc160_getTargetTorque_raw()
{
	return (int32_t) tmcc160_readInt(CURRENT_TARGET_REG_ADDR);
}

int32_t tmcc160_getActualTorque_raw()
{
	return (int32_t) tmcc160_readInt(CURRENT_ACTUAL_REG_ADDR);
}

int32_t tmcc160_getActualRampTorque_raw()
{
	// because this IC does not support a torque ramp!
	return tmcc160_getTargetTorque_raw();
}

// actual==raw motor current for this IC!
void tmcc160_setTargetTorque_mA(int32_t targetTorque)
{
	tmcc160_setTargetTorque_raw(targetTorque);
}

int32_t tmcc160_getTargetTorque_mA()
{
	return tmcc160_getTargetTorque_raw();
}

int32_t tmcc160_getActualTorque_mA()
{
	return tmcc160_getActualTorque_raw();
}

int32_t tmcc160_getActualRampTorque_mA()
{
	// because this IC does not support a torque ramp!
	return tmcc160_getTargetTorque_mA();
}

void tmcc160_setTargetVelocity(int32_t targetVelocity)
{
	tmcc160_writeInt(VELOCITY_TARGET_REG_ADDR | 0x80, targetVelocity);
}

int32_t tmcc160_getTargetVelocity()
{
	return (int32_t) tmcc160_readInt(VELOCITY_TARGET_REG_ADDR);
}

int32_t tmcc160_getActualVelocity()
{
	return (int32_t) tmcc160_readInt(VELOCITY_ACTUAL_REG_ADDR);
}

int32_t tmcc160_getActualRampVelocity()
{
	return (int32_t) tmcc160_readInt(RAMP_ACTUAL_VELOCITY_REG_ADDR);
}

void tmcc160_setAbsolutTargetPosition(int32_t targetPosition)
{
	tmcc160_writeInt(POSITION_TARGET_ABS_REG_ADDR | 0x80, targetPosition);
}

void tmcc160_setRelativeTargetPosition(int32_t relativePosition)
{
	tmcc160_writeInt(POSITION_TARGET_REL_REG_ADDR | 0x80,  relativePosition);
}

int32_t tmcc160_getTargetPosition()
{
	return (int32_t) tmcc160_readInt(POSITION_TARGET_ABS_REG_ADDR);
}

void tmcc160_setActualPosition(int32_t actualPosition)
{
	tmcc160_writeInt(POSITION_ACTUAL_REG_ADDR | 0x80, actualPosition);
}

int32_t tmcc160_getActualPosition()
{
	return (int32_t) tmcc160_readInt(POSITION_ACTUAL_REG_ADDR);
}

int32_t tmcc160_getActualRampPosition()
{
	// module does not support position ramp
	return tmcc160_getTargetPosition();
}
