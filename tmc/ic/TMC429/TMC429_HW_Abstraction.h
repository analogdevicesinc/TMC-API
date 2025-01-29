/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC429_HW_ABSTRACTION
#define TMC429_HW_ABSTRACTION

// Constants
#define TMC429_REGISTER_COUNT   128
#define TMC429_MOTORS           3
#define TMC429_WRITE_READ_BIT   0x01
#define TMC429_ADDRESS_MASK     0x7E
#define TMC429_MAX_VELOCITY     0x7FF
#define TMC429_MAX_ACCELERATION 0x7FF

// TMC429 Motor numbers to be combined with the addresses of the motor register set
// (e.g. TMC429_X_TARGET|TMC429_MOTOR1).
#define TMC429_MOTOR0        0
#define TMC429_MOTOR1        0x20
#define TMC429_MOTOR2        0x40
#define TMC429_MOTOR(motor)  (motor<<5)

// TMC429 Motor Register Set
#define TMC429_X_TARGET(motor)           (0x00|TMC429_MOTOR(motor))
#define TMC429_X_ACTUAL(motor)           (0x02|TMC429_MOTOR(motor))
#define TMC429_V_MIN(motor)              (0x04|TMC429_MOTOR(motor))
#define TMC429_V_MAX(motor)              (0x06|TMC429_MOTOR(motor))
#define TMC429_V_TARGET(motor)           (0x08|TMC429_MOTOR(motor))
#define TMC429_V_ACTUAL(motor)           (0x0A|TMC429_MOTOR(motor))
#define TMC429_A_MAX(motor)              (0x0C|TMC429_MOTOR(motor))
#define TMC429_A_ACTUAL(motor)           (0x0E|TMC429_MOTOR(motor))
#define TMC429_AGTAT_ALEAT(motor)        (0x10|TMC429_MOTOR(motor))
#define TMC429_PMUL_PDIV(motor)          (0x12|TMC429_MOTOR(motor))
#define TMC429_REF_CONF_RM(motor)        (0x14|TMC429_MOTOR(motor))
#define TMC429_IMASK_IFLAGS(motor)       (0x16|TMC429_MOTOR(motor))
#define TMC429_PULSE_DIV_RAMP_DIV(motor) (0x18|TMC429_MOTOR(motor))
#define TMC429_DX_REF_TOLERANCE(motor)   (0x1A|TMC429_MOTOR(motor))
#define TMC429_X_LATCHED(motor)          (0x1C|TMC429_MOTOR(motor))
#define TMC429_USTEP_COUNT_429(motor)    (0x1E|TMC429_MOTOR(motor))

// Other TMC429 registers (these exist only once)
#define TMC429_DATAGRAM_LOW_WORD   0x60
#define TMC429_DATAGRAM_HIGH_WORD  0x62
#define TMC429_COVER_POS_LEN       0x64
#define TMC429_COVER_DATAGRAM      0x66

#define TMC429_IF_CONFIG_429       0x68
#define TMC429_POS_COMP_429        0x6A
#define TMC429_POS_COMP_INT_429    0x6C
#define TMC429_POWER_DOWN_429      0x70
#define TMC429_TYPE_VERSION_429    0x72

#define TMC429_REF_SWITCHES                           0x7C
#define TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL 0x7E

// TMC429 read bit: combine this with any register address for reading from that
// register (otherwise it will be a write).
// e.g. TMC429_X_ACTUAL|TMC429_MOTOR0|TMC429_READ
#define TMC429_READ 0x01

// TMC429 ramp modes
#define TMC429_RAMP_MODE_RAMP      0
#define TMC429_RAMP_MODE_SOFT      1
#define TMC429_RAMP_MODE_VELOCITY  2
#define TMC429_RAMP_MODE_HOLD      3

// TMC429 stop switch modes
#define TMC429_NO_REF    0x03
#define TMC429_SOFT_REF  0x04

#define TMC429_NO_LIMIT    0
#define TMC429_HARD_LIMIT  1
#define TMC429_SOFT_LIMIT  2

// TMC429 stop switch flags
#define TMC429_REFSW_LEFT   0x02
#define TMC429_REFSW_RIGHT  0x01

// Flags of the TMC429 status byte
#define TMC429_M0_POS_REACHED  0x01
#define TMC429_M1_POS_REACHED  0x04
#define TMC429_M2_POS_REACHED  0x10
#define TMC429_STATUS_CDGW     0x40
#define TMC429_STATUS_INT      0x80

// TMC429 interrupt flags
#define TMC429_IFLAG_POS_REACHED      0x01
#define TMC429_IFLAG_REF_WRONG        0x02
#define TMC429_IFLAG_REF_MISS         0x04
#define TMC429_IFLAG_STOP             0x08
#define TMC429_IFLAG_STOP_LEFT_LOW    0x10
#define TMC429_IFLAG_STOP_RIGHT_LOW   0x20
#define TMC429_IFLAG_STOP_LEFT_HIGH   0x40
#define TMC429_IFLAG_STOP_RIGHT_HIGH  0x80

// TMC429 interface configuration bits
#define TMC429_IFCONF_INV_REF       0x0001
#define TMC429_IFCONF_SDO_INT       0x0002
#define TMC429_IFCONF_STEP_HALF     0x0004
#define TMC429_IFCONF_INV_STEP      0x0008
#define TMC429_IFCONF_INV_DIR       0x0010
#define TMC429_IFCONF_EN_SD         0x0020
#define TMC429_IFCONF_POS_COMP_0    0x0000
#define TMC429_IFCONF_POS_COMP_1    0x0040
#define TMC429_IFCONF_POS_COMP_2    0x0080
#define TMC429_IFCONF_POS_COMP_OFF  0x00C0
#define TMC429_IFCONF_EN_REFR       0x0100

// TMC429 microstep resolution selection bits
// Fullstep to microstep ratios
#define TMC429_USRS_1_1  0x00
#define TMC429_USRS_1_2  0x01
#define TMC429_USRS_1_4  0x02
#define TMC429_USRS_1_8  0x03
#define TMC429_USRS_1_16 0x04
#define TMC429_USRS_1_32 0x05
#define TMC429_USRS_1_64 0x06


// TMC429 fields - three stepper motor register sets
#define TMC429_X_TARGET_MASK                  0x00FFFFFF
#define TMC429_X_TARGET_SHIFT                 0
#define TMC429_X_TARGET_FIELD(motor)          ((RegisterField) { TMC429_X_TARGET_MASK,  TMC429_X_TARGET_SHIFT,  TMC429_X_TARGET(motor), false })
#define TMC429_X_ACTUAL_MASK                  0x00FFFFFF
#define TMC429_X_ACTUAL_SHIFT                 0
#define TMC429_X_ACTUAL_FIELD(motor)          ((RegisterField) { TMC429_X_ACTUAL_MASK,  TMC429_X_ACTUAL_SHIFT,  TMC429_X_ACTUAL(motor), true })
#define TMC429_V_MIN_MASK                     0x000007FF
#define TMC429_V_MIN_SHIFT                    0
#define TMC429_V_MIN_FIELD(motor)             ((RegisterField) { TMC429_V_MIN_MASK,  TMC429_V_MIN_SHIFT,  TMC429_V_MIN(motor), false })
#define TMC429_V_MAX_MASK                     0x000007FF
#define TMC429_V_MAX_SHIFT                    0
#define TMC429_V_MAX_FIELD(motor)             ((RegisterField) { TMC429_V_MAX_MASK,  TMC429_V_MAX_SHIFT,  TMC429_V_MAX(motor), false })
#define TMC429_V_TARGET_MASK                  0x00000FFF
#define TMC429_V_TARGET_SHIFT                 0
#define TMC429_V_TARGET_FIELD(motor)          ((RegisterField) { TMC429_V_TARGET_MASK,  TMC429_V_TARGET_SHIFT,  TMC429_V_TARGET(motor), false })
#define TMC429_V_ACTUAL_MASK                  0x00000FFF
#define TMC429_V_ACTUAL_SHIFT                 0
#define TMC429_V_ACTUAL_FIELD(motor)          ((RegisterField) { TMC429_V_ACTUAL_MASK,  TMC429_V_ACTUAL_SHIFT,  TMC429_V_ACTUAL(motor), true })
#define TMC429_A_MAX_MASK                     0x000007FF
#define TMC429_A_MAX_SHIFT                    0
#define TMC429_A_MAX_FIELD(motor)             ((RegisterField) { TMC429_A_MAX_MASK,  TMC429_A_MAX_SHIFT,  TMC429_A_MAX(motor), false })
#define TMC429_A_ACTUAL_MASK                  0x00000FFF
#define TMC429_A_ACTUAL_SHIFT                 0
#define TMC429_A_ACTUAL_FIELD(motor)          ((RegisterField) { TMC429_A_ACTUAL_MASK,  TMC429_A_ACTUAL_SHIFT,  TMC429_A_ACTUAL(motor), true })
#define TMC429_IS_AGTAT_MASK                  0x00700000
#define TMC429_IS_AGTAT_SHIFT                 20
#define TMC429_IS_AGTAT_FIELD(motor)          ((RegisterField) { TMC429_IS_AGTAT_MASK,  TMC429_IS_AGTAT_SHIFT,  TMC429_AGTAT_ALEAT(motor), false })
#define TMC429_IS_ALEAT_MASK                  0x00070000
#define TMC429_IS_ALEAT_SHIFT                 16
#define TMC429_IS_ALEAT_FIELD(motor)          ((RegisterField) { TMC429_IS_ALEAT_MASK,  TMC429_IS_ALEAT_SHIFT,  TMC429_AGTAT_ALEAT(motor), false })
#define TMC429_IS_v0_MASK                     0x00007000
#define TMC429_IS_v0_SHIFT                    12
#define TMC429_IS_v0_FIELD(motor)             ((RegisterField) { TMC429_IS_v0_MASK,  TMC429_IS_v0_SHIFT,  TMC429_AGTAT_ALEAT(motor), false })
#define TMC429_A_THRESHOLD_MASK               0x000007FF
#define TMC429_A_THRESHOLD_SHIFT              0
#define TMC429_A_THRESHOLD_FIELD(motor)       ((RegisterField) { TMC429_A_THRESHOLD_MASK,  TMC429_A_THRESHOLD_SHIFT,  TMC429_AGTAT_ALEAT(motor), false })
#define TMC429_PMUL_MASK                      0x00007F00
#define TMC429_PMUL_SHIFT                     8
#define TMC429_PMUL_FIELD(motor)              ((RegisterField) { TMC429_PMUL_MASK,  TMC429_PMUL_SHIFT,  TMC429_PMUL_PDIV(motor), false })
#define TMC429_PDIV_MASK                      0x0000000F
#define TMC429_PDIV_SHIFT                     0
#define TMC429_PDIV_FIELD(motor)              ((RegisterField) { TMC429_PDIV_MASK,  TMC429_PDIV_SHIFT,  TMC429_PMUL_PDIV(motor), false })
#define TMC429_LATCH_POSITION_MASK            0x00010000
#define TMC429_LATCH_POSITION_SHIFT           16
#define TMC429_LATCH_POSITION_FIELD(motor)    ((RegisterField) { TMC429_LATCH_POSITION_MASK,  TMC429_LATCH_POSITION_SHIFT,  TMC429_X_LATCHED(motor), false })
#define TMC429_REF_CONF_MASK                  0x00000F00
#define TMC429_REF_CONF_SHIFT                 8
#define TMC429_REF_CONF_FIELD(motor)          ((RegisterField) { TMC429_REF_CONF_MASK,  TMC429_REF_CONF_SHIFT,  TMC429_REF_CONF_RM(motor), false })
#define TMC429_RAMP_MODE_MASK                 0x00000002
#define TMC429_RAMP_MODE_SHIFT                0
#define TMC429_RAMP_MODE_FIELD(motor)         ((RegisterField) { TMC429_RAMP_MODE_MASK,  TMC429_RAMP_MODE_SHIFT,  TMC429_REF_CONF_RM(motor), false })
#define TMC429_INTERRUPT_MASK_MASK            0x0000FF00
#define TMC429_INTERRUPT_SHIFT                8
#define TMC429_INTERRUPT_FIELD(motor)         ((RegisterField) { TMC429_INTERRUPT_MASK_MASK,  TMC429_INTERRUPT_SHIFT,  TMC429_IMASK_IFLAGS(motor), false })
#define TMC429_INTERRUPT_FLAGS_MASK           0x000000FF
#define TMC429_INTERRUPT_FLAGS_SHIFT          0
#define TMC429_INTERRUPT_FLAGS_FIELD(motor)   ((RegisterField) { TMC429_INTERRUPT_FLAGS_MASK,  TMC429_INTERRUPT_FLAGS_SHIFT,  TMC429_IMASK_IFLAGS(motor), false })
#define TMC429_PULSE_DIV_MASK                 0x0000F000
#define TMC429_PULSE_DIV_SHIFT                12
#define TMC429_PULSE_DIV_FIELD(motor)         ((RegisterField) { TMC429_PULSE_DIV_MASK,  TMC429_PULSE_DIV_SHIFT,  TMC429_PULSE_DIV_RAMP_DIV(motor), false })
#define TMC429_RAMP_DIV_MASK                  0x00000F00
#define TMC429_RAMP_DIV_SHIFT                 8
#define TMC429_RAMP_DIV_FIELD(motor)          ((RegisterField) { TMC429_RAMP_DIV_MASK,  TMC429_RAMP_DIV_SHIFT,  TMC429_PULSE_DIV_RAMP_DIV(motor), false })
#define TMC429_USRS_MASK                      0x00000003
#define TMC429_USRS_SHIFT                     0
#define TMC429_USRS_FIELD(motor)              ((RegisterField) { TMC429_USRS_MASK,  TMC429_USRS_SHIFT,  TMC429_PULSE_DIV_RAMP_DIV(motor), false })
#define TMC429_DX_REF_TOLERANCE_MASK          0x00000FFF
#define TMC429_DX_REF_TOLERANCE_SHIFT         0
#define TMC429_DX_REF_TOLERANCE_FIELD(motor)  ((RegisterField) { TMC429_DX_REF_TOLERANCE_MASK,  TMC429_DX_REF_TOLERANCE_SHIFT,  TMC429_DX_REF_TOLERANCE(motor), false })
#define TMC429_X_LATCHED_MASK                 0x00FFFFFF
#define TMC429_X_LATCHED_SHIFT                0
#define TMC429_X_LATCHED_FIELD(motor)         ((RegisterField) { TMC429_X_LATCHED_MASK,  TMC429_X_LATCHED_SHIFT,  TMC429_X_LATCHED(motor), true })
#define TMC429_USTEP_COUNT_MASK               0x000000FF
#define TMC429_USTEP_COUNT_SHIFT              0
#define TMC429_USTEP_COUNT_FIELD(motor)       ((RegisterField) { TMC429_USTEP_COUNT_MASK,  TMC429_USTEP_COUNT_SHIFT,  TMC429_USTEP_COUNT_429(motor), false })

// Common TMC429 register fields
#define TMC429_DATAGRAM_LOW_WORD_MASK         0x00FFFFFF
#define TMC429_DATAGRAM_LOW_WORD_SHIFT        0
#define TMC429_DATAGRAM_LOW_WORD_FIELD        ((RegisterField) { TMC429_DATAGRAM_LOW_WORD_MASK,  TMC429_DATAGRAM_LOW_WORD_SHIFT,  TMC429_DATAGRAM_LOW_WORD, false })
#define TMC429_DATAGRAM_HIGH_WORD_MASK        0x00FFFFFF
#define TMC429_DATAGRAM_HIGH_WORD_SHIFT       0
#define TMC429_DATAGRAM_HIGH_WORD_FIELD       ((RegisterField) { TMC429_DATAGRAM_HIGH_WORD_MASK,  TMC429_DATAGRAM_HIGH_WORD_SHIFT,  TMC429_DATAGRAM_HIGH_WORD, false })
#define TMC429_COVER_DATAGRAM_WAITING_MASK    0x00800000
#define TMC429_COVER_DATAGRAM_WAITING_SHIFT   23
#define TMC429_COVER_DATAGRAM_WAITING_FIELD   ((RegisterField) { TMC429_COVER_DATAGRAM_WAITING_MASK,  TMC429_COVER_DATAGRAM_WAITING_SHIFT,  TMC429_COVER_POS_LEN, false })
#define TMC429_COVER_POSITION_MASK            0x00003F00
#define TMC429_COVER_POSITION_SHIFT           8
#define TMC429_COVER_POSITION_FIELD           ((RegisterField) { TMC429_COVER_POSITION_MASK,  TMC429_COVER_POSITION_SHIFT,  TMC429_COVER_POS_LEN, false })
#define TMC429_COVER_LENGTH_MASK              0x0000001F
#define TMC429_COVER_LENGTH_SHIFT             0
#define TMC429_COVER_LENGTH_FIELD             ((RegisterField) { TMC429_COVER_LENGTH_MASK,  TMC429_COVER_LENGTH_SHIFT,  TMC429_COVER_POS_LEN, false })
#define TMC429_COVER_DATAGRAM_MASK            0x00FFFFFF
#define TMC429_COVER_DATAGRAM_SHIFT           0
#define TMC429_COVER_DATAGRAM_FIELD           ((RegisterField) { TMC429_COVER_DATAGRAM_MASK,  TMC429_COVER_DATAGRAM_SHIFT,  TMC429_COVER_DATAGRAM, false })
#define TMC429_IF_CONFIG_MASK                 0x000001FF
#define TMC429_IF_CONFIG_SHIFT                0
#define TMC429_IF_CONFIG_FIELD                ((RegisterField) { TMC429_IF_CONFIG_MASK,  TMC429_IF_CONFIG_SHIFT,  TMC429_IF_CONFIG_429, false })
#define TMC429_POS_COMP_MASK                  0x00FFFFFF
#define TMC429_POS_COMP_SHIFT                 0
#define TMC429_POS_COMP_FIELD                 ((RegisterField) { TMC429_POS_COMP_MASK,  TMC429_POS_COMP_SHIFT,  TMC429_POS_COMP_429, false })
#define TMC429_POS_COMP_INT_MASK              0x00FF0000
#define TMC429_POS_COMP_INT_SHIFT             16
#define TMC429_POS_COMP_INT_FIELD             ((RegisterField) { TMC429_POS_COMP_INT_MASK,  TMC429_POS_COMP_INT_SHIFT,  TMC429_POS_COMP_INT_429, false })
#define TMC429_POS_COMP_M_MASK                0x00000100
#define TMC429_POS_COMP_M_SHIFT               8
#define TMC429_POS_COMP_M_FIELD               ((RegisterField) { TMC429_POS_COMP_M_MASK,  TMC429_POS_COMP_M_SHIFT,  TMC429_POS_COMP_INT_429, false })
#define TMC429_POS_COMP_I_MASK                0x00000001
#define TMC429_POS_COMP_I_SHIFT               0
#define TMC429_POS_COMP_I_FIELD               ((RegisterField) { TMC429_POS_COMP_I_MASK,  TMC429_POS_COMP_I_SHIFT,  TMC429_POS_COMP_INT_429, false })
#define TMC429_POWER_DOWN_MASK                0x00FFFFFF
#define TMC429_POWER_DOWN_SHIFT               0
#define TMC429_POWER_DOWN_FIELD               ((RegisterField) { TMC429_POWER_DOWN_MASK,  TMC429_POWER_DOWN_SHIFT,  TMC429_POWER_DOWN_429, false })
#define TMC429_TYPE_VERSION_MASK              0x00FFFFFF
#define TMC429_TYPE_VERSION_SHIFT             0
#define TMC429_TYPE_VERSION_FIELD             ((RegisterField) { TMC429_TYPE_VERSION_MASK,  TMC429_TYPE_VERSION_SHIFT,  TMC429_TYPE_VERSION_429, false })
#define TMC429_REF_SWITCHES_MASK              0x0000003F
#define TMC429_REF_SWITCHES_SHIFT             0
#define TMC429_REF_SWITCHES_FIELD             ((RegisterField) { TMC429_REF_SWITCHES_MASK,  TMC429_REF_SWITCHES_SHIFT,  TMC429_REF_SWITCHES, false })

// Stepper Motor Global Parameter register (SMGP)
#define TMC429_MOT1R_MASK                     0x00200000
#define TMC429_MOT1R_SHIFT                    21
#define TMC429_MOT1R_FIELD                    ((RegisterField) { TMC429_MOT1R_MASK,  TMC429_MOT1R_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_REFMUX_MASK                    0x00100000
#define TMC429_REFMUX_SHIFT                   20
#define TMC429_REFMUX_FIELD                   ((RegisterField) { TMC429_REFMUX_MASK,  TMC429_REFMUX_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_CONT_UPDATE_MASK               0x00010000
#define TMC429_CONT_UPDATE_SHIFT              16
#define TMC429_CONT_UPDATE_FIELD              ((RegisterField) { TMC429_CONT_UPDATE_MASK,  TMC429_CONT_UPDATE_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_CLK2_DIV_MASK                  0x0000FF00
#define TMC429_CLK2_DIV_SHIFT                 8
#define TMC429_CLK2_DIV_FIELD                 ((RegisterField) { TMC429_CLK2_DIV_MASK,  TMC429_CLK2_DIV_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_STPDIV_MASK                    0x00000F00
#define TMC429_STPDIV_SHIFT                   8
#define TMC429_STPDIV_FIELD                   ((RegisterField) { TMC429_STPDIV_MASK,  TMC429_STPDIV_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_cs_ComInd_MASK                 0x00000080
#define TMC429_cs_ComInd_SHIFT                7
#define TMC429_cs_ComInd_FIELD                ((RegisterField) { TMC429_cs_ComInd_MASK,  TMC429_cs_ComInd_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_POLARITIES_MASK                0x0000007C
#define TMC429_POLARITIES_SHIFT               2
#define TMC429_POLARITIES_FIELD               ((RegisterField) { TMC429_POLARITIES_MASK,  TMC429_POLARITIES_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })
#define TMC429_LSMD_MASK                      0x00000002
#define TMC429_LSMD_SHIFT                     0
#define TMC429_LSMD_FIELD                     ((RegisterField) { TMC429_LSMD_MASK,  TMC429_LSMD_SHIFT,  TMC429_STEPPER_MOTOR_GLOBAL_PARAMETER_CONTROL, false })

#endif /* TMC429_HW_ABSTRACTION */
