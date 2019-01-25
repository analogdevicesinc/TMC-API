/*
 * TMC4210 library definitions
 *
 * This file contains all macro and function definitions of the TMC4210 library.
*/

#ifndef TMC_IC_TMC4210_H_
#define TMC_IC_TMC4210_H_

#include "../../helpers/API_Header.h"
#include "TMC4210_Registers.h"

// TMC4210 library functions
void Init4210(void);
void ReadWrite4210(u8 *Read, u8 *Write);
void Write4210Zero(u8 Address);
void Write4210Bytes(u8 Address, u8 *Bytes);
void Write4210Datagram(u8 Address, u8 HighByte, u8 MidByte, u8 LowByte);
void Write4210Short(u8 Address, int Value);
void Write4210Int(u8 Address, int Value);
u8 Read4210Status(void);
u8 Read4210Bytes(u8 Address, u8 *Bytes);
u8 Read4210SingleByte(u8 Address, u8 Index);
s32 Read4210Short(u8 Address);
s32 Read4210Int(u8 Address);
void Set4210RampMode(u8 RampMode);
void Set4210SwitchMode(u8 SwitchMode);
u8 SetAMax(u32 AMax);
void HardStop(void);

#endif /* TMC_IC_TMC4210_H_ */
