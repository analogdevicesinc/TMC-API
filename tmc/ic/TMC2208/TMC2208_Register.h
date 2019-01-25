/*
 * TMC2208_Register.h
 *
 *  Created on: 11.07.2017
 *      Author: LK
 */

#ifndef TMC2208_REGISTER_H
#define TMC2208_REGISTER_H

// ===== TMC2208 & 2202 & TMC2208 & 2220 & 2225 "Donkey Kong" family register set =====

#define TMC2208_GCONF         0x00
#define TMC2208_GSTAT         0x01
#define TMC2208_IFCNT         0x02
#define TMC2208_SLAVECONF     0x03
#define TMC2208_OTP_PROG      0x04
#define TMC2208_OTP_READ      0x05
#define TMC2208_IOIN          0x06
#define TMC2208_FACTORY_CONF  0x07

#define TMC2208_IHOLD_IRUN    0x10
#define TMC2208_TPOWERDOWN    0x11
#define TMC2208_TSTEP         0x12
#define TMC2208_TPWMTHRS      0x13

#define TMC2208_VACTUAL       0x22

#define TMC2208_MSCNT         0x6A
#define TMC2208_MSCURACT      0x6B
#define TMC2208_CHOPCONF      0x6C
#define TMC2208_DRVSTATUS     0x6F
#define TMC2208_PWMCONF       0x70
#define TMC2208_PWMSCALE      0x71
#define TMC2208_PWM_AUTO      0x72

#endif /* TMC2208_Register */
