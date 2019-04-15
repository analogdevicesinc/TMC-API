/*
 * TMC457 library definitions
 *
 * This file contains all macro and function definitions of the TMC457 library.
*/

#ifndef TMC_IC_TMC457_H_
#define TMC_IC_TMC457_H_

	#include "tmc/helpers/API_Header.h"
	#include "TMC457_Register.h"

	void Write457Zero(uint8_t Address);
	void Write457Int(uint8_t Address, int32_t Value);
	void Write457Wavetable(uint16_t RAMAddress, uint16_t Value);
	int32_t Read457Int(uint8_t Address);
	uint16_t Read457Wavetable(uint16_t RAMAddress);
	void Set457RampMode(uint32_t RampMode);
	void Init457Wavetable(uint32_t Resolution, int32_t Offset);
	void Init457(void);
	void HardStop();

#endif /* TMC_IC_TMC457_H_ */

