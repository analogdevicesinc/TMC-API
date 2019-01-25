/*
 * TMC457 library definitions
 *
 * This file contains all macro and function definitions of the TMC457 library.
*/

#ifndef TMC_IC_TMC457_H_
#define TMC_IC_TMC457_H_

	#include "../../helpers/API_Header.h"
	#include "TMC457_Register.h"

	void Write457Zero(u8 Address);
	void Write457Int(u8 Address, s32 Value);
	void Write457Wavetable(u16 RAMAddress, u16 Value);
	s32 Read457Int(u8 Address);
	u16 Read457Wavetable(u16 RAMAddress);
	void Set457RampMode(u32 RampMode);
	void Init457Wavetable(u32 Resolution, s32 Offset);
	void Init457(void);
	void HardStop();

#endif /* TMC_IC_TMC457_H_ */

