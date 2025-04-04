/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC5272_HW_ABSTRACTION
#define TMC5272_HW_ABSTRACTION

// Constants
#define TMC5272_REGISTER_COUNT   128
#define TMC5272_MOTORS           2
#define TMC5272_WRITE_BIT        0x80
#define TMC5272_ADDRESS_MASK     0x7F
#define TMC5272_MAX_VELOCITY     8388096
#define TMC5272_MAX_ACCELERATION UINTN_MAX

// Ramp modes (Register TMC5272_RAMPMODE)
#define TMC5272_MODE_POSITION  0
#define TMC5272_MODE_VELPOS    1
#define TMC5272_MODE_VELNEG    2
#define TMC5272_MODE_HOLD      3

// Registers in TMC5272

#define MOTOR_ADDR(m)      (0x35 * m)

#define TMC5272_GCONF                0x00
#define TMC5272_GSTAT                0x01
#define TMC5272_IFCNT                0x02
#define TMC5272_SLAVECONF            0x03
#define TMC5272_IOIN                 0x04
#define TMC5272_DRV_CONF             0x05
#define TMC5272_GLOBAL_SCALER        0x06
#define TMC5272_RAMPMODE             0x07
#define TMC5272_MSLUT_ADDR           0x08
#define TMC5272_MSLUT_DATA           0x09

										 // motor = 0       motor = 1
#define TMC5272_X_COMPARE(motor)          (0x10 + MOTOR_ADDR(motor))      //      0x10            0x45
#define TMC5272_X_COMPARE_REPEAT(motor)   (0x11 + MOTOR_ADDR(motor))      //      0x11            0x46
#define TMC5272_IHOLD_IRUN(motor)         (0x12 + MOTOR_ADDR(motor))      //      0x12            0x47
#define TMC5272_TPOWERDOWN(motor)         (0x13 + MOTOR_ADDR(motor))      //      0x13            0x48
#define TMC5272_TSTEP(motor)              (0x14 + MOTOR_ADDR(motor))      //      0x14            0x49
#define TMC5272_TPWMTHRS(motor)           (0x15 + MOTOR_ADDR(motor))      //      0x15            0x4A
#define TMC5272_TCOOLTHRS(motor)          (0x16 + MOTOR_ADDR(motor))      //      0x16            0x4B
#define TMC5272_THIGH(motor)              (0x17 + MOTOR_ADDR(motor))      //      0x17            0x4C
#define TMC5272_XACTUAL(motor)            (0x18 + MOTOR_ADDR(motor))      //      0x18            0x4D
#define TMC5272_VACTUAL(motor)            (0x19 + MOTOR_ADDR(motor))      //      0x19            0x4E
#define TMC5272_AACTUAL(motor)            (0x1A + MOTOR_ADDR(motor))      //      0x1A            0x4F
#define TMC5272_VSTART(motor)             (0x1B + MOTOR_ADDR(motor))      //      0x1B            0x50
#define TMC5272_A1(motor)                 (0x1C + MOTOR_ADDR(motor))      //      0x1C            0x51
#define TMC5272_V1(motor)                 (0x1D + MOTOR_ADDR(motor))      //      0x1D            0x52
#define TMC5272_A2(motor)                 (0x1E + MOTOR_ADDR(motor))      //      0x1E            0x53
#define TMC5272_V2(motor)                 (0x1F + MOTOR_ADDR(motor))      //      0x1F            0x54
#define TMC5272_AMAX(motor)               (0x20 + MOTOR_ADDR(motor))      //      0x20            0x55
#define TMC5272_VMAX(motor)               (0x21 + MOTOR_ADDR(motor))      //      0x21            0x56
#define TMC5272_DMAX(motor)               (0x22 + MOTOR_ADDR(motor))      //      0x22            0x57
#define TMC5272_D2(motor)                 (0x23 + MOTOR_ADDR(motor))      //      0x23            0x58
#define TMC5272_D1(motor)                 (0x24 + MOTOR_ADDR(motor))      //      0x24            0x59
#define TMC5272_VSTOP(motor)              (0x25 + MOTOR_ADDR(motor))      //      0x25            0x5A
#define TMC5272_TVMAX(motor)              (0x26 + MOTOR_ADDR(motor))      //      0x26            0x5B
#define TMC5272_TZEROWAIT(motor)          (0x27 + MOTOR_ADDR(motor))      //      0x27            0x5C
#define TMC5272_XTARGET(motor)            (0x28 + MOTOR_ADDR(motor))      //      0x28            0x5D
#define TMC5272_VDCMIN(motor)             (0x29 + MOTOR_ADDR(motor))      //      0x29            0x5E
#define TMC5272_SW_MODE(motor)            (0x2A + MOTOR_ADDR(motor))      //      0x2A            0x5F
#define TMC5272_RAMP_STAT(motor)          (0x2B + MOTOR_ADDR(motor))      //      0x2B            0x60
#define TMC5272_XLATCH(motor)             (0x2C + MOTOR_ADDR(motor))      //      0x2C            0x61
#define TMC5272_POSITION_PI_CTRL(motor)   (0x2D + MOTOR_ADDR(motor))      //      0x2D            0x62
#define TMC5272_X_ENC(motor)              (0x2E + MOTOR_ADDR(motor))      //      0x2E            0x63
#define TMC5272_ENCMODE(motor)            (0x2F + MOTOR_ADDR(motor))      //      0x2F            0x64
#define TMC5272_ENC_CONST(motor)          (0x30 + MOTOR_ADDR(motor))      //      0x30            0x65
#define TMC5272_ENC_STATUS(motor)         (0x31 + MOTOR_ADDR(motor))      //      0x31            0x66
#define TMC5272_ENC_LATCH(motor)          (0x32 + MOTOR_ADDR(motor))      //      0x32            0x67
#define TMC5272_ENC_DEVIATION(motor)      (0x33 + MOTOR_ADDR(motor))      //      0x33            0x68
#define TMC5272_VIRTUAL_STOP_L(motor)     (0x34 + MOTOR_ADDR(motor))      //      0x34            0x69
#define TMC5272_VIRTUAL_STOP_R(motor)     (0x35 + MOTOR_ADDR(motor))      //      0x35            0x6A
#define TMC5272_MSCNT(motor)              (0x36 + MOTOR_ADDR(motor))      //      0x36            0x6B
#define TMC5272_MSCURACT(motor)           (0x37 + MOTOR_ADDR(motor))      //      0x37            0x6C
#define TMC5272_CHOPCONF(motor)           (0x38 + MOTOR_ADDR(motor))      //      0x38            0x6D
#define TMC5272_COOLCONF(motor)           (0x39 + MOTOR_ADDR(motor))      //      0x39            0x6E
#define TMC5272_DCCTRL(motor)             (0x3A + MOTOR_ADDR(motor))      //      0x3A            0x6F
#define TMC5272_DRV_STATUS(motor)         (0x3B + MOTOR_ADDR(motor))      //      0x3B            0x70
#define TMC5272_PWMCONF(motor)            (0x3C + MOTOR_ADDR(motor))      //      0x3C            0x71
#define TMC5272_PWM_SCALE(motor)          (0x3D + MOTOR_ADDR(motor))      //      0x3D            0x72
#define TMC5272_PWM_AUTO(motor)           (0x3E + MOTOR_ADDR(motor))      //      0x3E            0x73
#define TMC5272_SG4_THRS(motor)           (0x3F + MOTOR_ADDR(motor))      //      0x3F            0x74
#define TMC5272_SG4_RESULT(motor)         (0x40 + MOTOR_ADDR(motor))      //      0x40            0x75
#define TMC5272_SG4_IND(motor)            (0x41 + MOTOR_ADDR(motor))      //      0x41            0x76

// Register fields in TMC5272

#define TMC5272_GCONF_M0_EN_PWM_MODE_MASK                     0x00000001
#define TMC5272_GCONF_M0_EN_PWM_MODE_SHIFT                    0
#define TMC5272_GCONF_M0_EN_PWM_MODE_FIELD                    ((RegisterField) { TMC5272_GCONF_M0_EN_PWM_MODE_MASK,  TMC5272_GCONF_M0_EN_PWM_MODE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_MULTISTEP_FILT_MASK                  0x00000002
#define TMC5272_GCONF_M0_MULTISTEP_FILT_SHIFT                 1
#define TMC5272_GCONF_M0_MULTISTEP_FILT_FIELD                 ((RegisterField) { TMC5272_GCONF_M0_MULTISTEP_FILT_MASK,  TMC5272_GCONF_M0_MULTISTEP_FILT_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_SHAFT_MASK                           0x00000004
#define TMC5272_GCONF_M0_SHAFT_SHIFT                          2
#define TMC5272_GCONF_M0_SHAFT_FIELD(motor)                   ((RegisterField) { TMC5272_GCONF_M0_SHAFT_MASK,  TMC5272_GCONF_M0_SHAFT_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_DIAG0_ERROR_MASK                     0x00000008
#define TMC5272_GCONF_M0_DIAG0_ERROR_SHIFT                    3
#define TMC5272_GCONF_M0_DIAG0_ERROR_FIELD                    ((RegisterField) { TMC5272_GCONF_M0_DIAG0_ERROR_MASK,  TMC5272_GCONF_M0_DIAG0_ERROR_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG0_OTPW_MASK                         0x00000010
#define TMC5272_GCONF_DIAG0_OTPW_SHIFT                        4
#define TMC5272_GCONF_DIAG0_OTPW_FIELD                        ((RegisterField) { TMC5272_GCONF_DIAG0_OTPW_MASK,  TMC5272_GCONF_DIAG0_OTPW_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG0_STALL_STEP_MASK                   0x00000020
#define TMC5272_GCONF_DIAG0_STALL_STEP_SHIFT                  5
#define TMC5272_GCONF_DIAG0_STALL_STEP_SHIF                   ((RegisterField) { TMC5272_GCONF_DIAG0_OTPW_MASK,  TMC5272_GCONF_DIAG0_OTPW_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG1_STALL_DIR_MASK                    0x00000040
#define TMC5272_GCONF_DIAG1_STALL_DIR_SHIFT                   6
#define TMC5272_GCONF_DIAG1_STALL_DIR_FIELD                   ((RegisterField) { TMC5272_GCONF_DIAG1_STALL_DIR_MASK,  TMC5272_GCONF_DIAG1_STALL_DIR_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_DIAG1_INDEX_MASK                     0x00000080
#define TMC5272_GCONF_M0_DIAG1_INDEX_SHIFT                    7
#define TMC5272_GCONF_M0_DIAG1_INDEX_FIELD                    ((RegisterField) { TMC5272_GCONF_M0_DIAG1_INDEX_MASK,  TMC5272_GCONF_M0_DIAG1_INDEX_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG0_INT_PUSHPULL_MASK                 0x00000100
#define TMC5272_GCONF_DIAG0_INT_PUSHPULL_SHIFT                8
#define TMC5272_GCONF_DIAG0_INT_PUSHPULL_FIELD                ((RegisterField) { TMC5272_GCONF_M0_DIAG1_INDEX_MASK,  TMC5272_GCONF_M0_DIAG1_INDEX_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG1_POSCOMP_PUSHPULL_MASK             0x00000200
#define TMC5272_GCONF_DIAG1_POSCOMP_PUSHPULL_SHIFT            9
#define TMC5272_GCONF_DIAG1_POSCOMP_PUSHPULL_FIELD            ((RegisterField) { TMC5272_GCONF_DIAG1_POSCOMP_PUSHPULL_MASK,  TMC5272_GCONF_DIAG1_POSCOMP_PUSHPULL_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_SMALL_HYSTERESIS_MASK                0x00000400
#define TMC5272_GCONF_M0_SMALL_HYSTERESIS_SHIFT               10
#define TMC5272_GCONF_M0_SMALL_HYSTERESIS_FIELD               ((RegisterField) { TMC5272_GCONF_M0_SMALL_HYSTERESIS_MASK,  TMC5272_GCONF_M0_SMALL_HYSTERESIS_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_STOP_ENABLE_MASK                     0x00000800
#define TMC5272_GCONF_M0_STOP_ENABLE_SHIFT                    11
#define TMC5272_GCONF_M0_STOP_ENABLE_FIELD                    ((RegisterField) { TMC5272_GCONF_M0_STOP_ENABLE_MASK,  TMC5272_GCONF_M0_STOP_ENABLE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_DIRECT_MODE_MASK                     0x00001000
#define TMC5272_GCONF_M0_DIRECT_MODE_SHIFT                    12
#define TMC5272_GCONF_M0_DIRECT_MODE_FIELD                    ((RegisterField) { TMC5272_GCONF_M0_DIRECT_MODE_MASK,  TMC5272_GCONF_M0_DIRECT_MODE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_SD_MASK                              0x00002000
#define TMC5272_GCONF_M0_SD_SHIFT                             13
#define TMC5272_GCONF_M0_SD_FIELD                             ((RegisterField) { TMC5272_GCONF_M0_SD_MASK,  TMC5272_GCONF_M0_SD_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M0_DRV_ENN_MASK                         0x00004000
#define TMC5272_GCONF_M0_DRV_ENN_SHIFT                        14
#define TMC5272_GCONF_M0_DRV_ENN_FIELD                        ((RegisterField) { TMC5272_GCONF_M0_DRV_ENN_MASK,  TMC5272_GCONF_M0_DRV_ENN_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_EN_PWM_MODE_MASK                     0x00010000
#define TMC5272_GCONF_M1_EN_PWM_MODE_SHIFT                    16
#define TMC5272_GCONF_M1_EN_PWM_MODE_FIELD                    ((RegisterField) { TMC5272_GCONF_M1_EN_PWM_MODE_MASK,  TMC5272_GCONF_M1_EN_PWM_MODE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_MULTISTEP_FILT_MASK                  0x00020000
#define TMC5272_GCONF_M1_MULTISTEP_FILT_SHIFT                 17
#define TMC5272_GCONF_M1_MULTISTEP_FILT_FIELD                 ((RegisterField) { TMC5272_GCONF_M1_MULTISTEP_FILT_MASK,  TMC5272_GCONF_M1_MULTISTEP_FILT_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_SHAFT_MASK                           0x00040000
#define TMC5272_GCONF_M1_SHAFT_SHIFT                          18
#define TMC5272_GCONF_M1_SHAFT_FIELD                          ((RegisterField) { TMC5272_GCONF_M1_SHAFT_MASK,  TMC5272_GCONF_M1_SHAFT_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG0_INTOUT_SEL_MASK                   0x00180000
#define TMC5272_GCONF_DIAG0_INTOUT_SEL_SHIFT                  19
#define TMC5272_GCONF_DIAG0_INTOUT_SEL_FIELD                  ((RegisterField) { TMC5272_GCONF_DIAG0_INTOUT_SEL_MASK,  TMC5272_GCONF_DIAG0_INTOUT_SEL_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_DIAG1_X_COMP_SEL_MASK                   0x00600000
#define TMC5272_GCONF_DIAG1_X_COMP_SEL_SHIFT                  21
#define TMC5272_GCONF_DIAG1_X_COMP_SEL_FIELD                  ((RegisterField) { TMC5272_GCONF_DIAG1_X_COMP_SEL_MASK,  TMC5272_GCONF_DIAG1_X_COMP_SEL_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_DIAG1_INDEX_MASK                     0x00800000
#define TMC5272_GCONF_M1_DIAG1_INDEX_SHIFT                    23
#define TMC5272_GCONF_M1_DIAG1_INDEX_FIELD                    ((RegisterField) { TMC5272_GCONF_M1_DIAG1_INDEX_MASK,  TMC5272_GCONF_M1_DIAG1_INDEX_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_SMALL_HYSTERESIS_MASK                0x01000000
#define TMC5272_GCONF_M1_SMALL_HYSTERESIS_SHIFT               24
#define TMC5272_GCONF_M1_SMALL_HYSTERESIS_FIELD               ((RegisterField) { TMC5272_GCONF_M1_DIAG1_INDEX_MASK,  TMC5272_GCONF_M1_DIAG1_INDEX_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_STOP_ENABLE_MASK                     0x02000000
#define TMC5272_GCONF_M1_STOP_ENABLE_SHIFT                    25
#define TMC5272_GCONF_M1_STOP_ENABLE_FIELD                    ((RegisterField) { TMC5272_GCONF_M1_STOP_ENABLE_MASK,  TMC5272_GCONF_M1_STOP_ENABLE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_DIRECT_MODE_MASK                     0x04000000
#define TMC5272_GCONF_M1_DIRECT_MODE_SHIFT                    26
#define TMC5272_GCONF_M1_DIRECT_MODE_FIELD                    ((RegisterField) { TMC5272_GCONF_M1_DIRECT_MODE_MASK,  TMC5272_GCONF_M1_DIRECT_MODE_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_SD_MASK                              0x08000000
#define TMC5272_GCONF_M1_SD_SHIFT                             27
#define TMC5272_GCONF_M1_SD_FIELD                             ((RegisterField) { TMC5272_GCONF_M1_SD_MASK,  TMC5272_GCONF_M1_SD_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GCONF_M1_DRV_ENN_MASK                         0x10000000
#define TMC5272_GCONF_M1_DRV_ENN_SHIFT                        28
#define TMC5272_GCONF_M1_DRV_ENN_FIELD                        ((RegisterField) { TMC5272_GCONF_M1_DRV_ENN_MASK,  TMC5272_GCONF_M1_DRV_ENN_SHIFT,  TMC5272_GCONF, false })
#define TMC5272_GSTAT_RESET_MASK                              0x00000001
#define TMC5272_GSTAT_RESET_SHIFT                             0
#define TMC5272_GSTAT_RESET_FIELD                             ((RegisterField) { TMC5272_GSTAT_RESET_MASK,  TMC5272_GSTAT_RESET_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_GSTAT_M0_DRV_ERR_MASK                         0x00000002
#define TMC5272_GSTAT_M0_DRV_ERR_SHIFT                        1
#define TMC5272_GSTAT_M0_DRV_ERR_FIELD                        ((RegisterField) { TMC5272_GSTAT_M0_DRV_ERR_MASK,  TMC5272_GSTAT_M0_DRV_ERR_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_GSTAT_UV_CP_MASK                              0x00000004
#define TMC5272_GSTAT_UV_CP_SHIFT                             2
#define TMC5272_GSTAT_UV_CP_FIELD                             ((RegisterField) { TMC5272_GSTAT_UV_CP_MASK,  TMC5272_GSTAT_UV_CP_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_GSTAT_REGISTER_RESET_MASK                     0x00000008
#define TMC5272_GSTAT_REGISTER_RESET_SHIFT                    3
#define TMC5272_GSTAT_REGISTER_RESET_FIELD                    ((RegisterField) { TMC5272_GSTAT_REGISTER_RESET_MASK,  TMC5272_GSTAT_REGISTER_RESET_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_GSTAT_VM_UVLO_MASK                            0x00000010
#define TMC5272_GSTAT_VM_UVLO_SHIFT                           4
#define TMC5272_GSTAT_VM_UVLO_FIELD                           ((RegisterField) { TMC5272_GSTAT_VM_UVLO_MASK,  TMC5272_GSTAT_VM_UVLO_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_GSTAT_M1_DRV_ERR_MASK                         0x00000020
#define TMC5272_GSTAT_M1_DRV_ERR_SHIFT                        5
#define TMC5272_GSTAT_M1_DRV_ERR_FIELD                        ((RegisterField) { TMC5272_GSTAT_M1_DRV_ERR_MASK,  TMC5272_GSTAT_M1_DRV_ERR_SHIFT,  TMC5272_GSTAT, false })
#define TMC5272_IFCNT_MASK                                    0x000000FF
#define TMC5272_IFCNT_SHIFT                                   0
#define TMC5272_IFCNT_FIELD                                   ((RegisterField) { TMC5272_IFCNT_MASK,  TMC5272_IFCNT_SHIFT,  TMC5272_IFCNT, false })
#define TMC5272_SLAVECONF_SLAVEADDR_MASK                      0x000000FF
#define TMC5272_SLAVECONF_SLAVEADDR_SHIFT                     0
#define TMC5272_SLAVECONF_SLAVEADDR_FIELD                     ((RegisterField) { TMC5272_SLAVECONF_SLAVEADDR_MASK,  TMC5272_SLAVECONF_SLAVEADDR_SHIFT,  TMC5272_SLAVECONF, false })
#define TMC5272_SLAVECONF_SENDDELAY_MASK                      0x00000F00
#define TMC5272_SLAVECONF_SENDDELAY_SHIFT                     8
#define TMC5272_SLAVECONF_SENDDELAY_FIELD                     ((RegisterField) { TMC5272_SLAVECONF_SENDDELAY_MASK,  TMC5272_SLAVECONF_SENDDELAY_SHIFT,  TMC5272_SLAVECONF, false })
#define TMC5272_IOIN_ADC_TEMPERATURE_MASK                     0x000001FE
#define TMC5272_IOIN_ADC_TEMPERATURE_SHIFT                    1
#define TMC5272_IOIN_ADC_TEMPERATURE_FIELD                    ((RegisterField) { TMC5272_IOIN_ADC_TEMPERATURE_MASK,  TMC5272_IOIN_ADC_TEMPERATURE_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_ADC_EN_MASK                              0x00000200
#define TMC5272_IOIN_ADC_EN_SHIFT                             9
#define TMC5272_IOIN_ADC_EN_FIELD                             ((RegisterField) { TMC5272_IOIN_ADC_EN_MASK,  TMC5272_IOIN_ADC_EN_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_SEL_OSCILLATOR_MASK                      0x00000800
#define TMC5272_IOIN_SEL_OSCILLATOR_SHIFT                     11
#define TMC5272_IOIN_SEL_OSCILLATOR_FIELD                     ((RegisterField) { TMC5272_IOIN_SEL_OSCILLATOR_MASK,  TMC5272_IOIN_SEL_OSCILLATOR_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_EXT_RES_DET_MASK                         0x00001000
#define TMC5272_IOIN_EXT_RES_DET_SHIFT                        12
#define TMC5272_IOIN_EXT_RES_DET_FIELD                        ((RegisterField) { TMC5272_IOIN_EXT_RES_DET_MASK,  TMC5272_IOIN_EXT_RES_DET_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_OUTPUT_MASK                              0x00002000
#define TMC5272_IOIN_OUTPUT_SHIFT                             13
#define TMC5272_IOIN_OUTPUT_FIELD                             ((RegisterField) { TMC5272_IOIN_EXT_RES_DET_MASK,  TMC5272_IOIN_EXT_RES_DET_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_QSC_STATUS_MASK                          0x00008000
#define TMC5272_IOIN_QSC_STATUS_SHIFT                         15
#define TMC5272_IOIN_QSC_STATUS_FIELD                         ((RegisterField) { TMC5272_IOIN_QSC_STATUS_MASK,  TMC5272_IOIN_QSC_STATUS_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_SILICON_RV_MASK                          0x00070000
#define TMC5272_IOIN_SILICON_RV_SHIFT                         16
#define TMC5272_IOIN_SILICON_RV_FIELD                         ((RegisterField) { TMC5272_IOIN_SILICON_RV_MASK,  TMC5272_IOIN_SILICON_RV_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_IOIN_VERSION_MASK                             0xFF000000
#define TMC5272_IOIN_VERSION_SHIFT                            24
#define TMC5272_IOIN_VERSION_FIELD                            ((RegisterField) { TMC5272_IOIN_VERSION_MASK,  TMC5272_IOIN_VERSION_SHIFT,  TMC5272_IOIN, false })
#define TMC5272_DRV_CONF_FSR_M0_MASK                          0x00000003
#define TMC5272_DRV_CONF_FSR_M0_SHIFT                         0
#define TMC5272_DRV_CONF_FSR_M0_FIELD                         ((RegisterField) { TMC5272_DRV_CONF_FSR_M0_MASK,  TMC5272_DRV_CONF_FSR_M0_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_FSR_IREF_M0_MASK                     0x0000000C
#define TMC5272_DRV_CONF_FSR_IREF_M0_SHIFT                    2
#define TMC5272_DRV_CONF_FSR_IREF_M0_FIELD                         ((RegisterField) { TMC5272_DRV_CONF_FSR_IREF_M0_MASK,  TMC5272_DRV_CONF_FSR_IREF_M0_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M0_EN_EMERGENCY_DISABLE_MASK         0x00000010
#define TMC5272_DRV_CONF_M0_EN_EMERGENCY_DISABLE_SHIFT        4
#define TMC5272_DRV_CONF_M0_EN_EMERGENCY_DISABLE_FIELD        ((RegisterField) { TMC5272_DRV_CONF_M0_EN_EMERGENCY_DISABLE_MASK,  TMC5272_DRV_CONF_M0_EN_EMERGENCY_DISABLE_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M0_SEL_EM_STOP_SRC_MASK              0x00000020
#define TMC5272_DRV_CONF_M0_SEL_EM_STOP_SRC_SHIFT             5
#define TMC5272_DRV_CONF_M0_SEL_EM_STOP_SRC_FIELD             ((RegisterField) { TMC5272_DRV_CONF_M0_SEL_EM_STOP_SRC_MASK,  TMC5272_DRV_CONF_M0_SEL_EM_STOP_SRC_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_FSR_M1_MASK                          0x000000C0
#define TMC5272_DRV_CONF_FSR_M1_SHIFT                         6
#define TMC5272_DRV_CONF_FSR_M1_FIELD                         ((RegisterField) { TMC5272_DRV_CONF_FSR_M1_MASK,  TMC5272_DRV_CONF_FSR_M1_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_FSR_IREF_M1_MASK                     0x00000300
#define TMC5272_DRV_CONF_FSR_IREF_M1_SHIFT                    8
#define TMC5272_DRV_CONF_FSR_IREF_M1_FIELD                    ((RegisterField) { TMC5272_DRV_CONF_FSR_IREF_M1_MASK,  TMC5272_DRV_CONF_FSR_IREF_M1_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M1_EN_EMERGENCY_DISABLE_MASK         0x00000400
#define TMC5272_DRV_CONF_M1_EN_EMERGENCY_DISABLE_SHIFT        10
#define TMC5272_DRV_CONF_M1_EN_EMERGENCY_DISABLE1_FIELD       ((RegisterField) { TMC5272_DRV_CONF_M1_EN_EMERGENCY_DISABLE_MASK,  TMC5272_DRV_CONF_M1_EN_EMERGENCY_DISABLE_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M1_SEL_EM_STOP_SRC_MASK              0x00000800
#define TMC5272_DRV_CONF_M1_SEL_EM_STOP_SRC_SHIFT             11
#define TMC5272_DRV_CONF_M1_SEL_EM_STOP_SRC_FIELD             ((RegisterField) { TMC5272_DRV_CONF_M1_SEL_EM_STOP_SRC_MASK,  TMC5272_DRV_CONF_M1_SEL_EM_STOP_SRC_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M0_STANDSTILL_TIME_MASK              0x00070000
#define TMC5272_DRV_CONF_M0_STANDSTILL_TIME_SHIFT             16
#define TMC5272_DRV_CONF_M0_STANDSTILL_TIME_FIELD             ((RegisterField) { TMC5272_DRV_CONF_M0_STANDSTILL_TIME_MASK,  TMC5272_DRV_CONF_M0_STANDSTILL_TIME_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_DRV_CONF_M1_STANDSTILL_TIME_MASK              0x00700000
#define TMC5272_DRV_CONF_M1_STANDSTILL_TIME_SHIFT             20
#define TMC5272_DRV_CONF_M1_STANDSTILL_TIME_FIELD             ((RegisterField) { TMC5272_DRV_CONF_M1_STANDSTILL_TIME_MASK,  TMC5272_DRV_CONF_M1_STANDSTILL_TIME_SHIFT,  TMC5272_DRV_CONF, false })
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_A_MASK          0x000000FF
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_A_SHIFT         0
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_A_FIELD         ((RegisterField) { TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_A_MASK,  TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_A_SHIFT,  TMC5272_GLOBAL_SCALER, false })
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_B_MASK          0x0000FF00
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_B_SHIFT         8
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_B_FIELD         ((RegisterField) { TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_B_MASK,  TMC5272_GLOBAL_SCALER_GLOBALSCALER_M0_B_SHIFT,  TMC5272_GLOBAL_SCALER, false })
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_A_MASK          0x00FF0000
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_A_SHIFT         16
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_A_FIELD         ((RegisterField) { TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_A_MASK,  TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_A_SHIFT,  TMC5272_GLOBAL_SCALER, false })
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_B_MASK          0xFF000000
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_B_SHIFT         24
#define TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_B_FIELD         ((RegisterField) { TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_B_MASK,  TMC5272_GLOBAL_SCALER_GLOBALSCALER_M1_B_SHIFT,  TMC5272_GLOBAL_SCALER, false })
#define TMC5272_RAMPMODE_M0_RAMPMODE_MASK                     0x00000003
#define TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT                    0
#define TMC5272_RAMPMODE_M0_RAMPMODE_FIELD                    ((RegisterField) { TMC5272_RAMPMODE_M0_RAMPMODE_MASK,  TMC5272_RAMPMODE_M0_RAMPMODE_SHIFT,  TMC5272_RAMPMODE, false })
#define TMC5272_RAMPMODE_M1_RAMPMODE_MASK                     0x0000000C
#define TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT                    2
#define TMC5272_RAMPMODE_M1_RAMPMODE_FIELD                    ((RegisterField) { TMC5272_RAMPMODE_M1_RAMPMODE_MASK,  TMC5272_RAMPMODE_M1_RAMPMODE_SHIFT,  TMC5272_RAMPMODE, false })
#define TMC5272_RAMPMODE_SHIFT(motor)                         (2 * (motor))
#define TMC5272_RAMPMODE_MASK(motor)                          (TMC5272_RAMPMODE_M0_RAMPMODE_MASK << TMC5272_RAMPMODE_SHIFT(motor))
#define TMC5272_RAMPMODE_FIELD(motor)                         ((RegisterField) { TMC5272_RAMPMODE_MASK(motor),  TMC5272_RAMPMODE_SHIFT(motor),  TMC5272_RAMPMODE, false })
#define TMC5272_RAMPMODE_RAMP0_HOLD_MASK                      0x00000100
#define TMC5272_RAMPMODE_RAMP0_HOLD_SHIFT                     8
#define TMC5272_RAMPMODE_RAMP0_HOLD_FIELD                     ((RegisterField) { TMC5272_RAMPMODE_RAMP0_HOLD_MASK,  TMC5272_RAMPMODE_RAMP0_HOLD_SHIFT,  TMC5272_RAMPMODE, false })
#define TMC5272_RAMPMODE_RAMP1_HOLD_MASK                      0x00000200
#define TMC5272_RAMPMODE_RAMP1_HOLD_SHIFT                     9
#define TMC5272_RAMPMODE_RAMP1_HOLD_FIELD                     ((RegisterField) { TMC5272_RAMPMODE_RAMP1_HOLD_MASK,  TMC5272_RAMPMODE_RAMP1_HOLD_SHIFT,  TMC5272_RAMPMODE, false })
#define TMC5272_MSLUT_ADDR_MASK                               0x0000001F
#define TMC5272_MSLUT_ADDR_SHIFT                              0
#define TMC5272_MSLUT_ADDR_FIELD                              ((RegisterField) { TMC5272_MSLUT_ADDR_MASK,  TMC5272_MSLUT_ADDR_SHIFT,  TMC5272_MSLUT_ADDR, false })
#define TMC5272_MSLUT_START_START_SIN_MASK                    0xFF
#define TMC5272_MSLUT_START_START_SIN_SHIFT                   0
#define TMC5272_MSLUT_START_START_SIN_FIELD                   ((RegisterField) { TMC5272_MSLUT_START_START_SIN_MASK,  TMC5272_MSLUT_START_START_SIN_SHIFT,  TMC5272_MSLUT_DATA, false })
#define TMC5272_MSLUT_START_START_SIN90_MASK                  0xFF0000
#define TMC5272_MSLUT_START_START_SIN90_SHIFT                 16
#define TMC5272_MSLUT_START_START_SIN90_FIELD                 ((RegisterField) { TMC5272_MSLUT_START_START_SIN90_MASK,  TMC5272_MSLUT_START_START_SIN90_SHIFT,  TMC5272_MSLUT_DATA, false })
#define TMC5272_MSLUT_START_OFFSET_SIN90_MASK                 0xFF000000
#define TMC5272_MSLUT_START_OFFSET_SIN90_SHIFT                24
#define TMC5272_MSLUT_START_OFFSET_SIN90_FIELD                ((RegisterField) { TMC5272_MSLUT_START_OFFSET_SIN90_MASK,  TMC5272_MSLUT_START_OFFSET_SIN90_SHIFT,  TMC5272_MSLUT_DATA, true })
#define TMC5272_X_COMPARE_MASK                                0xFFFFFFFF
#define TMC5272_X_COMPARE_SHIFT                               0
#define TMC5272_X_COMPARE_FIELD(motor)                        ((RegisterField) { TMC5272_X_COMPARE_MASK,  TMC5272_X_COMPARE_SHIFT,  TMC5272_X_COMPARE(motor), true })
#define TMC5272_X_COMPARE_REPEAT_MASK                         0x00FFFFFF
#define TMC5272_X_COMPARE_REPEAT_SHIFT                        0
#define TMC5272_X_COMPARE_REPEAT_FIELD(motor)                 ((RegisterField) { TMC5272_X_COMPARE_REPEAT_MASK,  TMC5272_X_COMPARE_REPEAT_SHIFT,  TMC5272_X_COMPARE_REPEAT(motor), false })
#define TMC5272_IHOLD_IRUN_IHOLD_MASK                         0x0000001F
#define TMC5272_IHOLD_IRUN_IHOLD_SHIFT                        0
#define TMC5272_IHOLD_IRUN_IHOLD_FIELD(motor)                 ((RegisterField) { TMC5272_IHOLD_IRUN_IHOLD_MASK,  TMC5272_IHOLD_IRUN_IHOLD_SHIFT,  TMC5272_IHOLD_IRUN(motor), false })
#define TMC5272_IHOLD_IRUN_IRUN_MASK                          0x00001F00
#define TMC5272_IHOLD_IRUN_IRUN_SHIFT                         8
#define TMC5272_IHOLD_IRUN_IRUN_FIELD(motor)                  ((RegisterField) { TMC5272_IHOLD_IRUN_IRUN_MASK,  TMC5272_IHOLD_IRUN_IRUN_SHIFT,  TMC5272_IHOLD_IRUN(motor), false })
#define TMC5272_IHOLD_IRUN_IHOLDDELAY_MASK                    0x000F0000
#define TMC5272_IHOLD_IRUN_IHOLDDELAY_SHIFT                   16
#define TMC5272_IHOLD_IRUN_IHOLDDELAY_FIELD(motor)            ((RegisterField) { TMC5272_IHOLD_IRUN_IHOLDDELAY_MASK,  TMC5272_IHOLD_IRUN_IHOLDDELAY_SHIFT,  TMC5272_IHOLD_IRUN(motor), false })
#define TMC5272_IHOLD_IRUN_IRUNDELAY_MASK                     0x0F000000
#define TMC5272_IHOLD_IRUN_IRUNDELAY_SHIFT                    24
#define TMC5272_IHOLD_IRUN_IRUNDELAY_FIELD(motor)             ((RegisterField) { TMC5272_IHOLD_IRUN_IRUNDELAY_MASK,  TMC5272_IHOLD_IRUN_IRUNDELAY_SHIFT,  TMC5272_IHOLD_IRUN(motor), false })
#define TMC5272_TPOWERDOWN_MASK                               0x000000FF
#define TMC5272_TPOWERDOWN_SHIFT                              0
#define TMC5272_TPOWERDOWN_FIELD(motor)                       ((RegisterField) { TMC5272_TPOWERDOWN_MASK,  TMC5272_TPOWERDOWN_SHIFT,  TMC5272_TPOWERDOWN(motor), false })
#define TMC5272_TSTEP_MASK                                    0x000FFFFF
#define TMC5272_TSTEP_SHIFT                                   0
#define TMC5272_TSTEP_FIELD(motor)                            ((RegisterField) { TMC5272_TSTEP_MASK,  TMC5272_TSTEP_SHIFT,  TMC5272_TSTEP(motor), false })
#define TMC5272_TPWMTHRS_MASK                                 0x000FFFFF
#define TMC5272_TPWMTHRS_SHIFT                                0
#define TMC5272_TPWMTHRS_FIELD(motor)                         ((RegisterField) { TMC5272_TPWMTHRS_MASK,  TMC5272_TPWMTHRS_SHIFT,  TMC5272_TPWMTHRS(motor), false })
#define TMC5272_TCOOLTHRS_MASK                                0x000FFFFF
#define TMC5272_TCOOLTHRS_SHIFT                               0
#define TMC5272_TCOOLTHRS_FIELD(motor)                        ((RegisterField) { TMC5272_TCOOLTHRS_MASK,  TMC5272_TCOOLTHRS_SHIFT,  TMC5272_TCOOLTHRS(motor), false })
#define TMC5272_THIGH_MASK                                    0x000FFFFF
#define TMC5272_THIGH_SHIFT                                   0
#define TMC5272_THIGH_FIELD(motor)                            ((RegisterField) { TMC5272_THIGH_MASK,  TMC5272_THIGH_SHIFT,  TMC5272_THIGH(motor), false })
#define TMC5272_XACTUAL_MASK                                  0xFFFFFFFF
#define TMC5272_XACTUAL_SHIFT                                 0
#define TMC5272_XACTUAL_FIELD(motor)                          ((RegisterField) { TMC5272_XACTUAL_MASK,  TMC5272_XACTUAL_SHIFT,  TMC5272_XACTUAL(motor), true })
#define TMC5272_VACTUAL_MASK                                  0x00FFFFFF
#define TMC5272_VACTUAL_SHIFT                                 0
#define TMC5272_VACTUAL_FIELD(motor)                          ((RegisterField) { TMC5272_VACTUAL_MASK,  TMC5272_VACTUAL_SHIFT,  TMC5272_VACTUAL(motor), true })
#define TMC5272_AACTUAL_MASK                                  0x00FFFFFF
#define TMC5272_AACTUAL_SHIFT                                 0
#define TMC5272_AACTUAL_FIELD(motor)                          ((RegisterField) { TMC5272_AACTUAL_MASK,  TMC5272_AACTUAL_SHIFT,  TMC5272_AACTUAL(motor), true })
#define TMC5272_VSTART_MASK                                   0x0003FFFF
#define TMC5272_VSTART_SHIFT                                  0
#define TMC5272_VSTART_FIELD(motor)                           ((RegisterField) { TMC5272_VSTART_MASK,  TMC5272_VSTART_SHIFT,  TMC5272_VSTART(motor), false })
#define TMC5272_A1_MASK                                       0x0003FFFF
#define TMC5272_A1_SHIFT                                      0
#define TMC5272_A1_FIELD(motor)                               ((RegisterField) { TMC5272_A1_MASK,  TMC5272_A1_SHIFT,  TMC5272_A1(motor), false })
#define TMC5272_V1_MASK                                       0x000FFFFF
#define TMC5272_V1_SHIFT                                      0
#define TMC5272_V1_FIELD(motor)                               ((RegisterField) { TMC5272_V1_MASK,  TMC5272_V1_SHIFT,  TMC5272_V1(motor), false })
#define TMC5272_A2_MASK                                       0x0003FFFF
#define TMC5272_A2_SHIFT                                      0
#define TMC5272_A2_FIELD(motor)                               ((RegisterField) { TMC5272_A2_MASK,  TMC5272_A2_SHIFT,  TMC5272_A2(motor), false })
#define TMC5272_V2_MASK                                       0x000FFFFF
#define TMC5272_V2_SHIFT                                      0
#define TMC5272_V2_FIELD(motor)                               ((RegisterField) { TMC5272_V2_MASK,  TMC5272_V2_SHIFT,  TMC5272_V2(motor), false })
#define TMC5272_AMAX_MASK                                     0x0003FFFF
#define TMC5272_AMAX_SHIFT                                    0
#define TMC5272_AMAX_FIELD(motor)                             ((RegisterField) { TMC5272_AMAX_MASK,  TMC5272_AMAX_SHIFT,  TMC5272_AMAX(motor), false })
#define TMC5272_VMAX_MASK                                     0x007FFFFF
#define TMC5272_VMAX_SHIFT                                    0
#define TMC5272_VMAX_FIELD(motor)                             ((RegisterField) { TMC5272_VMAX_MASK,  TMC5272_VMAX_SHIFT,  TMC5272_VMAX(motor), false })
#define TMC5272_DMAX_MASK                                     0x0003FFFF
#define TMC5272_DMAX_SHIFT                                    0
#define TMC5272_DMAX_FIELD(motor)                             ((RegisterField) { TMC5272_DMAX_MASK,  TMC5272_DMAX_SHIFT,  TMC5272_DMAX(motor), false })
#define TMC5272_D2_MASK                                       0x0003FFFF
#define TMC5272_D2_SHIFT                                      0
#define TMC5272_D2_FIELD(motor)                               ((RegisterField) { TMC5272_D2_MASK,  TMC5272_D2_SHIFT,  TMC5272_D2(motor), false })
#define TMC5272_D1_MASK                                       0x0003FFFF
#define TMC5272_D1_SHIFT                                      0
#define TMC5272_D1_FIELD(motor)                               ((RegisterField) { TMC5272_D1_MASK,  TMC5272_D1_SHIFT,  TMC5272_D1(motor), false })
#define TMC5272_VSTOP_MASK                                    0x0003FFFF
#define TMC5272_VSTOP_SHIFT                                   0
#define TMC5272_VSTOP_FIELD(motor)                            ((RegisterField) { TMC5272_VSTOP_MASK,  TMC5272_VSTOP_SHIFT,  TMC5272_VSTOP(motor), false })
#define TMC5272_TVMAX_MASK                                    0x0000FFFF
#define TMC5272_TVMAX_SHIFT                                   0
#define TMC5272_TVMAX_FIELD(motor)                            ((RegisterField) { TMC5272_TVMAX_MASK,  TMC5272_TVMAX_SHIFT,  TMC5272_TVMAX(motor), false })
#define TMC5272_TZEROWAIT_MASK                                0x0000FFFF
#define TMC5272_TZEROWAIT_SHIFT                               0
#define TMC5272_TZEROWAIT_FIELD(motor)                        ((RegisterField) { TMC5272_TZEROWAIT_MASK,  TMC5272_TZEROWAIT_SHIFT,  TMC5272_TZEROWAIT(motor), false })
#define TMC5272_XTARGET_MASK                                  0xFFFFFFFF
#define TMC5272_XTARGET_SHIFT                                 0
#define TMC5272_XTARGET_FIELD(motor)                          ((RegisterField) { TMC5272_XTARGET_MASK,  TMC5272_XTARGET_SHIFT,  TMC5272_XTARGET(motor), true })
#define TMC5272_VDCMIN_RESERVED_MASK                          0x000000FF
#define TMC5272_VDCMIN_RESERVED_SHIFT                         0
#define TMC5272_VDCMIN_RESERVED_FIELD(motor)                  ((RegisterField) { TMC5272_VDCMIN_RESERVED_MASK,  TMC5272_VDCMIN_RESERVED_SHIFT,  TMC5272_VDCMIN(motor), false })
#define TMC5272_VDCMIN_VDCMIN_MASK                            0x007FFF00
#define TMC5272_VDCMIN_VDCMIN_SHIFT                           8
#define TMC5272_VDCMIN_VDCMIN_FIELD(motor)                    ((RegisterField) { TMC5272_VDCMIN_VDCMIN_MASK,  TMC5272_VDCMIN_VDCMIN_SHIFT,  TMC5272_VDCMIN(motor), false })
#define TMC5272_SW_MODE_STOP_L_ENABLE_MASK                    0x00000001
#define TMC5272_SW_MODE_STOP_L_ENABLE_SHIFT                   0
#define TMC5272_SW_MODE_STOP_L_ENABLE_FIELD(motor)            ((RegisterField) { TMC5272_SW_MODE_STOP_L_ENABLE_MASK,  TMC5272_SW_MODE_STOP_L_ENABLE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_STOP_R_ENABLE_MASK                    0x00000002
#define TMC5272_SW_MODE_STOP_R_ENABLE_SHIFT                   1
#define TMC5272_SW_MODE_STOP_R_ENABLE_FIELD(motor)            ((RegisterField) { TMC5272_SW_MODE_STOP_R_ENABLE_MASK,  TMC5272_SW_MODE_STOP_R_ENABLE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_POL_STOP_L_MASK                       0x00000004
#define TMC5272_SW_MODE_POL_STOP_L_SHIFT                      2
#define TMC5272_SW_MODE_POL_STOP_L_FIELD(motor)               ((RegisterField) { TMC5272_SW_MODE_POL_STOP_L_MASK,  TMC5272_SW_MODE_POL_STOP_L_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_POL_STOP_R_MASK                       0x00000008
#define TMC5272_SW_MODE_POL_STOP_R_SHIFT                      3
#define TMC5272_SW_MODE_POL_STOP_R_FIELD(motor)               ((RegisterField) { TMC5272_SW_MODE_POL_STOP_R_MASK,  TMC5272_SW_MODE_POL_STOP_R_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_SWAP_LR_MASK                          0x00000010
#define TMC5272_SW_MODE_SWAP_LR_SHIFT                         4
#define TMC5272_SW_MODE_SWAP_LR_FIELD(motor)                  ((RegisterField) { TMC5272_SW_MODE_SWAP_LR_MASK,  TMC5272_SW_MODE_SWAP_LR_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_LATCH_L_ACTIVE_MASK                   0x00000020
#define TMC5272_SW_MODE_LATCH_L_ACTIVE_SHIFT                  5
#define TMC5272_SW_MODE_LATCH_L_ACTIVE_FIELD(motor)           ((RegisterField) { TMC5272_SW_MODE_LATCH_L_ACTIVE_MASK,  TMC5272_SW_MODE_LATCH_L_ACTIVE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_LATCH_L_INACTIVE_MASK                 0x00000040
#define TMC5272_SW_MODE_LATCH_L_INACTIVE_SHIFT                6
#define TMC5272_SW_MODE_LATCH_L_INACTIVE_FIELD(motor)         ((RegisterField) { TMC5272_SW_MODE_LATCH_L_INACTIVE_MASK,  TMC5272_SW_MODE_LATCH_L_ACTIVE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_LATCH_R_ACTIVE_MASK                   0x00000080
#define TMC5272_SW_MODE_LATCH_R_ACTIVE_SHIFT                  7
#define TMC5272_SW_MODE_LATCH_R_ACTIVE_FIELD(motor)           ((RegisterField) { TMC5272_SW_MODE_LATCH_R_ACTIVE_MASK,  TMC5272_SW_MODE_LATCH_R_ACTIVE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_LATCH_R_INACTIVE_MASK                 0x00000100
#define TMC5272_SW_MODE_LATCH_R_INACTIVE_SHIFT                8
#define TMC5272_SW_MODE_LATCH_R_INACTIVE_FIELD(motor)         ((RegisterField) { TMC5272_SW_MODE_LATCH_R_INACTIVE_MASK,  TMC5272_SW_MODE_LATCH_R_INACTIVE_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_EN_LATCH_ENCODER_MASK                 0x00000200
#define TMC5272_SW_MODE_EN_LATCH_ENCODER_SHIFT                9
#define TMC5272_SW_MODE_EN_LATCH_ENCODER_FIELD(motor)         ((RegisterField) { TMC5272_SW_MODE_EN_LATCH_ENCODER_MASK,  TMC5272_SW_MODE_EN_LATCH_ENCODER_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_SG_STOP_MASK                          0x00000400
#define TMC5272_SW_MODE_SG_STOP_SHIFT                         10
#define TMC5272_SW_MODE_SG_STOP_FIELD(motor)                  ((RegisterField) { TMC5272_SW_MODE_SG_STOP_MASK,  TMC5272_SW_MODE_SG_STOP_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_EN_SOFTSTOP_MASK                      0x00000800
#define TMC5272_SW_MODE_EN_SOFTSTOP_SHIFT                     11
#define TMC5272_SW_MODE_EN_SOFTSTOP_FIELD(motor)              ((RegisterField) { TMC5272_SW_MODE_EN_SOFTSTOP_MASK,  TMC5272_SW_MODE_EN_SOFTSTOP_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_L_MASK                0x00001000
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_L_SHIFT               12
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_L_FIELD(motor)        ((RegisterField) { TMC5272_SW_MODE_EN_SOFTSTOP_MASK,  TMC5272_SW_MODE_EN_SOFTSTOP_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_R_MASK                0x00002000
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_R_SHIFT               13
#define TMC5272_SW_MODE_EN_VIRTUAL_STOP_R_FIELD(motor)        ((RegisterField) { TMC5272_SW_MODE_EN_VIRTUAL_STOP_R_MASK,  TMC5272_SW_MODE_EN_VIRTUAL_STOP_R_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_SW_MODE_VIRTUAL_STEP_ENC_MASK                 0x00004000
#define TMC5272_SW_MODE_VIRTUAL_STEP_ENC_SHIFT                14
#define TMC5272_SW_MODE_VIRTUAL_STEP_ENC_FIELD(motor)         ((RegisterField) { TMC5272_SW_MODE_VIRTUAL_STEP_ENC_MASK,  TMC5272_SW_MODE_VIRTUAL_STEP_ENC_SHIFT,  TMC5272_SW_MODE(motor), false })
#define TMC5272_RAMP_STAT_STATUS_STOP_L_MASK                  0x00000001
#define TMC5272_RAMP_STAT_STATUS_STOP_L_SHIFT                 0
#define TMC5272_RAMP_STAT_STATUS_STOP_L_FIELD(motor)          ((RegisterField) { TMC5272_RAMP_STAT_STATUS_STOP_L_MASK,  TMC5272_RAMP_STAT_STATUS_STOP_L_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_STOP_R_MASK                  0x00000002
#define TMC5272_RAMP_STAT_STATUS_STOP_R_SHIFT                 1
#define TMC5272_RAMP_STAT_STATUS_STOP_R_FIELD(motor)          ((RegisterField) { TMC5272_RAMP_STAT_STATUS_STOP_R_MASK,  TMC5272_RAMP_STAT_STATUS_STOP_R_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_LATCH_L_MASK                 0x00000004
#define TMC5272_RAMP_STAT_STATUS_LATCH_L_SHIFT                2
#define TMC5272_RAMP_STAT_STATUS_LATCH_L_FIELD(motor)         ((RegisterField) { TMC5272_RAMP_STAT_STATUS_LATCH_L_MASK,  TMC5272_RAMP_STAT_STATUS_LATCH_L_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_LATCH_R_MASK                 0x00000008
#define TMC5272_RAMP_STAT_STATUS_LATCH_R_SHIFT                3
#define TMC5272_RAMP_STAT_STATUS_LATCH_R_FIELD(motor)         ((RegisterField) { TMC5272_RAMP_STAT_STATUS_LATCH_R_MASK,  TMC5272_RAMP_STAT_STATUS_LATCH_R_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_EVENT_STOP_L_MASK                   0x00000010
#define TMC5272_RAMP_STAT_EVENT_STOP_L_SHIFT                  4
#define TMC5272_RAMP_STAT_EVENT_STOP_L_FIELD(motor)           ((RegisterField) { TMC5272_RAMP_STAT_EVENT_STOP_L_MASK,  TMC5272_RAMP_STAT_EVENT_STOP_L_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_EVENT_STOP_R_MASK                   0x00000020
#define TMC5272_RAMP_STAT_EVENT_STOP_R_SHIFT                  5
#define TMC5272_RAMP_STAT_EVENT_STOP_R_FIELD(motor)           ((RegisterField) { TMC5272_RAMP_STAT_EVENT_STOP_R_MASK,  TMC5272_RAMP_STAT_EVENT_STOP_R_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_EVENT_STOP_SG_MASK                  0x00000040
#define TMC5272_RAMP_STAT_EVENT_STOP_SG_SHIFT                 6
#define TMC5272_RAMP_STAT_EVENT_STOP_SG_FIELD(motor)          ((RegisterField) { TMC5272_RAMP_STAT_EVENT_STOP_SG_MASK,  TMC5272_RAMP_STAT_EVENT_STOP_SG_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_EVENT_POS_REACHED_MASK              0x00000080
#define TMC5272_RAMP_STAT_EVENT_POS_REACHED_SHIFT             7
#define TMC5272_RAMP_STAT_EVENT_POS_REACHED_FIELD(motor)      ((RegisterField) { TMC5272_RAMP_STAT_EVENT_POS_REACHED_MASK,  TMC5272_RAMP_STAT_EVENT_POS_REACHED_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_VELOCITY_REACHED_MASK               0x00000100
#define TMC5272_RAMP_STAT_VELOCITY_REACHED_SHIFT              8
#define TMC5272_RAMP_STAT_VELOCITY_REACHED_FIELD(motor)       ((RegisterField) { TMC5272_RAMP_STAT_VELOCITY_REACHED_MASK,  TMC5272_RAMP_STAT_VELOCITY_REACHED_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_POSITION_REACHED_MASK               0x00000200
#define TMC5272_RAMP_STAT_POSITION_REACHED_SHIFT              9
#define TMC5272_RAMP_STAT_POSITION_REACHED_FIELD(motor)       ((RegisterField) { TMC5272_RAMP_STAT_POSITION_REACHED_MASK,  TMC5272_RAMP_STAT_POSITION_REACHED_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_VZERO_MASK                          0x00000400
#define TMC5272_RAMP_STAT_VZERO_SHIFT                         10
#define TMC5272_RAMP_STAT_VZERO_FIELD(motor)                  ((RegisterField) { TMC5272_RAMP_STAT_VZERO_MASK,  TMC5272_RAMP_STAT_VZERO_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_T_ZEROWAIT_ACTIVE_MASK              0x00000800
#define TMC5272_RAMP_STAT_T_ZEROWAIT_ACTIVE_SHIFT             11
#define TMC5272_RAMP_STAT_T_ZEROWAIT_ACTIVE_FIELD(motor)      ((RegisterField) { TMC5272_RAMP_STAT_T_ZEROWAIT_ACTIVE_MASK,  TMC5272_RAMP_STAT_T_ZEROWAIT_ACTIVE_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_SECOND_MOVE_MASK                    0x00001000
#define TMC5272_RAMP_STAT_SECOND_MOVE_SHIFT                   12
#define TMC5272_RAMP_STAT_SECOND_MOVE_FIELD(motor)            ((RegisterField) { TMC5272_RAMP_STAT_SECOND_MOVE_MASK,  TMC5272_RAMP_STAT_SECOND_MOVE_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_SG_MASK                      0x00002000
#define TMC5272_RAMP_STAT_STATUS_SG_SHIFT                     13
#define TMC5272_RAMP_STAT_STATUS_SG_FIELD(motor)              ((RegisterField) { TMC5272_RAMP_STAT_STATUS_SG_MASK,  TMC5272_RAMP_STAT_STATUS_SG_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_L_MASK          0x00004000
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_L_SHIFT         14
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_L_FIELD(motor)  ((RegisterField) { TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_L_MASK,  TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_L_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_R_MASK          0x00008000
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_R_SHIFT         15
#define TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_R_FIELD(motor)  ((RegisterField) { TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_R_MASK,  TMC5272_RAMP_STAT_STATUS_VIRTUAL_STOP_R_SHIFT,  TMC5272_RAMP_STAT(motor), false })
#define TMC5272_XLATCH_MASK                                   0xFFFFFFFF
#define TMC5272_XLATCH_SHIFT                                  0
#define TMC5272_XLATCH_FIELD(motor)                           ((RegisterField) { TMC5272_XLATCH_MASK,  TMC5272_XLATCH_SHIFT,  TMC5272_XLATCH(motor), true })
#define TMC5272_POSITION_PI_CTRL_POSITION_PI_CTRL_REGS_MASK   0xFFFFFFFF
#define TMC5272_POSITION_PI_CTRL_POSITION_PI_CTRL_REGS_SHIFT  0
#define TMC5272_POSITION_PI_CTRL_POSITION_PI_CTRL_REGS_FIELD(motor)  ((RegisterField) { TMC5272_POSITION_PI_CTRL_POSITION_PI_CTRL_REGS_MASK,  TMC5272_POSITION_PI_CTRL_POSITION_PI_CTRL_REGS_SHIFT,  TMC5272_POSITION_PI_CTRL(motor), false })
#define TMC5272_X_ENC_MASK                                    0xFFFFFFFF
#define TMC5272_X_ENC_SHIFT                                   0
#define TMC5272_X_ENC_FIELD(motor)                            ((RegisterField) { TMC5272_X_ENC_MASK,  TMC5272_X_ENC_SHIFT,  TMC5272_X_ENC(motor), true })
#define TMC5272_ENCMODE_POL_A_MASK                            0x00000001
#define TMC5272_ENCMODE_POL_A_SHIFT                           0
#define TMC5272_ENCMODE_POL_A_FIELD(motor)                    ((RegisterField) { TMC5272_ENCMODE_POL_A_MASK,  TMC5272_ENCMODE_POL_A_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_POL_B_MASK                            0x00000002
#define TMC5272_ENCMODE_POL_B_SHIFT                           1
#define TMC5272_ENCMODE_POL_B_FIELD(motor)                    ((RegisterField) { TMC5272_ENCMODE_POL_B_MASK,  TMC5272_ENCMODE_POL_B_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_POL_N_MASK                            0x00000004
#define TMC5272_ENCMODE_POL_N_SHIFT                           2
#define TMC5272_ENCMODE_POL_N_FIELD(motor)                    ((RegisterField) { TMC5272_ENCMODE_POL_N_MASK,  TMC5272_ENCMODE_POL_N_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_IGNORE_AB_MASK                        0x00000008
#define TMC5272_ENCMODE_IGNORE_AB_SHIFT                       3
#define TMC5272_ENCMODE_IGNORE_AB_FIELD(motor)                ((RegisterField) { TMC5272_ENCMODE_IGNORE_AB_MASK,  TMC5272_ENCMODE_IGNORE_AB_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_CLR_CONT_MASK                         0x00000010
#define TMC5272_ENCMODE_CLR_CONT_SHIFT                        4
#define TMC5272_ENCMODE_CLR_CONT_FIELD(motor)                 ((RegisterField) { TMC5272_ENCMODE_CLR_CONT_MASK,  TMC5272_ENCMODE_CLR_CONT_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_CLR_ONCE_MASK                         0x00000020
#define TMC5272_ENCMODE_CLR_ONCE_SHIFT                        5
#define TMC5272_ENCMODE_CLR_ONCE_FIELD(motor)                 ((RegisterField) { TMC5272_ENCMODE_CLR_ONCE_MASK,  TMC5272_ENCMODE_CLR_ONCE_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_POS_NEG_EDGE_MASK                     0x000000C0
#define TMC5272_ENCMODE_POS_NEG_EDGE_SHIFT                    6
#define TMC5272_ENCMODE_POS_NEG_EDGE_FIELD(motor)             ((RegisterField) { TMC5272_ENCMODE_POS_NEG_EDGE_MASK,  TMC5272_ENCMODE_POS_NEG_EDGE_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_CLR_ENC_X_MASK                        0x00000100
#define TMC5272_ENCMODE_CLR_ENC_X_SHIFT                       8
#define TMC5272_ENCMODE_CLR_ENC_X_FIELD(motor)                ((RegisterField) { TMC5272_ENCMODE_CLR_ENC_X_MASK,  TMC5272_ENCMODE_CLR_ENC_X_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_LATCH_X_ACT_MASK                      0x00000200
#define TMC5272_ENCMODE_LATCH_X_ACT_SHIFT                     9
#define TMC5272_ENCMODE_LATCH_X_ACT_FIELD(motor)              ((RegisterField) { TMC5272_ENCMODE_LATCH_X_ACT_MASK,  TMC5272_ENCMODE_LATCH_X_ACT_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_ENC_SEL_DECIMAL_MASK                  0x00000400
#define TMC5272_ENCMODE_ENC_SEL_DECIMAL_SHIFT                 10
#define TMC5272_ENCMODE_ENC_SEL_DECIMAL_FIELD(motor)          ((RegisterField) { TMC5272_ENCMODE_ENC_SEL_DECIMAL_MASK,  TMC5272_ENCMODE_ENC_SEL_DECIMAL_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_NBEMF_ABN_SEL_MASK                    0x00000800
#define TMC5272_ENCMODE_NBEMF_ABN_SEL_SHIFT                   11
#define TMC5272_ENCMODE_NBEMF_ABN_SEL_FIELD(motor)            ((RegisterField) { TMC5272_ENCMODE_NBEMF_ABN_SEL_MASK,  TMC5272_ENCMODE_NBEMF_ABN_SEL_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_BEMF_HYST_MASK                        0x00007000
#define TMC5272_ENCMODE_BEMF_HYST_SHIFT                       12
#define TMC5272_ENCMODE_BEMF_HYST_FIELD(motor)                ((RegisterField) { TMC5272_ENCMODE_BEMF_HYST_MASK,  TMC5272_ENCMODE_BEMF_HYST_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENCMODE_BEMF_BLANK_TIME_MASK                  0x00FF0000
#define TMC5272_ENCMODE_BEMF_BLANK_TIME_SHIFT                 16
#define TMC5272_ENCMODE_BEMF_BLANK_TIME_FIELD(motor)          ((RegisterField) { TMC5272_ENCMODE_BEMF_BLANK_TIME_MASK,  TMC5272_ENCMODE_BEMF_BLANK_TIME_SHIFT,  TMC5272_ENCMODE(motor), false })
#define TMC5272_ENC_CONST_MASK                                0xFFFFFFFF
#define TMC5272_ENC_CONST_SHIFT                               0
#define TMC5272_ENC_CONST_FIELD(motor)                        ((RegisterField) { TMC5272_ENC_CONST_MASK,  TMC5272_ENC_CONST_SHIFT,  TMC5272_ENC_CONST(motor), true })
#define TMC5272_ENC_STATUS_N_EVENT_MASK                       0x00000001
#define TMC5272_ENC_STATUS_N_EVENT_SHIFT                      0
#define TMC5272_ENC_STATUS_N_EVENT_FIELD(motor)               ((RegisterField) { TMC5272_ENC_STATUS_N_EVENT_MASK,  TMC5272_ENC_STATUS_N_EVENT_SHIFT,  TMC5272_ENC_STATUS(motor), false })
#define TMC5272_ENC_STATUS_DEVIATION_WARN_MASK                0x00000002
#define TMC5272_ENC_STATUS_DEVIATION_WARN_SHIFT               1
#define TMC5272_ENC_STATUS_DEVIATION_WARN_FIELD(motor)        ((RegisterField) { TMC5272_ENC_STATUS_DEVIATION_WARN_MASK,  TMC5272_ENC_STATUS_DEVIATION_WARN_SHIFT,  TMC5272_ENC_STATUS(motor), false })
#define TMC5272_ENC_LATCH_MASK                                0xFFFFFFFF
#define TMC5272_ENC_LATCH_SHIFT                               0
#define TMC5272_ENC_LATCH_FIELD(motor)                        ((RegisterField) { TMC5272_ENC_LATCH_MASK,  TMC5272_ENC_LATCH_SHIFT,  TMC5272_ENC_LATCH(motor), true })
#define TMC5272_ENC_DEVIATION_MASK                            0x000FFFFF
#define TMC5272_ENC_DEVIATION_SHIFT                           0
#define TMC5272_ENC_DEVIATION_FIELD(motor)                    ((RegisterField) { TMC5272_ENC_DEVIATION_MASK,  TMC5272_ENC_DEVIATION_SHIFT,  TMC5272_ENC_DEVIATION(motor), false })
#define TMC5272_VIRTUAL_STOP_L_MASK                           0xFFFFFFFF
#define TMC5272_VIRTUAL_STOP_L_SHIFT                          0
#define TMC5272_VIRTUAL_STOP_L_FIELD(motor)                   ((RegisterField) { TMC5272_VIRTUAL_STOP_L_MASK,  TMC5272_VIRTUAL_STOP_L_SHIFT,  TMC5272_VIRTUAL_STOP_L(motor), true })
#define TMC5272_VIRTUAL_STOP_R_MASK                           0xFFFFFFFF
#define TMC5272_VIRTUAL_STOP_R_SHIFT                          0
#define TMC5272_VIRTUAL_STOP_R_FIELD(motor)                   ((RegisterField) { TMC5272_VIRTUAL_STOP_R_MASK,  TMC5272_VIRTUAL_STOP_R_SHIFT,  TMC5272_VIRTUAL_STOP_R(motor), true })
#define TMC5272_MSCNT_MASK                                    0x000003FF
#define TMC5272_MSCNT_SHIFT                                   0
#define TMC5272_MSCNT_FIELD(motor)                            ((RegisterField) { TMC5272_MSCNT_MASK,  TMC5272_MSCNT_SHIFT,  TMC5272_MSCNT(motor), false })
#define TMC5272_MSCURACT_CUR_A_MASK                           0x000001FF
#define TMC5272_MSCURACT_CUR_A_SHIFT                          0
#define TMC5272_MSCURACT_CUR_A_FIELD(motor)                   ((RegisterField) { TMC5272_MSCURACT_CUR_A_MASK,  TMC5272_MSCURACT_CUR_A_SHIFT,  TMC5272_MSCURACT(motor), false })
#define TMC5272_MSCURACT_CUR_B_MASK                           0x01FF0000
#define TMC5272_MSCURACT_CUR_B_SHIFT                          16
#define TMC5272_MSCURACT_CUR_B_FIELD(motor)                   ((RegisterField) { TMC5272_MSCURACT_CUR_B_MASK,  TMC5272_MSCURACT_CUR_B_SHIFT,  TMC5272_MSCURACT(motor), false })
#define TMC5272_CHOPCONF_TOFF_MASK                            0x0000000F
#define TMC5272_CHOPCONF_TOFF_SHIFT                           0
#define TMC5272_CHOPCONF_TOFF_FIELD(motor)                    ((RegisterField) { TMC5272_CHOPCONF_TOFF_MASK,  TMC5272_CHOPCONF_TOFF_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_HSTRT_TFD210_MASK                    0x00000070
#define TMC5272_CHOPCONF_HSTRT_TFD210_SHIFT                   4
#define TMC5272_CHOPCONF_HSTRT_TFD210_FIELD(motor)            ((RegisterField) { TMC5272_CHOPCONF_HSTRT_TFD210_MASK,  TMC5272_CHOPCONF_HSTRT_TFD210_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_HEND_OFFSET_MASK                     0x00000780
#define TMC5272_CHOPCONF_HEND_OFFSET_SHIFT                    7
#define TMC5272_CHOPCONF_HEND_OFFSET_FIELD(motor)             ((RegisterField) { TMC5272_CHOPCONF_HEND_OFFSET_MASK,  TMC5272_CHOPCONF_HEND_OFFSET_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_FD3_MASK                             0x00000800
#define TMC5272_CHOPCONF_FD3_SHIFT                            11
#define TMC5272_CHOPCONF_FD3_FIELD(motor)                     ((RegisterField) { TMC5272_CHOPCONF_FD3_MASK,  TMC5272_CHOPCONF_FD3_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_DISFDCC_MASK                         0x00001000
#define TMC5272_CHOPCONF_DISFDCC_SHIFT                        12
#define TMC5272_CHOPCONF_DISFDCC_FIELD(motor)                 ((RegisterField) { TMC5272_CHOPCONF_DISFDCC_MASK,  TMC5272_CHOPCONF_DISFDCC_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_CHM_MASK                             0x00004000
#define TMC5272_CHOPCONF_CHM_SHIFT                            14
#define TMC5272_CHOPCONF_CHM_FIELD(motor)                     ((RegisterField) { TMC5272_CHOPCONF_CHM_MASK,  TMC5272_CHOPCONF_CHM_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_TBL_MASK                             0x00018000
#define TMC5272_CHOPCONF_TBL_SHIFT                            15
#define TMC5272_CHOPCONF_TBL_FIELD(motor)                     ((RegisterField) { TMC5272_CHOPCONF_TBL_MASK,  TMC5272_CHOPCONF_TBL_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_VHIGHFS_MASK                         0x00040000
#define TMC5272_CHOPCONF_VHIGHFS_SHIFT                        18
#define TMC5272_CHOPCONF_VHIGHFS_FIELD(motor)                 ((RegisterField) { TMC5272_CHOPCONF_VHIGHFS_MASK,  TMC5272_CHOPCONF_VHIGHFS_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_VHIGHCHM_MASK                        0x00080000
#define TMC5272_CHOPCONF_VHIGHCHM_SHIFT                       19
#define TMC5272_CHOPCONF_VHIGHCHM_FIELD(motor)                ((RegisterField) { TMC5272_CHOPCONF_VHIGHCHM_MASK,  TMC5272_CHOPCONF_VHIGHCHM_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_TPFD_MASK                            0x00F00000
#define TMC5272_CHOPCONF_TPFD_SHIFT                           20
#define TMC5272_CHOPCONF_TPFD_FIELD(motor)                    ((RegisterField) { TMC5272_CHOPCONF_TPFD_MASK,  TMC5272_CHOPCONF_TPFD_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_MRES_MASK                            0x0F000000
#define TMC5272_CHOPCONF_MRES_SHIFT                           24
#define TMC5272_CHOPCONF_MRES_FIELD(motor)                    ((RegisterField) { TMC5272_CHOPCONF_MRES_MASK,  TMC5272_CHOPCONF_MRES_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_INTPOL_MASK                          0x10000000
#define TMC5272_CHOPCONF_INTPOL_SHIFT                         28
#define TMC5272_CHOPCONF_INTPOL_FIELD(motor)                  ((RegisterField) { TMC5272_CHOPCONF_INTPOL_MASK,  TMC5272_CHOPCONF_INTPOL_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_DEDGE_MASK                           0x20000000
#define TMC5272_CHOPCONF_DEDGE_SHIFT                          29
#define TMC5272_CHOPCONF_DEDGE_FIELD(motor)                   ((RegisterField) { TMC5272_CHOPCONF_DEDGE_MASK,  TMC5272_CHOPCONF_DEDGE_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_DISS2G_MASK                          0x40000000
#define TMC5272_CHOPCONF_DISS2G_SHIFT                         30
#define TMC5272_CHOPCONF_DISS2G_FIELD(motor)                  ((RegisterField) { TMC5272_CHOPCONF_DISS2G_MASK,  TMC5272_CHOPCONF_DISS2G_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_CHOPCONF_DISS2VS_MASK                         0x80000000
#define TMC5272_CHOPCONF_DISS2VS_SHIFT                        31
#define TMC5272_CHOPCONF_DISS2VS_FIELD(motor)                 ((RegisterField) { TMC5272_CHOPCONF_DISS2VS_MASK,  TMC5272_CHOPCONF_DISS2VS_SHIFT,  TMC5272_CHOPCONF(motor), false })
#define TMC5272_COOLCONF_SEMIN_MASK                           0x0000000F
#define TMC5272_COOLCONF_SEMIN_SHIFT                          0
#define TMC5272_COOLCONF_SEMIN_FIELD(motor)                   ((RegisterField) { TMC5272_COOLCONF_SEMIN_MASK,  TMC5272_COOLCONF_SEMIN_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_COOLCONF_SEUP_MASK                            0x00000060
#define TMC5272_COOLCONF_SEUP_SHIFT                           5
#define TMC5272_COOLCONF_SEUP_FIELD(motor)                    ((RegisterField) { TMC5272_COOLCONF_SEUP_MASK,  TMC5272_COOLCONF_SEUP_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_COOLCONF_SEMAX_MASK                           0x00000F00
#define TMC5272_COOLCONF_SEMAX_SHIFT                          8
#define TMC5272_COOLCONF_SEMAX_FIELD(motor)                   ((RegisterField) { TMC5272_COOLCONF_SEMAX_MASK,  TMC5272_COOLCONF_SEMAX_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_COOLCONF_SEDN_MASK                            0x00006000
#define TMC5272_COOLCONF_SEDN_SHIFT                           13
#define TMC5272_COOLCONF_SEDN_FIELD(motor)                    ((RegisterField) { TMC5272_COOLCONF_SEDN_MASK,  TMC5272_COOLCONF_SEDN_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_COOLCONF_SEIMIN_MASK                          0x00008000
#define TMC5272_COOLCONF_SEIMIN_SHIFT                         15
#define TMC5272_COOLCONF_SEIMIN_FIELD(motor)                  ((RegisterField) { TMC5272_COOLCONF_SEIMIN_MASK,  TMC5272_COOLCONF_SEIMIN_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_COOLCONF_SGT_MASK                             0x007F0000
#define TMC5272_COOLCONF_SGT_SHIFT                            16
#define TMC5272_COOLCONF_SGT_FIELD(motor)                     ((RegisterField) { TMC5272_COOLCONF_SGT_MASK,  TMC5272_COOLCONF_SGT_SHIFT,  TMC5272_COOLCONF(motor), true })
#define TMC5272_COOLCONF_SFILT_MASK                           0x01000000
#define TMC5272_COOLCONF_SFILT_SHIFT                          24
#define TMC5272_COOLCONF_SFILT_FIELD(motor)                   ((RegisterField) { TMC5272_COOLCONF_SFILT_MASK,  TMC5272_COOLCONF_SFILT_SHIFT,  TMC5272_COOLCONF(motor), false })
#define TMC5272_DCCTRL_DC_TIME_MASK                           0x000003FF
#define TMC5272_DCCTRL_DC_TIME_SHIFT                          0
#define TMC5272_DCCTRL_DC_TIME_FIELD(motor)                   ((RegisterField) { TMC5272_DCCTRL_DC_TIME_MASK,  TMC5272_DCCTRL_DC_TIME_SHIFT,  TMC5272_DCCTRL(motor), false })
#define TMC5272_DCCTRL_DC_SG_MASK                             0x00FFFC00
#define TMC5272_DCCTRL_DC_SG_SHIFT                            10
#define TMC5272_DCCTRL_DC_SG_FIELD(motor)                     ((RegisterField) { TMC5272_DCCTRL_DC_SG_MASK,  TMC5272_DCCTRL_DC_SG_SHIFT,  TMC5272_DCCTRL(motor), false })
#define TMC5272_DRV_STATUS_SG_RESULT_MASK                     0x000003FF
#define TMC5272_DRV_STATUS_SG_RESULT_SHIFT                    0
#define TMC5272_DRV_STATUS_SG_RESULT_FIELD(motor)             ((RegisterField) { TMC5272_DRV_STATUS_SG_RESULT_MASK,  TMC5272_DRV_STATUS_SG_RESULT_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_S2VSA_MASK                         0x00001000
#define TMC5272_DRV_STATUS_S2VSA_SHIFT                        12
#define TMC5272_DRV_STATUS_S2VSA_FIELD(motor)                 ((RegisterField) { TMC5272_DRV_STATUS_S2VSA_MASK,  TMC5272_DRV_STATUS_S2VSA_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_S2VSB_MASK                         0x00002000
#define TMC5272_DRV_STATUS_S2VSB_SHIFT                        13
#define TMC5272_DRV_STATUS_S2VSB_FIELD(motor)                 ((RegisterField) { TMC5272_DRV_STATUS_S2VSB_MASK,  TMC5272_DRV_STATUS_S2VSB_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_STEALTH_MASK                       0x00004000
#define TMC5272_DRV_STATUS_STEALTH_SHIFT                      14
#define TMC5272_DRV_STATUS_STEALTH_FIELD(motor)               ((RegisterField) { TMC5272_DRV_STATUS_STEALTH_MASK,  TMC5272_DRV_STATUS_STEALTH_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_FSACTIVE_MASK                      0x00008000
#define TMC5272_DRV_STATUS_FSACTIVE_SHIFT                     15
#define TMC5272_DRV_STATUS_FSACTIVE_FIELD(motor)              ((RegisterField) { TMC5272_DRV_STATUS_FSACTIVE_MASK,  TMC5272_DRV_STATUS_FSACTIVE_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_CS_ACTUAL_MASK                     0x001F0000
#define TMC5272_DRV_STATUS_CS_ACTUAL_SHIFT                    16
#define TMC5272_DRV_STATUS_CS_ACTUAL_FIELD(motor)             ((RegisterField) { TMC5272_DRV_STATUS_CS_ACTUAL_MASK,  TMC5272_DRV_STATUS_CS_ACTUAL_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_STALLGUARD_MASK                    0x01000000
#define TMC5272_DRV_STATUS_STALLGUARD_SHIFT                   24
#define TMC5272_DRV_STATUS_STALLGUARD_FIELD(motor)            ((RegisterField) { TMC5272_DRV_STATUS_STALLGUARD_MASK,  TMC5272_DRV_STATUS_STALLGUARD_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_OT_MASK                            0x02000000
#define TMC5272_DRV_STATUS_OT_SHIFT                           25
#define TMC5272_DRV_STATUS_OT_FIELD(motor)                    ((RegisterField) { TMC5272_DRV_STATUS_OT_MASK,  TMC5272_DRV_STATUS_OT_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_OTPW_MASK                          0x04000000
#define TMC5272_DRV_STATUS_OTPW_SHIFT                         26
#define TMC5272_DRV_STATUS_OTPW_FIELD(motor)                  ((RegisterField) { TMC5272_DRV_STATUS_OTPW_MASK,  TMC5272_DRV_STATUS_OTPW_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_S2GA_MASK                          0x08000000
#define TMC5272_DRV_STATUS_S2GA_SHIFT                         27
#define TMC5272_DRV_STATUS_S2GA_FIELD(motor)                  ((RegisterField) { TMC5272_DRV_STATUS_S2GA_MASK,  TMC5272_DRV_STATUS_S2GA_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_S2GB_MASK                          0x10000000
#define TMC5272_DRV_STATUS_S2GB_SHIFT                         28
#define TMC5272_DRV_STATUS_S2GB_FIELD(motor)                  ((RegisterField) { TMC5272_DRV_STATUS_S2GB_MASK,  TMC5272_DRV_STATUS_S2GB_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_OLA_MASK                           0x20000000
#define TMC5272_DRV_STATUS_OLA_SHIFT                          29
#define TMC5272_DRV_STATUS_OLA_FIELD(motor)                   ((RegisterField) { TMC5272_DRV_STATUS_OLA_MASK,  TMC5272_DRV_STATUS_OLA_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_OLB_MASK                           0x40000000
#define TMC5272_DRV_STATUS_OLB_SHIFT                          30
#define TMC5272_DRV_STATUS_OLB_FIELD(motor)                   ((RegisterField) { TMC5272_DRV_STATUS_OLB_MASK,  TMC5272_DRV_STATUS_OLB_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_DRV_STATUS_STST_MASK                          0x80000000
#define TMC5272_DRV_STATUS_STST_SHIFT                         31
#define TMC5272_DRV_STATUS_STST_FIELD(motor)                  ((RegisterField) { TMC5272_DRV_STATUS_STST_MASK,  TMC5272_DRV_STATUS_STST_SHIFT,  TMC5272_DRV_STATUS(motor), false })
#define TMC5272_PWMCONF_PWM_OFS_MASK                          0x000000FF
#define TMC5272_PWMCONF_PWM_OFS_SHIFT                         0
#define TMC5272_PWMCONF_PWM_OFS_FIELD(motor)                  ((RegisterField) { TMC5272_PWMCONF_PWM_OFS_MASK,  TMC5272_PWMCONF_PWM_OFS_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_GRAD_MASK                         0x0000FF00
#define TMC5272_PWMCONF_PWM_GRAD_SHIFT                        8
#define TMC5272_PWMCONF_PWM_GRAD_FIELD(motor)                 ((RegisterField) { TMC5272_PWMCONF_PWM_GRAD_MASK,  TMC5272_PWMCONF_PWM_GRAD_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_FREQ_MASK                         0x00030000
#define TMC5272_PWMCONF_PWM_FREQ_SHIFT                        16
#define TMC5272_PWMCONF_PWM_FREQ_FIELD(motor)                 ((RegisterField) { TMC5272_PWMCONF_PWM_FREQ_MASK,  TMC5272_PWMCONF_PWM_FREQ_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_AUTOSCALE_MASK                    0x00040000
#define TMC5272_PWMCONF_PWM_AUTOSCALE_SHIFT                   18
#define TMC5272_PWMCONF_PWM_AUTOSCALE_FIELD(motor)            ((RegisterField) { TMC5272_PWMCONF_PWM_AUTOSCALE_MASK,  TMC5272_PWMCONF_PWM_AUTOSCALE_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_AUTOGRAD_MASK                     0x00080000
#define TMC5272_PWMCONF_PWM_AUTOGRAD_SHIFT                    19
#define TMC5272_PWMCONF_PWM_AUTOGRAD_FIELD(motor)             ((RegisterField) { TMC5272_PWMCONF_PWM_AUTOGRAD_MASK,  TMC5272_PWMCONF_PWM_AUTOGRAD_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_FREEWHEEL_MASK                        0x00300000
#define TMC5272_PWMCONF_FREEWHEEL_SHIFT                       20
#define TMC5272_PWMCONF_FREEWHEEL_FIELD(motor)                ((RegisterField) { TMC5272_PWMCONF_FREEWHEEL_MASK,  TMC5272_PWMCONF_FREEWHEEL_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_MEAS_SD_ENABLE_MASK               0x00400000
#define TMC5272_PWMCONF_PWM_MEAS_SD_ENABLE_SHIFT              22
#define TMC5272_PWMCONF_PWM_MEAS_SD_ENABLE_FIELD(motor)       ((RegisterField) { TMC5272_PWMCONF_PWM_MEAS_SD_ENABLE_MASK,  TMC5272_PWMCONF_PWM_MEAS_SD_ENABLE_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_DIS_REG_STST_MASK                 0x00800000
#define TMC5272_PWMCONF_PWM_DIS_REG_STST_SHIFT                23
#define TMC5272_PWMCONF_PWM_DIS_REG_STST_FIELD(motor)         ((RegisterField) { TMC5272_PWMCONF_PWM_DIS_REG_STST_MASK,  TMC5272_PWMCONF_PWM_DIS_REG_STST_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_REG_MASK                          0x0F000000
#define TMC5272_PWMCONF_PWM_REG_SHIFT                         24
#define TMC5272_PWMCONF_PWM_REG_FIELD(motor)                  ((RegisterField) { TMC5272_PWMCONF_PWM_REG_MASK,  TMC5272_PWMCONF_PWM_REG_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWMCONF_PWM_LIM_MASK                          0xF0000000
#define TMC5272_PWMCONF_PWM_LIM_SHIFT                         28
#define TMC5272_PWMCONF_PWM_LIM_FIELD(motor)                  ((RegisterField) { TMC5272_PWMCONF_PWM_LIM_MASK,  TMC5272_PWMCONF_PWM_LIM_SHIFT,  TMC5272_PWMCONF(motor), false })
#define TMC5272_PWM_SCALE_PWM_SCALE_SUM_MASK                  0x000003FF
#define TMC5272_PWM_SCALE_PWM_SCALE_SUM_SHIFT                 0
#define TMC5272_PWM_SCALE_PWM_SCALE_SUM_FIELD(motor)          ((RegisterField) { TMC5272_PWM_SCALE_PWM_SCALE_SUM_MASK,  TMC5272_PWM_SCALE_PWM_SCALE_SUM_SHIFT,  TMC5272_PWM_SCALE(motor), false })
#define TMC5272_PWM_SCALE_PWM_SCALE_AUTO_MASK                 0x01FF0000
#define TMC5272_PWM_SCALE_PWM_SCALE_AUTO_SHIFT                16
#define TMC5272_PWM_SCALE_PWM_SCALE_AUTO_FIELD(motor)         ((RegisterField) { TMC5272_PWM_SCALE_PWM_SCALE_AUTO_MASK,  TMC5272_PWM_SCALE_PWM_SCALE_AUTO_SHIFT,  TMC5272_PWM_SCALE(motor), false })
#define TMC5272_PWM_AUTO_PWM_OFS_AUTO_MASK                    0x000000FF
#define TMC5272_PWM_AUTO_PWM_OFS_AUTO_SHIFT                   0
#define TMC5272_PWM_AUTO_PWM_OFS_AUTO_FIELD(motor)            ((RegisterField) { TMC5272_PWM_AUTO_PWM_OFS_AUTO_MASK,  TMC5272_PWM_AUTO_PWM_OFS_AUTO_SHIFT,  TMC5272_PWM_AUTO(motor), false })
#define TMC5272_PWM_AUTO_PWM_GRAD_AUTO_MASK                   0x00FF0000
#define TMC5272_PWM_AUTO_PWM_GRAD_AUTO_SHIFT                  16
#define TMC5272_PWM_AUTO_PWM_GRAD_AUTO_FIELD(motor)           ((RegisterField) { TMC5272_PWM_AUTO_PWM_GRAD_AUTO_MASK,  TMC5272_PWM_AUTO_PWM_GRAD_AUTO_SHIFT,  TMC5272_PWM_AUTO(motor), false })
#define TMC5272_SG4_THRS_SG4_THRS_MASK                        0x000000FF
#define TMC5272_SG4_THRS_SG4_THRS_SHIFT                       0
#define TMC5272_SG4_THRS_SG4_THRS_FIELD(motor)                ((RegisterField) { TMC5272_SG4_THRS_SG4_THRS_MASK,  TMC5272_SG4_THRS_SG4_THRS_SHIFT,  TMC5272_SG4_THRS(motor), false })
#define TMC5272_SG4_THRS_SG4_FILT_EN_MASK                     0x00000100
#define TMC5272_SG4_THRS_SG4_FILT_EN_SHIFT                    8
#define TMC5272_SG4_THRS_SG4_FILT_EN_FIELD(motor)             ((RegisterField) { TMC5272_SG4_THRS_SG4_FILT_EN_MASK,  TMC5272_SG4_THRS_SG4_FILT_EN_SHIFT,  TMC5272_SG4_THRS(motor), false })
#define TMC5272_SG4_THRS_SG_ANGLE_OFFSET_MASK                 0x00000200
#define TMC5272_SG4_THRS_SG_ANGLE_OFFSET_SHIFT                9
#define TMC5272_SG4_THRS_SG_ANGLE_OFFSET_FIELD(motor)         ((RegisterField) { TMC5272_SG4_THRS_SG_ANGLE_OFFSET_MASK,  TMC5272_SG4_THRS_SG_ANGLE_OFFSET_SHIFT,  TMC5272_SG4_THRS(motor), false })
#define TMC5272_SG4_RESULT_SG_RESULT_MASK                     0x000003FF
#define TMC5272_SG4_RESULT_SG_RESULT_SHIFT                    0
#define TMC5272_SG4_RESULT_SG_RESULT_FIELD(motor)             ((RegisterField) { TMC5272_SG4_RESULT_SG_RESULT_MASK,  TMC5272_SG4_RESULT_SG_RESULT_SHIFT,  TMC5272_SG4_RESULT(motor), false })
#define TMC5272_SG4_IND_SG4_IND_0_MASK                        0x000000FF
#define TMC5272_SG4_IND_SG4_IND_0_SHIFT                       0
#define TMC5272_SG4_IND_SG4_IND_0_FIELD(motor)                ((RegisterField) { TMC5272_SG4_IND_SG4_IND_0_MASK,  TMC5272_SG4_IND_SG4_IND_0_SHIFT,  TMC5272_SG4_IND(motor), false })
#define TMC5272_SG4_IND_SG4_IND_1_MASK                        0x0000FF00
#define TMC5272_SG4_IND_SG4_IND_1_SHIFT                       8
#define TMC5272_SG4_IND_SG4_IND_1_FIELD(motor)                ((RegisterField) { TMC5272_SG4_IND_SG4_IND_1_MASK,  TMC5272_SG4_IND_SG4_IND_1_SHIFT,  TMC5272_SG4_IND(motor), false })
#define TMC5272_SG4_IND_SG4_IND_2_MASK                        0x00FF0000
#define TMC5272_SG4_IND_SG4_IND_2_SHIFT                       16
#define TMC5272_SG4_IND_SG4_IND_2_FIELD(motor)                ((RegisterField) { TMC5272_SG4_IND_SG4_IND_2_MASK,  TMC5272_SG4_IND_SG4_IND_2_SHIFT,  TMC5272_SG4_IND(motor), false })
#define TMC5272_SG4_IND_SG4_IND_3_MASK                        0xFF000000
#define TMC5272_SG4_IND_SG4_IND_3_SHIFT                       24
#define TMC5272_SG4_IND_SG4_IND_3_FIELD(motor)                ((RegisterField) { TMC5272_SG4_IND_SG4_IND_3_MASK,  TMC5272_SG4_IND_SG4_IND_3_SHIFT,  TMC5272_SG4_IND(motor), false })

#endif
