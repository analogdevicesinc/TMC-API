/*
	This file provides all functions needed for easy
	access to the TMC424 encoder interface IC.

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

#include "TMC424.h"


/***************************************************************//**
	 \fn ReadWrite424(u8 *Read, u8 *Write)
	 \brief 32 bit SPI communication with TMC424
	 \param Read   four byte array holding the data read from the TMC424
	 \param Write  four byte array holding the data to write to the TMC424

	 This is the low-level function that does all SPI communication with
	 the TMC424. It sends a 32 bit SPI telegramme to the TMC424 and
	 receives the 32 bit answer telegramme from the TMC424.
********************************************************************/
static void ReadWrite424(u8 *Read, u8 *Write)
{
	Read[0] = ReadWriteSPI(SPI_DEV_ENCODER, Write[0], FALSE);
	Read[1] = ReadWriteSPI(SPI_DEV_ENCODER, Write[1], FALSE);
	Read[2] = ReadWriteSPI(SPI_DEV_ENCODER, Write[2], FALSE);
	Read[3] = ReadWriteSPI(SPI_DEV_ENCODER, Write[3], TRUE);
}


/***************************************************************//**
	 \fn Write424Bytes(u8 Address, u8 HiByte, u8 MidByte, u8 LoByte)
	 \brief Write to TMC424 register
	 \param Address   TMC424 register address
	 \param HiByte    MSB to be written
	 \param MidByte   Middle byte to be written
	 \param LoByte    LSB to be writteb

	 Write to the three single bytes of a TMC424 register.
********************************************************************/
static void Write424Bytes(u8 Address, u8 HiByte, u8 MidByte, u8 LoByte)
{
	ReadWriteSPI(SPI_DEV_ENCODER, Address|TMC424_WRITE, FALSE);
	ReadWriteSPI(SPI_DEV_ENCODER, HiByte, FALSE);
	ReadWriteSPI(SPI_DEV_ENCODER, MidByte, FALSE);
	ReadWriteSPI(SPI_DEV_ENCODER, LoByte, TRUE);
}


/***************************************************************//**
	 \fn SetEncoderPrescaler(u8 Index, u32 Prescaler, u8 SpecialFunctionBits)
	 \brief Index  TMC424 encoder channel (0, 1 or 2)
	 \param Prescaler   Encooder pre-scaler (see TMC424 data sheet)
	 \param SpecialFunctionBits  special encoder functions (see TMC424 data sheet)

	 This function sets the pre-scaler and the special functions of an encoder
	 channel.
********************************************************************/
void SetEncoderPrescaler(u8 Index, u32 Prescaler, u8 SpecialFunctionBits)
{
	u8 RegAddr;
	u32 ps;
	u32 sf;

	switch(Index)
	{
	case 0:
		RegAddr = TMC423_ENC_CONF_1;
		break;
	case 1:
		RegAddr = TMC423_ENC_CONF_2;
		break;
	case 2:
		RegAddr = TMC423_ENC_CONF_3;
		break;
	default:
		return;
	}

	ps = ((Prescaler & 0xFFFFFFF0) << 8) | (Prescaler & 0x0000000F);
	sf = SpecialFunctionBits;
	sf <<= 7;
	ps |= sf;
	Write423Bytes(RegAddr, 0, ps >> 16, ps >> 8, (u8) ps);
}


/***************************************************************//**
	 \fn ReadEncoder(u8 Index)
	 \brief  Read encoder counter
	 \param Index  Specifies the encoder (0, 1 or 2)
	 \return Encoder positon counter value

	 This function reads an encoder counter and returns its value
	 as a 32 bit signed value.
********************************************************************/
s32 ReadEncoder(u8 Index)
{
	u8 Read424[5], Write424[5];
	u32 Position;

	switch(Index)
	{
	case 0:
		Write424[0] = TMC423_ENC_DATA_1;
		break;
	case 1:
		Write424[0] = TMC423_ENC_DATA_2;
		break;
	case 2:
		Write424[0] = TMC423_ENC_DATA_3;
		break;
	default:
		return 0;
	}

	Write424[1] = 0;
	Write424[2] = 0;
	Write424[3] = 0;
	Write424[4] = 0;
	ReadWrite424(Read424, Write424);
	Position = (Read424[1]<<16) | (Read424[2]<<8) | Read424[3];
	if(Read424[1] & 0x80) // Sign extend the value
		Position |= 0xFF000000;

	return Position;
}


/***************************************************************//**
	 \fn WriteEncoder(u8 Index, s32 Value)
	 \brief Change encoder counter
	 \param Index  specifies the encoder (0, 1 or 2)
	 \param Value  value to be written

	 Change an encoder counter register to the given value.
********************************************************************/
void WriteEncoder(u8 Index, s32 Value)
{
	u8 RegAddr;

	switch(Index)
	{
	case 0:
		RegAddr = TMC423_ENC_DATA_1;
		break;
	case 1:
		RegAddr = TMC423_ENC_DATA_2;
		break;
	case 2:
		RegAddr = TMC423_ENC_DATA_3;
		break;
	default:
		return;
	}

	Write424Bytes(RegAddr, Value >> 16, Value >> 8, (u8) Value);
}


/***************************************************************//**
	 \fn ReadEncoderNullChannel(u8 Index)
	 \brief Check null channel of an encoder
	 \param Index  specifies the encoer (0, 1 or 2)
	 \return State of the N input for the given encoder

	 This function reads the state of the null channel input for an
	 encoder.
********************************************************************/
u8 ReadEncoderNullChannel(u8 Index)
{
	u8 Read424[4], Write424[4];

	Write424[0] = 0x12;
	Write424[1] = 0;
	Write424[2] = 0;
	Write424[3] = 0;
	ReadWrite424(Write424, Read424);

	switch(Index)
	{
	case 0:
		if((Read424[1] & 0x04))
			return 1;
		else
			return 0;
		break;
	case 1:
		if((Read424[1] & 0x08))
			return 1;
		else
			return 0;
		break;
	case 2:
		if((Read424[1] & 0x10))
			return 1;
		else
			return 0;
		break;
	default:
		return 0;
		break;
	}
}


/***************************************************************//**
	 \fn Init424()
	 \brief Initialize the TMC424

	 This function does the basic initialization of the TMC424.
	 The encoder prescalers are set to some example values, and the
	 encoder counters are cleared.
********************************************************************/
void Init424(void)
{
	// Set encoder prescalers to 12.5
	SetEncoderPrescaler(0, 0xC8, 0);
	SetEncoderPrescaler(1, 0xC8, 0);
	SetEncoderPrescaler(2, 0xC8, 0);

	// Switch off interrupts
	Write423Bytes(TMC424_INT_CTRL, 0, TMC424_CLR_FLAGS, 0, 0);

	// Clear encoder counters
	Write423Bytes(TMC424_ENC_DATA_1, 0, 0, 0, 0);
	Write423Bytes(TMC424_ENC_DATA_2, 0, 0, 0, 0);
	Write423Bytes(TMC424_ENC_DATA_3, 0, 0, 0, 0);
}
