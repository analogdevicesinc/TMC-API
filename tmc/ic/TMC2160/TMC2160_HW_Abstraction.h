/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2160_HW_ABSTRACTION
#define TMC2160_HW_ABSTRACTION


// Constants

#define TMC2160_REGISTER_COUNT   128 // Default register count
#define TMC2160_MOTORS           1
#define TMC2160_WRITE_BIT        0x80
#define TMC2160_ADDRESS_MASK     0x7F
#define TMC2160_MAX_VELOCITY     (int32_t)  2147483647
#define TMC2160_MAX_ACCELERATION (uint32_t)  4294967295u

// Registers in TMC2160

#define TMC2160_GCONF         0x00
#define TMC2160_GSTAT         0x01
#define TMC2160_IOIN___OUTPUT 0x04
#define TMC2160_X_COMPARE     0x05
#define TMC2160_OTP_PROG      0x06
#define TMC2160_OTP_READ      0x07
#define TMC2160_FACTORY_CONF  0x08
#define TMC2160_SHORT_CONF    0x09
#define TMC2160_DRV_CONF      0x0A
#define TMC2160_GLOBAL_SCALER 0x0B
#define TMC2160_OFFSET_READ   0x0C
#define TMC2160_IHOLD_IRUN    0x10
#define TMC2160_TPOWERDOWN    0x11
#define TMC2160_TSTEP         0x12
#define TMC2160_TPWMTHRS      0x13
#define TMC2160_TCOOLTHRS     0x14
#define TMC2160_THIGH         0x15
#define TMC2160_XDIRECT       0x2D
#define TMC2160_VDCMIN        0x33
#define TMC2160_MSLUT__       0x60
//#define TMC2160_MSLUT__       0x61
//#define TMC2160_MSLUT__       0x62
//#define TMC2160_MSLUT__       0x63
//#define TMC2160_MSLUT__       0x64
//#define TMC2160_MSLUT__       0x65
//#define TMC2160_MSLUT__       0x66
//#define TMC2160_MSLUT__       0x67
#define TMC2160_MSLUTSEL      0x68
#define TMC2160_MSLUTSTART    0x69
#define TMC2160_MSCNT         0x6A
#define TMC2160_MSCURACT      0x6B
#define TMC2160_CHOPCONF      0x6C
#define TMC2160_COOLCONF      0x6D
#define TMC2160_DCCTRL        0x6E
#define TMC2160_DRV_STATUS    0x6F
#define TMC2160_PWMCONF       0x70
#define TMC2160_PWM_SCALE     0x71
#define TMC2160_PWM_AUTO      0x72
#define TMC2160_LOST_STEPS    0x73

// Register fields in TMC2160


#define TMC2160_RECALIBRATE_MASK                         0x00000001
#define TMC2160_RECALIBRATE_SHIFT                        0
#define TMC2160_RECALIBRATE_FIELD                        ((TMC2160RegisterField) {TMC2160_RECALIBRATE_MASK, TMC2160_RECALIBRATE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_FASTSTANDSTILL_MASK                      0x00000002
#define TMC2160_FASTSTANDSTILL_SHIFT                     1
#define TMC2160_FASTSTANDSTILL_FIELD                     ((TMC2160RegisterField) {TMC2160_FASTSTANDSTILL_MASK, TMC2160_FASTSTANDSTILL_SHIFT, TMC2160_GCONF, false})
#define TMC2160_EN_PWM_MODE_MASK                         0x00000004
#define TMC2160_EN_PWM_MODE_SHIFT                        2
#define TMC2160_EN_PWM_MODE_FIELD                        ((TMC2160RegisterField) {TMC2160_EN_PWM_MODE_MASK, TMC2160_EN_PWM_MODE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_MULTISTEP_FILT_MASK                      0x00000008
#define TMC2160_MULTISTEP_FILT_SHIFT                     3
#define TMC2160_MULTISTEP_FILT_FIELD                     ((TMC2160RegisterField) {TMC2160_MULTISTEP_FILT_MASK, TMC2160_MULTISTEP_FILT_SHIFT, TMC2160_GCONF, false})
#define TMC2160_SHAFT_MASK                               0x00000010
#define TMC2160_SHAFT_SHIFT                              4
#define TMC2160_SHAFT_FIELD                              ((TMC2160RegisterField) {TMC2160_SHAFT_MASK, TMC2160_SHAFT_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__MASK   0x00000020
#define TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__SHIFT  5
#define TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__FIELD  ((TMC2160RegisterField) {TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__MASK, TMC2160_DIAG0_ERROR__ONLY_WITH_SD_MODE_1__SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__MASK    0x00000040
#define TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__SHIFT   6
#define TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__FIELD   ((TMC2160RegisterField) {TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__MASK, TMC2160_DIAG0_OTPW__ONLY_WITH_SD_MODE_1__SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG0_STALL_MASK                         0x00000080
#define TMC2160_DIAG0_STALL_SHIFT                        7
#define TMC2160_DIAG0_STALL_FIELD                        ((TMC2160RegisterField) {TMC2160_DIAG0_STALL_MASK, TMC2160_DIAG0_STALL_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_STALL_MASK                         0x00000100
#define TMC2160_DIAG1_STALL_SHIFT                        8
#define TMC2160_DIAG1_STALL_FIELD                        ((TMC2160RegisterField) {TMC2160_DIAG1_STALL_MASK, TMC2160_DIAG1_STALL_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_INDEX_MASK                         0x00000200
#define TMC2160_DIAG1_INDEX_SHIFT                        9
#define TMC2160_DIAG1_INDEX_FIELD                        ((TMC2160RegisterField) {TMC2160_DIAG1_INDEX_MASK, TMC2160_DIAG1_INDEX_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_ONSTATE_MASK                       0x00000400
#define TMC2160_DIAG1_ONSTATE_SHIFT                      10
#define TMC2160_DIAG1_ONSTATE_FIELD                      ((TMC2160RegisterField) {TMC2160_DIAG1_ONSTATE_MASK, TMC2160_DIAG1_ONSTATE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_STEPS_SKIPPED_MASK                 0x00000800
#define TMC2160_DIAG1_STEPS_SKIPPED_SHIFT                11
#define TMC2160_DIAG1_STEPS_SKIPPED_FIELD                ((TMC2160RegisterField) {TMC2160_DIAG1_STEPS_SKIPPED_MASK, TMC2160_DIAG1_STEPS_SKIPPED_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG0_INT_PUSHPULL_MASK                  0x00001000
#define TMC2160_DIAG0_INT_PUSHPULL_SHIFT                 12
#define TMC2160_DIAG0_INT_PUSHPULL_FIELD                 ((TMC2160RegisterField) {TMC2160_DIAG0_INT_PUSHPULL_MASK, TMC2160_DIAG0_INT_PUSHPULL_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_POSCOMP_PUSHPULL_MASK              0x00002000
#define TMC2160_DIAG1_POSCOMP_PUSHPULL_SHIFT             13
#define TMC2160_DIAG1_POSCOMP_PUSHPULL_FIELD             ((TMC2160RegisterField) {TMC2160_DIAG1_POSCOMP_PUSHPULL_MASK, TMC2160_DIAG1_POSCOMP_PUSHPULL_SHIFT, TMC2160_GCONF, false})
#define TMC2160_SMALL_HYSTERESIS_MASK                    0x00004000
#define TMC2160_SMALL_HYSTERESIS_SHIFT                   14
#define TMC2160_SMALL_HYSTERESIS_FIELD                   ((TMC2160RegisterField) {TMC2160_SMALL_HYSTERESIS_MASK, TMC2160_SMALL_HYSTERESIS_SHIFT, TMC2160_GCONF, false})
#define TMC2160_STOP_ENABLE_MASK                         0x00008000
#define TMC2160_STOP_ENABLE_SHIFT                        15
#define TMC2160_STOP_ENABLE_FIELD                        ((TMC2160RegisterField) {TMC2160_STOP_ENABLE_MASK, TMC2160_STOP_ENABLE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIRECT_MODE_MASK                         0x00010000
#define TMC2160_DIRECT_MODE_SHIFT                        16
#define TMC2160_DIRECT_MODE_FIELD                        ((TMC2160RegisterField) {TMC2160_DIRECT_MODE_MASK, TMC2160_DIRECT_MODE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_TEST_MODE_MASK                           0x00020000
#define TMC2160_TEST_MODE_SHIFT                          17
#define TMC2160_TEST_MODE_FIELD                          ((TMC2160RegisterField) {TMC2160_TEST_MODE_MASK, TMC2160_TEST_MODE_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG0_STEP_MASK                          0x00000080
#define TMC2160_DIAG0_STEP_SHIFT                         7
#define TMC2160_DIAG0_STEP_FIELD                         ((TMC2160RegisterField) {TMC2160_DIAG0_STEP_MASK, TMC2160_DIAG0_STEP_SHIFT, TMC2160_GCONF, false})
#define TMC2160_DIAG1_DIR_MASK                           0x00000100
#define TMC2160_DIAG1_DIR_SHIFT                          8
#define TMC2160_DIAG1_DIR_FIELD                          ((TMC2160RegisterField) {TMC2160_DIAG1_DIR_MASK, TMC2160_DIAG1_DIR_SHIFT, TMC2160_GCONF, false})
#define TMC2160_RESET_MASK                               0x00000001
#define TMC2160_RESET_SHIFT                              0
#define TMC2160_RESET_FIELD                              ((TMC2160RegisterField) {TMC2160_RESET_MASK, TMC2160_RESET_SHIFT, TMC2160_GSTAT, false})
#define TMC2160_DRV_ERR_MASK                             0x00000002
#define TMC2160_DRV_ERR_SHIFT                            1
#define TMC2160_DRV_ERR_FIELD                            ((TMC2160RegisterField) {TMC2160_DRV_ERR_MASK, TMC2160_DRV_ERR_SHIFT, TMC2160_GSTAT, false})
#define TMC2160_UV_CP_MASK                               0x00000004
#define TMC2160_UV_CP_SHIFT                              2
#define TMC2160_UV_CP_FIELD                              ((TMC2160RegisterField) {TMC2160_UV_CP_MASK, TMC2160_UV_CP_SHIFT, TMC2160_GSTAT, false})
#define TMC2160_STEP_MASK                                0x00000001
#define TMC2160_STEP_SHIFT                               0
#define TMC2160_STEP_FIELD                               ((TMC2160RegisterField) {TMC2160_STEP_MASK, TMC2160_STEP_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_DIR_MASK                                 0x00000002
#define TMC2160_DIR_SHIFT                                1
#define TMC2160_DIR_FIELD                                ((TMC2160RegisterField) {TMC2160_DIR_MASK, TMC2160_DIR_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_DCEN_CFG4_MASK                           0x00000004
#define TMC2160_DCEN_CFG4_SHIFT                          2
#define TMC2160_DCEN_CFG4_FIELD                          ((TMC2160RegisterField) {TMC2160_DCEN_CFG4_MASK, TMC2160_DCEN_CFG4_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_DCIN_CFG5_MASK                           0x00000008
#define TMC2160_DCIN_CFG5_SHIFT                          3
#define TMC2160_DCIN_CFG5_FIELD                          ((TMC2160RegisterField) {TMC2160_DCIN_CFG5_MASK, TMC2160_DCIN_CFG5_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_DRV_ENN_MASK                             0x00000010
#define TMC2160_DRV_ENN_SHIFT                            4
#define TMC2160_DRV_ENN_FIELD                            ((TMC2160RegisterField) {TMC2160_DRV_ENN_MASK, TMC2160_DRV_ENN_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_DCO_CFG6_MASK                            0x00000020
#define TMC2160_DCO_CFG6_SHIFT                           5
#define TMC2160_DCO_CFG6_FIELD                           ((TMC2160RegisterField) {TMC2160_DCO_CFG6_MASK, TMC2160_DCO_CFG6_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_VERSION_MASK                             0xFF000000
#define TMC2160_VERSION_SHIFT                            24
#define TMC2160_VERSION_FIELD                            ((TMC2160RegisterField) {TMC2160_VERSION_MASK, TMC2160_VERSION_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_OUTPUT_PIN_POLARITY_MASK                 0x00000001
#define TMC2160_OUTPUT_PIN_POLARITY_SHIFT                0
#define TMC2160_OUTPUT_PIN_POLARITY_FIELD                ((TMC2160RegisterField) {TMC2160_OUTPUT_PIN_POLARITY_MASK, TMC2160_OUTPUT_PIN_POLARITY_SHIFT, TMC2160_IOIN / OUTPUT, false})
#define TMC2160_X_COMPARE_MASK                           0xFFFFFFFF
#define TMC2160_X_COMPARE_SHIFT                          0
#define TMC2160_X_COMPARE_FIELD                          ((TMC2160RegisterField) {TMC2160_X_COMPARE_MASK, TMC2160_X_COMPARE_SHIFT, TMC2160_X_COMPARE, false})
#define TMC2160_OTPBIT_MASK                              0x00000007
#define TMC2160_OTPBIT_SHIFT                             0
#define TMC2160_OTPBIT_FIELD                             ((TMC2160RegisterField) {TMC2160_OTPBIT_MASK, TMC2160_OTPBIT_SHIFT, TMC2160_OTP_PROG, false})
#define TMC2160_OTPBYTE_MASK                             0x00000030
#define TMC2160_OTPBYTE_SHIFT                            4
#define TMC2160_OTPBYTE_FIELD                            ((TMC2160RegisterField) {TMC2160_OTPBYTE_MASK, TMC2160_OTPBYTE_SHIFT, TMC2160_OTP_PROG, false})
#define TMC2160_OTPMAGIC_MASK                            0x0000FF00
#define TMC2160_OTPMAGIC_SHIFT                           8
#define TMC2160_OTPMAGIC_FIELD                           ((TMC2160RegisterField) {TMC2160_OTPMAGIC_MASK, TMC2160_OTPMAGIC_SHIFT, TMC2160_OTP_PROG, false})
#define TMC2160_OTP_TBL_MASK                             0x00000080
#define TMC2160_OTP_TBL_SHIFT                            7
#define TMC2160_OTP_TBL_FIELD                            ((TMC2160RegisterField) {TMC2160_OTP_TBL_MASK, TMC2160_OTP_TBL_SHIFT, TMC2160_OTP_READ, false})
#define TMC2160_OTP_BBM_MASK                             0x00000040
#define TMC2160_OTP_BBM_SHIFT                            6
#define TMC2160_OTP_BBM_FIELD                            ((TMC2160RegisterField) {TMC2160_OTP_BBM_MASK, TMC2160_OTP_BBM_SHIFT, TMC2160_OTP_READ, false})
#define TMC2160_OTP_S2_LEVEL_MASK                        0x00000020
#define TMC2160_OTP_S2_LEVEL_SHIFT                       5
#define TMC2160_OTP_S2_LEVEL_FIELD                       ((TMC2160RegisterField) {TMC2160_OTP_S2_LEVEL_MASK, TMC2160_OTP_S2_LEVEL_SHIFT, TMC2160_OTP_READ, false})
#define TMC2160_OTP_FCLKTRIM_MASK                        0x0000001F
#define TMC2160_OTP_FCLKTRIM_SHIFT                       0
#define TMC2160_OTP_FCLKTRIM_FIELD                       ((TMC2160RegisterField) {TMC2160_OTP_FCLKTRIM_MASK, TMC2160_OTP_FCLKTRIM_SHIFT, TMC2160_OTP_READ, false})
#define TMC2160_FCLKTRIM_MASK                            0x0000001F
#define TMC2160_FCLKTRIM_SHIFT                           0
#define TMC2160_FCLKTRIM_FIELD                           ((TMC2160RegisterField) {TMC2160_FCLKTRIM_MASK, TMC2160_FCLKTRIM_SHIFT, TMC2160_FACTORY_CONF, false})
#define TMC2160_S2VS_LEVEL_MASK                          0x0000000F
#define TMC2160_S2VS_LEVEL_SHIFT                         0
#define TMC2160_S2VS_LEVEL_FIELD                         ((TMC2160RegisterField) {TMC2160_S2VS_LEVEL_MASK, TMC2160_S2VS_LEVEL_SHIFT, TMC2160_SHORT_CONF, false})
#define TMC2160_S2GND_LEVEL_MASK                         0x00000F00
#define TMC2160_S2GND_LEVEL_SHIFT                        8
#define TMC2160_S2GND_LEVEL_FIELD                        ((TMC2160RegisterField) {TMC2160_S2GND_LEVEL_MASK, TMC2160_S2GND_LEVEL_SHIFT, TMC2160_SHORT_CONF, false})
#define TMC2160_SHORTFILTER_MASK                         0x00030000
#define TMC2160_SHORTFILTER_SHIFT                        16
#define TMC2160_SHORTFILTER_FIELD                        ((TMC2160RegisterField) {TMC2160_SHORTFILTER_MASK, TMC2160_SHORTFILTER_SHIFT, TMC2160_SHORT_CONF, false})
#define TMC2160_SHORTDELAY_MASK                          0x00040000
#define TMC2160_SHORTDELAY_SHIFT                         18
#define TMC2160_SHORTDELAY_FIELD                         ((TMC2160RegisterField) {TMC2160_SHORTDELAY_MASK, TMC2160_SHORTDELAY_SHIFT, TMC2160_SHORT_CONF, false})
#define TMC2160_BBMTIME_MASK                             0x0000001F
#define TMC2160_BBMTIME_SHIFT                            0
#define TMC2160_BBMTIME_FIELD                            ((TMC2160RegisterField) {TMC2160_BBMTIME_MASK, TMC2160_BBMTIME_SHIFT, TMC2160_DRV_CONF, false})
#define TMC2160_BBMCLKS_MASK                             0x00000F00
#define TMC2160_BBMCLKS_SHIFT                            8
#define TMC2160_BBMCLKS_FIELD                            ((TMC2160RegisterField) {TMC2160_BBMCLKS_MASK, TMC2160_BBMCLKS_SHIFT, TMC2160_DRV_CONF, false})
#define TMC2160_OTSELECT_MASK                            0x00030000
#define TMC2160_OTSELECT_SHIFT                           16
#define TMC2160_OTSELECT_FIELD                           ((TMC2160RegisterField) {TMC2160_OTSELECT_MASK, TMC2160_OTSELECT_SHIFT, TMC2160_DRV_CONF, false})
#define TMC2160_DRVSTRENGTH_MASK                         0x000C0000
#define TMC2160_DRVSTRENGTH_SHIFT                        18
#define TMC2160_DRVSTRENGTH_FIELD                        ((TMC2160RegisterField) {TMC2160_DRVSTRENGTH_MASK, TMC2160_DRVSTRENGTH_SHIFT, TMC2160_DRV_CONF, false})
#define TMC2160_FILT_ISENSE_MASK                         0x00300000
#define TMC2160_FILT_ISENSE_SHIFT                        20
#define TMC2160_FILT_ISENSE_FIELD                        ((TMC2160RegisterField) {TMC2160_FILT_ISENSE_MASK, TMC2160_FILT_ISENSE_SHIFT, TMC2160_DRV_CONF, false})
#define TMC2160_GLOBAL_SCALER_MASK                       0x000000FF
#define TMC2160_GLOBAL_SCALER_SHIFT                      0
#define TMC2160_GLOBAL_SCALER_FIELD                      ((TMC2160RegisterField) {TMC2160_GLOBAL_SCALER_MASK, TMC2160_GLOBAL_SCALER_SHIFT, TMC2160_GLOBAL_SCALER, false})
#define TMC2160_OFFSET_READ_A_MASK                       0x0000FF00
#define TMC2160_OFFSET_READ_A_SHIFT                      8
#define TMC2160_OFFSET_READ_A_FIELD                      ((TMC2160RegisterField) {TMC2160_OFFSET_READ_A_MASK, TMC2160_OFFSET_READ_A_SHIFT, TMC2160_OFFSET_READ, true})
#define TMC2160_OFFSET_READ_B_MASK                       0x000000FF
#define TMC2160_OFFSET_READ_B_SHIFT                      0
#define TMC2160_OFFSET_READ_B_FIELD                      ((TMC2160RegisterField) {TMC2160_OFFSET_READ_B_MASK, TMC2160_OFFSET_READ_B_SHIFT, TMC2160_OFFSET_READ, true})
#define TMC2160_IHOLD_MASK                               0x0000001F
#define TMC2160_IHOLD_SHIFT                              0
#define TMC2160_IHOLD_FIELD                              ((TMC2160RegisterField) {TMC2160_IHOLD_MASK, TMC2160_IHOLD_SHIFT, TMC2160_IHOLD_IRUN, false})
#define TMC2160_IRUN_MASK                                0x00001F00
#define TMC2160_IRUN_SHIFT                               8
#define TMC2160_IRUN_FIELD                               ((TMC2160RegisterField) {TMC2160_IRUN_MASK, TMC2160_IRUN_SHIFT, TMC2160_IHOLD_IRUN, false})
#define TMC2160_IHOLDDELAY_MASK                          0x000F0000
#define TMC2160_IHOLDDELAY_SHIFT                         16
#define TMC2160_IHOLDDELAY_FIELD                         ((TMC2160RegisterField) {TMC2160_IHOLDDELAY_MASK, TMC2160_IHOLDDELAY_SHIFT, TMC2160_IHOLD_IRUN, false})
#define TMC2160_TPOWERDOWN_MASK                          0x000000FF
#define TMC2160_TPOWERDOWN_SHIFT                         0
#define TMC2160_TPOWERDOWN_FIELD                         ((TMC2160RegisterField) {TMC2160_TPOWERDOWN_MASK, TMC2160_TPOWERDOWN_SHIFT, TMC2160_TPOWERDOWN, false})
#define TMC2160_TSTEP_MASK                               0x000FFFFF
#define TMC2160_TSTEP_SHIFT                              0
#define TMC2160_TSTEP_FIELD                              ((TMC2160RegisterField) {TMC2160_TSTEP_MASK, TMC2160_TSTEP_SHIFT, TMC2160_TSTEP, false})
#define TMC2160_TPWMTHRS_MASK                            0x000FFFFF
#define TMC2160_TPWMTHRS_SHIFT                           0
#define TMC2160_TPWMTHRS_FIELD                           ((TMC2160RegisterField) {TMC2160_TPWMTHRS_MASK, TMC2160_TPWMTHRS_SHIFT, TMC2160_TPWMTHRS, false})
#define TMC2160_TCOOLTHRS_MASK                           0x000FFFFF
#define TMC2160_TCOOLTHRS_SHIFT                          0
#define TMC2160_TCOOLTHRS_FIELD                          ((TMC2160RegisterField) {TMC2160_TCOOLTHRS_MASK, TMC2160_TCOOLTHRS_SHIFT, TMC2160_TCOOLTHRS, false})
#define TMC2160_THIGH_MASK                               0x000FFFFF
#define TMC2160_THIGH_SHIFT                              0
#define TMC2160_THIGH_FIELD                              ((TMC2160RegisterField) {TMC2160_THIGH_MASK, TMC2160_THIGH_SHIFT, TMC2160_THIGH, false})
#define TMC2160_DIRECT_CURRENT_A_MASK                    0x000001FF
#define TMC2160_DIRECT_CURRENT_A_SHIFT                   0
#define TMC2160_DIRECT_CURRENT_A_FIELD                   ((TMC2160RegisterField) {TMC2160_DIRECT_CURRENT_A_MASK, TMC2160_DIRECT_CURRENT_A_SHIFT, TMC2160_XDIRECT, true})
#define TMC2160_DIRECT_CURRENT_B_MASK                    0x01FF0000
#define TMC2160_DIRECT_CURRENT_B_SHIFT                   16
#define TMC2160_DIRECT_CURRENT_B_FIELD                   ((TMC2160RegisterField) {TMC2160_DIRECT_CURRENT_B_MASK, TMC2160_DIRECT_CURRENT_B_SHIFT, TMC2160_XDIRECT, true})
#define TMC2160_VDCMIN_MASK                              0x007FFFFF
#define TMC2160_VDCMIN_SHIFT                             0
#define TMC2160_VDCMIN_FIELD                             ((TMC2160RegisterField) {TMC2160_VDCMIN_MASK, TMC2160_VDCMIN_SHIFT, TMC2160_VDCMIN, false})
#define TMC2160_OFS0_MASK                                0x00000001
#define TMC2160_OFS0_SHIFT                               0
#define TMC2160_OFS0_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS0_MASK, TMC2160_OFS0_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS1_MASK                                0x00000002
#define TMC2160_OFS1_SHIFT                               1
#define TMC2160_OFS1_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS1_MASK, TMC2160_OFS1_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS2_MASK                                0x00000004
#define TMC2160_OFS2_SHIFT                               2
#define TMC2160_OFS2_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS2_MASK, TMC2160_OFS2_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS3_MASK                                0x00000008
#define TMC2160_OFS3_SHIFT                               3
#define TMC2160_OFS3_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS3_MASK, TMC2160_OFS3_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS4_MASK                                0x00000010
#define TMC2160_OFS4_SHIFT                               4
#define TMC2160_OFS4_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS4_MASK, TMC2160_OFS4_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS5_MASK                                0x00000020
#define TMC2160_OFS5_SHIFT                               5
#define TMC2160_OFS5_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS5_MASK, TMC2160_OFS5_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS6_MASK                                0x00000040
#define TMC2160_OFS6_SHIFT                               6
#define TMC2160_OFS6_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS6_MASK, TMC2160_OFS6_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS7_MASK                                0x00000080
#define TMC2160_OFS7_SHIFT                               7
#define TMC2160_OFS7_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS7_MASK, TMC2160_OFS7_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS8_MASK                                0x00000100
#define TMC2160_OFS8_SHIFT                               8
#define TMC2160_OFS8_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS8_MASK, TMC2160_OFS8_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS9_MASK                                0x00000200
#define TMC2160_OFS9_SHIFT                               9
#define TMC2160_OFS9_FIELD                               ((TMC2160RegisterField) {TMC2160_OFS9_MASK, TMC2160_OFS9_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS10_MASK                               0x00000400
#define TMC2160_OFS10_SHIFT                              10
#define TMC2160_OFS10_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS10_MASK, TMC2160_OFS10_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS11_MASK                               0x00000800
#define TMC2160_OFS11_SHIFT                              11
#define TMC2160_OFS11_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS11_MASK, TMC2160_OFS11_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS12_MASK                               0x00001000
#define TMC2160_OFS12_SHIFT                              12
#define TMC2160_OFS12_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS12_MASK, TMC2160_OFS12_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS13_MASK                               0x00002000
#define TMC2160_OFS13_SHIFT                              13
#define TMC2160_OFS13_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS13_MASK, TMC2160_OFS13_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS14_MASK                               0x00004000
#define TMC2160_OFS14_SHIFT                              14
#define TMC2160_OFS14_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS14_MASK, TMC2160_OFS14_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS15_MASK                               0x00008000
#define TMC2160_OFS15_SHIFT                              15
#define TMC2160_OFS15_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS15_MASK, TMC2160_OFS15_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS16_MASK                               0x00010000
#define TMC2160_OFS16_SHIFT                              16
#define TMC2160_OFS16_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS16_MASK, TMC2160_OFS16_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS17_MASK                               0x00020000
#define TMC2160_OFS17_SHIFT                              17
#define TMC2160_OFS17_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS17_MASK, TMC2160_OFS17_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS18_MASK                               0x00040000
#define TMC2160_OFS18_SHIFT                              18
#define TMC2160_OFS18_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS18_MASK, TMC2160_OFS18_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS19_MASK                               0x00080000
#define TMC2160_OFS19_SHIFT                              19
#define TMC2160_OFS19_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS19_MASK, TMC2160_OFS19_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS20_MASK                               0x00100000
#define TMC2160_OFS20_SHIFT                              20
#define TMC2160_OFS20_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS20_MASK, TMC2160_OFS20_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS21_MASK                               0x00200000
#define TMC2160_OFS21_SHIFT                              21
#define TMC2160_OFS21_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS21_MASK, TMC2160_OFS21_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS22_MASK                               0x00400000
#define TMC2160_OFS22_SHIFT                              22
#define TMC2160_OFS22_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS22_MASK, TMC2160_OFS22_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS23_MASK                               0x00800000
#define TMC2160_OFS23_SHIFT                              23
#define TMC2160_OFS23_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS23_MASK, TMC2160_OFS23_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS24_MASK                               0x01000000
#define TMC2160_OFS24_SHIFT                              24
#define TMC2160_OFS24_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS24_MASK, TMC2160_OFS24_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS25_MASK                               0x02000000
#define TMC2160_OFS25_SHIFT                              25
#define TMC2160_OFS25_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS25_MASK, TMC2160_OFS25_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS26_MASK                               0x04000000
#define TMC2160_OFS26_SHIFT                              26
#define TMC2160_OFS26_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS26_MASK, TMC2160_OFS26_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS27_MASK                               0x08000000
#define TMC2160_OFS27_SHIFT                              27
#define TMC2160_OFS27_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS27_MASK, TMC2160_OFS27_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS28_MASK                               0x10000000
#define TMC2160_OFS28_SHIFT                              28
#define TMC2160_OFS28_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS28_MASK, TMC2160_OFS28_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS29_MASK                               0x20000000
#define TMC2160_OFS29_SHIFT                              29
#define TMC2160_OFS29_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS29_MASK, TMC2160_OFS29_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS30_MASK                               0x40000000
#define TMC2160_OFS30_SHIFT                              30
#define TMC2160_OFS30_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS30_MASK, TMC2160_OFS30_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS31_MASK                               0x80000000
#define TMC2160_OFS31_SHIFT                              31
#define TMC2160_OFS31_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS31_MASK, TMC2160_OFS31_SHIFT, TMC2160_MSLUT[0], false})
#define TMC2160_OFS32_MASK                               0x00000001
#define TMC2160_OFS32_SHIFT                              0
#define TMC2160_OFS32_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS32_MASK, TMC2160_OFS32_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS33_MASK                               0x00000002
#define TMC2160_OFS33_SHIFT                              1
#define TMC2160_OFS33_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS33_MASK, TMC2160_OFS33_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS34_MASK                               0x00000004
#define TMC2160_OFS34_SHIFT                              2
#define TMC2160_OFS34_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS34_MASK, TMC2160_OFS34_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS35_MASK                               0x00000008
#define TMC2160_OFS35_SHIFT                              3
#define TMC2160_OFS35_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS35_MASK, TMC2160_OFS35_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS36_MASK                               0x00000010
#define TMC2160_OFS36_SHIFT                              4
#define TMC2160_OFS36_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS36_MASK, TMC2160_OFS36_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS37_MASK                               0x00000020
#define TMC2160_OFS37_SHIFT                              5
#define TMC2160_OFS37_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS37_MASK, TMC2160_OFS37_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS38_MASK                               0x00000040
#define TMC2160_OFS38_SHIFT                              6
#define TMC2160_OFS38_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS38_MASK, TMC2160_OFS38_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS39_MASK                               0x00000080
#define TMC2160_OFS39_SHIFT                              7
#define TMC2160_OFS39_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS39_MASK, TMC2160_OFS39_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS40_MASK                               0x00000100
#define TMC2160_OFS40_SHIFT                              8
#define TMC2160_OFS40_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS40_MASK, TMC2160_OFS40_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS41_MASK                               0x00000200
#define TMC2160_OFS41_SHIFT                              9
#define TMC2160_OFS41_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS41_MASK, TMC2160_OFS41_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS42_MASK                               0x00000400
#define TMC2160_OFS42_SHIFT                              10
#define TMC2160_OFS42_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS42_MASK, TMC2160_OFS42_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS43_MASK                               0x00000800
#define TMC2160_OFS43_SHIFT                              11
#define TMC2160_OFS43_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS43_MASK, TMC2160_OFS43_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS44_MASK                               0x00001000
#define TMC2160_OFS44_SHIFT                              12
#define TMC2160_OFS44_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS44_MASK, TMC2160_OFS44_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS45_MASK                               0x00002000
#define TMC2160_OFS45_SHIFT                              13
#define TMC2160_OFS45_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS45_MASK, TMC2160_OFS45_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS46_MASK                               0x00004000
#define TMC2160_OFS46_SHIFT                              14
#define TMC2160_OFS46_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS46_MASK, TMC2160_OFS46_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS47_MASK                               0x00008000
#define TMC2160_OFS47_SHIFT                              15
#define TMC2160_OFS47_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS47_MASK, TMC2160_OFS47_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS48_MASK                               0x00010000
#define TMC2160_OFS48_SHIFT                              16
#define TMC2160_OFS48_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS48_MASK, TMC2160_OFS48_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS49_MASK                               0x00020000
#define TMC2160_OFS49_SHIFT                              17
#define TMC2160_OFS49_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS49_MASK, TMC2160_OFS49_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS50_MASK                               0x00040000
#define TMC2160_OFS50_SHIFT                              18
#define TMC2160_OFS50_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS50_MASK, TMC2160_OFS50_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS51_MASK                               0x00080000
#define TMC2160_OFS51_SHIFT                              19
#define TMC2160_OFS51_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS51_MASK, TMC2160_OFS51_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS52_MASK                               0x00100000
#define TMC2160_OFS52_SHIFT                              20
#define TMC2160_OFS52_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS52_MASK, TMC2160_OFS52_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS53_MASK                               0x00200000
#define TMC2160_OFS53_SHIFT                              21
#define TMC2160_OFS53_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS53_MASK, TMC2160_OFS53_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS54_MASK                               0x00400000
#define TMC2160_OFS54_SHIFT                              22
#define TMC2160_OFS54_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS54_MASK, TMC2160_OFS54_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS55_MASK                               0x00800000
#define TMC2160_OFS55_SHIFT                              23
#define TMC2160_OFS55_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS55_MASK, TMC2160_OFS55_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS56_MASK                               0x01000000
#define TMC2160_OFS56_SHIFT                              24
#define TMC2160_OFS56_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS56_MASK, TMC2160_OFS56_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS57_MASK                               0x02000000
#define TMC2160_OFS57_SHIFT                              25
#define TMC2160_OFS57_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS57_MASK, TMC2160_OFS57_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS58_MASK                               0x04000000
#define TMC2160_OFS58_SHIFT                              26
#define TMC2160_OFS58_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS58_MASK, TMC2160_OFS58_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS59_MASK                               0x08000000
#define TMC2160_OFS59_SHIFT                              27
#define TMC2160_OFS59_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS59_MASK, TMC2160_OFS59_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS60_MASK                               0x10000000
#define TMC2160_OFS60_SHIFT                              28
#define TMC2160_OFS60_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS60_MASK, TMC2160_OFS60_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS61_MASK                               0x20000000
#define TMC2160_OFS61_SHIFT                              29
#define TMC2160_OFS61_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS61_MASK, TMC2160_OFS61_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS62_MASK                               0x40000000
#define TMC2160_OFS62_SHIFT                              30
#define TMC2160_OFS62_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS62_MASK, TMC2160_OFS62_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS63_MASK                               0x80000000
#define TMC2160_OFS63_SHIFT                              31
#define TMC2160_OFS63_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS63_MASK, TMC2160_OFS63_SHIFT, TMC2160_MSLUT[1], false})
#define TMC2160_OFS64_MASK                               0x00000001
#define TMC2160_OFS64_SHIFT                              0
#define TMC2160_OFS64_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS64_MASK, TMC2160_OFS64_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS65_MASK                               0x00000002
#define TMC2160_OFS65_SHIFT                              1
#define TMC2160_OFS65_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS65_MASK, TMC2160_OFS65_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS66_MASK                               0x00000004
#define TMC2160_OFS66_SHIFT                              2
#define TMC2160_OFS66_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS66_MASK, TMC2160_OFS66_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS67_MASK                               0x00000008
#define TMC2160_OFS67_SHIFT                              3
#define TMC2160_OFS67_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS67_MASK, TMC2160_OFS67_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS68_MASK                               0x00000010
#define TMC2160_OFS68_SHIFT                              4
#define TMC2160_OFS68_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS68_MASK, TMC2160_OFS68_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS69_MASK                               0x00000020
#define TMC2160_OFS69_SHIFT                              5
#define TMC2160_OFS69_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS69_MASK, TMC2160_OFS69_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS70_MASK                               0x00000040
#define TMC2160_OFS70_SHIFT                              6
#define TMC2160_OFS70_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS70_MASK, TMC2160_OFS70_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS71_MASK                               0x00000080
#define TMC2160_OFS71_SHIFT                              7
#define TMC2160_OFS71_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS71_MASK, TMC2160_OFS71_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS72_MASK                               0x00000100
#define TMC2160_OFS72_SHIFT                              8
#define TMC2160_OFS72_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS72_MASK, TMC2160_OFS72_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS73_MASK                               0x00000200
#define TMC2160_OFS73_SHIFT                              9
#define TMC2160_OFS73_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS73_MASK, TMC2160_OFS73_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS74_MASK                               0x00000400
#define TMC2160_OFS74_SHIFT                              10
#define TMC2160_OFS74_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS74_MASK, TMC2160_OFS74_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS75_MASK                               0x00000800
#define TMC2160_OFS75_SHIFT                              11
#define TMC2160_OFS75_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS75_MASK, TMC2160_OFS75_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS76_MASK                               0x00001000
#define TMC2160_OFS76_SHIFT                              12
#define TMC2160_OFS76_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS76_MASK, TMC2160_OFS76_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS77_MASK                               0x00002000
#define TMC2160_OFS77_SHIFT                              13
#define TMC2160_OFS77_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS77_MASK, TMC2160_OFS77_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS78_MASK                               0x00004000
#define TMC2160_OFS78_SHIFT                              14
#define TMC2160_OFS78_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS78_MASK, TMC2160_OFS78_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS79_MASK                               0x00008000
#define TMC2160_OFS79_SHIFT                              15
#define TMC2160_OFS79_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS79_MASK, TMC2160_OFS79_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS80_MASK                               0x00010000
#define TMC2160_OFS80_SHIFT                              16
#define TMC2160_OFS80_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS80_MASK, TMC2160_OFS80_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS81_MASK                               0x00020000
#define TMC2160_OFS81_SHIFT                              17
#define TMC2160_OFS81_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS81_MASK, TMC2160_OFS81_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS82_MASK                               0x00040000
#define TMC2160_OFS82_SHIFT                              18
#define TMC2160_OFS82_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS82_MASK, TMC2160_OFS82_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS83_MASK                               0x00080000
#define TMC2160_OFS83_SHIFT                              19
#define TMC2160_OFS83_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS83_MASK, TMC2160_OFS83_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS84_MASK                               0x00100000
#define TMC2160_OFS84_SHIFT                              20
#define TMC2160_OFS84_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS84_MASK, TMC2160_OFS84_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS85_MASK                               0x00200000
#define TMC2160_OFS85_SHIFT                              21
#define TMC2160_OFS85_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS85_MASK, TMC2160_OFS85_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS86_MASK                               0x00400000
#define TMC2160_OFS86_SHIFT                              22
#define TMC2160_OFS86_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS86_MASK, TMC2160_OFS86_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS87_MASK                               0x00800000
#define TMC2160_OFS87_SHIFT                              23
#define TMC2160_OFS87_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS87_MASK, TMC2160_OFS87_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS88_MASK                               0x01000000
#define TMC2160_OFS88_SHIFT                              24
#define TMC2160_OFS88_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS88_MASK, TMC2160_OFS88_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS89_MASK                               0x02000000
#define TMC2160_OFS89_SHIFT                              25
#define TMC2160_OFS89_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS89_MASK, TMC2160_OFS89_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS90_MASK                               0x04000000
#define TMC2160_OFS90_SHIFT                              26
#define TMC2160_OFS90_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS90_MASK, TMC2160_OFS90_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS91_MASK                               0x08000000
#define TMC2160_OFS91_SHIFT                              27
#define TMC2160_OFS91_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS91_MASK, TMC2160_OFS91_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS92_MASK                               0x10000000
#define TMC2160_OFS92_SHIFT                              28
#define TMC2160_OFS92_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS92_MASK, TMC2160_OFS92_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS93_MASK                               0x20000000
#define TMC2160_OFS93_SHIFT                              29
#define TMC2160_OFS93_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS93_MASK, TMC2160_OFS93_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS94_MASK                               0x40000000
#define TMC2160_OFS94_SHIFT                              30
#define TMC2160_OFS94_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS94_MASK, TMC2160_OFS94_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS95_MASK                               0x80000000
#define TMC2160_OFS95_SHIFT                              31
#define TMC2160_OFS95_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS95_MASK, TMC2160_OFS95_SHIFT, TMC2160_MSLUT[2], false})
#define TMC2160_OFS96_MASK                               0x00000001
#define TMC2160_OFS96_SHIFT                              0
#define TMC2160_OFS96_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS96_MASK, TMC2160_OFS96_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS97_MASK                               0x00000002
#define TMC2160_OFS97_SHIFT                              1
#define TMC2160_OFS97_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS97_MASK, TMC2160_OFS97_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS98_MASK                               0x00000004
#define TMC2160_OFS98_SHIFT                              2
#define TMC2160_OFS98_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS98_MASK, TMC2160_OFS98_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS99_MASK                               0x00000008
#define TMC2160_OFS99_SHIFT                              3
#define TMC2160_OFS99_FIELD                              ((TMC2160RegisterField) {TMC2160_OFS99_MASK, TMC2160_OFS99_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS100_MASK                              0x00000010
#define TMC2160_OFS100_SHIFT                             4
#define TMC2160_OFS100_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS100_MASK, TMC2160_OFS100_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS101_MASK                              0x00000020
#define TMC2160_OFS101_SHIFT                             5
#define TMC2160_OFS101_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS101_MASK, TMC2160_OFS101_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS102_MASK                              0x00000040
#define TMC2160_OFS102_SHIFT                             6
#define TMC2160_OFS102_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS102_MASK, TMC2160_OFS102_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS103_MASK                              0x00000080
#define TMC2160_OFS103_SHIFT                             7
#define TMC2160_OFS103_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS103_MASK, TMC2160_OFS103_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS104_MASK                              0x00000100
#define TMC2160_OFS104_SHIFT                             8
#define TMC2160_OFS104_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS104_MASK, TMC2160_OFS104_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS105_MASK                              0x00000200
#define TMC2160_OFS105_SHIFT                             9
#define TMC2160_OFS105_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS105_MASK, TMC2160_OFS105_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS106_MASK                              0x00000400
#define TMC2160_OFS106_SHIFT                             10
#define TMC2160_OFS106_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS106_MASK, TMC2160_OFS106_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS107_MASK                              0x00000800
#define TMC2160_OFS107_SHIFT                             11
#define TMC2160_OFS107_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS107_MASK, TMC2160_OFS107_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS108_MASK                              0x00001000
#define TMC2160_OFS108_SHIFT                             12
#define TMC2160_OFS108_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS108_MASK, TMC2160_OFS108_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS109_MASK                              0x00002000
#define TMC2160_OFS109_SHIFT                             13
#define TMC2160_OFS109_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS109_MASK, TMC2160_OFS109_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS110_MASK                              0x00004000
#define TMC2160_OFS110_SHIFT                             14
#define TMC2160_OFS110_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS110_MASK, TMC2160_OFS110_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS111_MASK                              0x00008000
#define TMC2160_OFS111_SHIFT                             15
#define TMC2160_OFS111_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS111_MASK, TMC2160_OFS111_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS112_MASK                              0x00010000
#define TMC2160_OFS112_SHIFT                             16
#define TMC2160_OFS112_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS112_MASK, TMC2160_OFS112_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS113_MASK                              0x00020000
#define TMC2160_OFS113_SHIFT                             17
#define TMC2160_OFS113_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS113_MASK, TMC2160_OFS113_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS114_MASK                              0x00040000
#define TMC2160_OFS114_SHIFT                             18
#define TMC2160_OFS114_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS114_MASK, TMC2160_OFS114_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS115_MASK                              0x00080000
#define TMC2160_OFS115_SHIFT                             19
#define TMC2160_OFS115_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS115_MASK, TMC2160_OFS115_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS116_MASK                              0x00100000
#define TMC2160_OFS116_SHIFT                             20
#define TMC2160_OFS116_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS116_MASK, TMC2160_OFS116_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS117_MASK                              0x00200000
#define TMC2160_OFS117_SHIFT                             21
#define TMC2160_OFS117_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS117_MASK, TMC2160_OFS117_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS118_MASK                              0x00400000
#define TMC2160_OFS118_SHIFT                             22
#define TMC2160_OFS118_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS118_MASK, TMC2160_OFS118_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS119_MASK                              0x00800000
#define TMC2160_OFS119_SHIFT                             23
#define TMC2160_OFS119_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS119_MASK, TMC2160_OFS119_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS120_MASK                              0x01000000
#define TMC2160_OFS120_SHIFT                             24
#define TMC2160_OFS120_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS120_MASK, TMC2160_OFS120_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS121_MASK                              0x02000000
#define TMC2160_OFS121_SHIFT                             25
#define TMC2160_OFS121_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS121_MASK, TMC2160_OFS121_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS122_MASK                              0x04000000
#define TMC2160_OFS122_SHIFT                             26
#define TMC2160_OFS122_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS122_MASK, TMC2160_OFS122_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS123_MASK                              0x08000000
#define TMC2160_OFS123_SHIFT                             27
#define TMC2160_OFS123_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS123_MASK, TMC2160_OFS123_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS124_MASK                              0x10000000
#define TMC2160_OFS124_SHIFT                             28
#define TMC2160_OFS124_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS124_MASK, TMC2160_OFS124_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS125_MASK                              0x20000000
#define TMC2160_OFS125_SHIFT                             29
#define TMC2160_OFS125_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS125_MASK, TMC2160_OFS125_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS126_MASK                              0x40000000
#define TMC2160_OFS126_SHIFT                             30
#define TMC2160_OFS126_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS126_MASK, TMC2160_OFS126_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS127_MASK                              0x80000000
#define TMC2160_OFS127_SHIFT                             31
#define TMC2160_OFS127_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS127_MASK, TMC2160_OFS127_SHIFT, TMC2160_MSLUT[3], false})
#define TMC2160_OFS128_MASK                              0x00000001
#define TMC2160_OFS128_SHIFT                             0
#define TMC2160_OFS128_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS128_MASK, TMC2160_OFS128_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS129_MASK                              0x00000002
#define TMC2160_OFS129_SHIFT                             1
#define TMC2160_OFS129_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS129_MASK, TMC2160_OFS129_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS130_MASK                              0x00000004
#define TMC2160_OFS130_SHIFT                             2
#define TMC2160_OFS130_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS130_MASK, TMC2160_OFS130_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS131_MASK                              0x00000008
#define TMC2160_OFS131_SHIFT                             3
#define TMC2160_OFS131_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS131_MASK, TMC2160_OFS131_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS132_MASK                              0x00000010
#define TMC2160_OFS132_SHIFT                             4
#define TMC2160_OFS132_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS132_MASK, TMC2160_OFS132_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS133_MASK                              0x00000020
#define TMC2160_OFS133_SHIFT                             5
#define TMC2160_OFS133_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS133_MASK, TMC2160_OFS133_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS134_MASK                              0x00000040
#define TMC2160_OFS134_SHIFT                             6
#define TMC2160_OFS134_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS134_MASK, TMC2160_OFS134_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS135_MASK                              0x00000080
#define TMC2160_OFS135_SHIFT                             7
#define TMC2160_OFS135_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS135_MASK, TMC2160_OFS135_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS136_MASK                              0x00000100
#define TMC2160_OFS136_SHIFT                             8
#define TMC2160_OFS136_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS136_MASK, TMC2160_OFS136_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS137_MASK                              0x00000200
#define TMC2160_OFS137_SHIFT                             9
#define TMC2160_OFS137_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS137_MASK, TMC2160_OFS137_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS138_MASK                              0x00000400
#define TMC2160_OFS138_SHIFT                             10
#define TMC2160_OFS138_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS138_MASK, TMC2160_OFS138_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS139_MASK                              0x00000800
#define TMC2160_OFS139_SHIFT                             11
#define TMC2160_OFS139_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS139_MASK, TMC2160_OFS139_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS140_MASK                              0x00001000
#define TMC2160_OFS140_SHIFT                             12
#define TMC2160_OFS140_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS140_MASK, TMC2160_OFS140_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS141_MASK                              0x00002000
#define TMC2160_OFS141_SHIFT                             13
#define TMC2160_OFS141_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS141_MASK, TMC2160_OFS141_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS142_MASK                              0x00004000
#define TMC2160_OFS142_SHIFT                             14
#define TMC2160_OFS142_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS142_MASK, TMC2160_OFS142_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS143_MASK                              0x00008000
#define TMC2160_OFS143_SHIFT                             15
#define TMC2160_OFS143_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS143_MASK, TMC2160_OFS143_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS144_MASK                              0x00010000
#define TMC2160_OFS144_SHIFT                             16
#define TMC2160_OFS144_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS144_MASK, TMC2160_OFS144_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS145_MASK                              0x00020000
#define TMC2160_OFS145_SHIFT                             17
#define TMC2160_OFS145_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS145_MASK, TMC2160_OFS145_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS146_MASK                              0x00040000
#define TMC2160_OFS146_SHIFT                             18
#define TMC2160_OFS146_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS146_MASK, TMC2160_OFS146_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS147_MASK                              0x00080000
#define TMC2160_OFS147_SHIFT                             19
#define TMC2160_OFS147_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS147_MASK, TMC2160_OFS147_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS148_MASK                              0x00100000
#define TMC2160_OFS148_SHIFT                             20
#define TMC2160_OFS148_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS148_MASK, TMC2160_OFS148_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS149_MASK                              0x00200000
#define TMC2160_OFS149_SHIFT                             21
#define TMC2160_OFS149_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS149_MASK, TMC2160_OFS149_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS150_MASK                              0x00400000
#define TMC2160_OFS150_SHIFT                             22
#define TMC2160_OFS150_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS150_MASK, TMC2160_OFS150_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS151_MASK                              0x00800000
#define TMC2160_OFS151_SHIFT                             23
#define TMC2160_OFS151_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS151_MASK, TMC2160_OFS151_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS152_MASK                              0x01000000
#define TMC2160_OFS152_SHIFT                             24
#define TMC2160_OFS152_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS152_MASK, TMC2160_OFS152_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS153_MASK                              0x02000000
#define TMC2160_OFS153_SHIFT                             25
#define TMC2160_OFS153_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS153_MASK, TMC2160_OFS153_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS154_MASK                              0x04000000
#define TMC2160_OFS154_SHIFT                             26
#define TMC2160_OFS154_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS154_MASK, TMC2160_OFS154_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS155_MASK                              0x08000000
#define TMC2160_OFS155_SHIFT                             27
#define TMC2160_OFS155_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS155_MASK, TMC2160_OFS155_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS156_MASK                              0x10000000
#define TMC2160_OFS156_SHIFT                             28
#define TMC2160_OFS156_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS156_MASK, TMC2160_OFS156_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS157_MASK                              0x20000000
#define TMC2160_OFS157_SHIFT                             29
#define TMC2160_OFS157_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS157_MASK, TMC2160_OFS157_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS158_MASK                              0x40000000
#define TMC2160_OFS158_SHIFT                             30
#define TMC2160_OFS158_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS158_MASK, TMC2160_OFS158_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS159_MASK                              0x80000000
#define TMC2160_OFS159_SHIFT                             31
#define TMC2160_OFS159_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS159_MASK, TMC2160_OFS159_SHIFT, TMC2160_MSLUT[4], false})
#define TMC2160_OFS160_MASK                              0x00000001
#define TMC2160_OFS160_SHIFT                             0
#define TMC2160_OFS160_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS160_MASK, TMC2160_OFS160_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS161_MASK                              0x00000002
#define TMC2160_OFS161_SHIFT                             1
#define TMC2160_OFS161_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS161_MASK, TMC2160_OFS161_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS162_MASK                              0x00000004
#define TMC2160_OFS162_SHIFT                             2
#define TMC2160_OFS162_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS162_MASK, TMC2160_OFS162_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS163_MASK                              0x00000008
#define TMC2160_OFS163_SHIFT                             3
#define TMC2160_OFS163_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS163_MASK, TMC2160_OFS163_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS164_MASK                              0x00000010
#define TMC2160_OFS164_SHIFT                             4
#define TMC2160_OFS164_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS164_MASK, TMC2160_OFS164_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS165_MASK                              0x00000020
#define TMC2160_OFS165_SHIFT                             5
#define TMC2160_OFS165_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS165_MASK, TMC2160_OFS165_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS166_MASK                              0x00000040
#define TMC2160_OFS166_SHIFT                             6
#define TMC2160_OFS166_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS166_MASK, TMC2160_OFS166_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS167_MASK                              0x00000080
#define TMC2160_OFS167_SHIFT                             7
#define TMC2160_OFS167_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS167_MASK, TMC2160_OFS167_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS168_MASK                              0x00000100
#define TMC2160_OFS168_SHIFT                             8
#define TMC2160_OFS168_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS168_MASK, TMC2160_OFS168_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS169_MASK                              0x00000200
#define TMC2160_OFS169_SHIFT                             9
#define TMC2160_OFS169_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS169_MASK, TMC2160_OFS169_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS170_MASK                              0x00000400
#define TMC2160_OFS170_SHIFT                             10
#define TMC2160_OFS170_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS170_MASK, TMC2160_OFS170_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS171_MASK                              0x00000800
#define TMC2160_OFS171_SHIFT                             11
#define TMC2160_OFS171_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS171_MASK, TMC2160_OFS171_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS172_MASK                              0x00001000
#define TMC2160_OFS172_SHIFT                             12
#define TMC2160_OFS172_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS172_MASK, TMC2160_OFS172_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS173_MASK                              0x00002000
#define TMC2160_OFS173_SHIFT                             13
#define TMC2160_OFS173_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS173_MASK, TMC2160_OFS173_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS174_MASK                              0x00004000
#define TMC2160_OFS174_SHIFT                             14
#define TMC2160_OFS174_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS174_MASK, TMC2160_OFS174_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS175_MASK                              0x00008000
#define TMC2160_OFS175_SHIFT                             15
#define TMC2160_OFS175_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS175_MASK, TMC2160_OFS175_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS176_MASK                              0x00010000
#define TMC2160_OFS176_SHIFT                             16
#define TMC2160_OFS176_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS176_MASK, TMC2160_OFS176_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS177_MASK                              0x00020000
#define TMC2160_OFS177_SHIFT                             17
#define TMC2160_OFS177_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS177_MASK, TMC2160_OFS177_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS178_MASK                              0x00040000
#define TMC2160_OFS178_SHIFT                             18
#define TMC2160_OFS178_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS178_MASK, TMC2160_OFS178_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS179_MASK                              0x00080000
#define TMC2160_OFS179_SHIFT                             19
#define TMC2160_OFS179_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS179_MASK, TMC2160_OFS179_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS180_MASK                              0x00100000
#define TMC2160_OFS180_SHIFT                             20
#define TMC2160_OFS180_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS180_MASK, TMC2160_OFS180_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS181_MASK                              0x00200000
#define TMC2160_OFS181_SHIFT                             21
#define TMC2160_OFS181_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS181_MASK, TMC2160_OFS181_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS182_MASK                              0x00400000
#define TMC2160_OFS182_SHIFT                             22
#define TMC2160_OFS182_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS182_MASK, TMC2160_OFS182_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS183_MASK                              0x00800000
#define TMC2160_OFS183_SHIFT                             23
#define TMC2160_OFS183_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS183_MASK, TMC2160_OFS183_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS184_MASK                              0x01000000
#define TMC2160_OFS184_SHIFT                             24
#define TMC2160_OFS184_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS184_MASK, TMC2160_OFS184_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS185_MASK                              0x02000000
#define TMC2160_OFS185_SHIFT                             25
#define TMC2160_OFS185_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS185_MASK, TMC2160_OFS185_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS186_MASK                              0x04000000
#define TMC2160_OFS186_SHIFT                             26
#define TMC2160_OFS186_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS186_MASK, TMC2160_OFS186_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS187_MASK                              0x08000000
#define TMC2160_OFS187_SHIFT                             27
#define TMC2160_OFS187_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS187_MASK, TMC2160_OFS187_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS188_MASK                              0x10000000
#define TMC2160_OFS188_SHIFT                             28
#define TMC2160_OFS188_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS188_MASK, TMC2160_OFS188_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS189_MASK                              0x20000000
#define TMC2160_OFS189_SHIFT                             29
#define TMC2160_OFS189_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS189_MASK, TMC2160_OFS189_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS190_MASK                              0x40000000
#define TMC2160_OFS190_SHIFT                             30
#define TMC2160_OFS190_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS190_MASK, TMC2160_OFS190_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS191_MASK                              0x80000000
#define TMC2160_OFS191_SHIFT                             31
#define TMC2160_OFS191_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS191_MASK, TMC2160_OFS191_SHIFT, TMC2160_MSLUT[5], false})
#define TMC2160_OFS192_MASK                              0x00000001
#define TMC2160_OFS192_SHIFT                             0
#define TMC2160_OFS192_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS192_MASK, TMC2160_OFS192_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS193_MASK                              0x00000002
#define TMC2160_OFS193_SHIFT                             1
#define TMC2160_OFS193_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS193_MASK, TMC2160_OFS193_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS194_MASK                              0x00000004
#define TMC2160_OFS194_SHIFT                             2
#define TMC2160_OFS194_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS194_MASK, TMC2160_OFS194_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS195_MASK                              0x00000008
#define TMC2160_OFS195_SHIFT                             3
#define TMC2160_OFS195_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS195_MASK, TMC2160_OFS195_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS196_MASK                              0x00000010
#define TMC2160_OFS196_SHIFT                             4
#define TMC2160_OFS196_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS196_MASK, TMC2160_OFS196_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS197_MASK                              0x00000020
#define TMC2160_OFS197_SHIFT                             5
#define TMC2160_OFS197_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS197_MASK, TMC2160_OFS197_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS198_MASK                              0x00000040
#define TMC2160_OFS198_SHIFT                             6
#define TMC2160_OFS198_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS198_MASK, TMC2160_OFS198_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS199_MASK                              0x00000080
#define TMC2160_OFS199_SHIFT                             7
#define TMC2160_OFS199_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS199_MASK, TMC2160_OFS199_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS200_MASK                              0x00000100
#define TMC2160_OFS200_SHIFT                             8
#define TMC2160_OFS200_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS200_MASK, TMC2160_OFS200_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS201_MASK                              0x00000200
#define TMC2160_OFS201_SHIFT                             9
#define TMC2160_OFS201_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS201_MASK, TMC2160_OFS201_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS202_MASK                              0x00000400
#define TMC2160_OFS202_SHIFT                             10
#define TMC2160_OFS202_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS202_MASK, TMC2160_OFS202_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS203_MASK                              0x00000800
#define TMC2160_OFS203_SHIFT                             11
#define TMC2160_OFS203_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS203_MASK, TMC2160_OFS203_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS204_MASK                              0x00001000
#define TMC2160_OFS204_SHIFT                             12
#define TMC2160_OFS204_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS204_MASK, TMC2160_OFS204_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS205_MASK                              0x00002000
#define TMC2160_OFS205_SHIFT                             13
#define TMC2160_OFS205_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS205_MASK, TMC2160_OFS205_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS206_MASK                              0x00004000
#define TMC2160_OFS206_SHIFT                             14
#define TMC2160_OFS206_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS206_MASK, TMC2160_OFS206_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS207_MASK                              0x00008000
#define TMC2160_OFS207_SHIFT                             15
#define TMC2160_OFS207_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS207_MASK, TMC2160_OFS207_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS208_MASK                              0x00010000
#define TMC2160_OFS208_SHIFT                             16
#define TMC2160_OFS208_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS208_MASK, TMC2160_OFS208_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS209_MASK                              0x00020000
#define TMC2160_OFS209_SHIFT                             17
#define TMC2160_OFS209_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS209_MASK, TMC2160_OFS209_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS210_MASK                              0x00040000
#define TMC2160_OFS210_SHIFT                             18
#define TMC2160_OFS210_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS210_MASK, TMC2160_OFS210_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS211_MASK                              0x00080000
#define TMC2160_OFS211_SHIFT                             19
#define TMC2160_OFS211_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS211_MASK, TMC2160_OFS211_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS212_MASK                              0x00100000
#define TMC2160_OFS212_SHIFT                             20
#define TMC2160_OFS212_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS212_MASK, TMC2160_OFS212_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS213_MASK                              0x00200000
#define TMC2160_OFS213_SHIFT                             21
#define TMC2160_OFS213_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS213_MASK, TMC2160_OFS213_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS214_MASK                              0x00400000
#define TMC2160_OFS214_SHIFT                             22
#define TMC2160_OFS214_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS214_MASK, TMC2160_OFS214_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS215_MASK                              0x00800000
#define TMC2160_OFS215_SHIFT                             23
#define TMC2160_OFS215_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS215_MASK, TMC2160_OFS215_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS216_MASK                              0x01000000
#define TMC2160_OFS216_SHIFT                             24
#define TMC2160_OFS216_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS216_MASK, TMC2160_OFS216_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS217_MASK                              0x02000000
#define TMC2160_OFS217_SHIFT                             25
#define TMC2160_OFS217_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS217_MASK, TMC2160_OFS217_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS218_MASK                              0x04000000
#define TMC2160_OFS218_SHIFT                             26
#define TMC2160_OFS218_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS218_MASK, TMC2160_OFS218_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS219_MASK                              0x08000000
#define TMC2160_OFS219_SHIFT                             27
#define TMC2160_OFS219_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS219_MASK, TMC2160_OFS219_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS220_MASK                              0x10000000
#define TMC2160_OFS220_SHIFT                             28
#define TMC2160_OFS220_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS220_MASK, TMC2160_OFS220_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS221_MASK                              0x20000000
#define TMC2160_OFS221_SHIFT                             29
#define TMC2160_OFS221_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS221_MASK, TMC2160_OFS221_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS222_MASK                              0x40000000
#define TMC2160_OFS222_SHIFT                             30
#define TMC2160_OFS222_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS222_MASK, TMC2160_OFS222_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS223_MASK                              0x80000000
#define TMC2160_OFS223_SHIFT                             31
#define TMC2160_OFS223_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS223_MASK, TMC2160_OFS223_SHIFT, TMC2160_MSLUT[6], false})
#define TMC2160_OFS224_MASK                              0x00000001
#define TMC2160_OFS224_SHIFT                             0
#define TMC2160_OFS224_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS224_MASK, TMC2160_OFS224_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS225_MASK                              0x00000002
#define TMC2160_OFS225_SHIFT                             1
#define TMC2160_OFS225_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS225_MASK, TMC2160_OFS225_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS226_MASK                              0x00000004
#define TMC2160_OFS226_SHIFT                             2
#define TMC2160_OFS226_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS226_MASK, TMC2160_OFS226_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS227_MASK                              0x00000008
#define TMC2160_OFS227_SHIFT                             3
#define TMC2160_OFS227_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS227_MASK, TMC2160_OFS227_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS228_MASK                              0x00000010
#define TMC2160_OFS228_SHIFT                             4
#define TMC2160_OFS228_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS228_MASK, TMC2160_OFS228_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS229_MASK                              0x00000020
#define TMC2160_OFS229_SHIFT                             5
#define TMC2160_OFS229_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS229_MASK, TMC2160_OFS229_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS230_MASK                              0x00000040
#define TMC2160_OFS230_SHIFT                             6
#define TMC2160_OFS230_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS230_MASK, TMC2160_OFS230_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS231_MASK                              0x00000080
#define TMC2160_OFS231_SHIFT                             7
#define TMC2160_OFS231_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS231_MASK, TMC2160_OFS231_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS232_MASK                              0x00000100
#define TMC2160_OFS232_SHIFT                             8
#define TMC2160_OFS232_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS232_MASK, TMC2160_OFS232_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS233_MASK                              0x00000200
#define TMC2160_OFS233_SHIFT                             9
#define TMC2160_OFS233_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS233_MASK, TMC2160_OFS233_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS234_MASK                              0x00000400
#define TMC2160_OFS234_SHIFT                             10
#define TMC2160_OFS234_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS234_MASK, TMC2160_OFS234_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS235_MASK                              0x00000800
#define TMC2160_OFS235_SHIFT                             11
#define TMC2160_OFS235_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS235_MASK, TMC2160_OFS235_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS236_MASK                              0x00001000
#define TMC2160_OFS236_SHIFT                             12
#define TMC2160_OFS236_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS236_MASK, TMC2160_OFS236_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS237_MASK                              0x00002000
#define TMC2160_OFS237_SHIFT                             13
#define TMC2160_OFS237_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS237_MASK, TMC2160_OFS237_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS238_MASK                              0x00004000
#define TMC2160_OFS238_SHIFT                             14
#define TMC2160_OFS238_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS238_MASK, TMC2160_OFS238_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS239_MASK                              0x00008000
#define TMC2160_OFS239_SHIFT                             15
#define TMC2160_OFS239_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS239_MASK, TMC2160_OFS239_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS240_MASK                              0x00010000
#define TMC2160_OFS240_SHIFT                             16
#define TMC2160_OFS240_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS240_MASK, TMC2160_OFS240_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS241_MASK                              0x00020000
#define TMC2160_OFS241_SHIFT                             17
#define TMC2160_OFS241_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS241_MASK, TMC2160_OFS241_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS242_MASK                              0x00040000
#define TMC2160_OFS242_SHIFT                             18
#define TMC2160_OFS242_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS242_MASK, TMC2160_OFS242_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS243_MASK                              0x00080000
#define TMC2160_OFS243_SHIFT                             19
#define TMC2160_OFS243_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS243_MASK, TMC2160_OFS243_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS244_MASK                              0x00100000
#define TMC2160_OFS244_SHIFT                             20
#define TMC2160_OFS244_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS244_MASK, TMC2160_OFS244_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS245_MASK                              0x00200000
#define TMC2160_OFS245_SHIFT                             21
#define TMC2160_OFS245_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS245_MASK, TMC2160_OFS245_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS246_MASK                              0x00400000
#define TMC2160_OFS246_SHIFT                             22
#define TMC2160_OFS246_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS246_MASK, TMC2160_OFS246_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS247_MASK                              0x00800000
#define TMC2160_OFS247_SHIFT                             23
#define TMC2160_OFS247_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS247_MASK, TMC2160_OFS247_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS248_MASK                              0x01000000
#define TMC2160_OFS248_SHIFT                             24
#define TMC2160_OFS248_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS248_MASK, TMC2160_OFS248_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS249_MASK                              0x02000000
#define TMC2160_OFS249_SHIFT                             25
#define TMC2160_OFS249_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS249_MASK, TMC2160_OFS249_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS250_MASK                              0x04000000
#define TMC2160_OFS250_SHIFT                             26
#define TMC2160_OFS250_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS250_MASK, TMC2160_OFS250_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS251_MASK                              0x08000000
#define TMC2160_OFS251_SHIFT                             27
#define TMC2160_OFS251_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS251_MASK, TMC2160_OFS251_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS252_MASK                              0x10000000
#define TMC2160_OFS252_SHIFT                             28
#define TMC2160_OFS252_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS252_MASK, TMC2160_OFS252_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS253_MASK                              0x20000000
#define TMC2160_OFS253_SHIFT                             29
#define TMC2160_OFS253_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS253_MASK, TMC2160_OFS253_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS254_MASK                              0x40000000
#define TMC2160_OFS254_SHIFT                             30
#define TMC2160_OFS254_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS254_MASK, TMC2160_OFS254_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_OFS255_MASK                              0x80000000
#define TMC2160_OFS255_SHIFT                             31
#define TMC2160_OFS255_FIELD                             ((TMC2160RegisterField) {TMC2160_OFS255_MASK, TMC2160_OFS255_SHIFT, TMC2160_MSLUT[7], false})
#define TMC2160_W0_MASK                                  0x00000003
#define TMC2160_W0_SHIFT                                 0
#define TMC2160_W0_FIELD                                 ((TMC2160RegisterField) {TMC2160_W0_MASK, TMC2160_W0_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_W1_MASK                                  0x0000000C
#define TMC2160_W1_SHIFT                                 2
#define TMC2160_W1_FIELD                                 ((TMC2160RegisterField) {TMC2160_W1_MASK, TMC2160_W1_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_W2_MASK                                  0x00000030
#define TMC2160_W2_SHIFT                                 4
#define TMC2160_W2_FIELD                                 ((TMC2160RegisterField) {TMC2160_W2_MASK, TMC2160_W2_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_W3_MASK                                  0x000000C0
#define TMC2160_W3_SHIFT                                 6
#define TMC2160_W3_FIELD                                 ((TMC2160RegisterField) {TMC2160_W3_MASK, TMC2160_W3_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_X1_MASK                                  0x0000FF00
#define TMC2160_X1_SHIFT                                 8
#define TMC2160_X1_FIELD                                 ((TMC2160RegisterField) {TMC2160_X1_MASK, TMC2160_X1_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_X2_MASK                                  0x00FF0000
#define TMC2160_X2_SHIFT                                 16
#define TMC2160_X2_FIELD                                 ((TMC2160RegisterField) {TMC2160_X2_MASK, TMC2160_X2_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_X3_MASK                                  0xFF000000
#define TMC2160_X3_SHIFT                                 24
#define TMC2160_X3_FIELD                                 ((TMC2160RegisterField) {TMC2160_X3_MASK, TMC2160_X3_SHIFT, TMC2160_MSLUTSEL, false})
#define TMC2160_START_SIN_MASK                           0x000000FF
#define TMC2160_START_SIN_SHIFT                          0
#define TMC2160_START_SIN_FIELD                          ((TMC2160RegisterField) {TMC2160_START_SIN_MASK, TMC2160_START_SIN_SHIFT, TMC2160_MSLUTSTART, false})
#define TMC2160_START_SIN90_MASK                         0x00FF0000
#define TMC2160_START_SIN90_SHIFT                        16
#define TMC2160_START_SIN90_FIELD                        ((TMC2160RegisterField) {TMC2160_START_SIN90_MASK, TMC2160_START_SIN90_SHIFT, TMC2160_MSLUTSTART, false})
#define TMC2160_MSCNT_MASK                               0x000003FF
#define TMC2160_MSCNT_SHIFT                              0
#define TMC2160_MSCNT_FIELD                              ((TMC2160RegisterField) {TMC2160_MSCNT_MASK, TMC2160_MSCNT_SHIFT, TMC2160_MSCNT, false})
#define TMC2160_CUR_A_MASK                               0x000001FF
#define TMC2160_CUR_A_SHIFT                              0
#define TMC2160_CUR_A_FIELD                              ((TMC2160RegisterField) {TMC2160_CUR_A_MASK, TMC2160_CUR_A_SHIFT, TMC2160_MSCURACT, true})
#define TMC2160_CUR_B_MASK                               0x01FF0000
#define TMC2160_CUR_B_SHIFT                              16
#define TMC2160_CUR_B_FIELD                              ((TMC2160RegisterField) {TMC2160_CUR_B_MASK, TMC2160_CUR_B_SHIFT, TMC2160_MSCURACT, true})
#define TMC2160_TOFF_MASK                                0x0000000F
#define TMC2160_TOFF_SHIFT                               0
#define TMC2160_TOFF_FIELD                               ((TMC2160RegisterField) {TMC2160_TOFF_MASK, TMC2160_TOFF_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_TFD_2__0__MASK                           0x00000070
#define TMC2160_TFD_2__0__SHIFT                          4
#define TMC2160_TFD_2__0__FIELD                          ((TMC2160RegisterField) {TMC2160_TFD_2__0__MASK, TMC2160_TFD_2__0__SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_OFFSET_MASK                              0x00000780
#define TMC2160_OFFSET_SHIFT                             7
#define TMC2160_OFFSET_FIELD                             ((TMC2160RegisterField) {TMC2160_OFFSET_MASK, TMC2160_OFFSET_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_TFD___MASK                               0x00000800
#define TMC2160_TFD___SHIFT                              11
#define TMC2160_TFD___FIELD                              ((TMC2160RegisterField) {TMC2160_TFD___MASK, TMC2160_TFD___SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_DISFDCC_MASK                             0x00001000
#define TMC2160_DISFDCC_SHIFT                            12
#define TMC2160_DISFDCC_FIELD                            ((TMC2160RegisterField) {TMC2160_DISFDCC_MASK, TMC2160_DISFDCC_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_CHM_MASK                                 0x00004000
#define TMC2160_CHM_SHIFT                                14
#define TMC2160_CHM_FIELD                                ((TMC2160RegisterField) {TMC2160_CHM_MASK, TMC2160_CHM_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_TBL_MASK                                 0x00018000
#define TMC2160_TBL_SHIFT                                15
#define TMC2160_TBL_FIELD                                ((TMC2160RegisterField) {TMC2160_TBL_MASK, TMC2160_TBL_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_VHIGHFS_MASK                             0x00040000
#define TMC2160_VHIGHFS_SHIFT                            18
#define TMC2160_VHIGHFS_FIELD                            ((TMC2160RegisterField) {TMC2160_VHIGHFS_MASK, TMC2160_VHIGHFS_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_VHIGHCHM_MASK                            0x00080000
#define TMC2160_VHIGHCHM_SHIFT                           19
#define TMC2160_VHIGHCHM_FIELD                           ((TMC2160RegisterField) {TMC2160_VHIGHCHM_MASK, TMC2160_VHIGHCHM_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_TPFD_MASK                                0x00F00000
#define TMC2160_TPFD_SHIFT                               20
#define TMC2160_TPFD_FIELD                               ((TMC2160RegisterField) {TMC2160_TPFD_MASK, TMC2160_TPFD_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_MRES_MASK                                0x0F000000
#define TMC2160_MRES_SHIFT                               24
#define TMC2160_MRES_FIELD                               ((TMC2160RegisterField) {TMC2160_MRES_MASK, TMC2160_MRES_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_INTPOL_MASK                              0x10000000
#define TMC2160_INTPOL_SHIFT                             28
#define TMC2160_INTPOL_FIELD                             ((TMC2160RegisterField) {TMC2160_INTPOL_MASK, TMC2160_INTPOL_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_DEDGE_MASK                               0x20000000
#define TMC2160_DEDGE_SHIFT                              29
#define TMC2160_DEDGE_FIELD                              ((TMC2160RegisterField) {TMC2160_DEDGE_MASK, TMC2160_DEDGE_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_DISS2G_MASK                              0x40000000
#define TMC2160_DISS2G_SHIFT                             30
#define TMC2160_DISS2G_FIELD                             ((TMC2160RegisterField) {TMC2160_DISS2G_MASK, TMC2160_DISS2G_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_DISS2VS_MASK                             0x80000000
#define TMC2160_DISS2VS_SHIFT                            31
#define TMC2160_DISS2VS_FIELD                            ((TMC2160RegisterField) {TMC2160_DISS2VS_MASK, TMC2160_DISS2VS_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_RNDTF_MASK                               0x00002000
#define TMC2160_RNDTF_SHIFT                              13
#define TMC2160_RNDTF_FIELD                              ((TMC2160RegisterField) {TMC2160_RNDTF_MASK, TMC2160_RNDTF_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_VSENSE_MASK                              0x00020000
#define TMC2160_VSENSE_SHIFT                             17
#define TMC2160_VSENSE_FIELD                             ((TMC2160RegisterField) {TMC2160_VSENSE_MASK, TMC2160_VSENSE_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_HSTRT_MASK                               0x00000070
#define TMC2160_HSTRT_SHIFT                              4
#define TMC2160_HSTRT_FIELD                              ((TMC2160RegisterField) {TMC2160_HSTRT_MASK, TMC2160_HSTRT_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_HEND_MASK                                0x00000780
#define TMC2160_HEND_SHIFT                               7
#define TMC2160_HEND_FIELD                               ((TMC2160RegisterField) {TMC2160_HEND_MASK, TMC2160_HEND_SHIFT, TMC2160_CHOPCONF, false})
#define TMC2160_SEMIN_MASK                               0x0000000F
#define TMC2160_SEMIN_SHIFT                              0
#define TMC2160_SEMIN_FIELD                              ((TMC2160RegisterField) {TMC2160_SEMIN_MASK, TMC2160_SEMIN_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_SEUP_MASK                                0x00000060
#define TMC2160_SEUP_SHIFT                               5
#define TMC2160_SEUP_FIELD                               ((TMC2160RegisterField) {TMC2160_SEUP_MASK, TMC2160_SEUP_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_SEMAX_MASK                               0x00000F00
#define TMC2160_SEMAX_SHIFT                              8
#define TMC2160_SEMAX_FIELD                              ((TMC2160RegisterField) {TMC2160_SEMAX_MASK, TMC2160_SEMAX_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_SEDN_MASK                                0x00006000
#define TMC2160_SEDN_SHIFT                               13
#define TMC2160_SEDN_FIELD                               ((TMC2160RegisterField) {TMC2160_SEDN_MASK, TMC2160_SEDN_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_SEIMIN_MASK                              0x00008000
#define TMC2160_SEIMIN_SHIFT                             15
#define TMC2160_SEIMIN_FIELD                             ((TMC2160RegisterField) {TMC2160_SEIMIN_MASK, TMC2160_SEIMIN_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_SGT_MASK                                 0x007F0000
#define TMC2160_SGT_SHIFT                                16
#define TMC2160_SGT_FIELD                                ((TMC2160RegisterField) {TMC2160_SGT_MASK, TMC2160_SGT_SHIFT, TMC2160_COOLCONF, true})
#define TMC2160_SFILT_MASK                               0x01000000
#define TMC2160_SFILT_SHIFT                              24
#define TMC2160_SFILT_FIELD                              ((TMC2160RegisterField) {TMC2160_SFILT_MASK, TMC2160_SFILT_SHIFT, TMC2160_COOLCONF, false})
#define TMC2160_DC_TIME_MASK                             0x000003FF
#define TMC2160_DC_TIME_SHIFT                            0
#define TMC2160_DC_TIME_FIELD                            ((TMC2160RegisterField) {TMC2160_DC_TIME_MASK, TMC2160_DC_TIME_SHIFT, TMC2160_DCCTRL, false})
#define TMC2160_DC_SG_MASK                               0x00FF0000
#define TMC2160_DC_SG_SHIFT                              16
#define TMC2160_DC_SG_FIELD                              ((TMC2160RegisterField) {TMC2160_DC_SG_MASK, TMC2160_DC_SG_SHIFT, TMC2160_DCCTRL, false})
#define TMC2160_SG_RESULT_MASK                           0x000003FF
#define TMC2160_SG_RESULT_SHIFT                          0
#define TMC2160_SG_RESULT_FIELD                          ((TMC2160RegisterField) {TMC2160_SG_RESULT_MASK, TMC2160_SG_RESULT_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_S2VSA_MASK                               0x00001000
#define TMC2160_S2VSA_SHIFT                              12
#define TMC2160_S2VSA_FIELD                              ((TMC2160RegisterField) {TMC2160_S2VSA_MASK, TMC2160_S2VSA_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_S2VSB_MASK                               0x00002000
#define TMC2160_S2VSB_SHIFT                              13
#define TMC2160_S2VSB_FIELD                              ((TMC2160RegisterField) {TMC2160_S2VSB_MASK, TMC2160_S2VSB_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_STEALTH_MASK                             0x00004000
#define TMC2160_STEALTH_SHIFT                            14
#define TMC2160_STEALTH_FIELD                            ((TMC2160RegisterField) {TMC2160_STEALTH_MASK, TMC2160_STEALTH_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_FSACTIVE_MASK                            0x00008000
#define TMC2160_FSACTIVE_SHIFT                           15
#define TMC2160_FSACTIVE_FIELD                           ((TMC2160RegisterField) {TMC2160_FSACTIVE_MASK, TMC2160_FSACTIVE_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_CS_ACTUAL_MASK                           0x001F0000
#define TMC2160_CS_ACTUAL_SHIFT                          16
#define TMC2160_CS_ACTUAL_FIELD                          ((TMC2160RegisterField) {TMC2160_CS_ACTUAL_MASK, TMC2160_CS_ACTUAL_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_STALLGUARD_MASK                          0x01000000
#define TMC2160_STALLGUARD_SHIFT                         24
#define TMC2160_STALLGUARD_FIELD                         ((TMC2160RegisterField) {TMC2160_STALLGUARD_MASK, TMC2160_STALLGUARD_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_OT_MASK                                  0x02000000
#define TMC2160_OT_SHIFT                                 25
#define TMC2160_OT_FIELD                                 ((TMC2160RegisterField) {TMC2160_OT_MASK, TMC2160_OT_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_OTPW_MASK                                0x04000000
#define TMC2160_OTPW_SHIFT                               26
#define TMC2160_OTPW_FIELD                               ((TMC2160RegisterField) {TMC2160_OTPW_MASK, TMC2160_OTPW_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_S2GA_MASK                                0x08000000
#define TMC2160_S2GA_SHIFT                               27
#define TMC2160_S2GA_FIELD                               ((TMC2160RegisterField) {TMC2160_S2GA_MASK, TMC2160_S2GA_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_S2GB_MASK                                0x10000000
#define TMC2160_S2GB_SHIFT                               28
#define TMC2160_S2GB_FIELD                               ((TMC2160RegisterField) {TMC2160_S2GB_MASK, TMC2160_S2GB_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_OLA_MASK                                 0x20000000
#define TMC2160_OLA_SHIFT                                29
#define TMC2160_OLA_FIELD                                ((TMC2160RegisterField) {TMC2160_OLA_MASK, TMC2160_OLA_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_OLB_MASK                                 0x40000000
#define TMC2160_OLB_SHIFT                                30
#define TMC2160_OLB_FIELD                                ((TMC2160RegisterField) {TMC2160_OLB_MASK, TMC2160_OLB_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_STST_MASK                                0x80000000
#define TMC2160_STST_SHIFT                               31
#define TMC2160_STST_FIELD                               ((TMC2160RegisterField) {TMC2160_STST_MASK, TMC2160_STST_SHIFT, TMC2160_DRV_STATUS, false})
#define TMC2160_PWM_OFS_MASK                             0x000000FF
#define TMC2160_PWM_OFS_SHIFT                            0
#define TMC2160_PWM_OFS_FIELD                            ((TMC2160RegisterField) {TMC2160_PWM_OFS_MASK, TMC2160_PWM_OFS_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_GRAD_MASK                            0x0000FF00
#define TMC2160_PWM_GRAD_SHIFT                           8
#define TMC2160_PWM_GRAD_FIELD                           ((TMC2160RegisterField) {TMC2160_PWM_GRAD_MASK, TMC2160_PWM_GRAD_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_FREQ_MASK                            0x00030000
#define TMC2160_PWM_FREQ_SHIFT                           16
#define TMC2160_PWM_FREQ_FIELD                           ((TMC2160RegisterField) {TMC2160_PWM_FREQ_MASK, TMC2160_PWM_FREQ_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_AUTOSCALE_MASK                       0x00040000
#define TMC2160_PWM_AUTOSCALE_SHIFT                      18
#define TMC2160_PWM_AUTOSCALE_FIELD                      ((TMC2160RegisterField) {TMC2160_PWM_AUTOSCALE_MASK, TMC2160_PWM_AUTOSCALE_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_AUTOGRAD_MASK                        0x00080000
#define TMC2160_PWM_AUTOGRAD_SHIFT                       19
#define TMC2160_PWM_AUTOGRAD_FIELD                       ((TMC2160RegisterField) {TMC2160_PWM_AUTOGRAD_MASK, TMC2160_PWM_AUTOGRAD_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_FREEWHEEL_MASK                           0x00300000
#define TMC2160_FREEWHEEL_SHIFT                          20
#define TMC2160_FREEWHEEL_FIELD                          ((TMC2160RegisterField) {TMC2160_FREEWHEEL_MASK, TMC2160_FREEWHEEL_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_REG_MASK                             0x0F000000
#define TMC2160_PWM_REG_SHIFT                            24
#define TMC2160_PWM_REG_FIELD                            ((TMC2160RegisterField) {TMC2160_PWM_REG_MASK, TMC2160_PWM_REG_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_LIM_MASK                             0xF0000000
#define TMC2160_PWM_LIM_SHIFT                            28
#define TMC2160_PWM_LIM_FIELD                            ((TMC2160RegisterField) {TMC2160_PWM_LIM_MASK, TMC2160_PWM_LIM_SHIFT, TMC2160_PWMCONF, false})
#define TMC2160_PWM_SCALE_SUM_MASK                       0x000000FF
#define TMC2160_PWM_SCALE_SUM_SHIFT                      0
#define TMC2160_PWM_SCALE_SUM_FIELD                      ((TMC2160RegisterField) {TMC2160_PWM_SCALE_SUM_MASK, TMC2160_PWM_SCALE_SUM_SHIFT, TMC2160_PWM_SCALE, false})
#define TMC2160_PWM_SCALE_AUTO_MASK                      0x01FF0000
#define TMC2160_PWM_SCALE_AUTO_SHIFT                     16
#define TMC2160_PWM_SCALE_AUTO_FIELD                     ((TMC2160RegisterField) {TMC2160_PWM_SCALE_AUTO_MASK, TMC2160_PWM_SCALE_AUTO_SHIFT, TMC2160_PWM_SCALE, true})
#define TMC2160_PWM_OFS_AUTO_MASK                        0x000000FF
#define TMC2160_PWM_OFS_AUTO_SHIFT                       0
#define TMC2160_PWM_OFS_AUTO_FIELD                       ((TMC2160RegisterField) {TMC2160_PWM_OFS_AUTO_MASK, TMC2160_PWM_OFS_AUTO_SHIFT, TMC2160_PWM_AUTO, false})
#define TMC2160_PWM_GRAD_AUTO_MASK                       0x00FF0000
#define TMC2160_PWM_GRAD_AUTO_SHIFT                      16
#define TMC2160_PWM_GRAD_AUTO_FIELD                      ((TMC2160RegisterField) {TMC2160_PWM_GRAD_AUTO_MASK, TMC2160_PWM_GRAD_AUTO_SHIFT, TMC2160_PWM_AUTO, false})
#define TMC2160_LOST_STEPS_MASK                          0x000FFFFF
#define TMC2160_LOST_STEPS_SHIFT                         0
#define TMC2160_LOST_STEPS_FIELD                         ((TMC2160RegisterField) {TMC2160_LOST_STEPS_MASK, TMC2160_LOST_STEPS_SHIFT, TMC2160_LOST_STEPS, false})

#endif
