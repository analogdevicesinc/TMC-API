/*
 * TMC5271_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: JH based on TMC5160_Constants.h
 */

#ifndef TMC_IC_TMC5271_TMC5271_CONSTANTS_H_
#define TMC_IC_TMC5271_TMC5271_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC5271_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC5271_MOTORS           1
#define TMC5271_WRITE_BIT        TMC_WRITE_BIT
#define TMC5271_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC5271_MAX_VELOCITY     8388096
#define TMC5271_MAX_ACCELERATION u16_MAX

//// ramp modes (Register TMC5271_RAMPMODE)
#define TMC5271_MODE_POSITION  0
#define TMC5271_MODE_VELPOS    1
#define TMC5271_MODE_VELNEG    2
#define TMC5271_MODE_HOLD      3
//


#endif /* TMC_IC_TMC5271_TMC5271_CONSTANTS_H_ */
