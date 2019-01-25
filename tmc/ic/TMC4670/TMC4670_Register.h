/*
 * TMC4670_Register.h
 *
 *  Created on: 18.02.2016
 *      Author: ed
 */

#ifndef TMC4670_REGISTER_H
#define TMC4670_REGISTER_H

// ===== TMC4670 register set =====

	#define TMC4670_CHIPINFO_DATA                      0x00
	#define TMC4670_CHIPINFO_ADDR                      0x01

	#define TMC4670_ADC_RAW_DATA                       0x02
	#define TMC4670_ADC_RAW_ADDR                       0x03

	#define TMC4670_ADCSD_CLKCFG                       0x04
	#define TMC4670_ADC_I1_I0_EXT                      0x06
	#define TMC4670_ADC_I1_SCALE_OFFSET                0x08
	#define TMC4670_ADC_I0_SCALE_OFFSET                0x09
	#define TMC4670_ADC_I_SELECT                       0x0A

	#define TMC4670_AENC_0_SCALE_OFFSET                0x0D
	#define TMC4670_AENC_1_SCALE_OFFSET                0x0E
	#define TMC4670_AENC_2_SCALE_OFFSET                0x0F
	#define TMC4670_AENC_3_SCALE_OFFSET                0x10
	#define TMC4670_AENC_SELECT                        0x11

	#define TMC4670_ADC_IWY_IUX                        0x12
	#define TMC4670_ADC_IV                             0x13
	#define TMC4670_AENC_WY_UX                         0x15
	#define TMC4670_AENC_N_VN                          0x16

	#define TMC4670_PWM_POLARITIES                     0x17
	#define TMC4670_PWM_MAXCNT                         0x18
	#define TMC4670_PWM_BBM_H_BBM_L                    0x19
	#define TMC4670_PWM_SV_CHOP                        0x1A
	#define TMC4670_MOTOR_TYPE_N_POLE_PAIRS            0x1B

	#define TMC4670_PHI_E_EXT                          0x1C
	#define TMC4670_PHI_M_EXT                          0x1D
	#define TMC4670_POSITION_EXT                       0x1E
	#define TMC4670_OPENLOOP_MODE                      0x1F
	#define TMC4670_OPENLOOP_ACCELERATION              0x20
	#define TMC4670_OPENLOOP_VELOCITY_TARGET           0x21
	#define TMC4670_OPENLOOP_VELOCITY_ACTUAL           0x22
	#define TMC4670_OPENLOOP_PHI                       0x23
	#define TMC4670_UQ_UD_EXT                          0x24

	#define TMC4670_ABN_DECODER_MODE                   0x25
	#define TMC4670_ABN_DECODER_PPR                    0x26
	#define TMC4670_ABN_DECODER_COUNT                  0x27
	#define TMC4670_ABN_DECODER_COUNT_N                0x28
	#define TMC4670_ABN_DECODER_PHI_E_PHI_M_OFFSET     0x29
	#define TMC4670_ABN_DECODER_PHI_E_PHI_M            0x2A

	#define TMC4670_ABN_2_DECODER_MODE                 0x2C
	#define TMC4670_ABN_2_DECODER_PPR                  0x2D
	#define TMC4670_ABN_2_DECODER_COUNT                0x2E
	#define TMC4670_ABN_2_DECODER_COUNT_N              0x2F
	#define TMC4670_ABN_2_DECODER_PHI_M_OFFSET         0x30
	#define TMC4670_ABN_2_DECODER_PHI_M                0x31

	#define TMC4670_HALL_MODE                          0x33
	#define TMC4670_HALL_POSITION_060_000              0x34
	#define TMC4670_HALL_POSITION_180_120              0x35
	#define TMC4670_HALL_POSITION_300_240              0x36
	#define TMC4670_HALL_PHI_E_PHI_M_OFFSET            0x37
	#define TMC4670_HALL_DPHI_MAX                      0x38
	#define TMC4670_HALL_PHI_E_INTERPOLATED_PHI_E      0x39
	#define TMC4670_HALL_PHI_M                         0x3A

	#define TMC4670_AENC_DECODER_MODE                  0x3B
	#define TMC4670_AENC_DECODER_N_THRESHOLD           0x3C
	#define TMC4670_AENC_DECODER_PHI_A_RAW             0x3D
	#define TMC4670_AENC_DECODER_PHI_A_OFFSET          0x3E
	#define TMC4670_AENC_DECODER_PHI_A                 0x3F

	#define TMC4670_AENC_DECODER_PPR                   0x40
	#define TMC4670_AENC_DECODER_COUNT                 0x41
	#define TMC4670_AENC_DECODER_COUNT_N               0x42
	#define TMC4670_AENC_DECODER_COUNT_N_MASK          0x43
	#define TMC4670_AENC_DECODER_PHI_E_PHI_M_OFFSET    0x45
	#define TMC4670_AENC_DECODER_PHI_E_PHI_M           0x46
	#define TMC4670_AENC_DECODER_POSITION              0x47

	#define TMC4670_VELOCITY_SELECTION                 0x50
	#define TMC4670_POSITION_SELECTION                 0x51
	#define TMC4670_PHI_E_SELECTION                    0x52
	#define TMC4670_PHI_E                              0x53

	#define TMC4670_PID_FLUX_P_FLUX_I                  0x54
	#define TMC4670_PID_FLUX_D                         0x55
	#define TMC4670_PID_TORQUE_P_TORQUE_I              0x56
	#define TMC4670_PID_TORQUE_D                       0x57
	#define TMC4670_PID_VELOCITY_P_VELOCITY_I          0x58
	#define TMC4670_PID_VELOCITY_D                     0x59
	#define TMC4670_PID_POSITION_P_POSITION_I          0x5A
	#define TMC4670_PID_POSITION_D                     0x5B
	#define TMC4670_PID_TORQUE_FLUX_TARGET_DDT_LIMITS  0x5C
	#define TMC4670_PIDOUT_UQ_UD_LIMITS                0x5D
	#define TMC4670_PID_TORQUE_FLUX_LIMITS             0x5E
	#define TMC4670_PID_ACCELERATION_LIMIT             0x5F
	#define TMC4670_PID_VELOCITY_LIMIT                 0x60
	#define TMC4670_PID_POSITION_LIMIT_LOW             0x61
	#define TMC4670_PID_POSITION_LIMIT_HIGH            0x62

	#define TMC4670_MODE_RAMP_MODE_MOTION              0x63
	#define TMC4670_PID_TORQUE_FLUX_TARGET             0x64
	#define TMC4670_PID_TORQUE_FLUX_OFFSET             0x65
	#define TMC4670_PID_VELOCITY_TARGET                0x66
	#define TMC4670_PID_VELOCITY_OFFSET                0x67
	#define TMC4670_PID_POSITION_TARGET                0x68

	#define TMC4670_PID_TORQUE_FLUX_ACTUAL             0x69
	#define TMC4670_PID_VELOCITY_ACTUAL                0x6A
	#define TMC4670_PID_POSITION_ACTUAL                0x6B

	#define TMC4670_PID_ERROR_DATA                     0x6C
	#define TMC4670_PID_ERROR_ADDR                     0x6D
	#define TMC4670_INTERIM_DATA                       0x6E
	#define TMC4670_INTERIM_ADDR                       0x6F

	#define TMC4670_ADC_VM_LIMITS                      0x75
	#define TMC4670_INPUTS_RAW                         0x76
	#define TMC4670_OUTPUTS_RAW                        0x77

	#define TMC4670_STATUS_FLAGS                       0x7C

	#define TMC4670_WARNING_MASK                       0x7D
	#define TMC4670_ERROR_MASK                         0x7E

#endif /* TMC4670_REGISTER_H */
