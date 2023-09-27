/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC5240_REGISTER_H
#define TMC5240_REGISTER_H

// ===== TMC5240 register set =====

#define TMC5240_GCONF          0x00
#define TMC5240_GSTAT          0x01
#define TMC5240_IFCNT          0x02
#define TMC5240_SLAVECONF      0x03
#define TMC5240_INP_OUT        0x04
#define TMC5240_X_COMPARE      0x05
#define TMC5240_OTP_PROG       0x06
#define TMC5240_DRV_CONF       0x0A
#define TMC5240_GLOBAL_SCALER  0x0B

#define TMC5240_IHOLD_IRUN     0x10
#define TMC5240_TPOWERDOWN     0x11
#define TMC5240_TSTEP          0x12
#define TMC5240_TPWMTHRS       0x13
#define TMC5240_TCOOLTHRS      0x14
#define TMC5240_THIGH          0x15

#define TMC5240_RAMPMODE       0x20
#define TMC5240_XACTUAL        0x21
#define TMC5240_VACTUAL        0x22
#define TMC5240_VSTART         0x23
#define TMC5240_A1             0x24
#define TMC5240_V1             0x25
#define TMC5240_AMAX           0x26
#define TMC5240_VMAX           0x27
#define TMC5240_DMAX           0x28
#define TMC5240_TVMAX          0x29
#define TMC5240_D1             0x2A
#define TMC5240_VSTOP          0x2B
#define TMC5240_TZEROWAIT      0x2C
#define TMC5240_XTARGET        0x2D
#define TMC5240_V2	           0x2E
#define TMC5240_A2             0x2F

#define TMC5240_D2     		   0x30
#define TMC5240_AACTUAL        0x31
#define TMC5240_VDCMIN         0x33
#define TMC5240_SWMODE         0x34
#define TMC5240_RAMPSTAT       0x35
#define TMC5240_XLATCH         0x36
#define TMC5240_ENCMODE        0x38
#define TMC5240_XENC           0x39
#define TMC5240_ENC_CONST      0x3A
#define TMC5240_ENC_STATUS     0x3B
#define TMC5240_ENC_LATCH      0x3C
#define TMC5240_ENC_DEVIATION  0x3D

#define TMC5240_ADC_VSUPPLY_AIN 0x50
#define TMC5240_ADC_TEMP        0x51
#define TMC5240_OTW_OV_VTH      0x52

#define TMC5240_MSLUT0         0x60
#define TMC5240_MSLUT1         0x61
#define TMC5240_MSLUT2         0x62
#define TMC5240_MSLUT3         0x63
#define TMC5240_MSLUT4         0x64
#define TMC5240_MSLUT5         0x65
#define TMC5240_MSLUT6         0x66
#define TMC5240_MSLUT7         0x67
#define TMC5240_MSLUTSEL       0x68
#define TMC5240_MSLUTSTART     0x69
#define TMC5240_MSCNT          0x6A
#define TMC5240_MSCURACT       0x6B
#define TMC5240_CHOPCONF       0x6C
#define TMC5240_COOLCONF       0x6D
#define TMC5240_DCCTRL         0x6E
#define TMC5240_DRVSTATUS      0x6F

#define TMC5240_PWMCONF        0x70
#define TMC5240_PWMSCALE       0x71
#define TMC5240_PWM_AUTO       0x72
#define TMC5240_SG4_THRS       0x74
#define TMC5240_SG4_RESULT	   0x75
#define TMC5240_SG4_IND        0x76
#endif /* TMC5240_REGISTER_H */
