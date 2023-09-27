/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC7300_REGISTER_H
#define TMC7300_REGISTER_H

// ===== TMC7300 register set =====

#define TMC7300_GCONF          0x00
#define TMC7300_GSTAT          0x01
#define TMC7300_IFCNT          0x02
#define TMC7300_SLAVECONF      0x03
#define TMC7300_IOIN           0x06

#define TMC7300_CURRENT_LIMIT  0x10

#define TMC7300_PWM_AB         0x22

#define TMC7300_CHOPCONF       0x6C
#define TMC7300_DRVSTATUS      0x6F
#define TMC7300_PWMCONF        0x70

#endif /* TMC7300_Register */
