/*
 * TMC6630_Constants.h
 *
 *  Created on: 23.07.2018
 *      Author: LK
 */

#ifndef TMC_IC_TMC6630_TMC6630_CONSTANTS_H_
#define TMC_IC_TMC6630_TMC6630_CONSTANTS_H_

#include "../../helpers/Constants.h"

// pwm opts
#define TMC6630_PWM_OPTS_USE_EXT_HALL_VALUES_MASK  0x1
#define TMC6630_PWM_OPTS_USE_DYNAMiC_PWM           0x2
#define TMC6630_PWM_OPTS_USE_PWM_LIMIT_DDT         0x4

// motion modes
#define TMC6630_MOTION_MODE_STOPPED   0
#define TMC6630_MOTION_MODE_PWM_CNTL  1
#define TMC6630_MOTION_MODE_PWM_EXT   2
#define TMC6630_MOTION_MODE_TORQUE    4
#define TMC6630_MOTION_MODE_VELOCITY  8

// hall value opts
#define TMC6630_EXT_HALL_VALUE_MASK   0x000E0000
#define TMC6630_EXT_HALL_VALUE_SHIFT  17

#endif /* TMC_IC_TMC6630_TMC6630_CONSTANTS_H_ */
