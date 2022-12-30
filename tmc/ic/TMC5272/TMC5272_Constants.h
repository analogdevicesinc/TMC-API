/*
 * TMC5272_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: JH based on TMC5160_Constants.h
 */

#ifndef TMC_IC_TMC5272_TMC5272_CONSTANTS_H_
#define TMC_IC_TMC5272_TMC5272_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC5272_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC5272_MOTORS           2
#define TMC5272_WRITE_BIT        TMC_WRITE_BIT
#define TMC5272_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC5272_MAX_VELOCITY     8388096
#define TMC5272_MAX_ACCELERATION u16_MAX

//// ramp modes (Register TMC5272_RAMPMODE)
#define TMC5272_MODE_POSITION  0
#define TMC5272_MODE_VELPOS    1
#define TMC5272_MODE_VELNEG    2
#define TMC5272_MODE_HOLD      3
//


#endif /* TMC_IC_TMC5272_TMC5272_CONSTANTS_H_ */
