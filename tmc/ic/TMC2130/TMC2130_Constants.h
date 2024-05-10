/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2130_TMC2130_CONSTANTS_H_
#define TMC_IC_TMC2130_TMC2130_CONSTANTS_H_

#define TMC2130_REGISTER_COUNT   128 // Default register count
#define TMC2130_MOTORS           1
#define TMC2130_WRITE_BIT        0x80
#define TMC2130_ADDRESS_MASK     0x7F
#define TMC2130_MAX_VELOCITY     (int32_t)  2147483647
#define TMC2130_MAX_ACCELERATION (uint32_t)  16777215uL


#endif /* TMC_IC_TMC2130_TMC2130_CONSTANTS_H_ */
