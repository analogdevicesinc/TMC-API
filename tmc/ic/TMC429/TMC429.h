/*
 * TMC429 library definitions
 *
 * This file contains all macro and function definitions of the TMC429 library.
*/

#ifndef TMC_IC_TMC429_H_
#define TMC_IC_TMC429_H_

	#include "../../helpers/API_Header.h"
	#include "TMC429_Register.h"

	// TMC429 library functions
	void Init429(void);
	void ReadWrite429(u8 *Read, u8 *Write);
	void Write429Zero(u8 Address);
	void Write429Bytes(u8 Address, u8 *Bytes);
	void Write429Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte);
	void Write429Short(u8 Address, int Value);
	void Write429Int(u8 Address, int Value);
	u8 Read429Status(void);
	u8 Read429Bytes(u8 Address, u8 *Bytes);
	u8 Read429SingleByte(u8 Address, u8 Index);
	s32 Read429Short(u8 Address);
	s32 Read429Int(u8 Address);
	void Set429RampMode(u8 Axis, u8 RampMode);
	void Set429SwitchMode(u8 Axis, u8 SwitchMode);
	u8 SetAMax(u8 Motor, u32 AMax);
	void HardStop(u32 Motor);

#endif /* TMC_IC_TMC429_H_ */
