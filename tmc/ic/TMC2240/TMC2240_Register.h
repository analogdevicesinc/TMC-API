/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC2240_REGISTER_H
#define TMC2240_REGISTER_H

// ===== TMC2240 register set =====

#define TMC2240_GCONF          0x00
#define TMC2240_GSTAT          0x01
#define TMC2240_IFCNT          0x02
#define TMC2240_SLAVECONF      0x03
#define TMC2240_IOIN           0x04
#define TMC2240_DRV_CONF       0x0A
#define TMC2240_GLOBAL_SCALER  0x0B

#define TMC2240_IHOLD_IRUN     0x10
#define TMC2240_TPOWERDOWN     0x11
#define TMC2240_TSTEP          0x12
#define TMC2240_TPWMTHRS       0x13
#define TMC2240_TCOOLTHRS      0x14
#define TMC2240_THIGH          0x15

#define TMC2240_DIRECT_MODE    0x2D

#define TMC2240_ENCMODE        0x38
#define TMC2240_XENC           0x39
#define TMC2240_ENC_CONST      0x3A
#define TMC2240_ENC_STATUS     0x3B
#define TMC2240_ENC_LATCH      0x3C

#define TMC2240_ADC_VSUPPLY_AIN 0x50
#define TMC2240_ADC_TEMP        0x51
#define TMC2240_OTW_OV_VTH      0x52

#define TMC2240_MSLUT0         0x60
#define TMC2240_MSLUT1         0x61
#define TMC2240_MSLUT2         0x62
#define TMC2240_MSLUT3         0x63
#define TMC2240_MSLUT4         0x64
#define TMC2240_MSLUT5         0x65
#define TMC2240_MSLUT6         0x66
#define TMC2240_MSLUT7         0x67
#define TMC2240_MSLUTSEL       0x68
#define TMC2240_MSLUTSTART     0x69
#define TMC2240_MSCNT          0x6A
#define TMC2240_MSCURACT       0x6B
#define TMC2240_CHOPCONF       0x6C
#define TMC2240_COOLCONF       0x6D
#define TMC2240_DCCTRL         0x6E
#define TMC2240_DRVSTATUS      0x6F

#define TMC2240_PWMCONF        0x70
#define TMC2240_PWMSCALE       0x71
#define TMC2240_PWM_AUTO       0x72
#define TMC2240_SG4_THRS       0x74
#define TMC2240_SG4_RESULT	   0x75
#define TMC2240_SG4_IND        0x76
#endif /* TMC2240_REGISTER_H */
