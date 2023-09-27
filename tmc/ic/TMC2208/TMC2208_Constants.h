/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2208_TMC2208_CONSTANTS_H_
#define TMC_IC_TMC2208_TMC2208_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC2208_MOTORS           1
#define TMC2208_REGISTER_COUNT   TMC_REGISTER_COUNT
#define TMC2208_WRITE_BIT        TMC_WRITE_BIT
#define TMC2208_ADDRESS_MASK     TMC_ADDRESS_MASK
#define TMC2208_MAX_VELOCITY     s32_MAX
#define TMC2208_MAX_ACCELERATION u24_MAX

#endif /* TMC_IC_TMC2208_TMC2208_CONSTANTS_H_ */
