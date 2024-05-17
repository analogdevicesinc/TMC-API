/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2226_TMC2226_CONSTANTS_H_
#define TMC_IC_TMC2226_TMC2226_CONSTANTS_H_

#define TMC2226_MOTORS           			1
#define TMC2226_REGISTER_COUNT   			128 // Default register count
#define TMC2226_WRITE_BIT        			0x80
#define TMC2226_ADDRESS_MASK     			0x7F
#define TMC2226_MAX_VELOCITY     (int32_t) 	2147483647
#define TMC2226_MAX_ACCELERATION (uint32_t)	16777215uL

#endif /* TMC_IC_TMC2226_TMC2226_CONSTANTS_H_ */
