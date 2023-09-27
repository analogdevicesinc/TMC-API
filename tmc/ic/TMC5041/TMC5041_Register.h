/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC5041_REGISTER_H
#define TMC5041_REGISTER_H

// ===== TMC5041 register set =====

#define TMC5041_MOTOR_ADDR(m)      (0x20 << m)
#define TMC5041_MOTOR_ADDR_DRV(m)  (m << 4)
#define TMC5041_MOTOR_ADDR_PWM(m)  (m << 3)

#define TMC5041_GCONF      0x00
#define TMC5041_GSTAT      0x01
#define TMC5041_IFCNT      0x02
#define TMC5041_SLAVECONF  0x03
#define TMC5041_INPUT      0x04
#define TMC5041_X_COMPARE  0x05
                                                                         // motor = 0       motor = 1
#define TMC5041_PWMCONF(motor)     (0x10|TMC5041_MOTOR_ADDR_PWM(motor))  //      0x10            0x18
#define TMC5041_PWM_STATUS(motor)  (0x11|TMC5041_MOTOR_ADDR_PWM(motor))  //      0x11            0x19

                                                                         // motor = 0       motor = 1
#define TMC5041_RAMPMODE(motor)    (0x00|TMC5041_MOTOR_ADDR(motor))      //      0x20            0x40
#define TMC5041_XACTUAL(motor)     (0x01|TMC5041_MOTOR_ADDR(motor))      //      0x21            0x41
#define TMC5041_VACTUAL(motor)     (0x02|TMC5041_MOTOR_ADDR(motor))      //      0x22            0x42
#define TMC5041_VSTART(motor)      (0x03|TMC5041_MOTOR_ADDR(motor))      //      0x23            0x43
#define TMC5041_A1(motor)          (0x04|TMC5041_MOTOR_ADDR(motor))      //      0x24            0x44
#define TMC5041_V1(motor)          (0x05|TMC5041_MOTOR_ADDR(motor))      //      0x25            0x45
#define TMC5041_AMAX(motor)        (0x06|TMC5041_MOTOR_ADDR(motor))      //      0x26            0x46
#define TMC5041_VMAX(motor)        (0x07|TMC5041_MOTOR_ADDR(motor))      //      0x27            0x47
#define TMC5041_DMAX(motor)        (0x08|TMC5041_MOTOR_ADDR(motor))      //      0x28            0x48
#define TMC5041_D1(motor)          (0x0A|TMC5041_MOTOR_ADDR(motor))      //      0x2A            0x4A
#define TMC5041_VSTOP(motor)       (0x0B|TMC5041_MOTOR_ADDR(motor))      //      0x2B            0x4B
#define TMC5041_TZEROWAIT(motor)   (0x0C|TMC5041_MOTOR_ADDR(motor))      //      0x2C            0x4C
#define TMC5041_XTARGET(motor)     (0x0D|TMC5041_MOTOR_ADDR(motor))      //      0x2D            0x4D
#define TMC5041_IHOLD_IRUN(motor)  (0x10|TMC5041_MOTOR_ADDR(motor))      //      0x30            0x50
#define TMC5041_VCOOLTHRS(motor)   (0x11|TMC5041_MOTOR_ADDR(motor))      //      0x31            0x51
#define TMC5041_VHIGH(motor)       (0x12|TMC5041_MOTOR_ADDR(motor))      //      0x32            0x52
#define TMC5041_VDCMIN(motor)      (0x13|TMC5041_MOTOR_ADDR(motor))      //      0x33            0x53
#define TMC5041_SWMODE(motor)      (0x14|TMC5041_MOTOR_ADDR(motor))      //      0x34            0x54
#define TMC5041_RAMPSTAT(motor)    (0x15|TMC5041_MOTOR_ADDR(motor))      //      0x35            0x55
#define TMC5041_XLATCH(motor)      (0x16|TMC5041_MOTOR_ADDR(motor))      //      0x36            0x56
#define TMC5041_ENC_CONST(motor)   (0x1A|TMC5041_MOTOR_ADDR(motor))      //      0x3A            0x5A // todo CHECK REM 3: should be removable, TMC5041 doesn't have encoder features. Still used though (LH)

                                                                         // motor = 0       motor = 1
#define TMC5041_MSLUT0(motor)      (0x60|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x60            0x70
#define TMC5041_MSLUT1(motor)      (0x61|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x61            0x71
#define TMC5041_MSLUT2(motor)      (0x62|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x62            0x72
#define TMC5041_MSLUT3(motor)      (0x63|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x63            0x73
#define TMC5041_MSLUT4(motor)      (0x64|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x64            0x74
#define TMC5041_MSLUT5(motor)      (0x65|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x65            0x75
#define TMC5041_MSLUT6(motor)      (0x66|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x66            0x76
#define TMC5041_MSLUT7(motor)      (0x67|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x67            0x77
#define TMC5041_MSLUTSEL(motor)    (0x68|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x68            0x78
#define TMC5041_MSLUTSTART(motor)  (0x69|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x69            0x79
#define TMC5041_MSCNT(motor)       (0x6A|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x6A            0x7A
#define TMC5041_MSCURACT(motor)    (0x6B|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x6B            0x7B
#define TMC5041_CHOPCONF(motor)    (0x6C|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x6C            0x7C
#define TMC5041_COOLCONF(motor)    (0x6D|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x6D            0x7D
#define TMC5041_DRVSTATUS(motor)   (0x6F|TMC5041_MOTOR_ADDR_DRV(motor))  //      0x6F            0x7F

#endif /* TMC5041_REGISTER_H */
