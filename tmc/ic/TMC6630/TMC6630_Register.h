/*
* TMC6630_Register.h
*
*  Created on: 29.11.2016
*      Author: ed / bs
*/

#ifndef TMC6630_REGISTER_H
#define TMC6630_REGISTER_H

// ===== TMC6630 register set =====

#define TMC6630_CHIPINFO_DATA                   0x00
#define TMC6630_CHIPINFO_ADDR                   0x01
#define TMC6630_GENERAL_CONF                    0x02
#define TMC6630_STATUS                          0x03

#define TMC6630_INPUT_RAW                       0x04
#define TMC6630_COMP_RAW_WVU                    0x05

#define TMC6630_ADC_RAW_N_CALCULATED_U_BEMF     0x06
#define TMC6630_Z_BLK_CNTS_FILT_LENGTH_NCALC    0x07

#define TMC6630_AUTO_ZERO_VAL_IB_COMP           0x08

#define TMC6630_IB_OFFSET_CONF_FILT_LENGTH      0x09

#define TMC6630_DIR_HALL_ACTUAL_ADC_IB          0x0A
#define TMC6630_TRIGGER_PWM_CNT_SG_HALL_STATE   0x0B
#define TMC6630_AUTO_SWITCH_ON_OFF              0x0C
#define TMC6630_START_CONF                      0x0D

// regulation drive and stop options
#define TMC6630_OP_MODE                         0x0F

#define TMC6630_PWM_BBM_CHOP_OPTS               0x10
#define TMC6630_PWM_FREQ_MAXCNT                 0x11
#define TMC6630_PWM_LIMIT_HIGH_LOW              0x12
#define TMC6630_PWM_LIMIT_DDT                   0x13
#define TMC6630_PWM_VALUE                       0x14
#define TMC6630_PWM_MAXCNT_INT_VALUE_INT        0x15
#define TMC6630_PWM_VALUE_DEBUG                 0x16
#define TMC6630_PWM_VALUE_RELATIV               0x17
#define TMC6630_PWM_MIN_STALL_VALUE             0x18
#define TMC6630_SOUND_OPTS                      0x19
#define TMC6630_LED_CONF                        0x1A
#define TMC6630_SINCOMM_PHIDDT_PHI              0x1B
#define TMC6630_SINCOMM_PHIOUT_AMPL				0x1C
#define TMC6630_SINCOMM_PWMU_IBU                0x1D
#define TMC6630_SINCOMM_PWMV_IBV                0x1E
#define TMC6630_SINCOMM_PWMW_IBW                0x1F

#define TMC6630_CROSSING_OPTS                   0x20
#define TMC6630_HALL_DUR_EXT                    0x21
#define TMC6630_CROSSING_CNTS_MIN               0x22
#define TMC6630_CROSSING_CNTS_MAX               0x23
#define TMC6630_HALL_NEXT_HALL_ACTUAL_CROSSING  0x24
#define TMC6630_CROSSING_FILT                   0x25
#define TMC6630_CROSSING_SIGNAL_COUNT           0x26
#define TMC6630_HALL_DUR_P_I                    0x27
#define TMC6630_HALL_DURATION                   0x28
#define TMC6630_HALL_DURATION_PI                0x29
#define TMC6630_HALL_DURATION_FLT               0x2A

#define TMC6630_VELOCITY_PID_OPTS               0x30

// torque mode
#define TMC6630_TORQUE_P_I                      0x31
#define TMC6630_TORQUE_MAX_MIN                  0x32
#define TMC6630_TORQUE_TARGET_LIMIT_DDT         0x33
#define TMC6630_TORQUE_ERROR_PWM_VALUE          0x34
#define TMC6630_TORQUE_ERROR_SUM                0x35

// velocity mode
#define TMC6630_VELOCITY_P_I                    0x37
#define TMC6630_VELOCITY_MAX                    0x38
#define TMC6630_VELOCITY_MIN                    0x39
#define TMC6630_VELOCITY_LIMIT_DDT              0x3A
#define TMC6630_VELOCITY_TARGET                 0x3B
#define TMC6630_VELOCITY_ACTUAL                 0x3C
#define TMC6630_VELOCITY_ERROR                  0x3D
#define TMC6630_VELOCITY_ERROR_SUM              0x3E
#define TMC6630_VELOCITY_TORQUE_TARGET          0x3F

#define TMC6630_TORQUE_TARGET_LIMIT_DDT_OUT     0x47
#define TMC6630_VELOCITY_TARGET_LIMIT_DDT_OUT   0x48

// PWM input
#define TMC6630_PWM_CNTL_FILTER_MAXCNT_LENGTH   0x50
#define TMC6630_PWM_CNTL_LIMIT_MAX_SHORT_CNT    0x51
#define TMC6630_PWM_CNTL_DUTY_MAX_MIN           0x52
#define TMC6630_PWM_CNTL_DUTY_FILTERED_CALC     0x53

#define TMC6630_UART_BPS                        0x60
#define TMC6630_TEST_VECTOR                     0x61
#define TMC6630_HIGH_FLOAT_LOW                  0x62
#define TMC6630_INTEGRAL_ACTUAL                 0x63
#define TMC6630_INTEGRAL_LAST                   0x64

#define TMC6630_CNT01_INTEGRAL_LAST             0x6A
#define TMC6630_CNT01_INTEGRAL                  0x6B

#define TMC6630_ORDER                           0x7F

#endif /* TMC6630_REGISTER_H */
