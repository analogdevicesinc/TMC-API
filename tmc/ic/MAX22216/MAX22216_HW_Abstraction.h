/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef max22216_HW_ABSTRACTION
#define max22216_HW_ABSTRACTION


// Constants
#define MAX22216_SYNC_BYTE       0x55
#define MAX22216_MASTER_ADDRESS  0xFF

// motion modes
#define MAX22216_MOTION_MODE_STOPPED    0
#define MAX22216_MOTION_MODE_TORQUE     1
#define MAX22216_MOTION_MODE_VELOCITY   2
#define MAX22216_MOTION_MODE_POSITION   3
#define MAX22216_MOTION_MODE_UQ_UD_EXT  8

// PHI_E selections
#define MAX22216_PHI_E_EXTERNAL   1
#define MAX22216_PHI_E_OPEN_LOOP  2
#define MAX22216_PHI_E_ABN        3
#define MAX22216_PHI_E_HALL       5
#define MAX22216_PHI_E_AENC       6
#define MAX22216_PHI_A_AENC       7

#define MAX22216_STATE_NOTHING_TO_DO    0
#define MAX22216_STATE_START_INIT       1
#define MAX22216_STATE_WAIT_INIT_TIME   2
#define MAX22216_STATE_ESTIMATE_OFFSET  3

#define MAX22216_CHIPINFO_ADDR_SI_TYPE     0
#define MAX22216_CHIPINFO_ADDR_SI_VERSION  1
#define MAX22216_CHIPINFO_ADDR_SI_DATE     2
#define MAX22216_CHIPINFO_ADDR_SI_TIME     3
#define MAX22216_CHIPINFO_ADDR_SI_VARIANT  4
#define MAX22216_CHIPINFO_ADDR_SI_BUILD    5

#define MAX22216_WRITE_BIT 0x80
#define MAX22216_ADDRESS_MASK 0x7F


// Registers in max22216
#define MAX22216_GLOBAL_CTRL         0x00
#define MAX22216_GLOBAL_CFG          0x01
#define MAX22216_STATUS              0x02
#define MAX22216_STATUS_CFG          0x03
#define MAX22216_DC_H2L              0x04
#define MAX22216_VM_MONITOR          0x05
#define MAX22216_VM_THRESHOLD        0x06
#define MAX22216_F_AC                0x07
#define MAX22216_U_AC_SCAN           0x08
#define MAX22216_CFG_DC_L2H_0        0x09
#define MAX22216_CFG_DC_H_0          0x0A
#define MAX22216_CFG_DC_L_0          0x0B
#define MAX22216_CFG_L2H_TIME_0      0x0C
#define MAX22216_CFG_CTRL0_0         0x0D
#define MAX22216_CFG_CTRL1_0         0x0E
#define MAX22216_CFG_DPM0_0          0x0F
#define MAX22216_CFG_DPM1_0          0x10
#define MAX22216_CFG_IDC_THLD_0      0x11
#define MAX22216_CFG_R_THLD_0        0x12
#define MAX22216_CFG_IND_0_0         0x13
#define MAX22216_CFG_IND_1_0         0x14
#define MAX22216_CFG_P_0             0x15
#define MAX22216_CFG_I_0             0x16
#define MAX22216_CFG_DC_L2H_1        0x17
#define MAX22216_CFG_DC_H_1          0x18
#define MAX22216_CFG_DC_L_1          0x19
#define MAX22216_CFG_L2H_TIME_1      0x1A
#define MAX22216_CFG_CTRL0_1         0x1B
#define MAX22216_CFG_CTRL1_1         0x1C
#define MAX22216_CFG_DPM0_1          0x1D
#define MAX22216_CFG_DPM1_1          0x1E
#define MAX22216_CFG_IDC_THLD_1      0x1F
#define MAX22216_CFG_R_THLD_1        0x20
#define MAX22216_CFG_IND_0_1         0x21
#define MAX22216_CFG_IND_1_1         0x22
#define MAX22216_CFG_P_1             0x23
#define MAX22216_CFG_I_1             0x24
#define MAX22216_CFG_DC_L2H_2        0x25
#define MAX22216_CFG_DC_H_2          0x26
#define MAX22216_CFG_DC_L_2          0x27
#define MAX22216_CFG_L2H_TIME_2      0x28
#define MAX22216_CFG_CTRL0_2         0x29
#define MAX22216_CFG_CTRL1_2         0x2A
#define MAX22216_CFG_DPM0_2          0x2B
#define MAX22216_CFG_DPM1_2          0x2C
#define MAX22216_CFG_IDC_THLD_2      0x2D
#define MAX22216_CFG_R_THLD_2        0x2E
#define MAX22216_CFG_IND_0_2         0x2F
#define MAX22216_CFG_IND_1_2         0x30
#define MAX22216_CFG_P_2             0x31
#define MAX22216_CFG_I_2             0x32
#define MAX22216_CFG_DC_L2H_3        0x33
#define MAX22216_CFG_DC_H_3          0x34
#define MAX22216_CFG_DC_L_3          0x35
#define MAX22216_CFG_L2H_TIME_3      0x36
#define MAX22216_CFG_CTRL0_3         0x37
#define MAX22216_CFG_CTRL1_3         0x38
#define MAX22216_CFG_DPM0_3          0x39
#define MAX22216_CFG_DPM1_3          0x3A
#define MAX22216_CFG_IDC_THLD_3      0x3B
#define MAX22216_CFG_R_THLD_3        0x3C
#define MAX22216_CFG_IND_0_3         0x3D
#define MAX22216_CFG_IND_1_3         0x3E
#define MAX22216_CFG_P_3             0x3F
#define MAX22216_CFG_I_3             0x40
#define MAX22216_I_DPM_PEAK_0        0x41
#define MAX22216_I_DPM_VALLEY_0      0x42
#define MAX22216_TRAVEL_TIME_0       0x43
#define MAX22216_REACTION_TIME_0     0x44
#define MAX22216_I_MONITOR_0         0x45
#define MAX22216_I_AC_0              0x47
#define MAX22216_RES_0               0x48
#define MAX22216_PWM_DUTY_0          0x49
#define MAX22216_I_DPM_PEAK_1        0x4A
#define MAX22216_I_DPM_VALLEY_1      0x4B
#define MAX22216_TRAVEL_TIME_1       0x4C
#define MAX22216_REACTION_TIME_1     0x4D
#define MAX22216_I_MONITOR_1         0x4E
#define MAX22216_I_AC_1              0x50
#define MAX22216_RES_1               0x51
#define MAX22216_PWM_DUTY_1          0x52
#define MAX22216_I_DPM_PEAK_2        0x53
#define MAX22216_I_DPM_VALLEY_2      0x54
#define MAX22216_TRAVEL_TIME_2       0x55
#define MAX22216_REACTION_TIME_2     0x56
#define MAX22216_I_MONITOR_2         0x57
#define MAX22216_I_AC_2              0x59
#define MAX22216_RES_2               0x5A
#define MAX22216_PWM_DUTY_2          0x5B
#define MAX22216_I_DPM_PEAK_3        0x5C
#define MAX22216_I_DPM_VALLEY_3      0x5D
#define MAX22216_TRAVEL_TIME_3       0x5E
#define MAX22216_REACTION_TIME_3     0x5F
#define MAX22216_I_MONITOR_3         0x60
#define MAX22216_I_AC_3              0x62
#define MAX22216_RES_3               0x63
#define MAX22216_PWM_DUTY_3          0x64
#define MAX22216_FAULT0              0x65
#define MAX22216_FAULT1              0x66

#define MAX22216_OTP_CONTROL         0x68
#define MAX22216_OTP_STATUS          0x69
#define MAX22216_OTP_DATA0           0x7A
#define MAX22216_OTP_DATA1           0x7B
#define MAX22216_OTP_ADDR            0x7C


// CRC Fields
#define __None__                           0
#define MAX22216_CRC0_MASK                 0x1
#define MAX22216_CRC0_SHIFT                0
#define MAX22216_CRC0_FIELD                ((RegisterField) {MAX22216_CRC0_MASK, MAX22216_CRC0_SHIFT, __None__ , false})
#define MAX22216_CRC1_MASK                 0x2
#define MAX22216_CRC1_SHIFT                1
#define MAX22216_CRC1_FIELD                ((RegisterField) {MAX22216_CRC1_MASK, MAX22216_CRC1_SHIFT, __None__ , false})
#define MAX22216_CRC2_MASK                 0x4
#define MAX22216_CRC2_SHIFT                2
#define MAX22216_CRC2_FIELD                ((RegisterField) {MAX22216_CRC2_MASK, MAX22216_CRC2_SHIFT, __None__ , false})
#define MAX22216_CRC3_MASK                 0x8
#define MAX22216_CRC3_SHIFT                3
#define MAX22216_CRC3_FIELD                ((RegisterField) {MAX22216_CRC3_MASK, MAX22216_CRC3_SHIFT, __None__, false})
#define MAX22216_CRC4_MASK                 0x10
#define MAX22216_CRC4_SHIFT                4
#define MAX22216_CRC4_FIELD                ((RegisterField) {MAX22216_CRC4_MASK, MAX22216_CRC4_SHIFT, __None__, false})
#define MAX22216_CRC4_SHIFT                4
#define MAX22216_CRC4_FIELD                ((RegisterField) {MAX22216_CRC4_MASK, MAX22216_CRC4_SHIFT, __None__, false})
#define MAX22216_CRC5_MASK                 0x20
#define MAX22216_CRC5_SHIFT                5
#define MAX22216_CRC5_FIELD                ((RegisterField) {MAX22216_CRC5_MASK, MAX22216_CRC5_SHIFT, __None__, false})

// Register fields
#define MAX22216_SRT_PROG_MASK                 0x00000001
#define MAX22216_SRT_PROG_SHIFT                0
#define MAX22216_SRT_PROG_FIELD                ((RegisterField) {MAX22216_SRT_PROG_MASK, MAX22216_SRT_PROG_SHIFT, MAX22216_OTP_CONTROL, false})
#define MAX22216_STOP_PROG_MASK                0x00000002
#define MAX22216_STOP_PROG_SHIFT               1
#define MAX22216_STOP_PROG_FIELD               ((RegisterField) {MAX22216_STOP_PROG_MASK, MAX22216_STOP_PROG_SHIFT, MAX22216_OTP_CONTROL, false})
#define MAX22216_VERI_FAIL_MASK                0x00000002
#define MAX22216_VERI_FAIL_SHIFT               1
#define MAX22216_VERI_FAIL_FIELD               ((RegisterField) {MAX22216_VERI_FAIL_MASK, MAX22216_VERI_FAIL_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_OTP_FULL_MASK                 0x00000004
#define MAX22216_OTP_FULL_SHIFT                2
#define MAX22216_OTP_FULL_FIELD                ((RegisterField) {MAX22216_OTP_FULL_MASK, MAX22216_OTP_FULL_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_VPP_INIT_FAIL_MASK            0x00000008
#define MAX22216_VPP_INIT_FAIL_SHIFT           3
#define MAX22216_VPP_INIT_FAIL_FIELD           ((RegisterField) {MAX22216_VPP_INIT_FAIL_MASK, MAX22216_VPP_INIT_FAIL_MASK, MAX22216_OTP_STATUS, false})
#define MAX22216_OV_DURING_BURN_PULSE_MASK     0x00000010
#define MAX22216_OV_DURING_BURN_PULSE_SHIFT    4
#define MAX22216_OV_DURING_BURN_PULSE_FIELD    ((RegisterField) {MAX22216_OV_DURING_BURN_PULSE_MASK, MAX22216_OV_DURING_BURN_PULSE_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_ECC_ERR_1BIT_MASK             0x00000020
#define MAX22216_ECC_ERR_1BIT_SHIFT            5
#define MAX22216_ECC_ERR_1BIT_FIELD            ((RegisterField) {MAX22216_ECC_ERR_1BIT_MASK, MAX22216_ECC_ERR_1BIT_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_ECC_ERR_2BIT_MASK             0x00000040
#define MAX22216_ECC_ERR_2BIT_SHIFT            6
#define MAX22216_ECC_ERR_2BIT_FIELD            ((RegisterField) {MAX22216_ECC_ERR_2BIT_MASK, MAX22216_ECC_ERR_2BIT_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_DONE_MASK                     0x00000080
#define MAX22216_DONE_SHIFT                    7
#define MAX22216_DONE_FIELD                    ((RegisterField) {MAX22216_DONE_MASK, MAX22216_DONE_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_OTP_FAIL_MASK                 ~(MAX22216_DONE_MASK)
#define MAX22216_OTP_FAIL_SHIFT                0
#define MAX22216_OTP_FAIL_FIELD                ((RegisterField) {MAX22216_OTP_FAIL_MASK, MAX22216_OTP_FAIL_SHIFT, MAX22216_OTP_STATUS, false})
#define MAX22216_OTP_DATA0_MASK                0x000000FF
#define MAX22216_OTP_DATA0_SHIFT               0
#define MAX22216_OTP_DATA0_FIELD               ((RegisterField) {MAX22216_OTP_DATA0_MASK, MAX22216_OTP_DATA0_SHIFT, MAX22216_OTP_DATA0, false})
#define MAX22216_OTP_DATA1_MASK                0x000000FF
#define MAX22216_OTP_DATA1_SHIFT               0
#define MAX22216_OTP_DATA1_FIELD               ((RegisterField) {MAX22216_OTP_DATA1_MASK, MAX22216_OTP_DATA1_SHIFT, MAX22216_OTP_DATA1, false})
#define MAX22216_OTP_ADDR_MASK                 0x000000FF
#define MAX22216_OTP_ADDR_SHIFT                0
#define MAX22216_OTP_ADDR_FIELD                ((RegisterField) {MAX22216_OTP_ADDR_MASK, MAX22216_OTP_ADDR_SHIFT, MAX22216_OTP_ADDR, false})

// Register fields in max22216
#define MAX22216_CNTL0_MASK                 0x00000001
#define MAX22216_CNTL0_SHIFT                0
#define MAX22216_CNTL0_FIELD                ((RegisterField) {MAX22216_CNTL0_MASK, MAX22216_CNTL0_SHIFT, MAX22216_GLOBAL_CTRL, false})
#define MAX22216_CNTL1_MASK                 0x00000002
#define MAX22216_CNTL1_SHIFT                1
#define MAX22216_CNTL1_FIELD                ((RegisterField) {MAX22216_CNTL1_MASK, MAX22216_CNTL1_SHIFT, MAX22216_GLOBAL_CTRL, false})
#define MAX22216_CNTL2_MASK                 0x00000004
#define MAX22216_CNTL2_SHIFT                2
#define MAX22216_CNTL2_FIELD                ((RegisterField) {MAX22216_CNTL2_MASK, MAX22216_CNTL2_SHIFT, MAX22216_GLOBAL_CTRL, false})
#define MAX22216_CNTL3_MASK                 0x00000008
#define MAX22216_CNTL3_SHIFT                3
#define MAX22216_CNTL3_FIELD                ((RegisterField) {MAX22216_CNTL3_MASK, MAX22216_CNTL3_SHIFT, MAX22216_GLOBAL_CTRL, false})
#define MAX22216_F_PWM_M_MASK               0x000000F0
#define MAX22216_F_PWM_M_SHIFT              4
#define MAX22216_F_PWM_M_FIELD              ((RegisterField) {MAX22216_F_PWM_M_MASK, MAX22216_F_PWM_M_SHIFT, MAX22216_GLOBAL_CTRL, false})
#define MAX22216_CHS_MASK                   0x0000000F
#define MAX22216_CHS_SHIFT                  0
#define MAX22216_CHS_FIELD                  ((RegisterField) {MAX22216_CHS_MASK, MAX22216_CHS_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_VDRNVDRDUTY_MASK           0x00000010
#define MAX22216_VDRNVDRDUTY_SHIFT          4
#define MAX22216_VDRNVDRDUTY_FIELD          ((RegisterField) {MAX22216_VDRNVDRDUTY_MASK, MAX22216_VDRNVDRDUTY_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_STAT_POL_MASK              0x00000040
#define MAX22216_STAT_POL_SHIFT             6
#define MAX22216_STAT_POL_FIELD             ((RegisterField) {MAX22216_STAT_POL_MASK, MAX22216_STAT_POL_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_CNTL_POL_MASK              0x00000080
#define MAX22216_CNTL_POL_SHIFT             7
#define MAX22216_CNTL_POL_FIELD             ((RegisterField) {MAX22216_CNTL_POL_MASK, MAX22216_CNTL_POL_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_UVM_MASK                 0x00000100
#define MAX22216_M_UVM_SHIFT                8
#define MAX22216_M_UVM_FIELD                ((RegisterField) {MAX22216_M_UVM_MASK, MAX22216_M_UVM_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_COMF_MASK                0x00000200
#define MAX22216_M_COMF_SHIFT               9
#define MAX22216_M_COMF_FIELD               ((RegisterField) {MAX22216_M_COMF_MASK, MAX22216_M_COMF_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_DPM_MASK                 0x00000400
#define MAX22216_M_DPM_SHIFT                10
#define MAX22216_M_DPM_FIELD                ((RegisterField) {MAX22216_M_DPM_MASK, MAX22216_M_DPM_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_HHF_MASK                 0x00000800
#define MAX22216_M_HHF_SHIFT                11
#define MAX22216_M_HHF_FIELD                ((RegisterField) {MAX22216_M_HHF_MASK, MAX22216_M_HHF_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_OLF_MASK                 0x00001000
#define MAX22216_M_OLF_SHIFT                12
#define MAX22216_M_OLF_FIELD                ((RegisterField) {MAX22216_M_OLF_MASK, MAX22216_M_OLF_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_OCP_MASK                 0x00002000
#define MAX22216_M_OCP_SHIFT                13
#define MAX22216_M_OCP_FIELD                ((RegisterField) {MAX22216_M_OCP_MASK, MAX22216_M_OCP_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_M_OVT_MASK                 0x00004000
#define MAX22216_M_OVT_SHIFT                14
#define MAX22216_M_OVT_FIELD                ((RegisterField) {MAX22216_M_OVT_MASK, MAX22216_M_OVT_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_ACTIVE_MASK                0x00008000
#define MAX22216_ACTIVE_SHIFT               15
#define MAX22216_ACTIVE_FIELD               ((RegisterField) {MAX22216_ACTIVE_MASK, MAX22216_ACTIVE_SHIFT, MAX22216_GLOBAL_CFG, false})
#define MAX22216_RFU_MASK                   0x00000001
#define MAX22216_RFU_SHIFT                  0
#define MAX22216_RFU_FIELD                  ((RegisterField) {MAX22216_RFU_MASK, MAX22216_RFU_SHIFT, MAX22216_STATUS, false})
#define MAX22216_UVM_MASK                   0x00000002
#define MAX22216_UVM_SHIFT                  1
#define MAX22216_UVM_FIELD                  ((RegisterField) {MAX22216_UVM_MASK, MAX22216_UVM_SHIFT, MAX22216_STATUS, false})
#define MAX22216_COMER_MASK                 0x00000004
#define MAX22216_COMER_SHIFT                2
#define MAX22216_COMER_FIELD                ((RegisterField) {MAX22216_COMER_MASK, MAX22216_COMER_SHIFT, MAX22216_STATUS, false})
#define MAX22216_DPM_MASK                   0x00000008
#define MAX22216_DPM_SHIFT                  3
#define MAX22216_DPM_FIELD                  ((RegisterField) {MAX22216_DPM_MASK, MAX22216_DPM_SHIFT, MAX22216_STATUS, false})
#define MAX22216_HHF_MASK                   0x00000010
#define MAX22216_HHF_SHIFT                  4
#define MAX22216_HHF_FIELD                  ((RegisterField) {MAX22216_HHF_MASK, MAX22216_HHF_SHIFT, MAX22216_STATUS, false})
#define MAX22216_OLF_MASK                   0x00000020
#define MAX22216_OLF_SHIFT                  5
#define MAX22216_OLF_FIELD                  ((RegisterField) {MAX22216_OLF_MASK, MAX22216_OLF_SHIFT, MAX22216_STATUS, false})
#define MAX22216_OCP_MASK                   0x00000040
#define MAX22216_OCP_SHIFT                  6
#define MAX22216_OCP_FIELD                  ((RegisterField) {MAX22216_OCP_MASK, MAX22216_OCP_SHIFT, MAX22216_STATUS, false})
#define MAX22216_OVT_MASK                   0x00000080
#define MAX22216_OVT_SHIFT                  7
#define MAX22216_OVT_FIELD                  ((RegisterField) {MAX22216_OVT_MASK, MAX22216_OVT_SHIFT, MAX22216_STATUS, false})
#define MAX22216_IND_MASK                   0x00000100
#define MAX22216_IND_SHIFT                  8
#define MAX22216_IND_FIELD                  ((RegisterField) {MAX22216_IND_MASK, MAX22216_IND_SHIFT, MAX22216_STATUS, false})
#define MAX22216_RES_MASK                   0x00000200
#define MAX22216_RES_SHIFT                  9
#define MAX22216_RES_FIELD                  ((RegisterField) {MAX22216_RES_MASK, MAX22216_RES_SHIFT, MAX22216_STATUS, false})
#define MAX22216_MIN_T_ON_MASK              0x00000400
#define MAX22216_MIN_T_ON_SHIFT             10
#define MAX22216_MIN_T_ON_FIELD             ((RegisterField) {MAX22216_MIN_T_ON_MASK, MAX22216_MIN_T_ON_SHIFT, MAX22216_STATUS, false})
#define MAX22216_STT0_MASK                  0x00000800
#define MAX22216_STT0_SHIFT                 11
#define MAX22216_STT0_FIELD                 ((RegisterField) {MAX22216_STT0_MASK, MAX22216_STT0_SHIFT, MAX22216_STATUS, false})
#define MAX22216_STT1_MASK                  0x00001000
#define MAX22216_STT1_SHIFT                 12
#define MAX22216_STT1_FIELD                 ((RegisterField) {MAX22216_STT1_MASK, MAX22216_STT1_SHIFT, MAX22216_STATUS, false})
#define MAX22216_STT2_MASK                  0x00002000
#define MAX22216_STT2_SHIFT                 13
#define MAX22216_STT2_FIELD                 ((RegisterField) {MAX22216_STT2_MASK, MAX22216_STT2_SHIFT, MAX22216_STATUS, false})
#define MAX22216_STT3_MASK                  0x00004000
#define MAX22216_STT3_SHIFT                 14
#define MAX22216_STT3_FIELD                 ((RegisterField) {MAX22216_STT3_MASK, MAX22216_STT3_SHIFT, MAX22216_STATUS, false})
#define MAX22216_STAT_FUN_MASK              0x00000007
#define MAX22216_STAT_FUN_SHIFT             0
#define MAX22216_STAT_FUN_FIELD             ((RegisterField) {MAX22216_STAT_FUN_MASK, MAX22216_STAT_FUN_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_STAT_SEL0_MASK             0x00000008
#define MAX22216_STAT_SEL0_SHIFT            3
#define MAX22216_STAT_SEL0_FIELD            ((RegisterField) {MAX22216_STAT_SEL0_MASK, MAX22216_STAT_SEL0_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_STAT_SEL1_MASK             0x00000010
#define MAX22216_STAT_SEL1_SHIFT            4
#define MAX22216_STAT_SEL1_FIELD            ((RegisterField) {MAX22216_STAT_SEL1_MASK, MAX22216_STAT_SEL1_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_STRETCH_EN_MASK            0x00000060
#define MAX22216_STRETCH_EN_SHIFT           5
#define MAX22216_STRETCH_EN_FIELD           ((RegisterField) {MAX22216_STRETCH_EN_MASK, MAX22216_STRETCH_EN_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_EN_LDO_MASK                0x00000080
#define MAX22216_EN_LDO_SHIFT               7
#define MAX22216_EN_LDO_FIELD               ((RegisterField) {MAX22216_EN_LDO_MASK, MAX22216_EN_LDO_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_V5_NV3_MASK                0x00000100
#define MAX22216_V5_NV3_SHIFT               8
#define MAX22216_V5_NV3_FIELD               ((RegisterField) {MAX22216_V5_NV3_MASK, MAX22216_V5_NV3_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_M_UVM_CMP_MASK             0x00000200
#define MAX22216_M_UVM_CMP_SHIFT            9
#define MAX22216_M_UVM_CMP_FIELD            ((RegisterField) {MAX22216_M_UVM_CMP_MASK, MAX22216_M_UVM_CMP_SHIFT, MAX22216_STATUS_CFG, false})
#define MAX22216_DC_H2L_MASK                0x0000FFFF
#define MAX22216_DC_H2L_SHIFT               0
#define MAX22216_DC_H2L_FIELD               ((RegisterField) {MAX22216_DC_H2L_MASK, MAX22216_DC_H2L_SHIFT, MAX22216_DC_H2L, true})
#define MAX22216_VM_MONITOR_MASK            0x00001FFF
#define MAX22216_VM_MONITOR_SHIFT           0
#define MAX22216_VM_MONITOR_FIELD           ((RegisterField) {MAX22216_VM_MONITOR_MASK, MAX22216_VM_MONITOR_SHIFT, MAX22216_VM_MONITOR, false})
#define MAX22216_VM_THLD_DOWN_MASK          0x0000000F
#define MAX22216_VM_THLD_DOWN_SHIFT         0
#define MAX22216_VM_THLD_DOWN_FIELD         ((RegisterField) {MAX22216_VM_THLD_DOWN_MASK, MAX22216_VM_THLD_DOWN_SHIFT, MAX22216_VM_THRESHOLD, false})
#define MAX22216_VM_THLD_UP_MASK            0x000000F0
#define MAX22216_VM_THLD_UP_SHIFT           4
#define MAX22216_VM_THLD_UP_FIELD           ((RegisterField) {MAX22216_VM_THLD_UP_MASK, MAX22216_VM_THLD_UP_SHIFT, MAX22216_VM_THRESHOLD, false})
#define MAX22216_F_AC_SCAN_MASK             0x00000FFF
#define MAX22216_F_AC_SCAN_SHIFT            0
#define MAX22216_F_AC_SCAN_FIELD            ((RegisterField) {MAX22216_F_AC_SCAN_MASK, MAX22216_F_AC_SCAN_SHIFT, MAX22216_F_AC, false})
#define MAX22216_U_AC_SCAN_MASK             0x00007FFF
#define MAX22216_U_AC_SCAN_SHIFT            0
#define MAX22216_U_AC_SCAN_FIELD            ((RegisterField) {MAX22216_U_AC_SCAN_MASK, MAX22216_U_AC_SCAN_SHIFT, MAX22216_U_AC_SCAN, false})
#define MAX22216_DC_L2H_MASK                0x0000FFFF
#define MAX22216_DC_L2H_SHIFT               0
#define MAX22216_DC_L2H_FIELD               ((RegisterField) {MAX22216_DC_L2H_MASK, MAX22216_DC_L2H_SHIFT, MAX22216_CFG_DC_L2H_0, true})
#define MAX22216_DC_H_MASK                  0x0000FFFF
#define MAX22216_DC_H_SHIFT                 0
#define MAX22216_DC_H_FIELD                 ((RegisterField) {MAX22216_DC_H_MASK, MAX22216_DC_H_SHIFT, MAX22216_CFG_DC_H_0, true})
#define MAX22216_DC_L_MASK                  0x0000FFFF
#define MAX22216_DC_L_SHIFT                 0
#define MAX22216_DC_L_FIELD                 ((RegisterField) {MAX22216_DC_L_MASK, MAX22216_DC_L_SHIFT, MAX22216_CFG_DC_L_0, true})
#define MAX22216_TIME_L2H_MASK              0x0000FFFF
#define MAX22216_TIME_L2H_SHIFT             0
#define MAX22216_TIME_L2H_FIELD             ((RegisterField) {MAX22216_TIME_L2H_MASK, MAX22216_TIME_L2H_SHIFT, MAX22216_CFG_L2H_TIME_0, false})
#define MAX22216_RAMP_MASK                  0x000000FF
#define MAX22216_RAMP_SHIFT                 0
#define MAX22216_RAMP_FIELD                 ((RegisterField) {MAX22216_RAMP_MASK, MAX22216_RAMP_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_RUPE_MASK                  0x00000100
#define MAX22216_RUPE_SHIFT                 8
#define MAX22216_RUPE_FIELD                 ((RegisterField) {MAX22216_RUPE_MASK, MAX22216_RUPE_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_RMDE_MASK                  0x00000200
#define MAX22216_RMDE_SHIFT                 9
#define MAX22216_RMDE_FIELD                 ((RegisterField) {MAX22216_RMDE_MASK, MAX22216_RMDE_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_RDWE_MASK                  0x00000400
#define MAX22216_RDWE_SHIFT                 10
#define MAX22216_RDWE_FIELD                 ((RegisterField) {MAX22216_RDWE_MASK, MAX22216_RDWE_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_H2L_EN_MASK                0x00000800
#define MAX22216_H2L_EN_SHIFT               11
#define MAX22216_H2L_EN_FIELD               ((RegisterField) {MAX22216_H2L_EN_MASK, MAX22216_H2L_EN_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_OL_EN_MASK                 0x00001000
#define MAX22216_OL_EN_SHIFT                12
#define MAX22216_OL_EN_FIELD                ((RegisterField) {MAX22216_OL_EN_MASK, MAX22216_OL_EN_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_HHF_EN_MASK                0x00002000
#define MAX22216_HHF_EN_SHIFT               13
#define MAX22216_HHF_EN_FIELD               ((RegisterField) {MAX22216_HHF_EN_MASK, MAX22216_HHF_EN_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_CTRL_MODE_MASK             0x0000C000
#define MAX22216_CTRL_MODE_SHIFT            14
#define MAX22216_CTRL_MODE_FIELD            ((RegisterField) {MAX22216_CTRL_MODE_MASK, MAX22216_CTRL_MODE_SHIFT, MAX22216_CFG_CTRL0_0, false})
#define MAX22216_SNSF_MASK                  0x00000003
#define MAX22216_SNSF_SHIFT                 0
#define MAX22216_SNSF_FIELD                 ((RegisterField) {MAX22216_SNSF_MASK, MAX22216_SNSF_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_GAIN_MASK                  0x0000000C
#define MAX22216_GAIN_SHIFT                 2
#define MAX22216_GAIN_FIELD                 ((RegisterField) {MAX22216_GAIN_MASK, MAX22216_GAIN_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_SLEW_RATE_MASK             0x00000030
#define MAX22216_SLEW_RATE_SHIFT            4
#define MAX22216_SLEW_RATE_FIELD            ((RegisterField) {MAX22216_SLEW_RATE_MASK, MAX22216_SLEW_RATE_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_T_BLANKING_MASK            0x000000C0
#define MAX22216_T_BLANKING_SHIFT           6
#define MAX22216_T_BLANKING_FIELD           ((RegisterField) {MAX22216_T_BLANKING_MASK, MAX22216_T_BLANKING_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_F_PWM_MASK                 0x00000300
#define MAX22216_F_PWM_SHIFT                8
#define MAX22216_F_PWM_FIELD                ((RegisterField) {MAX22216_F_PWM_MASK, MAX22216_F_PWM_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_HSNLS_MASK                 0x00000400
#define MAX22216_HSNLS_SHIFT                10
#define MAX22216_HSNLS_FIELD                ((RegisterField) {MAX22216_HSNLS_MASK, MAX22216_HSNLS_SHIFT, MAX22216_CFG_CTRL1_0, false})
#define MAX22216_DPM_THLD_MASK              0x00000FFF
#define MAX22216_DPM_THLD_SHIFT             0
#define MAX22216_DPM_THLD_FIELD             ((RegisterField) {MAX22216_DPM_THLD_MASK, MAX22216_DPM_THLD_SHIFT, MAX22216_CFG_DPM0_0, false})
#define MAX22216_DPM_START_MASK             0x000000FF
#define MAX22216_DPM_START_SHIFT            0
#define MAX22216_DPM_START_FIELD            ((RegisterField) {MAX22216_DPM_START_MASK, MAX22216_DPM_START_SHIFT, MAX22216_CFG_DPM1_0, false})
#define MAX22216_DPM_MIN_NBR_MASK           0x00000F00
#define MAX22216_DPM_MIN_NBR_SHIFT          8
#define MAX22216_DPM_MIN_NBR_FIELD          ((RegisterField) {MAX22216_DPM_MIN_NBR_MASK, MAX22216_DPM_MIN_NBR_SHIFT, MAX22216_CFG_DPM1_0, false})
#define MAX22216_END_HIT_AUTO_MASK          0x00001000
#define MAX22216_END_HIT_AUTO_SHIFT         12
#define MAX22216_END_HIT_AUTO_FIELD         ((RegisterField) {MAX22216_END_HIT_AUTO_MASK, MAX22216_END_HIT_AUTO_SHIFT, MAX22216_CFG_DPM1_0, false})
#define MAX22216_END_HIT_TO_HIZ_AUTO_MASK   0x00002000
#define MAX22216_END_HIT_TO_HIZ_AUTO_SHIFT  13
#define MAX22216_END_HIT_TO_HIZ_AUTO_FIELD  ((RegisterField) {MAX22216_END_HIT_TO_HIZ_AUTO_MASK, MAX22216_END_HIT_TO_HIZ_AUTO_SHIFT, MAX22216_CFG_DPM1_0, false})
#define MAX22216_DPM_EN_MASK                0x00004000
#define MAX22216_DPM_EN_SHIFT               14
#define MAX22216_DPM_EN_FIELD               ((RegisterField) {MAX22216_DPM_EN_MASK, MAX22216_DPM_EN_SHIFT, MAX22216_CFG_DPM1_0, false})
#define MAX22216_IDC_THLD_MASK              0x0000FFFF
#define MAX22216_IDC_THLD_SHIFT             0
#define MAX22216_IDC_THLD_FIELD             ((RegisterField) {MAX22216_IDC_THLD_MASK, MAX22216_IDC_THLD_SHIFT, MAX22216_CFG_IDC_THLD_0, true})
#define MAX22216_RES_THLD_MASK              0x0000FFFF
#define MAX22216_RES_THLD_SHIFT             0
#define MAX22216_RES_THLD_FIELD             ((RegisterField) {MAX22216_RES_THLD_MASK, MAX22216_RES_THLD_SHIFT, MAX22216_CFG_R_THLD_0, false})
#define MAX22216_L_NBR_CALC_MASK            0x0000000F
#define MAX22216_L_NBR_CALC_SHIFT           0
#define MAX22216_L_NBR_CALC_FIELD           ((RegisterField) {MAX22216_L_NBR_CALC_MASK, MAX22216_L_NBR_CALC_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_L_MEAS_WCYCLES_MASK        0x000000F0
#define MAX22216_L_MEAS_WCYCLES_SHIFT       4
#define MAX22216_L_MEAS_WCYCLES_FIELD       ((RegisterField) {MAX22216_L_MEAS_WCYCLES_MASK, MAX22216_L_MEAS_WCYCLES_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_L_MEAS_H_MASK              0x00000100
#define MAX22216_L_MEAS_H_SHIFT             8
#define MAX22216_L_MEAS_H_FIELD             ((RegisterField) {MAX22216_L_MEAS_H_MASK, MAX22216_L_MEAS_H_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_L_MEAS_L2H_MASK            0x00000200
#define MAX22216_L_MEAS_L2H_SHIFT           9
#define MAX22216_L_MEAS_L2H_FIELD           ((RegisterField) {MAX22216_L_MEAS_L2H_MASK, MAX22216_L_MEAS_L2H_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_L_MEAS_EN_MASK             0x00000400
#define MAX22216_L_MEAS_EN_SHIFT            10
#define MAX22216_L_MEAS_EN_FIELD            ((RegisterField) {MAX22216_L_MEAS_EN_MASK, MAX22216_L_MEAS_EN_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_DITH_EN_MASK               0x00000800
#define MAX22216_DITH_EN_SHIFT              11
#define MAX22216_DITH_EN_FIELD              ((RegisterField) {MAX22216_DITH_EN_MASK, MAX22216_DITH_EN_SHIFT, MAX22216_CFG_IND_0_0, false})
#define MAX22216_IAC_THLD_MASK              0x00000FFF
#define MAX22216_IAC_THLD_SHIFT             0
#define MAX22216_IAC_THLD_FIELD             ((RegisterField) {MAX22216_IAC_THLD_MASK, MAX22216_IAC_THLD_SHIFT, MAX22216_CFG_IND_1_0, false})
#define MAX22216_CFG_P_MASK                 0x0000FFFF
#define MAX22216_CFG_P_SHIFT                0
#define MAX22216_CFG_P_FIELD                ((RegisterField) {MAX22216_CFG_P_MASK, MAX22216_CFG_P_SHIFT, MAX22216_CFG_P_0, false})
#define MAX22216_CFG_I_MASK                 0x0000FFFF
#define MAX22216_CFG_I_SHIFT                0
#define MAX22216_CFG_I_FIELD                ((RegisterField) {MAX22216_CFG_I_MASK, MAX22216_CFG_I_SHIFT, MAX22216_CFG_I_0, false})
#define MAX22216_I_DPM_PEAK_MASK            0x0000FFFF
#define MAX22216_I_DPM_PEAK_SHIFT           0
#define MAX22216_I_DPM_PEAK_FIELD           ((RegisterField) {MAX22216_I_DPM_PEAK_MASK, MAX22216_I_DPM_PEAK_SHIFT, MAX22216_I_DPM_PEAK_0, false})
#define MAX22216_I_DPM_VALLEY_MASK          0x0000FFFF
#define MAX22216_I_DPM_VALLEY_SHIFT         0
#define MAX22216_I_DPM_VALLEY_FIELD         ((RegisterField) {MAX22216_I_DPM_VALLEY_MASK, MAX22216_I_DPM_VALLEY_SHIFT, MAX22216_I_DPM_VALLEY_0, false})
#define MAX22216_TRAVEL_TIME_MASK           0x0000FFFF
#define MAX22216_TRAVEL_TIME_SHIFT          0
#define MAX22216_TRAVEL_TIME_FIELD          ((RegisterField) {MAX22216_TRAVEL_TIME_MASK, MAX22216_TRAVEL_TIME_SHIFT, MAX22216_TRAVEL_TIME_0, false})
#define MAX22216_REACTION_TIME_MASK         0x0000FFFF
#define MAX22216_REACTION_TIME_SHIFT        0
#define MAX22216_REACTION_TIME_FIELD        ((RegisterField) {MAX22216_REACTION_TIME_MASK, MAX22216_REACTION_TIME_SHIFT, MAX22216_REACTION_TIME_0, false})
#define MAX22216_I_MONITOR_MASK             0x0000FFFF
#define MAX22216_I_MONITOR_SHIFT            0
#define MAX22216_I_MONITOR_FIELD            ((RegisterField) {MAX22216_I_MONITOR_MASK, MAX22216_I_MONITOR_SHIFT, MAX22216_I_MONITOR_0, true})
#define MAX22216_I_AC_MASK                  0x0000FFFF
#define MAX22216_I_AC_SHIFT                 0
#define MAX22216_I_AC_FIELD                 ((RegisterField) {MAX22216_I_AC_MASK, MAX22216_I_AC_SHIFT, MAX22216_I_AC_0, true})
#define MAX22216_PWM_DUTYCYCLE_MASK         0x0000FFFF
#define MAX22216_PWM_DUTYCYCLE_SHIFT        0
#define MAX22216_PWM_DUTYCYCLE_FIELD        ((RegisterField) {MAX22216_PWM_DUTYCYCLE_MASK, MAX22216_PWM_DUTYCYCLE_SHIFT, MAX22216_PWM_DUTY_0, false})
#define MAX22216_OCP0_MASK                  0x00000001
#define MAX22216_OCP0_SHIFT                 0
#define MAX22216_OCP0_FIELD                 ((RegisterField) {MAX22216_OCP0_MASK, MAX22216_OCP0_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OCP1_MASK                  0x00000002
#define MAX22216_OCP1_SHIFT                 1
#define MAX22216_OCP1_FIELD                 ((RegisterField) {MAX22216_OCP1_MASK, MAX22216_OCP1_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OCP2_MASK                  0x00000004
#define MAX22216_OCP2_SHIFT                 2
#define MAX22216_OCP2_FIELD                 ((RegisterField) {MAX22216_OCP2_MASK, MAX22216_OCP2_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OCP3_MASK                  0x00000008
#define MAX22216_OCP3_SHIFT                 3
#define MAX22216_OCP3_FIELD                 ((RegisterField) {MAX22216_OCP3_MASK, MAX22216_OCP3_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_HHF0_MASK                  0x00000010
#define MAX22216_HHF0_SHIFT                 4
#define MAX22216_HHF0_FIELD                 ((RegisterField) {MAX22216_HHF0_MASK, MAX22216_HHF0_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_HHF1_MASK                  0x00000020
#define MAX22216_HHF1_SHIFT                 5
#define MAX22216_HHF1_FIELD                 ((RegisterField) {MAX22216_HHF1_MASK, MAX22216_HHF1_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_HHF2_MASK                  0x00000040
#define MAX22216_HHF2_SHIFT                 6
#define MAX22216_HHF2_FIELD                 ((RegisterField) {MAX22216_HHF2_MASK, MAX22216_HHF2_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_HHF3_MASK                  0x00000080
#define MAX22216_HHF3_SHIFT                 7
#define MAX22216_HHF3_FIELD                 ((RegisterField) {MAX22216_HHF3_MASK, MAX22216_HHF3_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OLF0_MASK                  0x00000100
#define MAX22216_OLF0_SHIFT                 8
#define MAX22216_OLF0_FIELD                 ((RegisterField) {MAX22216_OLF0_MASK, MAX22216_OLF0_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OLF1_MASK                  0x00000200
#define MAX22216_OLF1_SHIFT                 9
#define MAX22216_OLF1_FIELD                 ((RegisterField) {MAX22216_OLF1_MASK, MAX22216_OLF1_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OLF2_MASK                  0x00000400
#define MAX22216_OLF2_SHIFT                 10
#define MAX22216_OLF2_FIELD                 ((RegisterField) {MAX22216_OLF2_MASK, MAX22216_OLF2_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_OLF3_MASK                  0x00000800
#define MAX22216_OLF3_SHIFT                 11
#define MAX22216_OLF3_FIELD                 ((RegisterField) {MAX22216_OLF3_MASK, MAX22216_OLF3_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_DPM0_MASK                  0x00001000
#define MAX22216_DPM0_SHIFT                 12
#define MAX22216_DPM0_FIELD                 ((RegisterField) {MAX22216_DPM0_MASK, MAX22216_DPM0_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_DPM1_MASK                  0x00002000
#define MAX22216_DPM1_SHIFT                 13
#define MAX22216_DPM1_FIELD                 ((RegisterField) {MAX22216_DPM1_MASK, MAX22216_DPM1_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_DPM2_MASK                  0x00004000
#define MAX22216_DPM2_SHIFT                 14
#define MAX22216_DPM2_FIELD                 ((RegisterField) {MAX22216_DPM2_MASK, MAX22216_DPM2_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_DPM3_MASK                  0x00008000
#define MAX22216_DPM3_SHIFT                 15
#define MAX22216_DPM3_FIELD                 ((RegisterField) {MAX22216_DPM3_MASK, MAX22216_DPM3_SHIFT, MAX22216_FAULT0, false})
#define MAX22216_IND0_MASK                  0x00000001
#define MAX22216_IND0_SHIFT                 0
#define MAX22216_IND0_FIELD                 ((RegisterField) {MAX22216_IND0_MASK, MAX22216_IND0_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_IND1_MASK                  0x00000002
#define MAX22216_IND1_SHIFT                 1
#define MAX22216_IND1_FIELD                 ((RegisterField) {MAX22216_IND1_MASK, MAX22216_IND1_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_IND2_MASK                  0x00000004
#define MAX22216_IND2_SHIFT                 2
#define MAX22216_IND2_FIELD                 ((RegisterField) {MAX22216_IND2_MASK, MAX22216_IND2_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_IND3_MASK                  0x00000008
#define MAX22216_IND3_SHIFT                 3
#define MAX22216_IND3_FIELD                 ((RegisterField) {MAX22216_IND3_MASK, MAX22216_IND3_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_RES0_MASK                  0x00000080
#define MAX22216_RES0_SHIFT                 7
#define MAX22216_RES0_FIELD                 ((RegisterField) {MAX22216_RES0_MASK, MAX22216_RES0_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_RES1_MASK                  0x00000100
#define MAX22216_RES1_SHIFT                 8
#define MAX22216_RES1_FIELD                 ((RegisterField) {MAX22216_RES1_MASK, MAX22216_RES1_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_RES2_MASK                  0x00000200
#define MAX22216_RES2_SHIFT                 9
#define MAX22216_RES2_FIELD                 ((RegisterField) {MAX22216_RES2_MASK, MAX22216_RES2_SHIFT, MAX22216_FAULT1, false})
#define MAX22216_RES3_MASK                  0x00000400
#define MAX22216_RES3_SHIFT                 10
#define MAX22216_RES3_FIELD                 ((RegisterField) {MAX22216_RES3_MASK, MAX22216_RES3_SHIFT, MAX22216_FAULT1, false})

#endif
