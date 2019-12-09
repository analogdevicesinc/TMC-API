/*
 * TMC6100.h
 *
 *  Created on: 13.11.2019
 *      Author: ED
 */

#ifndef TMC_IC_TMC6100_H_
#define TMC_IC_TMC6100_H_

#include "tmc/helpers/API_Header.h"
#include "TMC6100_Constants.h"
#include "TMC6100_Register.h"

int tmc6100_readInt(uint8_t motor, uint8_t address);
void tmc6100_writeInt(uint8_t motor, uint8_t address, int value);

#endif /* TMC_IC_TMC6630_H_ */
