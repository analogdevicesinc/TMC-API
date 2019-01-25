/*
	This file provides all functions needed for easy
	access to the TMC429 motion control IC.

	Please not that functions for communication over SPI must be added by the user,
	because this is specific to the MCU that is to be used.

	The ReadWriteSPI function with the following parameters and functionality:
	First parameter: indentifies the SPI device
	Second parameter: byte to be sent to the SPI device
	Third parameter: FALSE means that more bytes will follow, so do not relase the
	  chip select line. TRUE means that this was the last byte, so release the chip
	  select line after this byte has been sent and the answer has been fully received.

	The function shall return the byte that has been received via SPI.
*/

#include "TMC429.h"

/***************************************************************//**
	 \fn ReadWrite429(u8 *Read, u8 *Write)
	 \brief 32 bit SPI communication with TMC429
	 \param Read   four byte array holding the data read from the TMC428
	 \param Write  four byte array holding the data to write to the TMC428

	 This is the low-level function that does all SPI communication with
	 the TMC429. It sends a 32 bit SPI telegramme to the TMC429 and
	 receives the 32 bit answer telegramme from the TMC429.
********************************************************************/
void ReadWrite429(u8 *Read, u8 *Write)
{
	Read[0] = ReadWriteSPI(SPI_DEV_TMC429, Write[0], FALSE);
	Read[1] = ReadWriteSPI(SPI_DEV_TMC429, Write[1], FALSE);
	Read[2] = ReadWriteSPI(SPI_DEV_TMC429, Write[2], FALSE);
	Read[3] = ReadWriteSPI(SPI_DEV_TMC429, Write[3], TRUE);
}

/***************************************************************//**
	 \fn Write429Bytes(u8 Address, u8 *Bytes)
	 \brief TMC429 write access
	 \param Address  TMC429 register address (see also TMC429.h)
	 \param Bytes  Array holding three bytes to be written to the
	               TMC429 register.

	 This function writes an array of  three bytes to a TMC429 register.
********************************************************************/
void Write429Bytes(u8 Address, u8 *Bytes)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = Bytes[0];
	Write[2] = Bytes[1];
	Write[3] = Bytes[2];
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Write429Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte)
	 \brief TMC429 write access
	 \param Address   TMC429 register address
	 \param HighByte  MSB of the TMC429 register
	 \param MidByte   mid byte of the TMC429 register
	 \param LowByte   LSB of the TMC429 register

	 This function write three bytes to a TMC429 register.
********************************************************************/
void Write429Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = HighByte;
	Write[2] = MidByte;
	Write[3] = LowByte;
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Write429Zero(u8 Address)
	 \brief Write zero to a TMC429 register
	 \param Address  TMC429 register address

	 This function sets a TMC429 register to zero. This can be useful
	 e.g. to stop a motor quickly.
********************************************************************/
void Write429Zero(u8 Address)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = 0;
	Write[2] = 0;
	Write[3] = 0;
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Write429Short(u8 Address, s32 Value)
	 \brief Write 16 bit value to a TMC429 register
	 \param Address  TMC429 register address
	 \param Value    Value to be written

	 This function writes a 16 bit value to a TMC429 register.
********************************************************************/
void Write429Short(u8 Address, s32 Value)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = 0;
	Write[2] = Value >> 8;
	Write[3] = Value & 0xFF;
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Write429Int(u8 Address, s32 Value)
	 \brief Write 24 bit value to a TMC429 register
	 \param Address  TMC429 register address
	 \param Value    Value to be written

	 This function writes a 24 bit value to a TMC429 register.
********************************************************************/
void Write429Int(u8 Address, s32 Value)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = Value >> 16;
	Write[2] = Value >> 8;
	Write[3] = Value & 0xFF;
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Read429Status
	 \brief Read TMC429 status byte

	 \return TMC429 status byte

	 This functions reads just the status byte of the TMC429 using
	 a single byte SPI access which makes this a little bit faster.
********************************************************************/
u8 Read429Status(void)
{
	return ReadWriteSPI(SPI_DEV_TMC429, 0x01, TRUE);
}

/***************************************************************//**
	 \fn Read429Bytes(u8 Address, u8 *Bytes)
	 \brief Read TMC429 register
	 \param Address  TMC429 register address (see TMC429.h)
	 \param Bytes  Pointer at array of three bytes

	 \return TMC429 status byte

	 This functions reads a TMC429 register and puts the result into
	 an array of bytes. It also returns the TMC429 status bytes.
********************************************************************/
u8 Read429Bytes(u8 Address, u8 *Bytes)
{
	u8 Read[4], Write[4];

	Write[0] = Address | TMC429_READ;
	ReadWrite429(Read, Write);

	Bytes[0] = Read[1];
	Bytes[1] = Read[2];
	Bytes[2] = Read[3];

	return Read[0];
}

/***************************************************************//**
	 \fn Read429SingleByte(u8 Address, u8 Index)
	 \brief Read TMC429 register
	 \param Address  TMC429 register address (see TMC429.h)
	 \param Index  TMC429 register byte to be returned (0..3)

	 \return TM429 register byte

	 This functions reads a TMC429 register and returns the desired
	 byte of that register.
********************************************************************/
u8 Read429SingleByte(u8 Address, u8 Index)
{
	u8 Read[4], Write[4];

	Write[0] = Address | TMC429_READ;
	ReadWrite429(Read, Write);

	return Read[Index+1];
}

/***************************************************************//**
	 \fn Read429Short(u8 Address)
	 \brief Read TMC429 register (12 bit)
	 \param Address  TMC429 register address (see TMC429.h)

	 \return TMC429 register value (sign extended)

	 This functions reads a TMC429 12 bit register and sign-extends the
	 register value to 32 bit.
********************************************************************/
s32 Read429Short(u8 Address)
{
	u8 Read[4], Write[4];
	s32 Result;

	Write[0] = Address | TMC429_READ;
	ReadWrite429(Read, Write);

	Result = (Read[2]<<8) | Read[3];
	if(Result & 0x00000800)
		Result |= 0xFFFFF000;

	return Result;
}

/***************************************************************//**
	 \fn Read429Int(u8 Address)
	 \brief Read TMC429 register (24 bit)
	 \param Address  TMC429 register address (see TMC429.h)

	 \return TMC429 register value (sign extended)

	 This functions reads a TMC429 24 bit register and sign-extends the
	 register value to 32 bit.
********************************************************************/
s32 Read429Int(u8 Address)
{
	u8 Read[4], Write[4];
	s32 Result;

	Write[0] = Address | TMC429_READ;
	ReadWrite429(Read, Write);

	Result = (Read[1]<<16) | (Read[2]<<8) | (Read[3]);
	if(Result & 0x00800000)
		Result |= 0xFF000000;

	return Result;
}

/***************************************************************//**
	 \fn Set429RampMode(u8 Axis, u8 RampMode)
	 \brief Set the ramping mode of an axis
	 \param  Axis  Motor number (0, 1 or 2)
	 \param  RampMode  ramping mode (RM_RAMP/RM_SOFT/RM_VELOCITY/RM_HOLD)

	 This functions changes the ramping mode of a motor in the TMC429.
	 It is some TMC429 register bit twiddling.
********************************************************************/
void Set429RampMode(u8 Axis, u8 RampMode)
{
	u8 Write[4], Read[4];

	Write[0] = TMC429_IDX_REFCONF_RM(Axis)|TMC429_READ;
	ReadWrite429(Read, Write);

	Write[0] = TMC429_IDX_REFCONF_RM(Axis);
	Write[1] = Read[1];
	Write[2] = Read[2];
	Write[3] = RampMode;
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn Set429SwitchMode(u8 Axis, u8 SwitchMode)
	 \brief Set the end switch mode
	 \param  Axis  Motor number (0, 1 or 2)
	 \param  SwitchMode  end switch mode

	 This functions changes the end switch mode of a motor in the TMC429.
	 It is some TMC429 register bit twiddling.
********************************************************************/
void Set429SwitchMode(u8 Axis, u8 SwitchMode)
{
	u8 Write[4], Read[4];

	Write[0] = TMC429_IDX_REFCONF_RM(Axis) | TMC429_READ;
	ReadWrite429(Read, Write);

	Write[0] = TMC429_IDX_REFCONF_RM(Axis);
	Write[1] = Read[1];
	Write[2] = SwitchMode;
	Write[3] = Read[3];
	ReadWrite429(Read, Write);
}

/***************************************************************//**
	 \fn SetAMax(u8 Motor, u32 AMax)
	 \brief Set the maximum acceleration
	 \param Motor  motor number (0, 1, 2)
	 \param AMax: maximum acceleration (1..2047)

	 This function sets the maximum acceleration and also calculates
	 the PMUL and PDIV value according to all other parameters
	 (please see the TMC429 data sheet for more info about PMUL and PDIV
	 values).
********************************************************************/
u8 SetAMax(u8 Motor, u32 AMax)
{
	s32 pm, pd;
	float p, p_reduced;
	s32 ramp_div;
	s32 pulse_div;
	u8 PulseRampDiv;
	u8 Data[3];

	AMax &= 0x000007FF;
	Read429Bytes(TMC429_IDX_PULSEDIV_RAMPDIV(Motor), Data);
	PulseRampDiv = Data[1];
	pulse_div = PulseRampDiv >> 4;
	ramp_div = PulseRampDiv & 0x0F;

	// -1 indicates : no valid pair found
	pm = -1;
	pd = -1;

	if(ramp_div >= pulse_div)
		p = AMax / ( 128.0 * (1<<ramp_div-pulse_div));  // Exponent positive or 0
	else
		p = AMax / ( 128.0 / (1<<pulse_div-ramp_div));  // Exponent negative

	p_reduced = p*0.988;

	s32 pdiv;
	for(pdiv = 0; pdiv <= 13; pdiv++)
	{
		s32 pmul = (s32) (p_reduced * 8.0 * (1<<pdiv)) - 128;

		if((0 <= pmul) && (pmul <= 127))
		{
			pm = pmul + 128;
			pd = pdiv;
		}
	}

	Data[0] = 0;
	Data[1] = (u8) pm;
	Data[2] = (u8) pd;
	Write429Bytes(TMC429_IDX_PMUL_PDIV(Motor), Data);
	Write429Short(TMC429_IDX_AMAX(Motor), AMax);

	return 0;
}

/***************************************************************//**
	 \fn HardStop(u32 Motor)
	 \brief Stop a motor immediately
	 \param Motor: motor number (0, 1, 2)

	 This function stops a motor immediately (hard stop) by switching
	 to velocity mode and then zeroing the V_TARGT and V_ACTUAL registers
	 of that axis.
********************************************************************/
void HardStop(u32 Motor)
{
	Set429RampMode(Motor, TMC429_RM_VELOCITY);
	Write429Zero(TMC429_IDX_VTARGET(Motor));
	Write429Zero(TMC429_IDX_VACTUAL(Motor));
}

/***************************************************************//**
	 \fn Init429
	 \brief TMC429 initialization

	 This function does all necessary initializations of the TMC429
	 to operate in step/direction mode.
********************************************************************/
void Init429(void)
{
	u8 motor;
	for(motor = 0; motor < 3; motor++)
	{
		u32 addr;
		for(addr = 0; addr <= TMC429_IDX_XLATCHED; addr++)
			Write429Zero(addr | TMC429_MOTOR(motor));
	}

	Write429Int(TMC429_IDX_IF_CONFIG_429, TMC429_IFCONF_EN_SD | TMC429_IFCONF_EN_REFR | TMC429_IFCONF_SDO_INT);
	Write429Datagram(TMC429_IDX_SMGP, 0x00, 0x00, 0x02);

	for(motor = 0; motor < 3; motor++)
	{
		Write429Datagram(TMC429_IDX_PULSEDIV_RAMPDIV(motor), 0x00, 0x37, 0x06);
		Write429Datagram(TMC429_IDX_REFCONF_RM(motor), 0x00, TMC429_NO_REF, 0x00);
		Write429Short(TMC429_IDX_VMIN(motor), 1);

		Write429Int(TMC429_IDX_VMAX(motor), 1000);
		SetAMax(motor, 1000);
	}
}
