/*
 * TMC262_1420_Constants.h
 *
 *  Created on: 25.06.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC262_1420_TMC262_1420_CONSTANTS_H_
#define TMC_IC_TMC262_1420_TMC262_1420_CONSTANTS_H_

#include "../../helpers/Constants.h"

#define TMC262_1420_REGISTER_COUNT   8
#define TMC262_1420_MOTORS           1
#define TMC262_1420_WRITE_BIT        0x08
#define TMC262_1420_ADDRESS_MASK     0x07
#define TMC262_1420_ADDRESS_SHIFT    17
#define TMC262_1420_MAX_VELOCITY     s32_MAX
#define TMC262_1420_MAX_ACCELERATION u24_MAX

// read addresses correspond with RDSEL, added latest to access latest data of common lower 7 bits
#define TMC262_1420_RESPONSE0        0
#define TMC262_1420_RESPONSE1        1
#define TMC262_1420_RESPONSE2        2
#define TMC262_1420_RESPONSE_LATEST  3

#endif /* TMC_IC_TMC262_1420_TMC262_1420_CONSTANTS_H_ */
