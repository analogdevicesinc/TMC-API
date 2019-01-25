/*
 * TMC2130_Register.h
 *
 *  Created on: 30.09.2016
 *      Author: bd
 */

#ifndef TMC2130_REGISTER_H
#define TMC2130_REGISTER_H

	// ===== TMC2130 register set =====

	#define TMC2130_GCONF       0x00
	#define TMC2130_GSTAT       0x01
	#define TMC2130_IOIN        0x04
	#define TMC2130_IHOLD_IRUN  0x10
	#define TMC2130_TPOWERDOWN  0x11
	#define TMC2130_TSTEP       0x12
	#define TMC2130_TPWMTHRS    0x13
	#define TMC2130_TCOOLTHRS   0x14
	#define TMC2130_THIGH       0x15

	#define TMC2130_XDIRECT     0x2D

	#define TMC2130_VDCMIN      0x33

	#define TMC2130_MSLUT0      0x60
	#define TMC2130_MSLUT1      0x61
	#define TMC2130_MSLUT2      0x62
	#define TMC2130_MSLUT3      0x63
	#define TMC2130_MSLUT4      0x64
	#define TMC2130_MSLUT5      0x65
	#define TMC2130_MSLUT6      0x66
	#define TMC2130_MSLUT7      0x67
	#define TMC2130_MSLUTSEL    0x68
	#define TMC2130_MSLUTSTART  0x69
	#define TMC2130_MSCNT       0x6A
	#define TMC2130_MSCURACT    0x6B
	#define TMC2130_CHOPCONF    0x6C
	#define TMC2130_COOLCONF    0x6D
	#define TMC2130_DCCTRL      0x6E
	#define TMC2130_DRV_STATUS  0x6F
	#define TMC2130_PWMCONF     0x70
	#define TMC2130_PWM_SCALE   0x71
	#define TMC2130_ENCM_CTRL   0x72
	#define TMC2130_LOST_STEPS  0x73

#endif /* TMC2130_REGISTER_H */
