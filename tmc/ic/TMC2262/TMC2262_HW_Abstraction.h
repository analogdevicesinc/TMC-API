/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC2262_HW_ABSTRACTION
#define TMC2262_HW_ABSTRACTION

// Constants

#define TMC2262_REGISTER_COUNT   128
#define TMC2262_MOTORS           1
#define TMC2262_WRITE_BIT        0x80
#define TMC2262_ADDRESS_MASK     0x7F
#define TMC2262_MAX_ACCELERATION 65535

// ramp modes (Register TMC2262_RAMPMODE)
#define TMC2262_MODE_POSITION  0
#define TMC2262_MODE_VELPOS    1
#define TMC2262_MODE_VELNEG    2
#define TMC2262_MODE_HOLD      3

// limit switch mode bits (Register TMC2262_SWMODE)
#define TMC2262_SW_STOPL_ENABLE    0x0001
#define TMC2262_SW_STOPR_ENABLE    0x0002
#define TMC2262_SW_STOPL_POLARITY  0x0004
#define TMC2262_SW_STOPR_POLARITY  0x0008
#define TMC2262_SW_SWAP_LR         0x0010
#define TMC2262_SW_LATCH_L_ACT     0x0020
#define TMC2262_SW_LATCH_L_INACT   0x0040
#define TMC2262_SW_LATCH_R_ACT     0x0080
#define TMC2262_SW_LATCH_R_INACT   0x0100
#define TMC2262_SW_LATCH_ENC       0x0200
#define TMC2262_SW_SG_STOP         0x0400
#define TMC2262_SW_SOFTSTOP        0x0800

// Status bits (Register TMC2262_RAMPSTAT)
#define TMC2262_RS_STOPL          0x0001
#define TMC2262_RS_STOPR          0x0002
#define TMC2262_RS_LATCHL         0x0004
#define TMC2262_RS_LATCHR         0x0008
#define TMC2262_RS_EV_STOPL       0x0010
#define TMC2262_RS_EV_STOPR       0x0020
#define TMC2262_RS_EV_STOP_SG     0x0040
#define TMC2262_RS_EV_POSREACHED  0x0080
#define TMC2262_RS_VELREACHED     0x0100
#define TMC2262_RS_POSREACHED     0x0200
#define TMC2262_RS_VZERO          0x0400
#define TMC2262_RS_ZEROWAIT       0x0800
#define TMC2262_RS_SECONDMOVE     0x1000
#define TMC2262_RS_SG             0x2000

// Encoderbits (Register TMC2262_ENCMODE)
#define TMC2262_EM_DECIMAL     0x0400
#define TMC2262_EM_LATCH_XACT  0x0200
#define TMC2262_EM_CLR_XENC    0x0100
#define TMC2262_EM_NEG_EDGE    0x0080
#define TMC2262_EM_POS_EDGE    0x0040
#define TMC2262_EM_CLR_ONCE    0x0020
#define TMC2262_EM_CLR_CONT    0x0010
#define TMC2262_EM_IGNORE_AB   0x0008
#define TMC2262_EM_POL_N       0x0004
#define TMC2262_EM_POL_B       0x0002
#define TMC2262_EM_POL_A       0x0001


// Register fields in TMC2262

#define TMC2262_GCONF                      0x00
#define TMC2262_GSTAT                      0x01
#define TMC2262_DIAG_CONF                  0x02
#define TMC2262_DIAG_DAC_CONF              0x03
#define TMC2262_IOIN                       0x04
#define TMC2262_DRV_CONF                   0x0A
#define TMC2262_PLL                        0x0B
#define TMC2262_IHOLD_IRUN                 0x10
#define TMC2262_TPOWERDOWN                 0x11
#define TMC2262_TSTEP                      0x12
#define TMC2262_TPWMTHRS                   0x13
#define TMC2262_TCOOLTHRS                  0x14
#define TMC2262_THIGH                      0x15
#define TMC2262_TSGP_LOW_VEL_THRS          0x16
#define TMC2262_T_RCOIL_MEAS               0x17
#define TMC2262_TUDCSTEP                   0x18
#define TMC2262_UDC_CONF                   0x19
#define TMC2262_STEPS_LOST                 0x1A
#define TMC2262_SW_MODE                    0x34
#define TMC2262_SG_SEQ_STOP_STAT           0x35
#define TMC2262_ENCMODE                    0x38
#define TMC2262_X_ENC                      0x39
#define TMC2262_ENC_CONST                  0x3A
#define TMC2262_ENC_STATUS                 0x3B
#define TMC2262_ENC_LATCH                  0x3C
#define TMC2262_ENC_DEVIATION              0x3D
#define TMC2262_CURRENT_PI_REG             0x40
#define TMC2262_ANGLE_PI_REG               0x41
#define TMC2262_CUR_ANGLE_LIMIT            0x42
#define TMC2262_ANGLE_LOWER_LIMIT          0x43
#define TMC2262_CUR_ANGLE_MEAS             0x44
#define TMC2262_PI_RESULTS                 0x45
#define TMC2262_COIL_INDUCT                0x46
#define TMC2262_R_COIL                     0x47
#define TMC2262_R_COIL_USER                0x48
#define TMC2262_SGP_CONF                   0x49
#define TMC2262_SGP_IND_2_3                0x4A
#define TMC2262_SGP_IND_0_1                0x4B
#define TMC2262_INDUCTANCE_VOLTAGE         0x4C
#define TMC2262_SGP_BEMF                   0x4D
#define TMC2262_COOLSTEPPLUS_CONF          0x4E
#define TMC2262_COOLSTEPPLUS_PI_REG        0x4F
#define TMC2262_COOLSTEPPLUS_PI_DOWN       0x50
#define TMC2262_COOLSTEPPLUS_RESERVE_CONF  0x51
#define TMC2262_COOLSTEPPLUS_LOAD_RESERVE  0x52
#define TMC2262_TSTEP_VELOCITY             0x53
#define TMC2262_ADC_VSUPPLY_TEMP           0x58
#define TMC2262_ADC_I                      0x59
#define TMC2262_OTW_OV_VTH                 0x5A
#define TMC2262_MSLUT__                    0x60
//#define TMC2262_MSLUT__                    0x61
//#define TMC2262_MSLUT__                    0x62
//#define TMC2262_MSLUT__                    0x63
//#define TMC2262_MSLUT__                    0x64
//#define TMC2262_MSLUT__                    0x65
//#define TMC2262_MSLUT__                    0x66
//#define TMC2262_MSLUT__                    0x67
#define TMC2262_MSLUTSEL                   0x68
#define TMC2262_MSLUTSTART                 0x69
#define TMC2262_MSCNT                      0x6A
#define TMC2262_MSCURACT                   0x6B
#define TMC2262_CHOPCONF                   0x6C
#define TMC2262_COOLCONF                   0x6D
#define TMC2262_DRV_STATUS                 0x6F
#define TMC2262_PWMCONF                    0x70


// Fields in TMC2262

#define TMC2262_FAST_STANDSTILL_MASK                0x00000001
#define TMC2262_FAST_STANDSTILL_SHIFT               0
#define TMC2262_FAST_STANDSTILL_FIELD               ((RegisterField) {TMC2262_FAST_STANDSTILL_MASK, TMC2262_FAST_STANDSTILL_SHIFT, TMC2262_GCONF, false})
#define TMC2262_EN_STEALTHCHOP_MASK                 0x00000002
#define TMC2262_EN_STEALTHCHOP_SHIFT                1
#define TMC2262_EN_STEALTHCHOP_FIELD                ((RegisterField) {TMC2262_EN_STEALTHCHOP_MASK, TMC2262_EN_STEALTHCHOP_SHIFT, TMC2262_GCONF, false})
#define TMC2262_MULTISTEP_FILT_MASK                 0x00000004
#define TMC2262_MULTISTEP_FILT_SHIFT                2
#define TMC2262_MULTISTEP_FILT_FIELD                ((RegisterField) {TMC2262_MULTISTEP_FILT_MASK, TMC2262_MULTISTEP_FILT_SHIFT, TMC2262_GCONF, false})
#define TMC2262_SHAFT_MASK                          0x00000008
#define TMC2262_SHAFT_SHIFT                         3
#define TMC2262_SHAFT_FIELD                         ((RegisterField) {TMC2262_SHAFT_MASK, TMC2262_SHAFT_SHIFT, TMC2262_GCONF, false})
#define TMC2262_SMALL_HYSTERESIS_MASK               0x00000010
#define TMC2262_SMALL_HYSTERESIS_SHIFT              4
#define TMC2262_SMALL_HYSTERESIS_FIELD              ((RegisterField) {TMC2262_SMALL_HYSTERESIS_MASK, TMC2262_SMALL_HYSTERESIS_SHIFT, TMC2262_GCONF, false})
#define TMC2262_STOP_ENABLE_MASK                    0x00000020
#define TMC2262_STOP_ENABLE_SHIFT                   5
#define TMC2262_STOP_ENABLE_FIELD                   ((RegisterField) {TMC2262_STOP_ENABLE_MASK, TMC2262_STOP_ENABLE_SHIFT, TMC2262_GCONF, false})
#define TMC2262_DIRECT_MODE_MASK                    0x00000040
#define TMC2262_DIRECT_MODE_SHIFT                   6
#define TMC2262_DIRECT_MODE_FIELD                   ((RegisterField) {TMC2262_DIRECT_MODE_MASK, TMC2262_DIRECT_MODE_SHIFT, TMC2262_GCONF, false})
#define TMC2262_LENGTH_STEPPULSE_MASK               0x00000F00
#define TMC2262_LENGTH_STEPPULSE_SHIFT              8
#define TMC2262_LENGTH_STEPPULSE_FIELD              ((RegisterField) {TMC2262_LENGTH_STEPPULSE_MASK, TMC2262_LENGTH_STEPPULSE_SHIFT, TMC2262_GCONF, false})
#define TMC2262_OV_NN_MASK                          0x00001000
#define TMC2262_OV_NN_SHIFT                         12
#define TMC2262_OV_NN_FIELD                         ((RegisterField) {TMC2262_OV_NN_MASK, TMC2262_OV_NN_SHIFT, TMC2262_GCONF, false})
#define TMC2262_RESET_MASK                          0x00000001
#define TMC2262_RESET_SHIFT                         0
#define TMC2262_RESET_FIELD                         ((RegisterField) {TMC2262_RESET_MASK, TMC2262_RESET_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_DRV_ERR_MASK                        0x00000002
#define TMC2262_DRV_ERR_SHIFT                       1
#define TMC2262_DRV_ERR_FIELD                       ((RegisterField) {TMC2262_DRV_ERR_MASK, TMC2262_DRV_ERR_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_UV_CP_MASK                          0x00000004
#define TMC2262_UV_CP_SHIFT                         2
#define TMC2262_UV_CP_FIELD                         ((RegisterField) {TMC2262_UV_CP_MASK, TMC2262_UV_CP_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_REGISTER_RESET_MASK                 0x00000008
#define TMC2262_REGISTER_RESET_SHIFT                3
#define TMC2262_REGISTER_RESET_FIELD                ((RegisterField) {TMC2262_REGISTER_RESET_MASK, TMC2262_REGISTER_RESET_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_VM_UVLO_MASK                        0x00000010
#define TMC2262_VM_UVLO_SHIFT                       4
#define TMC2262_VM_UVLO_FIELD                       ((RegisterField) {TMC2262_VM_UVLO_MASK, TMC2262_VM_UVLO_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_VCCIO_UV_MASK                       0x00000020
#define TMC2262_VCCIO_UV_SHIFT                      5
#define TMC2262_VCCIO_UV_FIELD                      ((RegisterField) {TMC2262_VCCIO_UV_MASK, TMC2262_VCCIO_UV_SHIFT, TMC2262_GSTAT, false})
#define TMC2262_DIAG0_ERROR_MASK                    0x00000001
#define TMC2262_DIAG0_ERROR_SHIFT                   0
#define TMC2262_DIAG0_ERROR_FIELD                   ((RegisterField) {TMC2262_DIAG0_ERROR_MASK, TMC2262_DIAG0_ERROR_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_OTPW_MASK                     0x00000002
#define TMC2262_DIAG0_OTPW_SHIFT                    1
#define TMC2262_DIAG0_OTPW_FIELD                    ((RegisterField) {TMC2262_DIAG0_OTPW_MASK, TMC2262_DIAG0_OTPW_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_STALL_MASK                    0x00000004
#define TMC2262_DIAG0_STALL_SHIFT                   2
#define TMC2262_DIAG0_STALL_FIELD                   ((RegisterField) {TMC2262_DIAG0_STALL_MASK, TMC2262_DIAG0_STALL_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_INDEX_MASK                    0x00000008
#define TMC2262_DIAG0_INDEX_SHIFT                   3
#define TMC2262_DIAG0_INDEX_FIELD                   ((RegisterField) {TMC2262_DIAG0_INDEX_MASK, TMC2262_DIAG0_INDEX_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_XCOMP_MASK                    0x00000040
#define TMC2262_DIAG0_XCOMP_SHIFT                   6
#define TMC2262_DIAG0_XCOMP_FIELD                   ((RegisterField) {TMC2262_DIAG0_XCOMP_MASK, TMC2262_DIAG0_XCOMP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_OV_MASK                       0x00000080
#define TMC2262_DIAG0_OV_SHIFT                      7
#define TMC2262_DIAG0_OV_FIELD                      ((RegisterField) {TMC2262_DIAG0_OV_MASK, TMC2262_DIAG0_OV_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_DCUSTEP_MASK                  0x00000100
#define TMC2262_DIAG0_DCUSTEP_SHIFT                 8
#define TMC2262_DIAG0_DCUSTEP_FIELD                 ((RegisterField) {TMC2262_DIAG0_DCUSTEP_MASK, TMC2262_DIAG0_DCUSTEP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_EV_STOP_SG_MASK               0x00000400
#define TMC2262_DIAG0_EV_STOP_SG_SHIFT              10
#define TMC2262_DIAG0_EV_STOP_SG_FIELD              ((RegisterField) {TMC2262_DIAG0_EV_STOP_SG_MASK, TMC2262_DIAG0_EV_STOP_SG_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_EV_N_DEVIATION_MASK           0x00001000
#define TMC2262_DIAG0_EV_N_DEVIATION_SHIFT          12
#define TMC2262_DIAG0_EV_N_DEVIATION_FIELD          ((RegisterField) {TMC2262_DIAG0_EV_N_DEVIATION_MASK, TMC2262_DIAG0_EV_N_DEVIATION_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_ERROR_MASK                    0x00002000
#define TMC2262_DIAG1_ERROR_SHIFT                   13
#define TMC2262_DIAG1_ERROR_FIELD                   ((RegisterField) {TMC2262_DIAG1_ERROR_MASK, TMC2262_DIAG1_ERROR_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_OTPW_MASK                     0x00004000
#define TMC2262_DIAG1_OTPW_SHIFT                    14
#define TMC2262_DIAG1_OTPW_FIELD                    ((RegisterField) {TMC2262_DIAG1_OTPW_MASK, TMC2262_DIAG1_OTPW_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_STALL_MASK                    0x00008000
#define TMC2262_DIAG1_STALL_SHIFT                   15
#define TMC2262_DIAG1_STALL_FIELD                   ((RegisterField) {TMC2262_DIAG1_STALL_MASK, TMC2262_DIAG1_STALL_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_INDEX_MASK                    0x00010000
#define TMC2262_DIAG1_INDEX_SHIFT                   16
#define TMC2262_DIAG1_INDEX_FIELD                   ((RegisterField) {TMC2262_DIAG1_INDEX_MASK, TMC2262_DIAG1_INDEX_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_OV_MASK                       0x00100000
#define TMC2262_DIAG1_OV_SHIFT                      20
#define TMC2262_DIAG1_OV_FIELD                      ((RegisterField) {TMC2262_DIAG1_OV_MASK, TMC2262_DIAG1_OV_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_UDCSTEP_MASK                  0x00200000
#define TMC2262_DIAG1_UDCSTEP_SHIFT                 21
#define TMC2262_DIAG1_UDCSTEP_FIELD                 ((RegisterField) {TMC2262_DIAG1_UDCSTEP_MASK, TMC2262_DIAG1_UDCSTEP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_EV_STOP_SG_MASK               0x00800000
#define TMC2262_DIAG1_EV_STOP_SG_SHIFT              23
#define TMC2262_DIAG1_EV_STOP_SG_FIELD              ((RegisterField) {TMC2262_DIAG1_EV_STOP_SG_MASK, TMC2262_DIAG1_EV_STOP_SG_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_EV_N_DEVIATION_MASK           0x02000000
#define TMC2262_DIAG1_EV_N_DEVIATION_SHIFT          25
#define TMC2262_DIAG1_EV_N_DEVIATION_FIELD          ((RegisterField) {TMC2262_DIAG1_EV_N_DEVIATION_MASK, TMC2262_DIAG1_EV_N_DEVIATION_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_NOD_PP_MASK                   0x10000000
#define TMC2262_DIAG0_NOD_PP_SHIFT                  28
#define TMC2262_DIAG0_NOD_PP_FIELD                  ((RegisterField) {TMC2262_DIAG0_NOD_PP_MASK, TMC2262_DIAG0_NOD_PP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_INVPP_MASK                    0x20000000
#define TMC2262_DIAG0_INVPP_SHIFT                   29
#define TMC2262_DIAG0_INVPP_FIELD                   ((RegisterField) {TMC2262_DIAG0_INVPP_MASK, TMC2262_DIAG0_INVPP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_NOD_PP_MASK                   0x40000000
#define TMC2262_DIAG1_NOD_PP_SHIFT                  30
#define TMC2262_DIAG1_NOD_PP_FIELD                  ((RegisterField) {TMC2262_DIAG1_NOD_PP_MASK, TMC2262_DIAG1_NOD_PP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG1_INVPP_MASK                    0x80000000
#define TMC2262_DIAG1_INVPP_SHIFT                   31
#define TMC2262_DIAG1_INVPP_FIELD                   ((RegisterField) {TMC2262_DIAG1_INVPP_MASK, TMC2262_DIAG1_INVPP_SHIFT, TMC2262_DIAG_CONF, false})
#define TMC2262_DIAG0_DAC_EN_MASK                   0x00000001
#define TMC2262_DIAG0_DAC_EN_SHIFT                  0
#define TMC2262_DIAG0_DAC_EN_FIELD                  ((RegisterField) {TMC2262_DIAG0_DAC_EN_MASK, TMC2262_DIAG0_DAC_EN_SHIFT, TMC2262_DIAG_DAC_CONF, false})
#define TMC2262_DIAG0_DAC_SEL_MASK                  0x000001F0
#define TMC2262_DIAG0_DAC_SEL_SHIFT                 4
#define TMC2262_DIAG0_DAC_SEL_FIELD                 ((RegisterField) {TMC2262_DIAG0_DAC_SEL_MASK, TMC2262_DIAG0_DAC_SEL_SHIFT, TMC2262_DIAG_DAC_CONF, false})
#define TMC2262_DIAG1_DAC_EN_MASK                   0x00001000
#define TMC2262_DIAG1_DAC_EN_SHIFT                  12
#define TMC2262_DIAG1_DAC_EN_FIELD                  ((RegisterField) {TMC2262_DIAG1_DAC_EN_MASK, TMC2262_DIAG1_DAC_EN_SHIFT, TMC2262_DIAG_DAC_CONF, false})
#define TMC2262_DIAG1_DAC_SEL_MASK                  0x001F0000
#define TMC2262_DIAG1_DAC_SEL_SHIFT                 16
#define TMC2262_DIAG1_DAC_SEL_FIELD                 ((RegisterField) {TMC2262_DIAG1_DAC_SEL_MASK, TMC2262_DIAG1_DAC_SEL_SHIFT, TMC2262_DIAG_DAC_CONF, false})
#define TMC2262_STEP_MASK                           0x00000001
#define TMC2262_STEP_SHIFT                          0
#define TMC2262_STEP_FIELD                          ((RegisterField) {TMC2262_STEP_MASK, TMC2262_STEP_SHIFT, TMC2262_IOIN, false})
#define TMC2262_DIR_MASK                            0x00000002
#define TMC2262_DIR_SHIFT                           1
#define TMC2262_DIR_FIELD                           ((RegisterField) {TMC2262_DIR_MASK, TMC2262_DIR_SHIFT, TMC2262_IOIN, false})
#define TMC2262_ENCB_MASK                           0x00000004
#define TMC2262_ENCB_SHIFT                          2
#define TMC2262_ENCB_FIELD                          ((RegisterField) {TMC2262_ENCB_MASK, TMC2262_ENCB_SHIFT, TMC2262_IOIN, false})
#define TMC2262_ENCA_MASK                           0x00000008
#define TMC2262_ENCA_SHIFT                          3
#define TMC2262_ENCA_FIELD                          ((RegisterField) {TMC2262_ENCA_MASK, TMC2262_ENCA_SHIFT, TMC2262_IOIN, false})
#define TMC2262_DRV_ENN_MASK                        0x00000010
#define TMC2262_DRV_ENN_SHIFT                       4
#define TMC2262_DRV_ENN_FIELD                       ((RegisterField) {TMC2262_DRV_ENN_MASK, TMC2262_DRV_ENN_SHIFT, TMC2262_IOIN, false})
#define TMC2262_ENCN_MASK                           0x00000020
#define TMC2262_ENCN_SHIFT                          5
#define TMC2262_ENCN_FIELD                          ((RegisterField) {TMC2262_ENCN_MASK, TMC2262_ENCN_SHIFT, TMC2262_IOIN, false})
#define TMC2262_RESERVED_MASK                       0x00000080
#define TMC2262_RESERVED_SHIFT                      7
#define TMC2262_RESERVED_FIELD                      ((RegisterField) {TMC2262_RESERVED_MASK, TMC2262_RESERVED_SHIFT, TMC2262_IOIN, false})
#define TMC2262_EXT_RES_DET_MASK                    0x00002000
#define TMC2262_EXT_RES_DET_SHIFT                   13
#define TMC2262_EXT_RES_DET_FIELD                   ((RegisterField) {TMC2262_EXT_RES_DET_MASK, TMC2262_EXT_RES_DET_SHIFT, TMC2262_IOIN, false})
#define TMC2262_EXT_CLK_MASK                        0x00004000
#define TMC2262_EXT_CLK_SHIFT                       14
#define TMC2262_EXT_CLK_FIELD                       ((RegisterField) {TMC2262_EXT_CLK_MASK, TMC2262_EXT_CLK_SHIFT, TMC2262_IOIN, false})
#define TMC2262_SILICON_RV_MASK                     0x00070000
#define TMC2262_SILICON_RV_SHIFT                    16
#define TMC2262_SILICON_RV_FIELD                    ((RegisterField) {TMC2262_SILICON_RV_MASK, TMC2262_SILICON_RV_SHIFT, TMC2262_IOIN, false})
#define TMC2262_CURRENT_RANGE_MASK                  0x00000003
#define TMC2262_CURRENT_RANGE_SHIFT                 0
#define TMC2262_CURRENT_RANGE_FIELD                 ((RegisterField) {TMC2262_CURRENT_RANGE_MASK, TMC2262_CURRENT_RANGE_SHIFT, TMC2262_DRV_CONF, false})
#define TMC2262_CURRENT_RANGE_SCALE_MASK            0x0000000C
#define TMC2262_CURRENT_RANGE_SCALE_SHIFT           2
#define TMC2262_CURRENT_RANGE_SCALE_FIELD           ((RegisterField) {TMC2262_CURRENT_RANGE_SCALE_MASK, TMC2262_CURRENT_RANGE_SCALE_SHIFT, TMC2262_DRV_CONF, false})
#define TMC2262_SLOPE_CONTROL_MASK                  0x00000030
#define TMC2262_SLOPE_CONTROL_SHIFT                 4
#define TMC2262_SLOPE_CONTROL_FIELD                 ((RegisterField) {TMC2262_SLOPE_CONTROL_MASK, TMC2262_SLOPE_CONTROL_SHIFT, TMC2262_DRV_CONF, false})
#define TMC2262_COMMIT_MASK                         0x00000001
#define TMC2262_COMMIT_SHIFT                        0
#define TMC2262_COMMIT_FIELD                        ((RegisterField) {TMC2262_COMMIT_MASK, TMC2262_COMMIT_SHIFT, TMC2262_PLL, false})
#define TMC2262_EXT_NOT_INT_MASK                    0x00000002
#define TMC2262_EXT_NOT_INT_SHIFT                   1
#define TMC2262_EXT_NOT_INT_FIELD                   ((RegisterField) {TMC2262_EXT_NOT_INT_MASK, TMC2262_EXT_NOT_INT_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLK_SYS_SEL_MASK                    0x00000004
#define TMC2262_CLK_SYS_SEL_SHIFT                   2
#define TMC2262_CLK_SYS_SEL_FIELD                   ((RegisterField) {TMC2262_CLK_SYS_SEL_MASK, TMC2262_CLK_SYS_SEL_SHIFT, TMC2262_PLL, false})
#define TMC2262_ADC_CLK_ENA_MASK                    0x00000008
#define TMC2262_ADC_CLK_ENA_SHIFT                   3
#define TMC2262_ADC_CLK_ENA_FIELD                   ((RegisterField) {TMC2262_ADC_CLK_ENA_MASK, TMC2262_ADC_CLK_ENA_SHIFT, TMC2262_PLL, false})
#define TMC2262_PWM_CLK_ENA_MASK                    0x00000010
#define TMC2262_PWM_CLK_ENA_SHIFT                   4
#define TMC2262_PWM_CLK_ENA_FIELD                   ((RegisterField) {TMC2262_PWM_CLK_ENA_MASK, TMC2262_PWM_CLK_ENA_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLOCK_DIVIDER_MASK                  0x000003E0
#define TMC2262_CLOCK_DIVIDER_SHIFT                 5
#define TMC2262_CLOCK_DIVIDER_FIELD                 ((RegisterField) {TMC2262_CLOCK_DIVIDER_MASK, TMC2262_CLOCK_DIVIDER_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLK_FSM_ENA_MASK                    0x00000400
#define TMC2262_CLK_FSM_ENA_SHIFT                   10
#define TMC2262_CLK_FSM_ENA_FIELD                   ((RegisterField) {TMC2262_CLK_FSM_ENA_MASK, TMC2262_CLK_FSM_ENA_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLK_1MO_TMO_MASK                    0x00001000
#define TMC2262_CLK_1MO_TMO_SHIFT                   12
#define TMC2262_CLK_1MO_TMO_FIELD                   ((RegisterField) {TMC2262_CLK_1MO_TMO_MASK, TMC2262_CLK_1MO_TMO_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLK_LOSS_MASK                       0x00002000
#define TMC2262_CLK_LOSS_SHIFT                      13
#define TMC2262_CLK_LOSS_FIELD                      ((RegisterField) {TMC2262_CLK_LOSS_MASK, TMC2262_CLK_LOSS_SHIFT, TMC2262_PLL, false})
#define TMC2262_CLK_IS_STUCK_MASK                   0x00004000
#define TMC2262_CLK_IS_STUCK_SHIFT                  14
#define TMC2262_CLK_IS_STUCK_FIELD                  ((RegisterField) {TMC2262_CLK_IS_STUCK_MASK, TMC2262_CLK_IS_STUCK_SHIFT, TMC2262_PLL, false})
#define TMC2262_PLL_LOCK_LOSS_MASK                  0x00008000
#define TMC2262_PLL_LOCK_LOSS_SHIFT                 15
#define TMC2262_PLL_LOCK_LOSS_FIELD                 ((RegisterField) {TMC2262_PLL_LOCK_LOSS_MASK, TMC2262_PLL_LOCK_LOSS_SHIFT, TMC2262_PLL, false})
#define TMC2262_IHOLD_MASK                          0x000000FF
#define TMC2262_IHOLD_SHIFT                         0
#define TMC2262_IHOLD_FIELD                         ((RegisterField) {TMC2262_IHOLD_MASK, TMC2262_IHOLD_SHIFT, TMC2262_IHOLD_IRUN, false})
#define TMC2262_IRUN_MASK                           0x0000FF00
#define TMC2262_IRUN_SHIFT                          8
#define TMC2262_IRUN_FIELD                          ((RegisterField) {TMC2262_IRUN_MASK, TMC2262_IRUN_SHIFT, TMC2262_IHOLD_IRUN, false})
#define TMC2262_IHOLDDELAY_MASK                     0x00FF0000
#define TMC2262_IHOLDDELAY_SHIFT                    16
#define TMC2262_IHOLDDELAY_FIELD                    ((RegisterField) {TMC2262_IHOLDDELAY_MASK, TMC2262_IHOLDDELAY_SHIFT, TMC2262_IHOLD_IRUN, false})
#define TMC2262_IRUNDELAY_MASK                      0x0F000000
#define TMC2262_IRUNDELAY_SHIFT                     24
#define TMC2262_IRUNDELAY_FIELD                     ((RegisterField) {TMC2262_IRUNDELAY_MASK, TMC2262_IRUNDELAY_SHIFT, TMC2262_IHOLD_IRUN, false})
#define TMC2262_TPOWERDOWN_MASK                     0x000000FF
#define TMC2262_TPOWERDOWN_SHIFT                    0
#define TMC2262_TPOWERDOWN_FIELD                    ((RegisterField) {TMC2262_TPOWERDOWN_MASK, TMC2262_TPOWERDOWN_SHIFT, TMC2262_TPOWERDOWN, false})
#define TMC2262_TSTEP_MASK                          0x000FFFFF
#define TMC2262_TSTEP_SHIFT                         0
#define TMC2262_TSTEP_FIELD                         ((RegisterField) {TMC2262_TSTEP_MASK, TMC2262_TSTEP_SHIFT, TMC2262_TSTEP, false})
#define TMC2262_TPWMTHRS_MASK                       0x000FFFFF
#define TMC2262_TPWMTHRS_SHIFT                      0
#define TMC2262_TPWMTHRS_FIELD                      ((RegisterField) {TMC2262_TPWMTHRS_MASK, TMC2262_TPWMTHRS_SHIFT, TMC2262_TPWMTHRS, false})
#define TMC2262_TCOOLTHRS_MASK                      0x000FFFFF
#define TMC2262_TCOOLTHRS_SHIFT                     0
#define TMC2262_TCOOLTHRS_FIELD                     ((RegisterField) {TMC2262_TCOOLTHRS_MASK, TMC2262_TCOOLTHRS_SHIFT, TMC2262_TCOOLTHRS, false})
#define TMC2262_THIGH_MASK                          0x000FFFFF
#define TMC2262_THIGH_SHIFT                         0
#define TMC2262_THIGH_FIELD                         ((RegisterField) {TMC2262_THIGH_MASK, TMC2262_THIGH_SHIFT, TMC2262_THIGH, false})
#define TMC2262_TSGP_LOW_VEL_THRS_MASK              0x000FFFFF
#define TMC2262_TSGP_LOW_VEL_THRS_SHIFT             0
#define TMC2262_TSGP_LOW_VEL_THRS_FIELD             ((RegisterField) {TMC2262_TSGP_LOW_VEL_THRS_MASK, TMC2262_TSGP_LOW_VEL_THRS_SHIFT, TMC2262_TSGP_LOW_VEL_THRS, false})
#define TMC2262_T_RCOIL_MEAS_MASK                   0x000FFFFF
#define TMC2262_T_RCOIL_MEAS_SHIFT                  0
#define TMC2262_T_RCOIL_MEAS_FIELD                  ((RegisterField) {TMC2262_T_RCOIL_MEAS_MASK, TMC2262_T_RCOIL_MEAS_SHIFT, TMC2262_T_RCOIL_MEAS, false})
#define TMC2262_TUDCSTEP_MASK                       0x000FFFFF
#define TMC2262_TUDCSTEP_SHIFT                      0
#define TMC2262_TUDCSTEP_FIELD                      ((RegisterField) {TMC2262_TUDCSTEP_MASK, TMC2262_TUDCSTEP_SHIFT, TMC2262_TUDCSTEP, false})
#define TMC2262_DECEL_THRS_MASK                     0x0000000F
#define TMC2262_DECEL_THRS_SHIFT                    0
#define TMC2262_DECEL_THRS_FIELD                    ((RegisterField) {TMC2262_DECEL_THRS_MASK, TMC2262_DECEL_THRS_SHIFT, TMC2262_UDC_CONF, false})
#define TMC2262_ACCEL_THRS_MASK                     0x000000F0
#define TMC2262_ACCEL_THRS_SHIFT                    4
#define TMC2262_ACCEL_THRS_FIELD                    ((RegisterField) {TMC2262_ACCEL_THRS_MASK, TMC2262_ACCEL_THRS_SHIFT, TMC2262_UDC_CONF, false})
#define TMC2262_UDC_ENABLE_MASK                     0x00000100
#define TMC2262_UDC_ENABLE_SHIFT                    8
#define TMC2262_UDC_ENABLE_FIELD                    ((RegisterField) {TMC2262_UDC_ENABLE_MASK, TMC2262_UDC_ENABLE_SHIFT, TMC2262_UDC_CONF, false})
#define TMC2262_STEPS_LOST_MASK                     0x000FFFFF
#define TMC2262_STEPS_LOST_SHIFT                    0
#define TMC2262_STEPS_LOST_FIELD                    ((RegisterField) {TMC2262_STEPS_LOST_MASK, TMC2262_STEPS_LOST_SHIFT, TMC2262_STEPS_LOST, true})
#define TMC2262_SG_STOP_MASK                        0x00000400
#define TMC2262_SG_STOP_SHIFT                       10
#define TMC2262_SG_STOP_FIELD                       ((RegisterField) {TMC2262_SG_STOP_MASK, TMC2262_SG_STOP_SHIFT, TMC2262_SW_MODE, false})
#define TMC2262_EVENT_STOP_SG_MASK                  0x00000040
#define TMC2262_EVENT_STOP_SG_SHIFT                 6
#define TMC2262_EVENT_STOP_SG_FIELD                 ((RegisterField) {TMC2262_EVENT_STOP_SG_MASK, TMC2262_EVENT_STOP_SG_SHIFT, TMC2262_SG_SEQ_STOP_STAT, false})
#define TMC2262_POL_A_MASK                          0x00000001
#define TMC2262_POL_A_SHIFT                         0
#define TMC2262_POL_A_FIELD                         ((RegisterField) {TMC2262_POL_A_MASK, TMC2262_POL_A_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_POL_B_MASK                          0x00000002
#define TMC2262_POL_B_SHIFT                         1
#define TMC2262_POL_B_FIELD                         ((RegisterField) {TMC2262_POL_B_MASK, TMC2262_POL_B_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_POL_N_MASK                          0x00000004
#define TMC2262_POL_N_SHIFT                         2
#define TMC2262_POL_N_FIELD                         ((RegisterField) {TMC2262_POL_N_MASK, TMC2262_POL_N_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_IGNORE_AB_MASK                      0x00000008
#define TMC2262_IGNORE_AB_SHIFT                     3
#define TMC2262_IGNORE_AB_FIELD                     ((RegisterField) {TMC2262_IGNORE_AB_MASK, TMC2262_IGNORE_AB_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_CLR_CONT_MASK                       0x00000010
#define TMC2262_CLR_CONT_SHIFT                      4
#define TMC2262_CLR_CONT_FIELD                      ((RegisterField) {TMC2262_CLR_CONT_MASK, TMC2262_CLR_CONT_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_CLR_ONCE_MASK                       0x00000020
#define TMC2262_CLR_ONCE_SHIFT                      5
#define TMC2262_CLR_ONCE_FIELD                      ((RegisterField) {TMC2262_CLR_ONCE_MASK, TMC2262_CLR_ONCE_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_POS_NEG_EDGE_MASK                   0x000000C0
#define TMC2262_POS_NEG_EDGE_SHIFT                  6
#define TMC2262_POS_NEG_EDGE_FIELD                  ((RegisterField) {TMC2262_POS_NEG_EDGE_MASK, TMC2262_POS_NEG_EDGE_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_CLR_ENC_X_MASK                      0x00000100
#define TMC2262_CLR_ENC_X_SHIFT                     8
#define TMC2262_CLR_ENC_X_FIELD                     ((RegisterField) {TMC2262_CLR_ENC_X_MASK, TMC2262_CLR_ENC_X_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_ENC_SEL_DECIMAL_MASK                0x00000400
#define TMC2262_ENC_SEL_DECIMAL_SHIFT               10
#define TMC2262_ENC_SEL_DECIMAL_FIELD               ((RegisterField) {TMC2262_ENC_SEL_DECIMAL_MASK, TMC2262_ENC_SEL_DECIMAL_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_NBEMF_ABN_SEL_MASK                  0x00000800
#define TMC2262_NBEMF_ABN_SEL_SHIFT                 11
#define TMC2262_NBEMF_ABN_SEL_FIELD                 ((RegisterField) {TMC2262_NBEMF_ABN_SEL_MASK, TMC2262_NBEMF_ABN_SEL_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_BEMF_HYST_MASK                      0x00007000
#define TMC2262_BEMF_HYST_SHIFT                     12
#define TMC2262_BEMF_HYST_FIELD                     ((RegisterField) {TMC2262_BEMF_HYST_MASK, TMC2262_BEMF_HYST_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_BEMF_BLANK_TIME_MASK                0x00FF0000
#define TMC2262_BEMF_BLANK_TIME_SHIFT               16
#define TMC2262_BEMF_BLANK_TIME_FIELD               ((RegisterField) {TMC2262_BEMF_BLANK_TIME_MASK, TMC2262_BEMF_BLANK_TIME_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_BEMF_FILTER_SEL_MASK                0x30000000
#define TMC2262_BEMF_FILTER_SEL_SHIFT               28
#define TMC2262_BEMF_FILTER_SEL_FIELD               ((RegisterField) {TMC2262_BEMF_FILTER_SEL_MASK, TMC2262_BEMF_FILTER_SEL_SHIFT, TMC2262_ENCMODE, false})
#define TMC2262_X_ENC_MASK                          0xFFFFFFFF
#define TMC2262_X_ENC_SHIFT                         0
#define TMC2262_X_ENC_FIELD                         ((RegisterField) {TMC2262_X_ENC_MASK, TMC2262_X_ENC_SHIFT, TMC2262_X_ENC, true})
#define TMC2262_ENC_CONST_MASK                      0xFFFFFFFF
#define TMC2262_ENC_CONST_SHIFT                     0
#define TMC2262_ENC_CONST_FIELD                     ((RegisterField) {TMC2262_ENC_CONST_MASK, TMC2262_ENC_CONST_SHIFT, TMC2262_ENC_CONST, true})
#define TMC2262_N_EVENT_MASK                        0x00000001
#define TMC2262_N_EVENT_SHIFT                       0
#define TMC2262_N_EVENT_FIELD                       ((RegisterField) {TMC2262_N_EVENT_MASK, TMC2262_N_EVENT_SHIFT, TMC2262_ENC_STATUS, false})
#define TMC2262_DEVIATION_WARN_MASK                 0x00000002
#define TMC2262_DEVIATION_WARN_SHIFT                1
#define TMC2262_DEVIATION_WARN_FIELD                ((RegisterField) {TMC2262_DEVIATION_WARN_MASK, TMC2262_DEVIATION_WARN_SHIFT, TMC2262_ENC_STATUS, false})
#define TMC2262_ENC_LATCH_MASK                      0xFFFFFFFF
#define TMC2262_ENC_LATCH_SHIFT                     0
#define TMC2262_ENC_LATCH_FIELD                     ((RegisterField) {TMC2262_ENC_LATCH_MASK, TMC2262_ENC_LATCH_SHIFT, TMC2262_ENC_LATCH, false})
#define TMC2262_ENC_DEVIATION_MASK                  0x000FFFFF
#define TMC2262_ENC_DEVIATION_SHIFT                 0
#define TMC2262_ENC_DEVIATION_FIELD                 ((RegisterField) {TMC2262_ENC_DEVIATION_MASK, TMC2262_ENC_DEVIATION_SHIFT, TMC2262_ENC_DEVIATION, false})
#define TMC2262_CUR_P_MASK                          0x00000FFF
#define TMC2262_CUR_P_SHIFT                         0
#define TMC2262_CUR_P_FIELD                         ((RegisterField) {TMC2262_CUR_P_MASK, TMC2262_CUR_P_SHIFT, TMC2262_CURRENT_PI_REG, false})
#define TMC2262_CUR_I_MASK                          0x03FF0000
#define TMC2262_CUR_I_SHIFT                         16
#define TMC2262_CUR_I_FIELD                         ((RegisterField) {TMC2262_CUR_I_MASK, TMC2262_CUR_I_SHIFT, TMC2262_CURRENT_PI_REG, false})
#define TMC2262_ANGLE_P_MASK                        0x00000FFF
#define TMC2262_ANGLE_P_SHIFT                       0
#define TMC2262_ANGLE_P_FIELD                       ((RegisterField) {TMC2262_ANGLE_P_MASK, TMC2262_ANGLE_P_SHIFT, TMC2262_ANGLE_PI_REG, false})
#define TMC2262_ANGLE_I_MASK                        0x03FF0000
#define TMC2262_ANGLE_I_SHIFT                       16
#define TMC2262_ANGLE_I_FIELD                       ((RegisterField) {TMC2262_ANGLE_I_MASK, TMC2262_ANGLE_I_SHIFT, TMC2262_ANGLE_PI_REG, false})
#define TMC2262_ANGLE_PI_LIMIT_MASK                 0x000003FF
#define TMC2262_ANGLE_PI_LIMIT_SHIFT                0
#define TMC2262_ANGLE_PI_LIMIT_FIELD                ((RegisterField) {TMC2262_ANGLE_PI_LIMIT_MASK, TMC2262_ANGLE_PI_LIMIT_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_ANGLE_PI_INT_POS_CLIP_MASK          0x00001000
#define TMC2262_ANGLE_PI_INT_POS_CLIP_SHIFT         12
#define TMC2262_ANGLE_PI_INT_POS_CLIP_FIELD         ((RegisterField) {TMC2262_ANGLE_PI_INT_POS_CLIP_MASK, TMC2262_ANGLE_PI_INT_POS_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_ANGLE_PI_INT_NEG_CLIP_MASK          0x00002000
#define TMC2262_ANGLE_PI_INT_NEG_CLIP_SHIFT         13
#define TMC2262_ANGLE_PI_INT_NEG_CLIP_FIELD         ((RegisterField) {TMC2262_ANGLE_PI_INT_NEG_CLIP_MASK, TMC2262_ANGLE_PI_INT_NEG_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_ANGLE_PI_POS_CLIP_MASK              0x00004000
#define TMC2262_ANGLE_PI_POS_CLIP_SHIFT             14
#define TMC2262_ANGLE_PI_POS_CLIP_FIELD             ((RegisterField) {TMC2262_ANGLE_PI_POS_CLIP_MASK, TMC2262_ANGLE_PI_POS_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_ANGLE_PI_NEG_CLIP_MASK              0x00008000
#define TMC2262_ANGLE_PI_NEG_CLIP_SHIFT             15
#define TMC2262_ANGLE_PI_NEG_CLIP_FIELD             ((RegisterField) {TMC2262_ANGLE_PI_NEG_CLIP_MASK, TMC2262_ANGLE_PI_NEG_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_CUR_PI_LIMIT_MASK                   0x0FFF0000
#define TMC2262_CUR_PI_LIMIT_SHIFT                  16
#define TMC2262_CUR_PI_LIMIT_FIELD                  ((RegisterField) {TMC2262_CUR_PI_LIMIT_MASK, TMC2262_CUR_PI_LIMIT_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_CUR_PI_INT_POS_CLIP_MASK            0x10000000
#define TMC2262_CUR_PI_INT_POS_CLIP_SHIFT           28
#define TMC2262_CUR_PI_INT_POS_CLIP_FIELD           ((RegisterField) {TMC2262_CUR_PI_INT_POS_CLIP_MASK, TMC2262_CUR_PI_INT_POS_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_CUR_PI_INT_NEG_CLIP_MASK            0x20000000
#define TMC2262_CUR_PI_INT_NEG_CLIP_SHIFT           29
#define TMC2262_CUR_PI_INT_NEG_CLIP_FIELD           ((RegisterField) {TMC2262_CUR_PI_INT_NEG_CLIP_MASK, TMC2262_CUR_PI_INT_NEG_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_CUR_PI_POS_CLIP_MASK                0x40000000
#define TMC2262_CUR_PI_POS_CLIP_SHIFT               30
#define TMC2262_CUR_PI_POS_CLIP_FIELD               ((RegisterField) {TMC2262_CUR_PI_POS_CLIP_MASK, TMC2262_CUR_PI_POS_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_CUR_PI_NEG_CLIP_MASK                0x80000000
#define TMC2262_CUR_PI_NEG_CLIP_SHIFT               31
#define TMC2262_CUR_PI_NEG_CLIP_FIELD               ((RegisterField) {TMC2262_CUR_PI_NEG_CLIP_MASK, TMC2262_CUR_PI_NEG_CLIP_SHIFT, TMC2262_CUR_ANGLE_LIMIT, false})
#define TMC2262_ANGLE_LOWER_I_LIMIT_MASK            0x000003FF
#define TMC2262_ANGLE_LOWER_I_LIMIT_SHIFT           0
#define TMC2262_ANGLE_LOWER_I_LIMIT_FIELD           ((RegisterField) {TMC2262_ANGLE_LOWER_I_LIMIT_MASK, TMC2262_ANGLE_LOWER_I_LIMIT_SHIFT, TMC2262_ANGLE_LOWER_LIMIT, false})
#define TMC2262_ANGLE_ERROR_MASK                    0x03FF0000
#define TMC2262_ANGLE_ERROR_SHIFT                   16
#define TMC2262_ANGLE_ERROR_FIELD                   ((RegisterField) {TMC2262_ANGLE_ERROR_MASK, TMC2262_ANGLE_ERROR_SHIFT, TMC2262_ANGLE_LOWER_LIMIT, true})
#define TMC2262_AMPL_MEAS_MASK                      0x00000FFF
#define TMC2262_AMPL_MEAS_SHIFT                     0
#define TMC2262_AMPL_MEAS_FIELD                     ((RegisterField) {TMC2262_AMPL_MEAS_MASK, TMC2262_AMPL_MEAS_SHIFT, TMC2262_CUR_ANGLE_MEAS, false})
#define TMC2262_ANGLE_MEAS_MASK                     0x03FF0000
#define TMC2262_ANGLE_MEAS_SHIFT                    16
#define TMC2262_ANGLE_MEAS_FIELD                    ((RegisterField) {TMC2262_ANGLE_MEAS_MASK, TMC2262_ANGLE_MEAS_SHIFT, TMC2262_CUR_ANGLE_MEAS, false})
#define TMC2262_PWM_CALC_MASK                       0x00001FFF
#define TMC2262_PWM_CALC_SHIFT                      0
#define TMC2262_PWM_CALC_FIELD                      ((RegisterField) {TMC2262_PWM_CALC_MASK, TMC2262_PWM_CALC_SHIFT, TMC2262_PI_RESULTS, true})
#define TMC2262_ANGLE_CORR_CALC_MASK                0x03FF0000
#define TMC2262_ANGLE_CORR_CALC_SHIFT               16
#define TMC2262_ANGLE_CORR_CALC_FIELD               ((RegisterField) {TMC2262_ANGLE_CORR_CALC_MASK, TMC2262_ANGLE_CORR_CALC_SHIFT, TMC2262_PI_RESULTS, true})
#define TMC2262_COIL_INDUCT_MASK                    0x00007FFF
#define TMC2262_COIL_INDUCT_SHIFT                   0
#define TMC2262_COIL_INDUCT_FIELD                   ((RegisterField) {TMC2262_COIL_INDUCT_MASK, TMC2262_COIL_INDUCT_SHIFT, TMC2262_COIL_INDUCT, false})
#define TMC2262_RCOIL_MANUAL_MASK                   0x00010000
#define TMC2262_RCOIL_MANUAL_SHIFT                  16
#define TMC2262_RCOIL_MANUAL_FIELD                  ((RegisterField) {TMC2262_RCOIL_MANUAL_MASK, TMC2262_RCOIL_MANUAL_SHIFT, TMC2262_COIL_INDUCT, false})
#define TMC2262_RCOIL_THERMAL_COUPLING_MASK         0x00020000
#define TMC2262_RCOIL_THERMAL_COUPLING_SHIFT        17
#define TMC2262_RCOIL_THERMAL_COUPLING_FIELD        ((RegisterField) {TMC2262_RCOIL_THERMAL_COUPLING_MASK, TMC2262_RCOIL_THERMAL_COUPLING_SHIFT, TMC2262_COIL_INDUCT, false})
#define TMC2262_R_COIL_AUTO_B_MASK                  0x00000FFF
#define TMC2262_R_COIL_AUTO_B_SHIFT                 0
#define TMC2262_R_COIL_AUTO_B_FIELD                 ((RegisterField) {TMC2262_R_COIL_AUTO_B_MASK, TMC2262_R_COIL_AUTO_B_SHIFT, TMC2262_R_COIL, false})
#define TMC2262_R_COIL_AUTO_A_MASK                  0x0FFF0000
#define TMC2262_R_COIL_AUTO_A_SHIFT                 16
#define TMC2262_R_COIL_AUTO_A_FIELD                 ((RegisterField) {TMC2262_R_COIL_AUTO_A_MASK, TMC2262_R_COIL_AUTO_A_SHIFT, TMC2262_R_COIL, false})
#define TMC2262_R_COIL_USER_B_MASK                  0x00000FFF
#define TMC2262_R_COIL_USER_B_SHIFT                 0
#define TMC2262_R_COIL_USER_B_FIELD                 ((RegisterField) {TMC2262_R_COIL_USER_B_MASK, TMC2262_R_COIL_USER_B_SHIFT, TMC2262_R_COIL_USER, false})
#define TMC2262_R_COIL_USER_A_MASK                  0x0FFF0000
#define TMC2262_R_COIL_USER_A_SHIFT                 16
#define TMC2262_R_COIL_USER_A_FIELD                 ((RegisterField) {TMC2262_R_COIL_USER_A_MASK, TMC2262_R_COIL_USER_A_SHIFT, TMC2262_R_COIL_USER, false})
#define TMC2262_SGP_THRS_MASK                       0x000001FF
#define TMC2262_SGP_THRS_SHIFT                      0
#define TMC2262_SGP_THRS_FIELD                      ((RegisterField) {TMC2262_SGP_THRS_MASK, TMC2262_SGP_THRS_SHIFT, TMC2262_SGP_CONF, true})
#define TMC2262_SGP_FILT_EN_MASK                    0x00001000
#define TMC2262_SGP_FILT_EN_SHIFT                   12
#define TMC2262_SGP_FILT_EN_FIELD                   ((RegisterField) {TMC2262_SGP_FILT_EN_MASK, TMC2262_SGP_FILT_EN_SHIFT, TMC2262_SGP_CONF, false})
#define TMC2262_SGP_LOW_VEL_FREEZE_MASK             0x00002000
#define TMC2262_SGP_LOW_VEL_FREEZE_SHIFT            13
#define TMC2262_SGP_LOW_VEL_FREEZE_FIELD            ((RegisterField) {TMC2262_SGP_LOW_VEL_FREEZE_MASK, TMC2262_SGP_LOW_VEL_FREEZE_SHIFT, TMC2262_SGP_CONF, false})
#define TMC2262_SGP_CLEAR_CUR_PI_MASK               0x00004000
#define TMC2262_SGP_CLEAR_CUR_PI_SHIFT              14
#define TMC2262_SGP_CLEAR_CUR_PI_FIELD              ((RegisterField) {TMC2262_SGP_CLEAR_CUR_PI_MASK, TMC2262_SGP_CLEAR_CUR_PI_SHIFT, TMC2262_SGP_CONF, false})
#define TMC2262_SGP_LOW_VEL_SLOPE_MASK              0x00FF0000
#define TMC2262_SGP_LOW_VEL_SLOPE_SHIFT             16
#define TMC2262_SGP_LOW_VEL_SLOPE_FIELD             ((RegisterField) {TMC2262_SGP_LOW_VEL_SLOPE_MASK, TMC2262_SGP_LOW_VEL_SLOPE_SHIFT, TMC2262_SGP_CONF, false})
#define TMC2262_SGP_LOW_VEL_CNTS_MASK               0x30000000
#define TMC2262_SGP_LOW_VEL_CNTS_SHIFT              28
#define TMC2262_SGP_LOW_VEL_CNTS_FIELD              ((RegisterField) {TMC2262_SGP_LOW_VEL_CNTS_MASK, TMC2262_SGP_LOW_VEL_CNTS_SHIFT, TMC2262_SGP_CONF, false})
#define TMC2262_SGP_IND_2_MASK                      0x000003FF
#define TMC2262_SGP_IND_2_SHIFT                     0
#define TMC2262_SGP_IND_2_FIELD                     ((RegisterField) {TMC2262_SGP_IND_2_MASK, TMC2262_SGP_IND_2_SHIFT, TMC2262_SGP_IND_2_3, true})
#define TMC2262_SGP_IND_3_MASK                      0x03FF0000
#define TMC2262_SGP_IND_3_SHIFT                     16
#define TMC2262_SGP_IND_3_FIELD                     ((RegisterField) {TMC2262_SGP_IND_3_MASK, TMC2262_SGP_IND_3_SHIFT, TMC2262_SGP_IND_2_3, true})
#define TMC2262_SGP_IND_0_MASK                      0x000003FF
#define TMC2262_SGP_IND_0_SHIFT                     0
#define TMC2262_SGP_IND_0_FIELD                     ((RegisterField) {TMC2262_SGP_IND_0_MASK, TMC2262_SGP_IND_0_SHIFT, TMC2262_SGP_IND_0_1, true})
#define TMC2262_SGP_IND_1_MASK                      0x03FF0000
#define TMC2262_SGP_IND_1_SHIFT                     16
#define TMC2262_SGP_IND_1_FIELD                     ((RegisterField) {TMC2262_SGP_IND_1_MASK, TMC2262_SGP_IND_1_SHIFT, TMC2262_SGP_IND_0_1, true})
#define TMC2262_UL_B_MASK                           0x00000FFF
#define TMC2262_UL_B_SHIFT                          0
#define TMC2262_UL_B_FIELD                          ((RegisterField) {TMC2262_UL_B_MASK, TMC2262_UL_B_SHIFT, TMC2262_INDUCTANCE_VOLTAGE, true})
#define TMC2262_UL_A_MASK                           0x0FFF0000
#define TMC2262_UL_A_SHIFT                          16
#define TMC2262_UL_A_FIELD                          ((RegisterField) {TMC2262_UL_A_MASK, TMC2262_UL_A_SHIFT, TMC2262_INDUCTANCE_VOLTAGE, true})
#define TMC2262_SGP_RAW_MASK                        0x000003FF
#define TMC2262_SGP_RAW_SHIFT                       0
#define TMC2262_SGP_RAW_FIELD                       ((RegisterField) {TMC2262_SGP_RAW_MASK, TMC2262_SGP_RAW_SHIFT, TMC2262_SGP_BEMF, true})
#define TMC2262_UBEMF_ABS_MASK                      0x0FFF0000
#define TMC2262_UBEMF_ABS_SHIFT                     16
#define TMC2262_UBEMF_ABS_FIELD                     ((RegisterField) {TMC2262_UBEMF_ABS_MASK, TMC2262_UBEMF_ABS_SHIFT, TMC2262_SGP_BEMF, false})
#define TMC2262_COOL_CUR_DIV_MASK                   0x0000000F
#define TMC2262_COOL_CUR_DIV_SHIFT                  0
#define TMC2262_COOL_CUR_DIV_FIELD                  ((RegisterField) {TMC2262_COOL_CUR_DIV_MASK, TMC2262_COOL_CUR_DIV_SHIFT, TMC2262_COOLSTEPPLUS_CONF, false})
#define TMC2262_LOAD_FILT_EN_MASK                   0x00000010
#define TMC2262_LOAD_FILT_EN_SHIFT                  4
#define TMC2262_LOAD_FILT_EN_FIELD                  ((RegisterField) {TMC2262_LOAD_FILT_EN_MASK, TMC2262_LOAD_FILT_EN_SHIFT, TMC2262_COOLSTEPPLUS_CONF, false})
#define TMC2262_COOLSTEP_P_MASK                     0x00000FFF
#define TMC2262_COOLSTEP_P_SHIFT                    0
#define TMC2262_COOLSTEP_P_FIELD                    ((RegisterField) {TMC2262_COOLSTEP_P_MASK, TMC2262_COOLSTEP_P_SHIFT, TMC2262_COOLSTEPPLUS_PI_REG, false})
#define TMC2262_COOLSTEP_I_MASK                     0x03FF0000
#define TMC2262_COOLSTEP_I_SHIFT                    16
#define TMC2262_COOLSTEP_I_FIELD                    ((RegisterField) {TMC2262_COOLSTEP_I_MASK, TMC2262_COOLSTEP_I_SHIFT, TMC2262_COOLSTEPPLUS_PI_REG, false})
#define TMC2262_COOL_PI_DOWN_LIMIT_MASK             0x00000FFF
#define TMC2262_COOL_PI_DOWN_LIMIT_SHIFT            0
#define TMC2262_COOL_PI_DOWN_LIMIT_FIELD            ((RegisterField) {TMC2262_COOL_PI_DOWN_LIMIT_MASK, TMC2262_COOL_PI_DOWN_LIMIT_SHIFT, TMC2262_COOLSTEPPLUS_PI_DOWN, false})
#define TMC2262_COOL_PI_OFF_SPEED_MASK              0x0FFF0000
#define TMC2262_COOL_PI_OFF_SPEED_SHIFT             16
#define TMC2262_COOL_PI_OFF_SPEED_FIELD             ((RegisterField) {TMC2262_COOL_PI_OFF_SPEED_MASK, TMC2262_COOL_PI_OFF_SPEED_SHIFT, TMC2262_COOLSTEPPLUS_PI_DOWN, false})
#define TMC2262_COOL_LOW_LOAD_RESERVE_MASK          0x000000FF
#define TMC2262_COOL_LOW_LOAD_RESERVE_SHIFT         0
#define TMC2262_COOL_LOW_LOAD_RESERVE_FIELD         ((RegisterField) {TMC2262_COOL_LOW_LOAD_RESERVE_MASK, TMC2262_COOL_LOW_LOAD_RESERVE_SHIFT, TMC2262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC2262_COOL_HI_LOAD_RESERVE_MASK           0x0000FF00
#define TMC2262_COOL_HI_LOAD_RESERVE_SHIFT          8
#define TMC2262_COOL_HI_LOAD_RESERVE_FIELD          ((RegisterField) {TMC2262_COOL_HI_LOAD_RESERVE_MASK, TMC2262_COOL_HI_LOAD_RESERVE_SHIFT, TMC2262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC2262_COOL_LOW_GENERATORIC_RESERVE_MASK   0x00FF0000
#define TMC2262_COOL_LOW_GENERATORIC_RESERVE_SHIFT  16
#define TMC2262_COOL_LOW_GENERATORIC_RESERVE_FIELD  ((RegisterField) {TMC2262_COOL_LOW_GENERATORIC_RESERVE_MASK, TMC2262_COOL_LOW_GENERATORIC_RESERVE_SHIFT, TMC2262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC2262_COOL_HI_GENERATORIC_RESERVE_MASK    0xFF000000
#define TMC2262_COOL_HI_GENERATORIC_RESERVE_SHIFT   24
#define TMC2262_COOL_HI_GENERATORIC_RESERVE_FIELD   ((RegisterField) {TMC2262_COOL_HI_GENERATORIC_RESERVE_MASK, TMC2262_COOL_HI_GENERATORIC_RESERVE_SHIFT, TMC2262_COOLSTEPPLUS_RESERVE_CONF, false})
#define TMC2262_SGP_RESULT_MASK                     0x000003FF
#define TMC2262_SGP_RESULT_SHIFT                    0
#define TMC2262_SGP_RESULT_FIELD                    ((RegisterField) {TMC2262_SGP_RESULT_MASK, TMC2262_SGP_RESULT_SHIFT, TMC2262_COOLSTEPPLUS_LOAD_RESERVE, true})
#define TMC2262_COOLSTEP_LOAD_RESERVE_MASK          0x01FF0000
#define TMC2262_COOLSTEP_LOAD_RESERVE_SHIFT         16
#define TMC2262_COOLSTEP_LOAD_RESERVE_FIELD         ((RegisterField) {TMC2262_COOLSTEP_LOAD_RESERVE_MASK, TMC2262_COOLSTEP_LOAD_RESERVE_SHIFT, TMC2262_COOLSTEPPLUS_LOAD_RESERVE, false})
#define TMC2262_TSTEP_VELOCITY_MASK                 0x007FFFFF
#define TMC2262_TSTEP_VELOCITY_SHIFT                0
#define TMC2262_TSTEP_VELOCITY_FIELD                ((RegisterField) {TMC2262_TSTEP_VELOCITY_MASK, TMC2262_TSTEP_VELOCITY_SHIFT, TMC2262_TSTEP_VELOCITY, true})
#define TMC2262_ADC_VSUPPLY_MASK                    0x000001FF
#define TMC2262_ADC_VSUPPLY_SHIFT                   0
#define TMC2262_ADC_VSUPPLY_FIELD                   ((RegisterField) {TMC2262_ADC_VSUPPLY_MASK, TMC2262_ADC_VSUPPLY_SHIFT, TMC2262_ADC_VSUPPLY_TEMP, false})
#define TMC2262_ADC_TEMP_MASK                       0x01FF0000
#define TMC2262_ADC_TEMP_SHIFT                      16
#define TMC2262_ADC_TEMP_FIELD                      ((RegisterField) {TMC2262_ADC_TEMP_MASK, TMC2262_ADC_TEMP_SHIFT, TMC2262_ADC_VSUPPLY_TEMP, false})
#define TMC2262_ADC_I_A_MASK                        0x00000FFF
#define TMC2262_ADC_I_A_SHIFT                       0
#define TMC2262_ADC_I_A_FIELD                       ((RegisterField) {TMC2262_ADC_I_A_MASK, TMC2262_ADC_I_A_SHIFT, TMC2262_ADC_I, true})
#define TMC2262_ADC_I_B_MASK                        0x0FFF0000
#define TMC2262_ADC_I_B_SHIFT                       16
#define TMC2262_ADC_I_B_FIELD                       ((RegisterField) {TMC2262_ADC_I_B_MASK, TMC2262_ADC_I_B_SHIFT, TMC2262_ADC_I, true})
#define TMC2262_OVERVOLTAGE_VTH_MASK                0x000001FF
#define TMC2262_OVERVOLTAGE_VTH_SHIFT               0
#define TMC2262_OVERVOLTAGE_VTH_FIELD               ((RegisterField) {TMC2262_OVERVOLTAGE_VTH_MASK, TMC2262_OVERVOLTAGE_VTH_SHIFT, TMC2262_OTW_OV_VTH, false})
#define TMC2262_OVERTEMPPREWARNING_VTH_MASK         0x01FF0000
#define TMC2262_OVERTEMPPREWARNING_VTH_SHIFT        16
#define TMC2262_OVERTEMPPREWARNING_VTH_FIELD        ((RegisterField) {TMC2262_OVERTEMPPREWARNING_VTH_MASK, TMC2262_OVERTEMPPREWARNING_VTH_SHIFT, TMC2262_OTW_OV_VTH, false})
#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
#define TMC2262_MSLUT___SHIFT                       0
#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[0], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[1], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[2], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[3], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[4], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[5], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[6], false})
//#define TMC2262_MSLUT___MASK                        0xFFFFFFFF
//#define TMC2262_MSLUT___SHIFT                       0
//#define TMC2262_MSLUT___FIELD                       ((RegisterField) {TMC2262_MSLUT___MASK, TMC2262_MSLUT___SHIFT, TMC2262_MSLUT[7], false})
#define TMC2262_W0_MASK                             0x00000003
#define TMC2262_W0_SHIFT                            0
#define TMC2262_W0_FIELD                            ((RegisterField) {TMC2262_W0_MASK, TMC2262_W0_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_W1_MASK                             0x0000000C
#define TMC2262_W1_SHIFT                            2
#define TMC2262_W1_FIELD                            ((RegisterField) {TMC2262_W1_MASK, TMC2262_W1_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_W2_MASK                             0x00000030
#define TMC2262_W2_SHIFT                            4
#define TMC2262_W2_FIELD                            ((RegisterField) {TMC2262_W2_MASK, TMC2262_W2_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_W3_MASK                             0x000000C0
#define TMC2262_W3_SHIFT                            6
#define TMC2262_W3_FIELD                            ((RegisterField) {TMC2262_W3_MASK, TMC2262_W3_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_X1_MASK                             0x0000FF00
#define TMC2262_X1_SHIFT                            8
#define TMC2262_X1_FIELD                            ((RegisterField) {TMC2262_X1_MASK, TMC2262_X1_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_X2_MASK                             0x00FF0000
#define TMC2262_X2_SHIFT                            16
#define TMC2262_X2_FIELD                            ((RegisterField) {TMC2262_X2_MASK, TMC2262_X2_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_X3_MASK                             0xFF000000
#define TMC2262_X3_SHIFT                            24
#define TMC2262_X3_FIELD                            ((RegisterField) {TMC2262_X3_MASK, TMC2262_X3_SHIFT, TMC2262_MSLUTSEL, false})
#define TMC2262_START_SIN_MASK                      0x000000FF
#define TMC2262_START_SIN_SHIFT                     0
#define TMC2262_START_SIN_FIELD                     ((RegisterField) {TMC2262_START_SIN_MASK, TMC2262_START_SIN_SHIFT, TMC2262_MSLUTSTART, false})
#define TMC2262_START_SIN90_MASK                    0x00FF0000
#define TMC2262_START_SIN90_SHIFT                   16
#define TMC2262_START_SIN90_FIELD                   ((RegisterField) {TMC2262_START_SIN90_MASK, TMC2262_START_SIN90_SHIFT, TMC2262_MSLUTSTART, false})
#define TMC2262_OFFSET_SIN90_MASK                   0xFF000000
#define TMC2262_OFFSET_SIN90_SHIFT                  24
#define TMC2262_OFFSET_SIN90_FIELD                  ((RegisterField) {TMC2262_OFFSET_SIN90_MASK, TMC2262_OFFSET_SIN90_SHIFT, TMC2262_MSLUTSTART, true})
#define TMC2262_MSCNT_MASK                          0x000003FF
#define TMC2262_MSCNT_SHIFT                         0
#define TMC2262_MSCNT_FIELD                         ((RegisterField) {TMC2262_MSCNT_MASK, TMC2262_MSCNT_SHIFT, TMC2262_MSCNT, false})
#define TMC2262_CUR_B_MASK                          0x000001FF
#define TMC2262_CUR_B_SHIFT                         0
#define TMC2262_CUR_B_FIELD                         ((RegisterField) {TMC2262_CUR_B_MASK, TMC2262_CUR_B_SHIFT, TMC2262_MSCURACT, true})
#define TMC2262_CUR_A_MASK                          0x01FF0000
#define TMC2262_CUR_A_SHIFT                         16
#define TMC2262_CUR_A_FIELD                         ((RegisterField) {TMC2262_CUR_A_MASK, TMC2262_CUR_A_SHIFT, TMC2262_MSCURACT, true})
#define TMC2262_TOFF_MASK                           0x0000000F
#define TMC2262_TOFF_SHIFT                          0
#define TMC2262_TOFF_FIELD                          ((RegisterField) {TMC2262_TOFF_MASK, TMC2262_TOFF_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_HSTRT_TFD210_MASK                   0x00000070
#define TMC2262_HSTRT_TFD210_SHIFT                  4
#define TMC2262_HSTRT_TFD210_FIELD                  ((RegisterField) {TMC2262_HSTRT_TFD210_MASK, TMC2262_HSTRT_TFD210_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_HEND_OFFSET_MASK                    0x00000780
#define TMC2262_HEND_OFFSET_SHIFT                   7
#define TMC2262_HEND_OFFSET_FIELD                   ((RegisterField) {TMC2262_HEND_OFFSET_MASK, TMC2262_HEND_OFFSET_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_FD3_MASK                            0x00000800
#define TMC2262_FD3_SHIFT                           11
#define TMC2262_FD3_FIELD                           ((RegisterField) {TMC2262_FD3_MASK, TMC2262_FD3_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_DISFDCC_MASK                        0x00001000
#define TMC2262_DISFDCC_SHIFT                       12
#define TMC2262_DISFDCC_FIELD                       ((RegisterField) {TMC2262_DISFDCC_MASK, TMC2262_DISFDCC_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_CHM_MASK                            0x00004000
#define TMC2262_CHM_SHIFT                           14
#define TMC2262_CHM_FIELD                           ((RegisterField) {TMC2262_CHM_MASK, TMC2262_CHM_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_TBL_MASK                            0x00018000
#define TMC2262_TBL_SHIFT                           15
#define TMC2262_TBL_FIELD                           ((RegisterField) {TMC2262_TBL_MASK, TMC2262_TBL_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_TPFD_MASK                           0x00F00000
#define TMC2262_TPFD_SHIFT                          20
#define TMC2262_TPFD_FIELD                          ((RegisterField) {TMC2262_TPFD_MASK, TMC2262_TPFD_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_MRES_MASK                           0x0F000000
#define TMC2262_MRES_SHIFT                          24
#define TMC2262_MRES_FIELD                          ((RegisterField) {TMC2262_MRES_MASK, TMC2262_MRES_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_INTPOL_MASK                         0x10000000
#define TMC2262_INTPOL_SHIFT                        28
#define TMC2262_INTPOL_FIELD                        ((RegisterField) {TMC2262_INTPOL_MASK, TMC2262_INTPOL_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_DEDGE_MASK                          0x20000000
#define TMC2262_DEDGE_SHIFT                         29
#define TMC2262_DEDGE_FIELD                         ((RegisterField) {TMC2262_DEDGE_MASK, TMC2262_DEDGE_SHIFT, TMC2262_CHOPCONF, false})
#define TMC2262_SEMIN_MASK                          0x0000000F
#define TMC2262_SEMIN_SHIFT                         0
#define TMC2262_SEMIN_FIELD                         ((RegisterField) {TMC2262_SEMIN_MASK, TMC2262_SEMIN_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SEUP_MASK                           0x00000060
#define TMC2262_SEUP_SHIFT                          5
#define TMC2262_SEUP_FIELD                          ((RegisterField) {TMC2262_SEUP_MASK, TMC2262_SEUP_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SEMAX_MASK                          0x00000F00
#define TMC2262_SEMAX_SHIFT                         8
#define TMC2262_SEMAX_FIELD                         ((RegisterField) {TMC2262_SEMAX_MASK, TMC2262_SEMAX_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SEDN_MASK                           0x00007000
#define TMC2262_SEDN_SHIFT                          12
#define TMC2262_SEDN_FIELD                          ((RegisterField) {TMC2262_SEDN_MASK, TMC2262_SEDN_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SEIMIN_MASK                         0x00008000
#define TMC2262_SEIMIN_SHIFT                        15
#define TMC2262_SEIMIN_FIELD                        ((RegisterField) {TMC2262_SEIMIN_MASK, TMC2262_SEIMIN_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SGT_MASK                            0x007F0000
#define TMC2262_SGT_SHIFT                           16
#define TMC2262_SGT_FIELD                           ((RegisterField) {TMC2262_SGT_MASK, TMC2262_SGT_SHIFT, TMC2262_COOLCONF, true})
#define TMC2262_THIGH_SG_OFF_MASK                   0x00800000
#define TMC2262_THIGH_SG_OFF_SHIFT                  23
#define TMC2262_THIGH_SG_OFF_FIELD                  ((RegisterField) {TMC2262_THIGH_SG_OFF_MASK, TMC2262_THIGH_SG_OFF_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SFILT_MASK                          0x01000000
#define TMC2262_SFILT_SHIFT                         24
#define TMC2262_SFILT_FIELD                         ((RegisterField) {TMC2262_SFILT_MASK, TMC2262_SFILT_SHIFT, TMC2262_COOLCONF, false})
#define TMC2262_SG_RESULT_MASK                      0x000003FF
#define TMC2262_SG_RESULT_SHIFT                     0
#define TMC2262_SG_RESULT_FIELD                     ((RegisterField) {TMC2262_SG_RESULT_MASK, TMC2262_SG_RESULT_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_SEQ_STOPPED_MASK                    0x00000400
#define TMC2262_SEQ_STOPPED_SHIFT                   10
#define TMC2262_SEQ_STOPPED_FIELD                   ((RegisterField) {TMC2262_SEQ_STOPPED_MASK, TMC2262_SEQ_STOPPED_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_OV_MASK                             0x00000800
#define TMC2262_OV_SHIFT                            11
#define TMC2262_OV_FIELD                            ((RegisterField) {TMC2262_OV_MASK, TMC2262_OV_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_S2VSA_MASK                          0x00001000
#define TMC2262_S2VSA_SHIFT                         12
#define TMC2262_S2VSA_FIELD                         ((RegisterField) {TMC2262_S2VSA_MASK, TMC2262_S2VSA_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_S2VSB_MASK                          0x00002000
#define TMC2262_S2VSB_SHIFT                         13
#define TMC2262_S2VSB_FIELD                         ((RegisterField) {TMC2262_S2VSB_MASK, TMC2262_S2VSB_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_STEALTH_MASK                        0x00004000
#define TMC2262_STEALTH_SHIFT                       14
#define TMC2262_STEALTH_FIELD                       ((RegisterField) {TMC2262_STEALTH_MASK, TMC2262_STEALTH_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_CS_ACTUAL_MASK                      0x00FF0000
#define TMC2262_CS_ACTUAL_SHIFT                     16
#define TMC2262_CS_ACTUAL_FIELD                     ((RegisterField) {TMC2262_CS_ACTUAL_MASK, TMC2262_CS_ACTUAL_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_STALLGUARD_MASK                     0x01000000
#define TMC2262_STALLGUARD_SHIFT                    24
#define TMC2262_STALLGUARD_FIELD                    ((RegisterField) {TMC2262_STALLGUARD_MASK, TMC2262_STALLGUARD_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_OT_MASK                             0x02000000
#define TMC2262_OT_SHIFT                            25
#define TMC2262_OT_FIELD                            ((RegisterField) {TMC2262_OT_MASK, TMC2262_OT_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_OTPW_MASK                           0x04000000
#define TMC2262_OTPW_SHIFT                          26
#define TMC2262_OTPW_FIELD                          ((RegisterField) {TMC2262_OTPW_MASK, TMC2262_OTPW_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_S2GA_MASK                           0x08000000
#define TMC2262_S2GA_SHIFT                          27
#define TMC2262_S2GA_FIELD                          ((RegisterField) {TMC2262_S2GA_MASK, TMC2262_S2GA_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_S2GB_MASK                           0x10000000
#define TMC2262_S2GB_SHIFT                          28
#define TMC2262_S2GB_FIELD                          ((RegisterField) {TMC2262_S2GB_MASK, TMC2262_S2GB_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_OLA_MASK                            0x20000000
#define TMC2262_OLA_SHIFT                           29
#define TMC2262_OLA_FIELD                           ((RegisterField) {TMC2262_OLA_MASK, TMC2262_OLA_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_OLB_MASK                            0x40000000
#define TMC2262_OLB_SHIFT                           30
#define TMC2262_OLB_FIELD                           ((RegisterField) {TMC2262_OLB_MASK, TMC2262_OLB_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_STST_MASK                           0x80000000
#define TMC2262_STST_SHIFT                          31
#define TMC2262_STST_FIELD                          ((RegisterField) {TMC2262_STST_MASK, TMC2262_STST_SHIFT, TMC2262_DRV_STATUS, false})
#define TMC2262_PWM_FREQ_MASK                       0x0000000F
#define TMC2262_PWM_FREQ_SHIFT                      0
#define TMC2262_PWM_FREQ_FIELD                      ((RegisterField) {TMC2262_PWM_FREQ_MASK, TMC2262_PWM_FREQ_SHIFT, TMC2262_PWMCONF, false})
#define TMC2262_FREEWHEEL_MASK                      0x00000030
#define TMC2262_FREEWHEEL_SHIFT                     4
#define TMC2262_FREEWHEEL_FIELD                     ((RegisterField) {TMC2262_FREEWHEEL_MASK, TMC2262_FREEWHEEL_SHIFT, TMC2262_PWMCONF, false})
#define TMC2262_OL_THRSH_MASK                       0x000000C0
#define TMC2262_OL_THRSH_SHIFT                      6
#define TMC2262_OL_THRSH_FIELD                      ((RegisterField) {TMC2262_OL_THRSH_MASK, TMC2262_OL_THRSH_SHIFT, TMC2262_PWMCONF, false})
#define TMC2262_SD_ON_MEAS_LO_MASK                  0x0000F000
#define TMC2262_SD_ON_MEAS_LO_SHIFT                 12
#define TMC2262_SD_ON_MEAS_LO_FIELD                 ((RegisterField) {TMC2262_SD_ON_MEAS_LO_MASK, TMC2262_SD_ON_MEAS_LO_SHIFT, TMC2262_PWMCONF, false})
#define TMC2262_SD_ON_MEAS_HI_MASK                  0x000F0000
#define TMC2262_SD_ON_MEAS_HI_SHIFT                 16
#define TMC2262_SD_ON_MEAS_HI_FIELD                 ((RegisterField) {TMC2262_SD_ON_MEAS_HI_MASK, TMC2262_SD_ON_MEAS_HI_SHIFT, TMC2262_PWMCONF, false})

#endif

