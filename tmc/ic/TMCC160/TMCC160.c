/*
 * TMCC160.c
 *
 *  Created on: 06.10.2016
 *      Author: ed
 */
#include "TMCC160.h"

#define __NOP asm volatile ("nop")

// => SPI wrapper
extern u8 tmcc160_spi_readwriteByte(u8 data, u8 lastTransfer);
// <= SPI wrapper

void tmcc160_init()
{
	// nothing to do here
}

void tmcc160_periodicJob(u32 actualSystick)
{
	// nothing to do here
	UNUSED(actualSystick);
}

void tmcc160_delay(uint32 nCount)
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

void tmcc160_writeInt(uint8 address, int value)
{
	tmcc160_spi_readwriteByte(address | 0x80, FALSE);
	tmcc160_spi_readwriteByte(0xFF & (value>>24), FALSE);
	tmcc160_spi_readwriteByte(0xFF & (value>>16), FALSE);
	tmcc160_spi_readwriteByte(0xFF & (value>>8), FALSE);
	tmcc160_spi_readwriteByte(0xFF & (value>>0), TRUE);
}

int tmcc160_readInt(uint8 address)
{
	// clear write bit
	address &= 0x7F;

	tmcc160_spi_readwriteByte(address, FALSE);
	tmcc160_spi_readwriteByte(0, FALSE);
	tmcc160_spi_readwriteByte(0, FALSE);
	tmcc160_spi_readwriteByte(0, FALSE);
	tmcc160_spi_readwriteByte(0, TRUE);

	// delay needed!
	tmcc160_default_spi_delay();

	tmcc160_spi_readwriteByte(address, FALSE);

	int value = tmcc160_spi_readwriteByte(0, FALSE);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, FALSE);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, FALSE);
	value <<= 8;
	value |= tmcc160_spi_readwriteByte(0, TRUE);

	return value;
}

void tmcc160_setTargetTorque_raw(s32 targetTorque)
{
	tmcc160_writeInt(CURRENT_TARGET_REG_ADDR | 0x80, targetTorque);
}

s32 tmcc160_getTargetTorque_raw()
{
	return (s32) tmcc160_readInt(CURRENT_TARGET_REG_ADDR);
}

s32 tmcc160_getActualTorque_raw()
{
	return (s32) tmcc160_readInt(CURRENT_ACTUAL_REG_ADDR);
}

s32 tmcc160_getActualRampTorque_raw()
{
	// because this IC does not support a torque ramp!
	return tmcc160_getTargetTorque_raw();
}

// actual==raw motor current for this IC!
void tmcc160_setTargetTorque_mA(s32 targetTorque)
{
	tmcc160_setTargetTorque_raw(targetTorque);
}

s32 tmcc160_getTargetTorque_mA()
{
	return tmcc160_getTargetTorque_raw();
}

s32 tmcc160_getActualTorque_mA()
{
	return tmcc160_getActualTorque_raw();
}

s32 tmcc160_getActualRampTorque_mA()
{
	// because this IC does not support a torque ramp!
	return tmcc160_getTargetTorque_mA();
}

void tmcc160_setTargetVelocity(s32 targetVelocity)
{
	tmcc160_writeInt(VELOCITY_TARGET_REG_ADDR | 0x80, targetVelocity);
}

s32 tmcc160_getTargetVelocity()
{
	return (s32) tmcc160_readInt(VELOCITY_TARGET_REG_ADDR);
}

s32 tmcc160_getActualVelocity()
{
	return (s32) tmcc160_readInt(VELOCITY_ACTUAL_REG_ADDR);
}

s32 tmcc160_getActualRampVelocity()
{
	return (s32) tmcc160_readInt(RAMP_ACTUAL_VELOCITY_REG_ADDR);
}

void tmcc160_setAbsolutTargetPosition(s32 targetPosition)
{
	tmcc160_writeInt(POSITION_TARGET_ABS_REG_ADDR | 0x80, targetPosition);
}

void tmcc160_setRelativeTargetPosition(s32 relativePosition)
{
	tmcc160_writeInt(POSITION_TARGET_REL_REG_ADDR | 0x80,  relativePosition);
}

s32 tmcc160_getTargetPosition()
{
	return (s32) tmcc160_readInt(POSITION_TARGET_ABS_REG_ADDR);
}

void tmcc160_setActualPosition(s32 actualPosition)
{
	tmcc160_writeInt(POSITION_ACTUAL_REG_ADDR | 0x80, actualPosition);
}

s32 tmcc160_getActualPosition()
{
	return (s32) tmcc160_readInt(POSITION_ACTUAL_REG_ADDR);
}

s32 tmcc160_getActualRampPosition()
{
	// module does not support position ramp
	return tmcc160_getTargetPosition();
}
