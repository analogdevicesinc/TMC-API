/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2208_HW_ABSTRACTION
#define TMC2208_HW_ABSTRACTION


// Constants

#define TMC2208_MOTORS           1
#define TMC2208_REGISTER_COUNT   128 // Default register count
#define TMC2208_WRITE_BIT        0x80
#define TMC2208_ADDRESS_MASK     0x7F
#define TMC2208_MAX_VELOCITY     (int32_t)  2147483647
#define TMC2208_MAX_ACCELERATION (uint32_t)  4294967295uL


// Registers in TMC2208
// ===== TMC2208 & 2202 & TMC2208 & 2220 & 2225 "Donkey Kong" family register set =====

#define TMC2208_GCONF         0x00
#define TMC2208_GSTAT         0x01
#define TMC2208_IFCNT         0x02
#define TMC2208_SLAVECONF     0x03
#define TMC2208_OTP_PROG      0x04
#define TMC2208_OTP_READ      0x05
#define TMC2208_IOIN          0x06
#define TMC2208_FACTORY_CONF  0x07
#define TMC2208_IHOLD_IRUN    0x10
#define TMC2208_TPOWERDOWN    0x11
#define TMC2208_TSTEP         0x12
#define TMC2208_TPWMTHRS      0x13
#define TMC2208_VACTUAL       0x22
#define TMC2208_MSCNT         0x6A
#define TMC2208_MSCURACT      0x6B
#define TMC2208_CHOPCONF      0x6C
#define TMC2208_DRVSTATUS     0x6F
#define TMC2208_PWMCONF       0x70
#define TMC2208_PWM_SCALE     0x71
#define TMC2208_PWM_AUTO      0x72


// Register fields in TMC2208

#define TMC2208_I_SCALE_ANALOG_MASK          0x00000001
#define TMC2208_I_SCALE_ANALOG_SHIFT         0
#define TMC2208_I_SCALE_ANALOG_FIELD         ((RegisterField) {TMC2208_I_SCALE_ANALOG_MASK, TMC2208_I_SCALE_ANALOG_SHIFT, TMC2208_GCONF, false})
#define TMC2208_INTERNAL_RSENSE_MASK         0x00000002
#define TMC2208_INTERNAL_RSENSE_SHIFT        1
#define TMC2208_INTERNAL_RSENSE_FIELD        ((RegisterField) {TMC2208_INTERNAL_RSENSE_MASK, TMC2208_INTERNAL_RSENSE_SHIFT, TMC2208_GCONF, false})
#define TMC2208_EN_SPREADCYCLE_MASK          0x00000004
#define TMC2208_EN_SPREADCYCLE_SHIFT         2
#define TMC2208_EN_SPREADCYCLE_FIELD         ((RegisterField) {TMC2208_EN_SPREADCYCLE_MASK, TMC2208_EN_SPREADCYCLE_SHIFT, TMC2208_GCONF, false})
#define TMC2208_SHAFT_MASK                   0x00000008
#define TMC2208_SHAFT_SHIFT                  3
#define TMC2208_SHAFT_FIELD                  ((RegisterField) {TMC2208_SHAFT_MASK, TMC2208_SHAFT_SHIFT, TMC2208_GCONF, false})
#define TMC2208_INDEX_OTPW_MASK              0x00000010
#define TMC2208_INDEX_OTPW_SHIFT             4
#define TMC2208_INDEX_OTPW_FIELD             ((RegisterField) {TMC2208_INDEX_OTPW_MASK, TMC2208_INDEX_OTPW_SHIFT, TMC2208_GCONF, false})
#define TMC2208_INDEX_STEP_MASK              0x00000020
#define TMC2208_INDEX_STEP_SHIFT             5
#define TMC2208_INDEX_STEP_FIELD             ((RegisterField) {TMC2208_INDEX_STEP_MASK, TMC2208_INDEX_STEP_SHIFT, TMC2208_GCONF, false})
#define TMC2208_PDN_DISABLE_MASK             0x00000040
#define TMC2208_PDN_DISABLE_SHIFT            6
#define TMC2208_PDN_DISABLE_FIELD            ((RegisterField) {TMC2208_PDN_DISABLE_MASK, TMC2208_PDN_DISABLE_SHIFT, TMC2208_GCONF, false})
#define TMC2208_MSTEP_REG_SELECT_MASK        0x00000080
#define TMC2208_MSTEP_REG_SELECT_SHIFT       7
#define TMC2208_MSTEP_REG_SELECT_FIELD       ((RegisterField) {TMC2208_MSTEP_REG_SELECT_MASK, TMC2208_MSTEP_REG_SELECT_SHIFT, TMC2208_GCONF, false})
#define TMC2208_MULTISTEP_FILT_MASK          0x00000100
#define TMC2208_MULTISTEP_FILT_SHIFT         8
#define TMC2208_MULTISTEP_FILT_FIELD         ((RegisterField) {TMC2208_MULTISTEP_FILT_MASK, TMC2208_MULTISTEP_FILT_SHIFT, TMC2208_GCONF, false})
#define TMC2208_TEST_MODE_MASK               0x00000200
#define TMC2208_TEST_MODE_SHIFT              9
#define TMC2208_TEST_MODE_FIELD              ((RegisterField) {TMC2208_TEST_MODE_MASK, TMC2208_TEST_MODE_SHIFT, TMC2208_GCONF, false})
#define TMC2208_RESET_MASK                   0x00000001
#define TMC2208_RESET_SHIFT                  0
#define TMC2208_RESET_FIELD                  ((RegisterField) {TMC2208_RESET_MASK, TMC2208_RESET_SHIFT, TMC2208_GSTAT, false})
#define TMC2208_DRV_ERR_MASK                 0x00000002
#define TMC2208_DRV_ERR_SHIFT                1
#define TMC2208_DRV_ERR_FIELD                ((RegisterField) {TMC2208_DRV_ERR_MASK, TMC2208_DRV_ERR_SHIFT, TMC2208_GSTAT, false})
#define TMC2208_UV_CP_MASK                   0x00000004
#define TMC2208_UV_CP_SHIFT                  2
#define TMC2208_UV_CP_FIELD                  ((RegisterField) {TMC2208_UV_CP_MASK, TMC2208_UV_CP_SHIFT, TMC2208_GSTAT, false})
#define TMC2208_IFCNT_MASK                   0x000000FF
#define TMC2208_IFCNT_SHIFT                  0
#define TMC2208_IFCNT_FIELD                  ((RegisterField) {TMC2208_IFCNT_MASK, TMC2208_IFCNT_SHIFT, TMC2208_IFCNT, false})
#define TMC2208_SLAVECONF_MASK               0x00000F00
#define TMC2208_SLAVECONF_SHIFT              8
#define TMC2208_SLAVECONF_FIELD              ((RegisterField) {TMC2208_SLAVECONF_MASK, TMC2208_SLAVECONF_SHIFT, TMC2208_SLAVECONF, false})
#define TMC2208_OTPBIT_MASK                  0x00000007
#define TMC2208_OTPBIT_SHIFT                 0
#define TMC2208_OTPBIT_FIELD                 ((RegisterField) {TMC2208_OTPBIT_MASK, TMC2208_OTPBIT_SHIFT, TMC2208_OTP_PROG, false})
#define TMC2208_OTPBYTE_MASK                 0x00000030
#define TMC2208_OTPBYTE_SHIFT                4
#define TMC2208_OTPBYTE_FIELD                ((RegisterField) {TMC2208_OTPBYTE_MASK, TMC2208_OTPBYTE_SHIFT, TMC2208_OTP_PROG, false})
#define TMC2208_OTPMAGIC_MASK                0x0000FF00
#define TMC2208_OTPMAGIC_SHIFT               8
#define TMC2208_OTPMAGIC_FIELD               ((RegisterField) {TMC2208_OTPMAGIC_MASK, TMC2208_OTPMAGIC_SHIFT, TMC2208_OTP_PROG, false})
#define TMC2208_OTP0_BYTE_0_READ_DATA_MASK   0x000000FF
#define TMC2208_OTP0_BYTE_0_READ_DATA_SHIFT  0
#define TMC2208_OTP0_BYTE_0_READ_DATA_FIELD  ((RegisterField) {TMC2208_OTP0_BYTE_0_READ_DATA_MASK, TMC2208_OTP0_BYTE_0_READ_DATA_SHIFT, TMC2208_OTP_READ, false})
#define TMC2208_OTP1_BYTE_1_READ_DATA_MASK   0x0000FF00
#define TMC2208_OTP1_BYTE_1_READ_DATA_SHIFT  8
#define TMC2208_OTP1_BYTE_1_READ_DATA_FIELD  ((RegisterField) {TMC2208_OTP1_BYTE_1_READ_DATA_MASK, TMC2208_OTP1_BYTE_1_READ_DATA_SHIFT, TMC2208_OTP_READ, false})
#define TMC2208_OTP2_BYTE_2_READ_DATA_MASK   0x00FF0000
#define TMC2208_OTP2_BYTE_2_READ_DATA_SHIFT  16
#define TMC2208_OTP2_BYTE_2_READ_DATA_FIELD  ((RegisterField) {TMC2208_OTP2_BYTE_2_READ_DATA_MASK, TMC2208_OTP2_BYTE_2_READ_DATA_SHIFT, TMC2208_OTP_READ, false})
#define TMC2208_ENN_MASK                     0x00000001
#define TMC2208_ENN_SHIFT                    0
#define TMC2208_ENN_FIELD                    ((RegisterField) {TMC2208_ENN_MASK, TMC2208_ENN_SHIFT, TMC2208_IOIN, false})
#define TMC2208_MS1_MASK                     0x00000004
#define TMC2208_MS1_SHIFT                    2
#define TMC2208_MS1_FIELD                    ((RegisterField) {TMC2208_MS1_MASK, TMC2208_MS1_SHIFT, TMC2208_IOIN, false})
#define TMC2208_MS2_MASK                     0x00000008
#define TMC2208_MS2_SHIFT                    3
#define TMC2208_MS2_FIELD                    ((RegisterField) {TMC2208_MS2_MASK, TMC2208_MS2_SHIFT, TMC2208_IOIN, false})
#define TMC2208_DIAG_MASK                    0x00000010
#define TMC2208_DIAG_SHIFT                   4
#define TMC2208_DIAG_FIELD                   ((RegisterField) {TMC2208_DIAG_MASK, TMC2208_DIAG_SHIFT, TMC2208_IOIN, false})
#define TMC2208_PDN_UART_MASK                0x00000040
#define TMC2208_PDN_UART_SHIFT               6
#define TMC2208_PDN_UART_FIELD               ((RegisterField) {TMC2208_PDN_UART_MASK, TMC2208_PDN_UART_SHIFT, TMC2208_IOIN, false})
#define TMC2208_STEP_MASK                    0x00000080
#define TMC2208_STEP_SHIFT                   7
#define TMC2208_STEP_FIELD                   ((RegisterField) {TMC2208_STEP_MASK, TMC2208_STEP_SHIFT, TMC2208_IOIN, false})
#define TMC2208_SEL_A_MASK                   0x00000100
#define TMC2208_SEL_A_SHIFT                  8
#define TMC2208_SEL_A_FIELD                  ((RegisterField) {TMC2208_SEL_A_MASK, TMC2208_SEL_A_SHIFT, TMC2208_IOIN, false})
#define TMC2208_DIR_MASK                     0x00000200
#define TMC2208_DIR_SHIFT                    9
#define TMC2208_DIR_FIELD                    ((RegisterField) {TMC2208_DIR_MASK, TMC2208_DIR_SHIFT, TMC2208_IOIN, false})
#define TMC2208_VERSION_MASK                 0xFF000000
#define TMC2208_VERSION_SHIFT                24
#define TMC2208_VERSION_FIELD                ((RegisterField) {TMC2208_VERSION_MASK, TMC2208_VERSION_SHIFT, TMC2208_IOIN, false})
#define TMC2208_FCLKTRIM_MASK                0x0000001F
#define TMC2208_FCLKTRIM_SHIFT               0
#define TMC2208_FCLKTRIM_FIELD               ((RegisterField) {TMC2208_FCLKTRIM_MASK, TMC2208_FCLKTRIM_SHIFT, TMC2208_FACTORY_CONF, false})
#define TMC2208_OTTRIM_MASK                  0x00000300
#define TMC2208_OTTRIM_SHIFT                 8
#define TMC2208_OTTRIM_FIELD                 ((RegisterField) {TMC2208_OTTRIM_MASK, TMC2208_OTTRIM_SHIFT, TMC2208_FACTORY_CONF, false})
#define TMC2208_IHOLD_MASK                   0x0000001F
#define TMC2208_IHOLD_SHIFT                  0
#define TMC2208_IHOLD_FIELD                  ((RegisterField) {TMC2208_IHOLD_MASK, TMC2208_IHOLD_SHIFT, TMC2208_IHOLD_IRUN, false})
#define TMC2208_IRUN_MASK                    0x00001F00
#define TMC2208_IRUN_SHIFT                   8
#define TMC2208_IRUN_FIELD                   ((RegisterField) {TMC2208_IRUN_MASK, TMC2208_IRUN_SHIFT, TMC2208_IHOLD_IRUN, false})
#define TMC2208_IHOLDDELAY_MASK              0x000F0000
#define TMC2208_IHOLDDELAY_SHIFT             16
#define TMC2208_IHOLDDELAY_FIELD             ((RegisterField) {TMC2208_IHOLDDELAY_MASK, TMC2208_IHOLDDELAY_SHIFT, TMC2208_IHOLD_IRUN, false})
#define TMC2208_TPOWERDOWN_MASK              0x000000FF
#define TMC2208_TPOWERDOWN_SHIFT             0
#define TMC2208_TPOWERDOWN_FIELD             ((RegisterField) {TMC2208_TPOWERDOWN_MASK, TMC2208_TPOWERDOWN_SHIFT, TMC2208_TPOWERDOWN, false})
#define TMC2208_TSTEP_MASK                   0x000FFFFF
#define TMC2208_TSTEP_SHIFT                  0
#define TMC2208_TSTEP_FIELD                  ((RegisterField) {TMC2208_TSTEP_MASK, TMC2208_TSTEP_SHIFT, TMC2208_TSTEP, false})
#define TMC2208_TPWMTHRS_MASK                0x000FFFFF
#define TMC2208_TPWMTHRS_SHIFT               0
#define TMC2208_TPWMTHRS_FIELD               ((RegisterField) {TMC2208_TPWMTHRS_MASK, TMC2208_TPWMTHRS_SHIFT, TMC2208_TPWMTHRS, false})
#define TMC2208_VACTUAL_MASK                 0x00FFFFFF
#define TMC2208_VACTUAL_SHIFT                0
#define TMC2208_VACTUAL_FIELD                ((RegisterField) {TMC2208_VACTUAL_MASK, TMC2208_VACTUAL_SHIFT, TMC2208_VACTUAL, true})
#define TMC2208_MSCNT_MASK                   0x000003FF
#define TMC2208_MSCNT_SHIFT                  0
#define TMC2208_MSCNT_FIELD                  ((RegisterField) {TMC2208_MSCNT_MASK, TMC2208_MSCNT_SHIFT, TMC2208_MSCNT, false})
#define TMC2208_CUR_A_MASK                   0x000001FF
#define TMC2208_CUR_A_SHIFT                  0
#define TMC2208_CUR_A_FIELD                  ((RegisterField) {TMC2208_CUR_A_MASK, TMC2208_CUR_A_SHIFT, TMC2208_MSCURACT, true})
#define TMC2208_CUR_B_MASK                   0x01FF0000
#define TMC2208_CUR_B_SHIFT                  16
#define TMC2208_CUR_B_FIELD                  ((RegisterField) {TMC2208_CUR_B_MASK, TMC2208_CUR_B_SHIFT, TMC2208_MSCURACT, true})
#define TMC2208_TOFF_MASK                    0x0000000F
#define TMC2208_TOFF_SHIFT                   0
#define TMC2208_TOFF_FIELD                   ((RegisterField) {TMC2208_TOFF_MASK, TMC2208_TOFF_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_HSTRT_MASK                   0x00000070
#define TMC2208_HSTRT_SHIFT                  4
#define TMC2208_HSTRT_FIELD                  ((RegisterField) {TMC2208_HSTRT_MASK, TMC2208_HSTRT_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_HEND_MASK                    0x00000780
#define TMC2208_HEND_SHIFT                   7
#define TMC2208_HEND_FIELD                   ((RegisterField) {TMC2208_HEND_MASK, TMC2208_HEND_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_TBL_MASK                     0x00018000
#define TMC2208_TBL_SHIFT                    15
#define TMC2208_TBL_FIELD                    ((RegisterField) {TMC2208_TBL_MASK, TMC2208_TBL_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_VSENSE_MASK                  0x00020000
#define TMC2208_VSENSE_SHIFT                 17
#define TMC2208_VSENSE_FIELD                 ((RegisterField) {TMC2208_VSENSE_MASK, TMC2208_VSENSE_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_MRES_MASK                    0x0F000000
#define TMC2208_MRES_SHIFT                   24
#define TMC2208_MRES_FIELD                   ((RegisterField) {TMC2208_MRES_MASK, TMC2208_MRES_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_INTPOL_MASK                  0x10000000
#define TMC2208_INTPOL_SHIFT                 28
#define TMC2208_INTPOL_FIELD                 ((RegisterField) {TMC2208_INTPOL_MASK, TMC2208_INTPOL_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_DEDGE_MASK                   0x20000000
#define TMC2208_DEDGE_SHIFT                  29
#define TMC2208_DEDGE_FIELD                  ((RegisterField) {TMC2208_DEDGE_MASK, TMC2208_DEDGE_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_DISS2G_MASK                  0x40000000
#define TMC2208_DISS2G_SHIFT                 30
#define TMC2208_DISS2G_FIELD                 ((RegisterField) {TMC2208_DISS2G_MASK, TMC2208_DISS2G_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_DISS2VS_MASK                 0x80000000
#define TMC2208_DISS2VS_SHIFT                31
#define TMC2208_DISS2VS_FIELD                ((RegisterField) {TMC2208_DISS2VS_MASK, TMC2208_DISS2VS_SHIFT, TMC2208_CHOPCONF, false})
#define TMC2208_OTPW_MASK                    0x00000001
#define TMC2208_OTPW_SHIFT                   0
#define TMC2208_OTPW_FIELD                   ((RegisterField) {TMC2208_OTPW_MASK, TMC2208_OTPW_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_OT_MASK                      0x00000002
#define TMC2208_OT_SHIFT                     1
#define TMC2208_OT_FIELD                     ((RegisterField) {TMC2208_OT_MASK, TMC2208_OT_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_S2GA_MASK                    0x00000004
#define TMC2208_S2GA_SHIFT                   2
#define TMC2208_S2GA_FIELD                   ((RegisterField) {TMC2208_S2GA_MASK, TMC2208_S2GA_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_S2GB_MASK                    0x00000008
#define TMC2208_S2GB_SHIFT                   3
#define TMC2208_S2GB_FIELD                   ((RegisterField) {TMC2208_S2GB_MASK, TMC2208_S2GB_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_S2VSA_MASK                   0x00000010
#define TMC2208_S2VSA_SHIFT                  4
#define TMC2208_S2VSA_FIELD                  ((RegisterField) {TMC2208_S2VSA_MASK, TMC2208_S2VSA_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_S2VSB_MASK                   0x00000020
#define TMC2208_S2VSB_SHIFT                  5
#define TMC2208_S2VSB_FIELD                  ((RegisterField) {TMC2208_S2VSB_MASK, TMC2208_S2VSB_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_OLA_MASK                     0x00000040
#define TMC2208_OLA_SHIFT                    6
#define TMC2208_OLA_FIELD                    ((RegisterField) {TMC2208_OLA_MASK, TMC2208_OLA_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_OLB_MASK                     0x00000080
#define TMC2208_OLB_SHIFT                    7
#define TMC2208_OLB_FIELD                    ((RegisterField) {TMC2208_OLB_MASK, TMC2208_OLB_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_T120_MASK                    0x00000100
#define TMC2208_T120_SHIFT                   8
#define TMC2208_T120_FIELD                   ((RegisterField) {TMC2208_T120_MASK, TMC2208_T120_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_T143_MASK                    0x00000200
#define TMC2208_T143_SHIFT                   9
#define TMC2208_T143_FIELD                   ((RegisterField) {TMC2208_T143_MASK, TMC2208_T143_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_T150_MASK                    0x00000400
#define TMC2208_T150_SHIFT                   10
#define TMC2208_T150_FIELD                   ((RegisterField) {TMC2208_T150_MASK, TMC2208_T150_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_T157_MASK                    0x00000800
#define TMC2208_T157_SHIFT                   11
#define TMC2208_T157_FIELD                   ((RegisterField) {TMC2208_T157_MASK, TMC2208_T157_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_CS_ACTUAL_MASK               0x001F0000
#define TMC2208_CS_ACTUAL_SHIFT              16
#define TMC2208_CS_ACTUAL_FIELD              ((RegisterField) {TMC2208_CS_ACTUAL_MASK, TMC2208_CS_ACTUAL_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_STEALTH_MASK                 0x40000000
#define TMC2208_STEALTH_SHIFT                30
#define TMC2208_STEALTH_FIELD                ((RegisterField) {TMC2208_STEALTH_MASK, TMC2208_STEALTH_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_STST_MASK                    0x80000000
#define TMC2208_STST_SHIFT                   31
#define TMC2208_STST_FIELD                   ((RegisterField) {TMC2208_STST_MASK, TMC2208_STST_SHIFT, TMC2208_DRV_STATUS, false})
#define TMC2208_PWM_OFS_MASK                 0x000000FF
#define TMC2208_PWM_OFS_SHIFT                0
#define TMC2208_PWM_OFS_FIELD                ((RegisterField) {TMC2208_PWM_OFS_MASK, TMC2208_PWM_OFS_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_GRAD_MASK                0x0000FF00
#define TMC2208_PWM_GRAD_SHIFT               8
#define TMC2208_PWM_GRAD_FIELD               ((RegisterField) {TMC2208_PWM_GRAD_MASK, TMC2208_PWM_GRAD_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_FREQ_MASK                0x00030000
#define TMC2208_PWM_FREQ_SHIFT               16
#define TMC2208_PWM_FREQ_FIELD               ((RegisterField) {TMC2208_PWM_FREQ_MASK, TMC2208_PWM_FREQ_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_AUTOSCALE_MASK           0x00040000
#define TMC2208_PWM_AUTOSCALE_SHIFT          18
#define TMC2208_PWM_AUTOSCALE_FIELD          ((RegisterField) {TMC2208_PWM_AUTOSCALE_MASK, TMC2208_PWM_AUTOSCALE_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_AUTOGRAD_MASK            0x00080000
#define TMC2208_PWM_AUTOGRAD_SHIFT           19
#define TMC2208_PWM_AUTOGRAD_FIELD           ((RegisterField) {TMC2208_PWM_AUTOGRAD_MASK, TMC2208_PWM_AUTOGRAD_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_FREEWHEEL_MASK               0x00300000
#define TMC2208_FREEWHEEL_SHIFT              20
#define TMC2208_FREEWHEEL_FIELD              ((RegisterField) {TMC2208_FREEWHEEL_MASK, TMC2208_FREEWHEEL_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_REG_MASK                 0x0F000000
#define TMC2208_PWM_REG_SHIFT                24
#define TMC2208_PWM_REG_FIELD                ((RegisterField) {TMC2208_PWM_REG_MASK, TMC2208_PWM_REG_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_LIM_MASK                 0xF0000000
#define TMC2208_PWM_LIM_SHIFT                28
#define TMC2208_PWM_LIM_FIELD                ((RegisterField) {TMC2208_PWM_LIM_MASK, TMC2208_PWM_LIM_SHIFT, TMC2208_PWMCONF, false})
#define TMC2208_PWM_SCALE_SUM_MASK           0x000000FF
#define TMC2208_PWM_SCALE_SUM_SHIFT          0
#define TMC2208_PWM_SCALE_SUM_FIELD          ((RegisterField) {TMC2208_PWM_SCALE_SUM_MASK, TMC2208_PWM_SCALE_SUM_SHIFT, TMC2208_PWM_SCALE, false})
#define TMC2208_PWM_SCALE_AUTO_MASK          0x01FF0000
#define TMC2208_PWM_SCALE_AUTO_SHIFT         16
#define TMC2208_PWM_SCALE_AUTO_FIELD         ((RegisterField) {TMC2208_PWM_SCALE_AUTO_MASK, TMC2208_PWM_SCALE_AUTO_SHIFT, TMC2208_PWM_SCALE, true})
#define TMC2208_PWM_OFS_AUTO_MASK            0x000000FF
#define TMC2208_PWM_OFS_AUTO_SHIFT           0
#define TMC2208_PWM_OFS_AUTO_FIELD           ((RegisterField) {TMC2208_PWM_OFS_AUTO_MASK, TMC2208_PWM_OFS_AUTO_SHIFT, TMC2208_PWM_AUTO, false})
#define TMC2208_PWM_GRAD_AUTO_MASK           0x00FF0000
#define TMC2208_PWM_GRAD_AUTO_SHIFT          16
#define TMC2208_PWM_GRAD_AUTO_FIELD          ((RegisterField) {TMC2208_PWM_GRAD_AUTO_MASK, TMC2208_PWM_GRAD_AUTO_SHIFT, TMC2208_PWM_AUTO, false})

#endif
