/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2130_HW_ABSTRACTION
#define TMC2130_HW_ABSTRACTION


// Constants

#define TMC2130_REGISTER_COUNT   128 // Default register count
#define TMC2130_MOTORS           1
#define TMC2130_WRITE_BIT        0x80
#define TMC2130_ADDRESS_MASK     0x7F
#define TMC2130_MAX_VELOCITY     (int32_t)  2147483647
#define TMC2130_MAX_ACCELERATION (uint32_t)  16777215uL


// Registers

#define TMC2130_GCONF       0x00
#define TMC2130_GSTAT       0x01
#define TMC2130_IOIN        0x04

#define TMC2130_IHOLD_IRUN  0x10
#define TMC2130_TPOWERDOWN  0x11
#define TMC2130_TSTEP       0x12
#define TMC2130_TPWMTHRS    0x13
#define TMC2130_TCOOLTHRS   0x14
#define TMC2130_THIGH       0x15

#define TMC2130_XDIRECT     0x2D

#define TMC2130_VDCMIN      0x33

#define TMC2130_MSLUT0      0x60
#define TMC2130_MSLUT1      0x61
#define TMC2130_MSLUT2      0x62
#define TMC2130_MSLUT3      0x63
#define TMC2130_MSLUT4      0x64
#define TMC2130_MSLUT5      0x65
#define TMC2130_MSLUT6      0x66
#define TMC2130_MSLUT7      0x67
#define TMC2130_MSLUTSEL    0x68
#define TMC2130_MSLUTSTART  0x69
#define TMC2130_MSCNT       0x6A
#define TMC2130_MSCURACT    0x6B

#define TMC2130_CHOPCONF    0x6C
#define TMC2130_COOLCONF    0x6D
#define TMC2130_DCCTRL      0x6E
#define TMC2130_DRV_STATUS  0x6F
#define TMC2130_PWMCONF     0x70
#define TMC2130_PWM_SCALE   0x71
#define TMC2130_ENCM_CTRL   0x72
#define TMC2130_LOST_STEPS  0x73

//2. definition
#define TMC2130_MSLUT__     0x60


// Register fields

#define TMC2130_I_SCALE_ANALOG_MASK           0x00000001
#define TMC2130_I_SCALE_ANALOG_SHIFT          0
#define TMC2130_I_SCALE_ANALOG_FIELD          ((RegisterField) {TMC2130_I_SCALE_ANALOG_MASK, TMC2130_I_SCALE_ANALOG_SHIFT, TMC2130_GCONF, false})
#define TMC2130_INTERNAL_RSENSE_MASK          0x00000002
#define TMC2130_INTERNAL_RSENSE_SHIFT         1
#define TMC2130_INTERNAL_RSENSE_FIELD         ((RegisterField) {TMC2130_INTERNAL_RSENSE_MASK, TMC2130_INTERNAL_RSENSE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_EN_PWM_MODE_MASK              0x00000004
#define TMC2130_EN_PWM_MODE_SHIFT             2
#define TMC2130_EN_PWM_MODE_FIELD             ((RegisterField) {TMC2130_EN_PWM_MODE_MASK, TMC2130_EN_PWM_MODE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_ENC_COMMUTATION_MASK          0x00000008
#define TMC2130_ENC_COMMUTATION_SHIFT         3
#define TMC2130_ENC_COMMUTATION_FIELD         ((RegisterField) {TMC2130_ENC_COMMUTATION_MASK, TMC2130_ENC_COMMUTATION_SHIFT, TMC2130_GCONF, false})
#define TMC2130_SHAFT_MASK                    0x00000010
#define TMC2130_SHAFT_SHIFT                   4
#define TMC2130_SHAFT_FIELD                   ((RegisterField) {TMC2130_SHAFT_MASK, TMC2130_SHAFT_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG0_ERROR_MASK              0x00000020
#define TMC2130_DIAG0_ERROR_SHIFT             5
#define TMC2130_DIAG0_ERROR_FIELD             ((RegisterField) {TMC2130_DIAG0_ERROR_MASK, TMC2130_DIAG0_ERROR_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG0_OTPW_MASK               0x00000040
#define TMC2130_DIAG0_OTPW_SHIFT              6
#define TMC2130_DIAG0_OTPW_FIELD              ((RegisterField) {TMC2130_DIAG0_OTPW_MASK, TMC2130_DIAG0_OTPW_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG0_STALL_MASK              0x00000080
#define TMC2130_DIAG0_STALL_SHIFT             7
#define TMC2130_DIAG0_STALL_FIELD             ((RegisterField) {TMC2130_DIAG0_STALL_MASK, TMC2130_DIAG0_STALL_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG1_STALL_MASK              0x00000100
#define TMC2130_DIAG1_STALL_SHIFT             8
#define TMC2130_DIAG1_STALL_FIELD             ((RegisterField) {TMC2130_DIAG1_STALL_MASK, TMC2130_DIAG1_STALL_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG1_INDEX_MASK              0x00000200
#define TMC2130_DIAG1_INDEX_SHIFT             9
#define TMC2130_DIAG1_INDEX_FIELD             ((RegisterField) {TMC2130_DIAG1_INDEX_MASK, TMC2130_DIAG1_INDEX_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG1_ONSTATE_MASK            0x00000400
#define TMC2130_DIAG1_ONSTATE_SHIFT           10
#define TMC2130_DIAG1_ONSTATE_FIELD           ((RegisterField) {TMC2130_DIAG1_ONSTATE_MASK, TMC2130_DIAG1_ONSTATE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG1_STEPS_SKIPPED_MASK      0x00000800
#define TMC2130_DIAG1_STEPS_SKIPPED_SHIFT     11
#define TMC2130_DIAG1_STEPS_SKIPPED_FIELD     ((RegisterField) {TMC2130_DIAG1_STEPS_SKIPPED_MASK, TMC2130_DIAG1_STEPS_SKIPPED_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG0_INT_PUSHPULL_MASK       0x00001000
#define TMC2130_DIAG0_INT_PUSHPULL_SHIFT      12
#define TMC2130_DIAG0_INT_PUSHPULL_FIELD      ((RegisterField) {TMC2130_DIAG0_INT_PUSHPULL_MASK, TMC2130_DIAG0_INT_PUSHPULL_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIAG1_POSCOMP_PUSHPULL_MASK   0x00002000
#define TMC2130_DIAG1_POSCOMP_PUSHPULL_SHIFT  13
#define TMC2130_DIAG1_POSCOMP_PUSHPULL_FIELD  ((RegisterField) {TMC2130_DIAG1_POSCOMP_PUSHPULL_MASK, TMC2130_DIAG1_POSCOMP_PUSHPULL_SHIFT, TMC2130_GCONF, false})
#define TMC2130_SMALL_HYSTERESIS_MASK         0x00004000
#define TMC2130_SMALL_HYSTERESIS_SHIFT        14
#define TMC2130_SMALL_HYSTERESIS_FIELD        ((RegisterField) {TMC2130_SMALL_HYSTERESIS_MASK, TMC2130_SMALL_HYSTERESIS_SHIFT, TMC2130_GCONF, false})
#define TMC2130_STOP_ENABLE_MASK              0x00008000
#define TMC2130_STOP_ENABLE_SHIFT             15
#define TMC2130_STOP_ENABLE_FIELD             ((RegisterField) {TMC2130_STOP_ENABLE_MASK, TMC2130_STOP_ENABLE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_DIRECT_MODE_MASK              0x00010000
#define TMC2130_DIRECT_MODE_SHIFT             16
#define TMC2130_DIRECT_MODE_FIELD             ((RegisterField) {TMC2130_DIRECT_MODE_MASK, TMC2130_DIRECT_MODE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_TEST_MODE_MASK                0x00020000
#define TMC2130_TEST_MODE_SHIFT               17
#define TMC2130_TEST_MODE_FIELD               ((RegisterField) {TMC2130_TEST_MODE_MASK, TMC2130_TEST_MODE_SHIFT, TMC2130_GCONF, false})
#define TMC2130_RESET_MASK                    0x00000001
#define TMC2130_RESET_SHIFT                   0
#define TMC2130_RESET_FIELD                   ((RegisterField) {TMC2130_RESET_MASK, TMC2130_RESET_SHIFT, TMC2130_GSTAT, false})
#define TMC2130_DRV_ERR_MASK                  0x00000002
#define TMC2130_DRV_ERR_SHIFT                 1
#define TMC2130_DRV_ERR_FIELD                 ((RegisterField) {TMC2130_DRV_ERR_MASK, TMC2130_DRV_ERR_SHIFT, TMC2130_GSTAT, false})
#define TMC2130_UV_CP_MASK                    0x00000004
#define TMC2130_UV_CP_SHIFT                   2
#define TMC2130_UV_CP_FIELD                   ((RegisterField) {TMC2130_UV_CP_MASK, TMC2130_UV_CP_SHIFT, TMC2130_GSTAT, false})
#define TMC2130_REFL_STEP_MASK                0x00000001
#define TMC2130_REFL_STEP_SHIFT               0
#define TMC2130_REFL_STEP_FIELD               ((RegisterField) {TMC2130_REFL_STEP_MASK, TMC2130_REFL_STEP_SHIFT, TMC2130_IOIN, false})
#define TMC2130_REFR_DIR_MASK                 0x00000002
#define TMC2130_REFR_DIR_SHIFT                1
#define TMC2130_REFR_DIR_FIELD                ((RegisterField) {TMC2130_REFR_DIR_MASK, TMC2130_REFR_DIR_SHIFT, TMC2130_IOIN, false})
#define TMC2130_ENCB_DCEN_CFG4_MASK           0x00000004
#define TMC2130_ENCB_DCEN_CFG4_SHIFT          2
#define TMC2130_ENCB_DCEN_CFG4_FIELD          ((RegisterField) {TMC2130_ENCB_DCEN_CFG4_MASK, TMC2130_ENCB_DCEN_CFG4_SHIFT, TMC2130_IOIN, false})
#define TMC2130_ENCA_DCIN_CFG5_MASK           0x00000008
#define TMC2130_ENCA_DCIN_CFG5_SHIFT          3
#define TMC2130_ENCA_DCIN_CFG5_FIELD          ((RegisterField) {TMC2130_ENCA_DCIN_CFG5_MASK, TMC2130_ENCA_DCIN_CFG5_SHIFT, TMC2130_IOIN, false})
#define TMC2130_DRV_ENN_CFG6_MASK             0x00000010
#define TMC2130_DRV_ENN_CFG6_SHIFT            4
#define TMC2130_DRV_ENN_CFG6_FIELD            ((RegisterField) {TMC2130_DRV_ENN_CFG6_MASK, TMC2130_DRV_ENN_CFG6_SHIFT, TMC2130_IOIN, false})
#define TMC2130_ENC_N_DCO_MASK                0x00000020
#define TMC2130_ENC_N_DCO_SHIFT               5
#define TMC2130_ENC_N_DCO_FIELD               ((RegisterField) {TMC2130_ENC_N_DCO_MASK, TMC2130_ENC_N_DCO_SHIFT, TMC2130_IOIN, false})
#define TMC2130_VERSION_MASK                  0xFF000000
#define TMC2130_VERSION_SHIFT                 24
#define TMC2130_VERSION_FIELD                 ((RegisterField) {TMC2130_VERSION_MASK, TMC2130_VERSION_SHIFT, TMC2130_IOIN, false})
#define TMC2130_IHOLD_MASK                    0x0000001F
#define TMC2130_IHOLD_SHIFT                   0
#define TMC2130_IHOLD_FIELD                   ((RegisterField) {TMC2130_IHOLD_MASK, TMC2130_IHOLD_SHIFT, TMC2130_IHOLD_IRUN, false})
#define TMC2130_IRUN_MASK                     0x00001F00
#define TMC2130_IRUN_SHIFT                    8
#define TMC2130_IRUN_FIELD                    ((RegisterField) {TMC2130_IRUN_MASK, TMC2130_IRUN_SHIFT, TMC2130_IHOLD_IRUN, false})
#define TMC2130_IHOLDDELAY_MASK               0x000F0000
#define TMC2130_IHOLDDELAY_SHIFT              16
#define TMC2130_IHOLDDELAY_FIELD              ((RegisterField) {TMC2130_IHOLDDELAY_MASK, TMC2130_IHOLDDELAY_SHIFT, TMC2130_IHOLD_IRUN, false})
#define TMC2130_TPOWERDOWN_MASK               0x000000FF
#define TMC2130_TPOWERDOWN_SHIFT              0
#define TMC2130_TPOWERDOWN_FIELD              ((RegisterField) {TMC2130_TPOWERDOWN_MASK, TMC2130_TPOWERDOWN_SHIFT, TMC2130_TPOWERDOWN, false})
#define TMC2130_TSTEP_MASK                    0x000FFFFF
#define TMC2130_TSTEP_SHIFT                   0
#define TMC2130_TSTEP_FIELD                   ((RegisterField) {TMC2130_TSTEP_MASK, TMC2130_TSTEP_SHIFT, TMC2130_TSTEP, false})
#define TMC2130_TPWMTHRS_MASK                 0x000FFFFF
#define TMC2130_TPWMTHRS_SHIFT                0
#define TMC2130_TPWMTHRS_FIELD                ((RegisterField) {TMC2130_TPWMTHRS_MASK, TMC2130_TPWMTHRS_SHIFT, TMC2130_TPWMTHRS, false})
#define TMC2130_TCOOLTHRS_MASK                0x000FFFFF
#define TMC2130_TCOOLTHRS_SHIFT               0
#define TMC2130_TCOOLTHRS_FIELD               ((RegisterField) {TMC2130_TCOOLTHRS_MASK, TMC2130_TCOOLTHRS_SHIFT, TMC2130_TCOOLTHRS, false})
#define TMC2130_THIGH_MASK                    0x000FFFFF
#define TMC2130_THIGH_SHIFT                   0
#define TMC2130_THIGH_FIELD                   ((RegisterField) {TMC2130_THIGH_MASK, TMC2130_THIGH_SHIFT, TMC2130_THIGH, false})
#define TMC2130_DIRECT_CURRENT_A_MASK         0x000001FF
#define TMC2130_DIRECT_CURRENT_A_SHIFT        0
#define TMC2130_DIRECT_CURRENT_A_FIELD        ((RegisterField) {TMC2130_DIRECT_CURRENT_A_MASK, TMC2130_DIRECT_CURRENT_A_SHIFT, TMC2130_XDIRECT, true})
#define TMC2130_DIRECT_CURRENT_B_MASK         0x01FF0000
#define TMC2130_DIRECT_CURRENT_B_SHIFT        16
#define TMC2130_DIRECT_CURRENT_B_FIELD        ((RegisterField) {TMC2130_DIRECT_CURRENT_B_MASK, TMC2130_DIRECT_CURRENT_B_SHIFT, TMC2130_XDIRECT, true})
#define TMC2130_VDCMIN_MASK                   0x07FFFFFF
#define TMC2130_VDCMIN_SHIFT                  0
#define TMC2130_VDCMIN_FIELD                  ((RegisterField) {TMC2130_VDCMIN_MASK, TMC2130_VDCMIN_SHIFT, TMC2130_VDCMIN, false})
#define TMC2130_OFS0_MASK                     0x00000001
#define TMC2130_OFS0_SHIFT                    0
#define TMC2130_OFS0_FIELD                    ((RegisterField) {TMC2130_OFS0_MASK, TMC2130_OFS0_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS1_MASK                     0x00000002
#define TMC2130_OFS1_SHIFT                    1
#define TMC2130_OFS1_FIELD                    ((RegisterField) {TMC2130_OFS1_MASK, TMC2130_OFS1_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS2_MASK                     0x00000004
#define TMC2130_OFS2_SHIFT                    2
#define TMC2130_OFS2_FIELD                    ((RegisterField) {TMC2130_OFS2_MASK, TMC2130_OFS2_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS3_MASK                     0x00000008
#define TMC2130_OFS3_SHIFT                    3
#define TMC2130_OFS3_FIELD                    ((RegisterField) {TMC2130_OFS3_MASK, TMC2130_OFS3_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS4_MASK                     0x00000010
#define TMC2130_OFS4_SHIFT                    4
#define TMC2130_OFS4_FIELD                    ((RegisterField) {TMC2130_OFS4_MASK, TMC2130_OFS4_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS5_MASK                     0x00000020
#define TMC2130_OFS5_SHIFT                    5
#define TMC2130_OFS5_FIELD                    ((RegisterField) {TMC2130_OFS5_MASK, TMC2130_OFS5_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS6_MASK                     0x00000040
#define TMC2130_OFS6_SHIFT                    6
#define TMC2130_OFS6_FIELD                    ((RegisterField) {TMC2130_OFS6_MASK, TMC2130_OFS6_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS7_MASK                     0x00000080
#define TMC2130_OFS7_SHIFT                    7
#define TMC2130_OFS7_FIELD                    ((RegisterField) {TMC2130_OFS7_MASK, TMC2130_OFS7_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS8_MASK                     0x00000100
#define TMC2130_OFS8_SHIFT                    8
#define TMC2130_OFS8_FIELD                    ((RegisterField) {TMC2130_OFS8_MASK, TMC2130_OFS8_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS9_MASK                     0x00000200
#define TMC2130_OFS9_SHIFT                    9
#define TMC2130_OFS9_FIELD                    ((RegisterField) {TMC2130_OFS9_MASK, TMC2130_OFS9_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS10_MASK                    0x00000400
#define TMC2130_OFS10_SHIFT                   10
#define TMC2130_OFS10_FIELD                   ((RegisterField) {TMC2130_OFS10_MASK, TMC2130_OFS10_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS11_MASK                    0x00000800
#define TMC2130_OFS11_SHIFT                   11
#define TMC2130_OFS11_FIELD                   ((RegisterField) {TMC2130_OFS11_MASK, TMC2130_OFS11_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS12_MASK                    0x00001000
#define TMC2130_OFS12_SHIFT                   12
#define TMC2130_OFS12_FIELD                   ((RegisterField) {TMC2130_OFS12_MASK, TMC2130_OFS12_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS13_MASK                    0x00002000
#define TMC2130_OFS13_SHIFT                   13
#define TMC2130_OFS13_FIELD                   ((RegisterField) {TMC2130_OFS13_MASK, TMC2130_OFS13_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS14_MASK                    0x00004000
#define TMC2130_OFS14_SHIFT                   14
#define TMC2130_OFS14_FIELD                   ((RegisterField) {TMC2130_OFS14_MASK, TMC2130_OFS14_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS15_MASK                    0x00008000
#define TMC2130_OFS15_SHIFT                   15
#define TMC2130_OFS15_FIELD                   ((RegisterField) {TMC2130_OFS15_MASK, TMC2130_OFS15_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS16_MASK                    0x00010000
#define TMC2130_OFS16_SHIFT                   16
#define TMC2130_OFS16_FIELD                   ((RegisterField) {TMC2130_OFS16_MASK, TMC2130_OFS16_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS17_MASK                    0x00020000
#define TMC2130_OFS17_SHIFT                   17
#define TMC2130_OFS17_FIELD                   ((RegisterField) {TMC2130_OFS17_MASK, TMC2130_OFS17_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS18_MASK                    0x00040000
#define TMC2130_OFS18_SHIFT                   18
#define TMC2130_OFS18_FIELD                   ((RegisterField) {TMC2130_OFS18_MASK, TMC2130_OFS18_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS19_MASK                    0x00080000
#define TMC2130_OFS19_SHIFT                   19
#define TMC2130_OFS19_FIELD                   ((RegisterField) {TMC2130_OFS19_MASK, TMC2130_OFS19_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS20_MASK                    0x00100000
#define TMC2130_OFS20_SHIFT                   20
#define TMC2130_OFS20_FIELD                   ((RegisterField) {TMC2130_OFS20_MASK, TMC2130_OFS20_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS21_MASK                    0x00200000
#define TMC2130_OFS21_SHIFT                   21
#define TMC2130_OFS21_FIELD                   ((RegisterField) {TMC2130_OFS21_MASK, TMC2130_OFS21_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS22_MASK                    0x00400000
#define TMC2130_OFS22_SHIFT                   22
#define TMC2130_OFS22_FIELD                   ((RegisterField) {TMC2130_OFS22_MASK, TMC2130_OFS22_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS23_MASK                    0x00800000
#define TMC2130_OFS23_SHIFT                   23
#define TMC2130_OFS23_FIELD                   ((RegisterField) {TMC2130_OFS23_MASK, TMC2130_OFS23_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS24_MASK                    0x01000000
#define TMC2130_OFS24_SHIFT                   24
#define TMC2130_OFS24_FIELD                   ((RegisterField) {TMC2130_OFS24_MASK, TMC2130_OFS24_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS25_MASK                    0x02000000
#define TMC2130_OFS25_SHIFT                   25
#define TMC2130_OFS25_FIELD                   ((RegisterField) {TMC2130_OFS25_MASK, TMC2130_OFS25_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS26_MASK                    0x04000000
#define TMC2130_OFS26_SHIFT                   26
#define TMC2130_OFS26_FIELD                   ((RegisterField) {TMC2130_OFS26_MASK, TMC2130_OFS26_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS27_MASK                    0x08000000
#define TMC2130_OFS27_SHIFT                   27
#define TMC2130_OFS27_FIELD                   ((RegisterField) {TMC2130_OFS27_MASK, TMC2130_OFS27_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS28_MASK                    0x10000000
#define TMC2130_OFS28_SHIFT                   28
#define TMC2130_OFS28_FIELD                   ((RegisterField) {TMC2130_OFS28_MASK, TMC2130_OFS28_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS29_MASK                    0x20000000
#define TMC2130_OFS29_SHIFT                   29
#define TMC2130_OFS29_FIELD                   ((RegisterField) {TMC2130_OFS29_MASK, TMC2130_OFS29_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS30_MASK                    0x40000000
#define TMC2130_OFS30_SHIFT                   30
#define TMC2130_OFS30_FIELD                   ((RegisterField) {TMC2130_OFS30_MASK, TMC2130_OFS30_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS31_MASK                    0x80000000
#define TMC2130_OFS31_SHIFT                   31
#define TMC2130_OFS31_FIELD                   ((RegisterField) {TMC2130_OFS31_MASK, TMC2130_OFS31_SHIFT, TMC2130_MSLUT[0], false})
#define TMC2130_OFS32_MASK                    0x00000001
#define TMC2130_OFS32_SHIFT                   0
#define TMC2130_OFS32_FIELD                   ((RegisterField) {TMC2130_OFS32_MASK, TMC2130_OFS32_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS33_MASK                    0x00000002
#define TMC2130_OFS33_SHIFT                   1
#define TMC2130_OFS33_FIELD                   ((RegisterField) {TMC2130_OFS33_MASK, TMC2130_OFS33_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS34_MASK                    0x00000004
#define TMC2130_OFS34_SHIFT                   2
#define TMC2130_OFS34_FIELD                   ((RegisterField) {TMC2130_OFS34_MASK, TMC2130_OFS34_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS35_MASK                    0x00000008
#define TMC2130_OFS35_SHIFT                   3
#define TMC2130_OFS35_FIELD                   ((RegisterField) {TMC2130_OFS35_MASK, TMC2130_OFS35_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS36_MASK                    0x00000010
#define TMC2130_OFS36_SHIFT                   4
#define TMC2130_OFS36_FIELD                   ((RegisterField) {TMC2130_OFS36_MASK, TMC2130_OFS36_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS37_MASK                    0x00000020
#define TMC2130_OFS37_SHIFT                   5
#define TMC2130_OFS37_FIELD                   ((RegisterField) {TMC2130_OFS37_MASK, TMC2130_OFS37_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS38_MASK                    0x00000040
#define TMC2130_OFS38_SHIFT                   6
#define TMC2130_OFS38_FIELD                   ((RegisterField) {TMC2130_OFS38_MASK, TMC2130_OFS38_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS39_MASK                    0x00000080
#define TMC2130_OFS39_SHIFT                   7
#define TMC2130_OFS39_FIELD                   ((RegisterField) {TMC2130_OFS39_MASK, TMC2130_OFS39_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS40_MASK                    0x00000100
#define TMC2130_OFS40_SHIFT                   8
#define TMC2130_OFS40_FIELD                   ((RegisterField) {TMC2130_OFS40_MASK, TMC2130_OFS40_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS41_MASK                    0x00000200
#define TMC2130_OFS41_SHIFT                   9
#define TMC2130_OFS41_FIELD                   ((RegisterField) {TMC2130_OFS41_MASK, TMC2130_OFS41_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS42_MASK                    0x00000400
#define TMC2130_OFS42_SHIFT                   10
#define TMC2130_OFS42_FIELD                   ((RegisterField) {TMC2130_OFS42_MASK, TMC2130_OFS42_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS43_MASK                    0x00000800
#define TMC2130_OFS43_SHIFT                   11
#define TMC2130_OFS43_FIELD                   ((RegisterField) {TMC2130_OFS43_MASK, TMC2130_OFS43_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS44_MASK                    0x00001000
#define TMC2130_OFS44_SHIFT                   12
#define TMC2130_OFS44_FIELD                   ((RegisterField) {TMC2130_OFS44_MASK, TMC2130_OFS44_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS45_MASK                    0x00002000
#define TMC2130_OFS45_SHIFT                   13
#define TMC2130_OFS45_FIELD                   ((RegisterField) {TMC2130_OFS45_MASK, TMC2130_OFS45_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS46_MASK                    0x00004000
#define TMC2130_OFS46_SHIFT                   14
#define TMC2130_OFS46_FIELD                   ((RegisterField) {TMC2130_OFS46_MASK, TMC2130_OFS46_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS47_MASK                    0x00008000
#define TMC2130_OFS47_SHIFT                   15
#define TMC2130_OFS47_FIELD                   ((RegisterField) {TMC2130_OFS47_MASK, TMC2130_OFS47_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS48_MASK                    0x00010000
#define TMC2130_OFS48_SHIFT                   16
#define TMC2130_OFS48_FIELD                   ((RegisterField) {TMC2130_OFS48_MASK, TMC2130_OFS48_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS49_MASK                    0x00020000
#define TMC2130_OFS49_SHIFT                   17
#define TMC2130_OFS49_FIELD                   ((RegisterField) {TMC2130_OFS49_MASK, TMC2130_OFS49_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS50_MASK                    0x00040000
#define TMC2130_OFS50_SHIFT                   18
#define TMC2130_OFS50_FIELD                   ((RegisterField) {TMC2130_OFS50_MASK, TMC2130_OFS50_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS51_MASK                    0x00080000
#define TMC2130_OFS51_SHIFT                   19
#define TMC2130_OFS51_FIELD                   ((RegisterField) {TMC2130_OFS51_MASK, TMC2130_OFS51_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS52_MASK                    0x00100000
#define TMC2130_OFS52_SHIFT                   20
#define TMC2130_OFS52_FIELD                   ((RegisterField) {TMC2130_OFS52_MASK, TMC2130_OFS52_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS53_MASK                    0x00200000
#define TMC2130_OFS53_SHIFT                   21
#define TMC2130_OFS53_FIELD                   ((RegisterField) {TMC2130_OFS53_MASK, TMC2130_OFS53_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS54_MASK                    0x00400000
#define TMC2130_OFS54_SHIFT                   22
#define TMC2130_OFS54_FIELD                   ((RegisterField) {TMC2130_OFS54_MASK, TMC2130_OFS54_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS55_MASK                    0x00800000
#define TMC2130_OFS55_SHIFT                   23
#define TMC2130_OFS55_FIELD                   ((RegisterField) {TMC2130_OFS55_MASK, TMC2130_OFS55_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS56_MASK                    0x01000000
#define TMC2130_OFS56_SHIFT                   24
#define TMC2130_OFS56_FIELD                   ((RegisterField) {TMC2130_OFS56_MASK, TMC2130_OFS56_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS57_MASK                    0x02000000
#define TMC2130_OFS57_SHIFT                   25
#define TMC2130_OFS57_FIELD                   ((RegisterField) {TMC2130_OFS57_MASK, TMC2130_OFS57_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS58_MASK                    0x04000000
#define TMC2130_OFS58_SHIFT                   26
#define TMC2130_OFS58_FIELD                   ((RegisterField) {TMC2130_OFS58_MASK, TMC2130_OFS58_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS59_MASK                    0x08000000
#define TMC2130_OFS59_SHIFT                   27
#define TMC2130_OFS59_FIELD                   ((RegisterField) {TMC2130_OFS59_MASK, TMC2130_OFS59_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS60_MASK                    0x10000000
#define TMC2130_OFS60_SHIFT                   28
#define TMC2130_OFS60_FIELD                   ((RegisterField) {TMC2130_OFS60_MASK, TMC2130_OFS60_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS61_MASK                    0x20000000
#define TMC2130_OFS61_SHIFT                   29
#define TMC2130_OFS61_FIELD                   ((RegisterField) {TMC2130_OFS61_MASK, TMC2130_OFS61_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS62_MASK                    0x40000000
#define TMC2130_OFS62_SHIFT                   30
#define TMC2130_OFS62_FIELD                   ((RegisterField) {TMC2130_OFS62_MASK, TMC2130_OFS62_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS63_MASK                    0x80000000
#define TMC2130_OFS63_SHIFT                   31
#define TMC2130_OFS63_FIELD                   ((RegisterField) {TMC2130_OFS63_MASK, TMC2130_OFS63_SHIFT, TMC2130_MSLUT[1], false})
#define TMC2130_OFS64_MASK                    0x00000001
#define TMC2130_OFS64_SHIFT                   0
#define TMC2130_OFS64_FIELD                   ((RegisterField) {TMC2130_OFS64_MASK, TMC2130_OFS64_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS65_MASK                    0x00000002
#define TMC2130_OFS65_SHIFT                   1
#define TMC2130_OFS65_FIELD                   ((RegisterField) {TMC2130_OFS65_MASK, TMC2130_OFS65_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS66_MASK                    0x00000004
#define TMC2130_OFS66_SHIFT                   2
#define TMC2130_OFS66_FIELD                   ((RegisterField) {TMC2130_OFS66_MASK, TMC2130_OFS66_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS67_MASK                    0x00000008
#define TMC2130_OFS67_SHIFT                   3
#define TMC2130_OFS67_FIELD                   ((RegisterField) {TMC2130_OFS67_MASK, TMC2130_OFS67_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS68_MASK                    0x00000010
#define TMC2130_OFS68_SHIFT                   4
#define TMC2130_OFS68_FIELD                   ((RegisterField) {TMC2130_OFS68_MASK, TMC2130_OFS68_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS69_MASK                    0x00000020
#define TMC2130_OFS69_SHIFT                   5
#define TMC2130_OFS69_FIELD                   ((RegisterField) {TMC2130_OFS69_MASK, TMC2130_OFS69_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS70_MASK                    0x00000040
#define TMC2130_OFS70_SHIFT                   6
#define TMC2130_OFS70_FIELD                   ((RegisterField) {TMC2130_OFS70_MASK, TMC2130_OFS70_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS71_MASK                    0x00000080
#define TMC2130_OFS71_SHIFT                   7
#define TMC2130_OFS71_FIELD                   ((RegisterField) {TMC2130_OFS71_MASK, TMC2130_OFS71_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS72_MASK                    0x00000100
#define TMC2130_OFS72_SHIFT                   8
#define TMC2130_OFS72_FIELD                   ((RegisterField) {TMC2130_OFS72_MASK, TMC2130_OFS72_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS73_MASK                    0x00000200
#define TMC2130_OFS73_SHIFT                   9
#define TMC2130_OFS73_FIELD                   ((RegisterField) {TMC2130_OFS73_MASK, TMC2130_OFS73_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS74_MASK                    0x00000400
#define TMC2130_OFS74_SHIFT                   10
#define TMC2130_OFS74_FIELD                   ((RegisterField) {TMC2130_OFS74_MASK, TMC2130_OFS74_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS75_MASK                    0x00000800
#define TMC2130_OFS75_SHIFT                   11
#define TMC2130_OFS75_FIELD                   ((RegisterField) {TMC2130_OFS75_MASK, TMC2130_OFS75_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS76_MASK                    0x00001000
#define TMC2130_OFS76_SHIFT                   12
#define TMC2130_OFS76_FIELD                   ((RegisterField) {TMC2130_OFS76_MASK, TMC2130_OFS76_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS77_MASK                    0x00002000
#define TMC2130_OFS77_SHIFT                   13
#define TMC2130_OFS77_FIELD                   ((RegisterField) {TMC2130_OFS77_MASK, TMC2130_OFS77_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS78_MASK                    0x00004000
#define TMC2130_OFS78_SHIFT                   14
#define TMC2130_OFS78_FIELD                   ((RegisterField) {TMC2130_OFS78_MASK, TMC2130_OFS78_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS79_MASK                    0x00008000
#define TMC2130_OFS79_SHIFT                   15
#define TMC2130_OFS79_FIELD                   ((RegisterField) {TMC2130_OFS79_MASK, TMC2130_OFS79_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS80_MASK                    0x00010000
#define TMC2130_OFS80_SHIFT                   16
#define TMC2130_OFS80_FIELD                   ((RegisterField) {TMC2130_OFS80_MASK, TMC2130_OFS80_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS81_MASK                    0x00020000
#define TMC2130_OFS81_SHIFT                   17
#define TMC2130_OFS81_FIELD                   ((RegisterField) {TMC2130_OFS81_MASK, TMC2130_OFS81_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS82_MASK                    0x00040000
#define TMC2130_OFS82_SHIFT                   18
#define TMC2130_OFS82_FIELD                   ((RegisterField) {TMC2130_OFS82_MASK, TMC2130_OFS82_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS83_MASK                    0x00080000
#define TMC2130_OFS83_SHIFT                   19
#define TMC2130_OFS83_FIELD                   ((RegisterField) {TMC2130_OFS83_MASK, TMC2130_OFS83_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS84_MASK                    0x00100000
#define TMC2130_OFS84_SHIFT                   20
#define TMC2130_OFS84_FIELD                   ((RegisterField) {TMC2130_OFS84_MASK, TMC2130_OFS84_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS85_MASK                    0x00200000
#define TMC2130_OFS85_SHIFT                   21
#define TMC2130_OFS85_FIELD                   ((RegisterField) {TMC2130_OFS85_MASK, TMC2130_OFS85_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS86_MASK                    0x00400000
#define TMC2130_OFS86_SHIFT                   22
#define TMC2130_OFS86_FIELD                   ((RegisterField) {TMC2130_OFS86_MASK, TMC2130_OFS86_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS87_MASK                    0x00800000
#define TMC2130_OFS87_SHIFT                   23
#define TMC2130_OFS87_FIELD                   ((RegisterField) {TMC2130_OFS87_MASK, TMC2130_OFS87_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS88_MASK                    0x01000000
#define TMC2130_OFS88_SHIFT                   24
#define TMC2130_OFS88_FIELD                   ((RegisterField) {TMC2130_OFS88_MASK, TMC2130_OFS88_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS89_MASK                    0x02000000
#define TMC2130_OFS89_SHIFT                   25
#define TMC2130_OFS89_FIELD                   ((RegisterField) {TMC2130_OFS89_MASK, TMC2130_OFS89_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS90_MASK                    0x04000000
#define TMC2130_OFS90_SHIFT                   26
#define TMC2130_OFS90_FIELD                   ((RegisterField) {TMC2130_OFS90_MASK, TMC2130_OFS90_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS91_MASK                    0x08000000
#define TMC2130_OFS91_SHIFT                   27
#define TMC2130_OFS91_FIELD                   ((RegisterField) {TMC2130_OFS91_MASK, TMC2130_OFS91_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS92_MASK                    0x10000000
#define TMC2130_OFS92_SHIFT                   28
#define TMC2130_OFS92_FIELD                   ((RegisterField) {TMC2130_OFS92_MASK, TMC2130_OFS92_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS93_MASK                    0x20000000
#define TMC2130_OFS93_SHIFT                   29
#define TMC2130_OFS93_FIELD                   ((RegisterField) {TMC2130_OFS93_MASK, TMC2130_OFS93_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS94_MASK                    0x40000000
#define TMC2130_OFS94_SHIFT                   30
#define TMC2130_OFS94_FIELD                   ((RegisterField) {TMC2130_OFS94_MASK, TMC2130_OFS94_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS95_MASK                    0x80000000
#define TMC2130_OFS95_SHIFT                   31
#define TMC2130_OFS95_FIELD                   ((RegisterField) {TMC2130_OFS95_MASK, TMC2130_OFS95_SHIFT, TMC2130_MSLUT[2], false})
#define TMC2130_OFS96_MASK                    0x00000001
#define TMC2130_OFS96_SHIFT                   0
#define TMC2130_OFS96_FIELD                   ((RegisterField) {TMC2130_OFS96_MASK, TMC2130_OFS96_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS97_MASK                    0x00000002
#define TMC2130_OFS97_SHIFT                   1
#define TMC2130_OFS97_FIELD                   ((RegisterField) {TMC2130_OFS97_MASK, TMC2130_OFS97_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS98_MASK                    0x00000004
#define TMC2130_OFS98_SHIFT                   2
#define TMC2130_OFS98_FIELD                   ((RegisterField) {TMC2130_OFS98_MASK, TMC2130_OFS98_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS99_MASK                    0x00000008
#define TMC2130_OFS99_SHIFT                   3
#define TMC2130_OFS99_FIELD                   ((RegisterField) {TMC2130_OFS99_MASK, TMC2130_OFS99_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS100_MASK                   0x00000010
#define TMC2130_OFS100_SHIFT                  4
#define TMC2130_OFS100_FIELD                  ((RegisterField) {TMC2130_OFS100_MASK, TMC2130_OFS100_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS101_MASK                   0x00000020
#define TMC2130_OFS101_SHIFT                  5
#define TMC2130_OFS101_FIELD                  ((RegisterField) {TMC2130_OFS101_MASK, TMC2130_OFS101_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS102_MASK                   0x00000040
#define TMC2130_OFS102_SHIFT                  6
#define TMC2130_OFS102_FIELD                  ((RegisterField) {TMC2130_OFS102_MASK, TMC2130_OFS102_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS103_MASK                   0x00000080
#define TMC2130_OFS103_SHIFT                  7
#define TMC2130_OFS103_FIELD                  ((RegisterField) {TMC2130_OFS103_MASK, TMC2130_OFS103_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS104_MASK                   0x00000100
#define TMC2130_OFS104_SHIFT                  8
#define TMC2130_OFS104_FIELD                  ((RegisterField) {TMC2130_OFS104_MASK, TMC2130_OFS104_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS105_MASK                   0x00000200
#define TMC2130_OFS105_SHIFT                  9
#define TMC2130_OFS105_FIELD                  ((RegisterField) {TMC2130_OFS105_MASK, TMC2130_OFS105_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS106_MASK                   0x00000400
#define TMC2130_OFS106_SHIFT                  10
#define TMC2130_OFS106_FIELD                  ((RegisterField) {TMC2130_OFS106_MASK, TMC2130_OFS106_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS107_MASK                   0x00000800
#define TMC2130_OFS107_SHIFT                  11
#define TMC2130_OFS107_FIELD                  ((RegisterField) {TMC2130_OFS107_MASK, TMC2130_OFS107_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS108_MASK                   0x00001000
#define TMC2130_OFS108_SHIFT                  12
#define TMC2130_OFS108_FIELD                  ((RegisterField) {TMC2130_OFS108_MASK, TMC2130_OFS108_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS109_MASK                   0x00002000
#define TMC2130_OFS109_SHIFT                  13
#define TMC2130_OFS109_FIELD                  ((RegisterField) {TMC2130_OFS109_MASK, TMC2130_OFS109_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS110_MASK                   0x00004000
#define TMC2130_OFS110_SHIFT                  14
#define TMC2130_OFS110_FIELD                  ((RegisterField) {TMC2130_OFS110_MASK, TMC2130_OFS110_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS111_MASK                   0x00008000
#define TMC2130_OFS111_SHIFT                  15
#define TMC2130_OFS111_FIELD                  ((RegisterField) {TMC2130_OFS111_MASK, TMC2130_OFS111_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS112_MASK                   0x00010000
#define TMC2130_OFS112_SHIFT                  16
#define TMC2130_OFS112_FIELD                  ((RegisterField) {TMC2130_OFS112_MASK, TMC2130_OFS112_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS113_MASK                   0x00020000
#define TMC2130_OFS113_SHIFT                  17
#define TMC2130_OFS113_FIELD                  ((RegisterField) {TMC2130_OFS113_MASK, TMC2130_OFS113_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS114_MASK                   0x00040000
#define TMC2130_OFS114_SHIFT                  18
#define TMC2130_OFS114_FIELD                  ((RegisterField) {TMC2130_OFS114_MASK, TMC2130_OFS114_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS115_MASK                   0x00080000
#define TMC2130_OFS115_SHIFT                  19
#define TMC2130_OFS115_FIELD                  ((RegisterField) {TMC2130_OFS115_MASK, TMC2130_OFS115_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS116_MASK                   0x00100000
#define TMC2130_OFS116_SHIFT                  20
#define TMC2130_OFS116_FIELD                  ((RegisterField) {TMC2130_OFS116_MASK, TMC2130_OFS116_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS117_MASK                   0x00200000
#define TMC2130_OFS117_SHIFT                  21
#define TMC2130_OFS117_FIELD                  ((RegisterField) {TMC2130_OFS117_MASK, TMC2130_OFS117_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS118_MASK                   0x00400000
#define TMC2130_OFS118_SHIFT                  22
#define TMC2130_OFS118_FIELD                  ((RegisterField) {TMC2130_OFS118_MASK, TMC2130_OFS118_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS119_MASK                   0x00800000
#define TMC2130_OFS119_SHIFT                  23
#define TMC2130_OFS119_FIELD                  ((RegisterField) {TMC2130_OFS119_MASK, TMC2130_OFS119_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS120_MASK                   0x01000000
#define TMC2130_OFS120_SHIFT                  24
#define TMC2130_OFS120_FIELD                  ((RegisterField) {TMC2130_OFS120_MASK, TMC2130_OFS120_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS121_MASK                   0x02000000
#define TMC2130_OFS121_SHIFT                  25
#define TMC2130_OFS121_FIELD                  ((RegisterField) {TMC2130_OFS121_MASK, TMC2130_OFS121_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS122_MASK                   0x04000000
#define TMC2130_OFS122_SHIFT                  26
#define TMC2130_OFS122_FIELD                  ((RegisterField) {TMC2130_OFS122_MASK, TMC2130_OFS122_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS123_MASK                   0x08000000
#define TMC2130_OFS123_SHIFT                  27
#define TMC2130_OFS123_FIELD                  ((RegisterField) {TMC2130_OFS123_MASK, TMC2130_OFS123_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS124_MASK                   0x10000000
#define TMC2130_OFS124_SHIFT                  28
#define TMC2130_OFS124_FIELD                  ((RegisterField) {TMC2130_OFS124_MASK, TMC2130_OFS124_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS125_MASK                   0x20000000
#define TMC2130_OFS125_SHIFT                  29
#define TMC2130_OFS125_FIELD                  ((RegisterField) {TMC2130_OFS125_MASK, TMC2130_OFS125_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS126_MASK                   0x40000000
#define TMC2130_OFS126_SHIFT                  30
#define TMC2130_OFS126_FIELD                  ((RegisterField) {TMC2130_OFS126_MASK, TMC2130_OFS126_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS127_MASK                   0x80000000
#define TMC2130_OFS127_SHIFT                  31
#define TMC2130_OFS127_FIELD                  ((RegisterField) {TMC2130_OFS127_MASK, TMC2130_OFS127_SHIFT, TMC2130_MSLUT[3], false})
#define TMC2130_OFS128_MASK                   0x00000001
#define TMC2130_OFS128_SHIFT                  0
#define TMC2130_OFS128_FIELD                  ((RegisterField) {TMC2130_OFS128_MASK, TMC2130_OFS128_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS129_MASK                   0x00000002
#define TMC2130_OFS129_SHIFT                  1
#define TMC2130_OFS129_FIELD                  ((RegisterField) {TMC2130_OFS129_MASK, TMC2130_OFS129_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS130_MASK                   0x00000004
#define TMC2130_OFS130_SHIFT                  2
#define TMC2130_OFS130_FIELD                  ((RegisterField) {TMC2130_OFS130_MASK, TMC2130_OFS130_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS131_MASK                   0x00000008
#define TMC2130_OFS131_SHIFT                  3
#define TMC2130_OFS131_FIELD                  ((RegisterField) {TMC2130_OFS131_MASK, TMC2130_OFS131_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS132_MASK                   0x00000010
#define TMC2130_OFS132_SHIFT                  4
#define TMC2130_OFS132_FIELD                  ((RegisterField) {TMC2130_OFS132_MASK, TMC2130_OFS132_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS133_MASK                   0x00000020
#define TMC2130_OFS133_SHIFT                  5
#define TMC2130_OFS133_FIELD                  ((RegisterField) {TMC2130_OFS133_MASK, TMC2130_OFS133_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS134_MASK                   0x00000040
#define TMC2130_OFS134_SHIFT                  6
#define TMC2130_OFS134_FIELD                  ((RegisterField) {TMC2130_OFS134_MASK, TMC2130_OFS134_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS135_MASK                   0x00000080
#define TMC2130_OFS135_SHIFT                  7
#define TMC2130_OFS135_FIELD                  ((RegisterField) {TMC2130_OFS135_MASK, TMC2130_OFS135_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS136_MASK                   0x00000100
#define TMC2130_OFS136_SHIFT                  8
#define TMC2130_OFS136_FIELD                  ((RegisterField) {TMC2130_OFS136_MASK, TMC2130_OFS136_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS137_MASK                   0x00000200
#define TMC2130_OFS137_SHIFT                  9
#define TMC2130_OFS137_FIELD                  ((RegisterField) {TMC2130_OFS137_MASK, TMC2130_OFS137_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS138_MASK                   0x00000400
#define TMC2130_OFS138_SHIFT                  10
#define TMC2130_OFS138_FIELD                  ((RegisterField) {TMC2130_OFS138_MASK, TMC2130_OFS138_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS139_MASK                   0x00000800
#define TMC2130_OFS139_SHIFT                  11
#define TMC2130_OFS139_FIELD                  ((RegisterField) {TMC2130_OFS139_MASK, TMC2130_OFS139_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS140_MASK                   0x00001000
#define TMC2130_OFS140_SHIFT                  12
#define TMC2130_OFS140_FIELD                  ((RegisterField) {TMC2130_OFS140_MASK, TMC2130_OFS140_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS141_MASK                   0x00002000
#define TMC2130_OFS141_SHIFT                  13
#define TMC2130_OFS141_FIELD                  ((RegisterField) {TMC2130_OFS141_MASK, TMC2130_OFS141_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS142_MASK                   0x00004000
#define TMC2130_OFS142_SHIFT                  14
#define TMC2130_OFS142_FIELD                  ((RegisterField) {TMC2130_OFS142_MASK, TMC2130_OFS142_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS143_MASK                   0x00008000
#define TMC2130_OFS143_SHIFT                  15
#define TMC2130_OFS143_FIELD                  ((RegisterField) {TMC2130_OFS143_MASK, TMC2130_OFS143_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS144_MASK                   0x00010000
#define TMC2130_OFS144_SHIFT                  16
#define TMC2130_OFS144_FIELD                  ((RegisterField) {TMC2130_OFS144_MASK, TMC2130_OFS144_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS145_MASK                   0x00020000
#define TMC2130_OFS145_SHIFT                  17
#define TMC2130_OFS145_FIELD                  ((RegisterField) {TMC2130_OFS145_MASK, TMC2130_OFS145_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS146_MASK                   0x00040000
#define TMC2130_OFS146_SHIFT                  18
#define TMC2130_OFS146_FIELD                  ((RegisterField) {TMC2130_OFS146_MASK, TMC2130_OFS146_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS147_MASK                   0x00080000
#define TMC2130_OFS147_SHIFT                  19
#define TMC2130_OFS147_FIELD                  ((RegisterField) {TMC2130_OFS147_MASK, TMC2130_OFS147_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS148_MASK                   0x00100000
#define TMC2130_OFS148_SHIFT                  20
#define TMC2130_OFS148_FIELD                  ((RegisterField) {TMC2130_OFS148_MASK, TMC2130_OFS148_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS149_MASK                   0x00200000
#define TMC2130_OFS149_SHIFT                  21
#define TMC2130_OFS149_FIELD                  ((RegisterField) {TMC2130_OFS149_MASK, TMC2130_OFS149_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS150_MASK                   0x00400000
#define TMC2130_OFS150_SHIFT                  22
#define TMC2130_OFS150_FIELD                  ((RegisterField) {TMC2130_OFS150_MASK, TMC2130_OFS150_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS151_MASK                   0x00800000
#define TMC2130_OFS151_SHIFT                  23
#define TMC2130_OFS151_FIELD                  ((RegisterField) {TMC2130_OFS151_MASK, TMC2130_OFS151_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS152_MASK                   0x01000000
#define TMC2130_OFS152_SHIFT                  24
#define TMC2130_OFS152_FIELD                  ((RegisterField) {TMC2130_OFS152_MASK, TMC2130_OFS152_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS153_MASK                   0x02000000
#define TMC2130_OFS153_SHIFT                  25
#define TMC2130_OFS153_FIELD                  ((RegisterField) {TMC2130_OFS153_MASK, TMC2130_OFS153_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS154_MASK                   0x04000000
#define TMC2130_OFS154_SHIFT                  26
#define TMC2130_OFS154_FIELD                  ((RegisterField) {TMC2130_OFS154_MASK, TMC2130_OFS154_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS155_MASK                   0x08000000
#define TMC2130_OFS155_SHIFT                  27
#define TMC2130_OFS155_FIELD                  ((RegisterField) {TMC2130_OFS155_MASK, TMC2130_OFS155_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS156_MASK                   0x10000000
#define TMC2130_OFS156_SHIFT                  28
#define TMC2130_OFS156_FIELD                  ((RegisterField) {TMC2130_OFS156_MASK, TMC2130_OFS156_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS157_MASK                   0x20000000
#define TMC2130_OFS157_SHIFT                  29
#define TMC2130_OFS157_FIELD                  ((RegisterField) {TMC2130_OFS157_MASK, TMC2130_OFS157_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS158_MASK                   0x40000000
#define TMC2130_OFS158_SHIFT                  30
#define TMC2130_OFS158_FIELD                  ((RegisterField) {TMC2130_OFS158_MASK, TMC2130_OFS158_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS159_MASK                   0x80000000
#define TMC2130_OFS159_SHIFT                  31
#define TMC2130_OFS159_FIELD                  ((RegisterField) {TMC2130_OFS159_MASK, TMC2130_OFS159_SHIFT, TMC2130_MSLUT[4], false})
#define TMC2130_OFS160_MASK                   0x00000001
#define TMC2130_OFS160_SHIFT                  0
#define TMC2130_OFS160_FIELD                  ((RegisterField) {TMC2130_OFS160_MASK, TMC2130_OFS160_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS161_MASK                   0x00000002
#define TMC2130_OFS161_SHIFT                  1
#define TMC2130_OFS161_FIELD                  ((RegisterField) {TMC2130_OFS161_MASK, TMC2130_OFS161_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS162_MASK                   0x00000004
#define TMC2130_OFS162_SHIFT                  2
#define TMC2130_OFS162_FIELD                  ((RegisterField) {TMC2130_OFS162_MASK, TMC2130_OFS162_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS163_MASK                   0x00000008
#define TMC2130_OFS163_SHIFT                  3
#define TMC2130_OFS163_FIELD                  ((RegisterField) {TMC2130_OFS163_MASK, TMC2130_OFS163_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS164_MASK                   0x00000010
#define TMC2130_OFS164_SHIFT                  4
#define TMC2130_OFS164_FIELD                  ((RegisterField) {TMC2130_OFS164_MASK, TMC2130_OFS164_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS165_MASK                   0x00000020
#define TMC2130_OFS165_SHIFT                  5
#define TMC2130_OFS165_FIELD                  ((RegisterField) {TMC2130_OFS165_MASK, TMC2130_OFS165_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS166_MASK                   0x00000040
#define TMC2130_OFS166_SHIFT                  6
#define TMC2130_OFS166_FIELD                  ((RegisterField) {TMC2130_OFS166_MASK, TMC2130_OFS166_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS167_MASK                   0x00000080
#define TMC2130_OFS167_SHIFT                  7
#define TMC2130_OFS167_FIELD                  ((RegisterField) {TMC2130_OFS167_MASK, TMC2130_OFS167_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS168_MASK                   0x00000100
#define TMC2130_OFS168_SHIFT                  8
#define TMC2130_OFS168_FIELD                  ((RegisterField) {TMC2130_OFS168_MASK, TMC2130_OFS168_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS169_MASK                   0x00000200
#define TMC2130_OFS169_SHIFT                  9
#define TMC2130_OFS169_FIELD                  ((RegisterField) {TMC2130_OFS169_MASK, TMC2130_OFS169_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS170_MASK                   0x00000400
#define TMC2130_OFS170_SHIFT                  10
#define TMC2130_OFS170_FIELD                  ((RegisterField) {TMC2130_OFS170_MASK, TMC2130_OFS170_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS171_MASK                   0x00000800
#define TMC2130_OFS171_SHIFT                  11
#define TMC2130_OFS171_FIELD                  ((RegisterField) {TMC2130_OFS171_MASK, TMC2130_OFS171_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS172_MASK                   0x00001000
#define TMC2130_OFS172_SHIFT                  12
#define TMC2130_OFS172_FIELD                  ((RegisterField) {TMC2130_OFS172_MASK, TMC2130_OFS172_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS173_MASK                   0x00002000
#define TMC2130_OFS173_SHIFT                  13
#define TMC2130_OFS173_FIELD                  ((RegisterField) {TMC2130_OFS173_MASK, TMC2130_OFS173_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS174_MASK                   0x00004000
#define TMC2130_OFS174_SHIFT                  14
#define TMC2130_OFS174_FIELD                  ((RegisterField) {TMC2130_OFS174_MASK, TMC2130_OFS174_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS175_MASK                   0x00008000
#define TMC2130_OFS175_SHIFT                  15
#define TMC2130_OFS175_FIELD                  ((RegisterField) {TMC2130_OFS175_MASK, TMC2130_OFS175_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS176_MASK                   0x00010000
#define TMC2130_OFS176_SHIFT                  16
#define TMC2130_OFS176_FIELD                  ((RegisterField) {TMC2130_OFS176_MASK, TMC2130_OFS176_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS177_MASK                   0x00020000
#define TMC2130_OFS177_SHIFT                  17
#define TMC2130_OFS177_FIELD                  ((RegisterField) {TMC2130_OFS177_MASK, TMC2130_OFS177_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS178_MASK                   0x00040000
#define TMC2130_OFS178_SHIFT                  18
#define TMC2130_OFS178_FIELD                  ((RegisterField) {TMC2130_OFS178_MASK, TMC2130_OFS178_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS179_MASK                   0x00080000
#define TMC2130_OFS179_SHIFT                  19
#define TMC2130_OFS179_FIELD                  ((RegisterField) {TMC2130_OFS179_MASK, TMC2130_OFS179_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS180_MASK                   0x00100000
#define TMC2130_OFS180_SHIFT                  20
#define TMC2130_OFS180_FIELD                  ((RegisterField) {TMC2130_OFS180_MASK, TMC2130_OFS180_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS181_MASK                   0x00200000
#define TMC2130_OFS181_SHIFT                  21
#define TMC2130_OFS181_FIELD                  ((RegisterField) {TMC2130_OFS181_MASK, TMC2130_OFS181_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS182_MASK                   0x00400000
#define TMC2130_OFS182_SHIFT                  22
#define TMC2130_OFS182_FIELD                  ((RegisterField) {TMC2130_OFS182_MASK, TMC2130_OFS182_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS183_MASK                   0x00800000
#define TMC2130_OFS183_SHIFT                  23
#define TMC2130_OFS183_FIELD                  ((RegisterField) {TMC2130_OFS183_MASK, TMC2130_OFS183_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS184_MASK                   0x01000000
#define TMC2130_OFS184_SHIFT                  24
#define TMC2130_OFS184_FIELD                  ((RegisterField) {TMC2130_OFS184_MASK, TMC2130_OFS184_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS185_MASK                   0x02000000
#define TMC2130_OFS185_SHIFT                  25
#define TMC2130_OFS185_FIELD                  ((RegisterField) {TMC2130_OFS185_MASK, TMC2130_OFS185_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS186_MASK                   0x04000000
#define TMC2130_OFS186_SHIFT                  26
#define TMC2130_OFS186_FIELD                  ((RegisterField) {TMC2130_OFS186_MASK, TMC2130_OFS186_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS187_MASK                   0x08000000
#define TMC2130_OFS187_SHIFT                  27
#define TMC2130_OFS187_FIELD                  ((RegisterField) {TMC2130_OFS187_MASK, TMC2130_OFS187_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS188_MASK                   0x10000000
#define TMC2130_OFS188_SHIFT                  28
#define TMC2130_OFS188_FIELD                  ((RegisterField) {TMC2130_OFS188_MASK, TMC2130_OFS188_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS189_MASK                   0x20000000
#define TMC2130_OFS189_SHIFT                  29
#define TMC2130_OFS189_FIELD                  ((RegisterField) {TMC2130_OFS189_MASK, TMC2130_OFS189_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS190_MASK                   0x40000000
#define TMC2130_OFS190_SHIFT                  30
#define TMC2130_OFS190_FIELD                  ((RegisterField) {TMC2130_OFS190_MASK, TMC2130_OFS190_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS191_MASK                   0x80000000
#define TMC2130_OFS191_SHIFT                  31
#define TMC2130_OFS191_FIELD                  ((RegisterField) {TMC2130_OFS191_MASK, TMC2130_OFS191_SHIFT, TMC2130_MSLUT[5], false})
#define TMC2130_OFS192_MASK                   0x00000001
#define TMC2130_OFS192_SHIFT                  0
#define TMC2130_OFS192_FIELD                  ((RegisterField) {TMC2130_OFS192_MASK, TMC2130_OFS192_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS193_MASK                   0x00000002
#define TMC2130_OFS193_SHIFT                  1
#define TMC2130_OFS193_FIELD                  ((RegisterField) {TMC2130_OFS193_MASK, TMC2130_OFS193_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS194_MASK                   0x00000004
#define TMC2130_OFS194_SHIFT                  2
#define TMC2130_OFS194_FIELD                  ((RegisterField) {TMC2130_OFS194_MASK, TMC2130_OFS194_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS195_MASK                   0x00000008
#define TMC2130_OFS195_SHIFT                  3
#define TMC2130_OFS195_FIELD                  ((RegisterField) {TMC2130_OFS195_MASK, TMC2130_OFS195_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS196_MASK                   0x00000010
#define TMC2130_OFS196_SHIFT                  4
#define TMC2130_OFS196_FIELD                  ((RegisterField) {TMC2130_OFS196_MASK, TMC2130_OFS196_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS197_MASK                   0x00000020
#define TMC2130_OFS197_SHIFT                  5
#define TMC2130_OFS197_FIELD                  ((RegisterField) {TMC2130_OFS197_MASK, TMC2130_OFS197_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS198_MASK                   0x00000040
#define TMC2130_OFS198_SHIFT                  6
#define TMC2130_OFS198_FIELD                  ((RegisterField) {TMC2130_OFS198_MASK, TMC2130_OFS198_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS199_MASK                   0x00000080
#define TMC2130_OFS199_SHIFT                  7
#define TMC2130_OFS199_FIELD                  ((RegisterField) {TMC2130_OFS199_MASK, TMC2130_OFS199_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS200_MASK                   0x00000100
#define TMC2130_OFS200_SHIFT                  8
#define TMC2130_OFS200_FIELD                  ((RegisterField) {TMC2130_OFS200_MASK, TMC2130_OFS200_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS201_MASK                   0x00000200
#define TMC2130_OFS201_SHIFT                  9
#define TMC2130_OFS201_FIELD                  ((RegisterField) {TMC2130_OFS201_MASK, TMC2130_OFS201_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS202_MASK                   0x00000400
#define TMC2130_OFS202_SHIFT                  10
#define TMC2130_OFS202_FIELD                  ((RegisterField) {TMC2130_OFS202_MASK, TMC2130_OFS202_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS203_MASK                   0x00000800
#define TMC2130_OFS203_SHIFT                  11
#define TMC2130_OFS203_FIELD                  ((RegisterField) {TMC2130_OFS203_MASK, TMC2130_OFS203_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS204_MASK                   0x00001000
#define TMC2130_OFS204_SHIFT                  12
#define TMC2130_OFS204_FIELD                  ((RegisterField) {TMC2130_OFS204_MASK, TMC2130_OFS204_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS205_MASK                   0x00002000
#define TMC2130_OFS205_SHIFT                  13
#define TMC2130_OFS205_FIELD                  ((RegisterField) {TMC2130_OFS205_MASK, TMC2130_OFS205_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS206_MASK                   0x00004000
#define TMC2130_OFS206_SHIFT                  14
#define TMC2130_OFS206_FIELD                  ((RegisterField) {TMC2130_OFS206_MASK, TMC2130_OFS206_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS207_MASK                   0x00008000
#define TMC2130_OFS207_SHIFT                  15
#define TMC2130_OFS207_FIELD                  ((RegisterField) {TMC2130_OFS207_MASK, TMC2130_OFS207_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS208_MASK                   0x00010000
#define TMC2130_OFS208_SHIFT                  16
#define TMC2130_OFS208_FIELD                  ((RegisterField) {TMC2130_OFS208_MASK, TMC2130_OFS208_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS209_MASK                   0x00020000
#define TMC2130_OFS209_SHIFT                  17
#define TMC2130_OFS209_FIELD                  ((RegisterField) {TMC2130_OFS209_MASK, TMC2130_OFS209_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS210_MASK                   0x00040000
#define TMC2130_OFS210_SHIFT                  18
#define TMC2130_OFS210_FIELD                  ((RegisterField) {TMC2130_OFS210_MASK, TMC2130_OFS210_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS211_MASK                   0x00080000
#define TMC2130_OFS211_SHIFT                  19
#define TMC2130_OFS211_FIELD                  ((RegisterField) {TMC2130_OFS211_MASK, TMC2130_OFS211_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS212_MASK                   0x00100000
#define TMC2130_OFS212_SHIFT                  20
#define TMC2130_OFS212_FIELD                  ((RegisterField) {TMC2130_OFS212_MASK, TMC2130_OFS212_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS213_MASK                   0x00200000
#define TMC2130_OFS213_SHIFT                  21
#define TMC2130_OFS213_FIELD                  ((RegisterField) {TMC2130_OFS213_MASK, TMC2130_OFS213_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS214_MASK                   0x00400000
#define TMC2130_OFS214_SHIFT                  22
#define TMC2130_OFS214_FIELD                  ((RegisterField) {TMC2130_OFS214_MASK, TMC2130_OFS214_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS215_MASK                   0x00800000
#define TMC2130_OFS215_SHIFT                  23
#define TMC2130_OFS215_FIELD                  ((RegisterField) {TMC2130_OFS215_MASK, TMC2130_OFS215_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS216_MASK                   0x01000000
#define TMC2130_OFS216_SHIFT                  24
#define TMC2130_OFS216_FIELD                  ((RegisterField) {TMC2130_OFS216_MASK, TMC2130_OFS216_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS217_MASK                   0x02000000
#define TMC2130_OFS217_SHIFT                  25
#define TMC2130_OFS217_FIELD                  ((RegisterField) {TMC2130_OFS217_MASK, TMC2130_OFS217_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS218_MASK                   0x04000000
#define TMC2130_OFS218_SHIFT                  26
#define TMC2130_OFS218_FIELD                  ((RegisterField) {TMC2130_OFS218_MASK, TMC2130_OFS218_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS219_MASK                   0x08000000
#define TMC2130_OFS219_SHIFT                  27
#define TMC2130_OFS219_FIELD                  ((RegisterField) {TMC2130_OFS219_MASK, TMC2130_OFS219_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS220_MASK                   0x10000000
#define TMC2130_OFS220_SHIFT                  28
#define TMC2130_OFS220_FIELD                  ((RegisterField) {TMC2130_OFS220_MASK, TMC2130_OFS220_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS221_MASK                   0x20000000
#define TMC2130_OFS221_SHIFT                  29
#define TMC2130_OFS221_FIELD                  ((RegisterField) {TMC2130_OFS221_MASK, TMC2130_OFS221_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS222_MASK                   0x40000000
#define TMC2130_OFS222_SHIFT                  30
#define TMC2130_OFS222_FIELD                  ((RegisterField) {TMC2130_OFS222_MASK, TMC2130_OFS222_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS223_MASK                   0x80000000
#define TMC2130_OFS223_SHIFT                  31
#define TMC2130_OFS223_FIELD                  ((RegisterField) {TMC2130_OFS223_MASK, TMC2130_OFS223_SHIFT, TMC2130_MSLUT[6], false})
#define TMC2130_OFS224_MASK                   0x00000001
#define TMC2130_OFS224_SHIFT                  0
#define TMC2130_OFS224_FIELD                  ((RegisterField) {TMC2130_OFS224_MASK, TMC2130_OFS224_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS225_MASK                   0x00000002
#define TMC2130_OFS225_SHIFT                  1
#define TMC2130_OFS225_FIELD                  ((RegisterField) {TMC2130_OFS225_MASK, TMC2130_OFS225_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS226_MASK                   0x00000004
#define TMC2130_OFS226_SHIFT                  2
#define TMC2130_OFS226_FIELD                  ((RegisterField) {TMC2130_OFS226_MASK, TMC2130_OFS226_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS227_MASK                   0x00000008
#define TMC2130_OFS227_SHIFT                  3
#define TMC2130_OFS227_FIELD                  ((RegisterField) {TMC2130_OFS227_MASK, TMC2130_OFS227_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS228_MASK                   0x00000010
#define TMC2130_OFS228_SHIFT                  4
#define TMC2130_OFS228_FIELD                  ((RegisterField) {TMC2130_OFS228_MASK, TMC2130_OFS228_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS229_MASK                   0x00000020
#define TMC2130_OFS229_SHIFT                  5
#define TMC2130_OFS229_FIELD                  ((RegisterField) {TMC2130_OFS229_MASK, TMC2130_OFS229_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS230_MASK                   0x00000040
#define TMC2130_OFS230_SHIFT                  6
#define TMC2130_OFS230_FIELD                  ((RegisterField) {TMC2130_OFS230_MASK, TMC2130_OFS230_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS231_MASK                   0x00000080
#define TMC2130_OFS231_SHIFT                  7
#define TMC2130_OFS231_FIELD                  ((RegisterField) {TMC2130_OFS231_MASK, TMC2130_OFS231_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS232_MASK                   0x00000100
#define TMC2130_OFS232_SHIFT                  8
#define TMC2130_OFS232_FIELD                  ((RegisterField) {TMC2130_OFS232_MASK, TMC2130_OFS232_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS233_MASK                   0x00000200
#define TMC2130_OFS233_SHIFT                  9
#define TMC2130_OFS233_FIELD                  ((RegisterField) {TMC2130_OFS233_MASK, TMC2130_OFS233_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS234_MASK                   0x00000400
#define TMC2130_OFS234_SHIFT                  10
#define TMC2130_OFS234_FIELD                  ((RegisterField) {TMC2130_OFS234_MASK, TMC2130_OFS234_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS235_MASK                   0x00000800
#define TMC2130_OFS235_SHIFT                  11
#define TMC2130_OFS235_FIELD                  ((RegisterField) {TMC2130_OFS235_MASK, TMC2130_OFS235_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS236_MASK                   0x00001000
#define TMC2130_OFS236_SHIFT                  12
#define TMC2130_OFS236_FIELD                  ((RegisterField) {TMC2130_OFS236_MASK, TMC2130_OFS236_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS237_MASK                   0x00002000
#define TMC2130_OFS237_SHIFT                  13
#define TMC2130_OFS237_FIELD                  ((RegisterField) {TMC2130_OFS237_MASK, TMC2130_OFS237_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS238_MASK                   0x00004000
#define TMC2130_OFS238_SHIFT                  14
#define TMC2130_OFS238_FIELD                  ((RegisterField) {TMC2130_OFS238_MASK, TMC2130_OFS238_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS239_MASK                   0x00008000
#define TMC2130_OFS239_SHIFT                  15
#define TMC2130_OFS239_FIELD                  ((RegisterField) {TMC2130_OFS239_MASK, TMC2130_OFS239_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS240_MASK                   0x00010000
#define TMC2130_OFS240_SHIFT                  16
#define TMC2130_OFS240_FIELD                  ((RegisterField) {TMC2130_OFS240_MASK, TMC2130_OFS240_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS241_MASK                   0x00020000
#define TMC2130_OFS241_SHIFT                  17
#define TMC2130_OFS241_FIELD                  ((RegisterField) {TMC2130_OFS241_MASK, TMC2130_OFS241_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS242_MASK                   0x00040000
#define TMC2130_OFS242_SHIFT                  18
#define TMC2130_OFS242_FIELD                  ((RegisterField) {TMC2130_OFS242_MASK, TMC2130_OFS242_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS243_MASK                   0x00080000
#define TMC2130_OFS243_SHIFT                  19
#define TMC2130_OFS243_FIELD                  ((RegisterField) {TMC2130_OFS243_MASK, TMC2130_OFS243_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS244_MASK                   0x00100000
#define TMC2130_OFS244_SHIFT                  20
#define TMC2130_OFS244_FIELD                  ((RegisterField) {TMC2130_OFS244_MASK, TMC2130_OFS244_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS245_MASK                   0x00200000
#define TMC2130_OFS245_SHIFT                  21
#define TMC2130_OFS245_FIELD                  ((RegisterField) {TMC2130_OFS245_MASK, TMC2130_OFS245_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS246_MASK                   0x00400000
#define TMC2130_OFS246_SHIFT                  22
#define TMC2130_OFS246_FIELD                  ((RegisterField) {TMC2130_OFS246_MASK, TMC2130_OFS246_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS247_MASK                   0x00800000
#define TMC2130_OFS247_SHIFT                  23
#define TMC2130_OFS247_FIELD                  ((RegisterField) {TMC2130_OFS247_MASK, TMC2130_OFS247_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS248_MASK                   0x01000000
#define TMC2130_OFS248_SHIFT                  24
#define TMC2130_OFS248_FIELD                  ((RegisterField) {TMC2130_OFS248_MASK, TMC2130_OFS248_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS249_MASK                   0x02000000
#define TMC2130_OFS249_SHIFT                  25
#define TMC2130_OFS249_FIELD                  ((RegisterField) {TMC2130_OFS249_MASK, TMC2130_OFS249_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS250_MASK                   0x04000000
#define TMC2130_OFS250_SHIFT                  26
#define TMC2130_OFS250_FIELD                  ((RegisterField) {TMC2130_OFS250_MASK, TMC2130_OFS250_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS251_MASK                   0x08000000
#define TMC2130_OFS251_SHIFT                  27
#define TMC2130_OFS251_FIELD                  ((RegisterField) {TMC2130_OFS251_MASK, TMC2130_OFS251_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS252_MASK                   0x10000000
#define TMC2130_OFS252_SHIFT                  28
#define TMC2130_OFS252_FIELD                  ((RegisterField) {TMC2130_OFS252_MASK, TMC2130_OFS252_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS253_MASK                   0x20000000
#define TMC2130_OFS253_SHIFT                  29
#define TMC2130_OFS253_FIELD                  ((RegisterField) {TMC2130_OFS253_MASK, TMC2130_OFS253_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS254_MASK                   0x40000000
#define TMC2130_OFS254_SHIFT                  30
#define TMC2130_OFS254_FIELD                  ((RegisterField) {TMC2130_OFS254_MASK, TMC2130_OFS254_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_OFS255_MASK                   0x80000000
#define TMC2130_OFS255_SHIFT                  31
#define TMC2130_OFS255_FIELD                  ((RegisterField) {TMC2130_OFS255_MASK, TMC2130_OFS255_SHIFT, TMC2130_MSLUT[7], false})
#define TMC2130_W0_MASK                       0x00000003
#define TMC2130_W0_SHIFT                      0
#define TMC2130_W0_FIELD                      ((RegisterField) {TMC2130_W0_MASK, TMC2130_W0_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_W1_MASK                       0x0000000C
#define TMC2130_W1_SHIFT                      2
#define TMC2130_W1_FIELD                      ((RegisterField) {TMC2130_W1_MASK, TMC2130_W1_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_W2_MASK                       0x00000030
#define TMC2130_W2_SHIFT                      4
#define TMC2130_W2_FIELD                      ((RegisterField) {TMC2130_W2_MASK, TMC2130_W2_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_W3_MASK                       0x000000C0
#define TMC2130_W3_SHIFT                      6
#define TMC2130_W3_FIELD                      ((RegisterField) {TMC2130_W3_MASK, TMC2130_W3_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_X1_MASK                       0x0000FF00
#define TMC2130_X1_SHIFT                      8
#define TMC2130_X1_FIELD                      ((RegisterField) {TMC2130_X1_MASK, TMC2130_X1_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_X2_MASK                       0x00FF0000
#define TMC2130_X2_SHIFT                      16
#define TMC2130_X2_FIELD                      ((RegisterField) {TMC2130_X2_MASK, TMC2130_X2_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_X3_MASK                       0xFF000000
#define TMC2130_X3_SHIFT                      24
#define TMC2130_X3_FIELD                      ((RegisterField) {TMC2130_X3_MASK, TMC2130_X3_SHIFT, TMC2130_MSLUTSEL, false})
#define TMC2130_START_SIN_MASK                0x000000FF
#define TMC2130_START_SIN_SHIFT               0
#define TMC2130_START_SIN_FIELD               ((RegisterField) {TMC2130_START_SIN_MASK, TMC2130_START_SIN_SHIFT, TMC2130_MSLUTSTART, false})
#define TMC2130_START_SIN90_MASK              0x00FF0000
#define TMC2130_START_SIN90_SHIFT             16
#define TMC2130_START_SIN90_FIELD             ((RegisterField) {TMC2130_START_SIN90_MASK, TMC2130_START_SIN90_SHIFT, TMC2130_MSLUTSTART, false})
#define TMC2130_MSCNT_MASK                    0x000003FF
#define TMC2130_MSCNT_SHIFT                   0
#define TMC2130_MSCNT_FIELD                   ((RegisterField) {TMC2130_MSCNT_MASK, TMC2130_MSCNT_SHIFT, TMC2130_MSCNT, false})
#define TMC2130_CUR_A_MASK                    0x000001FF
#define TMC2130_CUR_A_SHIFT                   0
#define TMC2130_CUR_A_FIELD                   ((RegisterField) {TMC2130_CUR_A_MASK, TMC2130_CUR_A_SHIFT, TMC2130_MSCURACT, true})
#define TMC2130_CUR_B_MASK                    0x01FF0000
#define TMC2130_CUR_B_SHIFT                   16
#define TMC2130_CUR_B_FIELD                   ((RegisterField) {TMC2130_CUR_B_MASK, TMC2130_CUR_B_SHIFT, TMC2130_MSCURACT, true})
#define TMC2130_TOFF_MASK                     0x0000000F
#define TMC2130_TOFF_SHIFT                    0
#define TMC2130_TOFF_FIELD                    ((RegisterField) {TMC2130_TOFF_MASK, TMC2130_TOFF_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_TFD_2__0__MASK                0x00000070
#define TMC2130_TFD_2__0__SHIFT               4
#define TMC2130_TFD_2__0__FIELD               ((RegisterField) {TMC2130_TFD_2__0__MASK, TMC2130_TFD_2__0__SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_OFFSET_MASK                   0x00000780
#define TMC2130_OFFSET_SHIFT                  7
#define TMC2130_OFFSET_FIELD                  ((RegisterField) {TMC2130_OFFSET_MASK, TMC2130_OFFSET_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_TFD___MASK                    0x00000800
#define TMC2130_TFD___SHIFT                   11
#define TMC2130_TFD___FIELD                   ((RegisterField) {TMC2130_TFD___MASK, TMC2130_TFD___SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_DISFDCC_MASK                  0x00001000
#define TMC2130_DISFDCC_SHIFT                 12
#define TMC2130_DISFDCC_FIELD                 ((RegisterField) {TMC2130_DISFDCC_MASK, TMC2130_DISFDCC_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_RNDTF_MASK                    0x00002000
#define TMC2130_RNDTF_SHIFT                   13
#define TMC2130_RNDTF_FIELD                   ((RegisterField) {TMC2130_RNDTF_MASK, TMC2130_RNDTF_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_CHM_MASK                      0x00004000
#define TMC2130_CHM_SHIFT                     14
#define TMC2130_CHM_FIELD                     ((RegisterField) {TMC2130_CHM_MASK, TMC2130_CHM_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_TBL_MASK                      0x00018000
#define TMC2130_TBL_SHIFT                     15
#define TMC2130_TBL_FIELD                     ((RegisterField) {TMC2130_TBL_MASK, TMC2130_TBL_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_VSENSE_MASK                   0x00020000
#define TMC2130_VSENSE_SHIFT                  17
#define TMC2130_VSENSE_FIELD                  ((RegisterField) {TMC2130_VSENSE_MASK, TMC2130_VSENSE_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_VHIGHFS_MASK                  0x00040000
#define TMC2130_VHIGHFS_SHIFT                 18
#define TMC2130_VHIGHFS_FIELD                 ((RegisterField) {TMC2130_VHIGHFS_MASK, TMC2130_VHIGHFS_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_VHIGHCHM_MASK                 0x00080000
#define TMC2130_VHIGHCHM_SHIFT                19
#define TMC2130_VHIGHCHM_FIELD                ((RegisterField) {TMC2130_VHIGHCHM_MASK, TMC2130_VHIGHCHM_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_SYNC_MASK                     0x00F00000
#define TMC2130_SYNC_SHIFT                    20
#define TMC2130_SYNC_FIELD                    ((RegisterField) {TMC2130_SYNC_MASK, TMC2130_SYNC_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_MRES_MASK                     0x0F000000
#define TMC2130_MRES_SHIFT                    24
#define TMC2130_MRES_FIELD                    ((RegisterField) {TMC2130_MRES_MASK, TMC2130_MRES_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_INTPOL_MASK                   0x10000000
#define TMC2130_INTPOL_SHIFT                  28
#define TMC2130_INTPOL_FIELD                  ((RegisterField) {TMC2130_INTPOL_MASK, TMC2130_INTPOL_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_DEDGE_MASK                    0x20000000
#define TMC2130_DEDGE_SHIFT                   29
#define TMC2130_DEDGE_FIELD                   ((RegisterField) {TMC2130_DEDGE_MASK, TMC2130_DEDGE_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_DISS2G_MASK                   0x40000000
#define TMC2130_DISS2G_SHIFT                  30
#define TMC2130_DISS2G_FIELD                  ((RegisterField) {TMC2130_DISS2G_MASK, TMC2130_DISS2G_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_HSTRT_MASK                    0x00000070
#define TMC2130_HSTRT_SHIFT                   4
#define TMC2130_HSTRT_FIELD                   ((RegisterField) {TMC2130_HSTRT_MASK, TMC2130_HSTRT_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_HEND_MASK                     0x00000780
#define TMC2130_HEND_SHIFT                    7
#define TMC2130_HEND_FIELD                    ((RegisterField) {TMC2130_HEND_MASK, TMC2130_HEND_SHIFT, TMC2130_CHOPCONF, false})
#define TMC2130_SEMIN_MASK                    0x0000000F
#define TMC2130_SEMIN_SHIFT                   0
#define TMC2130_SEMIN_FIELD                   ((RegisterField) {TMC2130_SEMIN_MASK, TMC2130_SEMIN_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_SEUP_MASK                     0x00000060
#define TMC2130_SEUP_SHIFT                    5
#define TMC2130_SEUP_FIELD                    ((RegisterField) {TMC2130_SEUP_MASK, TMC2130_SEUP_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_SEMAX_MASK                    0x00000F00
#define TMC2130_SEMAX_SHIFT                   8
#define TMC2130_SEMAX_FIELD                   ((RegisterField) {TMC2130_SEMAX_MASK, TMC2130_SEMAX_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_SEDN_MASK                     0x00006000
#define TMC2130_SEDN_SHIFT                    13
#define TMC2130_SEDN_FIELD                    ((RegisterField) {TMC2130_SEDN_MASK, TMC2130_SEDN_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_SEIMIN_MASK                   0x00008000
#define TMC2130_SEIMIN_SHIFT                  15
#define TMC2130_SEIMIN_FIELD                  ((RegisterField) {TMC2130_SEIMIN_MASK, TMC2130_SEIMIN_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_SGT_MASK                      0x007F0000
#define TMC2130_SGT_SHIFT                     16
#define TMC2130_SGT_FIELD                     ((RegisterField) {TMC2130_SGT_MASK, TMC2130_SGT_SHIFT, TMC2130_COOLCONF, true})
#define TMC2130_SFILT_MASK                    0x01000000
#define TMC2130_SFILT_SHIFT                   24
#define TMC2130_SFILT_FIELD                   ((RegisterField) {TMC2130_SFILT_MASK, TMC2130_SFILT_SHIFT, TMC2130_COOLCONF, false})
#define TMC2130_DC_TIME_MASK                  0x000003FF
#define TMC2130_DC_TIME_SHIFT                 0
#define TMC2130_DC_TIME_FIELD                 ((RegisterField) {TMC2130_DC_TIME_MASK, TMC2130_DC_TIME_SHIFT, TMC2130_DCCTRL, false})
#define TMC2130_DC_SG_MASK                    0x00FF0000
#define TMC2130_DC_SG_SHIFT                   16
#define TMC2130_DC_SG_FIELD                   ((RegisterField) {TMC2130_DC_SG_MASK, TMC2130_DC_SG_SHIFT, TMC2130_DCCTRL, false})
#define TMC2130_SG_RESULT_MASK                0x000003FF
#define TMC2130_SG_RESULT_SHIFT               0
#define TMC2130_SG_RESULT_FIELD               ((RegisterField) {TMC2130_SG_RESULT_MASK, TMC2130_SG_RESULT_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_FSACTIVE_MASK                 0x00008000
#define TMC2130_FSACTIVE_SHIFT                15
#define TMC2130_FSACTIVE_FIELD                ((RegisterField) {TMC2130_FSACTIVE_MASK, TMC2130_FSACTIVE_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_CS_ACTUAL_MASK                0x001F0000
#define TMC2130_CS_ACTUAL_SHIFT               16
#define TMC2130_CS_ACTUAL_FIELD               ((RegisterField) {TMC2130_CS_ACTUAL_MASK, TMC2130_CS_ACTUAL_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_STALLGUARD_MASK               0x01000000
#define TMC2130_STALLGUARD_SHIFT              24
#define TMC2130_STALLGUARD_FIELD              ((RegisterField) {TMC2130_STALLGUARD_MASK, TMC2130_STALLGUARD_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_OT_MASK                       0x02000000
#define TMC2130_OT_SHIFT                      25
#define TMC2130_OT_FIELD                      ((RegisterField) {TMC2130_OT_MASK, TMC2130_OT_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_OTPW_MASK                     0x04000000
#define TMC2130_OTPW_SHIFT                    26
#define TMC2130_OTPW_FIELD                    ((RegisterField) {TMC2130_OTPW_MASK, TMC2130_OTPW_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_S2GA_MASK                     0x08000000
#define TMC2130_S2GA_SHIFT                    27
#define TMC2130_S2GA_FIELD                    ((RegisterField) {TMC2130_S2GA_MASK, TMC2130_S2GA_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_S2GB_MASK                     0x10000000
#define TMC2130_S2GB_SHIFT                    28
#define TMC2130_S2GB_FIELD                    ((RegisterField) {TMC2130_S2GB_MASK, TMC2130_S2GB_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_OLA_MASK                      0x20000000
#define TMC2130_OLA_SHIFT                     29
#define TMC2130_OLA_FIELD                     ((RegisterField) {TMC2130_OLA_MASK, TMC2130_OLA_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_OLB_MASK                      0x40000000
#define TMC2130_OLB_SHIFT                     30
#define TMC2130_OLB_FIELD                     ((RegisterField) {TMC2130_OLB_MASK, TMC2130_OLB_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_STST_MASK                     0x80000000
#define TMC2130_STST_SHIFT                    31
#define TMC2130_STST_FIELD                    ((RegisterField) {TMC2130_STST_MASK, TMC2130_STST_SHIFT, TMC2130_DRV_STATUS, false})
#define TMC2130_PWM_AMPL_MASK                 0x000000FF
#define TMC2130_PWM_AMPL_SHIFT                0
#define TMC2130_PWM_AMPL_FIELD                ((RegisterField) {TMC2130_PWM_AMPL_MASK, TMC2130_PWM_AMPL_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_PWM_GRAD_MASK                 0x0000FF00
#define TMC2130_PWM_GRAD_SHIFT                8
#define TMC2130_PWM_GRAD_FIELD                ((RegisterField) {TMC2130_PWM_GRAD_MASK, TMC2130_PWM_GRAD_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_PWM_FREQ_MASK                 0x00030000
#define TMC2130_PWM_FREQ_SHIFT                16
#define TMC2130_PWM_FREQ_FIELD                ((RegisterField) {TMC2130_PWM_FREQ_MASK, TMC2130_PWM_FREQ_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_PWM_AUTOSCALE_MASK            0x00040000
#define TMC2130_PWM_AUTOSCALE_SHIFT           18
#define TMC2130_PWM_AUTOSCALE_FIELD           ((RegisterField) {TMC2130_PWM_AUTOSCALE_MASK, TMC2130_PWM_AUTOSCALE_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_PWM_SYMMETRIC_MASK            0x00080000
#define TMC2130_PWM_SYMMETRIC_SHIFT           19
#define TMC2130_PWM_SYMMETRIC_FIELD           ((RegisterField) {TMC2130_PWM_SYMMETRIC_MASK, TMC2130_PWM_SYMMETRIC_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_FREEWHEEL_MASK                0x00300000
#define TMC2130_FREEWHEEL_SHIFT               20
#define TMC2130_FREEWHEEL_FIELD               ((RegisterField) {TMC2130_FREEWHEEL_MASK, TMC2130_FREEWHEEL_SHIFT, TMC2130_PWMCONF, false})
#define TMC2130_PWM_SCALE_MASK                0x000000FF
#define TMC2130_PWM_SCALE_SHIFT               0
#define TMC2130_PWM_SCALE_FIELD               ((RegisterField) {TMC2130_PWM_SCALE_MASK, TMC2130_PWM_SCALE_SHIFT, TMC2130_PWM_SCALE, false})
#define TMC2130_INV_MASK                      0x00000001
#define TMC2130_INV_SHIFT                     0
#define TMC2130_INV_FIELD                     ((RegisterField) {TMC2130_INV_MASK, TMC2130_INV_SHIFT, TMC2130_ENCM_CTRL, false})
#define TMC2130_MAXSPEED_MASK                 0x00000002
#define TMC2130_MAXSPEED_SHIFT                1
#define TMC2130_MAXSPEED_FIELD                ((RegisterField) {TMC2130_MAXSPEED_MASK, TMC2130_MAXSPEED_SHIFT, TMC2130_ENCM_CTRL, false})
#define TMC2130_LOST_STEPS_MASK               0x000FFFFF
#define TMC2130_LOST_STEPS_SHIFT              0
#define TMC2130_LOST_STEPS_FIELD              ((RegisterField) {TMC2130_LOST_STEPS_MASK, TMC2130_LOST_STEPS_SHIFT, TMC2130_LOST_STEPS, false})

#endif
