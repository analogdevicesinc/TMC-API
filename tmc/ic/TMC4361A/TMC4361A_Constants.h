/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC4361A_TMC4361A_CONSTANTS_H_
#define TMC_IC_TMC4361A_TMC4361A_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC4361A_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC4361A_MOTORS           1
#define TMC4361A_WRITE_BIT        TMC_WRITE_BIT
#define TMC4361A_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC4361A_MAX_VELOCITY     s32_MAX
#define TMC4361A_MAX_ACCELERATION u24_MAX

#define TMC4361A_COVER_DONE (1<<25)

#define TMC4361A_RAMP_HOLD      0
#define TMC4361A_RAMP_TRAPEZ    1
#define TMC4361A_RAMP_SSHAPE    2

#define TMC4361A_RAMP_POSITION  4

#endif /* TMC_IC_TMC4361A_TMC4361A_CONSTANTS_H_ */
