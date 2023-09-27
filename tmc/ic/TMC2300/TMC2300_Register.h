/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC2300_REGISTER_H
#define TMC2300_REGISTER_H

// ===== TMC2300 register set =====

#define TMC2300_GCONF         0x00
#define TMC2300_GSTAT         0x01
#define TMC2300_IFCNT         0x02
#define TMC2300_SLAVECONF     0x03
#define TMC2300_IOIN          0x06

#define TMC2300_IHOLD_IRUN    0x10
#define TMC2300_TPOWERDOWN    0x11
#define TMC2300_TSTEP         0x12

#define TMC2300_TCOOLTHRS     0x14

#define TMC2300_VACTUAL       0x22
#define TMC2300_XDIRECT       0x22

#define TMC2300_SGTHRS        0x40
#define TMC2300_SG_VALUE      0x41
#define TMC2300_COOLCONF      0x42

#define TMC2300_MSCNT         0x6A
#define TMC2300_CHOPCONF      0x6C
#define TMC2300_DRVSTATUS     0x6F
#define TMC2300_PWMCONF       0x70
#define TMC2300_PWMSCALE      0x71
#define TMC2300_PWM_AUTO      0x72

#endif /* TMC2300_Register */
