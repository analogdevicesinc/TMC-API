/*
 * TMC2225_Register.h
 *
 *  Created on: 16.07.2017
 *      Author: LH
 */

#ifndef TMC2225_REGISTER_H
#define TMC2225_REGISTER_H

// ===== TMC2208 & 2202 & TMC2208 & 2220 & 2225 "Donkey Kong" family register set =====

#define TMC2225_GCONF         0x00
#define TMC2225_GSTAT         0x01
#define TMC2225_IFCNT         0x02
#define TMC2225_SLAVECONF     0x03
#define TMC2225_OTP_PROG      0x04
#define TMC2225_OTP_READ      0x05
#define TMC2225_IOIN          0x06
#define TMC2225_FACTORY_CONF  0x07

#define TMC2225_IHOLD_IRUN    0x10
#define TMC2225_TPOWERDOWN    0x11
#define TMC2225_TSTEP         0x12
#define TMC2225_TPWMTHRS      0x13

#define TMC2225_VACTUAL       0x22

#define TMC2225_MSCNT         0x6A
#define TMC2225_MSCURACT      0x6B
#define TMC2225_CHOPCONF      0x6C
#define TMC2225_DRVSTATUS     0x6F
#define TMC2225_PWMCONF       0x70
#define TMC2225_PWMSCALE      0x71
#define TMC2225_PWM_AUTO      0x72

#endif /* TMC2225_Register */
