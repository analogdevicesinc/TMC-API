/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2660_TMC2660_MACROS_H_
#define TMC_IC_TMC2660_TMC2660_MACROS_H_

#include "TMC2660_Constants.h"

#define TMC2660_IS_WRITE(datagram) ((datagram) >> (TMC2660_ADDRESS_SHIFT + 3))
#define TMC2660_ADDRESS(datagram) (((datagram) >> TMC2660_ADDRESS_SHIFT) & TMC2660_ADDRESS_MASK)
#define TMC2660_VALUE(datagram) ((datagram) & TMC2660_VALUE_MASK)

#endif /* TMC_IC_TMC2660_TMC2660_MACROS_H_ */
