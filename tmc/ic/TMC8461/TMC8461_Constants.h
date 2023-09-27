/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC8461_TMC8461_CONSTANTS_H_
#define TMC_IC_TMC8461_TMC8461_CONSTANTS_H_

#include "tmc/helpers/Constants.h"

#define TMC8461_CMD_READ      0x02
#define TMC8461_CMD_READ_WAIT 0x03
#define TMC8461_CMD_WRITE     0x04
#define TMC8461_CMD_ADDR_EXT  0x06

#define TMC8461_ESC_EEP_CMD_IDLE 0b000
#define TMC8461_ESC_EEP_CMD_READ 0b001
#define TMC8461_ESC_EEP_CMD_WRITE 0b010
#define TMC8461_ESC_EEP_CMD_RELOAD 0b100

#define TMC8461_EC_STATE_INIT 1
#define TMC8461_EC_STATE_BOOTSTRAP 3
#define TMC8461_EC_STATE_PREOP 2
#define TMC8461_EC_STATE_SAFEOP 4
#define TMC8461_EC_STATE_OPERATIONAL 8

#define TMC8461_MAGIC_RESET 0x524553
#define TMC8461_MAGIC_RESET_0 0x52 // 'R'
#define TMC8461_MAGIC_RESET_1 0x45 // 'E'
#define TMC8461_MAGIC_RESET_2 0x53 // 'S'

#endif /* TMC_IC_TMC8461_TMC8461_CONSTANTS_H_ */
