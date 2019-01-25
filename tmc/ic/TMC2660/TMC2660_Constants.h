/*
 * TMC2660_Constants.h
 *
 *  Created on: 20.08.2018
 *      Author: tmctest
 */

#ifndef TMC_IC_TMC2660_TMC2660_CONSTANTS_H_
#define TMC_IC_TMC2660_TMC2660_CONSTANTS_H_

#include "../../helpers/Constants.h"

#define TMC2660_REGISTER_COUNT   8
#define TMC2660_MOTORS           1
#define TMC2660_WRITE_BIT        0x08
#define TMC2660_ADDRESS_MASK     0x07
#define TMC2660_MAX_VELOCITY     s32_MAX
#define TMC2660_MAX_ACCELERATION u24_MAX

// read addressescorrespondes with RDSEL, added latest to access latest data of common lower 7 bits
#define TMC2660_RESPONSE0        0
#define TMC2660_RESPONSE1        1
#define TMC2660_RESPONSE2        2
#define TMC2660_RESPONSE_LATEST  3

#endif /* TMC_IC_TMC2660_TMC2660_CONSTANTS_H_ */
