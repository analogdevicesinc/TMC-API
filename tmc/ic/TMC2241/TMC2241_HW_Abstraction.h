/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC2241_H_
#define TMC_IC_TMC2241_H_

// Constants
#define TMC2241_REGISTER_COUNT   128
#define TMC2241_MOTORS           1
#define TMC2241_WRITE_BIT        0x80
#define TMC2241_ADDRESS_MASK     0x7F
#define TMC2241_MAX_VELOCITY     8388096
#define TMC2241_MAX_ACCELERATION (uint16_t)  65535

// ramp modes (Register TMC2241_RAMPMODE)
#define TMC2241_MODE_POSITION  0
#define TMC2241_MODE_VELPOS    1
#define TMC2241_MODE_VELNEG    2
#define TMC2241_MODE_HOLD      3

// limit switch mode bits (Register TMC2241_SWMODE)
#define TMC2241_SW_STOPL_ENABLE    0x0001
#define TMC2241_SW_STOPR_ENABLE    0x0002
#define TMC2241_SW_STOPL_POLARITY  0x0004
#define TMC2241_SW_STOPR_POLARITY  0x0008
#define TMC2241_SW_SWAP_LR         0x0010
#define TMC2241_SW_LATCH_L_ACT     0x0020
#define TMC2241_SW_LATCH_L_INACT   0x0040
#define TMC2241_SW_LATCH_R_ACT     0x0080
#define TMC2241_SW_LATCH_R_INACT   0x0100
#define TMC2241_SW_LATCH_ENC       0x0200
#define TMC2241_SW_SG_STOP         0x0400
#define TMC2241_SW_SOFTSTOP        0x0800

// Status bits (Register TMC2241_RAMPSTAT)
#define TMC2241_RS_STOPL          0x0001
#define TMC2241_RS_STOPR          0x0002
#define TMC2241_RS_LATCHL         0x0004
#define TMC2241_RS_LATCHR         0x0008
#define TMC2241_RS_EV_STOPL       0x0010
#define TMC2241_RS_EV_STOPR       0x0020
#define TMC2241_RS_EV_STOP_SG     0x0040
#define TMC2241_RS_EV_POSREACHED  0x0080
#define TMC2241_RS_VELREACHED     0x0100
#define TMC2241_RS_POSREACHED     0x0200
#define TMC2241_RS_VZERO          0x0400
#define TMC2241_RS_ZEROWAIT       0x0800
#define TMC2241_RS_SECONDMOVE     0x1000
#define TMC2241_RS_SG             0x2000

// Encoderbits (Register TMC2241_ENCMODE)
#define TMC2241_EM_DECIMAL     0x0400
#define TMC2241_EM_LATCH_XACT  0x0200
#define TMC2241_EM_CLR_XENC    0x0100
#define TMC2241_EM_NEG_EDGE    0x0080
#define TMC2241_EM_POS_EDGE    0x0040
#define TMC2241_EM_CLR_ONCE    0x0020
#define TMC2241_EM_CLR_CONT    0x0010
#define TMC2241_EM_IGNORE_AB   0x0008
#define TMC2241_EM_POL_N       0x0004
#define TMC2241_EM_POL_B       0x0002
#define TMC2241_EM_POL_A       0x0001


// Registers
#define TMC2241_GCONF            0x00
#define TMC2241_GSTAT            0x01
#define TMC2241_IFCNT            0x02
#define TMC2241_NODECONF         0x03
#define TMC2241_IOIN             0x04
#define TMC2241_DIAG_GCONF       0x07
#define TMC2241_DRV_CONF         0x0A
#define TMC2241_GLOBAL_SCALER    0x0B
#define TMC2241_IHOLD_IRUN       0x10
#define TMC2241_TPOWERDOWN       0x11
#define TMC2241_TSTEP            0x12
#define TMC2241_TPWMTHRS         0x13
#define TMC2241_TCOOLTHRS        0x14
#define TMC2241_THIGH            0x15
#define TMC2241_DIRECT_MODE      0x2D
#define TMC2241_ENCMODE          0x38
#define TMC2241_X_ENC            0x39
#define TMC2241_ENC_CONST        0x3A
#define TMC2241_ENC_STATUS       0x3B
#define TMC2241_ENC_LATCH        0x3C
#define TMC2241_ADC_VSUPPLY_AIN  0x50
#define TMC2241_ADC_TEMP         0x51
#define TMC2241_OTW_OV_VTH       0x52
#define TMC2241_MSLUT_0          0x60
#define TMC2241_MSLUT_1          0x61
#define TMC2241_MSLUT_2          0x62
#define TMC2241_MSLUT_3          0x63
#define TMC2241_MSLUT_4          0x64
#define TMC2241_MSLUT_5          0x65
#define TMC2241_MSLUT_6          0x66
#define TMC2241_MSLUT_7          0x67
#define TMC2241_MSLUTSEL         0x68
#define TMC2241_MSLUTSTART       0x69
#define TMC2241_MSCNT            0x6A
#define TMC2241_MSCURACT         0x6B
#define TMC2241_CHOPCONF         0x6C
#define TMC2241_COOLCONF         0x6D
#define TMC2241_DRV_STATUS       0x6F
#define TMC2241_PWMCONF          0x70
#define TMC2241_PWM_SCALE        0x71
#define TMC2241_PWM_AUTO         0x72
#define TMC2241_SG4_CONF         0x74
#define TMC2241_SG4_RESULT       0x75
#define TMC2241_SG4_IND          0x76

// Register fields
#define TMC2241_FAST_STANDSTILL_MASK          0x00000002
#define TMC2241_FAST_STANDSTILL_SHIFT         1
#define TMC2241_FAST_STANDSTILL_FIELD         ((RegisterField) {TMC2241_FAST_STANDSTILL_MASK, TMC2241_FAST_STANDSTILL_SHIFT, TMC2241_GCONF, false})
#define TMC2241_EN_PWM_MODE_MASK              0x00000004
#define TMC2241_EN_PWM_MODE_SHIFT             2
#define TMC2241_EN_PWM_MODE_FIELD             ((RegisterField) {TMC2241_EN_PWM_MODE_MASK, TMC2241_EN_PWM_MODE_SHIFT, TMC2241_GCONF, false})
#define TMC2241_MULTISTEP_FILT_MASK           0x00000008
#define TMC2241_MULTISTEP_FILT_SHIFT          3
#define TMC2241_MULTISTEP_FILT_FIELD          ((RegisterField) {TMC2241_MULTISTEP_FILT_MASK, TMC2241_MULTISTEP_FILT_SHIFT, TMC2241_GCONF, false})
#define TMC2241_SHAFT_MASK                    0x00000010
#define TMC2241_SHAFT_SHIFT                   4
#define TMC2241_SHAFT_FIELD                   ((RegisterField) {TMC2241_SHAFT_MASK, TMC2241_SHAFT_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG0_ERROR_MASK              0x00000020
#define TMC2241_DIAG0_ERROR_SHIFT             5
#define TMC2241_DIAG0_ERROR_FIELD             ((RegisterField) {TMC2241_DIAG0_ERROR_MASK, TMC2241_DIAG0_ERROR_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG0_OTPW_MASK               0x00000040
#define TMC2241_DIAG0_OTPW_SHIFT              6
#define TMC2241_DIAG0_OTPW_FIELD              ((RegisterField) {TMC2241_DIAG0_OTPW_MASK, TMC2241_DIAG0_OTPW_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG0_STALL_MASK              0x00000080
#define TMC2241_DIAG0_STALL_SHIFT             7
#define TMC2241_DIAG0_STALL_FIELD             ((RegisterField) {TMC2241_DIAG0_STALL_MASK, TMC2241_DIAG0_STALL_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG1_STALL_MASK              0x00000100
#define TMC2241_DIAG1_STALL_SHIFT             8
#define TMC2241_DIAG1_STALL_FIELD             ((RegisterField) {TMC2241_DIAG1_STALL_MASK, TMC2241_DIAG1_STALL_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG1_INDEX_MASK              0x00000200
#define TMC2241_DIAG1_INDEX_SHIFT             9
#define TMC2241_DIAG1_INDEX_FIELD             ((RegisterField) {TMC2241_DIAG1_INDEX_MASK, TMC2241_DIAG1_INDEX_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG1_ONSTATE_MASK            0x00000400
#define TMC2241_DIAG1_ONSTATE_SHIFT           10
#define TMC2241_DIAG1_ONSTATE_FIELD           ((RegisterField) {TMC2241_DIAG1_ONSTATE_MASK, TMC2241_DIAG1_ONSTATE_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG0_PUSHPULL_MASK           0x00001000
#define TMC2241_DIAG0_PUSHPULL_SHIFT          12
#define TMC2241_DIAG0_PUSHPULL_FIELD          ((RegisterField) {TMC2241_DIAG0_PUSHPULL_MASK, TMC2241_DIAG0_PUSHPULL_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIAG1_PUSHPULL_MASK           0x00002000
#define TMC2241_DIAG1_PUSHPULL_SHIFT          13
#define TMC2241_DIAG1_PUSHPULL_FIELD          ((RegisterField) {TMC2241_DIAG1_PUSHPULL_MASK, TMC2241_DIAG1_PUSHPULL_SHIFT, TMC2241_GCONF, false})
#define TMC2241_SMALL_HYSTERESIS_MASK         0x00004000
#define TMC2241_SMALL_HYSTERESIS_SHIFT        14
#define TMC2241_SMALL_HYSTERESIS_FIELD        ((RegisterField) {TMC2241_SMALL_HYSTERESIS_MASK, TMC2241_SMALL_HYSTERESIS_SHIFT, TMC2241_GCONF, false})
#define TMC2241_STOP_ENABLE_MASK              0x00008000
#define TMC2241_STOP_ENABLE_SHIFT             15
#define TMC2241_STOP_ENABLE_FIELD             ((RegisterField) {TMC2241_STOP_ENABLE_MASK, TMC2241_STOP_ENABLE_SHIFT, TMC2241_GCONF, false})
#define TMC2241_DIRECT_MODE_MASK              0x00010000
#define TMC2241_DIRECT_MODE_SHIFT             16
#define TMC2241_DIRECT_MODE_FIELD             ((RegisterField) {TMC2241_DIRECT_MODE_MASK, TMC2241_DIRECT_MODE_SHIFT, TMC2241_GCONF, false})
#define TMC2241_RESET_MASK                    0x00000001
#define TMC2241_RESET_SHIFT                   0
#define TMC2241_RESET_FIELD                   ((RegisterField) {TMC2241_RESET_MASK, TMC2241_RESET_SHIFT, TMC2241_GSTAT, false})
#define TMC2241_DRV_ERR_MASK                  0x00000002
#define TMC2241_DRV_ERR_SHIFT                 1
#define TMC2241_DRV_ERR_FIELD                 ((RegisterField) {TMC2241_DRV_ERR_MASK, TMC2241_DRV_ERR_SHIFT, TMC2241_GSTAT, false})
#define TMC2241_UV_CP_MASK                    0x00000004
#define TMC2241_UV_CP_SHIFT                   2
#define TMC2241_UV_CP_FIELD                   ((RegisterField) {TMC2241_UV_CP_MASK, TMC2241_UV_CP_SHIFT, TMC2241_GSTAT, false})
#define TMC2241_REGISTER_RESET_MASK           0x00000008
#define TMC2241_REGISTER_RESET_SHIFT          3
#define TMC2241_REGISTER_RESET_FIELD          ((RegisterField) {TMC2241_REGISTER_RESET_MASK, TMC2241_REGISTER_RESET_SHIFT, TMC2241_GSTAT, false})
#define TMC2241_VM_UVLO_MASK                  0x00000010
#define TMC2241_VM_UVLO_SHIFT                 4
#define TMC2241_VM_UVLO_FIELD                 ((RegisterField) {TMC2241_VM_UVLO_MASK, TMC2241_VM_UVLO_SHIFT, TMC2241_GSTAT, false})
#define TMC2241_IFCNT_MASK                    0x000000FF
#define TMC2241_IFCNT_SHIFT                   0
#define TMC2241_IFCNT_FIELD                   ((RegisterField) {TMC2241_IFCNT_MASK, TMC2241_IFCNT_SHIFT, TMC2241_IFCNT, false})
#define TMC2241_NODEADDR_MASK                 0x000000FF
#define TMC2241_NODEADDR_SHIFT                0
#define TMC2241_NODEADDR_FIELD                ((RegisterField) {TMC2241_NODEADDR_MASK, TMC2241_NODEADDR_SHIFT, TMC2241_NODECONF, false})
#define TMC2241_SENDDELAY_MASK                0x00000F00
#define TMC2241_SENDDELAY_SHIFT               8
#define TMC2241_SENDDELAY_FIELD               ((RegisterField) {TMC2241_SENDDELAY_MASK, TMC2241_SENDDELAY_SHIFT, TMC2241_NODECONF, false})
#define TMC2241_STEP_MASK                     0x00000001
#define TMC2241_STEP_SHIFT                    0
#define TMC2241_STEP_FIELD                    ((RegisterField) {TMC2241_STEP_MASK, TMC2241_STEP_SHIFT, TMC2241_IOIN, false})
#define TMC2241_DIR_MASK                      0x00000002
#define TMC2241_DIR_SHIFT                     1
#define TMC2241_DIR_FIELD                     ((RegisterField) {TMC2241_DIR_MASK, TMC2241_DIR_SHIFT, TMC2241_IOIN, false})
#define TMC2241_ENCB_MASK                     0x00000004
#define TMC2241_ENCB_SHIFT                    2
#define TMC2241_ENCB_FIELD                    ((RegisterField) {TMC2241_ENCB_MASK, TMC2241_ENCB_SHIFT, TMC2241_IOIN, false})
#define TMC2241_ENCA_MASK                     0x00000008
#define TMC2241_ENCA_SHIFT                    3
#define TMC2241_ENCA_FIELD                    ((RegisterField) {TMC2241_ENCA_MASK, TMC2241_ENCA_SHIFT, TMC2241_IOIN, false})
#define TMC2241_DRV_ENN_MASK                  0x00000010
#define TMC2241_DRV_ENN_SHIFT                 4
#define TMC2241_DRV_ENN_FIELD                 ((RegisterField) {TMC2241_DRV_ENN_MASK, TMC2241_DRV_ENN_SHIFT, TMC2241_IOIN, false})
#define TMC2241_ENCN_MASK                     0x00000020
#define TMC2241_ENCN_SHIFT                    5
#define TMC2241_ENCN_FIELD                    ((RegisterField) {TMC2241_ENCN_MASK, TMC2241_ENCN_SHIFT, TMC2241_IOIN, false})
#define TMC2241_UART_EN_MASK                  0x00000040
#define TMC2241_UART_EN_SHIFT                 6
#define TMC2241_UART_EN_FIELD                 ((RegisterField) {TMC2241_UART_EN_MASK, TMC2241_UART_EN_SHIFT, TMC2241_IOIN, false})
#define TMC2241_RESERVED_MASK                 0x00000080
#define TMC2241_RESERVED_SHIFT                7
#define TMC2241_RESERVED_FIELD                ((RegisterField) {TMC2241_RESERVED_MASK, TMC2241_RESERVED_SHIFT, TMC2241_IOIN, false})
#define TMC2241_COMP_A_MASK                   0x00000100
#define TMC2241_COMP_A_SHIFT                  8
#define TMC2241_COMP_A_FIELD                  ((RegisterField) {TMC2241_COMP_A_MASK, TMC2241_COMP_A_SHIFT, TMC2241_IOIN, false})
#define TMC2241_COMP_B_MASK                   0x00000200
#define TMC2241_COMP_B_SHIFT                  9
#define TMC2241_COMP_B_FIELD                  ((RegisterField) {TMC2241_COMP_B_MASK, TMC2241_COMP_B_SHIFT, TMC2241_IOIN, false})
#define TMC2241_COMP_A1_A2_MASK               0x00000400
#define TMC2241_COMP_A1_A2_SHIFT              10
#define TMC2241_COMP_A1_A2_FIELD              ((RegisterField) {TMC2241_COMP_A1_A2_MASK, TMC2241_COMP_A1_A2_SHIFT, TMC2241_IOIN, false})
#define TMC2241_COMP_B1_B2_MASK               0x00000800
#define TMC2241_COMP_B1_B2_SHIFT              11
#define TMC2241_COMP_B1_B2_FIELD              ((RegisterField) {TMC2241_COMP_B1_B2_MASK, TMC2241_COMP_B1_B2_SHIFT, TMC2241_IOIN, false})
#define TMC2241_OUTPUT_MASK                   0x00001000
#define TMC2241_OUTPUT_SHIFT                  12
#define TMC2241_OUTPUT_FIELD                  ((RegisterField) {TMC2241_OUTPUT_MASK, TMC2241_OUTPUT_SHIFT, TMC2241_IOIN, false})
#define TMC2241_EXT_RES_DET_MASK              0x00002000
#define TMC2241_EXT_RES_DET_SHIFT             13
#define TMC2241_EXT_RES_DET_FIELD             ((RegisterField) {TMC2241_EXT_RES_DET_MASK, TMC2241_EXT_RES_DET_SHIFT, TMC2241_IOIN, false})
#define TMC2241_EXT_CLK_MASK                  0x00004000
#define TMC2241_EXT_CLK_SHIFT                 14
#define TMC2241_EXT_CLK_FIELD                 ((RegisterField) {TMC2241_EXT_CLK_MASK, TMC2241_EXT_CLK_SHIFT, TMC2241_IOIN, false})
#define TMC2241_ADC_ERR_MASK                  0x00008000
#define TMC2241_ADC_ERR_SHIFT                 15
#define TMC2241_ADC_ERR_FIELD                 ((RegisterField) {TMC2241_ADC_ERR_MASK, TMC2241_ADC_ERR_SHIFT, TMC2241_IOIN, false})
#define TMC2241_SILICON_RV_MASK               0x00070000
#define TMC2241_SILICON_RV_SHIFT              16
#define TMC2241_SILICON_RV_FIELD              ((RegisterField) {TMC2241_SILICON_RV_MASK, TMC2241_SILICON_RV_SHIFT, TMC2241_IOIN, false})
//#define TMC2241_DIAG0_ERROR_MASK              0x00000001
//#define TMC2241_DIAG0_ERROR_SHIFT             0
//#define TMC2241_DIAG0_ERROR_FIELD             ((RegisterField) {TMC2241_DIAG0_ERROR_MASK, TMC2241_DIAG0_ERROR_SHIFT, TMC2241_DIAG_GCONF, false})
//#define TMC2241_DIAG0_OTPW_MASK               0x00000002
//#define TMC2241_DIAG0_OTPW_SHIFT              1
//#define TMC2241_DIAG0_OTPW_FIELD              ((RegisterField) {TMC2241_DIAG0_OTPW_MASK, TMC2241_DIAG0_OTPW_SHIFT, TMC2241_DIAG_GCONF, false})
//#define TMC2241_DIAG0_STALL_MASK              0x00000004
//#define TMC2241_DIAG0_STALL_SHIFT             2
//#define TMC2241_DIAG0_STALL_FIELD             ((RegisterField) {TMC2241_DIAG0_STALL_MASK, TMC2241_DIAG0_STALL_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG0_INDEX_MASK              0x00000008
#define TMC2241_DIAG0_INDEX_SHIFT             3
#define TMC2241_DIAG0_INDEX_FIELD             ((RegisterField) {TMC2241_DIAG0_INDEX_MASK, TMC2241_DIAG0_INDEX_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG0_EV_N_DEVIATION_MASK     0x00000400
#define TMC2241_DIAG0_EV_N_DEVIATION_SHIFT    10
#define TMC2241_DIAG0_EV_N_DEVIATION_FIELD    ((RegisterField) {TMC2241_DIAG0_EV_N_DEVIATION_MASK, TMC2241_DIAG0_EV_N_DEVIATION_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG0_OVERVOLTAGE_MASK        0x00000800
#define TMC2241_DIAG0_OVERVOLTAGE_SHIFT       11
#define TMC2241_DIAG0_OVERVOLTAGE_FIELD       ((RegisterField) {TMC2241_DIAG0_OVERVOLTAGE_MASK, TMC2241_DIAG0_OVERVOLTAGE_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG1_ERROR_MASK              0x00010000
#define TMC2241_DIAG1_ERROR_SHIFT             16
#define TMC2241_DIAG1_ERROR_FIELD             ((RegisterField) {TMC2241_DIAG1_ERROR_MASK, TMC2241_DIAG1_ERROR_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG1_OTPW_MASK               0x00020000
#define TMC2241_DIAG1_OTPW_SHIFT              17
#define TMC2241_DIAG1_OTPW_FIELD              ((RegisterField) {TMC2241_DIAG1_OTPW_MASK, TMC2241_DIAG1_OTPW_SHIFT, TMC2241_DIAG_GCONF, false})
//#define TMC2241_DIAG1_STALL_MASK              0x00040000
//#define TMC2241_DIAG1_STALL_SHIFT             18
//#define TMC2241_DIAG1_STALL_FIELD             ((RegisterField) {TMC2241_DIAG1_STALL_MASK, TMC2241_DIAG1_STALL_SHIFT, TMC2241_DIAG_GCONF, false})
//#define TMC2241_DIAG1_INDEX_MASK              0x00080000
//#define TMC2241_DIAG1_INDEX_SHIFT             19
//#define TMC2241_DIAG1_INDEX_FIELD             ((RegisterField) {TMC2241_DIAG1_INDEX_MASK, TMC2241_DIAG1_INDEX_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG1_EV_N_DEVIATION_MASK     0x04000000
#define TMC2241_DIAG1_EV_N_DEVIATION_SHIFT    26
#define TMC2241_DIAG1_EV_N_DEVIATION_FIELD    ((RegisterField) {TMC2241_DIAG1_EV_N_DEVIATION_MASK, TMC2241_DIAG1_EV_N_DEVIATION_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_DIAG1_OVERVOLTAGE_MASK        0x08000000
#define TMC2241_DIAG1_OVERVOLTAGE_SHIFT       27
#define TMC2241_DIAG1_OVERVOLTAGE_FIELD       ((RegisterField) {TMC2241_DIAG1_OVERVOLTAGE_MASK, TMC2241_DIAG1_OVERVOLTAGE_SHIFT, TMC2241_DIAG_GCONF, false})
#define TMC2241_CURRENT_RANGE_MASK            0x00000003
#define TMC2241_CURRENT_RANGE_SHIFT           0
#define TMC2241_CURRENT_RANGE_FIELD           ((RegisterField) {TMC2241_CURRENT_RANGE_MASK, TMC2241_CURRENT_RANGE_SHIFT, TMC2241_DRV_CONF, false})
#define TMC2241_SLOPE_CONTROL_MASK            0x00000030
#define TMC2241_SLOPE_CONTROL_SHIFT           4
#define TMC2241_SLOPE_CONTROL_FIELD           ((RegisterField) {TMC2241_SLOPE_CONTROL_MASK, TMC2241_SLOPE_CONTROL_SHIFT, TMC2241_DRV_CONF, false})
#define TMC2241_GLOBAL_SCALER_MASK            0x000000FF
#define TMC2241_GLOBAL_SCALER_SHIFT           0
#define TMC2241_GLOBAL_SCALER_FIELD           ((RegisterField) {TMC2241_GLOBAL_SCALER_MASK, TMC2241_GLOBAL_SCALER_SHIFT, TMC2241_GLOBAL_SCALER, false})
#define TMC2241_IHOLD_MASK                    0x0000001F
#define TMC2241_IHOLD_SHIFT                   0
#define TMC2241_IHOLD_FIELD                   ((RegisterField) {TMC2241_IHOLD_MASK, TMC2241_IHOLD_SHIFT, TMC2241_IHOLD_IRUN, false})
#define TMC2241_IRUN_MASK                     0x00001F00
#define TMC2241_IRUN_SHIFT                    8
#define TMC2241_IRUN_FIELD                    ((RegisterField) {TMC2241_IRUN_MASK, TMC2241_IRUN_SHIFT, TMC2241_IHOLD_IRUN, false})
#define TMC2241_IHOLDDELAY_MASK               0x000F0000
#define TMC2241_IHOLDDELAY_SHIFT              16
#define TMC2241_IHOLDDELAY_FIELD              ((RegisterField) {TMC2241_IHOLDDELAY_MASK, TMC2241_IHOLDDELAY_SHIFT, TMC2241_IHOLD_IRUN, false})
#define TMC2241_IRUNDELAY_MASK                0x0F000000
#define TMC2241_IRUNDELAY_SHIFT               24
#define TMC2241_IRUNDELAY_FIELD               ((RegisterField) {TMC2241_IRUNDELAY_MASK, TMC2241_IRUNDELAY_SHIFT, TMC2241_IHOLD_IRUN, false})
#define TMC2241_TPOWERDOWN_MASK               0x000000FF
#define TMC2241_TPOWERDOWN_SHIFT              0
#define TMC2241_TPOWERDOWN_FIELD              ((RegisterField) {TMC2241_TPOWERDOWN_MASK, TMC2241_TPOWERDOWN_SHIFT, TMC2241_TPOWERDOWN, false})
#define TMC2241_TSTEP_MASK                    0x000FFFFF
#define TMC2241_TSTEP_SHIFT                   0
#define TMC2241_TSTEP_FIELD                   ((RegisterField) {TMC2241_TSTEP_MASK, TMC2241_TSTEP_SHIFT, TMC2241_TSTEP, false})
#define TMC2241_TPWMTHRS_MASK                 0x000FFFFF
#define TMC2241_TPWMTHRS_SHIFT                0
#define TMC2241_TPWMTHRS_FIELD                ((RegisterField) {TMC2241_TPWMTHRS_MASK, TMC2241_TPWMTHRS_SHIFT, TMC2241_TPWMTHRS, false})
#define TMC2241_TCOOLTHRS_MASK                0x000FFFFF
#define TMC2241_TCOOLTHRS_SHIFT               0
#define TMC2241_TCOOLTHRS_FIELD               ((RegisterField) {TMC2241_TCOOLTHRS_MASK, TMC2241_TCOOLTHRS_SHIFT, TMC2241_TCOOLTHRS, false})
#define TMC2241_THIGH_MASK                    0x000FFFFF
#define TMC2241_THIGH_SHIFT                   0
#define TMC2241_THIGH_FIELD                   ((RegisterField) {TMC2241_THIGH_MASK, TMC2241_THIGH_SHIFT, TMC2241_THIGH, false})
#define TMC2241_DIRECT_COIL_A_MASK            0x000001FF
#define TMC2241_DIRECT_COIL_A_SHIFT           0
#define TMC2241_DIRECT_COIL_A_FIELD           ((RegisterField) {TMC2241_DIRECT_COIL_A_MASK, TMC2241_DIRECT_COIL_A_SHIFT, TMC2241_DIRECT_MODE, true})
#define TMC2241_DIRECT_COIL_B_MASK            0x01FF0000
#define TMC2241_DIRECT_COIL_B_SHIFT           16
#define TMC2241_DIRECT_COIL_B_FIELD           ((RegisterField) {TMC2241_DIRECT_COIL_B_MASK, TMC2241_DIRECT_COIL_B_SHIFT, TMC2241_DIRECT_MODE, true})
#define TMC2241_POL_A_MASK                    0x00000001
#define TMC2241_POL_A_SHIFT                   0
#define TMC2241_POL_A_FIELD                   ((RegisterField) {TMC2241_POL_A_MASK, TMC2241_POL_A_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_POL_B_MASK                    0x00000002
#define TMC2241_POL_B_SHIFT                   1
#define TMC2241_POL_B_FIELD                   ((RegisterField) {TMC2241_POL_B_MASK, TMC2241_POL_B_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_POL_N_MASK                    0x00000004
#define TMC2241_POL_N_SHIFT                   2
#define TMC2241_POL_N_FIELD                   ((RegisterField) {TMC2241_POL_N_MASK, TMC2241_POL_N_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_IGNORE_AB_MASK                0x00000008
#define TMC2241_IGNORE_AB_SHIFT               3
#define TMC2241_IGNORE_AB_FIELD               ((RegisterField) {TMC2241_IGNORE_AB_MASK, TMC2241_IGNORE_AB_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_CLR_CONT_MASK                 0x00000010
#define TMC2241_CLR_CONT_SHIFT                4
#define TMC2241_CLR_CONT_FIELD                ((RegisterField) {TMC2241_CLR_CONT_MASK, TMC2241_CLR_CONT_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_CLR_ONCE_MASK                 0x00000020
#define TMC2241_CLR_ONCE_SHIFT                5
#define TMC2241_CLR_ONCE_FIELD                ((RegisterField) {TMC2241_CLR_ONCE_MASK, TMC2241_CLR_ONCE_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_POS_NEG_EDGE_MASK             0x000000C0
#define TMC2241_POS_NEG_EDGE_SHIFT            6
#define TMC2241_POS_NEG_EDGE_FIELD            ((RegisterField) {TMC2241_POS_NEG_EDGE_MASK, TMC2241_POS_NEG_EDGE_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_CLR_ENC_X_MASK                0x00000100
#define TMC2241_CLR_ENC_X_SHIFT               8
#define TMC2241_CLR_ENC_X_FIELD               ((RegisterField) {TMC2241_CLR_ENC_X_MASK, TMC2241_CLR_ENC_X_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_LATCH_X_ACT_MASK              0x00000200
#define TMC2241_LATCH_X_ACT_SHIFT             9
#define TMC2241_LATCH_X_ACT_FIELD             ((RegisterField) {TMC2241_LATCH_X_ACT_MASK, TMC2241_LATCH_X_ACT_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_ENC_SEL_DECIMAL_MASK          0x00000400
#define TMC2241_ENC_SEL_DECIMAL_SHIFT         10
#define TMC2241_ENC_SEL_DECIMAL_FIELD         ((RegisterField) {TMC2241_ENC_SEL_DECIMAL_MASK, TMC2241_ENC_SEL_DECIMAL_SHIFT, TMC2241_ENCMODE, false})
#define TMC2241_X_ENC_MASK                    0xFFFFFFFF
#define TMC2241_X_ENC_SHIFT                   0
#define TMC2241_X_ENC_FIELD                   ((RegisterField) {TMC2241_X_ENC_MASK, TMC2241_X_ENC_SHIFT, TMC2241_X_ENC, true})
#define TMC2241_ENC_CONST_MASK                0xFFFFFFFF
#define TMC2241_ENC_CONST_SHIFT               0
#define TMC2241_ENC_CONST_FIELD               ((RegisterField) {TMC2241_ENC_CONST_MASK, TMC2241_ENC_CONST_SHIFT, TMC2241_ENC_CONST, true})
#define TMC2241_N_EVENT_MASK                  0x00000001
#define TMC2241_N_EVENT_SHIFT                 0
#define TMC2241_N_EVENT_FIELD                 ((RegisterField) {TMC2241_N_EVENT_MASK, TMC2241_N_EVENT_SHIFT, TMC2241_ENC_STATUS, false})
#define TMC2241_ENC_LATCH_MASK                0xFFFFFFFF
#define TMC2241_ENC_LATCH_SHIFT               0
#define TMC2241_ENC_LATCH_FIELD               ((RegisterField) {TMC2241_ENC_LATCH_MASK, TMC2241_ENC_LATCH_SHIFT, TMC2241_ENC_LATCH, false})
#define TMC2241_ADC_VSUPPLY_MASK              0x00001FFF
#define TMC2241_ADC_VSUPPLY_SHIFT             0
#define TMC2241_ADC_VSUPPLY_FIELD             ((RegisterField) {TMC2241_ADC_VSUPPLY_MASK, TMC2241_ADC_VSUPPLY_SHIFT, TMC2241_ADC_VSUPPLY_AIN, true})
#define TMC2241_ADC_AIN_MASK                  0x1FFF0000
#define TMC2241_ADC_AIN_SHIFT                 16
#define TMC2241_ADC_AIN_FIELD                 ((RegisterField) {TMC2241_ADC_AIN_MASK, TMC2241_ADC_AIN_SHIFT, TMC2241_ADC_VSUPPLY_AIN, true})
#define TMC2241_ADC_TEMP_MASK                 0x00001FFF
#define TMC2241_ADC_TEMP_SHIFT                0
#define TMC2241_ADC_TEMP_FIELD                ((RegisterField) {TMC2241_ADC_TEMP_MASK, TMC2241_ADC_TEMP_SHIFT, TMC2241_ADC_TEMP, true})
//#define TMC2241_RESERVED_MASK                 0x1FFF0000
//#define TMC2241_RESERVED_SHIFT                16
//#define TMC2241_RESERVED_FIELD                ((RegisterField) {TMC2241_RESERVED_MASK, TMC2241_RESERVED_SHIFT, TMC2241_ADC_TEMP, false})
#define TMC2241_OVERVOLTAGE_VTH_MASK          0x00001FFF
#define TMC2241_OVERVOLTAGE_VTH_SHIFT         0
#define TMC2241_OVERVOLTAGE_VTH_FIELD         ((RegisterField) {TMC2241_OVERVOLTAGE_VTH_MASK, TMC2241_OVERVOLTAGE_VTH_SHIFT, TMC2241_OTW_OV_VTH, false})
#define TMC2241_OVERTEMPPREWARNING_VTH_MASK   0x1FFF0000
#define TMC2241_OVERTEMPPREWARNING_VTH_SHIFT  16
#define TMC2241_OVERTEMPPREWARNING_VTH_FIELD  ((RegisterField) {TMC2241_OVERTEMPPREWARNING_VTH_MASK, TMC2241_OVERTEMPPREWARNING_VTH_SHIFT, TMC2241_OTW_OV_VTH, false})
#define TMC2241_MSLUT_0_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_0_SHIFT                 0
#define TMC2241_MSLUT_0_FIELD                 ((RegisterField) {TMC2241_MSLUT_0_MASK, TMC2241_MSLUT_0_SHIFT, TMC2241_MSLUT_0, false})
#define TMC2241_MSLUT_1_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_1_SHIFT                 0
#define TMC2241_MSLUT_1_FIELD                 ((RegisterField) {TMC2241_MSLUT_1_MASK, TMC2241_MSLUT_1_SHIFT, TMC2241_MSLUT_1, false})
#define TMC2241_MSLUT_2_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_2_SHIFT                 0
#define TMC2241_MSLUT_2_FIELD                 ((RegisterField) {TMC2241_MSLUT_2_MASK, TMC2241_MSLUT_2_SHIFT, TMC2241_MSLUT_2, false})
#define TMC2241_MSLUT_3_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_3_SHIFT                 0
#define TMC2241_MSLUT_3_FIELD                 ((RegisterField) {TMC2241_MSLUT_3_MASK, TMC2241_MSLUT_3_SHIFT, TMC2241_MSLUT_3, false})
#define TMC2241_MSLUT_4_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_4_SHIFT                 0
#define TMC2241_MSLUT_4_FIELD                 ((RegisterField) {TMC2241_MSLUT_4_MASK, TMC2241_MSLUT_4_SHIFT, TMC2241_MSLUT_4, false})
#define TMC2241_MSLUT_5_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_5_SHIFT                 0
#define TMC2241_MSLUT_5_FIELD                 ((RegisterField) {TMC2241_MSLUT_5_MASK, TMC2241_MSLUT_5_SHIFT, TMC2241_MSLUT_5, false})
#define TMC2241_MSLUT_6_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_6_SHIFT                 0
#define TMC2241_MSLUT_6_FIELD                 ((RegisterField) {TMC2241_MSLUT_6_MASK, TMC2241_MSLUT_6_SHIFT, TMC2241_MSLUT_6, false})
#define TMC2241_MSLUT_7_MASK                  0xFFFFFFFF
#define TMC2241_MSLUT_7_SHIFT                 0
#define TMC2241_MSLUT_7_FIELD                 ((RegisterField) {TMC2241_MSLUT_7_MASK, TMC2241_MSLUT_7_SHIFT, TMC2241_MSLUT_7, false})
#define TMC2241_W0_MASK                       0x00000003
#define TMC2241_W0_SHIFT                      0
#define TMC2241_W0_FIELD                      ((RegisterField) {TMC2241_W0_MASK, TMC2241_W0_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_W1_MASK                       0x0000000C
#define TMC2241_W1_SHIFT                      2
#define TMC2241_W1_FIELD                      ((RegisterField) {TMC2241_W1_MASK, TMC2241_W1_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_W2_MASK                       0x00000030
#define TMC2241_W2_SHIFT                      4
#define TMC2241_W2_FIELD                      ((RegisterField) {TMC2241_W2_MASK, TMC2241_W2_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_W3_MASK                       0x000000C0
#define TMC2241_W3_SHIFT                      6
#define TMC2241_W3_FIELD                      ((RegisterField) {TMC2241_W3_MASK, TMC2241_W3_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_X1_MASK                       0x0000FF00
#define TMC2241_X1_SHIFT                      8
#define TMC2241_X1_FIELD                      ((RegisterField) {TMC2241_X1_MASK, TMC2241_X1_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_X2_MASK                       0x00FF0000
#define TMC2241_X2_SHIFT                      16
#define TMC2241_X2_FIELD                      ((RegisterField) {TMC2241_X2_MASK, TMC2241_X2_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_X3_MASK                       0xFF000000
#define TMC2241_X3_SHIFT                      24
#define TMC2241_X3_FIELD                      ((RegisterField) {TMC2241_X3_MASK, TMC2241_X3_SHIFT, TMC2241_MSLUTSEL, false})
#define TMC2241_START_SIN_MASK                0x000000FF
#define TMC2241_START_SIN_SHIFT               0
#define TMC2241_START_SIN_FIELD               ((RegisterField) {TMC2241_START_SIN_MASK, TMC2241_START_SIN_SHIFT, TMC2241_MSLUTSTART, false})
#define TMC2241_START_SIN90_MASK              0x00FF0000
#define TMC2241_START_SIN90_SHIFT             16
#define TMC2241_START_SIN90_FIELD             ((RegisterField) {TMC2241_START_SIN90_MASK, TMC2241_START_SIN90_SHIFT, TMC2241_MSLUTSTART, false})
#define TMC2241_OFFSET_SIN90_MASK             0xFF000000
#define TMC2241_OFFSET_SIN90_SHIFT            24
#define TMC2241_OFFSET_SIN90_FIELD            ((RegisterField) {TMC2241_OFFSET_SIN90_MASK, TMC2241_OFFSET_SIN90_SHIFT, TMC2241_MSLUTSTART, false})
#define TMC2241_MSCNT_MASK                    0x000003FF
#define TMC2241_MSCNT_SHIFT                   0
#define TMC2241_MSCNT_FIELD                   ((RegisterField) {TMC2241_MSCNT_MASK, TMC2241_MSCNT_SHIFT, TMC2241_MSCNT, false})
#define TMC2241_CUR_B_MASK                    0x000001FF
#define TMC2241_CUR_B_SHIFT                   0
#define TMC2241_CUR_B_FIELD                   ((RegisterField) {TMC2241_CUR_B_MASK, TMC2241_CUR_B_SHIFT, TMC2241_MSCURACT, true})
#define TMC2241_CUR_A_MASK                    0x01FF0000
#define TMC2241_CUR_A_SHIFT                   16
#define TMC2241_CUR_A_FIELD                   ((RegisterField) {TMC2241_CUR_A_MASK, TMC2241_CUR_A_SHIFT, TMC2241_MSCURACT, true})
#define TMC2241_TOFF_MASK                     0x0000000F
#define TMC2241_TOFF_SHIFT                    0
#define TMC2241_TOFF_FIELD                    ((RegisterField) {TMC2241_TOFF_MASK, TMC2241_TOFF_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_HSTRT_TFD210_MASK             0x00000070
#define TMC2241_HSTRT_TFD210_SHIFT            4
#define TMC2241_HSTRT_TFD210_FIELD            ((RegisterField) {TMC2241_HSTRT_TFD210_MASK, TMC2241_HSTRT_TFD210_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_HEND_OFFSET_MASK              0x00000780
#define TMC2241_HEND_OFFSET_SHIFT             7
#define TMC2241_HEND_OFFSET_FIELD             ((RegisterField) {TMC2241_HEND_OFFSET_MASK, TMC2241_HEND_OFFSET_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_FD3_MASK                      0x00000800
#define TMC2241_FD3_SHIFT                     11
#define TMC2241_FD3_FIELD                     ((RegisterField) {TMC2241_FD3_MASK, TMC2241_FD3_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_DISFDCC_MASK                  0x00001000
#define TMC2241_DISFDCC_SHIFT                 12
#define TMC2241_DISFDCC_FIELD                 ((RegisterField) {TMC2241_DISFDCC_MASK, TMC2241_DISFDCC_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_CHM_MASK                      0x00004000
#define TMC2241_CHM_SHIFT                     14
#define TMC2241_CHM_FIELD                     ((RegisterField) {TMC2241_CHM_MASK, TMC2241_CHM_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_TBL_MASK                      0x00018000
#define TMC2241_TBL_SHIFT                     15
#define TMC2241_TBL_FIELD                     ((RegisterField) {TMC2241_TBL_MASK, TMC2241_TBL_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_VHIGHFS_MASK                  0x00040000
#define TMC2241_VHIGHFS_SHIFT                 18
#define TMC2241_VHIGHFS_FIELD                 ((RegisterField) {TMC2241_VHIGHFS_MASK, TMC2241_VHIGHFS_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_VHIGHCHM_MASK                 0x00080000
#define TMC2241_VHIGHCHM_SHIFT                19
#define TMC2241_VHIGHCHM_FIELD                ((RegisterField) {TMC2241_VHIGHCHM_MASK, TMC2241_VHIGHCHM_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_TPFD_MASK                     0x00F00000
#define TMC2241_TPFD_SHIFT                    20
#define TMC2241_TPFD_FIELD                    ((RegisterField) {TMC2241_TPFD_MASK, TMC2241_TPFD_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_MRES_MASK                     0x0F000000
#define TMC2241_MRES_SHIFT                    24
#define TMC2241_MRES_FIELD                    ((RegisterField) {TMC2241_MRES_MASK, TMC2241_MRES_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_INTPOL_MASK                   0x10000000
#define TMC2241_INTPOL_SHIFT                  28
#define TMC2241_INTPOL_FIELD                  ((RegisterField) {TMC2241_INTPOL_MASK, TMC2241_INTPOL_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_DEDGE_MASK                    0x20000000
#define TMC2241_DEDGE_SHIFT                   29
#define TMC2241_DEDGE_FIELD                   ((RegisterField) {TMC2241_DEDGE_MASK, TMC2241_DEDGE_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_DISS2G_MASK                   0x40000000
#define TMC2241_DISS2G_SHIFT                  30
#define TMC2241_DISS2G_FIELD                  ((RegisterField) {TMC2241_DISS2G_MASK, TMC2241_DISS2G_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_DISS2VS_MASK                  0x80000000
#define TMC2241_DISS2VS_SHIFT                 31
#define TMC2241_DISS2VS_FIELD                 ((RegisterField) {TMC2241_DISS2VS_MASK, TMC2241_DISS2VS_SHIFT, TMC2241_CHOPCONF, false})
#define TMC2241_SEMIN_MASK                    0x0000000F
#define TMC2241_SEMIN_SHIFT                   0
#define TMC2241_SEMIN_FIELD                   ((RegisterField) {TMC2241_SEMIN_MASK, TMC2241_SEMIN_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SEUP_MASK                     0x00000060
#define TMC2241_SEUP_SHIFT                    5
#define TMC2241_SEUP_FIELD                    ((RegisterField) {TMC2241_SEUP_MASK, TMC2241_SEUP_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SEMAX_MASK                    0x00000F00
#define TMC2241_SEMAX_SHIFT                   8
#define TMC2241_SEMAX_FIELD                   ((RegisterField) {TMC2241_SEMAX_MASK, TMC2241_SEMAX_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SEDN_MASK                     0x00006000
#define TMC2241_SEDN_SHIFT                    13
#define TMC2241_SEDN_FIELD                    ((RegisterField) {TMC2241_SEDN_MASK, TMC2241_SEDN_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SEIMIN_MASK                   0x00008000
#define TMC2241_SEIMIN_SHIFT                  15
#define TMC2241_SEIMIN_FIELD                  ((RegisterField) {TMC2241_SEIMIN_MASK, TMC2241_SEIMIN_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SGT_MASK                      0x007F0000
#define TMC2241_SGT_SHIFT                     16
#define TMC2241_SGT_FIELD                     ((RegisterField) {TMC2241_SGT_MASK, TMC2241_SGT_SHIFT, TMC2241_COOLCONF, true})
#define TMC2241_SFILT_MASK                    0x01000000
#define TMC2241_SFILT_SHIFT                   24
#define TMC2241_SFILT_FIELD                   ((RegisterField) {TMC2241_SFILT_MASK, TMC2241_SFILT_SHIFT, TMC2241_COOLCONF, false})
#define TMC2241_SG_RESULT_MASK                0x000003FF
#define TMC2241_SG_RESULT_SHIFT               0
#define TMC2241_SG_RESULT_FIELD               ((RegisterField) {TMC2241_SG_RESULT_MASK, TMC2241_SG_RESULT_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_S2VSA_MASK                    0x00001000
#define TMC2241_S2VSA_SHIFT                   12
#define TMC2241_S2VSA_FIELD                   ((RegisterField) {TMC2241_S2VSA_MASK, TMC2241_S2VSA_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_S2VSB_MASK                    0x00002000
#define TMC2241_S2VSB_SHIFT                   13
#define TMC2241_S2VSB_FIELD                   ((RegisterField) {TMC2241_S2VSB_MASK, TMC2241_S2VSB_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_STEALTH_MASK                  0x00004000
#define TMC2241_STEALTH_SHIFT                 14
#define TMC2241_STEALTH_FIELD                 ((RegisterField) {TMC2241_STEALTH_MASK, TMC2241_STEALTH_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_FSACTIVE_MASK                 0x00008000
#define TMC2241_FSACTIVE_SHIFT                15
#define TMC2241_FSACTIVE_FIELD                ((RegisterField) {TMC2241_FSACTIVE_MASK, TMC2241_FSACTIVE_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_CS_ACTUAL_MASK                0x001F0000
#define TMC2241_CS_ACTUAL_SHIFT               16
#define TMC2241_CS_ACTUAL_FIELD               ((RegisterField) {TMC2241_CS_ACTUAL_MASK, TMC2241_CS_ACTUAL_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_STALLGUARD_MASK               0x01000000
#define TMC2241_STALLGUARD_SHIFT              24
#define TMC2241_STALLGUARD_FIELD              ((RegisterField) {TMC2241_STALLGUARD_MASK, TMC2241_STALLGUARD_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_OT_MASK                       0x02000000
#define TMC2241_OT_SHIFT                      25
#define TMC2241_OT_FIELD                      ((RegisterField) {TMC2241_OT_MASK, TMC2241_OT_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_OTPW_MASK                     0x04000000
#define TMC2241_OTPW_SHIFT                    26
#define TMC2241_OTPW_FIELD                    ((RegisterField) {TMC2241_OTPW_MASK, TMC2241_OTPW_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_S2GA_MASK                     0x08000000
#define TMC2241_S2GA_SHIFT                    27
#define TMC2241_S2GA_FIELD                    ((RegisterField) {TMC2241_S2GA_MASK, TMC2241_S2GA_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_S2GB_MASK                     0x10000000
#define TMC2241_S2GB_SHIFT                    28
#define TMC2241_S2GB_FIELD                    ((RegisterField) {TMC2241_S2GB_MASK, TMC2241_S2GB_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_OLA_MASK                      0x20000000
#define TMC2241_OLA_SHIFT                     29
#define TMC2241_OLA_FIELD                     ((RegisterField) {TMC2241_OLA_MASK, TMC2241_OLA_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_OLB_MASK                      0x40000000
#define TMC2241_OLB_SHIFT                     30
#define TMC2241_OLB_FIELD                     ((RegisterField) {TMC2241_OLB_MASK, TMC2241_OLB_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_STST_MASK                     0x80000000
#define TMC2241_STST_SHIFT                    31
#define TMC2241_STST_FIELD                    ((RegisterField) {TMC2241_STST_MASK, TMC2241_STST_SHIFT, TMC2241_DRV_STATUS, false})
#define TMC2241_PWM_OFS_MASK                  0x000000FF
#define TMC2241_PWM_OFS_SHIFT                 0
#define TMC2241_PWM_OFS_FIELD                 ((RegisterField) {TMC2241_PWM_OFS_MASK, TMC2241_PWM_OFS_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_GRAD_MASK                 0x0000FF00
#define TMC2241_PWM_GRAD_SHIFT                8
#define TMC2241_PWM_GRAD_FIELD                ((RegisterField) {TMC2241_PWM_GRAD_MASK, TMC2241_PWM_GRAD_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_FREQ_MASK                 0x00030000
#define TMC2241_PWM_FREQ_SHIFT                16
#define TMC2241_PWM_FREQ_FIELD                ((RegisterField) {TMC2241_PWM_FREQ_MASK, TMC2241_PWM_FREQ_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_AUTOSCALE_MASK            0x00040000
#define TMC2241_PWM_AUTOSCALE_SHIFT           18
#define TMC2241_PWM_AUTOSCALE_FIELD           ((RegisterField) {TMC2241_PWM_AUTOSCALE_MASK, TMC2241_PWM_AUTOSCALE_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_AUTOGRAD_MASK             0x00080000
#define TMC2241_PWM_AUTOGRAD_SHIFT            19
#define TMC2241_PWM_AUTOGRAD_FIELD            ((RegisterField) {TMC2241_PWM_AUTOGRAD_MASK, TMC2241_PWM_AUTOGRAD_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_FREEWHEEL_MASK                0x00300000
#define TMC2241_FREEWHEEL_SHIFT               20
#define TMC2241_FREEWHEEL_FIELD               ((RegisterField) {TMC2241_FREEWHEEL_MASK, TMC2241_FREEWHEEL_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_MEAS_SD_ENABLE_MASK       0x00400000
#define TMC2241_PWM_MEAS_SD_ENABLE_SHIFT      22
#define TMC2241_PWM_MEAS_SD_ENABLE_FIELD      ((RegisterField) {TMC2241_PWM_MEAS_SD_ENABLE_MASK, TMC2241_PWM_MEAS_SD_ENABLE_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_DIS_REG_STST_MASK         0x00800000
#define TMC2241_PWM_DIS_REG_STST_SHIFT        23
#define TMC2241_PWM_DIS_REG_STST_FIELD        ((RegisterField) {TMC2241_PWM_DIS_REG_STST_MASK, TMC2241_PWM_DIS_REG_STST_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_REG_MASK                  0x0F000000
#define TMC2241_PWM_REG_SHIFT                 24
#define TMC2241_PWM_REG_FIELD                 ((RegisterField) {TMC2241_PWM_REG_MASK, TMC2241_PWM_REG_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_LIM_MASK                  0xF0000000
#define TMC2241_PWM_LIM_SHIFT                 28
#define TMC2241_PWM_LIM_FIELD                 ((RegisterField) {TMC2241_PWM_LIM_MASK, TMC2241_PWM_LIM_SHIFT, TMC2241_PWMCONF, false})
#define TMC2241_PWM_SCALE_SUM_MASK            0x000003FF
#define TMC2241_PWM_SCALE_SUM_SHIFT           0
#define TMC2241_PWM_SCALE_SUM_FIELD           ((RegisterField) {TMC2241_PWM_SCALE_SUM_MASK, TMC2241_PWM_SCALE_SUM_SHIFT, TMC2241_PWM_SCALE, false})
#define TMC2241_PWM_SCALE_AUTO_MASK           0x01FF0000
#define TMC2241_PWM_SCALE_AUTO_SHIFT          16
#define TMC2241_PWM_SCALE_AUTO_FIELD          ((RegisterField) {TMC2241_PWM_SCALE_AUTO_MASK, TMC2241_PWM_SCALE_AUTO_SHIFT, TMC2241_PWM_SCALE, false})
#define TMC2241_PWM_OFS_AUTO_MASK             0x000000FF
#define TMC2241_PWM_OFS_AUTO_SHIFT            0
#define TMC2241_PWM_OFS_AUTO_FIELD            ((RegisterField) {TMC2241_PWM_OFS_AUTO_MASK, TMC2241_PWM_OFS_AUTO_SHIFT, TMC2241_PWM_AUTO, false})
#define TMC2241_PWM_GRAD_AUTO_MASK            0x00FF0000
#define TMC2241_PWM_GRAD_AUTO_SHIFT           16
#define TMC2241_PWM_GRAD_AUTO_FIELD           ((RegisterField) {TMC2241_PWM_GRAD_AUTO_MASK, TMC2241_PWM_GRAD_AUTO_SHIFT, TMC2241_PWM_AUTO, false})
#define TMC2241_SG4_THRS_MASK                 0x000000FF
#define TMC2241_SG4_THRS_SHIFT                0
#define TMC2241_SG4_THRS_FIELD                ((RegisterField) {TMC2241_SG4_THRS_MASK, TMC2241_SG4_THRS_SHIFT, TMC2241_SG4_CONF, false})
#define TMC2241_SG4_FILT_EN_MASK              0x00000100
#define TMC2241_SG4_FILT_EN_SHIFT             8
#define TMC2241_SG4_FILT_EN_FIELD             ((RegisterField) {TMC2241_SG4_FILT_EN_MASK, TMC2241_SG4_FILT_EN_SHIFT, TMC2241_SG4_CONF, false})
#define TMC2241_SG_ANGLE_OFFSET_MASK          0x00000200
#define TMC2241_SG_ANGLE_OFFSET_SHIFT         9
#define TMC2241_SG_ANGLE_OFFSET_FIELD         ((RegisterField) {TMC2241_SG_ANGLE_OFFSET_MASK, TMC2241_SG_ANGLE_OFFSET_SHIFT, TMC2241_SG4_CONF, false})
#define TMC2241_SG4_RESULT_MASK               0x000003FF
#define TMC2241_SG4_RESULT_SHIFT              0
#define TMC2241_SG4_RESULT_FIELD              ((RegisterField) {TMC2241_SG4_RESULT_MASK, TMC2241_SG4_RESULT_SHIFT, TMC2241_SG4_RESULT, false})
#define TMC2241_SG4_IND_0_MASK                0x000000FF
#define TMC2241_SG4_IND_0_SHIFT               0
#define TMC2241_SG4_IND_0_FIELD               ((RegisterField) {TMC2241_SG4_IND_0_MASK, TMC2241_SG4_IND_0_SHIFT, TMC2241_SG4_IND, false})
#define TMC2241_SG4_IND_1_MASK                0x0000FF00
#define TMC2241_SG4_IND_1_SHIFT               8
#define TMC2241_SG4_IND_1_FIELD               ((RegisterField) {TMC2241_SG4_IND_1_MASK, TMC2241_SG4_IND_1_SHIFT, TMC2241_SG4_IND, false})
#define TMC2241_SG4_IND_2_MASK                0x00FF0000
#define TMC2241_SG4_IND_2_SHIFT               16
#define TMC2241_SG4_IND_2_FIELD               ((RegisterField) {TMC2241_SG4_IND_2_MASK, TMC2241_SG4_IND_2_SHIFT, TMC2241_SG4_IND, false})
#define TMC2241_SG4_IND_3_MASK                0xFF000000
#define TMC2241_SG4_IND_3_SHIFT               24
#define TMC2241_SG4_IND_3_FIELD               ((RegisterField) {TMC2241_SG4_IND_3_MASK, TMC2241_SG4_IND_3_SHIFT, TMC2241_SG4_IND, false})
#endif
