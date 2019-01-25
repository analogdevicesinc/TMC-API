/*
 * TMC6200.h
 *
 *  Created on: 14.03.2018
 *      Author: ed
 */

#ifndef TMC_IC_TMC6200_H_
#define TMC_IC_TMC6200_H_

#include "../../helpers/API_Header.h"
#include "TMC6200_Register.h"
#include "TMC6200_Constants.h"

int tmc6200_readInt(u8 motor, uint8 address);
void tmc6200_writeInt(u8 motor, uint8 address, int value);

#endif /* TMC_IC_TMC6630_H_ */
