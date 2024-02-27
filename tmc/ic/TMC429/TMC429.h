/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

/*
 * TMC429 library definitions
 *
 * This file contains all macro and function definitions of the TMC429 library.
*/

#ifndef TMC_IC_TMC429_H_
#define TMC_IC_TMC429_H_

	#include "tmc/helpers/API_Header.h"
	#include "TMC429_Register.h"

	#ifdef __cplusplus
	extern "C" {
	#endif

	// user must provide this function
	uint8_t ReadWriteSPI(void* p_SPI_DeviceHandle, uint8_t data,bool endTransaction);

	// TMC429 library functions
	void Init429(void);
	void ReadWrite429(uint8_t *Read, uint8_t *Write);
	void Write429Zero(uint8_t Address);
	void Write429Bytes(uint8_t Address, uint8_t *Bytes);
	void Write429Datagram(uint8_t Address, uint8_t HighByte, uint8_t MidByte, uint8_t LowByte);
	void Write429U16(uint8_t Address, uint16_t Value);
	void Write429U24(uint8_t Address, uint32_t Value);
	uint8_t Read429Status(void);
	uint8_t Read429Bytes(uint8_t Address, uint8_t *Bytes);
	uint8_t Read429SingleByte(uint8_t Address, uint8_t Index);
	int32_t Read429Int12(uint8_t Address);
	int32_t Read429Int24(uint8_t Address);
	void Set429RampMode(uint8_t Axis, uint8_t RampMode);
	void Set429SwitchMode(uint8_t Axis, uint8_t SwitchMode);
	uint8_t SetAMax(uint8_t Motor, uint32_t AMax);
	void HardStop(uint32_t Motor);

	#ifdef __cplusplus
	}
	#endif

#endif /* TMC_IC_TMC429_H_ */
