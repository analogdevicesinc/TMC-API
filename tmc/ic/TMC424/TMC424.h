/*
 * TMC424 library definitions
 *
 * This file contains all macro and function definitions of the TMC424 library.
*/

#ifndef TMC_IC_TMC424_H_
#define TMC_IC_TMC424_H_

	#include "tmc/helpers/API_Header.h"
	#include "TMC424_Register.h"

	void SetEncoderPrescaler(uint8_t Index, uint32_t Prescaler, uint8_t SpecialFunctionBits);
	int32_t ReadEncoder(uint8_t Which423, uint8_t Index);
	void WriteEncoder(uint8_t Index, int32_t Value);
	uint8_t ReadEncoderNullChannel(uint8_t Which424, uint8_t Index);
	void Init424(void);

#endif /* TMC_IC_TMC424_H_ */
