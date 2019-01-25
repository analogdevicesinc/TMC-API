/*
 * TMC5072_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC5072_TMC5072_CONSTANTS_H_
#define TMC_IC_TMC5072_TMC5072_CONSTANTS_H_

#include "../../helpers/Constants.h"

#define TMC5072_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC5072_MOTORS           2
#define TMC5072_WRITE_BIT        TMC_WRITE_BIT
#define TMC5072_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC5072_MAX_VELOCITY     8388096
#define TMC5072_MAX_ACCELERATION u16_MAX

// Rampenmodi (Register TMC562_RAMPMODE)
#define TMC5072_MODE_POSITION  0
#define TMC5072_MODE_VELPOS    1
#define TMC5072_MODE_VELNEG    2
#define TMC5072_MODE_HOLD      3

#endif /* TMC_IC_TMC5072_TMC5072_CONSTANTS_H_ */
