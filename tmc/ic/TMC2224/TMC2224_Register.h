/*
 * TMC2224_Register.h
 *
 *  Created on: 10.11.2016
 *      Author: bd
 */

#ifndef TMC2224_REGISTER_H
#define TMC2224_REGISTER_H

// ===== TMC2208 & 2202 & TMC2224 & 2220 & 2225 "Donkey Kong" family register set =====

#define TMC2224_GCONF         0x00
#define TMC2224_GSTAT         0x01
#define TMC2224_IFCNT         0x02
#define TMC2224_SLAVECONF     0x03
#define TMC2224_OTP_PROG      0x04
#define TMC2224_OTP_READ      0x05
#define TMC2224_IOIN          0x06
#define TMC2224_FACTORY_CONF  0x07

#define TMC2224_IHOLD_IRUN    0x10
#define TMC2224_TPOWERDOWN    0x11
#define TMC2224_TSTEP         0x12
#define TMC2224_TPWMTHRS      0x13

#define TMC2224_VACTUAL       0x22

#define TMC2224_MSCNT         0x6A
#define TMC2224_MSCURACT      0x6B
#define TMC2224_CHOPCONF      0x6C
#define TMC2224_DRVSTATUS     0x6F
#define TMC2224_PWMCONF       0x70
#define TMC2224_PWMSCALE      0x71
#define TMC2224_PWM_AUTO      0x72

#endif /* TMC2224_REGISTER_H */
