/*
 * TMCMinion_Register.h
 *
 *  Created on: 11.01.2019
 *      Author: LK
 */

#ifndef TMCMinion_REGISTER_H
#define TMCMinion_REGISTER_H

// ===== TMCMinion register set =====

#define TMCMinion_GCONF         0x00
#define TMCMinion_GSTAT         0x01
#define TMCMinion_IFCNT         0x02
#define TMCMinion_SLAVECONF     0x03
#define TMCMinion_IOIN          0x06

#define TMCMinion_IHOLD_IRUN    0x10
#define TMCMinion_TPOWERDOWN    0x11
#define TMCMinion_TSTEP         0x12
#define TMCMinion_TCOOLTHRS     0x14
#define TMCMinion_SGTHRS        0x40
#define TMCMinion_SG_VALUE      0x41
#define TMCMinion_COOLCONF      0x42

#define TMCMinion_VACTUAL       0x22

#define TMCMinion_MSCNT         0x6A
#define TMCMinion_MSCURACT      0x6B
#define TMCMinion_CHOPCONF      0x6C
#define TMCMinion_DRVSTATUS     0x6F
#define TMCMinion_PWMCONF       0x70
#define TMCMinion_PWMSCALE      0x71
#define TMCMinion_PWM_AUTO      0x72

#endif /* TMCMinion_Register */
