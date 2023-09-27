/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5062_TMC5062_CONSTANTS_H_
#define TMC_IC_TMC5062_TMC5062_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC5062_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC5062_MOTORS           2
#define TMC5062_WRITE_BIT        TMC_WRITE_BIT
#define TMC5062_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC5062_MAX_VELOCITY     8388096
#define TMC5062_MAX_ACCELERATION u16_MAX

// Rampenmodi (Register TMC5062_RAMPMODE)
#define TMC5062_MODE_POSITION  0
#define TMC5062_MODE_VELPOS    1
#define TMC5062_MODE_VELNEG    2
#define TMC5062_MODE_HOLD      3

#endif /* TMC_IC_TMC5062_TMC5062_CONSTANTS_H_ */
