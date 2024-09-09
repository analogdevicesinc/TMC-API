/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC5272_HW_ABSTRACTION
#define TMC5272_HW_ABSTRACTION

// Constants

#define TMC5031_REGISTER_COUNT   128 // Default register count
#define TMC5031_MOTORS           2
#define TMC5031_WRITE_BIT        0x80
#define TMC5031_ADDRESS_MASK     0x7F
#define TMC5031_MAX_VELOCITY     8388096
#define TMC5031_MAX_ACCELERATION (uint16_t)  65535

// Rampenmodi (Register TMC562_RAMPMODE)
#define TMC5031_MODE_POSITION  0
#define TMC5031_MODE_VELPOS    1
#define TMC5031_MODE_VELNEG    2
#define TMC5031_MODE_HOLD      3

// Registers in TMC5272

#define TMC5031_MOTOR_ADDR(m)      (0x20 << m)
#define TMC5031_MOTOR_ADDR_DRV(m)  (m << 4)
#define TMC5031_MOTOR_ADDR_PWM(m)  (m << 3)

#define TMC5031_GCONF      0x00
#define TMC5031_GSTAT      0x01
#define TMC5031_IFCNT      0x02
#define TMC5031_SLAVECONF  0x03
#define TMC5031_INP_OUT    0x04
#define TMC5031_X_COMPARE  0x05
                                                                         // motor = 0       motor = 1
#define TMC5031_PWMCONF(motor)     (0x10|TMC5031_MOTOR_ADDR_PWM(motor))  //      0x10            0x18
#define TMC5031_PWM_STATUS(motor)  (0x11|TMC5031_MOTOR_ADDR_PWM(motor))  //      0x11            0x19

                                                                         // motor = 0       motor = 1
#define TMC5031_RAMPMODE(motor)    (0x00|TMC5031_MOTOR_ADDR(motor))      //      0x20            0x40
#define TMC5031_XACTUAL(motor)     (0x01|TMC5031_MOTOR_ADDR(motor))      //      0x21            0x41
#define TMC5031_VACTUAL(motor)     (0x02|TMC5031_MOTOR_ADDR(motor))      //      0x22            0x42
#define TMC5031_VSTART(motor)      (0x03|TMC5031_MOTOR_ADDR(motor))      //      0x23            0x43
#define TMC5031_A1(motor)          (0x04|TMC5031_MOTOR_ADDR(motor))      //      0x24            0x44
#define TMC5031_V1(motor)          (0x05|TMC5031_MOTOR_ADDR(motor))      //      0x25            0x45
#define TMC5031_AMAX(motor)        (0x06|TMC5031_MOTOR_ADDR(motor))      //      0x26            0x46
#define TMC5031_VMAX(motor)        (0x07|TMC5031_MOTOR_ADDR(motor))      //      0x27            0x47
#define TMC5031_DMAX(motor)        (0x08|TMC5031_MOTOR_ADDR(motor))      //      0x28            0x48
#define TMC5031_D1(motor)          (0x0A|TMC5031_MOTOR_ADDR(motor))      //      0x2A            0x4A
#define TMC5031_VSTOP(motor)       (0x0B|TMC5031_MOTOR_ADDR(motor))      //      0x2B            0x4B
#define TMC5031_TZEROWAIT(motor)   (0x0C|TMC5031_MOTOR_ADDR(motor))      //      0x2C            0x4C
#define TMC5031_XTARGET(motor)     (0x0D|TMC5031_MOTOR_ADDR(motor))      //      0x2D            0x4D
#define TMC5031_IHOLD_IRUN(motor)  (0x10|TMC5031_MOTOR_ADDR(motor))      //      0x30            0x50
#define TMC5031_VCOOLTHRS(motor)   (0x11|TMC5031_MOTOR_ADDR(motor))      //      0x31            0x51
#define TMC5031_VHIGH(motor)       (0x12|TMC5031_MOTOR_ADDR(motor))      //      0x32            0x52
#define TMC5031_VDCMIN(motor)      (0x13|TMC5031_MOTOR_ADDR(motor))      //      0x33            0x53
#define TMC5031_SWMODE(motor)      (0x14|TMC5031_MOTOR_ADDR(motor))      //      0x34            0x54
#define TMC5031_RAMPSTAT(motor)    (0x15|TMC5031_MOTOR_ADDR(motor))      //      0x35            0x55
#define TMC5031_XLATCH(motor)      (0x16|TMC5031_MOTOR_ADDR(motor))      //      0x36            0x56
#define TMC5031_ENCMODE(motor)     (0x18|TMC5031_MOTOR_ADDR(motor))      //      0x38            0x58
#define TMC5031_XENC(motor)        (0x19|TMC5031_MOTOR_ADDR(motor))      //      0x39            0x59
#define TMC5031_ENC_CONST(motor)   (0x1A|TMC5031_MOTOR_ADDR(motor))      //      0x3A            0x5A
#define TMC5031_ENC_STATUS(motor)  (0x1B|TMC5031_MOTOR_ADDR(motor))      //      0x3B            0x5B
#define TMC5031_ENC_LATCH(motor)   (0x1C|TMC5031_MOTOR_ADDR(motor))      //      0x3C            0x5C

                                                                         // motor = 0       motor = 1
#define TMC5031_MSLUT0(motor)      (0x60|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x60            0x70
#define TMC5031_MSLUT1(motor)      (0x61|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x61            0x71
#define TMC5031_MSLUT2(motor)      (0x62|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x62            0x72
#define TMC5031_MSLUT3(motor)      (0x63|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x63            0x73
#define TMC5031_MSLUT4(motor)      (0x64|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x64            0x74
#define TMC5031_MSLUT5(motor)      (0x65|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x65            0x75
#define TMC5031_MSLUT6(motor)      (0x66|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x66            0x76
#define TMC5031_MSLUT7(motor)      (0x67|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x67            0x77
#define TMC5031_MSLUTSEL(motor)    (0x68|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x68            0x78
#define TMC5031_MSLUTSTART(motor)  (0x69|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x69            0x79
#define TMC5031_MSCNT(motor)       (0x6A|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6A            0x7A
#define TMC5031_MSCURACT(motor)    (0x6B|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6B            0x7B
#define TMC5031_CHOPCONF(motor)    (0x6C|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6C            0x7C
#define TMC5031_COOLCONF(motor)    (0x6D|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6D            0x7D
#define TMC5031_DCCTRL(motor)      (0x6E|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6E            0x7E
#define TMC5031_DRVSTATUS(motor)   (0x6F|TMC5031_MOTOR_ADDR_DRV(motor))  //      0x6F            0x7F

// Register fields in TMC5272

#define TMC5031_POSCMP_ENABLE_MASK       0x00000008
#define TMC5031_POSCMP_ENABLE_SHIFT      3
#define TMC5031_POSCMP_ENABLE_FIELD(motor)      ((RegisterField) {TMC5031_POSCMP_ENABLE_MASK, TMC5031_POSCMP_ENABLE_SHIFT, TMC5031_GCONF, false})
#define TMC5031_TEST_MODE_MASK           0x00000080
#define TMC5031_TEST_MODE_SHIFT          7
#define TMC5031_TEST_MODE_FIELD(motor)          ((RegisterField) {TMC5031_TEST_MODE_MASK, TMC5031_TEST_MODE_SHIFT, TMC5031_GCONF, false})
#define TMC5031_SHAFT1_MASK              0x00000100
#define TMC5031_SHAFT1_SHIFT             8
#define TMC5031_SHAFT1_FIELD(motor)             ((RegisterField) {TMC5031_SHAFT1_MASK, TMC5031_SHAFT1_SHIFT, TMC5031_GCONF, false})
#define TMC5031_SHAFT2_MASK              0x00000200
#define TMC5031_SHAFT2_SHIFT             9
#define TMC5031_SHAFT2_FIELD(motor)             ((RegisterField) {TMC5031_SHAFT2_MASK, TMC5031_SHAFT2_SHIFT, TMC5031_GCONF, false})
#define TMC5031_LOCK_GCONF_MASK          0x00000400
#define TMC5031_LOCK_GCONF_SHIFT         10
#define TMC5031_LOCK_GCONF_FIELD(motor)         ((RegisterField) {TMC5031_LOCK_GCONF_MASK, TMC5031_LOCK_GCONF_SHIFT, TMC5031_GCONF, false})
#define TMC5031_RESET_MASK               0x00000001
#define TMC5031_RESET_SHIFT              0
#define TMC5031_RESET_FIELD(motor)              ((RegisterField) {TMC5031_RESET_MASK, TMC5031_RESET_SHIFT, TMC5031_GSTAT, false})
#define TMC5031_DRV_ERR1_MASK            0x00000002
#define TMC5031_DRV_ERR1_SHIFT           1
#define TMC5031_DRV_ERR1_FIELD(motor)           ((RegisterField) {TMC5031_DRV_ERR1_MASK, TMC5031_DRV_ERR1_SHIFT, TMC5031_GSTAT, false})
#define TMC5031_UV_CP_MASK               0x00000008
#define TMC5031_UV_CP_SHIFT              3
#define TMC5031_UV_CP_FIELD(motor)              ((RegisterField) {TMC5031_UV_CP_MASK, TMC5031_UV_CP_SHIFT, TMC5031_GSTAT, false})
#define TMC5031_TEST_SEL_MASK            0x0000000F
#define TMC5031_TEST_SEL_SHIFT           0
#define TMC5031_TEST_SEL_FIELD(motor)           ((RegisterField) {TMC5031_TEST_SEL_MASK, TMC5031_TEST_SEL_SHIFT, TMC5031_SLAVECONF, false})
#define TMC5031_DRV_ENN_MASK             0x00000080
#define TMC5031_DRV_ENN_SHIFT            7
#define TMC5031_DRV_ENN_FIELD(motor)            ((RegisterField) {TMC5031_DRV_ENN_MASK, TMC5031_DRV_ENN_SHIFT, TMC5031_INPUT, false})
#define TMC5031_VERSION_MASK             0xFF000000
#define TMC5031_VERSION_SHIFT            24
#define TMC5031_VERSION_FIELD(motor)            ((RegisterField) {TMC5031_VERSION_MASK, TMC5031_VERSION_SHIFT, TMC5031_INPUT, false})
#define TMC5031_X_COMPARE_MASK           0xFFFFFFFF
#define TMC5031_X_COMPARE_SHIFT          0
#define TMC5031_X_COMPARE_FIELD(motor)          ((RegisterField) {TMC5031_X_COMPARE_MASK, TMC5031_X_COMPARE_SHIFT, TMC5031_X_COMPARE, false})
#define TMC5031_RAMPMODE_MASK            0x00000003
#define TMC5031_RAMPMODE_SHIFT           0
#define TMC5031_RAMPMODE_FIELD(motor)           ((RegisterField) {TMC5031_RAMPMODE_MASK, TMC5031_RAMPMODE_SHIFT, TMC5031_RAMPMODE(motor), false})
#define TMC5031_XACTUAL_MASK             0xFFFFFFFF
#define TMC5031_XACTUAL_SHIFT            0
#define TMC5031_XACTUAL_FIELD(motor)            ((RegisterField) {TMC5031_XACTUAL_MASK, TMC5031_XACTUAL_SHIFT, TMC5031_XACTUAL(motor), true})
#define TMC5031_VACTUAL_MASK             0x00FFFFFF
#define TMC5031_VACTUAL_SHIFT            0
#define TMC5031_VACTUAL_FIELD(motor)            ((RegisterField) {TMC5031_VACTUAL_MASK, TMC5031_VACTUAL_SHIFT, TMC5031_VACTUAL(motor), true})
#define TMC5031_VSTART_MASK              0x0003FFFF
#define TMC5031_VSTART_SHIFT             0
#define TMC5031_VSTART_FIELD(motor)             ((RegisterField) {TMC5031_VSTART_MASK, TMC5031_VSTART_SHIFT, TMC5031_VSTART(motor), false})
#define TMC5031_A1_MASK                  0x0000FFFF
#define TMC5031_A1_SHIFT                 0
#define TMC5031_A1_FIELD(motor)                 ((RegisterField) {TMC5031_A1_MASK, TMC5031_A1_SHIFT, TMC5031_A1(motor), false})
#define TMC5031_V1__MASK                 0x000FFFFF
#define TMC5031_V1__SHIFT                0
#define TMC5031_V1__FIELD(motor)                ((RegisterField) {TMC5031_V1__MASK, TMC5031_V1__SHIFT, TMC5031_V1(motor), false})
#define TMC5031_AMAX_MASK                0x0000FFFF
#define TMC5031_AMAX_SHIFT               0
#define TMC5031_AMAX_FIELD(motor)               ((RegisterField) {TMC5031_AMAX_MASK, TMC5031_AMAX_SHIFT, TMC5031_AMAX(motor), false})
#define TMC5031_VMAX_MASK                0x007FFFFF
#define TMC5031_VMAX_SHIFT               0
#define TMC5031_VMAX_FIELD(motor)               ((RegisterField) {TMC5031_VMAX_MASK, TMC5031_VMAX_SHIFT, TMC5031_VMAX(motor), false})
#define TMC5031_DMAX_MASK                0x0000FFFF
#define TMC5031_DMAX_SHIFT               0
#define TMC5031_DMAX_FIELD(motor)               ((RegisterField) {TMC5031_DMAX_MASK, TMC5031_DMAX_SHIFT, TMC5031_DMAX(motor), false})
#define TMC5031_D1_MASK                  0x0000FFFF
#define TMC5031_D1_SHIFT                 0
#define TMC5031_D1_FIELD(motor)                 ((RegisterField) {TMC5031_D1_MASK, TMC5031_D1_SHIFT, TMC5031_D1(motor), false})
#define TMC5031_VSTOP_MASK               0x0003FFFF
#define TMC5031_VSTOP_SHIFT              0
#define TMC5031_VSTOP_FIELD(motor)              ((RegisterField) {TMC5031_VSTOP_MASK, TMC5031_VSTOP_SHIFT, TMC5031_VSTOP(motor), false})
#define TMC5031_TZEROWAIT_MASK           0x0000FFFF
#define TMC5031_TZEROWAIT_SHIFT          0
#define TMC5031_TZEROWAIT_FIELD(motor)          ((RegisterField) {TMC5031_TZEROWAIT_MASK, TMC5031_TZEROWAIT_SHIFT, TMC5031_TZEROWAIT(motor), false})
#define TMC5031_XTARGET_MASK             0xFFFFFFFF
#define TMC5031_XTARGET_SHIFT            0
#define TMC5031_XTARGET_FIELD(motor)            ((RegisterField) {TMC5031_XTARGET_MASK, TMC5031_XTARGET_SHIFT, TMC5031_XTARGET(motor), true})
#define TMC5031_IHOLD_MASK               0x0000001F
#define TMC5031_IHOLD_SHIFT              0
#define TMC5031_IHOLD_FIELD(motor)              ((RegisterField) {TMC5031_IHOLD_MASK, TMC5031_IHOLD_SHIFT, TMC5031_IHOLD_IRUN(motor), false})
#define TMC5031_IRUN_MASK                0x00001F00
#define TMC5031_IRUN_SHIFT               8
#define TMC5031_IRUN_FIELD(motor)               ((RegisterField) {TMC5031_IRUN_MASK, TMC5031_IRUN_SHIFT, TMC5031_IHOLD_IRUN(motor), false})
#define TMC5031_IHOLDDELAY_MASK          0x000F0000
#define TMC5031_IHOLDDELAY_SHIFT         16
#define TMC5031_IHOLDDELAY_FIELD(motor)         ((RegisterField) {TMC5031_IHOLDDELAY_MASK, TMC5031_IHOLDDELAY_SHIFT, TMC5031_IHOLD_IRUN(motor), false})
#define TMC5031_VCOOLTHRS_MASK           0x007FFFFF
#define TMC5031_VCOOLTHRS_SHIFT          0
#define TMC5031_VCOOLTHRS_FIELD(motor)          ((RegisterField) {TMC5031_VCOOLTHRS_MASK, TMC5031_VCOOLTHRS_SHIFT, TMC5031_VCOOLTHRS(motor), false})
#define TMC5031_VHIGH_MASK               0x007FFFFF
#define TMC5031_VHIGH_SHIFT              0
#define TMC5031_VHIGH_FIELD(motor)              ((RegisterField) {TMC5031_VHIGH_MASK, TMC5031_VHIGH_SHIFT, TMC5031_VHIGH(motor), false})
#define TMC5031_STOP_L_ENABLE_MASK       0x00000001
#define TMC5031_STOP_L_ENABLE_SHIFT      0
#define TMC5031_STOP_L_ENABLE_FIELD(motor)      ((RegisterField) {TMC5031_STOP_L_ENABLE_MASK, TMC5031_STOP_L_ENABLE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_STOP_R_ENABLE_MASK       0x00000002
#define TMC5031_STOP_R_ENABLE_SHIFT      1
#define TMC5031_STOP_R_ENABLE_FIELD(motor)      ((RegisterField) {TMC5031_STOP_R_ENABLE_MASK, TMC5031_STOP_R_ENABLE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_POL_STOP_L_MASK          0x00000004
#define TMC5031_POL_STOP_L_SHIFT         2
#define TMC5031_POL_STOP_L_FIELD(motor)         ((RegisterField) {TMC5031_POL_STOP_L_MASK, TMC5031_POL_STOP_L_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_POL_STOP_R_MASK          0x00000008
#define TMC5031_POL_STOP_R_SHIFT         3
#define TMC5031_POL_STOP_R_FIELD(motor)         ((RegisterField) {TMC5031_POL_STOP_R_MASK, TMC5031_POL_STOP_R_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_SWAP_LR_MASK             0x00000010
#define TMC5031_SWAP_LR_SHIFT            4
#define TMC5031_SWAP_LR_FIELD(motor)            ((RegisterField) {TMC5031_SWAP_LR_MASK, TMC5031_SWAP_LR_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_LATCH_L_ACTIVE_MASK      0x00000020
#define TMC5031_LATCH_L_ACTIVE_SHIFT     5
#define TMC5031_LATCH_L_ACTIVE_FIELD(motor)     ((RegisterField) {TMC5031_LATCH_L_ACTIVE_MASK, TMC5031_LATCH_L_ACTIVE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_LATCH_L_INACTIVE_MASK    0x00000040
#define TMC5031_LATCH_L_INACTIVE_SHIFT   6
#define TMC5031_LATCH_L_INACTIVE_FIELD(motor)   ((RegisterField) {TMC5031_LATCH_L_INACTIVE_MASK, TMC5031_LATCH_L_INACTIVE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_LATCH_R_ACTIVE_MASK      0x00000080
#define TMC5031_LATCH_R_ACTIVE_SHIFT     7
#define TMC5031_LATCH_R_ACTIVE_FIELD(motor)     ((RegisterField) {TMC5031_LATCH_R_ACTIVE_MASK, TMC5031_LATCH_R_ACTIVE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_LATCH_R_INACTIVE_MASK    0x00000100
#define TMC5031_LATCH_R_INACTIVE_SHIFT   8
#define TMC5031_LATCH_R_INACTIVE_FIELD(motor)   ((RegisterField) {TMC5031_LATCH_R_INACTIVE_MASK, TMC5031_LATCH_R_INACTIVE_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_SG_STOP_MASK             0x00000400
#define TMC5031_SG_STOP_SHIFT            10
#define TMC5031_SG_STOP_FIELD(motor)            ((RegisterField) {TMC5031_SG_STOP_MASK, TMC5031_SG_STOP_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_EN_SOFTSTOP_MASK         0x00000800
#define TMC5031_EN_SOFTSTOP_SHIFT        11
#define TMC5031_EN_SOFTSTOP_FIELD(motor)        ((RegisterField) {TMC5031_EN_SOFTSTOP_MASK, TMC5031_EN_SOFTSTOP_SHIFT, TMC5031_SWMODE(motor), false})
#define TMC5031_STATUS_STOP_L_MASK       0x00000001
#define TMC5031_STATUS_STOP_L_SHIFT      0
#define TMC5031_STATUS_STOP_L_FIELD(motor)      ((RegisterField) {TMC5031_STATUS_STOP_L_MASK, TMC5031_STATUS_STOP_L_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_STATUS_STOP_R_MASK       0x00000002
#define TMC5031_STATUS_STOP_R_SHIFT      1
#define TMC5031_STATUS_STOP_R_FIELD(motor)      ((RegisterField) {TMC5031_STATUS_STOP_R_MASK, TMC5031_STATUS_STOP_R_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_STATUS_LATCH_L_MASK      0x00000004
#define TMC5031_STATUS_LATCH_L_SHIFT     2
#define TMC5031_STATUS_LATCH_L_FIELD(motor)     ((RegisterField) {TMC5031_STATUS_LATCH_L_MASK, TMC5031_STATUS_LATCH_L_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_STATUS_LATCH_R_MASK      0x00000008
#define TMC5031_STATUS_LATCH_R_SHIFT     3
#define TMC5031_STATUS_LATCH_R_FIELD(motor)     ((RegisterField) {TMC5031_STATUS_LATCH_R_MASK, TMC5031_STATUS_LATCH_R_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_EVENT_STOP_L_MASK        0x00000010
#define TMC5031_EVENT_STOP_L_SHIFT       4
#define TMC5031_EVENT_STOP_L_FIELD(motor)       ((RegisterField) {TMC5031_EVENT_STOP_L_MASK, TMC5031_EVENT_STOP_L_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_EVENT_STOP_R_MASK        0x00000020
#define TMC5031_EVENT_STOP_R_SHIFT       5
#define TMC5031_EVENT_STOP_R_FIELD(motor)       ((RegisterField) {TMC5031_EVENT_STOP_R_MASK, TMC5031_EVENT_STOP_R_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_EVENT_STOP_SG_MASK       0x00000040
#define TMC5031_EVENT_STOP_SG_SHIFT      6
#define TMC5031_EVENT_STOP_SG_FIELD(motor)      ((RegisterField) {TMC5031_EVENT_STOP_SG_MASK, TMC5031_EVENT_STOP_SG_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_EVENT_POS_REACHED_MASK   0x00000080
#define TMC5031_EVENT_POS_REACHED_SHIFT  7
#define TMC5031_EVENT_POS_REACHED_FIELD(motor)  ((RegisterField) {TMC5031_EVENT_POS_REACHED_MASK, TMC5031_EVENT_POS_REACHED_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_VELOCITY_REACHED_MASK    0x00000100
#define TMC5031_VELOCITY_REACHED_SHIFT   8
#define TMC5031_VELOCITY_REACHED_FIELD(motor)   ((RegisterField) {TMC5031_VELOCITY_REACHED_MASK, TMC5031_VELOCITY_REACHED_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_POSITION_REACHED_MASK    0x00000200
#define TMC5031_POSITION_REACHED_SHIFT   9
#define TMC5031_POSITION_REACHED_FIELD(motor)   ((RegisterField) {TMC5031_POSITION_REACHED_MASK, TMC5031_POSITION_REACHED_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_VZERO_MASK               0x00000400
#define TMC5031_VZERO_SHIFT              10
#define TMC5031_VZERO_FIELD(motor)              ((RegisterField) {TMC5031_VZERO_MASK, TMC5031_VZERO_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_T_ZEROWAIT_ACTIVE_MASK   0x00000800
#define TMC5031_T_ZEROWAIT_ACTIVE_SHIFT  11
#define TMC5031_T_ZEROWAIT_ACTIVE_FIELD(motor)  ((RegisterField) {TMC5031_T_ZEROWAIT_ACTIVE_MASK, TMC5031_T_ZEROWAIT_ACTIVE_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_SECOND_MOVE_MASK         0x00001000
#define TMC5031_SECOND_MOVE_SHIFT        12
#define TMC5031_SECOND_MOVE_FIELD(motor)        ((RegisterField) {TMC5031_SECOND_MOVE_MASK, TMC5031_SECOND_MOVE_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_STATUS_SG_MASK           0x00002000
#define TMC5031_STATUS_SG_SHIFT          13
#define TMC5031_STATUS_SG_FIELD(motor)          ((RegisterField) {TMC5031_STATUS_SG_MASK, TMC5031_STATUS_SG_SHIFT, TMC5031_RAMPSTAT(motor), false})
#define TMC5031_XLATCH_MASK              0xFFFFFFFF
#define TMC5031_XLATCH_SHIFT             0
#define TMC5031_XLATCH_FIELD(motor)             ((RegisterField) {TMC5031_XLATCH_MASK, TMC5031_XLATCH_SHIFT, TMC5031_XLATCH(motor), false})
#define TMC5031_OFS0_MASK                0x00000001
#define TMC5031_OFS0_SHIFT               0
#define TMC5031_OFS0_FIELD(motor)               ((RegisterField) {TMC5031_OFS0_MASK, TMC5031_OFS0_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS1_MASK                0x00000002
#define TMC5031_OFS1_SHIFT               1
#define TMC5031_OFS1_FIELD(motor)               ((RegisterField) {TMC5031_OFS1_MASK, TMC5031_OFS1_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS2_MASK                0x00000004
#define TMC5031_OFS2_SHIFT               2
#define TMC5031_OFS2_FIELD(motor)               ((RegisterField) {TMC5031_OFS2_MASK, TMC5031_OFS2_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS3_MASK                0x00000008
#define TMC5031_OFS3_SHIFT               3
#define TMC5031_OFS3_FIELD(motor)               ((RegisterField) {TMC5031_OFS3_MASK, TMC5031_OFS3_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS4_MASK                0x00000010
#define TMC5031_OFS4_SHIFT               4
#define TMC5031_OFS4_FIELD(motor)               ((RegisterField) {TMC5031_OFS4_MASK, TMC5031_OFS4_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS5_MASK                0x00000020
#define TMC5031_OFS5_SHIFT               5
#define TMC5031_OFS5_FIELD(motor)               ((RegisterField) {TMC5031_OFS5_MASK, TMC5031_OFS5_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS6_MASK                0x00000040
#define TMC5031_OFS6_SHIFT               6
#define TMC5031_OFS6_FIELD(motor)               ((RegisterField) {TMC5031_OFS6_MASK, TMC5031_OFS6_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS7_MASK                0x00000080
#define TMC5031_OFS7_SHIFT               7
#define TMC5031_OFS7_FIELD(motor)               ((RegisterField) {TMC5031_OFS7_MASK, TMC5031_OFS7_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS8_MASK                0x00000100
#define TMC5031_OFS8_SHIFT               8
#define TMC5031_OFS8_FIELD(motor)               ((RegisterField) {TMC5031_OFS8_MASK, TMC5031_OFS8_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS9_MASK                0x00000200
#define TMC5031_OFS9_SHIFT               9
#define TMC5031_OFS9_FIELD(motor)               ((RegisterField) {TMC5031_OFS9_MASK, TMC5031_OFS9_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS10_MASK               0x00000400
#define TMC5031_OFS10_SHIFT              10
#define TMC5031_OFS10_FIELD(motor)              ((RegisterField) {TMC5031_OFS10_MASK, TMC5031_OFS10_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS11_MASK               0x00000800
#define TMC5031_OFS11_SHIFT              11
#define TMC5031_OFS11_FIELD(motor)              ((RegisterField) {TMC5031_OFS11_MASK, TMC5031_OFS11_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS12_MASK               0x00001000
#define TMC5031_OFS12_SHIFT              12
#define TMC5031_OFS12_FIELD(motor)              ((RegisterField) {TMC5031_OFS12_MASK, TMC5031_OFS12_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS13_MASK               0x00002000
#define TMC5031_OFS13_SHIFT              13
#define TMC5031_OFS13_FIELD(motor)              ((RegisterField) {TMC5031_OFS13_MASK, TMC5031_OFS13_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS14_MASK               0x00004000
#define TMC5031_OFS14_SHIFT              14
#define TMC5031_OFS14_FIELD(motor)              ((RegisterField) {TMC5031_OFS14_MASK, TMC5031_OFS14_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS15_MASK               0x00008000
#define TMC5031_OFS15_SHIFT              15
#define TMC5031_OFS15_FIELD(motor)              ((RegisterField) {TMC5031_OFS15_MASK, TMC5031_OFS15_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS16_MASK               0x00010000
#define TMC5031_OFS16_SHIFT              16
#define TMC5031_OFS16_FIELD(motor)              ((RegisterField) {TMC5031_OFS16_MASK, TMC5031_OFS16_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS17_MASK               0x00020000
#define TMC5031_OFS17_SHIFT              17
#define TMC5031_OFS17_FIELD(motor)              ((RegisterField) {TMC5031_OFS17_MASK, TMC5031_OFS17_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS18_MASK               0x00040000
#define TMC5031_OFS18_SHIFT              18
#define TMC5031_OFS18_FIELD(motor)              ((RegisterField) {TMC5031_OFS18_MASK, TMC5031_OFS18_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS19_MASK               0x00080000
#define TMC5031_OFS19_SHIFT              19
#define TMC5031_OFS19_FIELD(motor)              ((RegisterField) {TMC5031_OFS19_MASK, TMC5031_OFS19_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS20_MASK               0x00100000
#define TMC5031_OFS20_SHIFT              20
#define TMC5031_OFS20_FIELD(motor)              ((RegisterField) {TMC5031_OFS20_MASK, TMC5031_OFS20_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS21_MASK               0x00200000
#define TMC5031_OFS21_SHIFT              21
#define TMC5031_OFS21_FIELD(motor)              ((RegisterField) {TMC5031_OFS21_MASK, TMC5031_OFS21_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS22_MASK               0x00400000
#define TMC5031_OFS22_SHIFT              22
#define TMC5031_OFS22_FIELD(motor)              ((RegisterField) {TMC5031_OFS22_MASK, TMC5031_OFS22_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS23_MASK               0x00800000
#define TMC5031_OFS23_SHIFT              23
#define TMC5031_OFS23_FIELD(motor)              ((RegisterField) {TMC5031_OFS23_MASK, TMC5031_OFS23_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS24_MASK               0x01000000
#define TMC5031_OFS24_SHIFT              24
#define TMC5031_OFS24_FIELD(motor)              ((RegisterField) {TMC5031_OFS24_MASK, TMC5031_OFS24_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS25_MASK               0x02000000
#define TMC5031_OFS25_SHIFT              25
#define TMC5031_OFS25_FIELD(motor)              ((RegisterField) {TMC5031_OFS25_MASK, TMC5031_OFS25_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS26_MASK               0x04000000
#define TMC5031_OFS26_SHIFT              26
#define TMC5031_OFS26_FIELD(motor)              ((RegisterField) {TMC5031_OFS26_MASK, TMC5031_OFS26_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS27_MASK               0x08000000
#define TMC5031_OFS27_SHIFT              27
#define TMC5031_OFS27_FIELD(motor)              ((RegisterField) {TMC5031_OFS27_MASK, TMC5031_OFS27_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS28_MASK               0x10000000
#define TMC5031_OFS28_SHIFT              28
#define TMC5031_OFS28_FIELD(motor)              ((RegisterField) {TMC5031_OFS28_MASK, TMC5031_OFS28_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS29_MASK               0x20000000
#define TMC5031_OFS29_SHIFT              29
#define TMC5031_OFS29_FIELD(motor)              ((RegisterField) {TMC5031_OFS29_MASK, TMC5031_OFS29_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS30_MASK               0x40000000
#define TMC5031_OFS30_SHIFT              30
#define TMC5031_OFS30_FIELD(motor)              ((RegisterField) {TMC5031_OFS30_MASK, TMC5031_OFS30_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS31_MASK               0x80000000
#define TMC5031_OFS31_SHIFT              31
#define TMC5031_OFS31_FIELD(motor)              ((RegisterField) {TMC5031_OFS31_MASK, TMC5031_OFS31_SHIFT, TMC5031_MSLUT[0](motor), false})
#define TMC5031_OFS32_MASK               0x00000001
#define TMC5031_OFS32_SHIFT              0
#define TMC5031_OFS32_FIELD(motor)              ((RegisterField) {TMC5031_OFS32_MASK, TMC5031_OFS32_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS33_MASK               0x00000002
#define TMC5031_OFS33_SHIFT              1
#define TMC5031_OFS33_FIELD(motor)              ((RegisterField) {TMC5031_OFS33_MASK, TMC5031_OFS33_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS34_MASK               0x00000004
#define TMC5031_OFS34_SHIFT              2
#define TMC5031_OFS34_FIELD(motor)              ((RegisterField) {TMC5031_OFS34_MASK, TMC5031_OFS34_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS35_MASK               0x00000008
#define TMC5031_OFS35_SHIFT              3
#define TMC5031_OFS35_FIELD(motor)              ((RegisterField) {TMC5031_OFS35_MASK, TMC5031_OFS35_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS36_MASK               0x00000010
#define TMC5031_OFS36_SHIFT              4
#define TMC5031_OFS36_FIELD(motor)              ((RegisterField) {TMC5031_OFS36_MASK, TMC5031_OFS36_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS37_MASK               0x00000020
#define TMC5031_OFS37_SHIFT              5
#define TMC5031_OFS37_FIELD(motor)              ((RegisterField) {TMC5031_OFS37_MASK, TMC5031_OFS37_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS38_MASK               0x00000040
#define TMC5031_OFS38_SHIFT              6
#define TMC5031_OFS38_FIELD(motor)              ((RegisterField) {TMC5031_OFS38_MASK, TMC5031_OFS38_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS39_MASK               0x00000080
#define TMC5031_OFS39_SHIFT              7
#define TMC5031_OFS39_FIELD(motor)              ((RegisterField) {TMC5031_OFS39_MASK, TMC5031_OFS39_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS40_MASK               0x00000100
#define TMC5031_OFS40_SHIFT              8
#define TMC5031_OFS40_FIELD(motor)              ((RegisterField) {TMC5031_OFS40_MASK, TMC5031_OFS40_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS41_MASK               0x00000200
#define TMC5031_OFS41_SHIFT              9
#define TMC5031_OFS41_FIELD(motor)              ((RegisterField) {TMC5031_OFS41_MASK, TMC5031_OFS41_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS42_MASK               0x00000400
#define TMC5031_OFS42_SHIFT              10
#define TMC5031_OFS42_FIELD(motor)              ((RegisterField) {TMC5031_OFS42_MASK, TMC5031_OFS42_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS43_MASK               0x00000800
#define TMC5031_OFS43_SHIFT              11
#define TMC5031_OFS43_FIELD(motor)              ((RegisterField) {TMC5031_OFS43_MASK, TMC5031_OFS43_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS44_MASK               0x00001000
#define TMC5031_OFS44_SHIFT              12
#define TMC5031_OFS44_FIELD(motor)              ((RegisterField) {TMC5031_OFS44_MASK, TMC5031_OFS44_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS45_MASK               0x00002000
#define TMC5031_OFS45_SHIFT              13
#define TMC5031_OFS45_FIELD(motor)              ((RegisterField) {TMC5031_OFS45_MASK, TMC5031_OFS45_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS46_MASK               0x00004000
#define TMC5031_OFS46_SHIFT              14
#define TMC5031_OFS46_FIELD(motor)              ((RegisterField) {TMC5031_OFS46_MASK, TMC5031_OFS46_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS47_MASK               0x00008000
#define TMC5031_OFS47_SHIFT              15
#define TMC5031_OFS47_FIELD(motor)              ((RegisterField) {TMC5031_OFS47_MASK, TMC5031_OFS47_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS48_MASK               0x00010000
#define TMC5031_OFS48_SHIFT              16
#define TMC5031_OFS48_FIELD(motor)              ((RegisterField) {TMC5031_OFS48_MASK, TMC5031_OFS48_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS49_MASK               0x00020000
#define TMC5031_OFS49_SHIFT              17
#define TMC5031_OFS49_FIELD(motor)              ((RegisterField) {TMC5031_OFS49_MASK, TMC5031_OFS49_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS50_MASK               0x00040000
#define TMC5031_OFS50_SHIFT              18
#define TMC5031_OFS50_FIELD(motor)              ((RegisterField) {TMC5031_OFS50_MASK, TMC5031_OFS50_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS51_MASK               0x00080000
#define TMC5031_OFS51_SHIFT              19
#define TMC5031_OFS51_FIELD(motor)              ((RegisterField) {TMC5031_OFS51_MASK, TMC5031_OFS51_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS52_MASK               0x00100000
#define TMC5031_OFS52_SHIFT              20
#define TMC5031_OFS52_FIELD(motor)              ((RegisterField) {TMC5031_OFS52_MASK, TMC5031_OFS52_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS53_MASK               0x00200000
#define TMC5031_OFS53_SHIFT              21
#define TMC5031_OFS53_FIELD(motor)              ((RegisterField) {TMC5031_OFS53_MASK, TMC5031_OFS53_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS54_MASK               0x00400000
#define TMC5031_OFS54_SHIFT              22
#define TMC5031_OFS54_FIELD(motor)              ((RegisterField) {TMC5031_OFS54_MASK, TMC5031_OFS54_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS55_MASK               0x00800000
#define TMC5031_OFS55_SHIFT              23
#define TMC5031_OFS55_FIELD(motor)              ((RegisterField) {TMC5031_OFS55_MASK, TMC5031_OFS55_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS56_MASK               0x01000000
#define TMC5031_OFS56_SHIFT              24
#define TMC5031_OFS56_FIELD(motor)              ((RegisterField) {TMC5031_OFS56_MASK, TMC5031_OFS56_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS57_MASK               0x02000000
#define TMC5031_OFS57_SHIFT              25
#define TMC5031_OFS57_FIELD(motor)              ((RegisterField) {TMC5031_OFS57_MASK, TMC5031_OFS57_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS58_MASK               0x04000000
#define TMC5031_OFS58_SHIFT              26
#define TMC5031_OFS58_FIELD(motor)              ((RegisterField) {TMC5031_OFS58_MASK, TMC5031_OFS58_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS59_MASK               0x08000000
#define TMC5031_OFS59_SHIFT              27
#define TMC5031_OFS59_FIELD(motor)              ((RegisterField) {TMC5031_OFS59_MASK, TMC5031_OFS59_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS60_MASK               0x10000000
#define TMC5031_OFS60_SHIFT              28
#define TMC5031_OFS60_FIELD(motor)              ((RegisterField) {TMC5031_OFS60_MASK, TMC5031_OFS60_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS61_MASK               0x20000000
#define TMC5031_OFS61_SHIFT              29
#define TMC5031_OFS61_FIELD(motor)              ((RegisterField) {TMC5031_OFS61_MASK, TMC5031_OFS61_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS62_MASK               0x40000000
#define TMC5031_OFS62_SHIFT              30
#define TMC5031_OFS62_FIELD(motor)              ((RegisterField) {TMC5031_OFS62_MASK, TMC5031_OFS62_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS63_MASK               0x80000000
#define TMC5031_OFS63_SHIFT              31
#define TMC5031_OFS63_FIELD(motor)              ((RegisterField) {TMC5031_OFS63_MASK, TMC5031_OFS63_SHIFT, TMC5031_MSLUT[1](motor), false})
#define TMC5031_OFS64_MASK               0x00000001
#define TMC5031_OFS64_SHIFT              0
#define TMC5031_OFS64_FIELD(motor)              ((RegisterField) {TMC5031_OFS64_MASK, TMC5031_OFS64_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS65_MASK               0x00000002
#define TMC5031_OFS65_SHIFT              1
#define TMC5031_OFS65_FIELD(motor)              ((RegisterField) {TMC5031_OFS65_MASK, TMC5031_OFS65_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS66_MASK               0x00000004
#define TMC5031_OFS66_SHIFT              2
#define TMC5031_OFS66_FIELD(motor)              ((RegisterField) {TMC5031_OFS66_MASK, TMC5031_OFS66_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS67_MASK               0x00000008
#define TMC5031_OFS67_SHIFT              3
#define TMC5031_OFS67_FIELD(motor)              ((RegisterField) {TMC5031_OFS67_MASK, TMC5031_OFS67_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS68_MASK               0x00000010
#define TMC5031_OFS68_SHIFT              4
#define TMC5031_OFS68_FIELD(motor)              ((RegisterField) {TMC5031_OFS68_MASK, TMC5031_OFS68_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS69_MASK               0x00000020
#define TMC5031_OFS69_SHIFT              5
#define TMC5031_OFS69_FIELD(motor)              ((RegisterField) {TMC5031_OFS69_MASK, TMC5031_OFS69_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS70_MASK               0x00000040
#define TMC5031_OFS70_SHIFT              6
#define TMC5031_OFS70_FIELD(motor)              ((RegisterField) {TMC5031_OFS70_MASK, TMC5031_OFS70_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS71_MASK               0x00000080
#define TMC5031_OFS71_SHIFT              7
#define TMC5031_OFS71_FIELD(motor)              ((RegisterField) {TMC5031_OFS71_MASK, TMC5031_OFS71_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS72_MASK               0x00000100
#define TMC5031_OFS72_SHIFT              8
#define TMC5031_OFS72_FIELD(motor)              ((RegisterField) {TMC5031_OFS72_MASK, TMC5031_OFS72_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS73_MASK               0x00000200
#define TMC5031_OFS73_SHIFT              9
#define TMC5031_OFS73_FIELD(motor)              ((RegisterField) {TMC5031_OFS73_MASK, TMC5031_OFS73_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS74_MASK               0x00000400
#define TMC5031_OFS74_SHIFT              10
#define TMC5031_OFS74_FIELD(motor)              ((RegisterField) {TMC5031_OFS74_MASK, TMC5031_OFS74_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS75_MASK               0x00000800
#define TMC5031_OFS75_SHIFT              11
#define TMC5031_OFS75_FIELD(motor)              ((RegisterField) {TMC5031_OFS75_MASK, TMC5031_OFS75_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS76_MASK               0x00001000
#define TMC5031_OFS76_SHIFT              12
#define TMC5031_OFS76_FIELD(motor)              ((RegisterField) {TMC5031_OFS76_MASK, TMC5031_OFS76_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS77_MASK               0x00002000
#define TMC5031_OFS77_SHIFT              13
#define TMC5031_OFS77_FIELD(motor)              ((RegisterField) {TMC5031_OFS77_MASK, TMC5031_OFS77_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS78_MASK               0x00004000
#define TMC5031_OFS78_SHIFT              14
#define TMC5031_OFS78_FIELD(motor)              ((RegisterField) {TMC5031_OFS78_MASK, TMC5031_OFS78_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS79_MASK               0x00008000
#define TMC5031_OFS79_SHIFT              15
#define TMC5031_OFS79_FIELD(motor)              ((RegisterField) {TMC5031_OFS79_MASK, TMC5031_OFS79_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS80_MASK               0x00010000
#define TMC5031_OFS80_SHIFT              16
#define TMC5031_OFS80_FIELD(motor)              ((RegisterField) {TMC5031_OFS80_MASK, TMC5031_OFS80_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS81_MASK               0x00020000
#define TMC5031_OFS81_SHIFT              17
#define TMC5031_OFS81_FIELD(motor)              ((RegisterField) {TMC5031_OFS81_MASK, TMC5031_OFS81_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS82_MASK               0x00040000
#define TMC5031_OFS82_SHIFT              18
#define TMC5031_OFS82_FIELD(motor)              ((RegisterField) {TMC5031_OFS82_MASK, TMC5031_OFS82_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS83_MASK               0x00080000
#define TMC5031_OFS83_SHIFT              19
#define TMC5031_OFS83_FIELD(motor)              ((RegisterField) {TMC5031_OFS83_MASK, TMC5031_OFS83_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS84_MASK               0x00100000
#define TMC5031_OFS84_SHIFT              20
#define TMC5031_OFS84_FIELD(motor)              ((RegisterField) {TMC5031_OFS84_MASK, TMC5031_OFS84_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS85_MASK               0x00200000
#define TMC5031_OFS85_SHIFT              21
#define TMC5031_OFS85_FIELD(motor)              ((RegisterField) {TMC5031_OFS85_MASK, TMC5031_OFS85_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS86_MASK               0x00400000
#define TMC5031_OFS86_SHIFT              22
#define TMC5031_OFS86_FIELD(motor)              ((RegisterField) {TMC5031_OFS86_MASK, TMC5031_OFS86_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS87_MASK               0x00800000
#define TMC5031_OFS87_SHIFT              23
#define TMC5031_OFS87_FIELD(motor)              ((RegisterField) {TMC5031_OFS87_MASK, TMC5031_OFS87_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS88_MASK               0x01000000
#define TMC5031_OFS88_SHIFT              24
#define TMC5031_OFS88_FIELD(motor)              ((RegisterField) {TMC5031_OFS88_MASK, TMC5031_OFS88_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS89_MASK               0x02000000
#define TMC5031_OFS89_SHIFT              25
#define TMC5031_OFS89_FIELD(motor)              ((RegisterField) {TMC5031_OFS89_MASK, TMC5031_OFS89_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS90_MASK               0x04000000
#define TMC5031_OFS90_SHIFT              26
#define TMC5031_OFS90_FIELD(motor)              ((RegisterField) {TMC5031_OFS90_MASK, TMC5031_OFS90_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS91_MASK               0x08000000
#define TMC5031_OFS91_SHIFT              27
#define TMC5031_OFS91_FIELD(motor)              ((RegisterField) {TMC5031_OFS91_MASK, TMC5031_OFS91_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS92_MASK               0x10000000
#define TMC5031_OFS92_SHIFT              28
#define TMC5031_OFS92_FIELD(motor)              ((RegisterField) {TMC5031_OFS92_MASK, TMC5031_OFS92_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS93_MASK               0x20000000
#define TMC5031_OFS93_SHIFT              29
#define TMC5031_OFS93_FIELD(motor)              ((RegisterField) {TMC5031_OFS93_MASK, TMC5031_OFS93_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS94_MASK               0x40000000
#define TMC5031_OFS94_SHIFT              30
#define TMC5031_OFS94_FIELD(motor)              ((RegisterField) {TMC5031_OFS94_MASK, TMC5031_OFS94_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS95_MASK               0x80000000
#define TMC5031_OFS95_SHIFT              31
#define TMC5031_OFS95_FIELD(motor)              ((RegisterField) {TMC5031_OFS95_MASK, TMC5031_OFS95_SHIFT, TMC5031_MSLUT[2](motor), false})
#define TMC5031_OFS96_MASK               0x00000001
#define TMC5031_OFS96_SHIFT              0
#define TMC5031_OFS96_FIELD(motor)              ((RegisterField) {TMC5031_OFS96_MASK, TMC5031_OFS96_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS97_MASK               0x00000002
#define TMC5031_OFS97_SHIFT              1
#define TMC5031_OFS97_FIELD(motor)              ((RegisterField) {TMC5031_OFS97_MASK, TMC5031_OFS97_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS98_MASK               0x00000004
#define TMC5031_OFS98_SHIFT              2
#define TMC5031_OFS98_FIELD(motor)              ((RegisterField) {TMC5031_OFS98_MASK, TMC5031_OFS98_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS99_MASK               0x00000008
#define TMC5031_OFS99_SHIFT              3
#define TMC5031_OFS99_FIELD(motor)              ((RegisterField) {TMC5031_OFS99_MASK, TMC5031_OFS99_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS100_MASK              0x00000010
#define TMC5031_OFS100_SHIFT             4
#define TMC5031_OFS100_FIELD(motor)             ((RegisterField) {TMC5031_OFS100_MASK, TMC5031_OFS100_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS101_MASK              0x00000020
#define TMC5031_OFS101_SHIFT             5
#define TMC5031_OFS101_FIELD(motor)             ((RegisterField) {TMC5031_OFS101_MASK, TMC5031_OFS101_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS102_MASK              0x00000040
#define TMC5031_OFS102_SHIFT             6
#define TMC5031_OFS102_FIELD(motor)             ((RegisterField) {TMC5031_OFS102_MASK, TMC5031_OFS102_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS103_MASK              0x00000080
#define TMC5031_OFS103_SHIFT             7
#define TMC5031_OFS103_FIELD(motor)             ((RegisterField) {TMC5031_OFS103_MASK, TMC5031_OFS103_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS104_MASK              0x00000100
#define TMC5031_OFS104_SHIFT             8
#define TMC5031_OFS104_FIELD(motor)             ((RegisterField) {TMC5031_OFS104_MASK, TMC5031_OFS104_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS105_MASK              0x00000200
#define TMC5031_OFS105_SHIFT             9
#define TMC5031_OFS105_FIELD(motor)             ((RegisterField) {TMC5031_OFS105_MASK, TMC5031_OFS105_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS106_MASK              0x00000400
#define TMC5031_OFS106_SHIFT             10
#define TMC5031_OFS106_FIELD(motor)             ((RegisterField) {TMC5031_OFS106_MASK, TMC5031_OFS106_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS107_MASK              0x00000800
#define TMC5031_OFS107_SHIFT             11
#define TMC5031_OFS107_FIELD(motor)             ((RegisterField) {TMC5031_OFS107_MASK, TMC5031_OFS107_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS108_MASK              0x00001000
#define TMC5031_OFS108_SHIFT             12
#define TMC5031_OFS108_FIELD(motor)             ((RegisterField) {TMC5031_OFS108_MASK, TMC5031_OFS108_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS109_MASK              0x00002000
#define TMC5031_OFS109_SHIFT             13
#define TMC5031_OFS109_FIELD(motor)             ((RegisterField) {TMC5031_OFS109_MASK, TMC5031_OFS109_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS110_MASK              0x00004000
#define TMC5031_OFS110_SHIFT             14
#define TMC5031_OFS110_FIELD(motor)             ((RegisterField) {TMC5031_OFS110_MASK, TMC5031_OFS110_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS111_MASK              0x00008000
#define TMC5031_OFS111_SHIFT             15
#define TMC5031_OFS111_FIELD(motor)             ((RegisterField) {TMC5031_OFS111_MASK, TMC5031_OFS111_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS112_MASK              0x00010000
#define TMC5031_OFS112_SHIFT             16
#define TMC5031_OFS112_FIELD(motor)             ((RegisterField) {TMC5031_OFS112_MASK, TMC5031_OFS112_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS113_MASK              0x00020000
#define TMC5031_OFS113_SHIFT             17
#define TMC5031_OFS113_FIELD(motor)             ((RegisterField) {TMC5031_OFS113_MASK, TMC5031_OFS113_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS114_MASK              0x00040000
#define TMC5031_OFS114_SHIFT             18
#define TMC5031_OFS114_FIELD(motor)             ((RegisterField) {TMC5031_OFS114_MASK, TMC5031_OFS114_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS115_MASK              0x00080000
#define TMC5031_OFS115_SHIFT             19
#define TMC5031_OFS115_FIELD(motor)             ((RegisterField) {TMC5031_OFS115_MASK, TMC5031_OFS115_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS116_MASK              0x00100000
#define TMC5031_OFS116_SHIFT             20
#define TMC5031_OFS116_FIELD(motor)             ((RegisterField) {TMC5031_OFS116_MASK, TMC5031_OFS116_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS117_MASK              0x00200000
#define TMC5031_OFS117_SHIFT             21
#define TMC5031_OFS117_FIELD(motor)             ((RegisterField) {TMC5031_OFS117_MASK, TMC5031_OFS117_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS118_MASK              0x00400000
#define TMC5031_OFS118_SHIFT             22
#define TMC5031_OFS118_FIELD(motor)             ((RegisterField) {TMC5031_OFS118_MASK, TMC5031_OFS118_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS119_MASK              0x00800000
#define TMC5031_OFS119_SHIFT             23
#define TMC5031_OFS119_FIELD(motor)             ((RegisterField) {TMC5031_OFS119_MASK, TMC5031_OFS119_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS120_MASK              0x01000000
#define TMC5031_OFS120_SHIFT             24
#define TMC5031_OFS120_FIELD(motor)             ((RegisterField) {TMC5031_OFS120_MASK, TMC5031_OFS120_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS121_MASK              0x02000000
#define TMC5031_OFS121_SHIFT             25
#define TMC5031_OFS121_FIELD(motor)             ((RegisterField) {TMC5031_OFS121_MASK, TMC5031_OFS121_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS122_MASK              0x04000000
#define TMC5031_OFS122_SHIFT             26
#define TMC5031_OFS122_FIELD(motor)             ((RegisterField) {TMC5031_OFS122_MASK, TMC5031_OFS122_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS123_MASK              0x08000000
#define TMC5031_OFS123_SHIFT             27
#define TMC5031_OFS123_FIELD(motor)             ((RegisterField) {TMC5031_OFS123_MASK, TMC5031_OFS123_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS124_MASK              0x10000000
#define TMC5031_OFS124_SHIFT             28
#define TMC5031_OFS124_FIELD(motor)             ((RegisterField) {TMC5031_OFS124_MASK, TMC5031_OFS124_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS125_MASK              0x20000000
#define TMC5031_OFS125_SHIFT             29
#define TMC5031_OFS125_FIELD(motor)             ((RegisterField) {TMC5031_OFS125_MASK, TMC5031_OFS125_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS126_MASK              0x40000000
#define TMC5031_OFS126_SHIFT             30
#define TMC5031_OFS126_FIELD(motor)             ((RegisterField) {TMC5031_OFS126_MASK, TMC5031_OFS126_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS127_MASK              0x80000000
#define TMC5031_OFS127_SHIFT             31
#define TMC5031_OFS127_FIELD(motor)             ((RegisterField) {TMC5031_OFS127_MASK, TMC5031_OFS127_SHIFT, TMC5031_MSLUT[3](motor), false})
#define TMC5031_OFS128_MASK              0x00000001
#define TMC5031_OFS128_SHIFT             0
#define TMC5031_OFS128_FIELD(motor)             ((RegisterField) {TMC5031_OFS128_MASK, TMC5031_OFS128_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS129_MASK              0x00000002
#define TMC5031_OFS129_SHIFT             1
#define TMC5031_OFS129_FIELD(motor)             ((RegisterField) {TMC5031_OFS129_MASK, TMC5031_OFS129_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS130_MASK              0x00000004
#define TMC5031_OFS130_SHIFT             2
#define TMC5031_OFS130_FIELD(motor)             ((RegisterField) {TMC5031_OFS130_MASK, TMC5031_OFS130_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS131_MASK              0x00000008
#define TMC5031_OFS131_SHIFT             3
#define TMC5031_OFS131_FIELD(motor)             ((RegisterField) {TMC5031_OFS131_MASK, TMC5031_OFS131_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS132_MASK              0x00000010
#define TMC5031_OFS132_SHIFT             4
#define TMC5031_OFS132_FIELD(motor)             ((RegisterField) {TMC5031_OFS132_MASK, TMC5031_OFS132_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS133_MASK              0x00000020
#define TMC5031_OFS133_SHIFT             5
#define TMC5031_OFS133_FIELD(motor)             ((RegisterField) {TMC5031_OFS133_MASK, TMC5031_OFS133_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS134_MASK              0x00000040
#define TMC5031_OFS134_SHIFT             6
#define TMC5031_OFS134_FIELD(motor)             ((RegisterField) {TMC5031_OFS134_MASK, TMC5031_OFS134_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS135_MASK              0x00000080
#define TMC5031_OFS135_SHIFT             7
#define TMC5031_OFS135_FIELD(motor)             ((RegisterField) {TMC5031_OFS135_MASK, TMC5031_OFS135_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS136_MASK              0x00000100
#define TMC5031_OFS136_SHIFT             8
#define TMC5031_OFS136_FIELD(motor)             ((RegisterField) {TMC5031_OFS136_MASK, TMC5031_OFS136_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS137_MASK              0x00000200
#define TMC5031_OFS137_SHIFT             9
#define TMC5031_OFS137_FIELD(motor)             ((RegisterField) {TMC5031_OFS137_MASK, TMC5031_OFS137_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS138_MASK              0x00000400
#define TMC5031_OFS138_SHIFT             10
#define TMC5031_OFS138_FIELD(motor)             ((RegisterField) {TMC5031_OFS138_MASK, TMC5031_OFS138_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS139_MASK              0x00000800
#define TMC5031_OFS139_SHIFT             11
#define TMC5031_OFS139_FIELD(motor)             ((RegisterField) {TMC5031_OFS139_MASK, TMC5031_OFS139_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS140_MASK              0x00001000
#define TMC5031_OFS140_SHIFT             12
#define TMC5031_OFS140_FIELD(motor)             ((RegisterField) {TMC5031_OFS140_MASK, TMC5031_OFS140_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS141_MASK              0x00002000
#define TMC5031_OFS141_SHIFT             13
#define TMC5031_OFS141_FIELD(motor)             ((RegisterField) {TMC5031_OFS141_MASK, TMC5031_OFS141_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS142_MASK              0x00004000
#define TMC5031_OFS142_SHIFT             14
#define TMC5031_OFS142_FIELD(motor)             ((RegisterField) {TMC5031_OFS142_MASK, TMC5031_OFS142_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS143_MASK              0x00008000
#define TMC5031_OFS143_SHIFT             15
#define TMC5031_OFS143_FIELD(motor)             ((RegisterField) {TMC5031_OFS143_MASK, TMC5031_OFS143_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS144_MASK              0x00010000
#define TMC5031_OFS144_SHIFT             16
#define TMC5031_OFS144_FIELD(motor)             ((RegisterField) {TMC5031_OFS144_MASK, TMC5031_OFS144_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS145_MASK              0x00020000
#define TMC5031_OFS145_SHIFT             17
#define TMC5031_OFS145_FIELD(motor)             ((RegisterField) {TMC5031_OFS145_MASK, TMC5031_OFS145_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS146_MASK              0x00040000
#define TMC5031_OFS146_SHIFT             18
#define TMC5031_OFS146_FIELD(motor)             ((RegisterField) {TMC5031_OFS146_MASK, TMC5031_OFS146_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS147_MASK              0x00080000
#define TMC5031_OFS147_SHIFT             19
#define TMC5031_OFS147_FIELD(motor)             ((RegisterField) {TMC5031_OFS147_MASK, TMC5031_OFS147_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS148_MASK              0x00100000
#define TMC5031_OFS148_SHIFT             20
#define TMC5031_OFS148_FIELD(motor)             ((RegisterField) {TMC5031_OFS148_MASK, TMC5031_OFS148_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS149_MASK              0x00200000
#define TMC5031_OFS149_SHIFT             21
#define TMC5031_OFS149_FIELD(motor)             ((RegisterField) {TMC5031_OFS149_MASK, TMC5031_OFS149_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS150_MASK              0x00400000
#define TMC5031_OFS150_SHIFT             22
#define TMC5031_OFS150_FIELD(motor)             ((RegisterField) {TMC5031_OFS150_MASK, TMC5031_OFS150_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS151_MASK              0x00800000
#define TMC5031_OFS151_SHIFT             23
#define TMC5031_OFS151_FIELD(motor)             ((RegisterField) {TMC5031_OFS151_MASK, TMC5031_OFS151_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS152_MASK              0x01000000
#define TMC5031_OFS152_SHIFT             24
#define TMC5031_OFS152_FIELD(motor)             ((RegisterField) {TMC5031_OFS152_MASK, TMC5031_OFS152_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS153_MASK              0x02000000
#define TMC5031_OFS153_SHIFT             25
#define TMC5031_OFS153_FIELD(motor)             ((RegisterField) {TMC5031_OFS153_MASK, TMC5031_OFS153_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS154_MASK              0x04000000
#define TMC5031_OFS154_SHIFT             26
#define TMC5031_OFS154_FIELD(motor)             ((RegisterField) {TMC5031_OFS154_MASK, TMC5031_OFS154_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS155_MASK              0x08000000
#define TMC5031_OFS155_SHIFT             27
#define TMC5031_OFS155_FIELD(motor)             ((RegisterField) {TMC5031_OFS155_MASK, TMC5031_OFS155_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS156_MASK              0x10000000
#define TMC5031_OFS156_SHIFT             28
#define TMC5031_OFS156_FIELD(motor)             ((RegisterField) {TMC5031_OFS156_MASK, TMC5031_OFS156_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS157_MASK              0x20000000
#define TMC5031_OFS157_SHIFT             29
#define TMC5031_OFS157_FIELD(motor)             ((RegisterField) {TMC5031_OFS157_MASK, TMC5031_OFS157_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS158_MASK              0x40000000
#define TMC5031_OFS158_SHIFT             30
#define TMC5031_OFS158_FIELD(motor)             ((RegisterField) {TMC5031_OFS158_MASK, TMC5031_OFS158_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS159_MASK              0x80000000
#define TMC5031_OFS159_SHIFT             31
#define TMC5031_OFS159_FIELD(motor)             ((RegisterField) {TMC5031_OFS159_MASK, TMC5031_OFS159_SHIFT, TMC5031_MSLUT[4](motor), false})
#define TMC5031_OFS160_MASK              0x00000001
#define TMC5031_OFS160_SHIFT             0
#define TMC5031_OFS160_FIELD(motor)             ((RegisterField) {TMC5031_OFS160_MASK, TMC5031_OFS160_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS161_MASK              0x00000002
#define TMC5031_OFS161_SHIFT             1
#define TMC5031_OFS161_FIELD(motor)             ((RegisterField) {TMC5031_OFS161_MASK, TMC5031_OFS161_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS162_MASK              0x00000004
#define TMC5031_OFS162_SHIFT             2
#define TMC5031_OFS162_FIELD(motor)             ((RegisterField) {TMC5031_OFS162_MASK, TMC5031_OFS162_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS163_MASK              0x00000008
#define TMC5031_OFS163_SHIFT             3
#define TMC5031_OFS163_FIELD(motor)             ((RegisterField) {TMC5031_OFS163_MASK, TMC5031_OFS163_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS164_MASK              0x00000010
#define TMC5031_OFS164_SHIFT             4
#define TMC5031_OFS164_FIELD(motor)             ((RegisterField) {TMC5031_OFS164_MASK, TMC5031_OFS164_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS165_MASK              0x00000020
#define TMC5031_OFS165_SHIFT             5
#define TMC5031_OFS165_FIELD(motor)             ((RegisterField) {TMC5031_OFS165_MASK, TMC5031_OFS165_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS166_MASK              0x00000040
#define TMC5031_OFS166_SHIFT             6
#define TMC5031_OFS166_FIELD(motor)             ((RegisterField) {TMC5031_OFS166_MASK, TMC5031_OFS166_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS167_MASK              0x00000080
#define TMC5031_OFS167_SHIFT             7
#define TMC5031_OFS167_FIELD(motor)             ((RegisterField) {TMC5031_OFS167_MASK, TMC5031_OFS167_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS168_MASK              0x00000100
#define TMC5031_OFS168_SHIFT             8
#define TMC5031_OFS168_FIELD(motor)             ((RegisterField) {TMC5031_OFS168_MASK, TMC5031_OFS168_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS169_MASK              0x00000200
#define TMC5031_OFS169_SHIFT             9
#define TMC5031_OFS169_FIELD(motor)             ((RegisterField) {TMC5031_OFS169_MASK, TMC5031_OFS169_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS170_MASK              0x00000400
#define TMC5031_OFS170_SHIFT             10
#define TMC5031_OFS170_FIELD(motor)             ((RegisterField) {TMC5031_OFS170_MASK, TMC5031_OFS170_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS171_MASK              0x00000800
#define TMC5031_OFS171_SHIFT             11
#define TMC5031_OFS171_FIELD(motor)             ((RegisterField) {TMC5031_OFS171_MASK, TMC5031_OFS171_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS172_MASK              0x00001000
#define TMC5031_OFS172_SHIFT             12
#define TMC5031_OFS172_FIELD(motor)             ((RegisterField) {TMC5031_OFS172_MASK, TMC5031_OFS172_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS173_MASK              0x00002000
#define TMC5031_OFS173_SHIFT             13
#define TMC5031_OFS173_FIELD(motor)             ((RegisterField) {TMC5031_OFS173_MASK, TMC5031_OFS173_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS174_MASK              0x00004000
#define TMC5031_OFS174_SHIFT             14
#define TMC5031_OFS174_FIELD(motor)             ((RegisterField) {TMC5031_OFS174_MASK, TMC5031_OFS174_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS175_MASK              0x00008000
#define TMC5031_OFS175_SHIFT             15
#define TMC5031_OFS175_FIELD(motor)             ((RegisterField) {TMC5031_OFS175_MASK, TMC5031_OFS175_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS176_MASK              0x00010000
#define TMC5031_OFS176_SHIFT             16
#define TMC5031_OFS176_FIELD(motor)             ((RegisterField) {TMC5031_OFS176_MASK, TMC5031_OFS176_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS177_MASK              0x00020000
#define TMC5031_OFS177_SHIFT             17
#define TMC5031_OFS177_FIELD(motor)             ((RegisterField) {TMC5031_OFS177_MASK, TMC5031_OFS177_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS178_MASK              0x00040000
#define TMC5031_OFS178_SHIFT             18
#define TMC5031_OFS178_FIELD(motor)             ((RegisterField) {TMC5031_OFS178_MASK, TMC5031_OFS178_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS179_MASK              0x00080000
#define TMC5031_OFS179_SHIFT             19
#define TMC5031_OFS179_FIELD(motor)             ((RegisterField) {TMC5031_OFS179_MASK, TMC5031_OFS179_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS180_MASK              0x00100000
#define TMC5031_OFS180_SHIFT             20
#define TMC5031_OFS180_FIELD(motor)             ((RegisterField) {TMC5031_OFS180_MASK, TMC5031_OFS180_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS181_MASK              0x00200000
#define TMC5031_OFS181_SHIFT             21
#define TMC5031_OFS181_FIELD(motor)             ((RegisterField) {TMC5031_OFS181_MASK, TMC5031_OFS181_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS182_MASK              0x00400000
#define TMC5031_OFS182_SHIFT             22
#define TMC5031_OFS182_FIELD(motor)             ((RegisterField) {TMC5031_OFS182_MASK, TMC5031_OFS182_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS183_MASK              0x00800000
#define TMC5031_OFS183_SHIFT             23
#define TMC5031_OFS183_FIELD(motor)             ((RegisterField) {TMC5031_OFS183_MASK, TMC5031_OFS183_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS184_MASK              0x01000000
#define TMC5031_OFS184_SHIFT             24
#define TMC5031_OFS184_FIELD(motor)             ((RegisterField) {TMC5031_OFS184_MASK, TMC5031_OFS184_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS185_MASK              0x02000000
#define TMC5031_OFS185_SHIFT             25
#define TMC5031_OFS185_FIELD(motor)             ((RegisterField) {TMC5031_OFS185_MASK, TMC5031_OFS185_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS186_MASK              0x04000000
#define TMC5031_OFS186_SHIFT             26
#define TMC5031_OFS186_FIELD(motor)             ((RegisterField) {TMC5031_OFS186_MASK, TMC5031_OFS186_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS187_MASK              0x08000000
#define TMC5031_OFS187_SHIFT             27
#define TMC5031_OFS187_FIELD(motor)             ((RegisterField) {TMC5031_OFS187_MASK, TMC5031_OFS187_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS188_MASK              0x10000000
#define TMC5031_OFS188_SHIFT             28
#define TMC5031_OFS188_FIELD(motor)             ((RegisterField) {TMC5031_OFS188_MASK, TMC5031_OFS188_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS189_MASK              0x20000000
#define TMC5031_OFS189_SHIFT             29
#define TMC5031_OFS189_FIELD(motor)             ((RegisterField) {TMC5031_OFS189_MASK, TMC5031_OFS189_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS190_MASK              0x40000000
#define TMC5031_OFS190_SHIFT             30
#define TMC5031_OFS190_FIELD(motor)             ((RegisterField) {TMC5031_OFS190_MASK, TMC5031_OFS190_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS191_MASK              0x80000000
#define TMC5031_OFS191_SHIFT             31
#define TMC5031_OFS191_FIELD(motor)             ((RegisterField) {TMC5031_OFS191_MASK, TMC5031_OFS191_SHIFT, TMC5031_MSLUT[5](motor), false})
#define TMC5031_OFS192_MASK              0x00000001
#define TMC5031_OFS192_SHIFT             0
#define TMC5031_OFS192_FIELD(motor)             ((RegisterField) {TMC5031_OFS192_MASK, TMC5031_OFS192_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS193_MASK              0x00000002
#define TMC5031_OFS193_SHIFT             1
#define TMC5031_OFS193_FIELD(motor)             ((RegisterField) {TMC5031_OFS193_MASK, TMC5031_OFS193_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS194_MASK              0x00000004
#define TMC5031_OFS194_SHIFT             2
#define TMC5031_OFS194_FIELD(motor)             ((RegisterField) {TMC5031_OFS194_MASK, TMC5031_OFS194_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS195_MASK              0x00000008
#define TMC5031_OFS195_SHIFT             3
#define TMC5031_OFS195_FIELD(motor)             ((RegisterField) {TMC5031_OFS195_MASK, TMC5031_OFS195_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS196_MASK              0x00000010
#define TMC5031_OFS196_SHIFT             4
#define TMC5031_OFS196_FIELD(motor)             ((RegisterField) {TMC5031_OFS196_MASK, TMC5031_OFS196_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS197_MASK              0x00000020
#define TMC5031_OFS197_SHIFT             5
#define TMC5031_OFS197_FIELD(motor)             ((RegisterField) {TMC5031_OFS197_MASK, TMC5031_OFS197_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS198_MASK              0x00000040
#define TMC5031_OFS198_SHIFT             6
#define TMC5031_OFS198_FIELD(motor)             ((RegisterField) {TMC5031_OFS198_MASK, TMC5031_OFS198_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS199_MASK              0x00000080
#define TMC5031_OFS199_SHIFT             7
#define TMC5031_OFS199_FIELD(motor)             ((RegisterField) {TMC5031_OFS199_MASK, TMC5031_OFS199_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS200_MASK              0x00000100
#define TMC5031_OFS200_SHIFT             8
#define TMC5031_OFS200_FIELD(motor)             ((RegisterField) {TMC5031_OFS200_MASK, TMC5031_OFS200_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS201_MASK              0x00000200
#define TMC5031_OFS201_SHIFT             9
#define TMC5031_OFS201_FIELD(motor)             ((RegisterField) {TMC5031_OFS201_MASK, TMC5031_OFS201_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS202_MASK              0x00000400
#define TMC5031_OFS202_SHIFT             10
#define TMC5031_OFS202_FIELD(motor)             ((RegisterField) {TMC5031_OFS202_MASK, TMC5031_OFS202_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS203_MASK              0x00000800
#define TMC5031_OFS203_SHIFT             11
#define TMC5031_OFS203_FIELD(motor)             ((RegisterField) {TMC5031_OFS203_MASK, TMC5031_OFS203_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS204_MASK              0x00001000
#define TMC5031_OFS204_SHIFT             12
#define TMC5031_OFS204_FIELD(motor)             ((RegisterField) {TMC5031_OFS204_MASK, TMC5031_OFS204_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS205_MASK              0x00002000
#define TMC5031_OFS205_SHIFT             13
#define TMC5031_OFS205_FIELD(motor)             ((RegisterField) {TMC5031_OFS205_MASK, TMC5031_OFS205_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS206_MASK              0x00004000
#define TMC5031_OFS206_SHIFT             14
#define TMC5031_OFS206_FIELD(motor)             ((RegisterField) {TMC5031_OFS206_MASK, TMC5031_OFS206_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS207_MASK              0x00008000
#define TMC5031_OFS207_SHIFT             15
#define TMC5031_OFS207_FIELD(motor)             ((RegisterField) {TMC5031_OFS207_MASK, TMC5031_OFS207_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS208_MASK              0x00010000
#define TMC5031_OFS208_SHIFT             16
#define TMC5031_OFS208_FIELD(motor)             ((RegisterField) {TMC5031_OFS208_MASK, TMC5031_OFS208_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS209_MASK              0x00020000
#define TMC5031_OFS209_SHIFT             17
#define TMC5031_OFS209_FIELD(motor)             ((RegisterField) {TMC5031_OFS209_MASK, TMC5031_OFS209_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS210_MASK              0x00040000
#define TMC5031_OFS210_SHIFT             18
#define TMC5031_OFS210_FIELD(motor)             ((RegisterField) {TMC5031_OFS210_MASK, TMC5031_OFS210_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS211_MASK              0x00080000
#define TMC5031_OFS211_SHIFT             19
#define TMC5031_OFS211_FIELD(motor)             ((RegisterField) {TMC5031_OFS211_MASK, TMC5031_OFS211_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS212_MASK              0x00100000
#define TMC5031_OFS212_SHIFT             20
#define TMC5031_OFS212_FIELD(motor)             ((RegisterField) {TMC5031_OFS212_MASK, TMC5031_OFS212_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS213_MASK              0x00200000
#define TMC5031_OFS213_SHIFT             21
#define TMC5031_OFS213_FIELD(motor)             ((RegisterField) {TMC5031_OFS213_MASK, TMC5031_OFS213_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS214_MASK              0x00400000
#define TMC5031_OFS214_SHIFT             22
#define TMC5031_OFS214_FIELD(motor)             ((RegisterField) {TMC5031_OFS214_MASK, TMC5031_OFS214_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS215_MASK              0x00800000
#define TMC5031_OFS215_SHIFT             23
#define TMC5031_OFS215_FIELD(motor)             ((RegisterField) {TMC5031_OFS215_MASK, TMC5031_OFS215_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS216_MASK              0x01000000
#define TMC5031_OFS216_SHIFT             24
#define TMC5031_OFS216_FIELD(motor)             ((RegisterField) {TMC5031_OFS216_MASK, TMC5031_OFS216_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS217_MASK              0x02000000
#define TMC5031_OFS217_SHIFT             25
#define TMC5031_OFS217_FIELD(motor)             ((RegisterField) {TMC5031_OFS217_MASK, TMC5031_OFS217_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS218_MASK              0x04000000
#define TMC5031_OFS218_SHIFT             26
#define TMC5031_OFS218_FIELD(motor)             ((RegisterField) {TMC5031_OFS218_MASK, TMC5031_OFS218_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS219_MASK              0x08000000
#define TMC5031_OFS219_SHIFT             27
#define TMC5031_OFS219_FIELD(motor)             ((RegisterField) {TMC5031_OFS219_MASK, TMC5031_OFS219_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS220_MASK              0x10000000
#define TMC5031_OFS220_SHIFT             28
#define TMC5031_OFS220_FIELD(motor)             ((RegisterField) {TMC5031_OFS220_MASK, TMC5031_OFS220_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS221_MASK              0x20000000
#define TMC5031_OFS221_SHIFT             29
#define TMC5031_OFS221_FIELD(motor)             ((RegisterField) {TMC5031_OFS221_MASK, TMC5031_OFS221_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS222_MASK              0x40000000
#define TMC5031_OFS222_SHIFT             30
#define TMC5031_OFS222_FIELD(motor)             ((RegisterField) {TMC5031_OFS222_MASK, TMC5031_OFS222_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS223_MASK              0x80000000
#define TMC5031_OFS223_SHIFT             31
#define TMC5031_OFS223_FIELD(motor)             ((RegisterField) {TMC5031_OFS223_MASK, TMC5031_OFS223_SHIFT, TMC5031_MSLUT[6](motor), false})
#define TMC5031_OFS224_MASK              0x00000001
#define TMC5031_OFS224_SHIFT             0
#define TMC5031_OFS224_FIELD(motor)             ((RegisterField) {TMC5031_OFS224_MASK, TMC5031_OFS224_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS225_MASK              0x00000002
#define TMC5031_OFS225_SHIFT             1
#define TMC5031_OFS225_FIELD(motor)             ((RegisterField) {TMC5031_OFS225_MASK, TMC5031_OFS225_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS226_MASK              0x00000004
#define TMC5031_OFS226_SHIFT             2
#define TMC5031_OFS226_FIELD(motor)             ((RegisterField) {TMC5031_OFS226_MASK, TMC5031_OFS226_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS227_MASK              0x00000008
#define TMC5031_OFS227_SHIFT             3
#define TMC5031_OFS227_FIELD(motor)             ((RegisterField) {TMC5031_OFS227_MASK, TMC5031_OFS227_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS228_MASK              0x00000010
#define TMC5031_OFS228_SHIFT             4
#define TMC5031_OFS228_FIELD(motor)             ((RegisterField) {TMC5031_OFS228_MASK, TMC5031_OFS228_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS229_MASK              0x00000020
#define TMC5031_OFS229_SHIFT             5
#define TMC5031_OFS229_FIELD(motor)             ((RegisterField) {TMC5031_OFS229_MASK, TMC5031_OFS229_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS230_MASK              0x00000040
#define TMC5031_OFS230_SHIFT             6
#define TMC5031_OFS230_FIELD(motor)             ((RegisterField) {TMC5031_OFS230_MASK, TMC5031_OFS230_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS231_MASK              0x00000080
#define TMC5031_OFS231_SHIFT             7
#define TMC5031_OFS231_FIELD(motor)             ((RegisterField) {TMC5031_OFS231_MASK, TMC5031_OFS231_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS232_MASK              0x00000100
#define TMC5031_OFS232_SHIFT             8
#define TMC5031_OFS232_FIELD(motor)             ((RegisterField) {TMC5031_OFS232_MASK, TMC5031_OFS232_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS233_MASK              0x00000200
#define TMC5031_OFS233_SHIFT             9
#define TMC5031_OFS233_FIELD(motor)             ((RegisterField) {TMC5031_OFS233_MASK, TMC5031_OFS233_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS234_MASK              0x00000400
#define TMC5031_OFS234_SHIFT             10
#define TMC5031_OFS234_FIELD(motor)             ((RegisterField) {TMC5031_OFS234_MASK, TMC5031_OFS234_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS235_MASK              0x00000800
#define TMC5031_OFS235_SHIFT             11
#define TMC5031_OFS235_FIELD(motor)             ((RegisterField) {TMC5031_OFS235_MASK, TMC5031_OFS235_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS236_MASK              0x00001000
#define TMC5031_OFS236_SHIFT             12
#define TMC5031_OFS236_FIELD(motor)             ((RegisterField) {TMC5031_OFS236_MASK, TMC5031_OFS236_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS237_MASK              0x00002000
#define TMC5031_OFS237_SHIFT             13
#define TMC5031_OFS237_FIELD(motor)             ((RegisterField) {TMC5031_OFS237_MASK, TMC5031_OFS237_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS238_MASK              0x00004000
#define TMC5031_OFS238_SHIFT             14
#define TMC5031_OFS238_FIELD(motor)             ((RegisterField) {TMC5031_OFS238_MASK, TMC5031_OFS238_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS239_MASK              0x00008000
#define TMC5031_OFS239_SHIFT             15
#define TMC5031_OFS239_FIELD(motor)             ((RegisterField) {TMC5031_OFS239_MASK, TMC5031_OFS239_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS240_MASK              0x00010000
#define TMC5031_OFS240_SHIFT             16
#define TMC5031_OFS240_FIELD(motor)             ((RegisterField) {TMC5031_OFS240_MASK, TMC5031_OFS240_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS241_MASK              0x00020000
#define TMC5031_OFS241_SHIFT             17
#define TMC5031_OFS241_FIELD(motor)             ((RegisterField) {TMC5031_OFS241_MASK, TMC5031_OFS241_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS242_MASK              0x00040000
#define TMC5031_OFS242_SHIFT             18
#define TMC5031_OFS242_FIELD(motor)             ((RegisterField) {TMC5031_OFS242_MASK, TMC5031_OFS242_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS243_MASK              0x00080000
#define TMC5031_OFS243_SHIFT             19
#define TMC5031_OFS243_FIELD(motor)             ((RegisterField) {TMC5031_OFS243_MASK, TMC5031_OFS243_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS244_MASK              0x00100000
#define TMC5031_OFS244_SHIFT             20
#define TMC5031_OFS244_FIELD(motor)             ((RegisterField) {TMC5031_OFS244_MASK, TMC5031_OFS244_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS245_MASK              0x00200000
#define TMC5031_OFS245_SHIFT             21
#define TMC5031_OFS245_FIELD(motor)             ((RegisterField) {TMC5031_OFS245_MASK, TMC5031_OFS245_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS246_MASK              0x00400000
#define TMC5031_OFS246_SHIFT             22
#define TMC5031_OFS246_FIELD(motor)             ((RegisterField) {TMC5031_OFS246_MASK, TMC5031_OFS246_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS247_MASK              0x00800000
#define TMC5031_OFS247_SHIFT             23
#define TMC5031_OFS247_FIELD(motor)             ((RegisterField) {TMC5031_OFS247_MASK, TMC5031_OFS247_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS248_MASK              0x01000000
#define TMC5031_OFS248_SHIFT             24
#define TMC5031_OFS248_FIELD(motor)             ((RegisterField) {TMC5031_OFS248_MASK, TMC5031_OFS248_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS249_MASK              0x02000000
#define TMC5031_OFS249_SHIFT             25
#define TMC5031_OFS249_FIELD(motor)             ((RegisterField) {TMC5031_OFS249_MASK, TMC5031_OFS249_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS250_MASK              0x04000000
#define TMC5031_OFS250_SHIFT             26
#define TMC5031_OFS250_FIELD(motor)             ((RegisterField) {TMC5031_OFS250_MASK, TMC5031_OFS250_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS251_MASK              0x08000000
#define TMC5031_OFS251_SHIFT             27
#define TMC5031_OFS251_FIELD(motor)             ((RegisterField) {TMC5031_OFS251_MASK, TMC5031_OFS251_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS252_MASK              0x10000000
#define TMC5031_OFS252_SHIFT             28
#define TMC5031_OFS252_FIELD(motor)             ((RegisterField) {TMC5031_OFS252_MASK, TMC5031_OFS252_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS253_MASK              0x20000000
#define TMC5031_OFS253_SHIFT             29
#define TMC5031_OFS253_FIELD(motor)             ((RegisterField) {TMC5031_OFS253_MASK, TMC5031_OFS253_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS254_MASK              0x40000000
#define TMC5031_OFS254_SHIFT             30
#define TMC5031_OFS254_FIELD(motor)             ((RegisterField) {TMC5031_OFS254_MASK, TMC5031_OFS254_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_OFS255_MASK              0x80000000
#define TMC5031_OFS255_SHIFT             31
#define TMC5031_OFS255_FIELD(motor)             ((RegisterField) {TMC5031_OFS255_MASK, TMC5031_OFS255_SHIFT, TMC5031_MSLUT[7](motor), false})
#define TMC5031_W0_MASK                  0x00000003
#define TMC5031_W0_SHIFT                 0
#define TMC5031_W0_FIELD(motor)                 ((RegisterField) {TMC5031_W0_MASK, TMC5031_W0_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_W1_MASK                  0x0000000C
#define TMC5031_W1_SHIFT                 2
#define TMC5031_W1_FIELD(motor)                 ((RegisterField) {TMC5031_W1_MASK, TMC5031_W1_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_W2_MASK                  0x00000030
#define TMC5031_W2_SHIFT                 4
#define TMC5031_W2_FIELD(motor)                 ((RegisterField) {TMC5031_W2_MASK, TMC5031_W2_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_W3_MASK                  0x000000C0
#define TMC5031_W3_SHIFT                 6
#define TMC5031_W3_FIELD(motor)                 ((RegisterField) {TMC5031_W3_MASK, TMC5031_W3_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_X1_MASK                  0x0000FF00
#define TMC5031_X1_SHIFT                 8
#define TMC5031_X1_FIELD(motor)                 ((RegisterField) {TMC5031_X1_MASK, TMC5031_X1_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_X2_MASK                  0x00FF0000
#define TMC5031_X2_SHIFT                 16
#define TMC5031_X2_FIELD(motor)                 ((RegisterField) {TMC5031_X2_MASK, TMC5031_X2_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_X3_MASK                  0xFF000000
#define TMC5031_X3_SHIFT                 24
#define TMC5031_X3_FIELD(motor)                 ((RegisterField) {TMC5031_X3_MASK, TMC5031_X3_SHIFT, TMC5031_MSLUTSEL(motor), false})
#define TMC5031_START_SIN_MASK           0x000000FF
#define TMC5031_START_SIN_SHIFT          0
#define TMC5031_START_SIN_FIELD(motor)          ((RegisterField) {TMC5031_START_SIN_MASK, TMC5031_START_SIN_SHIFT, TMC5031_MSLUTSTART(motor), false})
#define TMC5031_START_SIN90_MASK         0x00FF0000
#define TMC5031_START_SIN90_SHIFT        16
#define TMC5031_START_SIN90_FIELD(motor)        ((RegisterField) {TMC5031_START_SIN90_MASK, TMC5031_START_SIN90_SHIFT, TMC5031_MSLUTSTART(motor), false})
#define TMC5031_MSCNT_MASK               0x000003FF
#define TMC5031_MSCNT_SHIFT              0
#define TMC5031_MSCNT_FIELD(motor)              ((RegisterField) {TMC5031_MSCNT_MASK, TMC5031_MSCNT_SHIFT, TMC5031_MSCNT(motor), false})
#define TMC5031_CUR_A_MASK               0x000001FF
#define TMC5031_CUR_A_SHIFT              0
#define TMC5031_CUR_A_FIELD(motor)              ((RegisterField) {TMC5031_CUR_A_MASK, TMC5031_CUR_A_SHIFT, TMC5031_MSCURACT(motor), true})
#define TMC5031_CUR_B_MASK               0x01FF0000
#define TMC5031_CUR_B_SHIFT              16
#define TMC5031_CUR_B_FIELD(motor)              ((RegisterField) {TMC5031_CUR_B_MASK, TMC5031_CUR_B_SHIFT, TMC5031_MSCURACT(motor), true})
#define TMC5031_TOFF_MASK                0x0000000F
#define TMC5031_TOFF_SHIFT               0
#define TMC5031_TOFF_FIELD(motor)               ((RegisterField) {TMC5031_TOFF_MASK, TMC5031_TOFF_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_TFD_2__0__MASK           0x00000070
#define TMC5031_TFD_2__0__SHIFT          4
#define TMC5031_TFD_2__0__FIELD(motor)          ((RegisterField) {TMC5031_TFD_2__0__MASK, TMC5031_TFD_2__0__SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_OFFSET_MASK              0x00000780
#define TMC5031_OFFSET_SHIFT             7
#define TMC5031_OFFSET_FIELD(motor)             ((RegisterField) {TMC5031_OFFSET_MASK, TMC5031_OFFSET_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_TFD___MASK               0x00000800
#define TMC5031_TFD___SHIFT              11
#define TMC5031_TFD___FIELD(motor)              ((RegisterField) {TMC5031_TFD___MASK, TMC5031_TFD___SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_DISFDCC_MASK             0x00001000
#define TMC5031_DISFDCC_SHIFT            12
#define TMC5031_DISFDCC_FIELD(motor)            ((RegisterField) {TMC5031_DISFDCC_MASK, TMC5031_DISFDCC_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_RNDTF_MASK               0x00002000
#define TMC5031_RNDTF_SHIFT              13
#define TMC5031_RNDTF_FIELD(motor)              ((RegisterField) {TMC5031_RNDTF_MASK, TMC5031_RNDTF_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_CHM_MASK                 0x00004000
#define TMC5031_CHM_SHIFT                14
#define TMC5031_CHM_FIELD(motor)                ((RegisterField) {TMC5031_CHM_MASK, TMC5031_CHM_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_TBL_MASK                 0x00018000
#define TMC5031_TBL_SHIFT                15
#define TMC5031_TBL_FIELD(motor)                ((RegisterField) {TMC5031_TBL_MASK, TMC5031_TBL_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_VSENSE_MASK              0x00020000
#define TMC5031_VSENSE_SHIFT             17
#define TMC5031_VSENSE_FIELD(motor)             ((RegisterField) {TMC5031_VSENSE_MASK, TMC5031_VSENSE_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_VHIGHFS_MASK             0x00040000
#define TMC5031_VHIGHFS_SHIFT            18
#define TMC5031_VHIGHFS_FIELD(motor)            ((RegisterField) {TMC5031_VHIGHFS_MASK, TMC5031_VHIGHFS_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_VHIGHCHM_MASK            0x00080000
#define TMC5031_VHIGHCHM_SHIFT           19
#define TMC5031_VHIGHCHM_FIELD(motor)           ((RegisterField) {TMC5031_VHIGHCHM_MASK, TMC5031_VHIGHCHM_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_SYNC_MASK                0x00F00000
#define TMC5031_SYNC_SHIFT               20
#define TMC5031_SYNC_FIELD(motor)               ((RegisterField) {TMC5031_SYNC_MASK, TMC5031_SYNC_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_DISS2G_MASK              0x40000000
#define TMC5031_DISS2G_SHIFT             30
#define TMC5031_DISS2G_FIELD(motor)             ((RegisterField) {TMC5031_DISS2G_MASK, TMC5031_DISS2G_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_HSTRT_MASK               0x00000070
#define TMC5031_HSTRT_SHIFT              4
#define TMC5031_HSTRT_FIELD(motor)              ((RegisterField) {TMC5031_HSTRT_MASK, TMC5031_HSTRT_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_HEND_MASK                0x00000780
#define TMC5031_HEND_SHIFT               7
#define TMC5031_HEND_FIELD(motor)               ((RegisterField) {TMC5031_HEND_MASK, TMC5031_HEND_SHIFT, TMC5031_CHOPCONF(motor), false})
#define TMC5031_SEMIN_MASK               0x0000000F
#define TMC5031_SEMIN_SHIFT              0
#define TMC5031_SEMIN_FIELD(motor)              ((RegisterField) {TMC5031_SEMIN_MASK, TMC5031_SEMIN_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_SEUP_MASK                0x00000060
#define TMC5031_SEUP_SHIFT               5
#define TMC5031_SEUP_FIELD(motor)               ((RegisterField) {TMC5031_SEUP_MASK, TMC5031_SEUP_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_SEMAX_MASK               0x00000F00
#define TMC5031_SEMAX_SHIFT              8
#define TMC5031_SEMAX_FIELD(motor)              ((RegisterField) {TMC5031_SEMAX_MASK, TMC5031_SEMAX_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_SEDN_MASK                0x00006000
#define TMC5031_SEDN_SHIFT               13
#define TMC5031_SEDN_FIELD(motor)               ((RegisterField) {TMC5031_SEDN_MASK, TMC5031_SEDN_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_SEIMIN_MASK              0x00008000
#define TMC5031_SEIMIN_SHIFT             15
#define TMC5031_SEIMIN_FIELD(motor)             ((RegisterField) {TMC5031_SEIMIN_MASK, TMC5031_SEIMIN_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_SGT_MASK                 0x007F0000
#define TMC5031_SGT_SHIFT                16
#define TMC5031_SGT_FIELD(motor)                ((RegisterField) {TMC5031_SGT_MASK, TMC5031_SGT_SHIFT, TMC5031_COOLCONF(motor), true})
#define TMC5031_SFILT_MASK               0x01000000
#define TMC5031_SFILT_SHIFT              24
#define TMC5031_SFILT_FIELD(motor)              ((RegisterField) {TMC5031_SFILT_MASK, TMC5031_SFILT_SHIFT, TMC5031_COOLCONF(motor), false})
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M1 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_MRES_FIELD(motor)               ((RegisterField) {TMC5031_MRES_MASK, TMC5031_MRES_SHIFT,  TMC5031_COOLCONF(motor), false})
#define TMC5031_SG_RESULT_MASK           0x000003FF
#define TMC5031_SG_RESULT_SHIFT          0
#define TMC5031_SG_RESULT_FIELD(motor)          ((RegisterField) {TMC5031_SG_RESULT_MASK, TMC5031_SG_RESULT_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_FSACTIVE_MASK            0x00008000
#define TMC5031_FSACTIVE_SHIFT           15
#define TMC5031_FSACTIVE_FIELD(motor)           ((RegisterField) {TMC5031_FSACTIVE_MASK, TMC5031_FSACTIVE_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_CS_ACTUAL_MASK           0x001F0000
#define TMC5031_CS_ACTUAL_SHIFT          16
#define TMC5031_CS_ACTUAL_FIELD(motor)          ((RegisterField) {TMC5031_CS_ACTUAL_MASK, TMC5031_CS_ACTUAL_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_STALLGUARD_MASK          0x01000000
#define TMC5031_STALLGUARD_SHIFT         24
#define TMC5031_STALLGUARD_FIELD(motor)         ((RegisterField) {TMC5031_STALLGUARD_MASK, TMC5031_STALLGUARD_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_OT_MASK                  0x02000000
#define TMC5031_OT_SHIFT                 25
#define TMC5031_OT_FIELD(motor)                 ((RegisterField) {TMC5031_OT_MASK, TMC5031_OT_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_OTPW_MASK                0x04000000
#define TMC5031_OTPW_SHIFT               26
#define TMC5031_OTPW_FIELD(motor)               ((RegisterField) {TMC5031_OTPW_MASK, TMC5031_OTPW_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_S2GA_MASK                0x08000000
#define TMC5031_S2GA_SHIFT               27
#define TMC5031_S2GA_FIELD(motor)               ((RegisterField) {TMC5031_S2GA_MASK, TMC5031_S2GA_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_S2GB_MASK                0x10000000
#define TMC5031_S2GB_SHIFT               28
#define TMC5031_S2GB_FIELD(motor)               ((RegisterField) {TMC5031_S2GB_MASK, TMC5031_S2GB_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_OLA_MASK                 0x20000000
#define TMC5031_OLA_SHIFT                29
#define TMC5031_OLA_FIELD(motor)                ((RegisterField) {TMC5031_OLA_MASK, TMC5031_OLA_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_OLB_MASK                 0x40000000
#define TMC5031_OLB_SHIFT                30
#define TMC5031_OLB_FIELD(motor)                ((RegisterField) {TMC5031_OLB_MASK, TMC5031_OLB_SHIFT, TMC5031_DRVSTATUS(motor), false})
#define TMC5031_STST_MASK                0x80000000
#define TMC5031_STST_SHIFT               31
#define TMC5031_STST_FIELD(motor)               ((RegisterField) {TMC5031_STST_MASK, TMC5031_STST_SHIFT, TMC5031_DRVSTATUS(motor), false})



#endif
