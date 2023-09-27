/*******************************************************************************
* Copyright © 2020 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC2226_REGISTER_H
#define TMC2226_REGISTER_H

// ===== TMC2226 & 2202 & TMC2226 & 2220 & 2225 "Donkey Kong" family register set =====

#define TMC2226_GCONF         0x00
#define TMC2226_GSTAT         0x01
#define TMC2226_IFCNT         0x02
#define TMC2226_SLAVECONF     0x03
#define TMC2226_OTP_PROG      0x04
#define TMC2226_OTP_READ      0x05
#define TMC2226_IOIN          0x06
#define TMC2226_FACTORY_CONF  0x07

#define TMC2226_IHOLD_IRUN    0x10
#define TMC2226_TPOWERDOWN    0x11
#define TMC2226_TSTEP         0x12
#define TMC2226_TPWMTHRS      0x13
#define TMC2226_TCOOLTHRS     0x14

#define TMC2226_VACTUAL       0x22

#define TMC2226_SGTHRS        0x40
#define TMC2226_SG_RESULT     0x41
#define TMC2226_COOLCONF      0x42

#define TMC2226_MSCNT         0x6A
#define TMC2226_MSCURACT      0x6B
#define TMC2226_CHOPCONF      0x6C

#define TMC2226_DRVSTATUS     0x6F

#define TMC2226_PWMCONF       0x70
#define TMC2226_PWMSCALE      0x71
#define TMC2226_PWM_AUTO      0x72

#endif /* TMC2226_Register */
