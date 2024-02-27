/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

/*
 * TMC424 library definitions
 *
 * This file contains all macro and function definitions of the TMC424 library.
*/

#ifndef TMC_IC_TMC424_H_
#define TMC_IC_TMC424_H_

	#include "tmc/helpers/API_Header.h"
	#include "TMC424_Register.h"

	#ifdef __cplusplus
	extern "C" {
	#endif

	void SetEncoderPrescaler(uint8_t Index, uint32_t Prescaler, uint8_t SpecialFunctionBits);
	int32_t ReadEncoder(uint8_t Which423, uint8_t Index);
	void WriteEncoder(uint8_t Index, int32_t Value);
	uint8_t ReadEncoderNullChannel(uint8_t Which424, uint8_t Index);
	void Init424(void);

	#ifdef __cplusplus
	}
	#endif

#endif /* TMC_IC_TMC424_H_ */
