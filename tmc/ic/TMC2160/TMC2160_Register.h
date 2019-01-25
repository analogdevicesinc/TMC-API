/*
 * TMC2160_Register.h
 *
 *  Created on: 13.08.2018
 *      Author: LK
 */

#ifndef TMC2160_REGISTER_H
#define TMC2160_REGISTER_H

	// ===== TMC2160 register set =====

	#define TMC2160_GCONF       0x00
	#define TMC2160_GSTAT       0x01
	#define TMC2160_IOIN        0x04
	#define TMC2160_IHOLD_IRUN  0x10
	#define TMC2160_TPOWERDOWN  0x11
	#define TMC2160_TSTEP       0x12
	#define TMC2160_TPWMTHRS    0x13
	#define TMC2160_TCOOLTHRS   0x14
	#define TMC2160_THIGH       0x15

	#define TMC2160_XDIRECT     0x2D

	#define TMC2160_VDCMIN      0x33

	#define TMC2160_MSLUT0      0x60
	#define TMC2160_MSLUT1      0x61
	#define TMC2160_MSLUT2      0x62
	#define TMC2160_MSLUT3      0x63
	#define TMC2160_MSLUT4      0x64
	#define TMC2160_MSLUT5      0x65
	#define TMC2160_MSLUT6      0x66
	#define TMC2160_MSLUT7      0x67
	#define TMC2160_MSLUTSEL    0x68
	#define TMC2160_MSLUTSTART  0x69
	#define TMC2160_MSCNT       0x6A
	#define TMC2160_MSCURACT    0x6B
	#define TMC2160_CHOPCONF    0x6C
	#define TMC2160_COOLCONF    0x6D
	#define TMC2160_DCCTRL      0x6E
	#define TMC2160_DRV_STATUS  0x6F
	#define TMC2160_PWMCONF     0x70
	#define TMC2160_PWM_SCALE   0x71
	#define TMC2160_ENCM_CTRL   0x72
	#define TMC2160_LOST_STEPS  0x73

#endif /* TMC2160_REGISTER_H */
