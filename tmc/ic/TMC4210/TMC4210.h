/*
 * TMC4210 library definitions
 *
 * This file contains all macro and function definitions of the TMC4210 library.
*/

#ifndef TMC_IC_TMC4210_H_
#define TMC_IC_TMC4210_H_

#include "tmc/helpers/API_Header.h"
#include "TMC4210_Registers.h"

// TMC4210 library functions
void Init4210(void);
void ReadWrite4210(uint8_t *Read, uint8_t *Write);
void Write4210Zero(uint8_t Address);
void Write4210Bytes(uint8_t Address, uint8_t *Bytes);
void Write4210Datagram(uint8_t Address, uint8_t HighByte, uint8_t MidByte, uint8_t LowByte);
void Write4210Short(uint8_t Address, int Value);
void Write4210Int(uint8_t Address, int Value);
uint8_t Read4210Status(void);
uint8_t Read4210Bytes(uint8_t Address, uint8_t *Bytes);
uint8_t Read4210SingleByte(uint8_t Address, uint8_t Index);
int32_t Read4210Short(uint8_t Address);
int32_t Read4210Int(uint8_t Address);
void Set4210RampMode(uint8_t RampMode);
void Set4210SwitchMode(uint8_t SwitchMode);
uint8_t SetAMax(uint32_t AMax);
void HardStop(void);

#endif /* TMC_IC_TMC4210_H_ */
