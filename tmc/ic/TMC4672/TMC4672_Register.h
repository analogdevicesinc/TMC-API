/*
 * TMC4672_Registers.h
 *
 *  Created on: 09.11.2018
 *      Author: LK / ED
 */

#ifndef TMC4672_REGISTERS_H
#define TMC4672_REGISTERS_H

// ===== TMC4672 register set =====

#define TMC4672_CHIPINFO_DATA                      0x00
#define TMC4672_CHIPINFO_ADDR                      0x01

#define TMC4672_ADC_RAW_DATA                       0x02
#define TMC4672_ADC_RAW_ADDR                       0x03
#define TMC4672_ADC_CONFIG_DATA                    0x04
#define TMC4672_ADC_CONFIG_ADDR                    0x05

#define TMC4672_ADC_IWY_IUX                        0x06
#define TMC4672_ADC_IV_VM                          0x07
#define TMC4672_AENC_WY_UX                         0x08
#define TMC4672_AENC_VN                            0x09

#define TMC4672_PWM_POLARITIES                     0x0A
#define TMC4672_PWM_MAXCOUNT                       0x0B
#define TMC4672_PWM_BBM_H_BBM_L                    0x0C
#define TMC4672_PWM_SV_CHOP                        0x0D
#define TMC4672_MOTOR_TYPE_N_POLE_PAIRS            0x0E
#define TMC4672_ADC_I1_I0_EXT                      0x0F

#define TMC4672_PHI_E_EXT                          0x11
#define TMC4672_PHI_M_EXT                          0x12
#define TMC4672_POSITION_EXT                       0x13

#define TMC4672_OPENLOOP_MODE                      0x14
#define TMC4672_OPENLOOP_ACCELERATION              0x15
#define TMC4672_OPENLOOP_VELOCITY_TARGET           0x16
#define TMC4672_OPENLOOP_VELOCITY_ACTUAL           0x17
#define TMC4672_PHI_OPENLOOP                       0x18
#define TMC4672_UQ_UD_EXT                          0x19

#define TMC4672_POS_FB_CONFIG_DATA				   0x1A
#define TMC4672_POS_FB_CONFIG_ADDR				   0x1B

#define TMC4672_CONFIG_DATA                        0x1C
#define TMC4672_CONFIG_ADDR                        0x1D

#define TMC4672_ABN_DECODER_COUNT                  0x1E
#define TMC4672_ABN_DECODER_COUNT_N                0x1F
#define TMC4672_ABN_DECODER_PHI_E_PHI_M            0x20
#define TMC4672_ABN_DECODER_POSITION               0x21

#define TMC4672_ABN_2_DECODER_COUNT                0x22
#define TMC4672_ABN_2_DECODER_COUNT_N              0x23
#define TMC4672_ABN_2_DECODER_PHI_E_PHI_M          0x24
#define TMC4672_ABN_2_DECODER_POSITION             0x25

#define TMC4672_HALL_PHI_E_INTERPOLATED_PHI_E      0x26
#define TMC4672_HALL_PHI_M                         0x27

#define TMC4672_AENC_DECODER_COUNT                 0x28
#define TMC4672_AENC_DECODER_COUNT_N               0x29
#define TMC4672_AENC_DECODER_PHI_E_PHI_M           0x2A
#define TMC4672_AENC_DECODER_POSITION              0x2B

#define TMC4672_RAMP_STATUS						   0x2D
#define TMC4672_RAMP_AMAX_A1					   0x2E
#define TMC4672_RAMP_DMAX_D1					   0x2F
#define TMC4672_RAMP_VSTART 					   0x30
#define TMC4672_RAMP_V1     					   0x31
#define TMC4672_RAMP_VSTOP     					   0x32
#define TMC4672_RAMP_TZEROWAIT_SWITCHMODE		   0x33
#define TMC4672_RAMP_X_ACTUAL		               0x34
#define TMC4672_RAMP_V_ACTUAL		               0x35
#define TMC4672_RAMP_X_TARGET		               0x36
#define TMC4672_RAMP_V_FEEDFORWARD	               0x37

#define TMC4672_OBSERVER_R_S_L_S_CROSS             0x3A
#define TMC4672_OBSERVER_L_SD_L_SQ	               0x3B
#define TMC4672_OBSERVER_K_EMF_INV_K_FILT          0x3C
#define TMC4672_OBSERVER_K_D	        	       0x3D
#define TMC4672_OBSERVER_E_SD	    	           0x3E
#define TMC4672_OBSERVER_E_SQ		               0x3F
#define TMC4672_OBSERVER_VELOCITY	               0x40
#define TMC4672_OBSERVER_PHI_E		               0x41

#define TMC4672_VELOCITY_SELECTION                 0x4A
#define TMC4672_POSITION_SELECTION                 0x4B
#define TMC4672_PHI_E_SELECTION                    0x4C
#define TMC4672_PHI_E                              0x4D

#define TMC4672_PID_FLUX_P_FLUX_I                  0x4E
#define TMC4672_PID_TORQUE_P_TORQUE_I              0x50
#define TMC4672_PID_VELOCITY_P_VELOCITY_I          0x54
#define TMC4672_PID_POSITION_P_POSITION_I          0x57
#define TMC4672_PID_TYPE						   0x58

#define TMC4672_PIDOUT_UQ_UD_LIMITS                0x59
#define TMC4672_PID_TORQUE_FLUX_LIMITS             0x5A
#define TMC4672_PID_ACCELERATION_LIMIT             0x5B
#define TMC4672_PID_VELOCITY_LIMIT                 0x5C
#define TMC4672_PID_POSITION_LIMIT_LOW             0x5D
#define TMC4672_PID_POSITION_LIMIT_HIGH            0x5E

#define TMC4672_MODE_RAMP_MODE_MOTION              0x5F
#define TMC4672_PID_TORQUE_FLUX_TARGET             0x60
#define TMC4672_PID_TORQUE_FLUX_OFFSET             0x61
#define TMC4672_PIDIN_TORQUE_FLUX_TARGET           0x62

#define TMC4672_PID_VELOCITY_TARGET                0x63
#define TMC4672_PID_VELOCITY_OFFSET                0x64
#define TMC4672_PIDIN_VELOCITY_TARGET			   0x65

#define TMC4672_PID_POSITION_TARGET                0x66
#define TMC4672_PID_TORQUE_FLUX_ACTUAL             0x67
#define TMC4672_PID_VELOCITY_ACTUAL                0x68
#define TMC4672_PID_POSITION_ACTUAL                0x69

#define TMC4672_PID_ERROR_DATA                     0x6C
#define TMC4672_PID_ERROR_ADDR                     0x6D
#define TMC4672_INTERIM_DATA                       0x6E
#define TMC4672_INTERIM_ADDR                       0x6F

#define TMC4672_WATCHDOG_CFG                       0x70
#define TMC4672_ADC_VM_LIMITS                      0x71
#define TMC4672_INPUTS_RAW                         0x72
#define TMC4672_OUTPUTS_RAW                        0x73
#define TMC4672_STEP_WIDTH                         0x74

#define TMC4672_UART_BPS                           0x75
#define TMC4672_UART_ADDRS                         0x76

#define TMC4672_GPIO_dsADCI_CONFIG                 0x77

#define TMC4672_STATUS_FLAGS                       0x78
#define TMC4672_STATUS_MASK                        0x79

// motion modes
#define TMC4672_MOTION_MODE_STOPPED    			0
#define TMC4672_MOTION_MODE_TORQUE     			1
#define TMC4672_MOTION_MODE_VELOCITY   			2
#define TMC4672_MOTION_MODE_POSITION   			3
#define TMC4672_MOTION_MODE_PRBS_FLUX			4
#define TMC4672_MOTION_MODE_PRBS_TORQUE			5
#define TMC4672_MOTION_MODE_PRBS_VELOCITY		6
#define TMC4672_MOTION_MODE_PRBS_POSITION 		7
#define TMC4672_MOTION_MODE_UQ_UD_EXT  			8
#define TMC4672_MOTION_MODE_PIN_TORQUE_MODE		9
#define TMC4672_MOTION_MODE_PIN_VELOCITY_MODE	10
#define TMC4672_MOTION_MODE_PIN_POSITION_MODE	11

#endif /* TMC4672_REGISTERS_H */
