/*
 * TMC4330_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC4330_TMC4330_CONSTANTS_H_
#define TMC_IC_TMC4330_TMC4330_CONSTANTS_H_

#include "../../helpers/Constants.h"

#define TMC4330_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC4330_MOTORS           1
#define TMC4330_WRITE_BIT        TMC_WRITE_BIT
#define TMC4330_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC4330_MAX_VELOCITY     s32_MAX
#define TMC4330_MAX_ACCELERATION u24_MAX

#define TMC4330_RAMP_HOLD      0
#define TMC4330_RAMP_TRAPEZ    1
#define TMC4330_RAMP_SSHAPE    2
#define TMC4330_RAMP_POSITION  4

#endif /* TMC_IC_TMC4330_TMC4330_CONSTANTS_H_ */
