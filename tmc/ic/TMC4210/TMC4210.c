/*
  This file provides all functions needed for easy
  access to the TMC429 motion control IC.

  Please note that functions for communication over SPI must be added by the user,
  because this is specific to the MCU that is to be used.

  The ReadWriteSPI function with the following parameters and functionality:
  First parameter: indentifies the SPI device
  Second parameter: byte to be sent to the SPI device
  Third parameter: FALSE means that more bytes will follow, so do not relase the
    chip select line. TRUE means that this was the last byte, so release the chip
    select line after this byte has been sent and the answer has been fully received.

  The function shall return the byte that has been received via SPI.
*/

#include "TMC4210.h"

/***************************************************************//**
   \fn ReadWrite4210(u8 *Read, u8 *Write)
   \brief 32 bit SPI communication with TMC4210
   \param Read   four byte array holding the data read from the TMC428
   \param Write  four byte array holding the data to write to the TMC428

   This is the low-level function that does all SPI communication with
   the TMC4210. It sends a 32 bit SPI telegramme to the TMC4210 and
   receives the 32 bit answer telegramme from the TMC4210.
********************************************************************/
void ReadWrite4210(u8 *Read, u8 *Write)
{
	u8 Motor;

	Read[0] = ReadWriteSPI(SPI_DEV_TMC4210, Write[0], FALSE);
	Read[1] = ReadWriteSPI(SPI_DEV_TMC4210, Write[1], FALSE);
	Read[2] = ReadWriteSPI(SPI_DEV_TMC4210, Write[2], FALSE);
	Read[3] = ReadWriteSPI(SPI_DEV_TMC4210, Write[3], TRUE);
}

/***************************************************************//**
   \fn Write4210Bytes(u8 Address, u8 *Bytes)
   \brief TMC4210 write access
   \param Address  TMC4210 register address (see also TMC4210.h)
   \param Bytes  Array holding three bytes to be written to the
                 TMC4210 register.

   This function writes an array of  three bytes to a TMC4210 register.
********************************************************************/
void Write4210Bytes(u8 Address, u8 *Bytes)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = Bytes[0];
	Write[2] = Bytes[1];
	Write[3] = Bytes[2];
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Write4210Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte)
   \brief TMC4210 write access
   \param Address   TMC4210 register address
   \param HighByte  MSB of the TMC4210 register
   \param MidByte   mid byte of the TMC4210 register
   \param LowByte   LSB of the TMC4210 register

   This function write three bytes to a TMC4210 register.
********************************************************************/
void Write4210Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = HighByte;
	Write[2] = MidByte;
	Write[3] = LowByte;
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Write4210Zero(u8 Address)
   \brief Write zero to a TMC4210 register
   \param Address  TMC4210 register address

   This function sets a TMC4210 register to zero. This can be useful
   e.g. to stop a motor quickly.
********************************************************************/
void Write4210Zero(u8 Address)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = 0;
	Write[2] = 0;
	Write[3] = 0;
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Write4210Short(u8 Address, s32 Value)
   \brief Write 16 bit value to a TMC4210 register
   \param Address  TMC4210 register address
   \param Value    Value to be written

   This function writes a 16 bit value to a TMC4210 register.
********************************************************************/
void Write4210Short(u8 Address, s32 Value)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = 0;
	Write[2] = Value >> 8;
	Write[3] = Value & 0xFF;
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Write4210Int(u8 Address, s32 Value)
   \brief Write 24 bit value to a TMC4210 register
   \param Address  TMC4210 register address
   \param Value    Value to be written

   This function writes a 24 bit value to a TMC4210 register.
********************************************************************/
void Write4210Int(u8 Address, s32 Value)
{
	u8 Write[4], Read[4];

	Write[0] = Address;
	Write[1] = Value >> 16;
	Write[2] = Value >> 8;
	Write[3] = Value & 0xFF;
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Read4210Status
   \brief Read TMC4210 status byte

   \return TMC4210 status byte

   This functions reads just the status byte of the TMC4210 using
   a single byte SPI access which makes this a little bit faster.
********************************************************************/
u8 Read4210Status(void)
{
	return ReadWriteSPI(SPI_DEV_TMC4210, 0x01, TRUE);
}

/***************************************************************//**
   \fn Read4210Bytes(u8 Address, u8 *Bytes)
   \brief Read TMC4210 register
   \param Address  TMC4210 register address (see TMC4210.h)
   \param Bytes  Pointer at array of three bytes

   \return TMC4210 status byte

   This functions reads a TMC4210 register and puts the result into
   an array of bytes. It also returns the TMC4210 status bytes.
********************************************************************/
u8 Read4210Bytes(u8 Address, u8 *Bytes)
{
	u8 Read[4], Write[4];

	Write[0] = Address | TMC4210_READ;
	ReadWrite4210(Read, Write);

	Bytes[0] = Read[1];
	Bytes[1] = Read[2];
	Bytes[2] = Read[3];

	return Read[0];
}

/***************************************************************//**
   \fn Read4210SingleByte(u8 Address, u8 Index)
   \brief Read TMC4210 register
   \param Address  TMC4210 register address (see TMC4210.h)
   \param Index  TMC4210 register byte to be returned (0..3)

   \return TM4210 register byte

   This functions reads a TMC4210 register and returns the desired
   byte of that register.
********************************************************************/
u8 Read4210SingleByte(u8 Address, u8 Index)
{
	u8 Read[4], Write[4];

	Write[0] = Address | TMC4210_READ;
	ReadWrite4210(Read, Write);

	return Read[Index+1];
}

/***************************************************************//**
   \fn Read4210Short(u8 Address)
   \brief Read TMC4210 register (12 bit)
   \param Address  TMC4210 register address (see TMC4210.h)

   \return TMC4210 register value (sign extended)

   This functions reads a TMC4210 12 bit register and sign-extends the
   register value to 32 bit.
********************************************************************/
s32 Read4210Short(u8 Address)
{
	u8 Read[4], Write[4];
	s32 Result;

	Write[0] = Address | TMC4210_READ;
	ReadWrite4210(Read, Write);

	Result = (Read[2]<<8) | Read[3];
	if(Result & 0x00000800) // convert signed 12 bit to signed 32 bit
		Result |= 0xFFFFF000;

	return Result;
}

/***************************************************************//**
   \fn Read4210Int(u8 Address)
   \brief Read TMC4210 register (24 bit)
   \param Address  TMC4210 register address (see TMC4210.h)

   \return TMC4210 register value (sign extended)

   This functions reads a TMC4210 24 bit register and sign-extends the
   register value to 32 bit.
********************************************************************/
s32 Read4210Int(u8 Address)
{
	u8 Read[4], Write[4];
	s32 Result;

	Write[0] = Address | TMC4210_READ;
	ReadWrite4210(Read, Write);

	Result = (Read[1]<<16) | (Read[2]<<8) | Read[3];
	if(Result & 0x00800000) // convert signed 24 bit to signed 32 bit
		Result |= 0xFF000000;

	return Result;
}

/***************************************************************//**
   \fn Set4210RampMode(u8 Axis, u8 RampMode)
   \brief Set the ramping mode
   \param  RampMode  ramping mode (RM_RAMP/RM_SOFT/RM_VELOCITY/RM_HOLD)

   This functions changes the ramping mode of a motor in the TMC4210.
   It is some TMC4210 register bit twiddling.
********************************************************************/
void Set4210RampMode(u8 RampMode)
{
	u8 Write[4], Read[4];

	Write[0] = TMC4210_IDX_REFCONF_RM|TMC4210_READ;
	ReadWrite4210(Read, Write);

	Write[0] = TMC4210_IDX_REFCONF_RM;
	Write[1] = Read[1];
	Write[2] = Read[2];
	Write[3] = RampMode;
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn Set4210SwitchMode(u8 SwitchMode)
   \brief Set the end switch mode
   \param  SwitchMode  end switch mode

   This functions changes the end switch mode of a motor in the TMC4210.
   It is some TMC4210 register bit twiddling.
********************************************************************/
void Set4210SwitchMode(u8 SwitchMode)
{
	u8 Write[4], Read[4];

	Write[0] = TMC4210_IDX_REFCONF_RM|TMC4210_READ;
	ReadWrite4210(Read, Write);

	Write[0] = TMC4210_IDX_REFCONF_RM;
	Write[1] = Read[1];
	Write[2] = SwitchMode;
	Write[3] = Read[3];
	ReadWrite4210(Read, Write);
}

/***************************************************************//**
   \fn SetAMax(u32 AMax)
   \brief Set the maximum acceleration
   \param AMax: maximum acceleration (1..2047)

   This function sets the maximum acceleration and also calculates
   the PMUL and PDIV value according to all other parameters
   (please see the TMC4210 data sheet for more info about PMUL and PDIV
   values).
********************************************************************/
u8 SetAMax(u32 AMax)
{
	s32 pmul, pm, pd;
	float p, p_reduced;
	s32 ramp_div;
	s32 pulse_div;
	u8 PulseRampDiv;
	u8 Data[3];

	AMax &= 0x000007FF;
	Read4210Bytes(TMC4210_IDX_PULSEDIV_RAMPDIV, Data);
	PulseRampDiv = Data[1];
	pulse_div = PulseRampDiv >> 4;
	ramp_div = PulseRampDiv & 0x0F;

	// -1 indicates : no valid pair found
	pm = -1;
	pd = -1;

	if(ramp_div >= pulse_div)
		p = AMax / ( 128.0 * (1 << (ramp_div - pulse_div)));  // Exponent positive or 0
	else
		p = AMax / ( 128.0 / (1 << (pulse_div - ramp_div)));  // Exponent negative

	p_reduced = p*0.988;

	s32 pdiv;
	for(pdiv = 0; pdiv <= 13; pdiv++)
	{
		pmul = (s32) (p_reduced * 8.0 * (1<<pdiv)) - 128;

		if((0 <= pmul) && (pmul <= 127))
		{
			pm = pmul + 128;
			pd = pdiv;
		}
	}

	Data[0] = 0;
	Data[1] = (u8) pm;
	Data[2] = (u8) pd;
	Write4210Bytes(TMC4210_IDX_PMUL_PDIV, Data);
	Write4210Short(TMC4210_IDX_AMAX, AMax);

	return 0;
}

/***************************************************************//**
   \fn HardStop()
   \brief Stop the motor immediately

   This function stops the motor immediately (hard stop) by switching
   to velocity mode and then zeroing the V_TARGT and V_ACTUAL registers.
********************************************************************/
void HardStop(void)
{
	Set4210RampMode(TMC4210_RM_VELOCITY);
	Write4210Zero(TMC4210_IDX_VTARGET);
	Write4210Zero(TMC4210_IDX_VACTUAL);
}

/***************************************************************//**
   \fn Init4210
   \brief TMC4210 initialization

   This function does all necessary initializations of the TMC4210
   to operate in step/direction mode.
********************************************************************/
void Init4210(void)
{
	u32 addr;
	for(addr = 0; addr <= TMC4210_IDX_XLATCHED; addr++)
		Write4210Zero(addr | (Motor<<5));

	Write4210Int(TMC4210_IDX_IF_CONFIG_4210, TMC4210_IFCONF_EN_SD|TMC4210_IFCONF_EN_REFR|TMC4210_IFCONF_SDO_INT);
	Write4210Datagram(TMC4210_IDX_SMGP, 0x00, 0x00, 0x00);

	Write4210Datagram(TMC4210_IDX_PULSEDIV_RAMPDIV, 0x00, 0x37, 0x06);
	Write4210Datagram(TMC4210_IDX_REFCONF_RM, 0x00, TMC4210_NO_REF, 0x00);
	Write4210Short(TMC4210_IDX_VMIN, 1);

	Write4210Int(TMC4210_IDX_VMAX, 1000);
	SetAMax(1000);
}
