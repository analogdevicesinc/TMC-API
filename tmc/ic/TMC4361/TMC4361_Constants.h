/*
 * TMC4361_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC4361_TMC4361_CONSTANTS_H_
#define TMC_IC_TMC4361_TMC4361_CONSTANTS_H_

#include "../../helpers/Constants.h"

#define TMC4361_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC4361_MOTORS           1
#define TMC4361_WRITE_BIT        TMC_WRITE_BIT
#define TMC4361_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC4361_MAX_VELOCITY     s32_MAX
#define TMC4361_MAX_ACCELERATION u24_MAX

#define TMC4361_COVER_DONE (1<<25)

#define TMC4361_RAMP_HOLD      0
#define TMC4361_RAMP_TRAPEZ    1
#define TMC4361_RAMP_SSHAPE    2
#define TMC4361_RAMP_POSITION  4
#define TMC4361_RAMP_HOLD      0

#endif /* TMC_IC_TMC4361_TMC4361_CONSTANTS_H_ */
