/*
 * TMC424 library definitions
 *
 * This file contains all macro and function definitions of the TMC424 library.
*/

#ifndef TMC_IC_TMC424_H_
#define TMC_IC_TMC424_H_

	#include "../../helpers/API_Header.h"
	#include "TMC424_Register.h"

	void SetEncoderPrescaler(u8 Index, u32 Prescaler, u8 SpecialFunctionBits);
	s32 ReadEncoder(u8 Which423, u8 Index);
	void WriteEncoder(u8 Index, s32 Value);
	u8 ReadEncoderNullChannel(u8 Which424, u8 Index);
	void Init424(void);

#endif /* TMC_IC_TMC424_H_ */
