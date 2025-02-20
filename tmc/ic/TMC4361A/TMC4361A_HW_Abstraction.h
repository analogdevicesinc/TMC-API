/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC4361A_HW_ABSTRACTION
#define TMC4361A_HW_ABSTRACTION

// Constants in TMC4361A

#define TMC4361A_REGISTER_COUNT   128
#define TMC4361A_MOTORS           1
#define TMC4361A_WRITE_BIT        0x80
#define TMC4361A_ADDRESS_MASK     0x7F
#define TMC4361A_MAX_VELOCITY     (int32_t)  2147483647
#define TMC4361A_MAX_ACCELERATION (uint32_t)  16777215uL

#define TMC4361A_COVER_DONE (1<<25)

#define TMC4361A_RAMP_HOLD      0
#define TMC4361A_RAMP_TRAPEZ    1
#define TMC4361A_RAMP_SSHAPE    2

#define TMC4361A_RAMP_POSITION  4

// Registers in TMC4361A

#define TMC4361A_GENERAL_CONF                                  0x00
#define TMC4361A_REFERENCE_CONF                                0x01
#define TMC4361A_START_CONF                                    0x02
#define TMC4361A_INPUT_FILT_CONF                               0x03
#define TMC4361A_SPI_OUT_CONF                                  0x04
#define TMC4361A_CURRENT_CONF                                  0x05
#define TMC4361A_SCALE_VALUES                                  0x06
#define TMC4361A_ENC_IN_CONF                                   0x07
#define TMC4361A_ENC_IN_DATA                                   0x08
#define TMC4361A_ENC_OUT_DATA                                  0x09
#define TMC4361A_STEP_CONF                                     0x0A
#define TMC4361A_SPI_STATUS_SELECTION                          0x0B
#define TMC4361A_EVENT_CLEAR_CONF                              0x0C
#define TMC4361A_INTR_CONF                                     0x0D
#define TMC4361A_EVENTS                                        0x0E
#define TMC4361A_STATUS                                        0x0F
#define TMC4361A_STP_LENGTH_ADD                                0x10
#define TMC4361A_DIR_SETUP_TIME                                0x10
#define TMC4361A_START_OUT_ADD                                 0x11
#define TMC4361A_GEAR_RATIO                                    0x12
#define TMC4361A_START_DELAY                                   0x13
#define TMC4361A_CLK_GATING_DELAY                              0x14
#define TMC4361A_STDBY_DELAY                                   0x15
#define TMC4361A_FREEWHEEL_DELAY                               0x16
#define TMC4361A_VDRV_SCALE_LIMIT                              0x17
#define TMC4361A_PWM_VMAX                                      0x17
#define TMC4361A_UP_SCALE_DELAY                                0x18
#define TMC4361A_CL_UPSCALE_DELAY                              0x18
#define TMC4361A_HOLD_SCALE_DELAY                              0x19
#define TMC4361A_CL_DNSCALE_DELAY                              0x19
#define TMC4361A_DRV_SCALE_DELAY                               0x1A
#define TMC4361A_BOOST_TIME                                    0x1B
#define TMC4361A_CL_ANGLES                                     0x1C
#define TMC4361A_SPI_SWITCH_VEL                                0x1D
#define TMC4361A_DAC_ADDR                                      0x1D
#define TMC4361A_HOME_SAFETY_MARGIN                            0x1E
#define TMC4361A_PWM_FREQ                                      0x1F
#define TMC4361A_CHOPSYNC_DIV                                  0x1F
#define TMC4361A_RAMPMODE                                      0x20
#define TMC4361A_XACTUAL                                       0x21
#define TMC4361A_VACTUAL                                       0x22
#define TMC4361A_AACTUAL                                       0x23
#define TMC4361A_VMAX                                          0x24
#define TMC4361A_VSTART                                        0x25
#define TMC4361A_VSTOP                                         0x26
#define TMC4361A_VBREAK                                        0x27
#define TMC4361A_AMAX                                          0x28
#define TMC4361A_DMAX                                          0x29
#define TMC4361A_ASTART                                        0x2A
#define TMC4361A_DFINAL                                        0x2B
#define TMC4361A_DSTOP                                         0x2C
#define TMC4361A_BOW1                                          0x2D
#define TMC4361A_BOW2                                          0x2E
#define TMC4361A_BOW3                                          0x2F
#define TMC4361A_BOW4                                          0x30
#define TMC4361A_CLK_FREQ                                      0x31
#define TMC4361A_POS_COMP                                      0x32
#define TMC4361A_VIRT_STOP_LEFT                                0x33
#define TMC4361A_VIRT_STOP_RIGHT                               0x34
#define TMC4361A_X_HOME                                        0x35
#define TMC4361A_X_LATCH                                       0x36
#define TMC4361A_REV_CNT                                       0x36
#define TMC4361A_X_RANGE                                       0x36
#define TMC4361A_XTARGET                                       0x37
#define TMC4361A_X_PIPE0                                       0x38
#define TMC4361A_X_PIPE1                                       0x39
#define TMC4361A_X_PIPE2                                       0x3A
#define TMC4361A_X_PIPE3                                       0x3B
#define TMC4361A_X_PIPE4                                       0x3C
#define TMC4361A_X_PIPE5                                       0x3D
#define TMC4361A_X_PIPE6                                       0x3E
#define TMC4361A_X_PIPE7                                       0x3F
#define TMC4361A_SH_REG0                                       0x40
#define TMC4361A_SH_REG1                                       0x41
#define TMC4361A_SH_REG2                                       0x42
#define TMC4361A_SH_REG3                                       0x43
#define TMC4361A_SH_REG4                                       0x44
#define TMC4361A_SH_REG5                                       0x45
#define TMC4361A_SH_REG6                                       0x46
#define TMC4361A_SH_REG7                                       0x47
#define TMC4361A_SH_REG8                                       0x48
#define TMC4361A_SH_REG9                                       0x49
#define TMC4361A_SH_REG10                                      0x4A
#define TMC4361A_SH_REG11                                      0x4B
#define TMC4361A_SH_REG12                                      0x4C
#define TMC4361A_SH_REG13                                      0x4D
#define TMC4361A_FREEZE_REGISTERS                              0x4E
#define TMC4361A_CLK_GATING                                    0x4F
#define TMC4361A_SW_RESET                                      0x4F
#define TMC4361A_ENC_POS                                       0x50
#define TMC4361A_ENC_LATCH                                     0x51
#define TMC4361A_ENC_RESET_VAL                                 0x51
#define TMC4361A_ENC_POS_DEV                                   0x52
#define TMC4361A_CL_TR_TOLERANCE                               0x52
#define TMC4361A_ENC_POS_DEV_TOL                               0x53
#define TMC4361A_ENC_IN_RES                                    0x54
#define TMC4361A_ENC_CONST                                     0x54
#define TMC4361A_ENC_OUT_RES                                   0x55
#define TMC4361A_SER_CLK_IN_HIGH_LOW                           0x56
#define TMC4361A_SSI_IN_CLK_DELAY                              0x57
#define TMC4361A_SSI_IN_WTIME                                  0x57
#define TMC4361A_SER_PTIME                                     0x58
#define TMC4361A_CL_OFFSET                                     0x59
#define TMC4361A_PID_VEL                                       0x5A
#define TMC4361A_PID_P                                         0x5A
#define TMC4361A_CL_VMAX_CALC_P                                0x5A
#define TMC4361A_PID_ISUM_RD                                   0x5B
#define TMC4361A_PID_I                                         0x5B
#define TMC4361A_CL_VMAX_CALC_I                                0x5B
#define TMC4361A_PID_D                                         0x5C
#define TMC4361A_CL_DELTA_P                                    0x5C
#define TMC4361A_PID_E                                         0x5D
#define TMC4361A_PID_I_CLIP                                     0x5D
#define TMC4361A_PID_D_CLKDIV                                  0x5D
#define TMC4361A_PID_DV_CLIP                                   0x5E
#define TMC4361A_PID_TOLERANCE                                 0x5F
#define TMC4361A_CL_TOLERANCE                                  0x5F
#define TMC4361A_FS_VEL                                        0x60
#define TMC4361A_DC_VEL                                        0x60
#define TMC4361A_CL_VMIN_EMF                                   0x60
#define TMC4361A_DC_TIME                                       0x61
#define TMC4361A_DC_SG                                         0x61
#define TMC4361A_DC_BLKTIME                                    0x61
#define TMC4361A_CL_VADD_EMF                                   0x61
#define TMC4361A_DC_LSPTM                                      0x62
#define TMC4361A_ENC_VEL_ZERO                                  0x62
#define TMC4361A_ENC_VMEAN_WAIT                                0x63
#define TMC4361A_ENC_VMEAN_FILTER                              0x63
#define TMC4361A_ENC_VMEAN_INT                                 0x63
#define TMC4361A_ENC_SER_ENC_VARIATION                         0x63
#define TMC4361A_CL_CYCLE                                      0x63
#define TMC4361A_V_ENC                                         0x65
#define TMC4361A_V_ENC_MEAN                                    0x66
#define TMC4361A_VSTALL_LIMIT                                  0x67
#define TMC4361A_ADDR_TO_ENC                                   0x68
#define TMC4361A_DATA_TO_ENC                                   0x69
#define TMC4361A_ADDR_FROM_ENC                                 0x6A
#define TMC4361A_DATA_FROM_ENC                                 0x6B
#define TMC4361A_COVER_LOW                                     0x6C
#define TMC4361A_POLLING_STATUS                                0x6C
#define TMC4361A_COVER_HIGH                                    0x6D
#define TMC4361A_POLLING_REG                                   0x6D
#define TMC4361A_COVER_DRV_LOW                                 0x6E
#define TMC4361A_COVER_DRV_HIGH                                0x6F
#define TMC4361A_MSLUT_0                                       0x70
#define TMC4361A_MSLUT_1                                       0x71
#define TMC4361A_MSLUT_2                                       0x72
#define TMC4361A_MSLUT_3                                       0x73
#define TMC4361A_MSLUT_4                                       0x74
#define TMC4361A_MSLUT_5                                       0x75
#define TMC4361A_MSLUT_6                                       0x76
#define TMC4361A_MSLUT_7                                       0x77
#define TMC4361A_MSLUTSEL                                      0x78
#define TMC4361A_MSCNT                                         0x79
#define TMC4361A_MSOFFSET                                      0x79
#define TMC4361A_CURRENTA                                      0x7A
#define TMC4361A_CURRENTB                                      0x7A
#define TMC4361A_CURRENTA_SPI                                  0x7B
#define TMC4361A_CURRENTB_SPI                                  0x7B
#define TMC4361A_TZEROWAIT                                     0x7B
#define TMC4361A_SCALE_PARAM                                   0x7C
#define TMC4361A_CIRCULAR_DEC                                  0x7C
#define TMC4361A_ENC_COMP_XOFFSET                              0x7D
#define TMC4361A_ENC_COMP_YOFFSET                              0x7D
#define TMC4361A_ENC_COMP_AMPL                                 0x7D
#define TMC4361A_START_SIN                                     0x7E
#define TMC4361A_START_SIN90_120                               0x7E
#define TMC4361A_DAC_OFFSET                                    0x7E
#define TMC4361A_VERSION_NO                                    0x7F


// Fields in TMC4361A

#define TMC4361A_USE_ASTART_AND_VSTART_MASK                0x00000001
#define TMC4361A_USE_ASTART_AND_VSTART_SHIFT               0
#define TMC4361A_USE_ASTART_AND_VSTART_FIELD               ((RegisterField) {TMC4361A_USE_ASTART_AND_VSTART_MASK, TMC4361A_USE_ASTART_AND_VSTART_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_DIRECT_ACC_VAL_EN_MASK                    0x00000002
#define TMC4361A_DIRECT_ACC_VAL_EN_SHIFT                   1
#define TMC4361A_DIRECT_ACC_VAL_EN_FIELD                   ((RegisterField) {TMC4361A_DIRECT_ACC_VAL_EN_MASK, TMC4361A_DIRECT_ACC_VAL_EN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_DIRECT_BOW_VAL_EN_MASK                    0x00000004
#define TMC4361A_DIRECT_BOW_VAL_EN_SHIFT                   2
#define TMC4361A_DIRECT_BOW_VAL_EN_FIELD                   ((RegisterField) {TMC4361A_DIRECT_BOW_VAL_EN_MASK, TMC4361A_DIRECT_BOW_VAL_EN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_STEP_INACTIVE_POL_MASK                    0x00000008
#define TMC4361A_STEP_INACTIVE_POL_SHIFT                   3
#define TMC4361A_STEP_INACTIVE_POL_FIELD                   ((RegisterField) {TMC4361A_STEP_INACTIVE_POL_MASK, TMC4361A_STEP_INACTIVE_POL_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_TOGGLE_STEP_MASK                          0x00000010
#define TMC4361A_TOGGLE_STEP_SHIFT                         4
#define TMC4361A_TOGGLE_STEP_FIELD                         ((RegisterField) {TMC4361A_TOGGLE_STEP_MASK, TMC4361A_TOGGLE_STEP_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_POL_DIR_OUT_MASK                          0x00000020
#define TMC4361A_POL_DIR_OUT_SHIFT                         5
#define TMC4361A_POL_DIR_OUT_FIELD                         ((RegisterField) {TMC4361A_POL_DIR_OUT_MASK, TMC4361A_POL_DIR_OUT_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_SDIN_MODE_MASK                            0x000000c0
#define TMC4361A_SDIN_MODE_SHIFT                           6
#define TMC4361A_SDIN_MODE_FIELD                           ((RegisterField) {TMC4361A_SDIN_MODE_MASK, TMC4361A_SDIN_MODE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_POL_DIR_IN_MASK                           0x00000100
#define TMC4361A_POL_DIR_IN_SHIFT                          8
#define TMC4361A_POL_DIR_IN_FIELD                          ((RegisterField) {TMC4361A_POL_DIR_IN_MASK, TMC4361A_POL_DIR_IN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_SD_INDIRECT_CONTROL_MASK                  0x00000200
#define TMC4361A_SD_INDIRECT_CONTROL_SHIFT                 9
#define TMC4361A_SD_INDIRECT_CONTROL_FIELD                 ((RegisterField) {TMC4361A_SD_INDIRECT_CONTROL_MASK, TMC4361A_SD_INDIRECT_CONTROL_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_SERIAL_ENC_IN_MODE_MASK                   0x00000c00
#define TMC4361A_SERIAL_ENC_IN_MODE_SHIFT                  10
#define TMC4361A_SERIAL_ENC_IN_MODE_FIELD                  ((RegisterField) {TMC4361A_SERIAL_ENC_IN_MODE_MASK, TMC4361A_SERIAL_ENC_IN_MODE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_DIFF_ENC_IN_DISABLE_MASK                  0x00001000
#define TMC4361A_DIFF_ENC_IN_DISABLE_SHIFT                 12
#define TMC4361A_DIFF_ENC_IN_DISABLE_FIELD                 ((RegisterField) {TMC4361A_DIFF_ENC_IN_DISABLE_MASK, TMC4361A_DIFF_ENC_IN_DISABLE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_STDBY_CLK_PIN_ASSIGNMENT_MASK             0x00006000
#define TMC4361A_STDBY_CLK_PIN_ASSIGNMENT_SHIFT            13
#define TMC4361A_STDBY_CLK_PIN_ASSIGNMENT_FIELD            ((RegisterField) {TMC4361A_STDBY_CLK_PIN_ASSIGNMENT_MASK, TMC4361A_STDBY_CLK_PIN_ASSIGNMENT_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_INTR_POL_MASK                             0x00008000
#define TMC4361A_INTR_POL_SHIFT                            15
#define TMC4361A_INTR_POL_FIELD                            ((RegisterField) {TMC4361A_INTR_POL_MASK, TMC4361A_INTR_POL_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_INVERT_POL_TARGET_REACHED_MASK            0x00010000
#define TMC4361A_INVERT_POL_TARGET_REACHED_SHIFT           16
#define TMC4361A_INVERT_POL_TARGET_REACHED_FIELD           ((RegisterField) {TMC4361A_INVERT_POL_TARGET_REACHED_MASK, TMC4361A_INVERT_POL_TARGET_REACHED_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_FS_EN_MASK                                0x00080000
#define TMC4361A_FS_EN_SHIFT                               19
#define TMC4361A_FS_EN_FIELD                               ((RegisterField) {TMC4361A_FS_EN_MASK, TMC4361A_FS_EN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_FS_SDOUT_MASK                             0x00100000
#define TMC4361A_FS_SDOUT_SHIFT                            20
#define TMC4361A_FS_SDOUT_FIELD                            ((RegisterField) {TMC4361A_FS_SDOUT_MASK, TMC4361A_FS_SDOUT_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_DCSTEP_MODE_MASK                          0x00600000
#define TMC4361A_DCSTEP_MODE_SHIFT                         21
#define TMC4361A_DCSTEP_MODE_FIELD                         ((RegisterField) {TMC4361A_DCSTEP_MODE_MASK, TMC4361A_DCSTEP_MODE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_PWM_OUT_EN_MASK                           0x00800000
#define TMC4361A_PWM_OUT_EN_SHIFT                          23
#define TMC4361A_PWM_OUT_EN_FIELD                          ((RegisterField) {TMC4361A_PWM_OUT_EN_MASK, TMC4361A_PWM_OUT_EN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_SERIAL_ENC_OUT_ENABLE_MASK                0x01000000
#define TMC4361A_SERIAL_ENC_OUT_ENABLE_SHIFT               24
#define TMC4361A_SERIAL_ENC_OUT_ENABLE_FIELD               ((RegisterField) {TMC4361A_SERIAL_ENC_OUT_ENABLE_MASK, TMC4361A_SERIAL_ENC_OUT_ENABLE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_SERIAL_ENC_OUT_DIFF_DISABLE_MASK          0x02000000
#define TMC4361A_SERIAL_ENC_OUT_DIFF_DISABLE_SHIFT         25
#define TMC4361A_SERIAL_ENC_OUT_DIFF_DISABLE_FIELD         ((RegisterField) {TMC4361A_SERIAL_ENC_OUT_DIFF_DISABLE_MASK, TMC4361A_SERIAL_ENC_OUT_DIFF_DISABLE_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_AUTOMATIC_DIRECT_SDIN_SWITCH_OFF_MASK     0x04000000
#define TMC4361A_AUTOMATIC_DIRECT_SDIN_SWITCH_OFF_SHIFT    26
#define TMC4361A_AUTOMATIC_DIRECT_SDIN_SWITCH_OFF_FIELD    ((RegisterField) {TMC4361A_AUTOMATIC_DIRECT_SDIN_SWITCH_OFF_MASK, TMC4361A_AUTOMATIC_DIRECT_SDIN_SWITCH_OFF_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_CIRCULAR_CNT_AS_XLATCH_MASK               0x08000000
#define TMC4361A_CIRCULAR_CNT_AS_XLATCH_SHIFT              27
#define TMC4361A_CIRCULAR_CNT_AS_XLATCH_FIELD              ((RegisterField) {TMC4361A_CIRCULAR_CNT_AS_XLATCH_MASK, TMC4361A_CIRCULAR_CNT_AS_XLATCH_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_REVERSE_MOTOR_DIR_MASK                    0x10000000
#define TMC4361A_REVERSE_MOTOR_DIR_SHIFT                   28
#define TMC4361A_REVERSE_MOTOR_DIR_FIELD                   ((RegisterField) {TMC4361A_REVERSE_MOTOR_DIR_MASK, TMC4361A_REVERSE_MOTOR_DIR_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_INTR_TR_PU_PD_EN_MASK                     0x20000000
#define TMC4361A_INTR_TR_PU_PD_EN_SHIFT                    29
#define TMC4361A_INTR_TR_PU_PD_EN_FIELD                    ((RegisterField) {TMC4361A_INTR_TR_PU_PD_EN_MASK, TMC4361A_INTR_TR_PU_PD_EN_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_INTR_AS_WIRED_AND_MASK                    0x40000000
#define TMC4361A_INTR_AS_WIRED_AND_SHIFT                   30
#define TMC4361A_INTR_AS_WIRED_AND_FIELD                   ((RegisterField) {TMC4361A_INTR_AS_WIRED_AND_MASK, TMC4361A_INTR_AS_WIRED_AND_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_TR_AS_WIRED_AND_MASK                      0x80000000
#define TMC4361A_TR_AS_WIRED_AND_SHIFT                     31
#define TMC4361A_TR_AS_WIRED_AND_FIELD                     ((RegisterField) {TMC4361A_TR_AS_WIRED_AND_MASK, TMC4361A_TR_AS_WIRED_AND_SHIFT, TMC4361A_GENERAL_CONF, false})
#define TMC4361A_STOP_LEFT_EN_MASK                         0x00000001
#define TMC4361A_STOP_LEFT_EN_SHIFT                        0
#define TMC4361A_STOP_LEFT_EN_FIELD                        ((RegisterField) {TMC4361A_STOP_LEFT_EN_MASK, TMC4361A_STOP_LEFT_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_STOP_RIGHT_EN_MASK                        0x00000002
#define TMC4361A_STOP_RIGHT_EN_SHIFT                       1
#define TMC4361A_STOP_RIGHT_EN_FIELD                       ((RegisterField) {TMC4361A_STOP_RIGHT_EN_MASK, TMC4361A_STOP_RIGHT_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_POL_STOP_LEFT_MASK                        0x00000004
#define TMC4361A_POL_STOP_LEFT_SHIFT                       2
#define TMC4361A_POL_STOP_LEFT_FIELD                       ((RegisterField) {TMC4361A_POL_STOP_LEFT_MASK, TMC4361A_POL_STOP_LEFT_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_POL_STOP_RIGHT_MASK                       0x00000008
#define TMC4361A_POL_STOP_RIGHT_SHIFT                      3
#define TMC4361A_POL_STOP_RIGHT_FIELD                      ((RegisterField) {TMC4361A_POL_STOP_RIGHT_MASK, TMC4361A_POL_STOP_RIGHT_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_INVERT_STOP_DIRECTION_MASK                0x00000010
#define TMC4361A_INVERT_STOP_DIRECTION_SHIFT               4
#define TMC4361A_INVERT_STOP_DIRECTION_FIELD               ((RegisterField) {TMC4361A_INVERT_STOP_DIRECTION_MASK, TMC4361A_INVERT_STOP_DIRECTION_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_SOFT_STOP_EN_MASK                         0x00000020
#define TMC4361A_SOFT_STOP_EN_SHIFT                        5
#define TMC4361A_SOFT_STOP_EN_FIELD                        ((RegisterField) {TMC4361A_SOFT_STOP_EN_MASK, TMC4361A_SOFT_STOP_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_VIRTUAL_LEFT_LIMIT_EN_MASK                0x00000040
#define TMC4361A_VIRTUAL_LEFT_LIMIT_EN_SHIFT               6
#define TMC4361A_VIRTUAL_LEFT_LIMIT_EN_FIELD               ((RegisterField) {TMC4361A_VIRTUAL_LEFT_LIMIT_EN_MASK, TMC4361A_VIRTUAL_LEFT_LIMIT_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_VIRTUAL_RIGHT_LIMIT_EN_MASK               0x00000080
#define TMC4361A_VIRTUAL_RIGHT_LIMIT_EN_SHIFT              7
#define TMC4361A_VIRTUAL_RIGHT_LIMIT_EN_FIELD              ((RegisterField) {TMC4361A_VIRTUAL_RIGHT_LIMIT_EN_MASK, TMC4361A_VIRTUAL_RIGHT_LIMIT_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_VIRT_STOP_MODE_MASK                       0x00000300
#define TMC4361A_VIRT_STOP_MODE_SHIFT                      8
#define TMC4361A_VIRT_STOP_MODE_FIELD                      ((RegisterField) {TMC4361A_VIRT_STOP_MODE_MASK, TMC4361A_VIRT_STOP_MODE_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_LATCH_X_ON_INACTIVE_L_MASK                0x00000400
#define TMC4361A_LATCH_X_ON_INACTIVE_L_SHIFT               10
#define TMC4361A_LATCH_X_ON_INACTIVE_L_FIELD               ((RegisterField) {TMC4361A_LATCH_X_ON_INACTIVE_L_MASK, TMC4361A_LATCH_X_ON_INACTIVE_L_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_LATCH_X_ON_ACTIVE_L_MASK                  0x00000800
#define TMC4361A_LATCH_X_ON_ACTIVE_L_SHIFT                 11
#define TMC4361A_LATCH_X_ON_ACTIVE_L_FIELD                 ((RegisterField) {TMC4361A_LATCH_X_ON_ACTIVE_L_MASK, TMC4361A_LATCH_X_ON_ACTIVE_L_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_LATCH_X_ON_INACTIVE_R_MASK                0x00001000
#define TMC4361A_LATCH_X_ON_INACTIVE_R_SHIFT               12
#define TMC4361A_LATCH_X_ON_INACTIVE_R_FIELD               ((RegisterField) {TMC4361A_LATCH_X_ON_INACTIVE_R_MASK, TMC4361A_LATCH_X_ON_INACTIVE_R_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_LATCH_X_ON_ACTIVE_R_MASK                  0x00002000
#define TMC4361A_LATCH_X_ON_ACTIVE_R_SHIFT                 13
#define TMC4361A_LATCH_X_ON_ACTIVE_R_FIELD                 ((RegisterField) {TMC4361A_LATCH_X_ON_ACTIVE_R_MASK, TMC4361A_LATCH_X_ON_ACTIVE_R_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_STOP_LEFT_IS_HOME_MASK                    0x00004000
#define TMC4361A_STOP_LEFT_IS_HOME_SHIFT                   14
#define TMC4361A_STOP_LEFT_IS_HOME_FIELD                   ((RegisterField) {TMC4361A_STOP_LEFT_IS_HOME_MASK, TMC4361A_STOP_LEFT_IS_HOME_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_HOME_EVENT_MASK                           0x000f0000
#define TMC4361A_HOME_EVENT_SHIFT                          16
#define TMC4361A_HOME_EVENT_FIELD                          ((RegisterField) {TMC4361A_HOME_EVENT_MASK, TMC4361A_HOME_EVENT_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_START_HOME_TRACKING_MASK                  0x00100000
#define TMC4361A_START_HOME_TRACKING_SHIFT                 20
#define TMC4361A_START_HOME_TRACKING_FIELD                 ((RegisterField) {TMC4361A_START_HOME_TRACKING_MASK, TMC4361A_START_HOME_TRACKING_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_CLR_POS_AT_TARGET_MASK                    0x00200000
#define TMC4361A_CLR_POS_AT_TARGET_SHIFT                   21
#define TMC4361A_CLR_POS_AT_TARGET_FIELD                   ((RegisterField) {TMC4361A_CLR_POS_AT_TARGET_MASK, TMC4361A_CLR_POS_AT_TARGET_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_CIRCULAR_MOVEMENT_EN_MASK                 0x00400000
#define TMC4361A_CIRCULAR_MOVEMENT_EN_SHIFT                22
#define TMC4361A_CIRCULAR_MOVEMENT_EN_FIELD                ((RegisterField) {TMC4361A_CIRCULAR_MOVEMENT_EN_MASK, TMC4361A_CIRCULAR_MOVEMENT_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_POS_COMP_OUTPUT_MASK                      0x01800000
#define TMC4361A_POS_COMP_OUTPUT_SHIFT                     23
#define TMC4361A_POS_COMP_OUTPUT_FIELD                     ((RegisterField) {TMC4361A_POS_COMP_OUTPUT_MASK, TMC4361A_POS_COMP_OUTPUT_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_POS_COMP_SOURCE_MASK                      0x02000000
#define TMC4361A_POS_COMP_SOURCE_SHIFT                     25
#define TMC4361A_POS_COMP_SOURCE_FIELD                     ((RegisterField) {TMC4361A_POS_COMP_SOURCE_MASK, TMC4361A_POS_COMP_SOURCE_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_STOP_ON_STALL_MASK                        0x04000000
#define TMC4361A_STOP_ON_STALL_SHIFT                       26
#define TMC4361A_STOP_ON_STALL_FIELD                       ((RegisterField) {TMC4361A_STOP_ON_STALL_MASK, TMC4361A_STOP_ON_STALL_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_DRV_AFTER_STALL_MASK                      0x08000000
#define TMC4361A_DRV_AFTER_STALL_SHIFT                     27
#define TMC4361A_DRV_AFTER_STALL_FIELD                     ((RegisterField) {TMC4361A_DRV_AFTER_STALL_MASK, TMC4361A_DRV_AFTER_STALL_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_MODIFIED_POS_COPARE_MASK                  0x30000000
#define TMC4361A_MODIFIED_POS_COPARE_SHIFT                 28
#define TMC4361A_MODIFIED_POS_COPARE_FIELD                 ((RegisterField) {TMC4361A_MODIFIED_POS_COPARE_MASK, TMC4361A_MODIFIED_POS_COPARE_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_AUTOMATIC_COVER_MASK                      0x40000000
#define TMC4361A_AUTOMATIC_COVER_SHIFT                     30
#define TMC4361A_AUTOMATIC_COVER_FIELD                     ((RegisterField) {TMC4361A_AUTOMATIC_COVER_MASK, TMC4361A_AUTOMATIC_COVER_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_CIRCULAR_ENC_EN_MASK                      0x80000000
#define TMC4361A_CIRCULAR_ENC_EN_SHIFT                     31
#define TMC4361A_CIRCULAR_ENC_EN_FIELD                     ((RegisterField) {TMC4361A_CIRCULAR_ENC_EN_MASK, TMC4361A_CIRCULAR_ENC_EN_SHIFT, TMC4361A_REFERENCE_CONF, false})
#define TMC4361A_START_EN_0__MASK                          0x00000001
#define TMC4361A_START_EN_0__SHIFT                         0
#define TMC4361A_START_EN_0__FIELD                         ((RegisterField) {TMC4361A_START_EN_0__MASK, TMC4361A_START_EN_0__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_START_EN_1__MASK                          0x00000002
#define TMC4361A_START_EN_1__SHIFT                         1
#define TMC4361A_START_EN_1__FIELD                         ((RegisterField) {TMC4361A_START_EN_1__MASK, TMC4361A_START_EN_1__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_START_EN_2__MASK                          0x00000004
#define TMC4361A_START_EN_2__SHIFT                         2
#define TMC4361A_START_EN_2__FIELD                         ((RegisterField) {TMC4361A_START_EN_2__MASK, TMC4361A_START_EN_2__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_START_EN_3__MASK                          0x00000008
#define TMC4361A_START_EN_3__SHIFT                         3
#define TMC4361A_START_EN_3__FIELD                         ((RegisterField) {TMC4361A_START_EN_3__MASK, TMC4361A_START_EN_3__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_START_EN_4__MASK                          0x00000010
#define TMC4361A_START_EN_4__SHIFT                         4
#define TMC4361A_START_EN_4__FIELD                         ((RegisterField) {TMC4361A_START_EN_4__MASK, TMC4361A_START_EN_4__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_TRIGGER_EVENTS_0__MASK                    0x00000020
#define TMC4361A_TRIGGER_EVENTS_0__SHIFT                   5
#define TMC4361A_TRIGGER_EVENTS_0__FIELD                   ((RegisterField) {TMC4361A_TRIGGER_EVENTS_0__MASK, TMC4361A_TRIGGER_EVENTS_0__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_TRIGGER_EVENTS_1__MASK                    0x00000040
#define TMC4361A_TRIGGER_EVENTS_1__SHIFT                   6
#define TMC4361A_TRIGGER_EVENTS_1__FIELD                   ((RegisterField) {TMC4361A_TRIGGER_EVENTS_1__MASK, TMC4361A_TRIGGER_EVENTS_1__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_TRIGGER_EVENTS_2__MASK                    0x00000080
#define TMC4361A_TRIGGER_EVENTS_2__SHIFT                   7
#define TMC4361A_TRIGGER_EVENTS_2__FIELD                   ((RegisterField) {TMC4361A_TRIGGER_EVENTS_2__MASK, TMC4361A_TRIGGER_EVENTS_2__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_TRIGGER_EVENTS_3__MASK                    0x00000100
#define TMC4361A_TRIGGER_EVENTS_3__SHIFT                   8
#define TMC4361A_TRIGGER_EVENTS_3__FIELD                   ((RegisterField) {TMC4361A_TRIGGER_EVENTS_3__MASK, TMC4361A_TRIGGER_EVENTS_3__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_POL_START_SIGNAL_MASK                     0x00000200
#define TMC4361A_POL_START_SIGNAL_SHIFT                    9
#define TMC4361A_POL_START_SIGNAL_FIELD                    ((RegisterField) {TMC4361A_POL_START_SIGNAL_MASK, TMC4361A_POL_START_SIGNAL_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_IMMEDIATE_START_IN_MASK                   0x00000400
#define TMC4361A_IMMEDIATE_START_IN_SHIFT                  10
#define TMC4361A_IMMEDIATE_START_IN_FIELD                  ((RegisterField) {TMC4361A_IMMEDIATE_START_IN_MASK, TMC4361A_IMMEDIATE_START_IN_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_BUSY_STATE_EN_MASK                        0x00000800
#define TMC4361A_BUSY_STATE_EN_SHIFT                       11
#define TMC4361A_BUSY_STATE_EN_FIELD                       ((RegisterField) {TMC4361A_BUSY_STATE_EN_MASK, TMC4361A_BUSY_STATE_EN_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_PIPELINE_EN_0__MASK                       0x00001000
#define TMC4361A_PIPELINE_EN_0__SHIFT                      12
#define TMC4361A_PIPELINE_EN_0__FIELD                      ((RegisterField) {TMC4361A_PIPELINE_EN_0__MASK, TMC4361A_PIPELINE_EN_0__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_PIPELINE_EN_1__MASK                       0x00002000
#define TMC4361A_PIPELINE_EN_1__SHIFT                      13
#define TMC4361A_PIPELINE_EN_1__FIELD                      ((RegisterField) {TMC4361A_PIPELINE_EN_1__MASK, TMC4361A_PIPELINE_EN_1__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_PIPELINE_EN_2__MASK                       0x00004000
#define TMC4361A_PIPELINE_EN_2__SHIFT                      14
#define TMC4361A_PIPELINE_EN_2__FIELD                      ((RegisterField) {TMC4361A_PIPELINE_EN_2__MASK, TMC4361A_PIPELINE_EN_2__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_PIPELINE_EN_3__MASK                       0x00008000
#define TMC4361A_PIPELINE_EN_3__SHIFT                      15
#define TMC4361A_PIPELINE_EN_3__FIELD                      ((RegisterField) {TMC4361A_PIPELINE_EN_3__MASK, TMC4361A_PIPELINE_EN_3__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_SHADOW_OPTION_MASK                        0x00030000
#define TMC4361A_SHADOW_OPTION_SHIFT                       16
#define TMC4361A_SHADOW_OPTION_FIELD                       ((RegisterField) {TMC4361A_SHADOW_OPTION_MASK, TMC4361A_SHADOW_OPTION_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_CYCLIC_SHADOW_REGS_MASK                   0x00040000
#define TMC4361A_CYCLIC_SHADOW_REGS_SHIFT                  18
#define TMC4361A_CYCLIC_SHADOW_REGS_FIELD                  ((RegisterField) {TMC4361A_CYCLIC_SHADOW_REGS_MASK, TMC4361A_CYCLIC_SHADOW_REGS_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_SHADOW_MISS_CNT_MASK                      0x00f00000
#define TMC4361A_SHADOW_MISS_CNT_SHIFT                     20
#define TMC4361A_SHADOW_MISS_CNT_FIELD                     ((RegisterField) {TMC4361A_SHADOW_MISS_CNT_MASK, TMC4361A_SHADOW_MISS_CNT_SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_0__MASK                 0x01000000
#define TMC4361A_XPIPE_REWRITE_REG_0__SHIFT                24
#define TMC4361A_XPIPE_REWRITE_REG_0__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_0__MASK, TMC4361A_XPIPE_REWRITE_REG_0__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_1__MASK                 0x02000000
#define TMC4361A_XPIPE_REWRITE_REG_1__SHIFT                25
#define TMC4361A_XPIPE_REWRITE_REG_1__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_1__MASK, TMC4361A_XPIPE_REWRITE_REG_1__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_2__MASK                 0x04000000
#define TMC4361A_XPIPE_REWRITE_REG_2__SHIFT                26
#define TMC4361A_XPIPE_REWRITE_REG_2__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_2__MASK, TMC4361A_XPIPE_REWRITE_REG_2__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_3__MASK                 0x08000000
#define TMC4361A_XPIPE_REWRITE_REG_3__SHIFT                27
#define TMC4361A_XPIPE_REWRITE_REG_3__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_3__MASK, TMC4361A_XPIPE_REWRITE_REG_3__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_4__MASK                 0x10000000
#define TMC4361A_XPIPE_REWRITE_REG_4__SHIFT                28
#define TMC4361A_XPIPE_REWRITE_REG_4__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_4__MASK, TMC4361A_XPIPE_REWRITE_REG_4__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_5__MASK                 0x20000000
#define TMC4361A_XPIPE_REWRITE_REG_5__SHIFT                29
#define TMC4361A_XPIPE_REWRITE_REG_5__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_5__MASK, TMC4361A_XPIPE_REWRITE_REG_5__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_6__MASK                 0x40000000
#define TMC4361A_XPIPE_REWRITE_REG_6__SHIFT                30
#define TMC4361A_XPIPE_REWRITE_REG_6__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_6__MASK, TMC4361A_XPIPE_REWRITE_REG_6__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_XPIPE_REWRITE_REG_7__MASK                 0x80000000
#define TMC4361A_XPIPE_REWRITE_REG_7__SHIFT                31
#define TMC4361A_XPIPE_REWRITE_REG_7__FIELD                ((RegisterField) {TMC4361A_XPIPE_REWRITE_REG_7__MASK, TMC4361A_XPIPE_REWRITE_REG_7__SHIFT, TMC4361A_START_CONF, false})
#define TMC4361A_SR_ENC_IN_MASK                            0x00000007
#define TMC4361A_SR_ENC_IN_SHIFT                           0
#define TMC4361A_SR_ENC_IN_FIELD                           ((RegisterField) {TMC4361A_SR_ENC_IN_MASK, TMC4361A_SR_ENC_IN_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_FILT_L_ENC_IN_MASK                        0x00000070
#define TMC4361A_FILT_L_ENC_IN_SHIFT                       4
#define TMC4361A_FILT_L_ENC_IN_FIELD                       ((RegisterField) {TMC4361A_FILT_L_ENC_IN_MASK, TMC4361A_FILT_L_ENC_IN_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SD_FILT0_MASK                             0x00000080
#define TMC4361A_SD_FILT0_SHIFT                            7
#define TMC4361A_SD_FILT0_FIELD                            ((RegisterField) {TMC4361A_SD_FILT0_MASK, TMC4361A_SD_FILT0_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SR_REF_MASK                               0x00000700
#define TMC4361A_SR_REF_SHIFT                              8
#define TMC4361A_SR_REF_FIELD                              ((RegisterField) {TMC4361A_SR_REF_MASK, TMC4361A_SR_REF_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_FILT_L_REF_MASK                           0x00007000
#define TMC4361A_FILT_L_REF_SHIFT                          12
#define TMC4361A_FILT_L_REF_FIELD                          ((RegisterField) {TMC4361A_FILT_L_REF_MASK, TMC4361A_FILT_L_REF_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SD_FILT1_MASK                             0x00008000
#define TMC4361A_SD_FILT1_SHIFT                            15
#define TMC4361A_SD_FILT1_FIELD                            ((RegisterField) {TMC4361A_SD_FILT1_MASK, TMC4361A_SD_FILT1_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SR_S_MASK                                 0x00070000
#define TMC4361A_SR_S_SHIFT                                16
#define TMC4361A_SR_S_FIELD                                ((RegisterField) {TMC4361A_SR_S_MASK, TMC4361A_SR_S_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_FILT_L_S_MASK                             0x00700000
#define TMC4361A_FILT_L_S_SHIFT                            20
#define TMC4361A_FILT_L_S_FIELD                            ((RegisterField) {TMC4361A_FILT_L_S_MASK, TMC4361A_FILT_L_S_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SD_FILT2_MASK                             0x00800000
#define TMC4361A_SD_FILT2_SHIFT                            23
#define TMC4361A_SD_FILT2_FIELD                            ((RegisterField) {TMC4361A_SD_FILT2_MASK, TMC4361A_SD_FILT2_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SR_ENC_OUT_MASK                           0x07000000
#define TMC4361A_SR_ENC_OUT_SHIFT                          24
#define TMC4361A_SR_ENC_OUT_FIELD                          ((RegisterField) {TMC4361A_SR_ENC_OUT_MASK, TMC4361A_SR_ENC_OUT_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_FILT_L_ENC_OUT_MASK                       0x70000000
#define TMC4361A_FILT_L_ENC_OUT_SHIFT                      28
#define TMC4361A_FILT_L_ENC_OUT_FIELD                      ((RegisterField) {TMC4361A_FILT_L_ENC_OUT_MASK, TMC4361A_FILT_L_ENC_OUT_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SD_FILT3_MASK                             0x80000000
#define TMC4361A_SD_FILT3_SHIFT                            31
#define TMC4361A_SD_FILT3_FIELD                            ((RegisterField) {TMC4361A_SD_FILT3_MASK, TMC4361A_SD_FILT3_SHIFT, TMC4361A_INPUT_FILT_CONF, false})
#define TMC4361A_SPI_OUTPUT_FORMAT_MASK                    0x0000000f
#define TMC4361A_SPI_OUTPUT_FORMAT_SHIFT                   0
#define TMC4361A_SPI_OUTPUT_FORMAT_FIELD                   ((RegisterField) {TMC4361A_SPI_OUTPUT_FORMAT_MASK, TMC4361A_SPI_OUTPUT_FORMAT_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SSI_OUT_MTIME_MASK                        0x00fffff0
#define TMC4361A_SSI_OUT_MTIME_SHIFT                       4
#define TMC4361A_SSI_OUT_MTIME_FIELD                       ((RegisterField) {TMC4361A_SSI_OUT_MTIME_MASK, TMC4361A_SSI_OUT_MTIME_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_MIXED_DECAY_MASK                          0x00000030
#define TMC4361A_MIXED_DECAY_SHIFT                         4
#define TMC4361A_MIXED_DECAY_FIELD                         ((RegisterField) {TMC4361A_MIXED_DECAY_MASK, TMC4361A_MIXED_DECAY_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_AUTO_DOUBLE_CHOPSYNC_MASK                 0x00001000
#define TMC4361A_AUTO_DOUBLE_CHOPSYNC_SHIFT                12
#define TMC4361A_AUTO_DOUBLE_CHOPSYNC_FIELD                ((RegisterField) {TMC4361A_AUTO_DOUBLE_CHOPSYNC_MASK, TMC4361A_AUTO_DOUBLE_CHOPSYNC_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_STDBY_ON_STALL_FOR_24X_MASK               0x00000040
#define TMC4361A_STDBY_ON_STALL_FOR_24X_SHIFT              6
#define TMC4361A_STDBY_ON_STALL_FOR_24X_FIELD              ((RegisterField) {TMC4361A_STDBY_ON_STALL_FOR_24X_MASK, TMC4361A_STDBY_ON_STALL_FOR_24X_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_STALL_FLAG_INSTEAD_OF_UV_EN_MASK          0x00000080
#define TMC4361A_STALL_FLAG_INSTEAD_OF_UV_EN_SHIFT         7
#define TMC4361A_STALL_FLAG_INSTEAD_OF_UV_EN_FIELD         ((RegisterField) {TMC4361A_STALL_FLAG_INSTEAD_OF_UV_EN_MASK, TMC4361A_STALL_FLAG_INSTEAD_OF_UV_EN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_STALL_LOAD_LIMIT_MASK                     0x00000700
#define TMC4361A_STALL_LOAD_LIMIT_SHIFT                    8
#define TMC4361A_STALL_LOAD_LIMIT_FIELD                    ((RegisterField) {TMC4361A_STALL_LOAD_LIMIT_MASK, TMC4361A_STALL_LOAD_LIMIT_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_PWM_PHASE_SHFT_EN_MASK                    0x00000800
#define TMC4361A_PWM_PHASE_SHFT_EN_SHIFT                   11
#define TMC4361A_PWM_PHASE_SHFT_EN_FIELD                   ((RegisterField) {TMC4361A_PWM_PHASE_SHFT_EN_MASK, TMC4361A_PWM_PHASE_SHFT_EN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_THREE_PHASE_STEPPER_EN_MASK               0x00000010
#define TMC4361A_THREE_PHASE_STEPPER_EN_SHIFT              4
#define TMC4361A_THREE_PHASE_STEPPER_EN_FIELD              ((RegisterField) {TMC4361A_THREE_PHASE_STEPPER_EN_MASK, TMC4361A_THREE_PHASE_STEPPER_EN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_AUTOREPEAT_COVER_EN_MASK                  0x00000080
#define TMC4361A_AUTOREPEAT_COVER_EN_SHIFT                 7
#define TMC4361A_AUTOREPEAT_COVER_EN_FIELD                 ((RegisterField) {TMC4361A_AUTOREPEAT_COVER_EN_MASK, TMC4361A_AUTOREPEAT_COVER_EN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_COVER_DONE_ONLY_FOR_COVER_MASK            0x00001000
#define TMC4361A_COVER_DONE_ONLY_FOR_COVER_SHIFT           12
#define TMC4361A_COVER_DONE_ONLY_FOR_COVER_FIELD           ((RegisterField) {TMC4361A_COVER_DONE_ONLY_FOR_COVER_MASK, TMC4361A_COVER_DONE_ONLY_FOR_COVER_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SCALE_VALE_TRANSFER_EN_MASK               0x00000020
#define TMC4361A_SCALE_VALE_TRANSFER_EN_SHIFT              5
#define TMC4361A_SCALE_VALE_TRANSFER_EN_FIELD              ((RegisterField) {TMC4361A_SCALE_VALE_TRANSFER_EN_MASK, TMC4361A_SCALE_VALE_TRANSFER_EN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_DISABLE_POLLING_MASK                      0x00000040
#define TMC4361A_DISABLE_POLLING_SHIFT                     6
#define TMC4361A_DISABLE_POLLING_FIELD                     ((RegisterField) {TMC4361A_DISABLE_POLLING_MASK, TMC4361A_DISABLE_POLLING_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_POLL_BLOCK_EXP_MASK                       0x00000f00
#define TMC4361A_POLL_BLOCK_EXP_SHIFT                      8
#define TMC4361A_POLL_BLOCK_EXP_FIELD                      ((RegisterField) {TMC4361A_POLL_BLOCK_EXP_MASK, TMC4361A_POLL_BLOCK_EXP_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SCK_LOW_BEFORE_CSN_MASK                   0x00000010
#define TMC4361A_SCK_LOW_BEFORE_CSN_SHIFT                  4
#define TMC4361A_SCK_LOW_BEFORE_CSN_FIELD                  ((RegisterField) {TMC4361A_SCK_LOW_BEFORE_CSN_MASK, TMC4361A_SCK_LOW_BEFORE_CSN_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_NEW_OUT_BIT_AT_RISE_MASK                  0x00000020
#define TMC4361A_NEW_OUT_BIT_AT_RISE_SHIFT                 5
#define TMC4361A_NEW_OUT_BIT_AT_RISE_FIELD                 ((RegisterField) {TMC4361A_NEW_OUT_BIT_AT_RISE_MASK, TMC4361A_NEW_OUT_BIT_AT_RISE_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_DAC_CMD_LENGTH_MASK                       0x00000f80
#define TMC4361A_DAC_CMD_LENGTH_SHIFT                      7
#define TMC4361A_DAC_CMD_LENGTH_FIELD                      ((RegisterField) {TMC4361A_DAC_CMD_LENGTH_MASK, TMC4361A_DAC_CMD_LENGTH_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_COVER_DATA_LENGTH_MASK                    0x000fe000
#define TMC4361A_COVER_DATA_LENGTH_SHIFT                   13
#define TMC4361A_COVER_DATA_LENGTH_FIELD                   ((RegisterField) {TMC4361A_COVER_DATA_LENGTH_MASK, TMC4361A_COVER_DATA_LENGTH_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SPI_OUT_LOW_TIME_MASK                     0x00f00000
#define TMC4361A_SPI_OUT_LOW_TIME_SHIFT                    20
#define TMC4361A_SPI_OUT_LOW_TIME_FIELD                    ((RegisterField) {TMC4361A_SPI_OUT_LOW_TIME_MASK, TMC4361A_SPI_OUT_LOW_TIME_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SPI_OUT_HIGH_TIME_MASK                    0x0f000000
#define TMC4361A_SPI_OUT_HIGH_TIME_SHIFT                   24
#define TMC4361A_SPI_OUT_HIGH_TIME_FIELD                   ((RegisterField) {TMC4361A_SPI_OUT_HIGH_TIME_MASK, TMC4361A_SPI_OUT_HIGH_TIME_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_SPI_OUT_BLOCK_TIME_MASK                   0xf0000000
#define TMC4361A_SPI_OUT_BLOCK_TIME_SHIFT                  28
#define TMC4361A_SPI_OUT_BLOCK_TIME_FIELD                  ((RegisterField) {TMC4361A_SPI_OUT_BLOCK_TIME_MASK, TMC4361A_SPI_OUT_BLOCK_TIME_SHIFT, TMC4361A_SPI_OUT_CONF, false})
#define TMC4361A_HOLD_CURRENT_SCALE_EN_MASK                0x00000001
#define TMC4361A_HOLD_CURRENT_SCALE_EN_SHIFT               0
#define TMC4361A_HOLD_CURRENT_SCALE_EN_FIELD               ((RegisterField) {TMC4361A_HOLD_CURRENT_SCALE_EN_MASK, TMC4361A_HOLD_CURRENT_SCALE_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_DRIVE_CURRENT_SCALE_EN_MASK               0x00000002
#define TMC4361A_DRIVE_CURRENT_SCALE_EN_SHIFT              1
#define TMC4361A_DRIVE_CURRENT_SCALE_EN_FIELD              ((RegisterField) {TMC4361A_DRIVE_CURRENT_SCALE_EN_MASK, TMC4361A_DRIVE_CURRENT_SCALE_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_BOOST_CURRENT_ON_ACC_EN_MASK              0x00000004
#define TMC4361A_BOOST_CURRENT_ON_ACC_EN_SHIFT             2
#define TMC4361A_BOOST_CURRENT_ON_ACC_EN_FIELD             ((RegisterField) {TMC4361A_BOOST_CURRENT_ON_ACC_EN_MASK, TMC4361A_BOOST_CURRENT_ON_ACC_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_BOOST_CURRENT_ON_DEC_EN_MASK              0x00000008
#define TMC4361A_BOOST_CURRENT_ON_DEC_EN_SHIFT             3
#define TMC4361A_BOOST_CURRENT_ON_DEC_EN_FIELD             ((RegisterField) {TMC4361A_BOOST_CURRENT_ON_DEC_EN_MASK, TMC4361A_BOOST_CURRENT_ON_DEC_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_BOOST_CURRENT_AFTER_START_EN_MASK         0x00000010
#define TMC4361A_BOOST_CURRENT_AFTER_START_EN_SHIFT        4
#define TMC4361A_BOOST_CURRENT_AFTER_START_EN_FIELD        ((RegisterField) {TMC4361A_BOOST_CURRENT_AFTER_START_EN_MASK, TMC4361A_BOOST_CURRENT_AFTER_START_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_SEC_DRIVE_CURRENT_SCALE_EN_MASK           0x00000020
#define TMC4361A_SEC_DRIVE_CURRENT_SCALE_EN_SHIFT          5
#define TMC4361A_SEC_DRIVE_CURRENT_SCALE_EN_FIELD          ((RegisterField) {TMC4361A_SEC_DRIVE_CURRENT_SCALE_EN_MASK, TMC4361A_SEC_DRIVE_CURRENT_SCALE_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_FREEWHEELING_EN_MASK                      0x00000040
#define TMC4361A_FREEWHEELING_EN_SHIFT                     6
#define TMC4361A_FREEWHEELING_EN_FIELD                     ((RegisterField) {TMC4361A_FREEWHEELING_EN_MASK, TMC4361A_FREEWHEELING_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_CLOSED_LOOP_SCALE_EN_MASK                 0x00000080
#define TMC4361A_CLOSED_LOOP_SCALE_EN_SHIFT                7
#define TMC4361A_CLOSED_LOOP_SCALE_EN_FIELD                ((RegisterField) {TMC4361A_CLOSED_LOOP_SCALE_EN_MASK, TMC4361A_CLOSED_LOOP_SCALE_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_PWM_SCALE_EN_MASK                         0x00000100
#define TMC4361A_PWM_SCALE_EN_SHIFT                        8
#define TMC4361A_PWM_SCALE_EN_FIELD                        ((RegisterField) {TMC4361A_PWM_SCALE_EN_MASK, TMC4361A_PWM_SCALE_EN_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_PWM_AMPL_MASK                             0xffff0000
#define TMC4361A_PWM_AMPL_SHIFT                            16
#define TMC4361A_PWM_AMPL_FIELD                            ((RegisterField) {TMC4361A_PWM_AMPL_MASK, TMC4361A_PWM_AMPL_SHIFT, TMC4361A_CURRENT_CONF, false})
#define TMC4361A_BOOST_SCALE_VAL_MASK                      0x000000ff
#define TMC4361A_BOOST_SCALE_VAL_SHIFT                     0
#define TMC4361A_BOOST_SCALE_VAL_FIELD                     ((RegisterField) {TMC4361A_BOOST_SCALE_VAL_MASK, TMC4361A_BOOST_SCALE_VAL_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_DRV1_SCALE_VAL_MASK                       0x0000ff00
#define TMC4361A_DRV1_SCALE_VAL_SHIFT                      8
#define TMC4361A_DRV1_SCALE_VAL_FIELD                      ((RegisterField) {TMC4361A_DRV1_SCALE_VAL_MASK, TMC4361A_DRV1_SCALE_VAL_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_DRV2_SCALE_VAL_MASK                       0x00ff0000
#define TMC4361A_DRV2_SCALE_VAL_SHIFT                      16
#define TMC4361A_DRV2_SCALE_VAL_FIELD                      ((RegisterField) {TMC4361A_DRV2_SCALE_VAL_MASK, TMC4361A_DRV2_SCALE_VAL_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_HOLD_SCALE_VAL_MASK                       0xff000000
#define TMC4361A_HOLD_SCALE_VAL_SHIFT                      24
#define TMC4361A_HOLD_SCALE_VAL_FIELD                      ((RegisterField) {TMC4361A_HOLD_SCALE_VAL_MASK, TMC4361A_HOLD_SCALE_VAL_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_CL_IMIN_MASK                              0x000000ff
#define TMC4361A_CL_IMIN_SHIFT                             0
#define TMC4361A_CL_IMIN_FIELD                             ((RegisterField) {TMC4361A_CL_IMIN_MASK, TMC4361A_CL_IMIN_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_CL_IMAX_MASK                              0x0000ff00
#define TMC4361A_CL_IMAX_SHIFT                             8
#define TMC4361A_CL_IMAX_FIELD                             ((RegisterField) {TMC4361A_CL_IMAX_MASK, TMC4361A_CL_IMAX_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_CL_START_UP_MASK                          0x00ff0000
#define TMC4361A_CL_START_UP_SHIFT                         16
#define TMC4361A_CL_START_UP_FIELD                         ((RegisterField) {TMC4361A_CL_START_UP_MASK, TMC4361A_CL_START_UP_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_CL_START_DN_MASK                          0xff000000
#define TMC4361A_CL_START_DN_SHIFT                         24
#define TMC4361A_CL_START_DN_FIELD                         ((RegisterField) {TMC4361A_CL_START_DN_MASK, TMC4361A_CL_START_DN_SHIFT, TMC4361A_SCALE_VALUES, false})
#define TMC4361A_ENC_SEL_DECIMAL_MASK                      0x00000001
#define TMC4361A_ENC_SEL_DECIMAL_SHIFT                     0
#define TMC4361A_ENC_SEL_DECIMAL_FIELD                     ((RegisterField) {TMC4361A_ENC_SEL_DECIMAL_MASK, TMC4361A_ENC_SEL_DECIMAL_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CLEAR_ON_N_MASK                           0x00000002
#define TMC4361A_CLEAR_ON_N_SHIFT                          1
#define TMC4361A_CLEAR_ON_N_FIELD                          ((RegisterField) {TMC4361A_CLEAR_ON_N_MASK, TMC4361A_CLEAR_ON_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CLR_LATCH_CONT_ON_N_MASK                  0x00000004
#define TMC4361A_CLR_LATCH_CONT_ON_N_SHIFT                 2
#define TMC4361A_CLR_LATCH_CONT_ON_N_FIELD                 ((RegisterField) {TMC4361A_CLR_LATCH_CONT_ON_N_MASK, TMC4361A_CLR_LATCH_CONT_ON_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CLR_LATCH_ONCE_ON_N_MASK                  0x00000008
#define TMC4361A_CLR_LATCH_ONCE_ON_N_SHIFT                 3
#define TMC4361A_CLR_LATCH_ONCE_ON_N_FIELD                 ((RegisterField) {TMC4361A_CLR_LATCH_ONCE_ON_N_MASK, TMC4361A_CLR_LATCH_ONCE_ON_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_POL_N_MASK                                0x00000010
#define TMC4361A_POL_N_SHIFT                               4
#define TMC4361A_POL_N_FIELD                               ((RegisterField) {TMC4361A_POL_N_MASK, TMC4361A_POL_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_N_CHAN_SENSITIVITY_MASK                   0x00000060
#define TMC4361A_N_CHAN_SENSITIVITY_SHIFT                  5
#define TMC4361A_N_CHAN_SENSITIVITY_FIELD                  ((RegisterField) {TMC4361A_N_CHAN_SENSITIVITY_MASK, TMC4361A_N_CHAN_SENSITIVITY_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_POL_A_FOR_N_MASK                          0x00000080
#define TMC4361A_POL_A_FOR_N_SHIFT                         7
#define TMC4361A_POL_A_FOR_N_FIELD                         ((RegisterField) {TMC4361A_POL_A_FOR_N_MASK, TMC4361A_POL_A_FOR_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_POL_B_FOR_N_MASK                          0x00000100
#define TMC4361A_POL_B_FOR_N_SHIFT                         8
#define TMC4361A_POL_B_FOR_N_FIELD                         ((RegisterField) {TMC4361A_POL_B_FOR_N_MASK, TMC4361A_POL_B_FOR_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_IGNORE_AB_MASK                            0x00000200
#define TMC4361A_IGNORE_AB_SHIFT                           9
#define TMC4361A_IGNORE_AB_FIELD                           ((RegisterField) {TMC4361A_IGNORE_AB_MASK, TMC4361A_IGNORE_AB_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_LATCH_ENC_ON_N_MASK                       0x00000400
#define TMC4361A_LATCH_ENC_ON_N_SHIFT                      10
#define TMC4361A_LATCH_ENC_ON_N_FIELD                      ((RegisterField) {TMC4361A_LATCH_ENC_ON_N_MASK, TMC4361A_LATCH_ENC_ON_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_LATCH_X_ON_N_MASK                         0x00000800
#define TMC4361A_LATCH_X_ON_N_SHIFT                        11
#define TMC4361A_LATCH_X_ON_N_FIELD                        ((RegisterField) {TMC4361A_LATCH_X_ON_N_MASK, TMC4361A_LATCH_X_ON_N_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_MULTI_TURN_IN_EN_MASK                     0x00001000
#define TMC4361A_MULTI_TURN_IN_EN_SHIFT                    12
#define TMC4361A_MULTI_TURN_IN_EN_FIELD                    ((RegisterField) {TMC4361A_MULTI_TURN_IN_EN_MASK, TMC4361A_MULTI_TURN_IN_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_MULTI_TURN_IN_SIGNED_MASK                 0x00002000
#define TMC4361A_MULTI_TURN_IN_SIGNED_SHIFT                13
#define TMC4361A_MULTI_TURN_IN_SIGNED_FIELD                ((RegisterField) {TMC4361A_MULTI_TURN_IN_SIGNED_MASK, TMC4361A_MULTI_TURN_IN_SIGNED_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_MULTI_TURN_OUT_EN_MASK                    0x00004000
#define TMC4361A_MULTI_TURN_OUT_EN_SHIFT                   14
#define TMC4361A_MULTI_TURN_OUT_EN_FIELD                   ((RegisterField) {TMC4361A_MULTI_TURN_OUT_EN_MASK, TMC4361A_MULTI_TURN_OUT_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_USE_USTEPS_INSTEAD_OF_XRANGE_MASK         0x00008000
#define TMC4361A_USE_USTEPS_INSTEAD_OF_XRANGE_SHIFT        15
#define TMC4361A_USE_USTEPS_INSTEAD_OF_XRANGE_FIELD        ((RegisterField) {TMC4361A_USE_USTEPS_INSTEAD_OF_XRANGE_MASK, TMC4361A_USE_USTEPS_INSTEAD_OF_XRANGE_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CALC_MULTI_TURN_BEHAV_MASK                0x00010000
#define TMC4361A_CALC_MULTI_TURN_BEHAV_SHIFT               16
#define TMC4361A_CALC_MULTI_TURN_BEHAV_FIELD               ((RegisterField) {TMC4361A_CALC_MULTI_TURN_BEHAV_MASK, TMC4361A_CALC_MULTI_TURN_BEHAV_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SSI_MULTI_CYCLE_DATA_MASK                 0x00020000
#define TMC4361A_SSI_MULTI_CYCLE_DATA_SHIFT                17
#define TMC4361A_SSI_MULTI_CYCLE_DATA_FIELD                ((RegisterField) {TMC4361A_SSI_MULTI_CYCLE_DATA_MASK, TMC4361A_SSI_MULTI_CYCLE_DATA_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SSI_GRAY_CODE_EN_MASK                     0x00040000
#define TMC4361A_SSI_GRAY_CODE_EN_SHIFT                    18
#define TMC4361A_SSI_GRAY_CODE_EN_FIELD                    ((RegisterField) {TMC4361A_SSI_GRAY_CODE_EN_MASK, TMC4361A_SSI_GRAY_CODE_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_LEFT_ALIGNED_DATA_MASK                    0x00080000
#define TMC4361A_LEFT_ALIGNED_DATA_SHIFT                   19
#define TMC4361A_LEFT_ALIGNED_DATA_FIELD                   ((RegisterField) {TMC4361A_LEFT_ALIGNED_DATA_MASK, TMC4361A_LEFT_ALIGNED_DATA_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SPI_DATA_ON_CS_MASK                       0x00100000
#define TMC4361A_SPI_DATA_ON_CS_SHIFT                      20
#define TMC4361A_SPI_DATA_ON_CS_FIELD                      ((RegisterField) {TMC4361A_SPI_DATA_ON_CS_MASK, TMC4361A_SPI_DATA_ON_CS_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SPI_LOW_BEFORE_CS_MASK                    0x00200000
#define TMC4361A_SPI_LOW_BEFORE_CS_SHIFT                   21
#define TMC4361A_SPI_LOW_BEFORE_CS_FIELD                   ((RegisterField) {TMC4361A_SPI_LOW_BEFORE_CS_MASK, TMC4361A_SPI_LOW_BEFORE_CS_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_REGULATION_MODUS_MASK                     0x00c00000
#define TMC4361A_REGULATION_MODUS_SHIFT                    22
#define TMC4361A_REGULATION_MODUS_FIELD                    ((RegisterField) {TMC4361A_REGULATION_MODUS_MASK, TMC4361A_REGULATION_MODUS_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CL_CALIBRATION_EN_MASK                    0x01000000
#define TMC4361A_CL_CALIBRATION_EN_SHIFT                   24
#define TMC4361A_CL_CALIBRATION_EN_FIELD                   ((RegisterField) {TMC4361A_CL_CALIBRATION_EN_MASK, TMC4361A_CL_CALIBRATION_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CL_EMF_EN_MASK                            0x02000000
#define TMC4361A_CL_EMF_EN_SHIFT                           25
#define TMC4361A_CL_EMF_EN_FIELD                           ((RegisterField) {TMC4361A_CL_EMF_EN_MASK, TMC4361A_CL_EMF_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CL_CLR_XACT_MASK                          0x04000000
#define TMC4361A_CL_CLR_XACT_SHIFT                         26
#define TMC4361A_CL_CLR_XACT_FIELD                         ((RegisterField) {TMC4361A_CL_CLR_XACT_MASK, TMC4361A_CL_CLR_XACT_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CL_VLIMIT_EN_MASK                         0x08000000
#define TMC4361A_CL_VLIMIT_EN_SHIFT                        27
#define TMC4361A_CL_VLIMIT_EN_FIELD                        ((RegisterField) {TMC4361A_CL_VLIMIT_EN_MASK, TMC4361A_CL_VLIMIT_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_CL_VELOCITY_MODE_EN_MASK                  0x10000000
#define TMC4361A_CL_VELOCITY_MODE_EN_SHIFT                 28
#define TMC4361A_CL_VELOCITY_MODE_EN_FIELD                 ((RegisterField) {TMC4361A_CL_VELOCITY_MODE_EN_MASK, TMC4361A_CL_VELOCITY_MODE_EN_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_INVERT_ENC_DIR_MASK                       0x20000000
#define TMC4361A_INVERT_ENC_DIR_SHIFT                      29
#define TMC4361A_INVERT_ENC_DIR_FIELD                      ((RegisterField) {TMC4361A_INVERT_ENC_DIR_MASK, TMC4361A_INVERT_ENC_DIR_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_ENC_OUT_GRAY_MASK                         0x40000000
#define TMC4361A_ENC_OUT_GRAY_SHIFT                        30
#define TMC4361A_ENC_OUT_GRAY_FIELD                        ((RegisterField) {TMC4361A_ENC_OUT_GRAY_MASK, TMC4361A_ENC_OUT_GRAY_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_NO_ENC_VEL_PREPROC_MASK                   0x80000000
#define TMC4361A_NO_ENC_VEL_PREPROC_SHIFT                  31
#define TMC4361A_NO_ENC_VEL_PREPROC_FIELD                  ((RegisterField) {TMC4361A_NO_ENC_VEL_PREPROC_MASK, TMC4361A_NO_ENC_VEL_PREPROC_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SERIAL_ENC_VARIATION_LIMIT_MASK           0x80000000
#define TMC4361A_SERIAL_ENC_VARIATION_LIMIT_SHIFT          31
#define TMC4361A_SERIAL_ENC_VARIATION_LIMIT_FIELD          ((RegisterField) {TMC4361A_SERIAL_ENC_VARIATION_LIMIT_MASK, TMC4361A_SERIAL_ENC_VARIATION_LIMIT_SHIFT, TMC4361A_ENC_IN_CONF, false})
#define TMC4361A_SINGLE_TURN_RES_MASK                      0x0000001f
#define TMC4361A_SINGLE_TURN_RES_SHIFT                     0
#define TMC4361A_SINGLE_TURN_RES_FIELD                     ((RegisterField) {TMC4361A_SINGLE_TURN_RES_MASK, TMC4361A_SINGLE_TURN_RES_SHIFT, TMC4361A_ENC_IN_DATA, false})
#define TMC4361A_MULTI_TURN_RES_MASK                       0x000003e0
#define TMC4361A_MULTI_TURN_RES_SHIFT                      5
#define TMC4361A_MULTI_TURN_RES_FIELD                      ((RegisterField) {TMC4361A_MULTI_TURN_RES_MASK, TMC4361A_MULTI_TURN_RES_SHIFT, TMC4361A_ENC_IN_DATA, false})
#define TMC4361A_STATUS_BIT_CNT_MASK                       0x00000c00
#define TMC4361A_STATUS_BIT_CNT_SHIFT                      10
#define TMC4361A_STATUS_BIT_CNT_FIELD                      ((RegisterField) {TMC4361A_STATUS_BIT_CNT_MASK, TMC4361A_STATUS_BIT_CNT_SHIFT, TMC4361A_ENC_IN_DATA, false})
#define TMC4361A_SERIAL_ADDR_BITS_MASK                     0x00ff0000
#define TMC4361A_SERIAL_ADDR_BITS_SHIFT                    16
#define TMC4361A_SERIAL_ADDR_BITS_FIELD                    ((RegisterField) {TMC4361A_SERIAL_ADDR_BITS_MASK, TMC4361A_SERIAL_ADDR_BITS_SHIFT, TMC4361A_ENC_IN_DATA, false})
#define TMC4361A_SERIAL_DATA_BITS_MASK                     0xff000000
#define TMC4361A_SERIAL_DATA_BITS_SHIFT                    24
#define TMC4361A_SERIAL_DATA_BITS_FIELD                    ((RegisterField) {TMC4361A_SERIAL_DATA_BITS_MASK, TMC4361A_SERIAL_DATA_BITS_SHIFT, TMC4361A_ENC_IN_DATA, false})
#define TMC4361A_SINGLE_TURN_RES_OUT_MASK                  0x0000001f
#define TMC4361A_SINGLE_TURN_RES_OUT_SHIFT                 0
#define TMC4361A_SINGLE_TURN_RES_OUT_FIELD                 ((RegisterField) {TMC4361A_SINGLE_TURN_RES_OUT_MASK, TMC4361A_SINGLE_TURN_RES_OUT_SHIFT, TMC4361A_ENC_OUT_DATA, false})
#define TMC4361A_MULTI_TURN_RES_OUT_MASK                   0x000003e0
#define TMC4361A_MULTI_TURN_RES_OUT_SHIFT                  5
#define TMC4361A_MULTI_TURN_RES_OUT_FIELD                  ((RegisterField) {TMC4361A_MULTI_TURN_RES_OUT_MASK, TMC4361A_MULTI_TURN_RES_OUT_SHIFT, TMC4361A_ENC_OUT_DATA, false})
#define TMC4361A_MSTEP_PER_FS_MASK                         0x0000000f
#define TMC4361A_MSTEP_PER_FS_SHIFT                        0
#define TMC4361A_MSTEP_PER_FS_FIELD                        ((RegisterField) {TMC4361A_MSTEP_PER_FS_MASK, TMC4361A_MSTEP_PER_FS_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_FS_PER_REV_MASK                           0x0000fff0
#define TMC4361A_FS_PER_REV_SHIFT                          4
#define TMC4361A_FS_PER_REV_FIELD                          ((RegisterField) {TMC4361A_FS_PER_REV_MASK, TMC4361A_FS_PER_REV_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_SG_MASK                                   0x00010000
#define TMC4361A_SG_SHIFT                                  16
#define TMC4361A_SG_FIELD                                  ((RegisterField) {TMC4361A_SG_MASK, TMC4361A_SG_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OT_MASK                                   0x00020000
#define TMC4361A_OT_SHIFT                                  17
#define TMC4361A_OT_FIELD                                  ((RegisterField) {TMC4361A_OT_MASK, TMC4361A_OT_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OTPW_MASK                                 0x00040000
#define TMC4361A_OTPW_SHIFT                                18
#define TMC4361A_OTPW_FIELD                                ((RegisterField) {TMC4361A_OTPW_MASK, TMC4361A_OTPW_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_S2GA_MASK                                 0x00080000
#define TMC4361A_S2GA_SHIFT                                19
#define TMC4361A_S2GA_FIELD                                ((RegisterField) {TMC4361A_S2GA_MASK, TMC4361A_S2GA_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_S2GB_MASK                                 0x00100000
#define TMC4361A_S2GB_SHIFT                                20
#define TMC4361A_S2GB_FIELD                                ((RegisterField) {TMC4361A_S2GB_MASK, TMC4361A_S2GB_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OLA_MASK                                  0x00200000
#define TMC4361A_OLA_SHIFT                                 21
#define TMC4361A_OLA_FIELD                                 ((RegisterField) {TMC4361A_OLA_MASK, TMC4361A_OLA_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OLB_MASK                                  0x00400000
#define TMC4361A_OLB_SHIFT                                 22
#define TMC4361A_OLB_FIELD                                 ((RegisterField) {TMC4361A_OLB_MASK, TMC4361A_OLB_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_STST_MASK                                 0x00800000
#define TMC4361A_STST_SHIFT                                23
#define TMC4361A_STST_FIELD                                ((RegisterField) {TMC4361A_STST_MASK, TMC4361A_STST_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_UV_SF_MASK                                0x00010000
#define TMC4361A_UV_SF_SHIFT                               16
#define TMC4361A_UV_SF_FIELD                               ((RegisterField) {TMC4361A_UV_SF_MASK, TMC4361A_UV_SF_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OCA_MASK                                  0x00080000
#define TMC4361A_OCA_SHIFT                                 19
#define TMC4361A_OCA_FIELD                                 ((RegisterField) {TMC4361A_OCA_MASK, TMC4361A_OCA_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OCB_MASK                                  0x00100000
#define TMC4361A_OCB_SHIFT                                 20
#define TMC4361A_OCB_FIELD                                 ((RegisterField) {TMC4361A_OCB_MASK, TMC4361A_OCB_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_OCHS_MASK                                 0x00800000
#define TMC4361A_OCHS_SHIFT                                23
#define TMC4361A_OCHS_FIELD                                ((RegisterField) {TMC4361A_OCHS_MASK, TMC4361A_OCHS_SHIFT, TMC4361A_STEP_CONF, false})
#define TMC4361A_TARGET_REACHED_MASK                       0x00000001
#define TMC4361A_TARGET_REACHED_SHIFT                      0
#define TMC4361A_TARGET_REACHED_FIELD                      ((RegisterField) {TMC4361A_TARGET_REACHED_MASK, TMC4361A_TARGET_REACHED_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_POS_COMP_REACHED_MASK                     0x00000002
#define TMC4361A_POS_COMP_REACHED_SHIFT                    1
#define TMC4361A_POS_COMP_REACHED_FIELD                    ((RegisterField) {TMC4361A_POS_COMP_REACHED_MASK, TMC4361A_POS_COMP_REACHED_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_VEL_REACHED_MASK                          0x00000004
#define TMC4361A_VEL_REACHED_SHIFT                         2
#define TMC4361A_VEL_REACHED_FIELD                         ((RegisterField) {TMC4361A_VEL_REACHED_MASK, TMC4361A_VEL_REACHED_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_VEL_STATE_00_MASK                         0x00000008
#define TMC4361A_VEL_STATE_00_SHIFT                        3
#define TMC4361A_VEL_STATE_00_FIELD                        ((RegisterField) {TMC4361A_VEL_STATE_00_MASK, TMC4361A_VEL_STATE_00_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_VEL_STATE_01_MASK                         0x00000010
#define TMC4361A_VEL_STATE_01_SHIFT                        4
#define TMC4361A_VEL_STATE_01_FIELD                        ((RegisterField) {TMC4361A_VEL_STATE_01_MASK, TMC4361A_VEL_STATE_01_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_VEL_STATE_10_MASK                         0x00000020
#define TMC4361A_VEL_STATE_10_SHIFT                        5
#define TMC4361A_VEL_STATE_10_FIELD                        ((RegisterField) {TMC4361A_VEL_STATE_10_MASK, TMC4361A_VEL_STATE_10_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_RAMP_STATE_00_MASK                        0x00000040
#define TMC4361A_RAMP_STATE_00_SHIFT                       6
#define TMC4361A_RAMP_STATE_00_FIELD                       ((RegisterField) {TMC4361A_RAMP_STATE_00_MASK, TMC4361A_RAMP_STATE_00_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_RAMP_STATE_01_MASK                        0x00000080
#define TMC4361A_RAMP_STATE_01_SHIFT                       7
#define TMC4361A_RAMP_STATE_01_FIELD                       ((RegisterField) {TMC4361A_RAMP_STATE_01_MASK, TMC4361A_RAMP_STATE_01_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_RAMP_STATE_10_MASK                        0x00000100
#define TMC4361A_RAMP_STATE_10_SHIFT                       8
#define TMC4361A_RAMP_STATE_10_FIELD                       ((RegisterField) {TMC4361A_RAMP_STATE_10_MASK, TMC4361A_RAMP_STATE_10_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_MAX_PHASE_TRAP_MASK                       0x00000200
#define TMC4361A_MAX_PHASE_TRAP_SHIFT                      9
#define TMC4361A_MAX_PHASE_TRAP_FIELD                      ((RegisterField) {TMC4361A_MAX_PHASE_TRAP_MASK, TMC4361A_MAX_PHASE_TRAP_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_FROZEN_MASK                               0x00000400
#define TMC4361A_FROZEN_SHIFT                              10
#define TMC4361A_FROZEN_FIELD                              ((RegisterField) {TMC4361A_FROZEN_MASK, TMC4361A_FROZEN_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_STOPL_EVENT_MASK                          0x00000800
#define TMC4361A_STOPL_EVENT_SHIFT                         11
#define TMC4361A_STOPL_EVENT_FIELD                         ((RegisterField) {TMC4361A_STOPL_EVENT_MASK, TMC4361A_STOPL_EVENT_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_STOPR_EVENT_MASK                          0x00001000
#define TMC4361A_STOPR_EVENT_SHIFT                         12
#define TMC4361A_STOPR_EVENT_FIELD                         ((RegisterField) {TMC4361A_STOPR_EVENT_MASK, TMC4361A_STOPR_EVENT_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_VSTOPL_ACTIVE_MASK                        0x00002000
#define TMC4361A_VSTOPL_ACTIVE_SHIFT                       13
#define TMC4361A_VSTOPL_ACTIVE_FIELD                       ((RegisterField) {TMC4361A_VSTOPL_ACTIVE_MASK, TMC4361A_VSTOPL_ACTIVE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_HOME_ERROR_MASK                           0x00008000
#define TMC4361A_HOME_ERROR_SHIFT                          15
#define TMC4361A_HOME_ERROR_FIELD                          ((RegisterField) {TMC4361A_HOME_ERROR_MASK, TMC4361A_HOME_ERROR_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_XLATCH_DONE_MASK                          0x00010000
#define TMC4361A_XLATCH_DONE_SHIFT                         16
#define TMC4361A_XLATCH_DONE_FIELD                         ((RegisterField) {TMC4361A_XLATCH_DONE_MASK, TMC4361A_XLATCH_DONE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_FS_ACTIVE_MASK                            0x00020000
#define TMC4361A_FS_ACTIVE_SHIFT                           17
#define TMC4361A_FS_ACTIVE_FIELD                           ((RegisterField) {TMC4361A_FS_ACTIVE_MASK, TMC4361A_FS_ACTIVE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_ENC_FAIL_MASK                             0x00040000
#define TMC4361A_ENC_FAIL_SHIFT                            18
#define TMC4361A_ENC_FAIL_FIELD                            ((RegisterField) {TMC4361A_ENC_FAIL_MASK, TMC4361A_ENC_FAIL_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_N_ACTIVE_MASK                             0x00080000
#define TMC4361A_N_ACTIVE_SHIFT                            19
#define TMC4361A_N_ACTIVE_FIELD                            ((RegisterField) {TMC4361A_N_ACTIVE_MASK, TMC4361A_N_ACTIVE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_ENC_DONE_MASK                             0x00100000
#define TMC4361A_ENC_DONE_SHIFT                            20
#define TMC4361A_ENC_DONE_FIELD                            ((RegisterField) {TMC4361A_ENC_DONE_MASK, TMC4361A_ENC_DONE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_SER_ENC_DATA_FAIL_MASK                    0x00200000
#define TMC4361A_SER_ENC_DATA_FAIL_SHIFT                   21
#define TMC4361A_SER_ENC_DATA_FAIL_FIELD                   ((RegisterField) {TMC4361A_SER_ENC_DATA_FAIL_MASK, TMC4361A_SER_ENC_DATA_FAIL_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_SER_DATA_DONE_MASK                        0x00800000
#define TMC4361A_SER_DATA_DONE_SHIFT                       23
#define TMC4361A_SER_DATA_DONE_FIELD                       ((RegisterField) {TMC4361A_SER_DATA_DONE_MASK, TMC4361A_SER_DATA_DONE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_SERIAL_ENC_FLAGS_MASK                     0x01000000
#define TMC4361A_SERIAL_ENC_FLAGS_SHIFT                    24
#define TMC4361A_SERIAL_ENC_FLAGS_FIELD                    ((RegisterField) {TMC4361A_SERIAL_ENC_FLAGS_MASK, TMC4361A_SERIAL_ENC_FLAGS_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_COVER_DONE_MASK                           0x02000000
#define TMC4361A_COVER_DONE_SHIFT                          25
#define TMC4361A_COVER_DONE_FIELD                          ((RegisterField) {TMC4361A_COVER_DONE_MASK, TMC4361A_COVER_DONE_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_ENC_VEL0_MASK                             0x04000000
#define TMC4361A_ENC_VEL0_SHIFT                            26
#define TMC4361A_ENC_VEL0_FIELD                            ((RegisterField) {TMC4361A_ENC_VEL0_MASK, TMC4361A_ENC_VEL0_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_CL_MAX_MASK                               0x08000000
#define TMC4361A_CL_MAX_SHIFT                              27
#define TMC4361A_CL_MAX_FIELD                              ((RegisterField) {TMC4361A_CL_MAX_MASK, TMC4361A_CL_MAX_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_CL_FIT_MASK                               0x10000000
#define TMC4361A_CL_FIT_SHIFT                              28
#define TMC4361A_CL_FIT_FIELD                              ((RegisterField) {TMC4361A_CL_FIT_MASK, TMC4361A_CL_FIT_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_MOTOR_EV_MASK                             0x40000000
#define TMC4361A_MOTOR_EV_SHIFT                            30
#define TMC4361A_MOTOR_EV_FIELD                            ((RegisterField) {TMC4361A_MOTOR_EV_MASK, TMC4361A_MOTOR_EV_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_RST_EV_MASK                               0x80000000
#define TMC4361A_RST_EV_SHIFT                              31
#define TMC4361A_RST_EV_FIELD                              ((RegisterField) {TMC4361A_RST_EV_MASK, TMC4361A_RST_EV_SHIFT, TMC4361A_SPI_STATUS_SELECTION, false})
#define TMC4361A_TARGET_REACHED_F_MASK                     0x00000001
#define TMC4361A_TARGET_REACHED_F_SHIFT                    0
#define TMC4361A_TARGET_REACHED_F_FIELD                    ((RegisterField) {TMC4361A_TARGET_REACHED_F_MASK, TMC4361A_TARGET_REACHED_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_POS_COMP_REACHED_F_MASK                   0x00000002
#define TMC4361A_POS_COMP_REACHED_F_SHIFT                  1
#define TMC4361A_POS_COMP_REACHED_F_FIELD                  ((RegisterField) {TMC4361A_POS_COMP_REACHED_F_MASK, TMC4361A_POS_COMP_REACHED_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_VEL_REACHED_F_MASK                        0x00000004
#define TMC4361A_VEL_REACHED_F_SHIFT                       2
#define TMC4361A_VEL_REACHED_F_FIELD                       ((RegisterField) {TMC4361A_VEL_REACHED_F_MASK, TMC4361A_VEL_REACHED_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_VEL_STATE_F_MASK                          0x00000018
#define TMC4361A_VEL_STATE_F_SHIFT                         3
#define TMC4361A_VEL_STATE_F_FIELD                         ((RegisterField) {TMC4361A_VEL_STATE_F_MASK, TMC4361A_VEL_STATE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_RAMP_STATE_F_MASK                         0x00000060
#define TMC4361A_RAMP_STATE_F_SHIFT                        5
#define TMC4361A_RAMP_STATE_F_FIELD                        ((RegisterField) {TMC4361A_RAMP_STATE_F_MASK, TMC4361A_RAMP_STATE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_STOPL_ACTIVE_F_MASK                       0x00000080
#define TMC4361A_STOPL_ACTIVE_F_SHIFT                      7
#define TMC4361A_STOPL_ACTIVE_F_FIELD                      ((RegisterField) {TMC4361A_STOPL_ACTIVE_F_MASK, TMC4361A_STOPL_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_STOPR_ACTIVE_F_MASK                       0x00000100
#define TMC4361A_STOPR_ACTIVE_F_SHIFT                      8
#define TMC4361A_STOPR_ACTIVE_F_FIELD                      ((RegisterField) {TMC4361A_STOPR_ACTIVE_F_MASK, TMC4361A_STOPR_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_VSTOPL_ACTIVE_F_MASK                      0x00000200
#define TMC4361A_VSTOPL_ACTIVE_F_SHIFT                     9
#define TMC4361A_VSTOPL_ACTIVE_F_FIELD                     ((RegisterField) {TMC4361A_VSTOPL_ACTIVE_F_MASK, TMC4361A_VSTOPL_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_VSTOPR_ACTIVE_F_MASK                      0x00000400
#define TMC4361A_VSTOPR_ACTIVE_F_SHIFT                     10
#define TMC4361A_VSTOPR_ACTIVE_F_FIELD                     ((RegisterField) {TMC4361A_VSTOPR_ACTIVE_F_MASK, TMC4361A_VSTOPR_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_ACTIVE_STALL_F_MASK                       0x00000800
#define TMC4361A_ACTIVE_STALL_F_SHIFT                      11
#define TMC4361A_ACTIVE_STALL_F_FIELD                      ((RegisterField) {TMC4361A_ACTIVE_STALL_F_MASK, TMC4361A_ACTIVE_STALL_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_HOME_ERROR_F_MASK                         0x00001000
#define TMC4361A_HOME_ERROR_F_SHIFT                        12
#define TMC4361A_HOME_ERROR_F_FIELD                        ((RegisterField) {TMC4361A_HOME_ERROR_F_MASK, TMC4361A_HOME_ERROR_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_FS_ACTIVE_F_MASK                          0x00002000
#define TMC4361A_FS_ACTIVE_F_SHIFT                         13
#define TMC4361A_FS_ACTIVE_F_FIELD                         ((RegisterField) {TMC4361A_FS_ACTIVE_F_MASK, TMC4361A_FS_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_ENC_FAIL_F_MASK                           0x00004000
#define TMC4361A_ENC_FAIL_F_SHIFT                          14
#define TMC4361A_ENC_FAIL_F_FIELD                          ((RegisterField) {TMC4361A_ENC_FAIL_F_MASK, TMC4361A_ENC_FAIL_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_N_ACTIVE_F_MASK                           0x00008000
#define TMC4361A_N_ACTIVE_F_SHIFT                          15
#define TMC4361A_N_ACTIVE_F_FIELD                          ((RegisterField) {TMC4361A_N_ACTIVE_F_MASK, TMC4361A_N_ACTIVE_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_ENC_LATCH_F_MASK                          0x00010000
#define TMC4361A_ENC_LATCH_F_SHIFT                         16
#define TMC4361A_ENC_LATCH_F_FIELD                         ((RegisterField) {TMC4361A_ENC_LATCH_F_MASK, TMC4361A_ENC_LATCH_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_MULTI_CYCLE_FAIL_F___SER_ENC_VAR_F_MASK   0x00020000
#define TMC4361A_MULTI_CYCLE_FAIL_F___SER_ENC_VAR_F_SHIFT  17
#define TMC4361A_MULTI_CYCLE_FAIL_F___SER_ENC_VAR_F_FIELD  ((RegisterField) {TMC4361A_MULTI_CYCLE_FAIL_F___SER_ENC_VAR_F_MASK, TMC4361A_MULTI_CYCLE_FAIL_F___SER_ENC_VAR_F_SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_SERIAL_ENC_FLAG___MASK                    0x00100000
#define TMC4361A_SERIAL_ENC_FLAG___SHIFT                   20
#define TMC4361A_SERIAL_ENC_FLAG___FIELD                   ((RegisterField) {TMC4361A_SERIAL_ENC_FLAG___MASK, TMC4361A_SERIAL_ENC_FLAG___SHIFT, TMC4361A_STATUS, false})
#define TMC4361A_STP_LENGTH_ADD_MASK                       0x0000FFFF
#define TMC4361A_STP_LENGTH_ADD_SHIFT                      0
#define TMC4361A_STP_LENGTH_ADD_FIELD                      ((RegisterField) {TMC4361A_STP_LENGTH_ADD_MASK, TMC4361A_STP_LENGTH_ADD_SHIFT, TMC4361A_STP_LENGTH_ADD, false})
#define TMC4361A_DIR_SETUP_TIME_MASK                       0xFFFF0000
#define TMC4361A_DIR_SETUP_TIME_SHIFT                      16
#define TMC4361A_DIR_SETUP_TIME_FIELD                      ((RegisterField) {TMC4361A_DIR_SETUP_TIME_MASK, TMC4361A_DIR_SETUP_TIME_SHIFT, TMC4361A_DIR_SETUP_TIME, false})
#define TMC4361A_START_OUT_ADD_MASK                        0xFFFFFFFF
#define TMC4361A_START_OUT_ADD_SHIFT                       0
#define TMC4361A_START_OUT_ADD_FIELD                       ((RegisterField) {TMC4361A_START_OUT_ADD_MASK, TMC4361A_START_OUT_ADD_SHIFT, TMC4361A_START_OUT_ADD, false})
#define TMC4361A_GEAR_RATIO_MASK                           0xFFFFFFFF
#define TMC4361A_GEAR_RATIO_SHIFT                          0
#define TMC4361A_GEAR_RATIO_FIELD                          ((RegisterField) {TMC4361A_GEAR_RATIO_MASK, TMC4361A_GEAR_RATIO_SHIFT, TMC4361A_GEAR_RATIO, true})
#define TMC4361A_START_DELAY_MASK                          0xFFFFFFFF
#define TMC4361A_START_DELAY_SHIFT                         0
#define TMC4361A_START_DELAY_FIELD                         ((RegisterField) {TMC4361A_START_DELAY_MASK, TMC4361A_START_DELAY_SHIFT, TMC4361A_START_DELAY, false})
#define TMC4361A_CLK_GATING_DELAY_MASK                     0xFFFFFFFF
#define TMC4361A_CLK_GATING_DELAY_SHIFT                    0
#define TMC4361A_CLK_GATING_DELAY_FIELD                    ((RegisterField) {TMC4361A_CLK_GATING_DELAY_MASK, TMC4361A_CLK_GATING_DELAY_SHIFT, TMC4361A_CLK_GATING_DELAY, false})
#define TMC4361A_STDBY_DELAY_MASK                          0xFFFFFFFF
#define TMC4361A_STDBY_DELAY_SHIFT                         0
#define TMC4361A_STDBY_DELAY_FIELD                         ((RegisterField) {TMC4361A_STDBY_DELAY_MASK, TMC4361A_STDBY_DELAY_SHIFT, TMC4361A_STDBY_DELAY, false})
#define TMC4361A_FREEWHEEL_DELAY_MASK                      0xFFFFFFFF
#define TMC4361A_FREEWHEEL_DELAY_SHIFT                     0
#define TMC4361A_FREEWHEEL_DELAY_FIELD                     ((RegisterField) {TMC4361A_FREEWHEEL_DELAY_MASK, TMC4361A_FREEWHEEL_DELAY_SHIFT, TMC4361A_FREEWHEEL_DELAY, false})
#define TMC4361A_VDRV_SCALE_LIMIT_MASK                     0x00FFFFFF
#define TMC4361A_VDRV_SCALE_LIMIT_SHIFT                    0
#define TMC4361A_VDRV_SCALE_LIMIT_FIELD                    ((RegisterField) {TMC4361A_VDRV_SCALE_LIMIT_MASK, TMC4361A_VDRV_SCALE_LIMIT_SHIFT, TMC4361A_VDRV_SCALE_LIMIT, false})
#define TMC4361A_PWM_VMAX_MASK                             0x00FFFFFF
#define TMC4361A_PWM_VMAX_SHIFT                            0
#define TMC4361A_PWM_VMAX_FIELD                            ((RegisterField) {TMC4361A_PWM_VMAX_MASK, TMC4361A_PWM_VMAX_SHIFT, TMC4361A_PWM_VMAX, false})
#define TMC4361A_UP_SCALE_DELAY_MASK                       0x00FFFFFF
#define TMC4361A_UP_SCALE_DELAY_SHIFT                      0
#define TMC4361A_UP_SCALE_DELAY_FIELD                      ((RegisterField) {TMC4361A_UP_SCALE_DELAY_MASK, TMC4361A_UP_SCALE_DELAY_SHIFT, TMC4361A_UP_SCALE_DELAY, false})
#define TMC4361A_CL_UPSCALE_DELAY_MASK                     0x00FFFFFF
#define TMC4361A_CL_UPSCALE_DELAY_SHIFT                    0
#define TMC4361A_CL_UPSCALE_DELAY_FIELD                    ((RegisterField) {TMC4361A_CL_UPSCALE_DELAY_MASK, TMC4361A_CL_UPSCALE_DELAY_SHIFT, TMC4361A_CL_UPSCALE_DELAY, false})
//#define TMC4361A_UP_SCALE_dY_FIELD                      ((RegisterField) {TMC4361A_UP_SCALE_DELAY_MASK, TMC4361A_UP_SCALE_DELAY_SHIFT, TMC4361A_UP_SCALE_DELAY, false})
#define TMC4361A_HOLD_SCALE_DELAY_MASK                     0x00FFFFFF
#define TMC4361A_HOLD_SCALE_DELAY_SHIFT                    0
#define TMC4361A_HOLD_SCALE_DELAY_FIELD                    ((RegisterField) {TMC4361A_HOLD_SCALE_DELAY_MASK, TMC4361A_HOLD_SCALE_DELAY_SHIFT, TMC4361A_HOLD_SCALE_DELAY, false})
#define TMC4361A_CL_DNSCALE_DELAY_MASK                     0x00FFFFFF
#define TMC4361A_CL_DNSCALE_DELAY_SHIFT                    0
#define TMC4361A_CL_DNSCALE_DELAY_FIELD                    ((RegisterField) {TMC4361A_CL_DNSCALE_DELAY_MASK, TMC4361A_CL_DNSCALE_DELAY_SHIFT, TMC4361A_CL_DNSCALE_DELAY, false})
#define TMC4361A_DRV_SCALE_DELAY_MASK                      0x00FFFFFF
#define TMC4361A_DRV_SCALE_DELAY_SHIFT                     0
#define TMC4361A_DRV_SCALE_DELAY_FIELD                     ((RegisterField) {TMC4361A_DRV_SCALE_DELAY_MASK, TMC4361A_DRV_SCALE_DELAY_SHIFT, TMC4361A_DRV_SCALE_DELAY, false})
#define TMC4361A_BOOST_TIME_MASK                           0x00FFFFFF
#define TMC4361A_BOOST_TIME_SHIFT                          0
#define TMC4361A_BOOST_TIME_FIELD                          ((RegisterField) {TMC4361A_BOOST_TIME_MASK, TMC4361A_BOOST_TIME_SHIFT, TMC4361A_BOOST_TIME, false})
#define TMC4361A_CL_BETA_MASK                              0x000001FF
#define TMC4361A_CL_BETA_SHIFT                             0
#define TMC4361A_CL_BETA_FIELD                             ((RegisterField) {TMC4361A_CL_BETA_MASK, TMC4361A_CL_BETA_SHIFT, TMC4361A_CL ANGLES, false})
#define TMC4361A_CL_GAMMA_MASK                             0x00FF0000
#define TMC4361A_CL_GAMMA_SHIFT                            16
#define TMC4361A_CL_GAMMA_FIELD                            ((RegisterField) {TMC4361A_CL_GAMMA_MASK, TMC4361A_CL_GAMMA_SHIFT, TMC4361A_CL ANGLES, false})
#define TMC4361A_SPI_SWITCH_VEL_MASK                       0x00FFFFFF
#define TMC4361A_SPI_SWITCH_VEL_SHIFT                      0
#define TMC4361A_SPI_SWITCH_VEL_FIELD                      ((RegisterField) {TMC4361A_SPI_SWITCH_VEL_MASK, TMC4361A_SPI_SWITCH_VEL_SHIFT, TMC4361A_SPI_SWITCH_VEL, false})
#define TMC4361A_DAC_ADDR_A_MASK                           0x0000FFFF
#define TMC4361A_DAC_ADDR_A_SHIFT                          0
#define TMC4361A_DAC_ADDR_A_FIELD                          ((RegisterField) {TMC4361A_DAC_ADDR_A_MASK, TMC4361A_DAC_ADDR_A_SHIFT, TMC4361A_DAC_ADDR_A, false})
#define TMC4361A_DAC_ADDR_B_MASK                           0xFFFF0000
#define TMC4361A_DAC_ADDR_B_SHIFT                          16
#define TMC4361A_DAC_ADDR_B_FIELD                          ((RegisterField) {TMC4361A_DAC_ADDR_B_MASK, TMC4361A_DAC_ADDR_B_SHIFT, TMC4361A_DAC_ADDR_B, false})
#define TMC4361A_HOME_SAFETY_MARGIN_MASK                   0x0000FFFF
#define TMC4361A_HOME_SAFETY_MARGIN_SHIFT                  0
#define TMC4361A_HOME_SAFETY_MARGIN_FIELD                  ((RegisterField) {TMC4361A_HOME_SAFETY_MARGIN_MASK, TMC4361A_HOME_SAFETY_MARGIN_SHIFT, TMC4361A_HOME_SAFETY_MARGIN, false})
#define TMC4361A_PWM_FREQ_MASK                             0x0000FFFF
#define TMC4361A_PWM_FREQ_SHIFT                            0
#define TMC4361A_PWM_FREQ_FIELD                            ((RegisterField) {TMC4361A_PWM_FREQ_MASK, TMC4361A_PWM_FREQ_SHIFT, TMC4361A_PWM_FREQ, false})
#define TMC4361A_CHOPSYNC_DIV_MASK                         0x00000FFF
#define TMC4361A_CHOPSYNC_DIV_SHIFT                        0
#define TMC4361A_CHOPSYNC_DIV_FIELD                        ((RegisterField) {TMC4361A_CHOPSYNC_DIV_MASK, TMC4361A_CHOPSYNC_DIV_SHIFT, TMC4361A_CHOPSYNC_DIV, false})
#define TMC4361A_OPERATION_MODE_MASK                       0x00000004
#define TMC4361A_OPERATION_MODE_SHIFT                      2
#define TMC4361A_OPERATION_MODE_FIELD                      ((RegisterField) {TMC4361A_OPERATION_MODE_MASK, TMC4361A_OPERATION_MODE_SHIFT, TMC4361A_RAMPMODE, false})
#define TMC4361A_RAMP_PROFILE_MASK                         0x00000003
#define TMC4361A_RAMP_PROFILE_SHIFT                        0
#define TMC4361A_RAMP_PROFILE_FIELD                        ((RegisterField) {TMC4361A_RAMP_PROFILE_MASK, TMC4361A_RAMP_PROFILE_SHIFT, TMC4361A_RAMPMODE, false})
#define TMC4361A_XACTUAL_MASK                              0xFFFFFFFF
#define TMC4361A_XACTUAL_SHIFT                             0
#define TMC4361A_XACTUAL_FIELD                             ((RegisterField) {TMC4361A_XACTUAL_MASK, TMC4361A_XACTUAL_SHIFT, TMC4361A_XACTUAL, true})
#define TMC4361A_VACTUAL_MASK                              0xFFFFFFFF
#define TMC4361A_VACTUAL_SHIFT                             0
#define TMC4361A_VACTUAL_FIELD                             ((RegisterField) {TMC4361A_VACTUAL_MASK, TMC4361A_VACTUAL_SHIFT, TMC4361A_VACTUAL, true})
#define TMC4361A_AACTUAL_MASK                              0xFFFFFFFF
#define TMC4361A_AACTUAL_SHIFT                             0
#define TMC4361A_AACTUAL_FIELD                             ((RegisterField) {TMC4361A_AACTUAL_MASK, TMC4361A_AACTUAL_SHIFT, TMC4361A_AACTUAL, true})
#define TMC4361A_VMAX_MASK                                 0xFFFFFFFF
#define TMC4361A_VMAX_SHIFT                                0
#define TMC4361A_VMAX_FIELD                                ((RegisterField) {TMC4361A_VMAX_MASK, TMC4361A_VMAX_SHIFT, TMC4361A_VMAX, true})
#define TMC4361A_VSTART_MASK                               0x7FFFFFFF
#define TMC4361A_VSTART_SHIFT                              0
#define TMC4361A_VSTART_FIELD                              ((RegisterField) {TMC4361A_VSTART_MASK, TMC4361A_VSTART_SHIFT, TMC4361A_VSTART, false})
#define TMC4361A_VSTOP_MASK                                0x7FFFFFFF
#define TMC4361A_VSTOP_SHIFT                               0
#define TMC4361A_VSTOP_FIELD                               ((RegisterField) {TMC4361A_VSTOP_MASK, TMC4361A_VSTOP_SHIFT, TMC4361A_VSTOP, false})
#define TMC4361A_VBREAK_MASK                               0x7FFFFFFF
#define TMC4361A_VBREAK_SHIFT                              0
#define TMC4361A_VBREAK_FIELD                              ((RegisterField) {TMC4361A_VBREAK_MASK, TMC4361A_VBREAK_SHIFT, TMC4361A_VBREAK, false})
#define TMC4361A_FREQUENCY_MODE_MASK                       0x00FFFFFF
#define TMC4361A_FREQUENCY_MODE_SHIFT                      0
#define TMC4361A_FREQUENCY_MODE_FIELD                      ((RegisterField) {TMC4361A_FREQUENCY_MODE_MASK, TMC4361A_FREQUENCY_MODE_SHIFT, TMC4361A_AMAX, false})
#define TMC4361A_DIRECT_MODE_MASK                          0x00FFFFFF
#define TMC4361A_DIRECT_MODE_SHIFT                         0
#define TMC4361A_DIRECT_MODE_FIELD                         ((RegisterField) {TMC4361A_DIRECT_MODE_MASK, TMC4361A_DIRECT_MODE_SHIFT, TMC4361A_AMAX, false})
#define TMC4361A_SIGN_AACT_MASK                            0x80000000
#define TMC4361A_SIGN_AACT_SHIFT                           31
#define TMC4361A_SIGN_AACT_FIELD                           ((RegisterField) {TMC4361A_SIGN_AACT_MASK, TMC4361A_SIGN_AACT_SHIFT, TMC4361A_ASTART, false})
#define TMC4361A_CLK_FREQ_MASK                             0x01FFFFFF
#define TMC4361A_CLK_FREQ_SHIFT                            0
#define TMC4361A_CLK_FREQ_FIELD                            ((RegisterField) {TMC4361A_CLK_FREQ_MASK, TMC4361A_CLK_FREQ_SHIFT, TMC4361A_CLK_FREQ, false})
#define TMC4361A_POS_COMP_MASK                             0xFFFFFFFF
#define TMC4361A_POS_COMP_SHIFT                            0
#define TMC4361A_POS_COMP_FIELD                            ((RegisterField) {TMC4361A_POS_COMP_MASK, TMC4361A_POS_COMP_SHIFT, TMC4361A_POS_COMP, true})
#define TMC4361A_VIRT_STOP_LEFT_MASK                       0xFFFFFFFF
#define TMC4361A_VIRT_STOP_LEFT_SHIFT                      0
#define TMC4361A_VIRT_STOP_LEFT_FIELD                      ((RegisterField) {TMC4361A_VIRT_STOP_LEFT_MASK, TMC4361A_VIRT_STOP_LEFT_SHIFT, TMC4361A_VIRT_STOP_LEFT, true})
#define TMC4361A_VIRT_STOP_RIGHT_MASK                      0xFFFFFFFF
#define TMC4361A_VIRT_STOP_RIGHT_SHIFT                     0
#define TMC4361A_VIRT_STOP_RIGHT_FIELD                     ((RegisterField) {TMC4361A_VIRT_STOP_RIGHT_MASK, TMC4361A_VIRT_STOP_RIGHT_SHIFT, TMC4361A_VIRT_STOP_RIGHT, true})
#define TMC4361A_X_HOME_MASK                               0xFFFFFFFF
#define TMC4361A_X_HOME_SHIFT                              0
#define TMC4361A_X_HOME_FIELD                              ((RegisterField) {TMC4361A_X_HOME_MASK, TMC4361A_X_HOME_SHIFT, TMC4361A_X_HOME, true})
#define TMC4361A_X_LATCH_MASK                              0xFFFFFFFF
#define TMC4361A_X_LATCH_SHIFT                             0
#define TMC4361A_X_LATCH_FIELD                             ((RegisterField) {TMC4361A_X_LATCH_MASK, TMC4361A_X_LATCH_SHIFT, TMC4361A_X_LATCH, true})
#define TMC4361A_REV_CNT_MASK                              0xFFFFFFFF
#define TMC4361A_REV_CNT_SHIFT                             0
#define TMC4361A_REV_CNT_FIELD                             ((RegisterField) {TMC4361A_REV_CNT_MASK, TMC4361A_REV_CNT_SHIFT, TMC4361A_REV_CNT, true})
#define TMC4361A_X_RANGE_MASK                              0xFFFFFFFF
#define TMC4361A_X_RANGE_SHIFT                             0
#define TMC4361A_X_RANGE_FIELD                             ((RegisterField) {TMC4361A_X_RANGE_MASK, TMC4361A_X_RANGE_SHIFT, TMC4361A_X_RANGE, false})
#define TMC4361A_XTARGET_MASK                              0xFFFFFFFF
#define TMC4361A_XTARGET_SHIFT                             0
#define TMC4361A_XTARGET_FIELD                             ((RegisterField) {TMC4361A_XTARGET_MASK, TMC4361A_XTARGET_SHIFT, TMC4361A_XTARGET, true})
#define TMC4361A_X_PIPE0__XTARGET__MASK                    0xFFFFFFFF
#define TMC4361A_X_PIPE0__XTARGET__SHIFT                   0
#define TMC4361A_X_PIPE0__XTARGET__FIELD                   ((RegisterField) {TMC4361A_X_PIPE0__XTARGET__MASK, TMC4361A_X_PIPE0__XTARGET__SHIFT, TMC4361A_X_PIPE0, true})
#define TMC4361A_X_PIPE0__POS_COMP__MASK                   0xFFFFFFFF
#define TMC4361A_X_PIPE0__POS_COMP__SHIFT                  0
#define TMC4361A_X_PIPE0__POS_COMP__FIELD                  ((RegisterField) {TMC4361A_X_PIPE0__POS_COMP__MASK, TMC4361A_X_PIPE0__POS_COMP__SHIFT, TMC4361A_X_PIPE0, true})
#define TMC4361A_X_PIPE0__GEAR_RATIO__MASK                 0xFFFFFFFF
#define TMC4361A_X_PIPE0__GEAR_RATIO__SHIFT                0
#define TMC4361A_X_PIPE0__GEAR_RATIO__FIELD                ((RegisterField) {TMC4361A_X_PIPE0__GEAR_RATIO__MASK, TMC4361A_X_PIPE0__GEAR_RATIO__SHIFT, TMC4361A_X_PIPE0, true})
#define TMC4361A_X_PIPE0__GENERAL_CONF__MASK               0xFFFFFFFF
#define TMC4361A_X_PIPE0__GENERAL_CONF__SHIFT              0
#define TMC4361A_X_PIPE0__GENERAL_CONF__FIELD              ((RegisterField) {TMC4361A_X_PIPE0__GENERAL_CONF__MASK, TMC4361A_X_PIPE0__GENERAL_CONF__SHIFT, TMC4361A_X_PIPE0, false})
#define TMC4361A_X_PIPE1__XTARGET__MASK                    0xFFFFFFFF
#define TMC4361A_X_PIPE1__XTARGET__SHIFT                   0
#define TMC4361A_X_PIPE1__XTARGET__FIELD                   ((RegisterField) {TMC4361A_X_PIPE1__XTARGET__MASK, TMC4361A_X_PIPE1__XTARGET__SHIFT, TMC4361A_X_PIPE1, true})
#define TMC4361A_X_PIPE1__POS_COMP__MASK                   0xFFFFFFFF
#define TMC4361A_X_PIPE1__POS_COMP__SHIFT                  0
#define TMC4361A_X_PIPE1__POS_COMP__FIELD                  ((RegisterField) {TMC4361A_X_PIPE1__POS_COMP__MASK, TMC4361A_X_PIPE1__POS_COMP__SHIFT, TMC4361A_X_PIPE1, true})
#define TMC4361A_X_PIPE1__GEAR_RATIO__MASK                 0xFFFFFFFF
#define TMC4361A_X_PIPE1__GEAR_RATIO__SHIFT                0
#define TMC4361A_X_PIPE1__GEAR_RATIO__FIELD                ((RegisterField) {TMC4361A_X_PIPE1__GEAR_RATIO__MASK, TMC4361A_X_PIPE1__GEAR_RATIO__SHIFT, TMC4361A_X_PIPE1, true})
#define TMC4361A_X_PIPE1__GENERAL_CONF__MASK               0xFFFFFFFF
#define TMC4361A_X_PIPE1__GENERAL_CONF__SHIFT              0
#define TMC4361A_X_PIPE1__GENERAL_CONF__FIELD              ((RegisterField) {TMC4361A_X_PIPE1__GENERAL_CONF__MASK, TMC4361A_X_PIPE1__GENERAL_CONF__SHIFT, TMC4361A_X_PIPE1, false})
#define TMC4361A_X_PIPE2_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE2_SHIFT                             0
#define TMC4361A_X_PIPE2_FIELD                             ((RegisterField) {TMC4361A_X_PIPE2_MASK, TMC4361A_X_PIPE2_SHIFT, TMC4361A_X_PIPE2, true})
#define TMC4361A_X_PIPE3_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE3_SHIFT                             0
#define TMC4361A_X_PIPE3_FIELD                             ((RegisterField) {TMC4361A_X_PIPE3_MASK, TMC4361A_X_PIPE3_SHIFT, TMC4361A_X_PIPE3, true})
#define TMC4361A_X_PIPE4_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE4_SHIFT                             0
#define TMC4361A_X_PIPE4_FIELD                             ((RegisterField) {TMC4361A_X_PIPE4_MASK, TMC4361A_X_PIPE4_SHIFT, TMC4361A_X_PIPE4, true})
#define TMC4361A_X_PIPE5_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE5_SHIFT                             0
#define TMC4361A_X_PIPE5_FIELD                             ((RegisterField) {TMC4361A_X_PIPE5_MASK, TMC4361A_X_PIPE5_SHIFT, TMC4361A_X_PIPE5, true})
#define TMC4361A_X_PIPE6_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE6_SHIFT                             0
#define TMC4361A_X_PIPE6_FIELD                             ((RegisterField) {TMC4361A_X_PIPE6_MASK, TMC4361A_X_PIPE6_SHIFT, TMC4361A_X_PIPE6, true})
#define TMC4361A_X_PIPE7_MASK                              0xFFFFFFFF
#define TMC4361A_X_PIPE7_SHIFT                             0
#define TMC4361A_X_PIPE7_FIELD                             ((RegisterField) {TMC4361A_X_PIPE7_MASK, TMC4361A_X_PIPE7_SHIFT, TMC4361A_X_PIPE7, true})
#define TMC4361A_SH_REG0_VMAX_MASK                         0xFFFFFFFF
#define TMC4361A_SH_REG0_VMAX_SHIFT                        0
#define TMC4361A_SH_REG0_VMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG0_VMAX_MASK, TMC4361A_SH_REG0_VMAX_SHIFT, TMC4361A_SH_REG0, true})
#define TMC4361A_SH_REG1_AMAX_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG1_AMAX_SHIFT                        0
#define TMC4361A_SH_REG1_AMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG1_AMAX_MASK, TMC4361A_SH_REG1_AMAX_SHIFT, TMC4361A_SH_REG1, false})
#define TMC4361A_SH_REG2_DMAX_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG2_DMAX_SHIFT                        0
#define TMC4361A_SH_REG2_DMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG2_DMAX_MASK, TMC4361A_SH_REG2_DMAX_SHIFT, TMC4361A_SH_REG2, false})
#define TMC4361A_SH_REG3_ASTART_MASK                       0x00FFFFFF
#define TMC4361A_SH_REG3_ASTART_SHIFT                      0
#define TMC4361A_SH_REG3_ASTART_FIELD                      ((RegisterField) {TMC4361A_SH_REG3_ASTART_MASK, TMC4361A_SH_REG3_ASTART_SHIFT, TMC4361A_SH_REG3, false})
#define TMC4361A_SH_REG3_BOW1_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG3_BOW1_SHIFT                        0
#define TMC4361A_SH_REG3_BOW1_FIELD                        ((RegisterField) {TMC4361A_SH_REG3_BOW1_MASK, TMC4361A_SH_REG3_BOW1_SHIFT, TMC4361A_SH_REG3, false})
#define TMC4361A_SH_REG4_DFINAL_MASK                       0x00FFFFFF
#define TMC4361A_SH_REG4_DFINAL_SHIFT                      0
#define TMC4361A_SH_REG4_DFINAL_FIELD                      ((RegisterField) {TMC4361A_SH_REG4_DFINAL_MASK, TMC4361A_SH_REG4_DFINAL_SHIFT, TMC4361A_SH_REG4, false})
#define TMC4361A_SH_REG4_BOW2_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG4_BOW2_SHIFT                        0
#define TMC4361A_SH_REG4_BOW2_FIELD                        ((RegisterField) {TMC4361A_SH_REG4_BOW2_MASK, TMC4361A_SH_REG4_BOW2_SHIFT, TMC4361A_SH_REG4, false})
#define TMC4361A_SH_REG5_VBREAK_MASK                       0x7FFFFFFF
#define TMC4361A_SH_REG5_VBREAK_SHIFT                      0
#define TMC4361A_SH_REG5_VBREAK_FIELD                      ((RegisterField) {TMC4361A_SH_REG5_VBREAK_MASK, TMC4361A_SH_REG5_VBREAK_SHIFT, TMC4361A_SH_REG5, false})
#define TMC4361A_SH_REG5_BOW3_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG5_BOW3_SHIFT                        0
#define TMC4361A_SH_REG5_BOW3_FIELD                        ((RegisterField) {TMC4361A_SH_REG5_BOW3_MASK, TMC4361A_SH_REG5_BOW3_SHIFT, TMC4361A_SH_REG5, false})
#define TMC4361A_SH_REG6_VSTART_MASK                       0x7FFFFFFF
#define TMC4361A_SH_REG6_VSTART_SHIFT                      0
#define TMC4361A_SH_REG6_VSTART_FIELD                      ((RegisterField) {TMC4361A_SH_REG6_VSTART_MASK, TMC4361A_SH_REG6_VSTART_SHIFT, TMC4361A_SH_REG6, false})
#define TMC4361A_SH_REG6_BOW4_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG6_BOW4_SHIFT                        0
#define TMC4361A_SH_REG6_BOW4_FIELD                        ((RegisterField) {TMC4361A_SH_REG6_BOW4_MASK, TMC4361A_SH_REG6_BOW4_SHIFT, TMC4361A_SH_REG6, false})
#define TMC4361A_SH_REG6_VSTOP_MASK                        0x7FFFFFFF
#define TMC4361A_SH_REG6_VSTOP_SHIFT                       0
#define TMC4361A_SH_REG6_VSTOP_FIELD                       ((RegisterField) {TMC4361A_SH_REG6_VSTOP_MASK, TMC4361A_SH_REG6_VSTOP_SHIFT, TMC4361A_SH_REG6, false})
#define TMC4361A_SH_REG7_VSTOP_MASK                        0xFFFFFFFF
#define TMC4361A_SH_REG7_VSTOP_SHIFT                       0
#define TMC4361A_SH_REG7_VSTOP_FIELD                       ((RegisterField) {TMC4361A_SH_REG7_VSTOP_MASK, TMC4361A_SH_REG7_VSTOP_SHIFT, TMC4361A_SH_REG7, false})
#define TMC4361A_SH_REG7_VMAX_MASK                         0xFFFFFFFF
#define TMC4361A_SH_REG7_VMAX_SHIFT                        0
#define TMC4361A_SH_REG7_VMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG7_VMAX_MASK, TMC4361A_SH_REG7_VMAX_SHIFT, TMC4361A_SH_REG7, true})
#define TMC4361A_SH_REG8_BOW1_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG8_BOW1_SHIFT                        0
#define TMC4361A_SH_REG8_BOW1_FIELD                        ((RegisterField) {TMC4361A_SH_REG8_BOW1_MASK, TMC4361A_SH_REG8_BOW1_SHIFT, TMC4361A_SH_REG8, false})
#define TMC4361A_SH_REG8_AMAX_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG8_AMAX_SHIFT                        0
#define TMC4361A_SH_REG8_AMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG8_AMAX_MASK, TMC4361A_SH_REG8_AMAX_SHIFT, TMC4361A_SH_REG8, false})
#define TMC4361A_SH_REG9_BOW2_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG9_BOW2_SHIFT                        0
#define TMC4361A_SH_REG9_BOW2_FIELD                        ((RegisterField) {TMC4361A_SH_REG9_BOW2_MASK, TMC4361A_SH_REG9_BOW2_SHIFT, TMC4361A_SH_REG9, false})
#define TMC4361A_SH_REG9_DMAX_MASK                         0x00FFFFFF
#define TMC4361A_SH_REG9_DMAX_SHIFT                        0
#define TMC4361A_SH_REG9_DMAX_FIELD                        ((RegisterField) {TMC4361A_SH_REG9_DMAX_MASK, TMC4361A_SH_REG9_DMAX_SHIFT, TMC4361A_SH_REG9, false})
#define TMC4361A_SH_REG10_BOW3_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG10_BOW3_SHIFT                       0
#define TMC4361A_SH_REG10_BOW3_FIELD                       ((RegisterField) {TMC4361A_SH_REG10_BOW3_MASK, TMC4361A_SH_REG10_BOW3_SHIFT, TMC4361A_SH_REG10, false})
#define TMC4361A_SH_REG10_BOW1_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG10_BOW1_SHIFT                       0
#define TMC4361A_SH_REG10_BOW1_FIELD                       ((RegisterField) {TMC4361A_SH_REG10_BOW1_MASK, TMC4361A_SH_REG10_BOW1_SHIFT, TMC4361A_SH_REG10, false})
#define TMC4361A_SH_REG10_ASTART_MASK                      0x00FFFFFF
#define TMC4361A_SH_REG10_ASTART_SHIFT                     0
#define TMC4361A_SH_REG10_ASTART_FIELD                     ((RegisterField) {TMC4361A_SH_REG10_ASTART_MASK, TMC4361A_SH_REG10_ASTART_SHIFT, TMC4361A_SH_REG10, false})
#define TMC4361A_SH_REG11_BOW4_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG11_BOW4_SHIFT                       0
#define TMC4361A_SH_REG11_BOW4_FIELD                       ((RegisterField) {TMC4361A_SH_REG11_BOW4_MASK, TMC4361A_SH_REG11_BOW4_SHIFT, TMC4361A_SH_REG11, false})
#define TMC4361A_SH_REG11_BOW2_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG11_BOW2_SHIFT                       0
#define TMC4361A_SH_REG11_BOW2_FIELD                       ((RegisterField) {TMC4361A_SH_REG11_BOW2_MASK, TMC4361A_SH_REG11_BOW2_SHIFT, TMC4361A_SH_REG11, false})
#define TMC4361A_SH_REG11_DFINAL_MASK                      0x00FFFFFF
#define TMC4361A_SH_REG11_DFINAL_SHIFT                     0
#define TMC4361A_SH_REG11_DFINAL_FIELD                     ((RegisterField) {TMC4361A_SH_REG11_DFINAL_MASK, TMC4361A_SH_REG11_DFINAL_SHIFT, TMC4361A_SH_REG11, false})
#define TMC4361A_SH_REG12_BOW3_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG12_BOW3_SHIFT                       0
#define TMC4361A_SH_REG12_BOW3_FIELD                       ((RegisterField) {TMC4361A_SH_REG12_BOW3_MASK, TMC4361A_SH_REG12_BOW3_SHIFT, TMC4361A_SH_REG12, false})
#define TMC4361A_SH_REG12_VBREAK_MASK                      0x7FFFFFFF
#define TMC4361A_SH_REG12_VBREAK_SHIFT                     0
#define TMC4361A_SH_REG12_VBREAK_FIELD                     ((RegisterField) {TMC4361A_SH_REG12_VBREAK_MASK, TMC4361A_SH_REG12_VBREAK_SHIFT, TMC4361A_SH_REG12, false})
#define TMC4361A_SH_REG13_BOW4_MASK                        0x00FFFFFF
#define TMC4361A_SH_REG13_BOW4_SHIFT                       0
#define TMC4361A_SH_REG13_BOW4_FIELD                       ((RegisterField) {TMC4361A_SH_REG13_BOW4_MASK, TMC4361A_SH_REG13_BOW4_SHIFT, TMC4361A_SH_REG13, false})
#define TMC4361A_SH_REG13_VSTART_MASK                      0x7FFFFFFF
#define TMC4361A_SH_REG13_VSTART_SHIFT                     0
#define TMC4361A_SH_REG13_VSTART_FIELD                     ((RegisterField) {TMC4361A_SH_REG13_VSTART_MASK, TMC4361A_SH_REG13_VSTART_SHIFT, TMC4361A_SH_REG13, false})
#define TMC4361A_SH_REG13_VSTOP_MASK                       0x7FFFFFFF
#define TMC4361A_SH_REG13_VSTOP_SHIFT                      0
#define TMC4361A_SH_REG13_VSTOP_FIELD                      ((RegisterField) {TMC4361A_SH_REG13_VSTOP_MASK, TMC4361A_SH_REG13_VSTOP_SHIFT, TMC4361A_SH_REG13, false})
#define TMC4361A_DFREEZE_MASK                              0x00FFFFFF
#define TMC4361A_DFREEZE_SHIFT                             0
#define TMC4361A_DFREEZE_FIELD                             ((RegisterField) {TMC4361A_DFREEZE_MASK, TMC4361A_DFREEZE_SHIFT, TMC4361A_Freeze Registers, false})
#define TMC4361A_IFREEZE_MASK                              0xFF000000
#define TMC4361A_IFREEZE_SHIFT                             24
#define TMC4361A_IFREEZE_FIELD                             ((RegisterField) {TMC4361A_IFREEZE_MASK, TMC4361A_IFREEZE_SHIFT, TMC4361A_Freeze Registers, false})
#define TMC4361A_CLK_GATING_REG_MASK                       0x00000007
#define TMC4361A_CLK_GATING_REG_SHIFT                      0
#define TMC4361A_CLK_GATING_REG_FIELD                      ((RegisterField) {TMC4361A_CLK_GATING_REG_MASK, TMC4361A_CLK_GATING_REG_SHIFT, TMC4361A_CLK_GATING_REG, false})
#define TMC4361A_RESET_REG_MASK                            0xFFFFFF00
#define TMC4361A_RESET_REG_SHIFT                           8
#define TMC4361A_RESET_REG_FIELD                           ((RegisterField) {TMC4361A_RESET_REG_MASK, TMC4361A_RESET_REG_SHIFT, TMC4361A_RESET_REG, false})
#define TMC4361A_ENC_POS_MASK                              0xFFFFFFFF
#define TMC4361A_ENC_POS_SHIFT                             0
#define TMC4361A_ENC_POS_FIELD                             ((RegisterField) {TMC4361A_ENC_POS_MASK, TMC4361A_ENC_POS_SHIFT, TMC4361A_ENC_POS, true})
#define TMC4361A_ENC_LATCH_MASK                            0xFFFFFFFF
#define TMC4361A_ENC_LATCH_SHIFT                           0
#define TMC4361A_ENC_LATCH_FIELD                           ((RegisterField) {TMC4361A_ENC_LATCH_MASK, TMC4361A_ENC_LATCH_SHIFT, TMC4361A_ENC_LATCH, true})
#define TMC4361A_ENC_RESET_VAL_MASK                        0xFFFFFFFF
#define TMC4361A_ENC_RESET_VAL_SHIFT                       0
#define TMC4361A_ENC_RESET_VAL_FIELD                       ((RegisterField) {TMC4361A_ENC_RESET_VAL_MASK, TMC4361A_ENC_RESET_VAL_SHIFT, TMC4361A_ENC_RESET_VAL, true})
#define TMC4361A_ENC_POS_DEV_MASK                          0xFFFFFFFF
#define TMC4361A_ENC_POS_DEV_SHIFT                         0
#define TMC4361A_ENC_POS_DEV_FIELD                         ((RegisterField) {TMC4361A_ENC_POS_DEV_MASK, TMC4361A_ENC_POS_DEV_SHIFT, TMC4361A_ENC_POS_DEV, true})
#define TMC4361A_CL_TR_TOLERANCE_MASK                      0x7FFFFFFF
#define TMC4361A_CL_TR_TOLERANCE_SHIFT                     0
#define TMC4361A_CL_TR_TOLERANCE_FIELD                     ((RegisterField) {TMC4361A_CL_TR_TOLERANCE_MASK, TMC4361A_CL_TR_TOLERANCE_SHIFT, TMC4361A_CL_TR_TOLERANCE, false})
#define TMC4361A_ENC_POS_DEV_TOL_MASK                      0x7FFFFFFF
#define TMC4361A_ENC_POS_DEV_TOL_SHIFT                     0
#define TMC4361A_ENC_POS_DEV_TOL_FIELD                     ((RegisterField) {TMC4361A_ENC_POS_DEV_TOL_MASK, TMC4361A_ENC_POS_DEV_TOL_SHIFT, TMC4361A_ENC_POS_DEV_TOL, false})
#define TMC4361A_ENC_CONST_MASK                            0x7FFFFFFF
#define TMC4361A_ENC_CONST_SHIFT                           0
#define TMC4361A_ENC_CONST_FIELD                           ((RegisterField) {TMC4361A_ENC_CONST_MASK, TMC4361A_ENC_CONST_SHIFT, TMC4361A_ENC_CONST, false})
#define TMC4361A_ENC_IN_RES_MASK                           0x7FFFFFFF
#define TMC4361A_ENC_IN_RES_SHIFT                          0
#define TMC4361A_ENC_IN_RES_FIELD                          ((RegisterField) {TMC4361A_ENC_IN_RES_MASK, TMC4361A_ENC_IN_RES_SHIFT, TMC4361A_ENC_IN_RES, false})
#define TMC4361A_MANUAL_ENC_CONST_MASK                     0x80000000
#define TMC4361A_MANUAL_ENC_CONST_SHIFT                    31
#define TMC4361A_MANUAL_ENC_CONST_FIELD                    ((RegisterField) {TMC4361A_MANUAL_ENC_CONST_MASK, TMC4361A_MANUAL_ENC_CONST_SHIFT, TMC4361A_manual_enc_const, false})
#define TMC4361A_ENC_OUT_RES_MASK                          0x7FFFFFFF
#define TMC4361A_ENC_OUT_RES_SHIFT                         0
#define TMC4361A_ENC_OUT_RES_FIELD                         ((RegisterField) {TMC4361A_ENC_OUT_RES_MASK, TMC4361A_ENC_OUT_RES_SHIFT, TMC4361A_ENC_OUT_RES, false})
#define TMC4361A_SER_CLK_IN_HIGH_MASK                      0x0000FFFF
#define TMC4361A_SER_CLK_IN_HIGH_SHIFT                     0
#define TMC4361A_SER_CLK_IN_HIGH_FIELD                     ((RegisterField) {TMC4361A_SER_CLK_IN_HIGH_MASK, TMC4361A_SER_CLK_IN_HIGH_SHIFT, TMC4361A_SER_CLK_IN_HIGH, false})
#define TMC4361A_SER_CLK_IN_LOW_MASK                       0xFFFF0000
#define TMC4361A_SER_CLK_IN_LOW_SHIFT                      16
#define TMC4361A_SER_CLK_IN_LOW_FIELD                      ((RegisterField) {TMC4361A_SER_CLK_IN_LOW_MASK, TMC4361A_SER_CLK_IN_LOW_SHIFT, TMC4361A_SER_CLK_IN_LOW, false})
#define TMC4361A_SSI_IN_CLK_DELAY_MASK                     0x0000FFFF
#define TMC4361A_SSI_IN_CLK_DELAY_SHIFT                    0
#define TMC4361A_SSI_IN_CLK_DELAY_FIELD                    ((RegisterField) {TMC4361A_SSI_IN_CLK_DELAY_MASK, TMC4361A_SSI_IN_CLK_DELAY_SHIFT, TMC4361A_SSI_IN_CLK_DELAY, false})
#define TMC4361A_SSI_IN_WTIME_MASK                         0xFFFF0000
#define TMC4361A_SSI_IN_WTIME_SHIFT                        16
#define TMC4361A_SSI_IN_WTIME_FIELD                        ((RegisterField) {TMC4361A_SSI_IN_WTIME_MASK, TMC4361A_SSI_IN_WTIME_SHIFT, TMC4361A_SSI_IN_WTIME, false})
#define TMC4361A_SER_PTIME_MASK                            0x000FFFFF
#define TMC4361A_SER_PTIME_SHIFT                           0
#define TMC4361A_SER_PTIME_FIELD                           ((RegisterField) {TMC4361A_SER_PTIME_MASK, TMC4361A_SER_PTIME_SHIFT, TMC4361A_SER_PTIME, false})
#define TMC4361A_CL_OFFSET_MASK                            0xFFFFFFFF
#define TMC4361A_CL_OFFSET_SHIFT                           0
#define TMC4361A_CL_OFFSET_FIELD                           ((RegisterField) {TMC4361A_CL_OFFSET_MASK, TMC4361A_CL_OFFSET_SHIFT, TMC4361A_CL_OFFSET, true})
#define TMC4361A_PID_VEL_MASK                              0xFFFFFFFF
#define TMC4361A_PID_VEL_SHIFT                             0
#define TMC4361A_PID_VEL_FIELD                             ((RegisterField) {TMC4361A_PID_VEL_MASK, TMC4361A_PID_VEL_SHIFT, TMC4361A_PID_VEL, true})
#define TMC4361A_CL_VMAX_CALC_P_MASK                       0x00FFFFFF
#define TMC4361A_CL_VMAX_CALC_P_SHIFT                      0
#define TMC4361A_CL_VMAX_CALC_P_FIELD                      ((RegisterField) {TMC4361A_CL_VMAX_CALC_P_MASK, TMC4361A_CL_VMAX_CALC_P_SHIFT, TMC4361A_CL_VMAX_CALC_P, false})
#define TMC4361A_PID_P_MASK                                0x00FFFFFF
#define TMC4361A_PID_P_SHIFT                               0
#define TMC4361A_PID_P_FIELD                               ((RegisterField) {TMC4361A_PID_P_MASK, TMC4361A_PID_P_SHIFT, TMC4361A_PID_P, false})
#define TMC4361A_PID_ISUM_RD_MASK                          0xFFFFFFFF
#define TMC4361A_PID_ISUM_RD_SHIFT                         0
#define TMC4361A_PID_ISUM_RD_FIELD                         ((RegisterField) {TMC4361A_PID_ISUM_RD_MASK, TMC4361A_PID_ISUM_RD_SHIFT, TMC4361A_PID_ISUM_RD, true})
#define TMC4361A_CL_VMAX_CALC_I_MASK                       0x00FFFFFF
#define TMC4361A_CL_VMAX_CALC_I_SHIFT                      0
#define TMC4361A_CL_VMAX_CALC_I_FIELD                      ((RegisterField) {TMC4361A_CL_VMAX_CALC_I_MASK, TMC4361A_CL_VMAX_CALC_I_SHIFT, TMC4361A_CL_VMAX_CALC_I, false})
#define TMC4361A_PID_I_MASK                                0x00FFFFFF
#define TMC4361A_PID_I_SHIFT                               0
#define TMC4361A_PID_I_FIELD                               ((RegisterField) {TMC4361A_PID_I_MASK, TMC4361A_PID_I_SHIFT, TMC4361A_PID_I, false})
#define TMC4361A_CL_DELTA_P_MASK                           0x00FFFFFF
#define TMC4361A_CL_DELTA_P_SHIFT                          0
#define TMC4361A_CL_DELTA_P_FIELD                          ((RegisterField) {TMC4361A_CL_DELTA_P_MASK, TMC4361A_CL_DELTA_P_SHIFT, TMC4361A_CL_DELTA_P, false})
#define TMC4361A_PID_D_MASK                                0x00FFFFFF
#define TMC4361A_PID_D_SHIFT                               0
#define TMC4361A_PID_D_FIELD                               ((RegisterField) {TMC4361A_PID_D_MASK, TMC4361A_PID_D_SHIFT, TMC4361A_PID_D, false})
#define TMC4361A_PID_E_MASK                                0xFFFFFFFF
#define TMC4361A_PID_E_SHIFT                               0
#define TMC4361A_PID_E_FIELD                               ((RegisterField) {TMC4361A_PID_E_MASK, TMC4361A_PID_E_SHIFT, TMC4361A_PID_E, true})
#define TMC4361A_PID_I_CLIP_MASK                           0x00007FFF
#define TMC4361A_PID_I_CLIP_SHIFT                          0
#define TMC4361A_PID_I_CLIP_FIELD                          ((RegisterField) {TMC4361A_PID_I_CLIP_MASK, TMC4361A_PID_I_CLIP_SHIFT, TMC4361A_PID_I_CLIP, false})
#define TMC4361A_PID_D_CLKDIV_MASK                         0x00FF0000
#define TMC4361A_PID_D_CLKDIV_SHIFT                        16
#define TMC4361A_PID_D_CLKDIV_FIELD                        ((RegisterField) {TMC4361A_PID_D_CLKDIV_MASK, TMC4361A_PID_D_CLKDIV_SHIFT, TMC4361A_PID_D_CLKDIV, false})
#define TMC4361A_PID_DV_CLIP_MASK                          0x7FFFFFFF
#define TMC4361A_PID_DV_CLIP_SHIFT                         0
#define TMC4361A_PID_DV_CLIP_FIELD                         ((RegisterField) {TMC4361A_PID_DV_CLIP_MASK, TMC4361A_PID_DV_CLIP_SHIFT, TMC4361A_PID_DV_CLIP, false})
#define TMC4361A_CL_TOLERANCE_MASK                         0x000000FF
#define TMC4361A_CL_TOLERANCE_SHIFT                        0
#define TMC4361A_CL_TOLERANCE_FIELD                        ((RegisterField) {TMC4361A_CL_TOLERANCE_MASK, TMC4361A_CL_TOLERANCE_SHIFT, TMC4361A_CL_TOLERANCE, false})
#define TMC4361A_PID_TOLERANCE_MASK                        0x000FFFFF
#define TMC4361A_PID_TOLERANCE_SHIFT                       0
#define TMC4361A_PID_TOLERANCE_FIELD                       ((RegisterField) {TMC4361A_PID_TOLERANCE_MASK, TMC4361A_PID_TOLERANCE_SHIFT, TMC4361A_PID_TOLERANCE, false})
#define TMC4361A_FS_VEL_MASK                               0x00FFFFFF
#define TMC4361A_FS_VEL_SHIFT                              0
#define TMC4361A_FS_VEL_FIELD                              ((RegisterField) {TMC4361A_FS_VEL_MASK, TMC4361A_FS_VEL_SHIFT, TMC4361A_FS_VEL, false})
#define TMC4361A_DC_VEL_MASK                               0x00FFFFFF
#define TMC4361A_DC_VEL_SHIFT                              0
#define TMC4361A_DC_VEL_FIELD                              ((RegisterField) {TMC4361A_DC_VEL_MASK, TMC4361A_DC_VEL_SHIFT, TMC4361A_DC_VEL, false})
#define TMC4361A_CL_VMIN_EMF_MASK                          0x00FFFFFF
#define TMC4361A_CL_VMIN_EMF_SHIFT                         0
#define TMC4361A_CL_VMIN_EMF_FIELD                         ((RegisterField) {TMC4361A_CL_VMIN_EMF_MASK, TMC4361A_CL_VMIN_EMF_SHIFT, TMC4361A_CL_VMIN_EMF, false})
#define TMC4361A_DC_TIME_MASK                              0x000000FF
#define TMC4361A_DC_TIME_SHIFT                             0
#define TMC4361A_DC_TIME_FIELD                             ((RegisterField) {TMC4361A_DC_TIME_MASK, TMC4361A_DC_TIME_SHIFT, TMC4361A_DC_TIME, false})
#define TMC4361A_DC_SG_MASK                                0x0000FF00
#define TMC4361A_DC_SG_SHIFT                               8
#define TMC4361A_DC_SG_FIELD                               ((RegisterField) {TMC4361A_DC_SG_MASK, TMC4361A_DC_SG_SHIFT, TMC4361A_DC_SG, false})
#define TMC4361A_DC_BLKTIME_MASK                           0xFFFF0000
#define TMC4361A_DC_BLKTIME_SHIFT                          16
#define TMC4361A_DC_BLKTIME_FIELD                          ((RegisterField) {TMC4361A_DC_BLKTIME_MASK, TMC4361A_DC_BLKTIME_SHIFT, TMC4361A_DC_BLKTIME, false})
#define TMC4361A_CL_VADD_EMF_MASK                          0x00FFFFFF
#define TMC4361A_CL_VADD_EMF_SHIFT                         0
#define TMC4361A_CL_VADD_EMF_FIELD                         ((RegisterField) {TMC4361A_CL_VADD_EMF_MASK, TMC4361A_CL_VADD_EMF_SHIFT, TMC4361A_CL_VADD_EMF, false})
#define TMC4361A_DC_LSPTM_MASK                             0xFFFFFFFF
#define TMC4361A_DC_LSPTM_SHIFT                            0
#define TMC4361A_DC_LSPTM_FIELD                            ((RegisterField) {TMC4361A_DC_LSPTM_MASK, TMC4361A_DC_LSPTM_SHIFT, TMC4361A_DC_LSPTM, false})
#define TMC4361A_ENC_VEL_ZERO_MASK                         0x00FFFFFF
#define TMC4361A_ENC_VEL_ZERO_SHIFT                        0
#define TMC4361A_ENC_VEL_ZERO_FIELD                        ((RegisterField) {TMC4361A_ENC_VEL_ZERO_MASK, TMC4361A_ENC_VEL_ZERO_SHIFT, TMC4361A_ENC_VEL_ZERO, false})
#define TMC4361A_ENC_VMEAN_WAIT_MASK                       0x000000FF
#define TMC4361A_ENC_VMEAN_WAIT_SHIFT                      0
#define TMC4361A_ENC_VMEAN_WAIT_FIELD                      ((RegisterField) {TMC4361A_ENC_VMEAN_WAIT_MASK, TMC4361A_ENC_VMEAN_WAIT_SHIFT, TMC4361A_ENC_VMEAN_WAIT, false})
#define TMC4361A_ENC_VMEAN_FILTER_MASK                     0x00000F00
#define TMC4361A_ENC_VMEAN_FILTER_SHIFT                    8
#define TMC4361A_ENC_VMEAN_FILTER_FIELD                    ((RegisterField) {TMC4361A_ENC_VMEAN_FILTER_MASK, TMC4361A_ENC_VMEAN_FILTER_SHIFT, TMC4361A_ENC_VMEAN_FILTER, false})
#define TMC4361A_ENC_VMEAN_INT_MASK                        0xFFFF0000
#define TMC4361A_ENC_VMEAN_INT_SHIFT                       16
#define TMC4361A_ENC_VMEAN_INT_FIELD                       ((RegisterField) {TMC4361A_ENC_VMEAN_INT_MASK, TMC4361A_ENC_VMEAN_INT_SHIFT, TMC4361A_ENC_VMEAN_INT, false})
#define TMC4361A_SER_ENC_VARIATION_MASK                    0x000000FF
#define TMC4361A_SER_ENC_VARIATION_SHIFT                   0
#define TMC4361A_SER_ENC_VARIATION_FIELD                   ((RegisterField) {TMC4361A_SER_ENC_VARIATION_MASK, TMC4361A_SER_ENC_VARIATION_SHIFT, TMC4361A_SER_ENC_VARIATION, false})
#define TMC4361A_CL_CYCLE_MASK                             0xFFFF0000
#define TMC4361A_CL_CYCLE_SHIFT                            16
#define TMC4361A_CL_CYCLE_FIELD                            ((RegisterField) {TMC4361A_CL_CYCLE_MASK, TMC4361A_CL_CYCLE_SHIFT, TMC4361A_CL_CYCLE, false})
#define TMC4361A_V_ENC_MASK                                0xFFFFFFFF
#define TMC4361A_V_ENC_SHIFT                               0
#define TMC4361A_V_ENC_FIELD                               ((RegisterField) {TMC4361A_V_ENC_MASK, TMC4361A_V_ENC_SHIFT, TMC4361A_V_ENC, true})
#define TMC4361A_V_ENC_MEAN_MASK                           0xFFFFFFFF
#define TMC4361A_V_ENC_MEAN_SHIFT                          0
#define TMC4361A_V_ENC_MEAN_FIELD                          ((RegisterField) {TMC4361A_V_ENC_MEAN_MASK, TMC4361A_V_ENC_MEAN_SHIFT, TMC4361A_V_ENC_MEAN, true})
#define TMC4361A_VSTALL_LIMIT_MASK                         0x00FFFFFF
#define TMC4361A_VSTALL_LIMIT_SHIFT                        0
#define TMC4361A_VSTALL_LIMIT_FIELD                        ((RegisterField) {TMC4361A_VSTALL_LIMIT_MASK, TMC4361A_VSTALL_LIMIT_SHIFT, TMC4361A_VSTALL_LIMIT, false})
#define TMC4361A_ADDR_TO_ENC_MASK                          0xFFFFFFFF
#define TMC4361A_ADDR_TO_ENC_SHIFT                         0
#define TMC4361A_ADDR_TO_ENC_FIELD                         ((RegisterField) {TMC4361A_ADDR_TO_ENC_MASK, TMC4361A_ADDR_TO_ENC_SHIFT, TMC4361A_ADDR_TO_ENC, false})
#define TMC4361A_DATA_TO_ENC_MASK                          0xFFFFFFFF
#define TMC4361A_DATA_TO_ENC_SHIFT                         0
#define TMC4361A_DATA_TO_ENC_FIELD                         ((RegisterField) {TMC4361A_DATA_TO_ENC_MASK, TMC4361A_DATA_TO_ENC_SHIFT, TMC4361A_DATA_TO_ENC, false})
#define TMC4361A_ADDR_FROM_ENC_MASK                        0xFFFFFFFF
#define TMC4361A_ADDR_FROM_ENC_SHIFT                       0
#define TMC4361A_ADDR_FROM_ENC_FIELD                       ((RegisterField) {TMC4361A_ADDR_FROM_ENC_MASK, TMC4361A_ADDR_FROM_ENC_SHIFT, TMC4361A_ADDR_FROM_ENC, false})
#define TMC4361A_DATA_FROM_ENC_MASK                        0xFFFFFFFF
#define TMC4361A_DATA_FROM_ENC_SHIFT                       0
#define TMC4361A_DATA_FROM_ENC_FIELD                       ((RegisterField) {TMC4361A_DATA_FROM_ENC_MASK, TMC4361A_DATA_FROM_ENC_SHIFT, TMC4361A_DATA_FROM_ENC, false})
#define TMC4361A_POLLING_STATUS_MASK                       0xFFFFFFFF
#define TMC4361A_POLLING_STATUS_SHIFT                      0
#define TMC4361A_POLLING_STATUS_FIELD                      ((RegisterField) {TMC4361A_POLLING_STATUS_MASK, TMC4361A_POLLING_STATUS_SHIFT, TMC4361A_POLLING_STATUS, false})
#define TMC4361A_COVER_LOW_MASK                            0xFFFFFFFF
#define TMC4361A_COVER_LOW_SHIFT                           0
#define TMC4361A_COVER_LOW_FIELD                           ((RegisterField) {TMC4361A_COVER_LOW_MASK, TMC4361A_COVER_LOW_SHIFT, TMC4361A_COVER_LOW, false})
#define TMC4361A_POLLING_REG_GSTAT_MASK                    0xF0000000
#define TMC4361A_POLLING_REG_GSTAT_SHIFT                   28
#define TMC4361A_POLLING_REG_GSTAT_FIELD                   ((RegisterField) {TMC4361A_POLLING_REG_GSTAT_MASK, TMC4361A_POLLING_REG_GSTAT_SHIFT, TMC4361A_POLLING_REG_GSTAT, false})
#define TMC4361A_POLLING_REG_PWM_SCALE_MASK                0x0FF00000
#define TMC4361A_POLLING_REG_PWM_SCALE_SHIFT               20
#define TMC4361A_POLLING_REG_PWM_SCALE_FIELD               ((RegisterField) {TMC4361A_POLLING_REG_PWM_SCALE_MASK, TMC4361A_POLLING_REG_PWM_SCALE_SHIFT, TMC4361A_POLLING_REG_PWM_SCALE, false})
#define TMC4361A_POLLING_REG_LOST_STEPS_MASK               0xFFFFFFFF
#define TMC4361A_POLLING_REG_LOST_STEPS_SHIFT              0
#define TMC4361A_POLLING_REG_LOST_STEPS_FIELD              ((RegisterField) {TMC4361A_POLLING_REG_LOST_STEPS_MASK, TMC4361A_POLLING_REG_LOST_STEPS_SHIFT, TMC4361A_POLLING_REG_LOST_STEPS, false})
#define TMC4361A_COVER_HIGH_MASK                           0xFFFFFFFF
#define TMC4361A_COVER_HIGH_SHIFT                          0
#define TMC4361A_COVER_HIGH_FIELD                          ((RegisterField) {TMC4361A_COVER_HIGH_MASK, TMC4361A_COVER_HIGH_SHIFT, TMC4361A_COVER_HIGH, false})
#define TMC4361A_COVER_DRV_LOW_MASK                        0xFFFFFFFF
#define TMC4361A_COVER_DRV_LOW_SHIFT                       0
#define TMC4361A_COVER_DRV_LOW_FIELD                       ((RegisterField) {TMC4361A_COVER_DRV_LOW_MASK, TMC4361A_COVER_DRV_LOW_SHIFT, TMC4361A_COVER_DRV_LOW, false})
#define TMC4361A_COVER_DRV_HIGH_MASK                       0xFFFFFFFF
#define TMC4361A_COVER_DRV_HIGH_SHIFT                      0
#define TMC4361A_COVER_DRV_HIGH_FIELD                      ((RegisterField) {TMC4361A_COVER_DRV_HIGH_MASK, TMC4361A_COVER_DRV_HIGH_SHIFT, TMC4361A_COVER_DRV_HIGH, false})
#define TMC4361A_MSLUT_0_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_0_SHIFT                             0
#define TMC4361A_MSLUT_0_FIELD                             ((RegisterField) {TMC4361A_MSLUT_0_MASK, TMC4361A_MSLUT_0_SHIFT, TMC4361A_MSLUT_0, false})
#define TMC4361A_MSLUT_1_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_1_SHIFT                             0
#define TMC4361A_MSLUT_1_FIELD                             ((RegisterField) {TMC4361A_MSLUT_1_MASK, TMC4361A_MSLUT_1_SHIFT, TMC4361A_MSLUT_1, false})
#define TMC4361A_MSLUT_2_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_2_SHIFT                             0
#define TMC4361A_MSLUT_2_FIELD                             ((RegisterField) {TMC4361A_MSLUT_2_MASK, TMC4361A_MSLUT_2_SHIFT, TMC4361A_MSLUT_2, false})
#define TMC4361A_MSLUT_3_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_3_SHIFT                             0
#define TMC4361A_MSLUT_3_FIELD                             ((RegisterField) {TMC4361A_MSLUT_3_MASK, TMC4361A_MSLUT_3_SHIFT, TMC4361A_MSLUT_3, false})
#define TMC4361A_MSLUT_4_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_4_SHIFT                             0
#define TMC4361A_MSLUT_4_FIELD                             ((RegisterField) {TMC4361A_MSLUT_4_MASK, TMC4361A_MSLUT_4_SHIFT, TMC4361A_MSLUT_4, false})
#define TMC4361A_MSLUT_5_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_5_SHIFT                             0
#define TMC4361A_MSLUT_5_FIELD                             ((RegisterField) {TMC4361A_MSLUT_5_MASK, TMC4361A_MSLUT_5_SHIFT, TMC4361A_MSLUT_5, false})
#define TMC4361A_MSLUT_6_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_6_SHIFT                             0
#define TMC4361A_MSLUT_6_FIELD                             ((RegisterField) {TMC4361A_MSLUT_6_MASK, TMC4361A_MSLUT_6_SHIFT, TMC4361A_MSLUT_6, false})
#define TMC4361A_MSLUT_7_MASK                              0xFFFFFFFF
#define TMC4361A_MSLUT_7_SHIFT                             0
#define TMC4361A_MSLUT_7_FIELD                             ((RegisterField) {TMC4361A_MSLUT_7_MASK, TMC4361A_MSLUT_7_SHIFT, TMC4361A_MSLUT_7, false})
#define TMC4361A_MSLUTSEL_MASK                             0xFFFFFFFF
#define TMC4361A_MSLUTSEL_SHIFT                            0
#define TMC4361A_MSLUTSEL_FIELD                            ((RegisterField) {TMC4361A_MSLUTSEL_MASK, TMC4361A_MSLUTSEL_SHIFT, TMC4361A_MSLUTSEL, false})
#define TMC4361A_MSCNT_MASK                                0x000003FF
#define TMC4361A_MSCNT_SHIFT                               0
#define TMC4361A_MSCNT_FIELD                               ((RegisterField) {TMC4361A_MSCNT_MASK, TMC4361A_MSCNT_SHIFT, TMC4361A_MSCNT, false})
#define TMC4361A_MSOFFSET_MASK                             0x000003FF
#define TMC4361A_MSOFFSET_SHIFT                            0
#define TMC4361A_MSOFFSET_FIELD                            ((RegisterField) {TMC4361A_MSOFFSET_MASK, TMC4361A_MSOFFSET_SHIFT, TMC4361A_MSOFFSET, false})
#define TMC4361A_CURRENTA_MASK                             0x000001FF
#define TMC4361A_CURRENTA_SHIFT                            0
#define TMC4361A_CURRENTA_FIELD                            ((RegisterField) {TMC4361A_CURRENTA_MASK, TMC4361A_CURRENTA_SHIFT, TMC4361A_CURRENTA, true})
#define TMC4361A_CURRENTB_MASK                             0x01FF0000
#define TMC4361A_CURRENTB_SHIFT                            16
#define TMC4361A_CURRENTB_FIELD                            ((RegisterField) {TMC4361A_CURRENTB_MASK, TMC4361A_CURRENTB_SHIFT, TMC4361A_CURRENTB, true})
#define TMC4361A_CURRENTA_SPI_MASK                         0x000001FF
#define TMC4361A_CURRENTA_SPI_SHIFT                        0
#define TMC4361A_CURRENTA_SPI_FIELD                        ((RegisterField) {TMC4361A_CURRENTA_SPI_MASK, TMC4361A_CURRENTA_SPI_SHIFT, TMC4361A_CURRENTA_SPI, true})
#define TMC4361A_CURRENTB_SPI_MASK                         0x01FF0000
#define TMC4361A_CURRENTB_SPI_SHIFT                        16
#define TMC4361A_CURRENTB_SPI_FIELD                        ((RegisterField) {TMC4361A_CURRENTB_SPI_MASK, TMC4361A_CURRENTB_SPI_SHIFT, TMC4361A_CURRENTB_SPI, true})
#define TMC4361A_TZEROWAIT_MASK                            0xFFFFFFFF
#define TMC4361A_TZEROWAIT_SHIFT                           0
#define TMC4361A_TZEROWAIT_FIELD                           ((RegisterField) {TMC4361A_TZEROWAIT_MASK, TMC4361A_TZEROWAIT_SHIFT, TMC4361A_TZEROWAIT, false})
#define TMC4361A_SCALE_PARAM_MASK                          0x000001FF
#define TMC4361A_SCALE_PARAM_SHIFT                         0
#define TMC4361A_SCALE_PARAM_FIELD                         ((RegisterField) {TMC4361A_SCALE_PARAM_MASK, TMC4361A_SCALE_PARAM_SHIFT, TMC4361A_SCALE_PARAM, false})
#define TMC4361A_CIRCULAR_DEC_MASK                         0xFFFFFFFF
#define TMC4361A_CIRCULAR_DEC_SHIFT                        0
#define TMC4361A_CIRCULAR_DEC_FIELD                        ((RegisterField) {TMC4361A_CIRCULAR_DEC_MASK, TMC4361A_CIRCULAR_DEC_SHIFT, TMC4361A_CIRCULAR_DEC, false})
#define TMC4361A_ENC_COMP_XOFFSET_MASK                     0x0000FFFF
#define TMC4361A_ENC_COMP_XOFFSET_SHIFT                    0
#define TMC4361A_ENC_COMP_XOFFSET_FIELD                    ((RegisterField) {TMC4361A_ENC_COMP_XOFFSET_MASK, TMC4361A_ENC_COMP_XOFFSET_SHIFT, TMC4361A_ENC_COMP_XOFFSET, false})
#define TMC4361A_ENC_COMP_YOFFSET_MASK                     0x00FF0000
#define TMC4361A_ENC_COMP_YOFFSET_SHIFT                    16
#define TMC4361A_ENC_COMP_YOFFSET_FIELD                    ((RegisterField) {TMC4361A_ENC_COMP_YOFFSET_MASK, TMC4361A_ENC_COMP_YOFFSET_SHIFT, TMC4361A_ENC_COMP_YOFFSET, true})
#define TMC4361A_START_SIN_MASK                            0x000000FF
#define TMC4361A_START_SIN_SHIFT                           0
#define TMC4361A_START_SIN_FIELD                           ((RegisterField) {TMC4361A_START_SIN_MASK, TMC4361A_START_SIN_SHIFT, TMC4361A_START_SIN, false})
#define TMC4361A_START_SIN90_120_MASK                      0x00FF0000
#define TMC4361A_START_SIN90_120_SHIFT                     16
#define TMC4361A_START_SIN90_120_FIELD                     ((RegisterField) {TMC4361A_START_SIN90_120_MASK, TMC4361A_START_SIN90_120_SHIFT, TMC4361A_START_SIN90_120, false})
#define TMC4361A_DAC_OFFSET_MASK                           0xFF000000
#define TMC4361A_DAC_OFFSET_SHIFT                          24
#define TMC4361A_DAC_OFFSET_FIELD                          ((RegisterField) {TMC4361A_DAC_OFFSET_MASK, TMC4361A_DAC_OFFSET_SHIFT, TMC4361A_DAC_OFFSET, false})
#define TMC4361A_VERSION_NO_MASK                           0x0000000F
#define TMC4361A_VERSION_NO_SHIFT                          0
#define TMC4361A_VERSION_NO_FIELD                          ((RegisterField) {TMC4361A_VERSION_NO_MASK, TMC4361A_VERSION_NO_SHIFT, TMC4361A_VERSION_NO, true})

#endif /* TMC4361A_HW_ABSTRACTION_H */
