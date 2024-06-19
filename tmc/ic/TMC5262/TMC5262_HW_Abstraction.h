/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC5262_HW_ABSTRACTION
#define TMC5262_HW_ABSTRACTION


//	Constants in TMC5262

#define TMC5262_REGISTER_COUNT   128
#define TMC5262_MOTORS           1
#define TMC5262_WRITE_BIT        0x80
#define TMC5262_ADDRESS_MASK     0x7F
#define TMC5262_MAX_VELOCITY     8388096
#define TMC5262_MAX_ACCELERATION 65535

// ramp modes (Register TMC5262_RAMPMODE)
#define TMC5262_MODE_POSITION  0
#define TMC5262_MODE_VELPOS    1
#define TMC5262_MODE_VELNEG    2
#define TMC5262_MODE_HOLD      3

// limit switch mode bits (Register TMC5262_SWMODE)
#define TMC5262_SW_STOPL_ENABLE    0x0001
#define TMC5262_SW_STOPR_ENABLE    0x0002
#define TMC5262_SW_STOPL_POLARITY  0x0004
#define TMC5262_SW_STOPR_POLARITY  0x0008
#define TMC5262_SW_SWAP_LR         0x0010
#define TMC5262_SW_LATCH_L_ACT     0x0020
#define TMC5262_SW_LATCH_L_INACT   0x0040
#define TMC5262_SW_LATCH_R_ACT     0x0080
#define TMC5262_SW_LATCH_R_INACT   0x0100
#define TMC5262_SW_LATCH_ENC       0x0200
#define TMC5262_SW_SG_STOP         0x0400
#define TMC5262_SW_SOFTSTOP        0x0800

// Status bits (Register TMC5262_RAMPSTAT)
#define TMC5262_RS_STOPL          0x0001
#define TMC5262_RS_STOPR          0x0002
#define TMC5262_RS_LATCHL         0x0004
#define TMC5262_RS_LATCHR         0x0008
#define TMC5262_RS_EV_STOPL       0x0010
#define TMC5262_RS_EV_STOPR       0x0020
#define TMC5262_RS_EV_STOP_SG     0x0040
#define TMC5262_RS_EV_POSREACHED  0x0080
#define TMC5262_RS_VELREACHED     0x0100
#define TMC5262_RS_POSREACHED     0x0200
#define TMC5262_RS_VZERO          0x0400
#define TMC5262_RS_ZEROWAIT       0x0800
#define TMC5262_RS_SECONDMOVE     0x1000
#define TMC5262_RS_SG             0x2000

// Encoderbits (Register TMC5262_ENCMODE)
#define TMC5262_EM_DECIMAL     0x0400
#define TMC5262_EM_LATCH_XACT  0x0200
#define TMC5262_EM_CLR_XENC    0x0100
#define TMC5262_EM_NEG_EDGE    0x0080
#define TMC5262_EM_POS_EDGE    0x0040
#define TMC5262_EM_CLR_ONCE    0x0020
#define TMC5262_EM_CLR_CONT    0x0010
#define TMC5262_EM_IGNORE_AB   0x0008
#define TMC5262_EM_POL_N       0x0004
#define TMC5262_EM_POL_B       0x0002
#define TMC5262_EM_POL_A       0x0001


// Registers in TMC5262

#define TMC5262_GCONF                      0x00
#define TMC5262_GSTAT                      0x01
#define TMC5262_DIAG_CONF                  0x02
#define TMC5262_DIAG_DAC_CONF              0x03
#define TMC5262_IOIN                       0x04
#define TMC5262_X_COMPARE                  0x05
#define TMC5262_X_COMPARE_REPEAT           0x06
#define TMC5262_DRV_CONF                   0x0A
#define TMC5262_PLL                        0x0B
#define TMC5262_IHOLD_IRUN                 0x10
#define TMC5262_TPOWERDOWN                 0x11
#define TMC5262_TSTEP                      0x12
#define TMC5262_TPWMTHRS                   0x13
#define TMC5262_TCOOLTHRS                  0x14
#define TMC5262_THIGH                      0x15
#define TMC5262_TSGP_LOW_VEL_THRS          0x16
#define TMC5262_T_RCOIL_MEAS               0x17
#define TMC5262_TUDCSTEP                   0x18
#define TMC5262_UDC_CONF                   0x19
#define TMC5262_STEPS_LOST                 0x1A
#define TMC5262_RAMPMODE                   0x20
#define TMC5262_XACTUAL                    0x21
#define TMC5262_VACTUAL                    0x22
#define TMC5262_VSTART                     0x23
#define TMC5262_A1                         0x24
#define TMC5262_V1                         0x25
#define TMC5262_AMAX                       0x26
#define TMC5262_VMAX                       0x27
#define TMC5262_DMAX                       0x28
#define TMC5262_TVMAX                      0x29
#define TMC5262_D1                         0x2A
#define TMC5262_VSTOP                      0x2B
#define TMC5262_TZEROWAIT                  0x2C
#define TMC5262_XTARGET                    0x2D
#define TMC5262_V2                         0x2E
#define TMC5262_A2                         0x2F
#define TMC5262_D2                         0x30
#define TMC5262_AACTUAL                    0x31
#define TMC5262_SW_MODE                    0x34
#define TMC5262_RAMP_STAT                  0x35
#define TMC5262_XLATCH                     0x36
#define TMC5262_ENCMODE                    0x38
#define TMC5262_X_ENC                      0x39
#define TMC5262_ENC_CONST                  0x3A
#define TMC5262_ENC_STATUS                 0x3B
#define TMC5262_ENC_LATCH                  0x3C
#define TMC5262_ENC_DEVIATION              0x3D
#define TMC5262_VIRTUAL_STOP_L             0x3E
#define TMC5262_VIRTUAL_STOP_R             0x3F
#define TMC5262_CURRENT_PI_REG             0x40
#define TMC5262_ANGLE_PI_REG               0x41
#define TMC5262_CUR_ANGLE_LIMIT            0x42
#define TMC5262_ANGLE_LOWER_LIMIT          0x43
#define TMC5262_CUR_ANGLE_MEAS             0x44
#define TMC5262_PI_RESULTS                 0x45
#define TMC5262_COIL_INDUCT                0x46
#define TMC5262_R_COIL                     0x47
#define TMC5262_R_COIL_USER                0x48
#define TMC5262_SGP_CONF                   0x49
#define TMC5262_SGP_IND_2_3                0x4A
#define TMC5262_SGP_IND_0_1                0x4B
#define TMC5262_INDUCTANCE_VOLTAGE         0x4C
#define TMC5262_SGP_BEMF                   0x4D
#define TMC5262_COOLSTEPPLUS_CONF          0x4E
#define TMC5262_COOLSTEPPLUS_PI_REG        0x4F
#define TMC5262_COOLSTEPPLUS_PI_DOWN       0x50
#define TMC5262_COOLSTEPPLUS_RESERVE_CONF  0x51
#define TMC5262_COOLSTEPPLUS_LOAD_RESERVE  0x52
#define TMC5262_TSTEP_VELOCITY             0x53
#define TMC5262_ADC_VSUPPLY_TEMP           0x58
#define TMC5262_ADC_I                      0x59
#define TMC5262_OTW_OV_VTH                 0x5A
#define TMC5262_MSLUT_0                    0x60
#define TMC5262_MSLUT_1                    0x61
#define TMC5262_MSLUT_2                    0x62
#define TMC5262_MSLUT_3                    0x63
#define TMC5262_MSLUT_4                    0x64
#define TMC5262_MSLUT_5                    0x65
#define TMC5262_MSLUT_6                    0x66
#define TMC5262_MSLUT_7                    0x67
#define TMC5262_MSLUTSEL                   0x68
#define TMC5262_MSLUTSTART                 0x69
#define TMC5262_MSCNT                      0x6A
#define TMC5262_MSCURACT                   0x6B
#define TMC5262_CHOPCONF                   0x6C
#define TMC5262_COOLCONF                   0x6D
#define TMC5262_DRV_STATUS                 0x6F
#define TMC5262_PWMCONF                    0x70


// Fields in TMC5262

#define TMC5262_FAST_STANDSTILL_MASK                0x00000001
#define TMC5262_FAST_STANDSTILL_SHIFT               0
#define TMC5262_FAST_STANDSTILL_FIELD               ((RegisterField) {TMC5262_FAST_STANDSTILL_MASK, TMC5262_FAST_STANDSTILL_SHIFT, TMC5262_GCONF, false})
#define TMC5262_EN_STEALTHCHOP_MASK                 0x00000002
#define TMC5262_EN_STEALTHCHOP_SHIFT                1
#define TMC5262_EN_STEALTHCHOP_FIELD                ((RegisterField) {TMC5262_EN_STEALTHCHOP_MASK, TMC5262_EN_STEALTHCHOP_SHIFT, TMC5262_GCONF, false})
#define TMC5262_MULTISTEP_FILT_MASK                 0x00000004
#define TMC5262_MULTISTEP_FILT_SHIFT                2
#define TMC5262_MULTISTEP_FILT_FIELD                ((RegisterField) {TMC5262_MULTISTEP_FILT_MASK, TMC5262_MULTISTEP_FILT_SHIFT, TMC5262_GCONF, false})
#define TMC5262_SHAFT_MASK                          0x00000008
#define TMC5262_SHAFT_SHIFT                         3
#define TMC5262_SHAFT_FIELD                         ((RegisterField) {TMC5262_SHAFT_MASK, TMC5262_SHAFT_SHIFT, TMC5262_GCONF, false})
#define TMC5262_SMALL_HYSTERESIS_MASK               0x00000010
#define TMC5262_SMALL_HYSTERESIS_SHIFT              4
#define TMC5262_SMALL_HYSTERESIS_FIELD              ((RegisterField) {TMC5262_SMALL_HYSTERESIS_MASK, TMC5262_SMALL_HYSTERESIS_SHIFT, TMC5262_GCONF, false})
#define TMC5262_STOP_ENABLE_MASK                    0x00000020
#define TMC5262_STOP_ENABLE_SHIFT                   5
#define TMC5262_STOP_ENABLE_FIELD                   ((RegisterField) {TMC5262_STOP_ENABLE_MASK, TMC5262_STOP_ENABLE_SHIFT, TMC5262_GCONF, false})
#define TMC5262_DIRECT_MODE_MASK                    0x00000040
#define TMC5262_DIRECT_MODE_SHIFT                   6
#define TMC5262_DIRECT_MODE_FIELD                   ((RegisterField) {TMC5262_DIRECT_MODE_MASK, TMC5262_DIRECT_MODE_SHIFT, TMC5262_GCONF, false})
#define TMC5262_LENGTH_STEPPULSE_MASK               0x00000F00
#define TMC5262_LENGTH_STEPPULSE_SHIFT              8
#define TMC5262_LENGTH_STEPPULSE_FIELD              ((RegisterField) {TMC5262_LENGTH_STEPPULSE_MASK, TMC5262_LENGTH_STEPPULSE_SHIFT, TMC5262_GCONF, false})
#define TMC5262_OV_NN_MASK                          0x00001000
#define TMC5262_OV_NN_SHIFT                         12
#define TMC5262_OV_NN_FIELD                         ((RegisterField) {TMC5262_OV_NN_MASK, TMC5262_OV_NN_SHIFT, TMC5262_GCONF, false})
#define TMC5262_THREEPHASE_MCC_MASK                 0x40000000
#define TMC5262_THREEPHASE_MCC_SHIFT                30
#define TMC5262_THREEPHASE_MCC_FIELD                ((RegisterField) {TMC5262_THREEPHASE_MCC_MASK, TMC5262_THREEPHASE_MCC_SHIFT, TMC5262_GCONF, false})
#define TMC5262_STEP_DIR_MASK                       0x80000000
#define TMC5262_STEP_DIR_SHIFT                      31
#define TMC5262_STEP_DIR_FIELD                      ((RegisterField) {TMC5262_STEP_DIR_MASK, TMC5262_STEP_DIR_SHIFT, TMC5262_GCONF, false})
#define TMC5262_RESET_MASK                          0x00000001
#define TMC5262_RESET_SHIFT                         0
#define TMC5262_RESET_FIELD                         ((RegisterField) {TMC5262_RESET_MASK, TMC5262_RESET_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_DRV_ERR_MASK                        0x00000002
#define TMC5262_DRV_ERR_SHIFT                       1
#define TMC5262_DRV_ERR_FIELD                       ((RegisterField) {TMC5262_DRV_ERR_MASK, TMC5262_DRV_ERR_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_UV_CP_MASK                          0x00000004
#define TMC5262_UV_CP_SHIFT                         2
#define TMC5262_UV_CP_FIELD                         ((RegisterField) {TMC5262_UV_CP_MASK, TMC5262_UV_CP_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_REGISTER_RESET_MASK                 0x00000008
#define TMC5262_REGISTER_RESET_SHIFT                3
#define TMC5262_REGISTER_RESET_FIELD                ((RegisterField) {TMC5262_REGISTER_RESET_MASK, TMC5262_REGISTER_RESET_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_VM_UVLO_MASK                        0x00000010
#define TMC5262_VM_UVLO_SHIFT                       4
#define TMC5262_VM_UVLO_FIELD                       ((RegisterField) {TMC5262_VM_UVLO_MASK, TMC5262_VM_UVLO_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_VCCIO_UV_MASK                       0x00000020
#define TMC5262_VCCIO_UV_SHIFT                      5
#define TMC5262_VCCIO_UV_FIELD                      ((RegisterField) {TMC5262_VCCIO_UV_MASK, TMC5262_VCCIO_UV_SHIFT, TMC5262_GSTAT, false})
#define TMC5262_DIAG0_ERROR_MASK                    0x00000001
#define TMC5262_DIAG0_ERROR_SHIFT                   0
#define TMC5262_DIAG0_ERROR_FIELD                   ((RegisterField) {TMC5262_DIAG0_ERROR_MASK, TMC5262_DIAG0_ERROR_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_OTPW_MASK                     0x00000002
#define TMC5262_DIAG0_OTPW_SHIFT                    1
#define TMC5262_DIAG0_OTPW_FIELD                    ((RegisterField) {TMC5262_DIAG0_OTPW_MASK, TMC5262_DIAG0_OTPW_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_STALL_MASK                    0x00000004
#define TMC5262_DIAG0_STALL_SHIFT                   2
#define TMC5262_DIAG0_STALL_FIELD                   ((RegisterField) {TMC5262_DIAG0_STALL_MASK, TMC5262_DIAG0_STALL_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_INDEX_MASK                    0x00000008
#define TMC5262_DIAG0_INDEX_SHIFT                   3
#define TMC5262_DIAG0_INDEX_FIELD                   ((RegisterField) {TMC5262_DIAG0_INDEX_MASK, TMC5262_DIAG0_INDEX_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_STEP_MASK                     0x00000010
#define TMC5262_DIAG0_STEP_SHIFT                    4
#define TMC5262_DIAG0_STEP_FIELD                    ((RegisterField) {TMC5262_DIAG0_STEP_MASK, TMC5262_DIAG0_STEP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_DIR_MASK                      0x00000020
#define TMC5262_DIAG0_DIR_SHIFT                     5
#define TMC5262_DIAG0_DIR_FIELD                     ((RegisterField) {TMC5262_DIAG0_DIR_MASK, TMC5262_DIAG0_DIR_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_XCOMP_MASK                    0x00000040
#define TMC5262_DIAG0_XCOMP_SHIFT                   6
#define TMC5262_DIAG0_XCOMP_FIELD                   ((RegisterField) {TMC5262_DIAG0_XCOMP_MASK, TMC5262_DIAG0_XCOMP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_OV_MASK                       0x00000080
#define TMC5262_DIAG0_OV_SHIFT                      7
#define TMC5262_DIAG0_OV_FIELD                      ((RegisterField) {TMC5262_DIAG0_OV_MASK, TMC5262_DIAG0_OV_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_DCUSTEP_MASK                  0x00000100
#define TMC5262_DIAG0_DCUSTEP_SHIFT                 8
#define TMC5262_DIAG0_DCUSTEP_FIELD                 ((RegisterField) {TMC5262_DIAG0_DCUSTEP_MASK, TMC5262_DIAG0_DCUSTEP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_EV_STOP_REF_MASK              0x00000200
#define TMC5262_DIAG0_EV_STOP_REF_SHIFT             9
#define TMC5262_DIAG0_EV_STOP_REF_FIELD             ((RegisterField) {TMC5262_DIAG0_EV_STOP_REF_MASK, TMC5262_DIAG0_EV_STOP_REF_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_EV_STOP_SG_MASK               0x00000400
#define TMC5262_DIAG0_EV_STOP_SG_SHIFT              10
#define TMC5262_DIAG0_EV_STOP_SG_FIELD              ((RegisterField) {TMC5262_DIAG0_EV_STOP_SG_MASK, TMC5262_DIAG0_EV_STOP_SG_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_EV_POS_REACHED_MASK           0x00000800
#define TMC5262_DIAG0_EV_POS_REACHED_SHIFT          11
#define TMC5262_DIAG0_EV_POS_REACHED_FIELD          ((RegisterField) {TMC5262_DIAG0_EV_POS_REACHED_MASK, TMC5262_DIAG0_EV_POS_REACHED_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_EV_N_DEVIATION_MASK           0x00001000
#define TMC5262_DIAG0_EV_N_DEVIATION_SHIFT          12
#define TMC5262_DIAG0_EV_N_DEVIATION_FIELD          ((RegisterField) {TMC5262_DIAG0_EV_N_DEVIATION_MASK, TMC5262_DIAG0_EV_N_DEVIATION_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_ERROR_MASK                    0x00002000
#define TMC5262_DIAG1_ERROR_SHIFT                   13
#define TMC5262_DIAG1_ERROR_FIELD                   ((RegisterField) {TMC5262_DIAG1_ERROR_MASK, TMC5262_DIAG1_ERROR_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_OTPW_MASK                     0x00004000
#define TMC5262_DIAG1_OTPW_SHIFT                    14
#define TMC5262_DIAG1_OTPW_FIELD                    ((RegisterField) {TMC5262_DIAG1_OTPW_MASK, TMC5262_DIAG1_OTPW_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_STALL_MASK                    0x00008000
#define TMC5262_DIAG1_STALL_SHIFT                   15
#define TMC5262_DIAG1_STALL_FIELD                   ((RegisterField) {TMC5262_DIAG1_STALL_MASK, TMC5262_DIAG1_STALL_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_INDEX_MASK                    0x00010000
#define TMC5262_DIAG1_INDEX_SHIFT                   16
#define TMC5262_DIAG1_INDEX_FIELD                   ((RegisterField) {TMC5262_DIAG1_INDEX_MASK, TMC5262_DIAG1_INDEX_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_STEP_MASK                     0x00020000
#define TMC5262_DIAG1_STEP_SHIFT                    17
#define TMC5262_DIAG1_STEP_FIELD                    ((RegisterField) {TMC5262_DIAG1_STEP_MASK, TMC5262_DIAG1_STEP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_DIR_MASK                      0x00040000
#define TMC5262_DIAG1_DIR_SHIFT                     18
#define TMC5262_DIAG1_DIR_FIELD                     ((RegisterField) {TMC5262_DIAG1_DIR_MASK, TMC5262_DIAG1_DIR_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_XCOMP_MASK                    0x00080000
#define TMC5262_DIAG1_XCOMP_SHIFT                   19
#define TMC5262_DIAG1_XCOMP_FIELD                   ((RegisterField) {TMC5262_DIAG1_XCOMP_MASK, TMC5262_DIAG1_XCOMP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_OV_MASK                       0x00100000
#define TMC5262_DIAG1_OV_SHIFT                      20
#define TMC5262_DIAG1_OV_FIELD                      ((RegisterField) {TMC5262_DIAG1_OV_MASK, TMC5262_DIAG1_OV_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_UDCSTEP_MASK                  0x00200000
#define TMC5262_DIAG1_UDCSTEP_SHIFT                 21
#define TMC5262_DIAG1_UDCSTEP_FIELD                 ((RegisterField) {TMC5262_DIAG1_UDCSTEP_MASK, TMC5262_DIAG1_UDCSTEP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_EV_STOP_REF_MASK              0x00400000
#define TMC5262_DIAG1_EV_STOP_REF_SHIFT             22
#define TMC5262_DIAG1_EV_STOP_REF_FIELD             ((RegisterField) {TMC5262_DIAG1_EV_STOP_REF_MASK, TMC5262_DIAG1_EV_STOP_REF_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_EV_STOP_SG_MASK               0x00800000
#define TMC5262_DIAG1_EV_STOP_SG_SHIFT              23
#define TMC5262_DIAG1_EV_STOP_SG_FIELD              ((RegisterField) {TMC5262_DIAG1_EV_STOP_SG_MASK, TMC5262_DIAG1_EV_STOP_SG_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_EV_POS_REACHED_MASK           0x01000000
#define TMC5262_DIAG1_EV_POS_REACHED_SHIFT          24
#define TMC5262_DIAG1_EV_POS_REACHED_FIELD          ((RegisterField) {TMC5262_DIAG1_EV_POS_REACHED_MASK, TMC5262_DIAG1_EV_POS_REACHED_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_EV_N_DEVIATION_MASK           0x02000000
#define TMC5262_DIAG1_EV_N_DEVIATION_SHIFT          25
#define TMC5262_DIAG1_EV_N_DEVIATION_FIELD          ((RegisterField) {TMC5262_DIAG1_EV_N_DEVIATION_MASK, TMC5262_DIAG1_EV_N_DEVIATION_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_NOD_PP_MASK                   0x10000000
#define TMC5262_DIAG0_NOD_PP_SHIFT                  28
#define TMC5262_DIAG0_NOD_PP_FIELD                  ((RegisterField) {TMC5262_DIAG0_NOD_PP_MASK, TMC5262_DIAG0_NOD_PP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_INVPP_MASK                    0x20000000
#define TMC5262_DIAG0_INVPP_SHIFT                   29
#define TMC5262_DIAG0_INVPP_FIELD                   ((RegisterField) {TMC5262_DIAG0_INVPP_MASK, TMC5262_DIAG0_INVPP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_NOD_PP_MASK                   0x40000000
#define TMC5262_DIAG1_NOD_PP_SHIFT                  30
#define TMC5262_DIAG1_NOD_PP_FIELD                  ((RegisterField) {TMC5262_DIAG1_NOD_PP_MASK, TMC5262_DIAG1_NOD_PP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG1_INVPP_MASK                    0x80000000
#define TMC5262_DIAG1_INVPP_SHIFT                   31
#define TMC5262_DIAG1_INVPP_FIELD                   ((RegisterField) {TMC5262_DIAG1_INVPP_MASK, TMC5262_DIAG1_INVPP_SHIFT, TMC5262_DIAG_CONF, false})
#define TMC5262_DIAG0_DAC_EN_MASK                   0x00000001
#define TMC5262_DIAG0_DAC_EN_SHIFT                  0
#define TMC5262_DIAG0_DAC_EN_FIELD                  ((RegisterField) {TMC5262_DIAG0_DAC_EN_MASK, TMC5262_DIAG0_DAC_EN_SHIFT, TMC5262_DIAG_DAC_CONF, false})
#define TMC5262_DIAG0_DAC_SEL_MASK                  0x000001F0
#define TMC5262_DIAG0_DAC_SEL_SHIFT                 4
#define TMC5262_DIAG0_DAC_SEL_FIELD                 ((RegisterField) {TMC5262_DIAG0_DAC_SEL_MASK, TMC5262_DIAG0_DAC_SEL_SHIFT, TMC5262_DIAG_DAC_CONF, false})
#define TMC5262_DIAG1_DAC_EN_MASK                   0x00001000
#define TMC5262_DIAG1_DAC_EN_SHIFT                  12
#define TMC5262_DIAG1_DAC_EN_FIELD                  ((RegisterField) {TMC5262_DIAG1_DAC_EN_MASK, TMC5262_DIAG1_DAC_EN_SHIFT, TMC5262_DIAG_DAC_CONF, false})
#define TMC5262_DIAG1_DAC_SEL_MASK                  0x001F0000
#define TMC5262_DIAG1_DAC_SEL_SHIFT                 16
#define TMC5262_DIAG1_DAC_SEL_FIELD                 ((RegisterField) {TMC5262_DIAG1_DAC_SEL_MASK, TMC5262_DIAG1_DAC_SEL_SHIFT, TMC5262_DIAG_DAC_CONF, false})
#define TMC5262_REFL_MASK                           0x00000001
#define TMC5262_REFL_SHIFT                          0
#define TMC5262_REFL_FIELD                          ((RegisterField) {TMC5262_REFL_MASK, TMC5262_REFL_SHIFT, TMC5262_IOIN, false})
#define TMC5262_REFR_MASK                           0x00000002
#define TMC5262_REFR_SHIFT                          1
#define TMC5262_REFR_FIELD                          ((RegisterField) {TMC5262_REFR_MASK, TMC5262_REFR_SHIFT, TMC5262_IOIN, false})
#define TMC5262_ENCB_MASK                           0x00000004
#define TMC5262_ENCB_SHIFT                          2
#define TMC5262_ENCB_FIELD                          ((RegisterField) {TMC5262_ENCB_MASK, TMC5262_ENCB_SHIFT, TMC5262_IOIN, false})
#define TMC5262_ENCA_MASK                           0x00000008
#define TMC5262_ENCA_SHIFT                          3
#define TMC5262_ENCA_FIELD                          ((RegisterField) {TMC5262_ENCA_MASK, TMC5262_ENCA_SHIFT, TMC5262_IOIN, false})
#define TMC5262_DRV_ENN_MASK                        0x00000010
#define TMC5262_DRV_ENN_SHIFT                       4
#define TMC5262_DRV_ENN_FIELD                       ((RegisterField) {TMC5262_DRV_ENN_MASK, TMC5262_DRV_ENN_SHIFT, TMC5262_IOIN, false})
#define TMC5262_ENCN_MASK                           0x00000020
#define TMC5262_ENCN_SHIFT                          5
#define TMC5262_ENCN_FIELD                          ((RegisterField) {TMC5262_ENCN_MASK, TMC5262_ENCN_SHIFT, TMC5262_IOIN, false})
#define TMC5262_RESERVED_MASK                       0x00000080
#define TMC5262_RESERVED_SHIFT                      7
#define TMC5262_RESERVED_FIELD                      ((RegisterField) {TMC5262_RESERVED_MASK, TMC5262_RESERVED_SHIFT, TMC5262_IOIN, false})
#define TMC5262_EXT_RES_DET_MASK                    0x00002000
#define TMC5262_EXT_RES_DET_SHIFT                   13
#define TMC5262_EXT_RES_DET_FIELD                   ((RegisterField) {TMC5262_EXT_RES_DET_MASK, TMC5262_EXT_RES_DET_SHIFT, TMC5262_IOIN, false})
#define TMC5262_EXT_CLK_MASK                        0x00004000
#define TMC5262_EXT_CLK_SHIFT                       14
#define TMC5262_EXT_CLK_FIELD                       ((RegisterField) {TMC5262_EXT_CLK_MASK, TMC5262_EXT_CLK_SHIFT, TMC5262_IOIN, false})
#define TMC5262_SILICON_RV_MASK                     0x00070000
#define TMC5262_SILICON_RV_SHIFT                    16
#define TMC5262_SILICON_RV_FIELD                    ((RegisterField) {TMC5262_SILICON_RV_MASK, TMC5262_SILICON_RV_SHIFT, TMC5262_IOIN, false})
#define TMC5262_VERSION_MASK                        0xFF000000
#define TMC5262_VERSION_SHIFT                       24
#define TMC5262_VERSION_FIELD                       ((RegisterField) {TMC5262_VERSION_MASK, TMC5262_VERSION_SHIFT, TMC5262_IOIN, false})
#define TMC5262_X_COMPARE_MASK                      0xFFFFFFFF
#define TMC5262_X_COMPARE_SHIFT                     0
#define TMC5262_X_COMPARE_FIELD                     ((RegisterField) {TMC5262_X_COMPARE_MASK, TMC5262_X_COMPARE_SHIFT, TMC5262_X_COMPARE, true})
#define TMC5262_X_COMPARE_REPEAT_MASK               0x00FFFFFF
#define TMC5262_X_COMPARE_REPEAT_SHIFT              0
#define TMC5262_X_COMPARE_REPEAT_FIELD              ((RegisterField) {TMC5262_X_COMPARE_REPEAT_MASK, TMC5262_X_COMPARE_REPEAT_SHIFT, TMC5262_X_COMPARE_REPEAT, false})
#define TMC5262_CURRENT_RANGE_MASK                  0x00000003
#define TMC5262_CURRENT_RANGE_SHIFT                 0
#define TMC5262_CURRENT_RANGE_FIELD                 ((RegisterField) {TMC5262_CURRENT_RANGE_MASK, TMC5262_CURRENT_RANGE_SHIFT, TMC5262_DRV_CONF, false})
#define TMC5262_CURRENT_RANGE_SCALE_MASK            0x0000000C
#define TMC5262_CURRENT_RANGE_SCALE_SHIFT           2
#define TMC5262_CURRENT_RANGE_SCALE_FIELD           ((RegisterField) {TMC5262_CURRENT_RANGE_SCALE_MASK, TMC5262_CURRENT_RANGE_SCALE_SHIFT, TMC5262_DRV_CONF, false})
#define TMC5262_SLOPE_CONTROL_MASK                  0x00000030
#define TMC5262_SLOPE_CONTROL_SHIFT                 4
#define TMC5262_SLOPE_CONTROL_FIELD                 ((RegisterField) {TMC5262_SLOPE_CONTROL_MASK, TMC5262_SLOPE_CONTROL_SHIFT, TMC5262_DRV_CONF, false})
#define TMC5262_COMMIT_MASK                         0x00000001
#define TMC5262_COMMIT_SHIFT                        0
#define TMC5262_COMMIT_FIELD                        ((RegisterField) {TMC5262_COMMIT_MASK, TMC5262_COMMIT_SHIFT, TMC5262_PLL, false})
#define TMC5262_EXT_NOT_INT_MASK                    0x00000002
#define TMC5262_EXT_NOT_INT_SHIFT                   1
#define TMC5262_EXT_NOT_INT_FIELD                   ((RegisterField) {TMC5262_EXT_NOT_INT_MASK, TMC5262_EXT_NOT_INT_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLK_SYS_SEL_MASK                    0x00000004
#define TMC5262_CLK_SYS_SEL_SHIFT                   2
#define TMC5262_CLK_SYS_SEL_FIELD                   ((RegisterField) {TMC5262_CLK_SYS_SEL_MASK, TMC5262_CLK_SYS_SEL_SHIFT, TMC5262_PLL, false})
#define TMC5262_ADC_CLK_ENA_MASK                    0x00000008
#define TMC5262_ADC_CLK_ENA_SHIFT                   3
#define TMC5262_ADC_CLK_ENA_FIELD                   ((RegisterField) {TMC5262_ADC_CLK_ENA_MASK, TMC5262_ADC_CLK_ENA_SHIFT, TMC5262_PLL, false})
#define TMC5262_PWM_CLK_ENA_MASK                    0x00000010
#define TMC5262_PWM_CLK_ENA_SHIFT                   4
#define TMC5262_PWM_CLK_ENA_FIELD                   ((RegisterField) {TMC5262_PWM_CLK_ENA_MASK, TMC5262_PWM_CLK_ENA_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLOCK_DIVIDER_MASK                  0x000003E0
#define TMC5262_CLOCK_DIVIDER_SHIFT                 5
#define TMC5262_CLOCK_DIVIDER_FIELD                 ((RegisterField) {TMC5262_CLOCK_DIVIDER_MASK, TMC5262_CLOCK_DIVIDER_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLK_FSM_ENA_MASK                    0x00000400
#define TMC5262_CLK_FSM_ENA_SHIFT                   10
#define TMC5262_CLK_FSM_ENA_FIELD                   ((RegisterField) {TMC5262_CLK_FSM_ENA_MASK, TMC5262_CLK_FSM_ENA_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLK_1MO_TMO_MASK                    0x00001000
#define TMC5262_CLK_1MO_TMO_SHIFT                   12
#define TMC5262_CLK_1MO_TMO_FIELD                   ((RegisterField) {TMC5262_CLK_1MO_TMO_MASK, TMC5262_CLK_1MO_TMO_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLK_LOSS_MASK                       0x00002000
#define TMC5262_CLK_LOSS_SHIFT                      13
#define TMC5262_CLK_LOSS_FIELD                      ((RegisterField) {TMC5262_CLK_LOSS_MASK, TMC5262_CLK_LOSS_SHIFT, TMC5262_PLL, false})
#define TMC5262_CLK_IS_STUCK_MASK                   0x00004000
#define TMC5262_CLK_IS_STUCK_SHIFT                  14
#define TMC5262_CLK_IS_STUCK_FIELD                  ((RegisterField) {TMC5262_CLK_IS_STUCK_MASK, TMC5262_CLK_IS_STUCK_SHIFT, TMC5262_PLL, false})
#define TMC5262_PLL_LOCK_LOSS_MASK                  0x00008000
#define TMC5262_PLL_LOCK_LOSS_SHIFT                 15
#define TMC5262_PLL_LOCK_LOSS_FIELD                 ((RegisterField) {TMC5262_PLL_LOCK_LOSS_MASK, TMC5262_PLL_LOCK_LOSS_SHIFT, TMC5262_PLL, false})
#define TMC5262_IHOLD_MASK                          0x000000FF
#define TMC5262_IHOLD_SHIFT                         0
#define TMC5262_IHOLD_FIELD                         ((RegisterField) {TMC5262_IHOLD_MASK, TMC5262_IHOLD_SHIFT, TMC5262_IHOLD_IRUN, false})
#define TMC5262_IRUN_MASK                           0x0000FF00
#define TMC5262_IRUN_SHIFT                          8
#define TMC5262_IRUN_FIELD                          ((RegisterField) {TMC5262_IRUN_MASK, TMC5262_IRUN_SHIFT, TMC5262_IHOLD_IRUN, false})
#define TMC5262_IHOLDDELAY_MASK                     0x00FF0000
#define TMC5262_IHOLDDELAY_SHIFT                    16
#define TMC5262_IHOLDDELAY_FIELD                    ((RegisterField) {TMC5262_IHOLDDELAY_MASK, TMC5262_IHOLDDELAY_SHIFT, TMC5262_IHOLD_IRUN, false})
#define TMC5262_IRUNDELAY_MASK                      0x0F000000
#define TMC5262_IRUNDELAY_SHIFT                     24
#define TMC5262_IRUNDELAY_FIELD                     ((RegisterField) {TMC5262_IRUNDELAY_MASK, TMC5262_IRUNDELAY_SHIFT, TMC5262_IHOLD_IRUN, false})
#define TMC5262_TPOWERDOWN_MASK                     0x000000FF
#define TMC5262_TPOWERDOWN_SHIFT                    0
#define TMC5262_TPOWERDOWN_FIELD                    ((RegisterField) {TMC5262_TPOWERDOWN_MASK, TMC5262_TPOWERDOWN_SHIFT, TMC5262_TPOWERDOWN, false})
#define TMC5262_TSTEP_MASK                          0x000FFFFF
#define TMC5262_TSTEP_SHIFT                         0
#define TMC5262_TSTEP_FIELD                         ((RegisterField) {TMC5262_TSTEP_MASK, TMC5262_TSTEP_SHIFT, TMC5262_TSTEP, false})
#define TMC5262_TPWMTHRS_MASK                       0x000FFFFF
#define TMC5262_TPWMTHRS_SHIFT                      0
#define TMC5262_TPWMTHRS_FIELD                      ((RegisterField) {TMC5262_TPWMTHRS_MASK, TMC5262_TPWMTHRS_SHIFT, TMC5262_TPWMTHRS, false})
#define TMC5262_TCOOLTHRS_MASK                      0x000FFFFF
#define TMC5262_TCOOLTHRS_SHIFT                     0
#define TMC5262_TCOOLTHRS_FIELD                     ((RegisterField) {TMC5262_TCOOLTHRS_MASK, TMC5262_TCOOLTHRS_SHIFT, TMC5262_TCOOLTHRS, false})
#define TMC5262_THIGH_MASK                          0x000FFFFF
#define TMC5262_THIGH_SHIFT                         0
#define TMC5262_THIGH_FIELD                         ((RegisterField) {TMC5262_THIGH_MASK, TMC5262_THIGH_SHIFT, TMC5262_THIGH, false})
#define TMC5262_TSGP_LOW_VEL_THRS_MASK              0x000FFFFF
#define TMC5262_TSGP_LOW_VEL_THRS_SHIFT             0
#define TMC5262_TSGP_LOW_VEL_THRS_FIELD             ((RegisterField) {TMC5262_TSGP_LOW_VEL_THRS_MASK, TMC5262_TSGP_LOW_VEL_THRS_SHIFT, TMC5262_TSGP_LOW_VEL_THRS, false})
#define TMC5262_T_RCOIL_MEAS_MASK                   0x000FFFFF
#define TMC5262_T_RCOIL_MEAS_SHIFT                  0
#define TMC5262_T_RCOIL_MEAS_FIELD                  ((RegisterField) {TMC5262_T_RCOIL_MEAS_MASK, TMC5262_T_RCOIL_MEAS_SHIFT, TMC5262_T_RCOIL_MEAS, false})
#define TMC5262_TUDCSTEP_MASK                       0x000FFFFF
#define TMC5262_TUDCSTEP_SHIFT                      0
#define TMC5262_TUDCSTEP_FIELD                      ((RegisterField) {TMC5262_TUDCSTEP_MASK, TMC5262_TUDCSTEP_SHIFT, TMC5262_TUDCSTEP, false})
#define TMC5262_DECEL_THRS_MASK                     0x0000000F
#define TMC5262_DECEL_THRS_SHIFT                    0
#define TMC5262_DECEL_THRS_FIELD                    ((RegisterField) {TMC5262_DECEL_THRS_MASK, TMC5262_DECEL_THRS_SHIFT, TMC5262_UDC_CONF, false})
#define TMC5262_ACCEL_THRS_MASK                     0x000000F0
#define TMC5262_ACCEL_THRS_SHIFT                    4
#define TMC5262_ACCEL_THRS_FIELD                    ((RegisterField) {TMC5262_ACCEL_THRS_MASK, TMC5262_ACCEL_THRS_SHIFT, TMC5262_UDC_CONF, false})
#define TMC5262_UDC_ENABLE_MASK                     0x00000100
#define TMC5262_UDC_ENABLE_SHIFT                    8
#define TMC5262_UDC_ENABLE_FIELD                    ((RegisterField) {TMC5262_UDC_ENABLE_MASK, TMC5262_UDC_ENABLE_SHIFT, TMC5262_UDC_CONF, false})
#define TMC5262_STEPS_LOST_MASK                     0x000FFFFF
#define TMC5262_STEPS_LOST_SHIFT                    0
#define TMC5262_STEPS_LOST_FIELD                    ((RegisterField) {TMC5262_STEPS_LOST_MASK, TMC5262_STEPS_LOST_SHIFT, TMC5262_STEPS_LOST, true})
#define TMC5262_RAMPMODE_MASK                       0x00000003
#define TMC5262_RAMPMODE_SHIFT                      0
#define TMC5262_RAMPMODE_FIELD                      ((RegisterField) {TMC5262_RAMPMODE_MASK, TMC5262_RAMPMODE_SHIFT, TMC5262_RAMPMODE, false})
#define TMC5262_XACTUAL_MASK                        0xFFFFFFFF
#define TMC5262_XACTUAL_SHIFT                       0
#define TMC5262_XACTUAL_FIELD                       ((RegisterField) {TMC5262_XACTUAL_MASK, TMC5262_XACTUAL_SHIFT, TMC5262_XACTUAL, true})
#define TMC5262_VACTUAL_MASK                        0x00FFFFFF
#define TMC5262_VACTUAL_SHIFT                       0
#define TMC5262_VACTUAL_FIELD                       ((RegisterField) {TMC5262_VACTUAL_MASK, TMC5262_VACTUAL_SHIFT, TMC5262_VACTUAL, true})
#define TMC5262_VSTART_MASK                         0x0003FFFF
#define TMC5262_VSTART_SHIFT                        0
#define TMC5262_VSTART_FIELD                        ((RegisterField) {TMC5262_VSTART_MASK, TMC5262_VSTART_SHIFT, TMC5262_VSTART, false})
#define TMC5262_A1_MASK                             0x0003FFFF
#define TMC5262_A1_SHIFT                            0
#define TMC5262_A1_FIELD                            ((RegisterField) {TMC5262_A1_MASK, TMC5262_A1_SHIFT, TMC5262_A1, false})
#define TMC5262_V1_MASK                             0x000FFFFF
#define TMC5262_V1_SHIFT                            0
#define TMC5262_V1_FIELD                            ((RegisterField) {TMC5262_V1_MASK, TMC5262_V1_SHIFT, TMC5262_V1, false})
#define TMC5262_AMAX_MASK                           0x0003FFFF
#define TMC5262_AMAX_SHIFT                          0
#define TMC5262_AMAX_FIELD                          ((RegisterField) {TMC5262_AMAX_MASK, TMC5262_AMAX_SHIFT, TMC5262_AMAX, false})
#define TMC5262_VMAX_MASK                           0x007FFFFF
#define TMC5262_VMAX_SHIFT                          0
#define TMC5262_VMAX_FIELD                          ((RegisterField) {TMC5262_VMAX_MASK, TMC5262_VMAX_SHIFT, TMC5262_VMAX, false})
#define TMC5262_DMAX_MASK                           0x0003FFFF
#define TMC5262_DMAX_SHIFT                          0
#define TMC5262_DMAX_FIELD                          ((RegisterField) {TMC5262_DMAX_MASK, TMC5262_DMAX_SHIFT, TMC5262_DMAX, false})
#define TMC5262_TVMAX_MASK                          0x0000FFFF
#define TMC5262_TVMAX_SHIFT                         0
#define TMC5262_TVMAX_FIELD                         ((RegisterField) {TMC5262_TVMAX_MASK, TMC5262_TVMAX_SHIFT, TMC5262_TVMAX, false})
#define TMC5262_D1_MASK                             0x0003FFFF
#define TMC5262_D1_SHIFT                            0
#define TMC5262_D1_FIELD                            ((RegisterField) {TMC5262_D1_MASK, TMC5262_D1_SHIFT, TMC5262_D1, false})
#define TMC5262_VSTOP_MASK                          0x0003FFFF
#define TMC5262_VSTOP_SHIFT                         0
#define TMC5262_VSTOP_FIELD                         ((RegisterField) {TMC5262_VSTOP_MASK, TMC5262_VSTOP_SHIFT, TMC5262_VSTOP, false})
#define TMC5262_TZEROWAIT_MASK                      0x0000FFFF
#define TMC5262_TZEROWAIT_SHIFT                     0
#define TMC5262_TZEROWAIT_FIELD                     ((RegisterField) {TMC5262_TZEROWAIT_MASK, TMC5262_TZEROWAIT_SHIFT, TMC5262_TZEROWAIT, false})
#define TMC5262_XTARGET_MASK                        0xFFFFFFFF
#define TMC5262_XTARGET_SHIFT                       0
#define TMC5262_XTARGET_FIELD                       ((RegisterField) {TMC5262_XTARGET_MASK, TMC5262_XTARGET_SHIFT, TMC5262_XTARGET, true})
#define TMC5262_V2_MASK                             0x000FFFFF
#define TMC5262_V2_SHIFT                            0
#define TMC5262_V2_FIELD                            ((RegisterField) {TMC5262_V2_MASK, TMC5262_V2_SHIFT, TMC5262_V2, false})
#define TMC5262_A2_MASK                             0x0003FFFF
#define TMC5262_A2_SHIFT                            0
#define TMC5262_A2_FIELD                            ((RegisterField) {TMC5262_A2_MASK, TMC5262_A2_SHIFT, TMC5262_A2, false})
#define TMC5262_D2_MASK                             0x0003FFFF
#define TMC5262_D2_SHIFT                            0
#define TMC5262_D2_FIELD                            ((RegisterField) {TMC5262_D2_MASK, TMC5262_D2_SHIFT, TMC5262_D2, false})
#define TMC5262_AACTUAL_MASK                        0x00FFFFFF
#define TMC5262_AACTUAL_SHIFT                       0
#define TMC5262_AACTUAL_FIELD                       ((RegisterField) {TMC5262_AACTUAL_MASK, TMC5262_AACTUAL_SHIFT, TMC5262_AACTUAL, true})
#define TMC5262_STOP_L_ENABLE_MASK                  0x00000001
#define TMC5262_STOP_L_ENABLE_SHIFT                 0
#define TMC5262_STOP_L_ENABLE_FIELD                 ((RegisterField) {TMC5262_STOP_L_ENABLE_MASK, TMC5262_STOP_L_ENABLE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_STOP_R_ENABLE_MASK                  0x00000002
#define TMC5262_STOP_R_ENABLE_SHIFT                 1
#define TMC5262_STOP_R_ENABLE_FIELD                 ((RegisterField) {TMC5262_STOP_R_ENABLE_MASK, TMC5262_STOP_R_ENABLE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_POL_STOP_L_MASK                     0x00000004
#define TMC5262_POL_STOP_L_SHIFT                    2
#define TMC5262_POL_STOP_L_FIELD                    ((RegisterField) {TMC5262_POL_STOP_L_MASK, TMC5262_POL_STOP_L_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_POL_STOP_R_MASK                     0x00000008
#define TMC5262_POL_STOP_R_SHIFT                    3
#define TMC5262_POL_STOP_R_FIELD                    ((RegisterField) {TMC5262_POL_STOP_R_MASK, TMC5262_POL_STOP_R_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_SWAP_LR_MASK                        0x00000010
#define TMC5262_SWAP_LR_SHIFT                       4
#define TMC5262_SWAP_LR_FIELD                       ((RegisterField) {TMC5262_SWAP_LR_MASK, TMC5262_SWAP_LR_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_LATCH_L_ACTIVE_MASK                 0x00000020
#define TMC5262_LATCH_L_ACTIVE_SHIFT                5
#define TMC5262_LATCH_L_ACTIVE_FIELD                ((RegisterField) {TMC5262_LATCH_L_ACTIVE_MASK, TMC5262_LATCH_L_ACTIVE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_LATCH_L_INACTIVE_MASK               0x00000040
#define TMC5262_LATCH_L_INACTIVE_SHIFT              6
#define TMC5262_LATCH_L_INACTIVE_FIELD              ((RegisterField) {TMC5262_LATCH_L_INACTIVE_MASK, TMC5262_LATCH_L_INACTIVE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_LATCH_R_ACTIVE_MASK                 0x00000080
#define TMC5262_LATCH_R_ACTIVE_SHIFT                7
#define TMC5262_LATCH_R_ACTIVE_FIELD                ((RegisterField) {TMC5262_LATCH_R_ACTIVE_MASK, TMC5262_LATCH_R_ACTIVE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_LATCH_R_INACTIVE_MASK               0x00000100
#define TMC5262_LATCH_R_INACTIVE_SHIFT              8
#define TMC5262_LATCH_R_INACTIVE_FIELD              ((RegisterField) {TMC5262_LATCH_R_INACTIVE_MASK, TMC5262_LATCH_R_INACTIVE_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_EN_LATCH_ENCODER_MASK               0x00000200
#define TMC5262_EN_LATCH_ENCODER_SHIFT              9
#define TMC5262_EN_LATCH_ENCODER_FIELD              ((RegisterField) {TMC5262_EN_LATCH_ENCODER_MASK, TMC5262_EN_LATCH_ENCODER_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_SG_STOP_MASK                        0x00000400
#define TMC5262_SG_STOP_SHIFT                       10
#define TMC5262_SG_STOP_FIELD                       ((RegisterField) {TMC5262_SG_STOP_MASK, TMC5262_SG_STOP_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_EN_SOFTSTOP_MASK                    0x00000800
#define TMC5262_EN_SOFTSTOP_SHIFT                   11
#define TMC5262_EN_SOFTSTOP_FIELD                   ((RegisterField) {TMC5262_EN_SOFTSTOP_MASK, TMC5262_EN_SOFTSTOP_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_EN_VIRTUAL_STOP_L_MASK              0x00001000
#define TMC5262_EN_VIRTUAL_STOP_L_SHIFT             12
#define TMC5262_EN_VIRTUAL_STOP_L_FIELD             ((RegisterField) {TMC5262_EN_VIRTUAL_STOP_L_MASK, TMC5262_EN_VIRTUAL_STOP_L_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_EN_VIRTUAL_STOP_R_MASK              0x00002000
#define TMC5262_EN_VIRTUAL_STOP_R_SHIFT             13
#define TMC5262_EN_VIRTUAL_STOP_R_FIELD             ((RegisterField) {TMC5262_EN_VIRTUAL_STOP_R_MASK, TMC5262_EN_VIRTUAL_STOP_R_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_VIRTUAL_STOP_ENC_MASK               0x00004000
#define TMC5262_VIRTUAL_STOP_ENC_SHIFT              14
#define TMC5262_VIRTUAL_STOP_ENC_FIELD              ((RegisterField) {TMC5262_VIRTUAL_STOP_ENC_MASK, TMC5262_VIRTUAL_STOP_ENC_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_HARD_STOP_CLR_CUR_INT_MASK          0x00008000
#define TMC5262_HARD_STOP_CLR_CUR_INT_SHIFT         15
#define TMC5262_HARD_STOP_CLR_CUR_INT_FIELD         ((RegisterField) {TMC5262_HARD_STOP_CLR_CUR_INT_MASK, TMC5262_HARD_STOP_CLR_CUR_INT_SHIFT, TMC5262_SW_MODE, false})
#define TMC5262_STATUS_STOP_L_MASK                  0x00000001
#define TMC5262_STATUS_STOP_L_SHIFT                 0
#define TMC5262_STATUS_STOP_L_FIELD                 ((RegisterField) {TMC5262_STATUS_STOP_L_MASK, TMC5262_STATUS_STOP_L_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_STOP_R_MASK                  0x00000002
#define TMC5262_STATUS_STOP_R_SHIFT                 1
#define TMC5262_STATUS_STOP_R_FIELD                 ((RegisterField) {TMC5262_STATUS_STOP_R_MASK, TMC5262_STATUS_STOP_R_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_LATCH_L_MASK                 0x00000004
#define TMC5262_STATUS_LATCH_L_SHIFT                2
#define TMC5262_STATUS_LATCH_L_FIELD                ((RegisterField) {TMC5262_STATUS_LATCH_L_MASK, TMC5262_STATUS_LATCH_L_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_LATCH_R_MASK                 0x00000008
#define TMC5262_STATUS_LATCH_R_SHIFT                3
#define TMC5262_STATUS_LATCH_R_FIELD                ((RegisterField) {TMC5262_STATUS_LATCH_R_MASK, TMC5262_STATUS_LATCH_R_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_EVENT_STOP_L_MASK                   0x00000010
#define TMC5262_EVENT_STOP_L_SHIFT                  4
#define TMC5262_EVENT_STOP_L_FIELD                  ((RegisterField) {TMC5262_EVENT_STOP_L_MASK, TMC5262_EVENT_STOP_L_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_EVENT_STOP_R_MASK                   0x00000020
#define TMC5262_EVENT_STOP_R_SHIFT                  5
#define TMC5262_EVENT_STOP_R_FIELD                  ((RegisterField) {TMC5262_EVENT_STOP_R_MASK, TMC5262_EVENT_STOP_R_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_EVENT_STOP_SG_MASK                  0x00000040
#define TMC5262_EVENT_STOP_SG_SHIFT                 6
#define TMC5262_EVENT_STOP_SG_FIELD                 ((RegisterField) {TMC5262_EVENT_STOP_SG_MASK, TMC5262_EVENT_STOP_SG_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_EVENT_POS_REACHED_MASK              0x00000080
#define TMC5262_EVENT_POS_REACHED_SHIFT             7
#define TMC5262_EVENT_POS_REACHED_FIELD             ((RegisterField) {TMC5262_EVENT_POS_REACHED_MASK, TMC5262_EVENT_POS_REACHED_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_VELOCITY_REACHED_MASK               0x00000100
#define TMC5262_VELOCITY_REACHED_SHIFT              8
#define TMC5262_VELOCITY_REACHED_FIELD              ((RegisterField) {TMC5262_VELOCITY_REACHED_MASK, TMC5262_VELOCITY_REACHED_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_POSITION_REACHED_MASK               0x00000200
#define TMC5262_POSITION_REACHED_SHIFT              9
#define TMC5262_POSITION_REACHED_FIELD              ((RegisterField) {TMC5262_POSITION_REACHED_MASK, TMC5262_POSITION_REACHED_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_VZERO_MASK                          0x00000400
#define TMC5262_VZERO_SHIFT                         10
#define TMC5262_VZERO_FIELD                         ((RegisterField) {TMC5262_VZERO_MASK, TMC5262_VZERO_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_T_ZEROWAIT_ACTIVE_MASK              0x00000800
#define TMC5262_T_ZEROWAIT_ACTIVE_SHIFT             11
#define TMC5262_T_ZEROWAIT_ACTIVE_FIELD             ((RegisterField) {TMC5262_T_ZEROWAIT_ACTIVE_MASK, TMC5262_T_ZEROWAIT_ACTIVE_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_SECOND_MOVE_MASK                    0x00001000
#define TMC5262_SECOND_MOVE_SHIFT                   12
#define TMC5262_SECOND_MOVE_FIELD                   ((RegisterField) {TMC5262_SECOND_MOVE_MASK, TMC5262_SECOND_MOVE_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_SG_MASK                      0x00002000
#define TMC5262_STATUS_SG_SHIFT                     13
#define TMC5262_STATUS_SG_FIELD                     ((RegisterField) {TMC5262_STATUS_SG_MASK, TMC5262_STATUS_SG_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_VIRTUAL_STOP_L_MASK          0x00004000
#define TMC5262_STATUS_VIRTUAL_STOP_L_SHIFT         14
#define TMC5262_STATUS_VIRTUAL_STOP_L_FIELD         ((RegisterField) {TMC5262_STATUS_VIRTUAL_STOP_L_MASK, TMC5262_STATUS_VIRTUAL_STOP_L_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_STATUS_VIRTUAL_STOP_R_MASK          0x00008000
#define TMC5262_STATUS_VIRTUAL_STOP_R_SHIFT         15
#define TMC5262_STATUS_VIRTUAL_STOP_R_FIELD         ((RegisterField) {TMC5262_STATUS_VIRTUAL_STOP_R_MASK, TMC5262_STATUS_VIRTUAL_STOP_R_SHIFT, TMC5262_RAMP_STAT, false})
#define TMC5262_XLATCH_MASK                         0xFFFFFFFF
#define TMC5262_XLATCH_SHIFT                        0
#define TMC5262_XLATCH_FIELD                        ((RegisterField) {TMC5262_XLATCH_MASK, TMC5262_XLATCH_SHIFT, TMC5262_XLATCH, false})
#define TMC5262_POL_A_MASK                          0x00000001
#define TMC5262_POL_A_SHIFT                         0
#define TMC5262_POL_A_FIELD                         ((RegisterField) {TMC5262_POL_A_MASK, TMC5262_POL_A_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_POL_B_MASK                          0x00000002
#define TMC5262_POL_B_SHIFT                         1
#define TMC5262_POL_B_FIELD                         ((RegisterField) {TMC5262_POL_B_MASK, TMC5262_POL_B_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_POL_N_MASK                          0x00000004
#define TMC5262_POL_N_SHIFT                         2
#define TMC5262_POL_N_FIELD                         ((RegisterField) {TMC5262_POL_N_MASK, TMC5262_POL_N_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_IGNORE_AB_MASK                      0x00000008
#define TMC5262_IGNORE_AB_SHIFT                     3
#define TMC5262_IGNORE_AB_FIELD                     ((RegisterField) {TMC5262_IGNORE_AB_MASK, TMC5262_IGNORE_AB_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_CLR_CONT_MASK                       0x00000010
#define TMC5262_CLR_CONT_SHIFT                      4
#define TMC5262_CLR_CONT_FIELD                      ((RegisterField) {TMC5262_CLR_CONT_MASK, TMC5262_CLR_CONT_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_CLR_ONCE_MASK                       0x00000020
#define TMC5262_CLR_ONCE_SHIFT                      5
#define TMC5262_CLR_ONCE_FIELD                      ((RegisterField) {TMC5262_CLR_ONCE_MASK, TMC5262_CLR_ONCE_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_POS_NEG_EDGE_MASK                   0x000000C0
#define TMC5262_POS_NEG_EDGE_SHIFT                  6
#define TMC5262_POS_NEG_EDGE_FIELD                  ((RegisterField) {TMC5262_POS_NEG_EDGE_MASK, TMC5262_POS_NEG_EDGE_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_CLR_ENC_X_MASK                      0x00000100
#define TMC5262_CLR_ENC_X_SHIFT                     8
#define TMC5262_CLR_ENC_X_FIELD                     ((RegisterField) {TMC5262_CLR_ENC_X_MASK, TMC5262_CLR_ENC_X_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_LATCH_X_ACT_MASK                    0x00000200
#define TMC5262_LATCH_X_ACT_SHIFT                   9
#define TMC5262_LATCH_X_ACT_FIELD                   ((RegisterField) {TMC5262_LATCH_X_ACT_MASK, TMC5262_LATCH_X_ACT_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_ENC_SEL_DECIMAL_MASK                0x00000400
#define TMC5262_ENC_SEL_DECIMAL_SHIFT               10
#define TMC5262_ENC_SEL_DECIMAL_FIELD               ((RegisterField) {TMC5262_ENC_SEL_DECIMAL_MASK, TMC5262_ENC_SEL_DECIMAL_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_NBEMF_ABN_SEL_MASK                  0x00000800
#define TMC5262_NBEMF_ABN_SEL_SHIFT                 11
#define TMC5262_NBEMF_ABN_SEL_FIELD                 ((RegisterField) {TMC5262_NBEMF_ABN_SEL_MASK, TMC5262_NBEMF_ABN_SEL_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_BEMF_HYST_MASK                      0x00007000
#define TMC5262_BEMF_HYST_SHIFT                     12
#define TMC5262_BEMF_HYST_FIELD                     ((RegisterField) {TMC5262_BEMF_HYST_MASK, TMC5262_BEMF_HYST_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_BEMF_BLANK_TIME_MASK                0x00FF0000
#define TMC5262_BEMF_BLANK_TIME_SHIFT               16
#define TMC5262_BEMF_BLANK_TIME_FIELD               ((RegisterField) {TMC5262_BEMF_BLANK_TIME_MASK, TMC5262_BEMF_BLANK_TIME_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_BEMF_FILTER_SEL_MASK                0x30000000
#define TMC5262_BEMF_FILTER_SEL_SHIFT               28
#define TMC5262_BEMF_FILTER_SEL_FIELD               ((RegisterField) {TMC5262_BEMF_FILTER_SEL_MASK, TMC5262_BEMF_FILTER_SEL_SHIFT, TMC5262_ENCMODE, false})
#define TMC5262_X_ENC_MASK                          0xFFFFFFFF
#define TMC5262_X_ENC_SHIFT                         0
#define TMC5262_X_ENC_FIELD                         ((RegisterField) {TMC5262_X_ENC_MASK, TMC5262_X_ENC_SHIFT, TMC5262_X_ENC, true})
#define TMC5262_ENC_CONST_MASK                      0xFFFFFFFF
#define TMC5262_ENC_CONST_SHIFT                     0
#define TMC5262_ENC_CONST_FIELD                     ((RegisterField) {TMC5262_ENC_CONST_MASK, TMC5262_ENC_CONST_SHIFT, TMC5262_ENC_CONST, true})
#define TMC5262_N_EVENT_MASK                        0x00000001
#define TMC5262_N_EVENT_SHIFT                       0
#define TMC5262_N_EVENT_FIELD                       ((RegisterField) {TMC5262_N_EVENT_MASK, TMC5262_N_EVENT_SHIFT, TMC5262_ENC_STATUS, false})
#define TMC5262_DEVIATION_WARN_MASK                 0x00000002
#define TMC5262_DEVIATION_WARN_SHIFT                1
#define TMC5262_DEVIATION_WARN_FIELD                ((RegisterField) {TMC5262_DEVIATION_WARN_MASK, TMC5262_DEVIATION_WARN_SHIFT, TMC5262_ENC_STATUS, false})
#define TMC5262_ENC_LATCH_MASK                      0xFFFFFFFF
#define TMC5262_ENC_LATCH_SHIFT                     0
#define TMC5262_ENC_LATCH_FIELD                     ((RegisterField) {TMC5262_ENC_LATCH_MASK, TMC5262_ENC_LATCH_SHIFT, TMC5262_ENC_LATCH, false})
#define TMC5262_ENC_DEVIATION_MASK                  0x000FFFFF
#define TMC5262_ENC_DEVIATION_SHIFT                 0
#define TMC5262_ENC_DEVIATION_FIELD                 ((RegisterField) {TMC5262_ENC_DEVIATION_MASK, TMC5262_ENC_DEVIATION_SHIFT, TMC5262_ENC_DEVIATION, false})
#define TMC5262_VIRTUAL_STOP_L_MASK                 0xFFFFFFFF
#define TMC5262_VIRTUAL_STOP_L_SHIFT                0
#define TMC5262_VIRTUAL_STOP_L_FIELD                ((RegisterField) {TMC5262_VIRTUAL_STOP_L_MASK, TMC5262_VIRTUAL_STOP_L_SHIFT, TMC5262_VIRTUAL_STOP_L, true})
#define TMC5262_VIRTUAL_STOP_R_MASK                 0xFFFFFFFF
#define TMC5262_VIRTUAL_STOP_R_SHIFT                0
#define TMC5262_VIRTUAL_STOP_R_FIELD                ((RegisterField) {TMC5262_VIRTUAL_STOP_R_MASK, TMC5262_VIRTUAL_STOP_R_SHIFT, TMC5262_VIRTUAL_STOP_R, true})
#define TMC5262_CUR_P_MASK                          0x00000FFF
#define TMC5262_CUR_P_SHIFT                         0
#define TMC5262_CUR_P_FIELD                         ((RegisterField) {TMC5262_CUR_P_MASK, TMC5262_CUR_P_SHIFT, TMC5262_CURRENT_PI_REG, false})
#define TMC5262_CUR_I_MASK                          0x03FF0000
#define TMC5262_CUR_I_SHIFT                         16
#define TMC5262_CUR_I_FIELD                         ((RegisterField) {TMC5262_CUR_I_MASK, TMC5262_CUR_I_SHIFT, TMC5262_CURRENT_PI_REG, false})
#define TMC5262_ANGLE_P_MASK                        0x00000FFF
#define TMC5262_ANGLE_P_SHIFT                       0
#define TMC5262_ANGLE_P_FIELD                       ((RegisterField) {TMC5262_ANGLE_P_MASK, TMC5262_ANGLE_P_SHIFT, TMC5262_ANGLE_PI_REG, false})
#define TMC5262_ANGLE_I_MASK                        0x03FF0000
#define TMC5262_ANGLE_I_SHIFT                       16
#define TMC5262_ANGLE_I_FIELD                       ((RegisterField) {TMC5262_ANGLE_I_MASK, TMC5262_ANGLE_I_SHIFT, TMC5262_ANGLE_PI_REG, false})
#define TMC5262_ANGLE_PI_LIMIT_MASK                 0x000003FF
#define TMC5262_ANGLE_PI_LIMIT_SHIFT                0
#define TMC5262_ANGLE_PI_LIMIT_FIELD                ((RegisterField) {TMC5262_ANGLE_PI_LIMIT_MASK, TMC5262_ANGLE_PI_LIMIT_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_ANGLE_PI_INT_POS_CLIP_MASK          0x00001000
#define TMC5262_ANGLE_PI_INT_POS_CLIP_SHIFT         12
#define TMC5262_ANGLE_PI_INT_POS_CLIP_FIELD         ((RegisterField) {TMC5262_ANGLE_PI_INT_POS_CLIP_MASK, TMC5262_ANGLE_PI_INT_POS_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_ANGLE_PI_INT_NEG_CLIP_MASK          0x00002000
#define TMC5262_ANGLE_PI_INT_NEG_CLIP_SHIFT         13
#define TMC5262_ANGLE_PI_INT_NEG_CLIP_FIELD         ((RegisterField) {TMC5262_ANGLE_PI_INT_NEG_CLIP_MASK, TMC5262_ANGLE_PI_INT_NEG_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_ANGLE_PI_POS_CLIP_MASK              0x00004000
#define TMC5262_ANGLE_PI_POS_CLIP_SHIFT             14
#define TMC5262_ANGLE_PI_POS_CLIP_FIELD             ((RegisterField) {TMC5262_ANGLE_PI_POS_CLIP_MASK, TMC5262_ANGLE_PI_POS_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_ANGLE_PI_NEG_CLIP_MASK              0x00008000
#define TMC5262_ANGLE_PI_NEG_CLIP_SHIFT             15
#define TMC5262_ANGLE_PI_NEG_CLIP_FIELD             ((RegisterField) {TMC5262_ANGLE_PI_NEG_CLIP_MASK, TMC5262_ANGLE_PI_NEG_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_CUR_PI_LIMIT_MASK                   0x0FFF0000
#define TMC5262_CUR_PI_LIMIT_SHIFT                  16
#define TMC5262_CUR_PI_LIMIT_FIELD                  ((RegisterField) {TMC5262_CUR_PI_LIMIT_MASK, TMC5262_CUR_PI_LIMIT_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_CUR_PI_INT_POS_CLIP_MASK            0x10000000
#define TMC5262_CUR_PI_INT_POS_CLIP_SHIFT           28
#define TMC5262_CUR_PI_INT_POS_CLIP_FIELD           ((RegisterField) {TMC5262_CUR_PI_INT_POS_CLIP_MASK, TMC5262_CUR_PI_INT_POS_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_CUR_PI_INT_NEG_CLIP_MASK            0x20000000
#define TMC5262_CUR_PI_INT_NEG_CLIP_SHIFT           29
#define TMC5262_CUR_PI_INT_NEG_CLIP_FIELD           ((RegisterField) {TMC5262_CUR_PI_INT_NEG_CLIP_MASK, TMC5262_CUR_PI_INT_NEG_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_CUR_PI_POS_CLIP_MASK                0x40000000
#define TMC5262_CUR_PI_POS_CLIP_SHIFT               30
#define TMC5262_CUR_PI_POS_CLIP_FIELD               ((RegisterField) {TMC5262_CUR_PI_POS_CLIP_MASK, TMC5262_CUR_PI_POS_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_CUR_PI_NEG_CLIP_MASK                0x80000000
#define TMC5262_CUR_PI_NEG_CLIP_SHIFT               31
#define TMC5262_CUR_PI_NEG_CLIP_FIELD               ((RegisterField) {TMC5262_CUR_PI_NEG_CLIP_MASK, TMC5262_CUR_PI_NEG_CLIP_SHIFT, TMC5262_CUR_ANGLE_LIMIT, false})
#define TMC5262_ANGLE_LOWER_I_LIMIT_MASK            0x000003FF
#define TMC5262_ANGLE_LOWER_I_LIMIT_SHIFT           0
#define TMC5262_ANGLE_LOWER_I_LIMIT_FIELD           ((RegisterField) {TMC5262_ANGLE_LOWER_I_LIMIT_MASK, TMC5262_ANGLE_LOWER_I_LIMIT_SHIFT, TMC5262_ANGLE_LOWER_LIMIT, false})
#define TMC5262_ANGLE_ERROR_MASK                    0x03FF0000
#define TMC5262_ANGLE_ERROR_SHIFT                   16
#define TMC5262_ANGLE_ERROR_FIELD                   ((RegisterField) {TMC5262_ANGLE_ERROR_MASK, TMC5262_ANGLE_ERROR_SHIFT, TMC5262_ANGLE_LOWER_LIMIT, true})
#define TMC5262_AMPL_MEAS_MASK                      0x00000FFF
#define TMC5262_AMPL_MEAS_SHIFT                     0
#define TMC5262_AMPL_MEAS_FIELD                     ((RegisterField) {TMC5262_AMPL_MEAS_MASK, TMC5262_AMPL_MEAS_SHIFT, TMC5262_CUR_ANGLE_MEAS, false})
#define TMC5262_ANGLE_MEAS_MASK                     0x03FF0000
#define TMC5262_ANGLE_MEAS_SHIFT                    16
#define TMC5262_ANGLE_MEAS_FIELD                    ((RegisterField) {TMC5262_ANGLE_MEAS_MASK, TMC5262_ANGLE_MEAS_SHIFT, TMC5262_CUR_ANGLE_MEAS, false})
#define TMC5262_PWM_CALC_MASK                       0x00001FFF
#define TMC5262_PWM_CALC_SHIFT                      0
#define TMC5262_PWM_CALC_FIELD                      ((RegisterField) {TMC5262_PWM_CALC_MASK, TMC5262_PWM_CALC_SHIFT, TMC5262_PI_RESULTS, true})
#define TMC5262_ANGLE_CORR_CALC_MASK                0x03FF0000
#define TMC5262_ANGLE_CORR_CALC_SHIFT               16
#define TMC5262_ANGLE_CORR_CALC_FIELD               ((RegisterField) {TMC5262_ANGLE_CORR_CALC_MASK, TMC5262_ANGLE_CORR_CALC_SHIFT, TMC5262_PI_RESULTS, true})
#define TMC5262_COIL_INDUCT_MASK                    0x00007FFF
#define TMC5262_COIL_INDUCT_SHIFT                   0
#define TMC5262_COIL_INDUCT_FIELD                   ((RegisterField) {TMC5262_COIL_INDUCT_MASK, TMC5262_COIL_INDUCT_SHIFT, TMC5262_COIL_INDUCT, false})
#define TMC5262_RCOIL_MANUAL_MASK                   0x00010000
#define TMC5262_RCOIL_MANUAL_SHIFT                  16
#define TMC5262_RCOIL_MANUAL_FIELD                  ((RegisterField) {TMC5262_RCOIL_MANUAL_MASK, TMC5262_RCOIL_MANUAL_SHIFT, TMC5262_COIL_INDUCT, false})
#define TMC5262_RCOIL_THERMAL_COUPLING_MASK         0x00020000
#define TMC5262_RCOIL_THERMAL_COUPLING_SHIFT        17
#define TMC5262_RCOIL_THERMAL_COUPLING_FIELD        ((RegisterField) {TMC5262_RCOIL_THERMAL_COUPLING_MASK, TMC5262_RCOIL_THERMAL_COUPLING_SHIFT, TMC5262_COIL_INDUCT, false})
#define TMC5262_R_COIL_AUTO_B_MASK                  0x00000FFF
#define TMC5262_R_COIL_AUTO_B_SHIFT                 0
#define TMC5262_R_COIL_AUTO_B_FIELD                 ((RegisterField) {TMC5262_R_COIL_AUTO_B_MASK, TMC5262_R_COIL_AUTO_B_SHIFT, TMC5262_R_COIL, false})
#define TMC5262_R_COIL_AUTO_A_MASK                  0x0FFF0000
#define TMC5262_R_COIL_AUTO_A_SHIFT                 16
#define TMC5262_R_COIL_AUTO_A_FIELD                 ((RegisterField) {TMC5262_R_COIL_AUTO_A_MASK, TMC5262_R_COIL_AUTO_A_SHIFT, TMC5262_R_COIL, false})
#define TMC5262_R_COIL_USER_B_MASK                  0x00000FFF
#define TMC5262_R_COIL_USER_B_SHIFT                 0
#define TMC5262_R_COIL_USER_B_FIELD                 ((RegisterField) {TMC5262_R_COIL_USER_B_MASK, TMC5262_R_COIL_USER_B_SHIFT, TMC5262_R_COIL_USER, false})
#define TMC5262_R_COIL_USER_A_MASK                  0x0FFF0000
#define TMC5262_R_COIL_USER_A_SHIFT                 16
#define TMC5262_R_COIL_USER_A_FIELD                 ((RegisterField) {TMC5262_R_COIL_USER_A_MASK, TMC5262_R_COIL_USER_A_SHIFT, TMC5262_R_COIL_USER, false})
#define TMC5262_SGP_THRS_MASK                       0x000001FF
#define TMC5262_SGP_THRS_SHIFT                      0
#define TMC5262_SGP_THRS_FIELD                      ((RegisterField) {TMC5262_SGP_THRS_MASK, TMC5262_SGP_THRS_SHIFT, TMC5262_SGP_CONF, true})
#define TMC5262_SGP_FILT_EN_MASK                    0x00001000
#define TMC5262_SGP_FILT_EN_SHIFT                   12
#define TMC5262_SGP_FILT_EN_FIELD                   ((RegisterField) {TMC5262_SGP_FILT_EN_MASK, TMC5262_SGP_FILT_EN_SHIFT, TMC5262_SGP_CONF, false})
#define TMC5262_SGP_LOW_VEL_FREEZE_MASK             0x00002000
#define TMC5262_SGP_LOW_VEL_FREEZE_SHIFT            13
#define TMC5262_SGP_LOW_VEL_FREEZE_FIELD            ((RegisterField) {TMC5262_SGP_LOW_VEL_FREEZE_MASK, TMC5262_SGP_LOW_VEL_FREEZE_SHIFT, TMC5262_SGP_CONF, false})
#define TMC5262_SGP_CLEAR_CUR_PI_MASK               0x00004000
#define TMC5262_SGP_CLEAR_CUR_PI_SHIFT              14
#define TMC5262_SGP_CLEAR_CUR_PI_FIELD              ((RegisterField) {TMC5262_SGP_CLEAR_CUR_PI_MASK, TMC5262_SGP_CLEAR_CUR_PI_SHIFT, TMC5262_SGP_CONF, false})
#define TMC5262_SGP_LOW_VEL_SLOPE_MASK              0x00FF0000
#define TMC5262_SGP_LOW_VEL_SLOPE_SHIFT             16
#define TMC5262_SGP_LOW_VEL_SLOPE_FIELD             ((RegisterField) {TMC5262_SGP_LOW_VEL_SLOPE_MASK, TMC5262_SGP_LOW_VEL_SLOPE_SHIFT, TMC5262_SGP_CONF, false})
#define TMC5262_SGP_LOW_VEL_CNTS_MASK               0x30000000
#define TMC5262_SGP_LOW_VEL_CNTS_SHIFT              28
#define TMC5262_SGP_LOW_VEL_CNTS_FIELD              ((RegisterField) {TMC5262_SGP_LOW_VEL_CNTS_MASK, TMC5262_SGP_LOW_VEL_CNTS_SHIFT, TMC5262_SGP_CONF, false})
#define TMC5262_SGP_IND_2_MASK                      0x000003FF
#define TMC5262_SGP_IND_2_SHIFT                     0
#define TMC5262_SGP_IND_2_FIELD                     ((RegisterField) {TMC5262_SGP_IND_2_MASK, TMC5262_SGP_IND_2_SHIFT, TMC5262_SGP_IND_2_3, true})
#define TMC5262_SGP_IND_3_MASK                      0x03FF0000
#define TMC5262_SGP_IND_3_SHIFT                     16
#define TMC5262_SGP_IND_3_FIELD                     ((RegisterField) {TMC5262_SGP_IND_3_MASK, TMC5262_SGP_IND_3_SHIFT, TMC5262_SGP_IND_2_3, true})
#define TMC5262_SGP_IND_0_MASK                      0x000003FF
#define TMC5262_SGP_IND_0_SHIFT                     0
#define TMC5262_SGP_IND_0_FIELD                     ((RegisterField) {TMC5262_SGP_IND_0_MASK, TMC5262_SGP_IND_0_SHIFT, TMC5262_SGP_IND_0_1, true})
#define TMC5262_SGP_IND_1_MASK                      0x03FF0000
#define TMC5262_SGP_IND_1_SHIFT                     16
#define TMC5262_SGP_IND_1_FIELD                     ((RegisterField) {TMC5262_SGP_IND_1_MASK, TMC5262_SGP_IND_1_SHIFT, TMC5262_SGP_IND_0_1, true})
#define TMC5262_UL_B_MASK                           0x00000FFF
#define TMC5262_UL_B_SHIFT                          0
#define TMC5262_UL_B_FIELD                          ((RegisterField) {TMC5262_UL_B_MASK, TMC5262_UL_B_SHIFT, TMC5262_INDUCTANCE_VOLTAGE, true})
#define TMC5262_UL_A_MASK                           0x0FFF0000
#define TMC5262_UL_A_SHIFT                          16
#define TMC5262_UL_A_FIELD                          ((RegisterField) {TMC5262_UL_A_MASK, TMC5262_UL_A_SHIFT, TMC5262_INDUCTANCE_VOLTAGE, true})
#define TMC5262_SGP_RAW_MASK                        0x000003FF
#define TMC5262_SGP_RAW_SHIFT                       0
#define TMC5262_SGP_RAW_FIELD                       ((RegisterField) {TMC5262_SGP_RAW_MASK, TMC5262_SGP_RAW_SHIFT, TMC5262_SGP_BEMF, true})
#define TMC5262_UBEMF_ABS_MASK                      0x0FFF0000
#define TMC5262_UBEMF_ABS_SHIFT                     16
#define TMC5262_UBEMF_ABS_FIELD                     ((RegisterField) {TMC5262_UBEMF_ABS_MASK, TMC5262_UBEMF_ABS_SHIFT, TMC5262_SGP_BEMF, false})
#define TMC5262_COOL_CUR_DIV_MASK                   0x0000000F
#define TMC5262_COOL_CUR_DIV_SHIFT                  0
#define TMC5262_COOL_CUR_DIV_FIELD                  ((RegisterField) {TMC5262_COOL_CUR_DIV_MASK, TMC5262_COOL_CUR_DIV_SHIFT, TMC5262_COOLSTEPPLUS_CONF, false})
#define TMC5262_LOAD_FILT_EN_MASK                   0x00000010
#define TMC5262_LOAD_FILT_EN_SHIFT                  4
#define TMC5262_LOAD_FILT_EN_FIELD                  ((RegisterField) {TMC5262_LOAD_FILT_EN_MASK, TMC5262_LOAD_FILT_EN_SHIFT, TMC5262_COOLSTEPPLUS_CONF, false})
#define TMC5262_COOLSTEP_P_MASK                     0x00000FFF
#define TMC5262_COOLSTEP_P_SHIFT                    0
#define TMC5262_COOLSTEP_P_FIELD                    ((RegisterField) {TMC5262_COOLSTEP_P_MASK, TMC5262_COOLSTEP_P_SHIFT, TMC5262_COOLSTEPPLUS_PI_REG, false})
#define TMC5262_COOLSTEP_I_MASK                     0x03FF0000
#define TMC5262_COOLSTEP_I_SHIFT                    16
#define TMC5262_COOLSTEP_I_FIELD                    ((RegisterField) {TMC5262_COOLSTEP_I_MASK, TMC5262_COOLSTEP_I_SHIFT, TMC5262_COOLSTEPPLUS_PI_REG, false})
#define TMC5262_COOL_PI_DOWN_LIMIT_MASK             0x00000FFF
#define TMC5262_COOL_PI_DOWN_LIMIT_SHIFT            0
#define TMC5262_COOL_PI_DOWN_LIMIT_FIELD            ((RegisterField) {TMC5262_COOL_PI_DOWN_LIMIT_MASK, TMC5262_COOL_PI_DOWN_LIMIT_SHIFT, TMC5262_COOLSTEPPLUS_PI_DOWN, false})
#define TMC5262_COOL_PI_OFF_SPEED_MASK              0x0FFF0000
#define TMC5262_COOL_PI_OFF_SPEED_SHIFT             16
#define TMC5262_COOL_PI_OFF_SPEED_FIELD             ((RegisterField) {TMC5262_COOL_PI_OFF_SPEED_MASK, TMC5262_COOL_PI_OFF_SPEED_SHIFT, TMC5262_COOLSTEPPLUS_PI_DOWN, false})
#define TMC5262_COOL_LOW_LOAD_RESERVE_MASK          0x000000FF
#define TMC5262_COOL_LOW_LOAD_RESERVE_SHIFT         0
#define TMC5262_COOL_LOW_LOAD_RESERVE_FIELD         ((RegisterField) {TMC5262_COOL_LOW_LOAD_RESERVE_MASK, TMC5262_COOL_LOW_LOAD_RESERVE_SHIFT, TMC5262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC5262_COOL_HI_LOAD_RESERVE_MASK           0x0000FF00
#define TMC5262_COOL_HI_LOAD_RESERVE_SHIFT          8
#define TMC5262_COOL_HI_LOAD_RESERVE_FIELD          ((RegisterField) {TMC5262_COOL_HI_LOAD_RESERVE_MASK, TMC5262_COOL_HI_LOAD_RESERVE_SHIFT, TMC5262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC5262_COOL_LOW_GENERATORIC_RESERVE_MASK   0x00FF0000
#define TMC5262_COOL_LOW_GENERATORIC_RESERVE_SHIFT  16
#define TMC5262_COOL_LOW_GENERATORIC_RESERVE_FIELD  ((RegisterField) {TMC5262_COOL_LOW_GENERATORIC_RESERVE_MASK, TMC5262_COOL_LOW_GENERATORIC_RESERVE_SHIFT, TMC5262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC5262_COOL_HI_GENERATORIC_RESERVE_MASK    0xFF000000
#define TMC5262_COOL_HI_GENERATORIC_RESERVE_SHIFT   24
#define TMC5262_COOL_HI_GENERATORIC_RESERVE_FIELD   ((RegisterField) {TMC5262_COOL_HI_GENERATORIC_RESERVE_MASK, TMC5262_COOL_HI_GENERATORIC_RESERVE_SHIFT, TMC5262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC5262_SGP_RESULT_MASK                     0x000003FF
#define TMC5262_SGP_RESULT_SHIFT                    0
#define TMC5262_SGP_RESULT_FIELD                    ((RegisterField) {TMC5262_SGP_RESULT_MASK, TMC5262_SGP_RESULT_SHIFT, TMC5262_COOLSTEPPLUS_LOAD_RESERVE, true})
#define TMC5262_COOLSTEP_LOAD_RESERVE_MASK          0x01FF0000
#define TMC5262_COOLSTEP_LOAD_RESERVE_SHIFT         16
#define TMC5262_COOLSTEP_LOAD_RESERVE_FIELD         ((RegisterField) {TMC5262_COOLSTEP_LOAD_RESERVE_MASK, TMC5262_COOLSTEP_LOAD_RESERVE_SHIFT, TMC5262_COOLSTEPPLUS_LOAD_RESERVE, false})
#define TMC5262_TSTEP_VELOCITY_MASK                 0x007FFFFF
#define TMC5262_TSTEP_VELOCITY_SHIFT                0
#define TMC5262_TSTEP_VELOCITY_FIELD                ((RegisterField) {TMC5262_TSTEP_VELOCITY_MASK, TMC5262_TSTEP_VELOCITY_SHIFT, TMC5262_TSTEP_VELOCITY, true})
#define TMC5262_ADC_VSUPPLY_MASK                    0x000001FF
#define TMC5262_ADC_VSUPPLY_SHIFT                   0
#define TMC5262_ADC_VSUPPLY_FIELD                   ((RegisterField) {TMC5262_ADC_VSUPPLY_MASK, TMC5262_ADC_VSUPPLY_SHIFT, TMC5262_ADC_VSUPPLY_TEMP, false})
#define TMC5262_ADC_TEMP_MASK                       0x01FF0000
#define TMC5262_ADC_TEMP_SHIFT                      16
#define TMC5262_ADC_TEMP_FIELD                      ((RegisterField) {TMC5262_ADC_TEMP_MASK, TMC5262_ADC_TEMP_SHIFT, TMC5262_ADC_VSUPPLY_TEMP, false})
#define TMC5262_ADC_I_A_MASK                        0x00000FFF
#define TMC5262_ADC_I_A_SHIFT                       0
#define TMC5262_ADC_I_A_FIELD                       ((RegisterField) {TMC5262_ADC_I_A_MASK, TMC5262_ADC_I_A_SHIFT, TMC5262_ADC_I, true})
#define TMC5262_ADC_I_B_MASK                        0x0FFF0000
#define TMC5262_ADC_I_B_SHIFT                       16
#define TMC5262_ADC_I_B_FIELD                       ((RegisterField) {TMC5262_ADC_I_B_MASK, TMC5262_ADC_I_B_SHIFT, TMC5262_ADC_I, true})
#define TMC5262_OVERVOLTAGE_VTH_MASK                0x000001FF
#define TMC5262_OVERVOLTAGE_VTH_SHIFT               0
#define TMC5262_OVERVOLTAGE_VTH_FIELD               ((RegisterField) {TMC5262_OVERVOLTAGE_VTH_MASK, TMC5262_OVERVOLTAGE_VTH_SHIFT, TMC5262_OTW_OV_VTH, false})
#define TMC5262_OVERTEMPPREWARNING_VTH_MASK         0x01FF0000
#define TMC5262_OVERTEMPPREWARNING_VTH_SHIFT        16
#define TMC5262_OVERTEMPPREWARNING_VTH_FIELD        ((RegisterField) {TMC5262_OVERTEMPPREWARNING_VTH_MASK, TMC5262_OVERTEMPPREWARNING_VTH_SHIFT, TMC5262_OTW_OV_VTH, false})
#define TMC5262_MSLUT_0_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_0_SHIFT                       0
#define TMC5262_MSLUT_0_FIELD                       ((RegisterField) {TMC5262_MSLUT_0_MASK, TMC5262_MSLUT_0_SHIFT, TMC5262_MSLUT_0, false}
#define TMC5262_MSLUT_1_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_1_SHIFT                       0
#define TMC5262_MSLUT_1_FIELD                       ((RegisterField) {TMC5262_MSLUT_1_MASK, TMC5262_MSLUT_1_SHIFT, TMC5262_MSLUT_1, false}
#define TMC5262_MSLUT_2_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_2_SHIFT                       0
#define TMC5262_MSLUT_2_FIELD                       ((RegisterField) {TMC5262_MSLUT_2_MASK, TMC5262_MSLUT_2_SHIFT, TMC5262_MSLUT_2, false}
#define TMC5262_MSLUT_3_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_3_SHIFT                       0
#define TMC5262_MSLUT_3_FIELD                       ((RegisterField) {TMC5262_MSLUT_3_MASK, TMC5262_MSLUT_3_SHIFT, TMC5262_MSLUT_3, false}
#define TMC5262_MSLUT_4_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_4_SHIFT                       0
#define TMC5262_MSLUT_4_FIELD                       ((RegisterField) {TMC5262_MSLUT_4_MASK, TMC5262_MSLUT_4_SHIFT, TMC5262_MSLUT_4, false}
#define TMC5262_MSLUT_5_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_5_SHIFT                       0
#define TMC5262_MSLUT_5_FIELD                       ((RegisterField) {TMC5262_MSLUT_5_MASK, TMC5262_MSLUT_5_SHIFT, TMC5262_MSLUT_5, false}
#define TMC5262_MSLUT_6_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_6_SHIFT                       0
#define TMC5262_MSLUT_6_FIELD                       ((RegisterField) {TMC5262_MSLUT_6_MASK, TMC5262_MSLUT_6_SHIFT, TMC5262_MSLUT_6, false}
#define TMC5262_MSLUT_7_MASK                        0xFFFFFFFF
#define TMC5262_MSLUT_7_SHIFT                       0
#define TMC5262_MSLUT_7_FIELD                       ((RegisterField) {TMC5262_MSLUT_7_MASK, TMC5262_MSLUT_7_SHIFT, TMC5262_MSLUT_7, false}
#define TMC5262_W0_MASK                             0x00000003
#define TMC5262_W0_SHIFT                            0
#define TMC5262_W0_FIELD                            ((RegisterField) {TMC5262_W0_MASK, TMC5262_W0_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_W1_MASK                             0x0000000C
#define TMC5262_W1_SHIFT                            2
#define TMC5262_W1_FIELD                            ((RegisterField) {TMC5262_W1_MASK, TMC5262_W1_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_W2_MASK                             0x00000030
#define TMC5262_W2_SHIFT                            4
#define TMC5262_W2_FIELD                            ((RegisterField) {TMC5262_W2_MASK, TMC5262_W2_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_W3_MASK                             0x000000C0
#define TMC5262_W3_SHIFT                            6
#define TMC5262_W3_FIELD                            ((RegisterField) {TMC5262_W3_MASK, TMC5262_W3_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_X1_MASK                             0x0000FF00
#define TMC5262_X1_SHIFT                            8
#define TMC5262_X1_FIELD                            ((RegisterField) {TMC5262_X1_MASK, TMC5262_X1_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_X2_MASK                             0x00FF0000
#define TMC5262_X2_SHIFT                            16
#define TMC5262_X2_FIELD                            ((RegisterField) {TMC5262_X2_MASK, TMC5262_X2_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_X3_MASK                             0xFF000000
#define TMC5262_X3_SHIFT                            24
#define TMC5262_X3_FIELD                            ((RegisterField) {TMC5262_X3_MASK, TMC5262_X3_SHIFT, TMC5262_MSLUTSEL, false})
#define TMC5262_START_SIN_MASK                      0x000000FF
#define TMC5262_START_SIN_SHIFT                     0
#define TMC5262_START_SIN_FIELD                     ((RegisterField) {TMC5262_START_SIN_MASK, TMC5262_START_SIN_SHIFT, TMC5262_MSLUTSTART, false})
#define TMC5262_START_SIN90_MASK                    0x00FF0000
#define TMC5262_START_SIN90_SHIFT                   16
#define TMC5262_START_SIN90_FIELD                   ((RegisterField) {TMC5262_START_SIN90_MASK, TMC5262_START_SIN90_SHIFT, TMC5262_MSLUTSTART, false})
#define TMC5262_OFFSET_SIN90_MASK                   0xFF000000
#define TMC5262_OFFSET_SIN90_SHIFT                  24
#define TMC5262_OFFSET_SIN90_FIELD                  ((RegisterField) {TMC5262_OFFSET_SIN90_MASK, TMC5262_OFFSET_SIN90_SHIFT, TMC5262_MSLUTSTART, true})
#define TMC5262_MSCNT_MASK                          0x000003FF
#define TMC5262_MSCNT_SHIFT                         0
#define TMC5262_MSCNT_FIELD                         ((RegisterField) {TMC5262_MSCNT_MASK, TMC5262_MSCNT_SHIFT, TMC5262_MSCNT, false})
#define TMC5262_CUR_B_MASK                          0x000001FF
#define TMC5262_CUR_B_SHIFT                         0
#define TMC5262_CUR_B_FIELD                         ((RegisterField) {TMC5262_CUR_B_MASK, TMC5262_CUR_B_SHIFT, TMC5262_MSCURACT, true})
#define TMC5262_CUR_A_MASK                          0x01FF0000
#define TMC5262_CUR_A_SHIFT                         16
#define TMC5262_CUR_A_FIELD                         ((RegisterField) {TMC5262_CUR_A_MASK, TMC5262_CUR_A_SHIFT, TMC5262_MSCURACT, true})
#define TMC5262_TOFF_MASK                           0x0000000F
#define TMC5262_TOFF_SHIFT                          0
#define TMC5262_TOFF_FIELD                          ((RegisterField) {TMC5262_TOFF_MASK, TMC5262_TOFF_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_HSTRT_TFD210_MASK                   0x00000070
#define TMC5262_HSTRT_TFD210_SHIFT                  4
#define TMC5262_HSTRT_TFD210_FIELD                  ((RegisterField) {TMC5262_HSTRT_TFD210_MASK, TMC5262_HSTRT_TFD210_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_HEND_OFFSET_MASK                    0x00000780
#define TMC5262_HEND_OFFSET_SHIFT                   7
#define TMC5262_HEND_OFFSET_FIELD                   ((RegisterField) {TMC5262_HEND_OFFSET_MASK, TMC5262_HEND_OFFSET_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_FD3_MASK                            0x00000800
#define TMC5262_FD3_SHIFT                           11
#define TMC5262_FD3_FIELD                           ((RegisterField) {TMC5262_FD3_MASK, TMC5262_FD3_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_DISFDCC_MASK                        0x00001000
#define TMC5262_DISFDCC_SHIFT                       12
#define TMC5262_DISFDCC_FIELD                       ((RegisterField) {TMC5262_DISFDCC_MASK, TMC5262_DISFDCC_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_CHM_MASK                            0x00004000
#define TMC5262_CHM_SHIFT                           14
#define TMC5262_CHM_FIELD                           ((RegisterField) {TMC5262_CHM_MASK, TMC5262_CHM_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_TBL_MASK                            0x00018000
#define TMC5262_TBL_SHIFT                           15
#define TMC5262_TBL_FIELD                           ((RegisterField) {TMC5262_TBL_MASK, TMC5262_TBL_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_TPFD_MASK                           0x00F00000
#define TMC5262_TPFD_SHIFT                          20
#define TMC5262_TPFD_FIELD                          ((RegisterField) {TMC5262_TPFD_MASK, TMC5262_TPFD_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_MRES_MASK                           0x0F000000
#define TMC5262_MRES_SHIFT                          24
#define TMC5262_MRES_FIELD                          ((RegisterField) {TMC5262_MRES_MASK, TMC5262_MRES_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_INTPOL_MASK                         0x10000000
#define TMC5262_INTPOL_SHIFT                        28
#define TMC5262_INTPOL_FIELD                        ((RegisterField) {TMC5262_INTPOL_MASK, TMC5262_INTPOL_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_DEDGE_MASK                          0x20000000
#define TMC5262_DEDGE_SHIFT                         29
#define TMC5262_DEDGE_FIELD                         ((RegisterField) {TMC5262_DEDGE_MASK, TMC5262_DEDGE_SHIFT, TMC5262_CHOPCONF, false})
#define TMC5262_SEMIN_MASK                          0x0000000F
#define TMC5262_SEMIN_SHIFT                         0
#define TMC5262_SEMIN_FIELD                         ((RegisterField) {TMC5262_SEMIN_MASK, TMC5262_SEMIN_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SEUP_MASK                           0x00000060
#define TMC5262_SEUP_SHIFT                          5
#define TMC5262_SEUP_FIELD                          ((RegisterField) {TMC5262_SEUP_MASK, TMC5262_SEUP_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SEMAX_MASK                          0x00000F00
#define TMC5262_SEMAX_SHIFT                         8
#define TMC5262_SEMAX_FIELD                         ((RegisterField) {TMC5262_SEMAX_MASK, TMC5262_SEMAX_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SEDN_MASK                           0x00007000
#define TMC5262_SEDN_SHIFT                          12
#define TMC5262_SEDN_FIELD                          ((RegisterField) {TMC5262_SEDN_MASK, TMC5262_SEDN_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SEIMIN_MASK                         0x00008000
#define TMC5262_SEIMIN_SHIFT                        15
#define TMC5262_SEIMIN_FIELD                        ((RegisterField) {TMC5262_SEIMIN_MASK, TMC5262_SEIMIN_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SGT_MASK                            0x007F0000
#define TMC5262_SGT_SHIFT                           16
#define TMC5262_SGT_FIELD                           ((RegisterField) {TMC5262_SGT_MASK, TMC5262_SGT_SHIFT, TMC5262_COOLCONF, true})
#define TMC5262_THIGH_SG_OFF_MASK                   0x00800000
#define TMC5262_THIGH_SG_OFF_SHIFT                  23
#define TMC5262_THIGH_SG_OFF_FIELD                  ((RegisterField) {TMC5262_THIGH_SG_OFF_MASK, TMC5262_THIGH_SG_OFF_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SFILT_MASK                          0x01000000
#define TMC5262_SFILT_SHIFT                         24
#define TMC5262_SFILT_FIELD                         ((RegisterField) {TMC5262_SFILT_MASK, TMC5262_SFILT_SHIFT, TMC5262_COOLCONF, false})
#define TMC5262_SG_RESULT_MASK                      0x000003FF
#define TMC5262_SG_RESULT_SHIFT                     0
#define TMC5262_SG_RESULT_FIELD                     ((RegisterField) {TMC5262_SG_RESULT_MASK, TMC5262_SG_RESULT_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_SEQ_STOPPED_MASK                    0x00000400
#define TMC5262_SEQ_STOPPED_SHIFT                   10
#define TMC5262_SEQ_STOPPED_FIELD                   ((RegisterField) {TMC5262_SEQ_STOPPED_MASK, TMC5262_SEQ_STOPPED_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_OV_MASK                             0x00000800
#define TMC5262_OV_SHIFT                            11
#define TMC5262_OV_FIELD                            ((RegisterField) {TMC5262_OV_MASK, TMC5262_OV_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_S2VSA_MASK                          0x00001000
#define TMC5262_S2VSA_SHIFT                         12
#define TMC5262_S2VSA_FIELD                         ((RegisterField) {TMC5262_S2VSA_MASK, TMC5262_S2VSA_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_S2VSB_MASK                          0x00002000
#define TMC5262_S2VSB_SHIFT                         13
#define TMC5262_S2VSB_FIELD                         ((RegisterField) {TMC5262_S2VSB_MASK, TMC5262_S2VSB_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_STEALTH_MASK                        0x00004000
#define TMC5262_STEALTH_SHIFT                       14
#define TMC5262_STEALTH_FIELD                       ((RegisterField) {TMC5262_STEALTH_MASK, TMC5262_STEALTH_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_CS_ACTUAL_MASK                      0x00FF0000
#define TMC5262_CS_ACTUAL_SHIFT                     16
#define TMC5262_CS_ACTUAL_FIELD                     ((RegisterField) {TMC5262_CS_ACTUAL_MASK, TMC5262_CS_ACTUAL_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_STALLGUARD_MASK                     0x01000000
#define TMC5262_STALLGUARD_SHIFT                    24
#define TMC5262_STALLGUARD_FIELD                    ((RegisterField) {TMC5262_STALLGUARD_MASK, TMC5262_STALLGUARD_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_OT_MASK                             0x02000000
#define TMC5262_OT_SHIFT                            25
#define TMC5262_OT_FIELD                            ((RegisterField) {TMC5262_OT_MASK, TMC5262_OT_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_OTPW_MASK                           0x04000000
#define TMC5262_OTPW_SHIFT                          26
#define TMC5262_OTPW_FIELD                          ((RegisterField) {TMC5262_OTPW_MASK, TMC5262_OTPW_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_S2GA_MASK                           0x08000000
#define TMC5262_S2GA_SHIFT                          27
#define TMC5262_S2GA_FIELD                          ((RegisterField) {TMC5262_S2GA_MASK, TMC5262_S2GA_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_S2GB_MASK                           0x10000000
#define TMC5262_S2GB_SHIFT                          28
#define TMC5262_S2GB_FIELD                          ((RegisterField) {TMC5262_S2GB_MASK, TMC5262_S2GB_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_OLA_MASK                            0x20000000
#define TMC5262_OLA_SHIFT                           29
#define TMC5262_OLA_FIELD                           ((RegisterField) {TMC5262_OLA_MASK, TMC5262_OLA_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_OLB_MASK                            0x40000000
#define TMC5262_OLB_SHIFT                           30
#define TMC5262_OLB_FIELD                           ((RegisterField) {TMC5262_OLB_MASK, TMC5262_OLB_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_STST_MASK                           0x80000000
#define TMC5262_STST_SHIFT                          31
#define TMC5262_STST_FIELD                          ((RegisterField) {TMC5262_STST_MASK, TMC5262_STST_SHIFT, TMC5262_DRV_STATUS, false})
#define TMC5262_PWM_FREQ_MASK                       0x0000000F
#define TMC5262_PWM_FREQ_SHIFT                      0
#define TMC5262_PWM_FREQ_FIELD                      ((RegisterField) {TMC5262_PWM_FREQ_MASK, TMC5262_PWM_FREQ_SHIFT, TMC5262_PWMCONF, false})
#define TMC5262_FREEWHEEL_MASK                      0x00000030
#define TMC5262_FREEWHEEL_SHIFT                     4
#define TMC5262_FREEWHEEL_FIELD                     ((RegisterField) {TMC5262_FREEWHEEL_MASK, TMC5262_FREEWHEEL_SHIFT, TMC5262_PWMCONF, false})
#define TMC5262_OL_THRSH_MASK                       0x000000C0
#define TMC5262_OL_THRSH_SHIFT                      6
#define TMC5262_OL_THRSH_FIELD                      ((RegisterField) {TMC5262_OL_THRSH_MASK, TMC5262_OL_THRSH_SHIFT, TMC5262_PWMCONF, false})
#define TMC5262_SD_ON_MEAS_LO_MASK                  0x0000F000
#define TMC5262_SD_ON_MEAS_LO_SHIFT                 12
#define TMC5262_SD_ON_MEAS_LO_FIELD                 ((RegisterField) {TMC5262_SD_ON_MEAS_LO_MASK, TMC5262_SD_ON_MEAS_LO_SHIFT, TMC5262_PWMCONF, false})
#define TMC5262_SD_ON_MEAS_HI_MASK                  0x000F0000
#define TMC5262_SD_ON_MEAS_HI_SHIFT                 16
#define TMC5262_SD_ON_MEAS_HI_FIELD                 ((RegisterField) {TMC5262_SD_ON_MEAS_HI_MASK, TMC5262_SD_ON_MEAS_HI_SHIFT, TMC5262_PWMCONF, false})
#define TMC5262_SD_ON_MEAS_MASK                     0x000FF000
#define TMC5262_SD_ON_MEAS_SHIFT                    12
#define TMC5262_SD_ON_MEAS_FIELD                 	((RegisterField) {TMC5262_SD_ON_MEAS_MASK, TMC5262_SD_ON_MEAS_SHIFT, TMC5262_PWMCONF, false})

#endif
