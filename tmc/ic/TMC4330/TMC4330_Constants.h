/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC4330_TMC4330_CONSTANTS_H_
#define TMC_IC_TMC4330_TMC4330_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

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
