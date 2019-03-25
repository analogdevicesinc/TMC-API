/*
 * TMC2590_Constants.h
 *
 *  Created on: 09.01.2019
 *      Author: LK
 */

#ifndef TMC_IC_TMC2590_TMC2590_CONSTANTS_H_
#define TMC_IC_TMC2590_TMC2590_CONSTANTS_H_

#include "../../../TMC-API/tmc/helpers/Constants.h"

#define TMC2590_REGISTER_COUNT   8
#define TMC2590_MOTORS           1
#define TMC2590_WRITE_BIT        0x08
#define TMC2590_ADDRESS_MASK     0x07
#define TMC2590_ADDRESS_SHIFT    17
#define TMC2590_MAX_VELOCITY     s32_MAX
#define TMC2590_MAX_ACCELERATION u24_MAX

// read addresses correspond with RDSEL, added latest to access latest data of common lower 7 bits
#define TMC2590_RESPONSE0        0
#define TMC2590_RESPONSE1        1
#define TMC2590_RESPONSE2        2
#define TMC2590_RESPONSE_LATEST  3

#endif /* TMC_IC_TMC2590_TMC2590_CONSTANTS_H_ */
