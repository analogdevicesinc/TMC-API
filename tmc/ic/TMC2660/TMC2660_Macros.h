/*
 * TMC2660_Macros.h
 *
 *  Created on: 01.10.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC2660_TMC2660_MACROS_H_
#define TMC_IC_TMC2660_TMC2660_MACROS_H_

#include "TMC2660_Constants.h"

#define TMC2660_IS_WRITE(datagram) ((datagram) >> (TMC2660_ADDRESS_SHIFT + 3))
#define TMC2660_ADDRESS(datagram) (((datagram) >> TMC2660_ADDRESS_SHIFT) & TMC2660_ADDRESS_MASK)
#define TMC2660_VALUE(datagram) ((datagram) & TMC2660_VALUE_MASK)

#endif /* TMC_IC_TMC2660_TMC2660_MACROS_H_ */
