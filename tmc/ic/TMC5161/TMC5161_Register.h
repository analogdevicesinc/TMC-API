/*
* TMC5161_Register.h
*
*  Created on: 13.06.2018
*      Author: LK
*/

#ifndef TMC5161_REGISTER_H
#define TMC5161_REGISTER_H

// ===== TMC5161 register set =====

#define TMC5161_GCONF          0x00
#define TMC5161_GSTAT          0x01
#define TMC5161_IFCNT          0x02
#define TMC5161_SLAVECONF      0x03
#define TMC5161_INP_OUT        0x04
#define TMC5161_X_COMPARE      0x05
#define TMC5161_OTP_PROG       0x06
#define TMC5161_OTP_READ       0x07
#define TMC5161_FACTORY_CONF   0x08
#define TMC5161_SHORT_CONF     0x09
#define TMC5161_DRV_CONF       0x0A
#define TMC5161_GLOBAL_SCALER  0x0B
#define TMC5161_OFFSET_READ    0x0C
#define TMC5161_IHOLD_IRUN     0x10
#define TMC5161_TPOWERDOWN     0x11
#define TMC5161_TSTEP          0x12
#define TMC5161_TPWMTHRS       0x13
#define TMC5161_TCOOLTHRS      0x14
#define TMC5161_THIGH          0x15

#define TMC5161_RAMPMODE       0x20
#define TMC5161_XACTUAL        0x21
#define TMC5161_VACTUAL        0x22
#define TMC5161_VSTART         0x23
#define TMC5161_A1             0x24
#define TMC5161_V1             0x25
#define TMC5161_AMAX           0x26
#define TMC5161_VMAX           0x27
#define TMC5161_DMAX           0x28
#define TMC5161_D1             0x2A
#define TMC5161_VSTOP          0x2B
#define TMC5161_TZEROWAIT      0x2C
#define TMC5161_XTARGET        0x2D

#define TMC5161_VDCMIN         0x33
#define TMC5161_SWMODE         0x34
#define TMC5161_RAMPSTAT       0x35
#define TMC5161_XLATCH         0x36
#define TMC5161_ENCMODE        0x38
#define TMC5161_XENC           0x39
#define TMC5161_ENC_CONST      0x3A
#define TMC5161_ENC_STATUS     0x3B
#define TMC5161_ENC_LATCH      0x3C
#define TMC5161_ENC_DEVIATION  0x3D

#define TMC5161_MSLUT0         0x60
#define TMC5161_MSLUT1         0x61
#define TMC5161_MSLUT2         0x62
#define TMC5161_MSLUT3         0x63
#define TMC5161_MSLUT4         0x64
#define TMC5161_MSLUT5         0x65
#define TMC5161_MSLUT6         0x66
#define TMC5161_MSLUT7         0x67
#define TMC5161_MSLUTSEL       0x68
#define TMC5161_MSLUTSTART     0x69
#define TMC5161_MSCNT          0x6A
#define TMC5161_MSCURACT       0x6B
#define TMC5161_CHOPCONF       0x6C
#define TMC5161_COOLCONF       0x6D
#define TMC5161_DCCTRL         0x6E
#define TMC5161_DRVSTATUS      0x6F
#define TMC5161_PWMCONF        0x70
#define TMC5161_PWMSCALE       0x71
#define TMC5161_PWM_AUTO       0x72
#define TMC5161_LOST_STEPS     0x73

#endif /* TMC5161_REGISTER_H */
