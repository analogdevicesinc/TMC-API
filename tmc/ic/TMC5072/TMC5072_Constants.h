/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5072_TMC5072_CONSTANTS_H_
#define TMC_IC_TMC5072_TMC5072_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

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
