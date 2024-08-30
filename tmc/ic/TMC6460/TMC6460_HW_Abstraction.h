/*******************************************************************************
* Copyright © 2026 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC_IC_TMC6460_HW_ABSTRACTION_H_
#define TMC_IC_TMC6460_HW_ABSTRACTION_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t mask;
    uint8_t  shift;
    uint16_t addr;
    bool     isSigned;
} TMC6460RegisterField;


// --- TMC6460 Registers -------------------------------------------------------
// CHIP registers
#define TMC6460_CHIP_ID                               0x0000
#define TMC6460_CHIP_VARIANT                          0x0001
#define TMC6460_CHIP_REVISION                         0x0002
#define TMC6460_CHIP_INPUTS_RAW                       0x0004
#define TMC6460_CHIP_OUTPUTS_RAW                      0x0005
#define TMC6460_CHIP_IO_MATRIX                        0x0006
#define TMC6460_CHIP_IO_PU_PD                         0x0007
#define TMC6460_CHIP_IO_CONFIG                        0x0008
#define TMC6460_CHIP_STATUS_FLAGS                     0x0009
#define TMC6460_CHIP_EVENTS                           0x000A
#define TMC6460_CHIP_FAULTN_INT_MASK                  0x000B
#define TMC6460_CHIP_SPI_STATUS_MASK                  0x000C

// CLK_CTRL registers
#define TMC6460_CLK_CTRL_CONFIG                       0x0040
#define TMC6460_CLK_CTRL_STATUS                       0x0041

// ADC registers
#define TMC6460_ADC_CONFIG                            0x0080
#define TMC6460_ADC_ADC_VERSION                       0x0081
#define TMC6460_ADC_I2_I1_RAW                         0x0082
#define TMC6460_ADC_VM_I3_RAW                         0x0083
#define TMC6460_ADC_TEMP_RAW                          0x0084
#define TMC6460_ADC_AIN_V_AIN_U_RAW                   0x0085
#define TMC6460_ADC_AIN_AIN_W_RAW                     0x0086
#define TMC6460_ADC_STATUS                            0x008A
#define TMC6460_ADC_I123                              0x008C

// MCC_ADC registers
#define TMC6460_MCC_ADC_I_GEN_CONFIG                  0x00C0
#define TMC6460_MCC_ADC_IW_IU                         0x00C1
#define TMC6460_MCC_ADC_IV                            0x00C2
#define TMC6460_MCC_ADC_CSA_GAIN                      0x00C3
#define TMC6460_MCC_ADC_EVENTS                        0x00C4
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X         0x00C5
#define TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X             0x00C6
#define TMC6460_MCC_ADC_TEMP_LIMITS                   0x00C7
#define TMC6460_MCC_ADC_CURRENT_OVERLOAD              0x00C8

// MCC_CONFIG registers
#define TMC6460_MCC_CONFIG_MOTOR_MOTION               0x0100
#define TMC6460_MCC_CONFIG_GDRV                       0x0101
#define TMC6460_MCC_CONFIG_PWM                        0x0102
#define TMC6460_MCC_CONFIG_PWM_PERIOD                 0x0103
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS       0x0104
#define TMC6460_MCC_CONFIG_MCC_STATUS                 0x0105
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG       0x0106
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG 0x0107
#define TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC     0x0108
#define TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD         0x0109

// FOC registers
#define TMC6460_FOC_PID_CONFIG                        0x0140
#define TMC6460_FOC_PID_U_S_MAX                       0x0141
#define TMC6460_FOC_PID_FLUX_COEFF                    0x0142
#define TMC6460_FOC_PID_TORQUE_COEFF                  0x0143
#define TMC6460_FOC_PID_FIELDWEAK_COEFF               0x0144
#define TMC6460_FOC_PID_VELOCITY_COEFF                0x0145
#define TMC6460_FOC_PID_POSITION_COEFF                0x0146
#define TMC6460_FOC_PID_POSITION_TOLERANCE            0x0147
#define TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY      0x0148
#define TMC6460_FOC_PID_UQ_UD_LIMITS                  0x0149
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS            0x014A
#define TMC6460_FOC_PID_VELOCITY_LIMIT                0x014B
#define TMC6460_FOC_PID_POSITION_LIMIT_LOW            0x014C
#define TMC6460_FOC_PID_POSITION_LIMIT_HIGH           0x014D
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET            0x014E
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET            0x014F
#define TMC6460_FOC_PID_VELOCITY_TARGET               0x0150
#define TMC6460_FOC_PID_VELOCITY_OFFSET               0x0151
#define TMC6460_FOC_PID_POSITION_TARGET               0x0152
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL            0x0153
#define TMC6460_FOC_PID_VELOCITY_ACTUAL               0x0154
#define TMC6460_FOC_PID_POSITION_ACTUAL               0x0155
#define TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET        0x0156
#define TMC6460_FOC_PID_TORQUE_ERROR                  0x0157
#define TMC6460_FOC_PID_FLUX_ERROR                    0x0158
#define TMC6460_FOC_PID_VELOCITY_ERROR                0x0159
#define TMC6460_FOC_PID_VELOCITY_ERROR_MAX            0x015A
#define TMC6460_FOC_PID_POSITION_ERROR                0x015B
#define TMC6460_FOC_PID_POSITION_ERROR_MAX            0x015C
#define TMC6460_FOC_PID_TORQUE_INTEGRATOR             0x015D
#define TMC6460_FOC_PID_FLUX_INTEGRATOR               0x015E
#define TMC6460_FOC_PID_VELOCITY_INTEGRATOR           0x015F
#define TMC6460_FOC_PID_POSITION_INTEGRATOR           0x0160
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET          0x0161
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET             0x0162
#define TMC6460_FOC_PIDIN_POSITION_TARGET             0x0163
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED  0x0164
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED     0x0165
#define TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED     0x0166
#define TMC6460_FOC_FOC_IBETA_IALPHA                  0x0167
#define TMC6460_FOC_FOC_IQ_ID                         0x0168
#define TMC6460_FOC_FOC_UQ_UD                         0x0169
#define TMC6460_FOC_FOC_UQ_UD_LIMITED                 0x016A
#define TMC6460_FOC_FOC_UBETA_UALPHA                  0x016B
#define TMC6460_FOC_FOC_UW_UU                         0x016C
#define TMC6460_FOC_FOC_UV                            0x016D
#define TMC6460_FOC_PWM_V_U                           0x016E
#define TMC6460_FOC_PWM_W                             0x016F
#define TMC6460_FOC_FOC_STATUS                        0x0170
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL             0x0171
#define TMC6460_FOC_P_MOTOR                           0x0172
#define TMC6460_FOC_I_T_ACTUAL                        0x0173
#define TMC6460_FOC_PRBS_AMPLITUDE                    0x0174
#define TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO          0x0175

// BIQUAD registers
#define TMC6460_BIQUAD_BIQUAD_EN                      0x0180
#define TMC6460_BIQUAD_VELOCITY_A1                    0x0181
#define TMC6460_BIQUAD_VELOCITY_A2                    0x0182
#define TMC6460_BIQUAD_VELOCITY_B0                    0x0183
#define TMC6460_BIQUAD_VELOCITY_B1                    0x0184
#define TMC6460_BIQUAD_VELOCITY_B2                    0x0185
#define TMC6460_BIQUAD_TORQUE_A1                      0x0186
#define TMC6460_BIQUAD_TORQUE_A2                      0x0187
#define TMC6460_BIQUAD_TORQUE_B0                      0x0188
#define TMC6460_BIQUAD_TORQUE_B1                      0x0189
#define TMC6460_BIQUAD_TORQUE_B2                      0x018A

// RAMPER registers
#define TMC6460_RAMPER_TIME_CONFIG                    0x01C0
#define TMC6460_RAMPER_SWITCH_MODE                    0x01C1
#define TMC6460_RAMPER_PHI_E                          0x01C3
#define TMC6460_RAMPER_A1                             0x01C4
#define TMC6460_RAMPER_A2                             0x01C5
#define TMC6460_RAMPER_A_MAX                          0x01C6
#define TMC6460_RAMPER_D1                             0x01C7
#define TMC6460_RAMPER_D2                             0x01C8
#define TMC6460_RAMPER_D_MAX                          0x01C9
#define TMC6460_RAMPER_V_START                        0x01CA
#define TMC6460_RAMPER_V1                             0x01CB
#define TMC6460_RAMPER_V2                             0x01CC
#define TMC6460_RAMPER_V_STOP                         0x01CD
#define TMC6460_RAMPER_V_MAX                          0x01CE
#define TMC6460_RAMPER_ACCELERATION                   0x01CF
#define TMC6460_RAMPER_V_ACTUAL                       0x01D0
#define TMC6460_RAMPER_POSITION                       0x01D1
#define TMC6460_RAMPER_POSITION_LATCH                 0x01D2
#define TMC6460_RAMPER_POSITION_ACTUAL_LATCH          0x01D3
#define TMC6460_RAMPER_STATUS                         0x01D4
#define TMC6460_RAMPER_EVENTS                         0x01D5

// EXT_CTRL registers
#define TMC6460_EXT_CTRL_VOLTAGE                      0x0200
#define TMC6460_EXT_CTRL_PWM_V_U                      0x0202
#define TMC6460_EXT_CTRL_PWM_W                        0x0203

// FEEDBACK registers
#define TMC6460_FEEDBACK_CONF_CH_A                    0x0240
#define TMC6460_FEEDBACK_CONF_CH_B                    0x0241
#define TMC6460_FEEDBACK_PHI_E_OFFSET                 0x0242
#define TMC6460_FEEDBACK_LUT                          0x0243
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF            0x0244
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF            0x0245
#define TMC6460_FEEDBACK_VELOCITY_PER_FILTER          0x0246
#define TMC6460_FEEDBACK_PHI_CONVERTED                0x0247
#define TMC6460_FEEDBACK_CH_A                         0x0248
#define TMC6460_FEEDBACK_CH_B                         0x0249
#define TMC6460_FEEDBACK_VELOCITY_FRQ                 0x024A
#define TMC6460_FEEDBACK_VELOCITY_PER                 0x024B
#define TMC6460_FEEDBACK_LUT_WDATA                    0x024C
#define TMC6460_FEEDBACK_PHI_EXT_A                    0x024D
#define TMC6460_FEEDBACK_PHI_EXT_B                    0x024E
#define TMC6460_FEEDBACK_VELOCITY_EXT                 0x024F
#define TMC6460_FEEDBACK_OUTPUT_CONF                  0x0250
#define TMC6460_FEEDBACK_PHI_E                        0x0251
#define TMC6460_FEEDBACK_PHI_DIFF_LIMIT               0x0252

// ABN registers
#define TMC6460_ABN_CONFIG                            0x0280
#define TMC6460_ABN_COUNT                             0x0281
#define TMC6460_ABN_COUNT_N_CAPTURE                   0x0282
#define TMC6460_ABN_COUNT_N_WRITE                     0x0283
#define TMC6460_ABN_EVENTS                            0x0284

// ABN2 registers
#define TMC6460_ABN2_CONFIG                           0x02C0
#define TMC6460_ABN2_COUNT                            0x02C1
#define TMC6460_ABN2_COUNT_N_CAPTURE                  0x02C2
#define TMC6460_ABN2_COUNT_N_WRITE                    0x02C3
#define TMC6460_ABN2_EVENTS                           0x02C4

// HALL registers
#define TMC6460_HALL_MAP_CONFIG                       0x0300
#define TMC6460_HALL_DIG_COUNT                        0x0301
#define TMC6460_HALL_ANA_CONFIG                       0x0302
#define TMC6460_HALL_ANA_UX_CONFIG                    0x0303
#define TMC6460_HALL_ANA_VN_CONFIG                    0x0304
#define TMC6460_HALL_ANA_WY_CONFIG                    0x0305
#define TMC6460_HALL_ANA_UX_OUT                       0x0306
#define TMC6460_HALL_ANA_VN_OUT                       0x0307
#define TMC6460_HALL_ANA_WY_OUT                       0x0308
#define TMC6460_HALL_ANA_OUT                          0x0309
#define TMC6460_HALL_DIG_EVENTS                       0x030A

// UART registers
#define TMC6460_UART_CONTROL                          0x0340
#define TMC6460_UART_TIMEOUT                          0x0341
#define TMC6460_UART_STATUS                           0x0342
#define TMC6460_UART_EVENTS                           0x0343
#define TMC6460_UART_RTMI_CH_0                        0x0344
#define TMC6460_UART_RTMI_CH_1                        0x0345
#define TMC6460_UART_RTMI_CH_2                        0x0346
#define TMC6460_UART_RTMI_CH_3                        0x0347
#define TMC6460_UART_RTMI_CH_4                        0x0348
#define TMC6460_UART_RTMI_CH_5                        0x0349
#define TMC6460_UART_RTMI_CH_6                        0x034A
#define TMC6460_UART_RTMI_CH_7                        0x034B

// IO_CONTROLLER registers
#define TMC6460_IO_CONTROLLER_CONTROL                 0x0380
#define TMC6460_IO_CONTROLLER_COMMAND                 0x0381
#define TMC6460_IO_CONTROLLER_RESPONSE_0              0x0382
#define TMC6460_IO_CONTROLLER_RESPONSE_1              0x0383
#define TMC6460_IO_CONTROLLER_RESPONSE_2              0x0384
#define TMC6460_IO_CONTROLLER_RESPONSE_3              0x0385

// --- TMC6460 Fields ----------------------------------------------------------
// CHIP.ID fields
#define TMC6460_CHIP_ID_MASK                                                0xFFFFFFFF
#define TMC6460_CHIP_ID_SHIFT                                               0
#define TMC6460_CHIP_ID_FIELD                                               ((TMC6460RegisterField) {.mask=TMC6460_CHIP_ID_MASK, .shift=TMC6460_CHIP_ID_SHIFT, .addr=TMC6460_CHIP_ID, .isSigned=false })

// CHIP.VARIANT fields
#define TMC6460_CHIP_VARIANT_MASK                                           0xFFFFFFFF
#define TMC6460_CHIP_VARIANT_SHIFT                                          0
#define TMC6460_CHIP_VARIANT_FIELD                                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_VARIANT_MASK, .shift=TMC6460_CHIP_VARIANT_SHIFT, .addr=TMC6460_CHIP_VARIANT, .isSigned=false })

// CHIP.REVISION fields
#define TMC6460_CHIP_REVISION_MASK                                          0x7FFFFFFF
#define TMC6460_CHIP_REVISION_SHIFT                                         0
#define TMC6460_CHIP_REVISION_FIELD                                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_REVISION_MASK, .shift=TMC6460_CHIP_REVISION_SHIFT, .addr=TMC6460_CHIP_REVISION, .isSigned=false })

// CHIP.INPUTS_RAW fields
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_A_RAW_MASK                          0x00000001
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_A_RAW_SHIFT                         0
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_A_RAW_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_A_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_A_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_B_RAW_MASK                          0x00000002
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_B_RAW_SHIFT                         1
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_B_RAW_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_B_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_B_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_N_RAW_MASK                          0x00000004
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_N_RAW_SHIFT                         2
#define TMC6460_CHIP_INPUTS_RAW_PIN_ENC_N_RAW_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_N_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_ENC_N_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_U_RAW_MASK                         0x00000008
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_U_RAW_SHIFT                        3
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_U_RAW_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_U_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_U_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_V_RAW_MASK                         0x00000010
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_V_RAW_SHIFT                        4
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_V_RAW_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_V_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_V_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_W_RAW_MASK                         0x00000020
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_W_RAW_SHIFT                        5
#define TMC6460_CHIP_INPUTS_RAW_PIN_HALL_W_RAW_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_W_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_HALL_W_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_L_RAW_MASK                          0x00000040
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_L_RAW_SHIFT                         6
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_L_RAW_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_REF_L_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_REF_L_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_R_RAW_MASK                          0x00000080
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_R_RAW_SHIFT                         7
#define TMC6460_CHIP_INPUTS_RAW_PIN_REF_R_RAW_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_REF_R_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_REF_R_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDI_RAW_MASK                            0x00000100
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDI_RAW_SHIFT                           8
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDI_RAW_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_SDI_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_SDI_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDO_RAW_MASK                            0x00000200
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDO_RAW_SHIFT                           9
#define TMC6460_CHIP_INPUTS_RAW_PIN_SDO_RAW_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_SDO_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_SDO_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_SCK_RAW_MASK                            0x00000400
#define TMC6460_CHIP_INPUTS_RAW_PIN_SCK_RAW_SHIFT                           10
#define TMC6460_CHIP_INPUTS_RAW_PIN_SCK_RAW_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_SCK_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_SCK_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_CSN_RAW_MASK                            0x00000800
#define TMC6460_CHIP_INPUTS_RAW_PIN_CSN_RAW_SHIFT                           11
#define TMC6460_CHIP_INPUTS_RAW_PIN_CSN_RAW_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_CSN_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_CSN_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_PWM_IN_RAW_MASK                         0x00001000
#define TMC6460_CHIP_INPUTS_RAW_PIN_PWM_IN_RAW_SHIFT                        12
#define TMC6460_CHIP_INPUTS_RAW_PIN_PWM_IN_RAW_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_PWM_IN_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_PWM_IN_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_UART_RXD_RAW_MASK                       0x00002000
#define TMC6460_CHIP_INPUTS_RAW_PIN_UART_RXD_RAW_SHIFT                      13
#define TMC6460_CHIP_INPUTS_RAW_PIN_UART_RXD_RAW_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_UART_RXD_RAW_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_UART_RXD_RAW_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PIN_DRV_EN_MASK                             0x00008000
#define TMC6460_CHIP_INPUTS_RAW_PIN_DRV_EN_SHIFT                            15
#define TMC6460_CHIP_INPUTS_RAW_PIN_DRV_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PIN_DRV_EN_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PIN_DRV_EN_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC_A_MASK                                  0x00010000
#define TMC6460_CHIP_INPUTS_RAW_ENC_A_SHIFT                                 16
#define TMC6460_CHIP_INPUTS_RAW_ENC_A_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC_A_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC_A_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC_B_MASK                                  0x00020000
#define TMC6460_CHIP_INPUTS_RAW_ENC_B_SHIFT                                 17
#define TMC6460_CHIP_INPUTS_RAW_ENC_B_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC_B_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC_B_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC_N_MASK                                  0x00040000
#define TMC6460_CHIP_INPUTS_RAW_ENC_N_SHIFT                                 18
#define TMC6460_CHIP_INPUTS_RAW_ENC_N_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC_N_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC_N_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC2_A_MASK                                 0x00080000
#define TMC6460_CHIP_INPUTS_RAW_ENC2_A_SHIFT                                19
#define TMC6460_CHIP_INPUTS_RAW_ENC2_A_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC2_A_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC2_A_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC2_B_MASK                                 0x00100000
#define TMC6460_CHIP_INPUTS_RAW_ENC2_B_SHIFT                                20
#define TMC6460_CHIP_INPUTS_RAW_ENC2_B_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC2_B_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC2_B_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_ENC2_N_MASK                                 0x00200000
#define TMC6460_CHIP_INPUTS_RAW_ENC2_N_SHIFT                                21
#define TMC6460_CHIP_INPUTS_RAW_ENC2_N_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_ENC2_N_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_ENC2_N_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_HALL_U_MASK                                 0x00400000
#define TMC6460_CHIP_INPUTS_RAW_HALL_U_SHIFT                                22
#define TMC6460_CHIP_INPUTS_RAW_HALL_U_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_HALL_U_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_HALL_U_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_HALL_V_MASK                                 0x00800000
#define TMC6460_CHIP_INPUTS_RAW_HALL_V_SHIFT                                23
#define TMC6460_CHIP_INPUTS_RAW_HALL_V_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_HALL_V_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_HALL_V_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_HALL_W_MASK                                 0x01000000
#define TMC6460_CHIP_INPUTS_RAW_HALL_W_SHIFT                                24
#define TMC6460_CHIP_INPUTS_RAW_HALL_W_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_HALL_W_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_HALL_W_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_REF_L_MASK                                  0x02000000
#define TMC6460_CHIP_INPUTS_RAW_REF_L_SHIFT                                 25
#define TMC6460_CHIP_INPUTS_RAW_REF_L_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_REF_L_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_REF_L_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_REF_R_MASK                                  0x04000000
#define TMC6460_CHIP_INPUTS_RAW_REF_R_SHIFT                                 26
#define TMC6460_CHIP_INPUTS_RAW_REF_R_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_REF_R_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_REF_R_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_REF_H_MASK                                  0x08000000
#define TMC6460_CHIP_INPUTS_RAW_REF_H_SHIFT                                 27
#define TMC6460_CHIP_INPUTS_RAW_REF_H_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_REF_H_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_REF_H_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN0_MASK                             0x10000000
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN0_SHIFT                            28
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN0_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_DIRECT_IN0_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_DIRECT_IN0_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN1_MASK                             0x20000000
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN1_SHIFT                            29
#define TMC6460_CHIP_INPUTS_RAW_DIRECT_IN1_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_DIRECT_IN1_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_DIRECT_IN1_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_DIR_IN_MASK                                 0x40000000
#define TMC6460_CHIP_INPUTS_RAW_DIR_IN_SHIFT                                30
#define TMC6460_CHIP_INPUTS_RAW_DIR_IN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_DIR_IN_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_DIR_IN_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_INPUTS_RAW_PWM_IN_MASK                                 0x80000000
#define TMC6460_CHIP_INPUTS_RAW_PWM_IN_SHIFT                                31
#define TMC6460_CHIP_INPUTS_RAW_PWM_IN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_INPUTS_RAW_PWM_IN_MASK, .shift=TMC6460_CHIP_INPUTS_RAW_PWM_IN_SHIFT, .addr=TMC6460_CHIP_INPUTS_RAW, .isSigned=false })

// CHIP.OUTPUTS_RAW fields
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_L_MASK                               0x00000001
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_L_SHIFT                              0
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_L_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_U_L_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_U_L_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_H_MASK                               0x00000002
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_H_SHIFT                              1
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_U_H_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_U_H_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_U_H_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_L_MASK                               0x00000004
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_L_SHIFT                              2
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_L_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_V_L_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_V_L_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_H_MASK                               0x00000008
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_H_SHIFT                              3
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_V_H_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_V_H_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_V_H_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_L_MASK                               0x00000010
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_L_SHIFT                              4
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_L_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_W_L_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_W_L_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_H_MASK                               0x00000020
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_H_SHIFT                              5
#define TMC6460_CHIP_OUTPUTS_RAW_PWM_W_H_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_PWM_W_H_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_PWM_W_H_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_INT_OUT_MASK                               0x00000040
#define TMC6460_CHIP_OUTPUTS_RAW_INT_OUT_SHIFT                              6
#define TMC6460_CHIP_OUTPUTS_RAW_INT_OUT_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_INT_OUT_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_INT_OUT_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_FAULTN_OUT_MASK                            0x00000080
#define TMC6460_CHIP_OUTPUTS_RAW_FAULTN_OUT_SHIFT                           7
#define TMC6460_CHIP_OUTPUTS_RAW_FAULTN_OUT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_FAULTN_OUT_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_FAULTN_OUT_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_A_MASK                    0x01000000
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_A_SHIFT                   24
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_A_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_A_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_A_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_B_MASK                    0x02000000
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_B_SHIFT                   25
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_B_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_B_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_B_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_N_MASK                    0x04000000
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_N_SHIFT                   26
#define TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_N_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_N_MASK, .shift=TMC6460_CHIP_OUTPUTS_RAW_INVALID_DIFF_ENC_N_SHIFT, .addr=TMC6460_CHIP_OUTPUTS_RAW, .isSigned=false })

// CHIP.IO_MATRIX fields
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_A_MASK                               0x00000003
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_A_SHIFT                              0
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_A_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_ENC_A_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_ENC_A_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_B_MASK                               0x0000000C
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_B_SHIFT                              2
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_B_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_ENC_B_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_ENC_B_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_N_MASK                               0x00000030
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_N_SHIFT                              4
#define TMC6460_CHIP_IO_MATRIX_PIN_ENC_N_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_ENC_N_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_ENC_N_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_U_MASK                              0x000001C0
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_U_SHIFT                             6
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_U_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_HALL_U_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_HALL_U_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_V_MASK                              0x00000E00
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_V_SHIFT                             9
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_V_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_HALL_V_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_HALL_V_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_W_MASK                              0x00007000
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_W_SHIFT                             12
#define TMC6460_CHIP_IO_MATRIX_PIN_HALL_W_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_HALL_W_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_HALL_W_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_L_MASK                               0x00018000
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_L_SHIFT                              15
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_L_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_REF_L_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_REF_L_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_R_MASK                               0x00060000
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_R_SHIFT                              17
#define TMC6460_CHIP_IO_MATRIX_PIN_REF_R_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_REF_R_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_REF_R_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_SDI_MASK                                 0x00180000
#define TMC6460_CHIP_IO_MATRIX_PIN_SDI_SHIFT                                19
#define TMC6460_CHIP_IO_MATRIX_PIN_SDI_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_SDI_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_SDI_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_SDO_MASK                                 0x00600000
#define TMC6460_CHIP_IO_MATRIX_PIN_SDO_SHIFT                                21
#define TMC6460_CHIP_IO_MATRIX_PIN_SDO_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_SDO_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_SDO_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_SCK_MASK                                 0x00800000
#define TMC6460_CHIP_IO_MATRIX_PIN_SCK_SHIFT                                23
#define TMC6460_CHIP_IO_MATRIX_PIN_SCK_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_SCK_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_SCK_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_PWM_IN_MASK                              0x03000000
#define TMC6460_CHIP_IO_MATRIX_PIN_PWM_IN_SHIFT                             24
#define TMC6460_CHIP_IO_MATRIX_PIN_PWM_IN_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_PWM_IN_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_PWM_IN_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_RXD_MASK                            0x0C000000
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_RXD_SHIFT                           26
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_RXD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_UART_RXD_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_UART_RXD_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_TXD_MASK                            0x30000000
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_TXD_SHIFT                           28
#define TMC6460_CHIP_IO_MATRIX_PIN_UART_TXD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_UART_TXD_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_UART_TXD_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })
#define TMC6460_CHIP_IO_MATRIX_PIN_FAULTN_MASK                              0xC0000000
#define TMC6460_CHIP_IO_MATRIX_PIN_FAULTN_SHIFT                             30
#define TMC6460_CHIP_IO_MATRIX_PIN_FAULTN_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_MATRIX_PIN_FAULTN_MASK, .shift=TMC6460_CHIP_IO_MATRIX_PIN_FAULTN_SHIFT, .addr=TMC6460_CHIP_IO_MATRIX, .isSigned=false })

// CHIP.IO_PU_PD fields
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PU_MASK                             0x00000001
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PU_SHIFT                            0
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PU_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PU_MASK                             0x00000002
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PU_SHIFT                            1
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PU_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PU_MASK                             0x00000004
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PU_SHIFT                            2
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PU_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PU_MASK                            0x00000008
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PU_SHIFT                           3
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PU_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PU_MASK                            0x00000010
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PU_SHIFT                           4
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PU_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PU_MASK                            0x00000020
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PU_SHIFT                           5
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PU_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PU_MASK                             0x00000040
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PU_SHIFT                            6
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PU_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PU_MASK                             0x00000080
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PU_SHIFT                            7
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PU_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PD_MASK                             0x00000100
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PD_SHIFT                            8
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_A_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PD_MASK                             0x00000200
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PD_SHIFT                            9
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_B_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PD_MASK                             0x00000400
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PD_SHIFT                            10
#define TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_ENC_N_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PD_MASK                            0x00000800
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PD_SHIFT                           11
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_U_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PD_MASK                            0x00001000
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PD_SHIFT                           12
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_V_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PD_MASK                            0x00002000
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PD_SHIFT                           13
#define TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_HALL_W_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PD_MASK                             0x00004000
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PD_SHIFT                            14
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_REF_L_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PD_MASK                             0x00008000
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PD_SHIFT                            15
#define TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_REF_R_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PU_MASK                               0x00010000
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PU_SHIFT                              16
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PU_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_SDI_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_SDI_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PU_MASK                               0x00020000
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PU_SHIFT                              17
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PU_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_SCK_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_SCK_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PU_MASK                            0x00040000
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PU_SHIFT                           18
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PU_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PU_MASK                          0x00080000
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PU_SHIFT                         19
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PU_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_SDO_PU_MASK                               0x00100000
#define TMC6460_CHIP_IO_PU_PD_PIN_SDO_PU_SHIFT                              20
#define TMC6460_CHIP_IO_PU_PD_PIN_SDO_PU_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_SDO_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_SDO_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_FAULTN_PU_MASK                            0x00400000
#define TMC6460_CHIP_IO_PU_PD_PIN_FAULTN_PU_SHIFT                           22
#define TMC6460_CHIP_IO_PU_PD_PIN_FAULTN_PU_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_FAULTN_PU_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_FAULTN_PU_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PD_MASK                               0x01000000
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PD_SHIFT                              24
#define TMC6460_CHIP_IO_PU_PD_PIN_SDI_PD_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_SDI_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_SDI_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PD_MASK                               0x02000000
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PD_SHIFT                              25
#define TMC6460_CHIP_IO_PU_PD_PIN_SCK_PD_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_SCK_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_SCK_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PD_MASK                            0x04000000
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PD_SHIFT                           26
#define TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PD_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_PWM_IN_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PD_MASK                          0x08000000
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PD_SHIFT                         27
#define TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PD_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PD_MASK, .shift=TMC6460_CHIP_IO_PU_PD_PIN_UART_RXD_PD_SHIFT, .addr=TMC6460_CHIP_IO_PU_PD, .isSigned=false })

// CHIP.IO_CONFIG fields
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_A_MASK                           0x00000001
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_A_SHIFT                          0
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_A_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_A_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_A_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_B_MASK                           0x00000002
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_B_SHIFT                          1
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_B_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_B_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_B_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_N_MASK                           0x00000004
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_N_SHIFT                          2
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_N_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_N_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_ENC_N_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_U_MASK                          0x00000008
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_U_SHIFT                         3
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_U_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_U_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_U_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_V_MASK                          0x00000010
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_V_SHIFT                         4
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_V_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_V_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_V_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_W_MASK                          0x00000020
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_W_SHIFT                         5
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_W_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_W_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_HALL_W_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_L_MASK                           0x00000040
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_L_SHIFT                          6
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_L_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_L_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_L_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_R_MASK                           0x00000080
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_R_SHIFT                          7
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_R_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_R_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_REF_R_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SDI_MASK                             0x00000100
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SDI_SHIFT                            8
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SDI_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_SDI_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_SDI_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SCK_MASK                             0x00000200
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SCK_SHIFT                            9
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_SCK_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_SCK_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_SCK_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_PWM_IN_MASK                          0x00000400
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_PWM_IN_SHIFT                         10
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_PWM_IN_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_PWM_IN_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_PWM_IN_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_RXD_MASK                             0x00000800
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_RXD_SHIFT                            11
#define TMC6460_CHIP_IO_CONFIG_INV_PIN_RXD_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_INV_PIN_RXD_MASK, .shift=TMC6460_CHIP_IO_CONFIG_INV_PIN_RXD_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_ENC_FLT_MASK                                 0x00003000
#define TMC6460_CHIP_IO_CONFIG_ENC_FLT_SHIFT                                12
#define TMC6460_CHIP_IO_CONFIG_ENC_FLT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_ENC_FLT_MASK, .shift=TMC6460_CHIP_IO_CONFIG_ENC_FLT_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_HALL_FLT_MASK                                0x0000C000
#define TMC6460_CHIP_IO_CONFIG_HALL_FLT_SHIFT                               14
#define TMC6460_CHIP_IO_CONFIG_HALL_FLT_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_HALL_FLT_MASK, .shift=TMC6460_CHIP_IO_CONFIG_HALL_FLT_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_REF_FLT_MASK                                 0x00030000
#define TMC6460_CHIP_IO_CONFIG_REF_FLT_SHIFT                                16
#define TMC6460_CHIP_IO_CONFIG_REF_FLT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_REF_FLT_MASK, .shift=TMC6460_CHIP_IO_CONFIG_REF_FLT_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_PWM_IN_FLT_MASK                              0x000C0000
#define TMC6460_CHIP_IO_CONFIG_PWM_IN_FLT_SHIFT                             18
#define TMC6460_CHIP_IO_CONFIG_PWM_IN_FLT_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_PWM_IN_FLT_MASK, .shift=TMC6460_CHIP_IO_CONFIG_PWM_IN_FLT_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIO_MASK                           0x00300000
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIO_SHIFT                          20
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIO_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIO_MASK, .shift=TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIO_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIOF_MASK                          0x00C00000
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIOF_SHIFT                         22
#define TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIOF_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIOF_MASK, .shift=TMC6460_CHIP_IO_CONFIG_ANA_DIV_VCCIOF_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_L_AS_REF_R_MASK                  0x01000000
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_L_AS_REF_R_SHIFT                 24
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_L_AS_REF_R_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_L_AS_REF_R_MASK, .shift=TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_L_AS_REF_R_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_R_AS_REF_L_MASK                  0x02000000
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_R_AS_REF_L_SHIFT                 25
#define TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_R_AS_REF_L_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_R_AS_REF_L_MASK, .shift=TMC6460_CHIP_IO_CONFIG_USE_PIN_REF_R_AS_REF_L_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })
#define TMC6460_CHIP_IO_CONFIG_DIFF_DELAY_MASK                              0xF0000000
#define TMC6460_CHIP_IO_CONFIG_DIFF_DELAY_SHIFT                             28
#define TMC6460_CHIP_IO_CONFIG_DIFF_DELAY_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_IO_CONFIG_DIFF_DELAY_MASK, .shift=TMC6460_CHIP_IO_CONFIG_DIFF_DELAY_SHIFT, .addr=TMC6460_CHIP_IO_CONFIG, .isSigned=false })

// CHIP.STATUS_FLAGS fields
#define TMC6460_CHIP_STATUS_FLAGS_PWRUP_FAIL_STATUS_MASK                    0x00000001
#define TMC6460_CHIP_STATUS_FLAGS_PWRUP_FAIL_STATUS_SHIFT                   0
#define TMC6460_CHIP_STATUS_FLAGS_PWRUP_FAIL_STATUS_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_PWRUP_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_PWRUP_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_SPI_FAIL_STATUS_MASK                      0x00000002
#define TMC6460_CHIP_STATUS_FLAGS_SPI_FAIL_STATUS_SHIFT                     1
#define TMC6460_CHIP_STATUS_FLAGS_SPI_FAIL_STATUS_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_SPI_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_SPI_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_UART_FAIL_STATUS_MASK                     0x00000004
#define TMC6460_CHIP_STATUS_FLAGS_UART_FAIL_STATUS_SHIFT                    2
#define TMC6460_CHIP_STATUS_FLAGS_UART_FAIL_STATUS_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_UART_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_UART_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_VCC_IOF_FAIL_STATUS_MASK                  0x00000008
#define TMC6460_CHIP_STATUS_FLAGS_VCC_IOF_FAIL_STATUS_SHIFT                 3
#define TMC6460_CHIP_STATUS_FLAGS_VCC_IOF_FAIL_STATUS_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_VCC_IOF_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_VCC_IOF_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_CP_FAIL_STATUS_MASK                       0x00000010
#define TMC6460_CHIP_STATUS_FLAGS_CP_FAIL_STATUS_SHIFT                      4
#define TMC6460_CHIP_STATUS_FLAGS_CP_FAIL_STATUS_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_CP_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_CP_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_UV_VM_STATUS_MASK                         0x00000020
#define TMC6460_CHIP_STATUS_FLAGS_UV_VM_STATUS_SHIFT                        5
#define TMC6460_CHIP_STATUS_FLAGS_UV_VM_STATUS_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_UV_VM_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_UV_VM_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_POWER_FAIL_STATUS_MASK                    0x00000040
#define TMC6460_CHIP_STATUS_FLAGS_POWER_FAIL_STATUS_SHIFT                   6
#define TMC6460_CHIP_STATUS_FLAGS_POWER_FAIL_STATUS_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_POWER_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_POWER_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_CLK_PLL_FAIL_STATUS_MASK                  0x00000080
#define TMC6460_CHIP_STATUS_FLAGS_CLK_PLL_FAIL_STATUS_SHIFT                 7
#define TMC6460_CHIP_STATUS_FLAGS_CLK_PLL_FAIL_STATUS_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_CLK_PLL_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_CLK_PLL_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_EXT_RES_FAIL_STATUS_MASK                  0x00000100
#define TMC6460_CHIP_STATUS_FLAGS_EXT_RES_FAIL_STATUS_SHIFT                 8
#define TMC6460_CHIP_STATUS_FLAGS_EXT_RES_FAIL_STATUS_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_EXT_RES_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_EXT_RES_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_ADC_FAIL_STATUS_MASK                      0x00000200
#define TMC6460_CHIP_STATUS_FLAGS_ADC_FAIL_STATUS_SHIFT                     9
#define TMC6460_CHIP_STATUS_FLAGS_ADC_FAIL_STATUS_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_ADC_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_ADC_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_TEMP_LIMIT_FAIL_STATUS_MASK               0x00000400
#define TMC6460_CHIP_STATUS_FLAGS_TEMP_LIMIT_FAIL_STATUS_SHIFT              10
#define TMC6460_CHIP_STATUS_FLAGS_TEMP_LIMIT_FAIL_STATUS_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_TEMP_LIMIT_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_TEMP_LIMIT_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_VEL_FAIL_STATUS_MASK                      0x00000800
#define TMC6460_CHIP_STATUS_FLAGS_VEL_FAIL_STATUS_SHIFT                     11
#define TMC6460_CHIP_STATUS_FLAGS_VEL_FAIL_STATUS_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_VEL_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_VEL_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_SHRT_FAIL_STATUS_MASK                     0x00001000
#define TMC6460_CHIP_STATUS_FLAGS_SHRT_FAIL_STATUS_SHIFT                    12
#define TMC6460_CHIP_STATUS_FLAGS_SHRT_FAIL_STATUS_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_SHRT_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_SHRT_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_OT_FAIL_STATUS_MASK                       0x00002000
#define TMC6460_CHIP_STATUS_FLAGS_OT_FAIL_STATUS_SHIFT                      13
#define TMC6460_CHIP_STATUS_FLAGS_OT_FAIL_STATUS_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_OT_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_OT_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_DIFF_ENC_FAIL_STATUS_MASK                 0x00004000
#define TMC6460_CHIP_STATUS_FLAGS_DIFF_ENC_FAIL_STATUS_SHIFT                14
#define TMC6460_CHIP_STATUS_FLAGS_DIFF_ENC_FAIL_STATUS_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_DIFF_ENC_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_DIFF_ENC_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_IO_CONTROLLER_STATUS_MASK                 0x00008000
#define TMC6460_CHIP_STATUS_FLAGS_IO_CONTROLLER_STATUS_SHIFT                15
#define TMC6460_CHIP_STATUS_FLAGS_IO_CONTROLLER_STATUS_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_IO_CONTROLLER_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_IO_CONTROLLER_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_STALL_FAIL_STATUS_MASK               0x00010000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_STALL_FAIL_STATUS_SHIFT              16
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_STALL_FAIL_STATUS_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_STALL_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_STALL_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_TARGET_REACHED_STATUS_MASK           0x00020000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_TARGET_REACHED_STATUS_SHIFT          17
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_TARGET_REACHED_STATUS_FIELD          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_TARGET_REACHED_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_TARGET_REACHED_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_REACHED_STATUS_MASK                0x00040000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_REACHED_STATUS_SHIFT               18
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_REACHED_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_V_REACHED_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_V_REACHED_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_ZERO_STATUS_MASK                   0x00080000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_ZERO_STATUS_SHIFT                  19
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_V_ZERO_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_V_ZERO_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_V_ZERO_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_LR_STATUS_MASK                   0x00100000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_LR_STATUS_SHIFT                  20
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_LR_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_LR_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_LR_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_H_STATUS_MASK                    0x00200000
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_H_STATUS_SHIFT                   21
#define TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_H_STATUS_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_H_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_RAMP_REF_H_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_ABN_FAIL_STATUS_MASK                      0x00400000
#define TMC6460_CHIP_STATUS_FLAGS_ABN_FAIL_STATUS_SHIFT                     22
#define TMC6460_CHIP_STATUS_FLAGS_ABN_FAIL_STATUS_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_ABN_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_ABN_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_HALL_FAIL_STATUS_MASK                     0x00800000
#define TMC6460_CHIP_STATUS_FLAGS_HALL_FAIL_STATUS_SHIFT                    23
#define TMC6460_CHIP_STATUS_FLAGS_HALL_FAIL_STATUS_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_HALL_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_HALL_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_CURRENT_OVERLOAD_STATUS_MASK              0x01000000
#define TMC6460_CHIP_STATUS_FLAGS_CURRENT_OVERLOAD_STATUS_SHIFT             24
#define TMC6460_CHIP_STATUS_FLAGS_CURRENT_OVERLOAD_STATUS_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_CURRENT_OVERLOAD_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_CURRENT_OVERLOAD_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_I_CLIPPED_STATUS_MASK                     0x02000000
#define TMC6460_CHIP_STATUS_FLAGS_I_CLIPPED_STATUS_SHIFT                    25
#define TMC6460_CHIP_STATUS_FLAGS_I_CLIPPED_STATUS_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_I_CLIPPED_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_I_CLIPPED_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_AIN_CLIPPED_STATUS_MASK                   0x04000000
#define TMC6460_CHIP_STATUS_FLAGS_AIN_CLIPPED_STATUS_SHIFT                  26
#define TMC6460_CHIP_STATUS_FLAGS_AIN_CLIPPED_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_AIN_CLIPPED_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_AIN_CLIPPED_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_VM_TEMP_CLIPPED_STATUS_MASK               0x08000000
#define TMC6460_CHIP_STATUS_FLAGS_VM_TEMP_CLIPPED_STATUS_SHIFT              27
#define TMC6460_CHIP_STATUS_FLAGS_VM_TEMP_CLIPPED_STATUS_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_VM_TEMP_CLIPPED_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_VM_TEMP_CLIPPED_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_OV_VM_LIMIT_FAIL_STATUS_MASK              0x10000000
#define TMC6460_CHIP_STATUS_FLAGS_OV_VM_LIMIT_FAIL_STATUS_SHIFT             28
#define TMC6460_CHIP_STATUS_FLAGS_OV_VM_LIMIT_FAIL_STATUS_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_OV_VM_LIMIT_FAIL_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_OV_VM_LIMIT_FAIL_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_OVERTEMP_WARN_STATUS_MASK                 0x20000000
#define TMC6460_CHIP_STATUS_FLAGS_OVERTEMP_WARN_STATUS_SHIFT                29
#define TMC6460_CHIP_STATUS_FLAGS_OVERTEMP_WARN_STATUS_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_OVERTEMP_WARN_STATUS_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_OVERTEMP_WARN_STATUS_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_SYS_READY_STATE_MASK                      0x40000000
#define TMC6460_CHIP_STATUS_FLAGS_SYS_READY_STATE_SHIFT                     30
#define TMC6460_CHIP_STATUS_FLAGS_SYS_READY_STATE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_SYS_READY_STATE_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_SYS_READY_STATE_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })
#define TMC6460_CHIP_STATUS_FLAGS_GDRV_ON_STATE_MASK                        0x80000000
#define TMC6460_CHIP_STATUS_FLAGS_GDRV_ON_STATE_SHIFT                       31
#define TMC6460_CHIP_STATUS_FLAGS_GDRV_ON_STATE_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CHIP_STATUS_FLAGS_GDRV_ON_STATE_MASK, .shift=TMC6460_CHIP_STATUS_FLAGS_GDRV_ON_STATE_SHIFT, .addr=TMC6460_CHIP_STATUS_FLAGS, .isSigned=false })

// CHIP.EVENTS fields
#define TMC6460_CHIP_EVENTS_RST_EVENT_MASK                                  0x00000001
#define TMC6460_CHIP_EVENTS_RST_EVENT_SHIFT                                 0
#define TMC6460_CHIP_EVENTS_RST_EVENT_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RST_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RST_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_SPI_FAIL_EVENT_MASK                             0x00000002
#define TMC6460_CHIP_EVENTS_SPI_FAIL_EVENT_SHIFT                            1
#define TMC6460_CHIP_EVENTS_SPI_FAIL_EVENT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_SPI_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_SPI_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_UART_FAIL_EVENT_MASK                            0x00000004
#define TMC6460_CHIP_EVENTS_UART_FAIL_EVENT_SHIFT                           2
#define TMC6460_CHIP_EVENTS_UART_FAIL_EVENT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_UART_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_UART_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_VCCIOF_FAIL_EVENT_MASK                          0x00000008
#define TMC6460_CHIP_EVENTS_VCCIOF_FAIL_EVENT_SHIFT                         3
#define TMC6460_CHIP_EVENTS_VCCIOF_FAIL_EVENT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_VCCIOF_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_VCCIOF_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_CP_FAIL_EVENT_MASK                              0x00000010
#define TMC6460_CHIP_EVENTS_CP_FAIL_EVENT_SHIFT                             4
#define TMC6460_CHIP_EVENTS_CP_FAIL_EVENT_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_CP_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_CP_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_UV_VM_EVENT_MASK                                0x00000020
#define TMC6460_CHIP_EVENTS_UV_VM_EVENT_SHIFT                               5
#define TMC6460_CHIP_EVENTS_UV_VM_EVENT_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_UV_VM_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_UV_VM_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_POWER_FAIL_EVENT_MASK                           0x00000040
#define TMC6460_CHIP_EVENTS_POWER_FAIL_EVENT_SHIFT                          6
#define TMC6460_CHIP_EVENTS_POWER_FAIL_EVENT_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_POWER_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_POWER_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_CLK_PLL_FAIL_EVENT_MASK                         0x00000080
#define TMC6460_CHIP_EVENTS_CLK_PLL_FAIL_EVENT_SHIFT                        7
#define TMC6460_CHIP_EVENTS_CLK_PLL_FAIL_EVENT_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_CLK_PLL_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_CLK_PLL_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_EXT_RES_FAIL_EVENT_MASK                         0x00000100
#define TMC6460_CHIP_EVENTS_EXT_RES_FAIL_EVENT_SHIFT                        8
#define TMC6460_CHIP_EVENTS_EXT_RES_FAIL_EVENT_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_EXT_RES_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_EXT_RES_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_ADC_FAIL_EVENT_MASK                             0x00000200
#define TMC6460_CHIP_EVENTS_ADC_FAIL_EVENT_SHIFT                            9
#define TMC6460_CHIP_EVENTS_ADC_FAIL_EVENT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_ADC_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_ADC_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_TEMP_LIMIT_FAIL_EVENT_MASK                      0x00000400
#define TMC6460_CHIP_EVENTS_TEMP_LIMIT_FAIL_EVENT_SHIFT                     10
#define TMC6460_CHIP_EVENTS_TEMP_LIMIT_FAIL_EVENT_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_TEMP_LIMIT_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_TEMP_LIMIT_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_VEL_FAIL_EVENT_MASK                             0x00000800
#define TMC6460_CHIP_EVENTS_VEL_FAIL_EVENT_SHIFT                            11
#define TMC6460_CHIP_EVENTS_VEL_FAIL_EVENT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_VEL_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_VEL_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_SHRT_FAIL_EVENT_MASK                            0x00001000
#define TMC6460_CHIP_EVENTS_SHRT_FAIL_EVENT_SHIFT                           12
#define TMC6460_CHIP_EVENTS_SHRT_FAIL_EVENT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_SHRT_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_SHRT_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_OT_FAIL_EVENT_MASK                              0x00002000
#define TMC6460_CHIP_EVENTS_OT_FAIL_EVENT_SHIFT                             13
#define TMC6460_CHIP_EVENTS_OT_FAIL_EVENT_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_OT_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_OT_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_DIFF_ENC_FAIL_EVENT_MASK                        0x00004000
#define TMC6460_CHIP_EVENTS_DIFF_ENC_FAIL_EVENT_SHIFT                       14
#define TMC6460_CHIP_EVENTS_DIFF_ENC_FAIL_EVENT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_DIFF_ENC_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_DIFF_ENC_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_IO_CONTROLLER_EVENT_MASK                        0x00008000
#define TMC6460_CHIP_EVENTS_IO_CONTROLLER_EVENT_SHIFT                       15
#define TMC6460_CHIP_EVENTS_IO_CONTROLLER_EVENT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_IO_CONTROLLER_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_IO_CONTROLLER_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_STALL_FAIL_EVENT_MASK                      0x00010000
#define TMC6460_CHIP_EVENTS_RAMP_STALL_FAIL_EVENT_SHIFT                     16
#define TMC6460_CHIP_EVENTS_RAMP_STALL_FAIL_EVENT_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_STALL_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_STALL_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_TARGET_REACHED_EVENT_MASK                  0x00020000
#define TMC6460_CHIP_EVENTS_RAMP_TARGET_REACHED_EVENT_SHIFT                 17
#define TMC6460_CHIP_EVENTS_RAMP_TARGET_REACHED_EVENT_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_TARGET_REACHED_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_TARGET_REACHED_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_V_REACHED_EVENT_MASK                       0x00040000
#define TMC6460_CHIP_EVENTS_RAMP_V_REACHED_EVENT_SHIFT                      18
#define TMC6460_CHIP_EVENTS_RAMP_V_REACHED_EVENT_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_V_REACHED_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_V_REACHED_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_V_ZERO_EVENT_MASK                          0x00080000
#define TMC6460_CHIP_EVENTS_RAMP_V_ZERO_EVENT_SHIFT                         19
#define TMC6460_CHIP_EVENTS_RAMP_V_ZERO_EVENT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_V_ZERO_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_V_ZERO_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_REF_LR_EVENT_MASK                          0x00100000
#define TMC6460_CHIP_EVENTS_RAMP_REF_LR_EVENT_SHIFT                         20
#define TMC6460_CHIP_EVENTS_RAMP_REF_LR_EVENT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_REF_LR_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_REF_LR_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_RAMP_REF_H_EVENT_MASK                           0x00200000
#define TMC6460_CHIP_EVENTS_RAMP_REF_H_EVENT_SHIFT                          21
#define TMC6460_CHIP_EVENTS_RAMP_REF_H_EVENT_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_RAMP_REF_H_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_RAMP_REF_H_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_ABN_FAIL_EVENT_MASK                             0x00400000
#define TMC6460_CHIP_EVENTS_ABN_FAIL_EVENT_SHIFT                            22
#define TMC6460_CHIP_EVENTS_ABN_FAIL_EVENT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_ABN_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_ABN_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_HALL_FAIL_EVENT_MASK                            0x00800000
#define TMC6460_CHIP_EVENTS_HALL_FAIL_EVENT_SHIFT                           23
#define TMC6460_CHIP_EVENTS_HALL_FAIL_EVENT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_HALL_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_HALL_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_CURRENT_OVERLOAD_EVENT_MASK                     0x01000000
#define TMC6460_CHIP_EVENTS_CURRENT_OVERLOAD_EVENT_SHIFT                    24
#define TMC6460_CHIP_EVENTS_CURRENT_OVERLOAD_EVENT_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_CURRENT_OVERLOAD_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_CURRENT_OVERLOAD_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_I_CLIPPED_EVENT_MASK                            0x02000000
#define TMC6460_CHIP_EVENTS_I_CLIPPED_EVENT_SHIFT                           25
#define TMC6460_CHIP_EVENTS_I_CLIPPED_EVENT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_I_CLIPPED_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_I_CLIPPED_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_AIN_CLIPPED_EVENT_MASK                          0x04000000
#define TMC6460_CHIP_EVENTS_AIN_CLIPPED_EVENT_SHIFT                         26
#define TMC6460_CHIP_EVENTS_AIN_CLIPPED_EVENT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_AIN_CLIPPED_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_AIN_CLIPPED_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_VM_TEMP_CLIPPED_EVENT_MASK                      0x08000000
#define TMC6460_CHIP_EVENTS_VM_TEMP_CLIPPED_EVENT_SHIFT                     27
#define TMC6460_CHIP_EVENTS_VM_TEMP_CLIPPED_EVENT_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_VM_TEMP_CLIPPED_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_VM_TEMP_CLIPPED_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_OV_VM_LIMIT_FAIL_EVENT_MASK                     0x10000000
#define TMC6460_CHIP_EVENTS_OV_VM_LIMIT_FAIL_EVENT_SHIFT                    28
#define TMC6460_CHIP_EVENTS_OV_VM_LIMIT_FAIL_EVENT_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_OV_VM_LIMIT_FAIL_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_OV_VM_LIMIT_FAIL_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_OVERTEMP_WARN_EVENT_MASK                        0x20000000
#define TMC6460_CHIP_EVENTS_OVERTEMP_WARN_EVENT_SHIFT                       29
#define TMC6460_CHIP_EVENTS_OVERTEMP_WARN_EVENT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_OVERTEMP_WARN_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_OVERTEMP_WARN_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_SYS_READY_EVENT_MASK                            0x40000000
#define TMC6460_CHIP_EVENTS_SYS_READY_EVENT_SHIFT                           30
#define TMC6460_CHIP_EVENTS_SYS_READY_EVENT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_SYS_READY_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_SYS_READY_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })
#define TMC6460_CHIP_EVENTS_GDRV_ON_EVENT_MASK                              0x80000000
#define TMC6460_CHIP_EVENTS_GDRV_ON_EVENT_SHIFT                             31
#define TMC6460_CHIP_EVENTS_GDRV_ON_EVENT_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CHIP_EVENTS_GDRV_ON_EVENT_MASK, .shift=TMC6460_CHIP_EVENTS_GDRV_ON_EVENT_SHIFT, .addr=TMC6460_CHIP_EVENTS, .isSigned=false })

// CHIP.FAULTN_INT_MASK fields
#define TMC6460_CHIP_FAULTN_INT_MASK_MASK                                   0xFFFFFFFF
#define TMC6460_CHIP_FAULTN_INT_MASK_SHIFT                                  0
#define TMC6460_CHIP_FAULTN_INT_MASK_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_CHIP_FAULTN_INT_MASK_MASK, .shift=TMC6460_CHIP_FAULTN_INT_MASK_SHIFT, .addr=TMC6460_CHIP_FAULTN_INT_MASK, .isSigned=false })

// CHIP.SPI_STATUS_MASK fields
#define TMC6460_CHIP_SPI_STATUS_MASK_MASK                                   0xFFFFFFFF
#define TMC6460_CHIP_SPI_STATUS_MASK_SHIFT                                  0
#define TMC6460_CHIP_SPI_STATUS_MASK_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_CHIP_SPI_STATUS_MASK_MASK, .shift=TMC6460_CHIP_SPI_STATUS_MASK_SHIFT, .addr=TMC6460_CHIP_SPI_STATUS_MASK, .isSigned=false })

// CLK_CTRL.CONFIG fields
#define TMC6460_CLK_CTRL_CONFIG_COMMIT_MASK                                 0x00000001
#define TMC6460_CLK_CTRL_CONFIG_COMMIT_SHIFT                                0
#define TMC6460_CLK_CTRL_CONFIG_COMMIT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_COMMIT_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_COMMIT_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_PLL_SRC_MASK                                0x00000002
#define TMC6460_CLK_CTRL_CONFIG_PLL_SRC_SHIFT                               1
#define TMC6460_CLK_CTRL_CONFIG_PLL_SRC_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_PLL_SRC_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_PLL_SRC_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_PLL_EN_MASK                                 0x00000004
#define TMC6460_CLK_CTRL_CONFIG_PLL_EN_SHIFT                                2
#define TMC6460_CLK_CTRL_CONFIG_PLL_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_PLL_EN_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_PLL_EN_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_ADC_CLK_EN_MASK                             0x00000008
#define TMC6460_CLK_CTRL_CONFIG_ADC_CLK_EN_SHIFT                            3
#define TMC6460_CLK_CTRL_CONFIG_ADC_CLK_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_ADC_CLK_EN_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_ADC_CLK_EN_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_PWM_CLK_EN_MASK                             0x00000010
#define TMC6460_CLK_CTRL_CONFIG_PWM_CLK_EN_SHIFT                            4
#define TMC6460_CLK_CTRL_CONFIG_PWM_CLK_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_PWM_CLK_EN_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_PWM_CLK_EN_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_CLK_FSM_EN_MASK                             0x00000020
#define TMC6460_CLK_CTRL_CONFIG_CLK_FSM_EN_SHIFT                            5
#define TMC6460_CLK_CTRL_CONFIG_CLK_FSM_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_CLK_FSM_EN_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_CLK_FSM_EN_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })
#define TMC6460_CLK_CTRL_CONFIG_CLOCK_DIVIDER_MASK                          0x00001F00
#define TMC6460_CLK_CTRL_CONFIG_CLOCK_DIVIDER_SHIFT                         8
#define TMC6460_CLK_CTRL_CONFIG_CLOCK_DIVIDER_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_CONFIG_CLOCK_DIVIDER_MASK, .shift=TMC6460_CLK_CTRL_CONFIG_CLOCK_DIVIDER_SHIFT, .addr=TMC6460_CLK_CTRL_CONFIG, .isSigned=false })

// CLK_CTRL.STATUS fields
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_OK_MASK                             0x00000001
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_OK_SHIFT                            0
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_OK_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_1M0_OK_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_1M0_OK_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_TIMEOUT_MASK                        0x00000002
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_TIMEOUT_SHIFT                       1
#define TMC6460_CLK_CTRL_STATUS_CLK_1M0_TIMEOUT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_1M0_TIMEOUT_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_1M0_TIMEOUT_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_MASK                            0x00000004
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_SHIFT                           2
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_CLK_STUCK_MASK                              0x00000008
#define TMC6460_CLK_CTRL_STATUS_CLK_STUCK_SHIFT                             3
#define TMC6460_CLK_CTRL_STATUS_CLK_STUCK_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_STUCK_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_STUCK_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_PLL_ERR_MASK                                0x00000010
#define TMC6460_CLK_CTRL_STATUS_PLL_ERR_SHIFT                               4
#define TMC6460_CLK_CTRL_STATUS_PLL_ERR_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_PLL_ERR_MASK, .shift=TMC6460_CLK_CTRL_STATUS_PLL_ERR_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_PLL_LOCK_ON_MASK                            0x00000020
#define TMC6460_CLK_CTRL_STATUS_PLL_LOCK_ON_SHIFT                           5
#define TMC6460_CLK_CTRL_STATUS_PLL_LOCK_ON_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_PLL_LOCK_ON_MASK, .shift=TMC6460_CLK_CTRL_STATUS_PLL_LOCK_ON_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_PLL_READY_MASK                              0x00000040
#define TMC6460_CLK_CTRL_STATUS_PLL_READY_SHIFT                             6
#define TMC6460_CLK_CTRL_STATUS_PLL_READY_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_PLL_READY_MASK, .shift=TMC6460_CLK_CTRL_STATUS_PLL_READY_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_RPT_MASK                        0x00FF0000
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_RPT_SHIFT                       16
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_RPT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_RPT_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_FSM_ERR_RPT_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_FLG_MASK                            0xFF000000
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_FLG_SHIFT                           24
#define TMC6460_CLK_CTRL_STATUS_CLK_FSM_FLG_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_CLK_CTRL_STATUS_CLK_FSM_FLG_MASK, .shift=TMC6460_CLK_CTRL_STATUS_CLK_FSM_FLG_SHIFT, .addr=TMC6460_CLK_CTRL_STATUS, .isSigned=false })

// ADC.CONFIG fields
#define TMC6460_ADC_CONFIG_NRST_ADC_0_MASK                                  0x00000004
#define TMC6460_ADC_CONFIG_NRST_ADC_0_SHIFT                                 2
#define TMC6460_ADC_CONFIG_NRST_ADC_0_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_CONFIG_NRST_ADC_0_MASK, .shift=TMC6460_ADC_CONFIG_NRST_ADC_0_SHIFT, .addr=TMC6460_ADC_CONFIG, .isSigned=false })
#define TMC6460_ADC_CONFIG_NRST_ADC_1_MASK                                  0x00000008
#define TMC6460_ADC_CONFIG_NRST_ADC_1_SHIFT                                 3
#define TMC6460_ADC_CONFIG_NRST_ADC_1_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_CONFIG_NRST_ADC_1_MASK, .shift=TMC6460_ADC_CONFIG_NRST_ADC_1_SHIFT, .addr=TMC6460_ADC_CONFIG, .isSigned=false })
#define TMC6460_ADC_CONFIG_CSA_AZ_FLT_EXP_MASK                              0x00000F00
#define TMC6460_ADC_CONFIG_CSA_AZ_FLT_EXP_SHIFT                             8
#define TMC6460_ADC_CONFIG_CSA_AZ_FLT_EXP_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_ADC_CONFIG_CSA_AZ_FLT_EXP_MASK, .shift=TMC6460_ADC_CONFIG_CSA_AZ_FLT_EXP_SHIFT, .addr=TMC6460_ADC_CONFIG, .isSigned=false })

// ADC.ADC_VERSION fields
#define TMC6460_ADC_ADC_VERSION_VERSION_NUMBER_MASK                         0xFFFFFFFF
#define TMC6460_ADC_ADC_VERSION_VERSION_NUMBER_SHIFT                        0
#define TMC6460_ADC_ADC_VERSION_VERSION_NUMBER_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_ADC_ADC_VERSION_VERSION_NUMBER_MASK, .shift=TMC6460_ADC_ADC_VERSION_VERSION_NUMBER_SHIFT, .addr=TMC6460_ADC_ADC_VERSION, .isSigned=false })

// ADC.I2_I1_RAW fields
#define TMC6460_ADC_I2_I1_RAW_I1_MASK                                       0x0000FFFF
#define TMC6460_ADC_I2_I1_RAW_I1_SHIFT                                      0
#define TMC6460_ADC_I2_I1_RAW_I1_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_ADC_I2_I1_RAW_I1_MASK, .shift=TMC6460_ADC_I2_I1_RAW_I1_SHIFT, .addr=TMC6460_ADC_I2_I1_RAW, .isSigned=true })
#define TMC6460_ADC_I2_I1_RAW_I2_MASK                                       0xFFFF0000
#define TMC6460_ADC_I2_I1_RAW_I2_SHIFT                                      16
#define TMC6460_ADC_I2_I1_RAW_I2_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_ADC_I2_I1_RAW_I2_MASK, .shift=TMC6460_ADC_I2_I1_RAW_I2_SHIFT, .addr=TMC6460_ADC_I2_I1_RAW, .isSigned=true })

// ADC.VM_I3_RAW fields
#define TMC6460_ADC_VM_I3_RAW_I3_MASK                                       0x0000FFFF
#define TMC6460_ADC_VM_I3_RAW_I3_SHIFT                                      0
#define TMC6460_ADC_VM_I3_RAW_I3_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_ADC_VM_I3_RAW_I3_MASK, .shift=TMC6460_ADC_VM_I3_RAW_I3_SHIFT, .addr=TMC6460_ADC_VM_I3_RAW, .isSigned=true })
#define TMC6460_ADC_VM_I3_RAW_VM_MASK                                       0xFFFF0000
#define TMC6460_ADC_VM_I3_RAW_VM_SHIFT                                      16
#define TMC6460_ADC_VM_I3_RAW_VM_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_ADC_VM_I3_RAW_VM_MASK, .shift=TMC6460_ADC_VM_I3_RAW_VM_SHIFT, .addr=TMC6460_ADC_VM_I3_RAW, .isSigned=true })

// ADC.TEMP_RAW fields
#define TMC6460_ADC_TEMP_RAW_TEMP_EXT_MASK                                  0x0000FFFF
#define TMC6460_ADC_TEMP_RAW_TEMP_EXT_SHIFT                                 0
#define TMC6460_ADC_TEMP_RAW_TEMP_EXT_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_TEMP_RAW_TEMP_EXT_MASK, .shift=TMC6460_ADC_TEMP_RAW_TEMP_EXT_SHIFT, .addr=TMC6460_ADC_TEMP_RAW, .isSigned=true })
#define TMC6460_ADC_TEMP_RAW_TEMP_INT_MASK                                  0xFFFF0000
#define TMC6460_ADC_TEMP_RAW_TEMP_INT_SHIFT                                 16
#define TMC6460_ADC_TEMP_RAW_TEMP_INT_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_TEMP_RAW_TEMP_INT_MASK, .shift=TMC6460_ADC_TEMP_RAW_TEMP_INT_SHIFT, .addr=TMC6460_ADC_TEMP_RAW, .isSigned=true })

// ADC.AIN_V_AIN_U_RAW fields
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_U_MASK                              0x0000FFFF
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_U_SHIFT                             0
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_U_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_U_MASK, .shift=TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_U_SHIFT, .addr=TMC6460_ADC_AIN_V_AIN_U_RAW, .isSigned=true })
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_V_MASK                              0xFFFF0000
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_V_SHIFT                             16
#define TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_V_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_V_MASK, .shift=TMC6460_ADC_AIN_V_AIN_U_RAW_AIN_V_SHIFT, .addr=TMC6460_ADC_AIN_V_AIN_U_RAW, .isSigned=true })

// ADC.AIN_AIN_W_RAW fields
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_W_MASK                                0x0000FFFF
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_W_SHIFT                               0
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_W_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_ADC_AIN_AIN_W_RAW_AIN_W_MASK, .shift=TMC6460_ADC_AIN_AIN_W_RAW_AIN_W_SHIFT, .addr=TMC6460_ADC_AIN_AIN_W_RAW, .isSigned=true })
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_MASK                                  0xFFFF0000
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_SHIFT                                 16
#define TMC6460_ADC_AIN_AIN_W_RAW_AIN_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_AIN_AIN_W_RAW_AIN_MASK, .shift=TMC6460_ADC_AIN_AIN_W_RAW_AIN_SHIFT, .addr=TMC6460_ADC_AIN_AIN_W_RAW, .isSigned=true })

// ADC.STATUS fields
#define TMC6460_ADC_STATUS_ADC_0_READY_MASK                                 0x00000001
#define TMC6460_ADC_STATUS_ADC_0_READY_SHIFT                                0
#define TMC6460_ADC_STATUS_ADC_0_READY_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_0_READY_MASK, .shift=TMC6460_ADC_STATUS_ADC_0_READY_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_ADC_1_READY_MASK                                 0x00000002
#define TMC6460_ADC_STATUS_ADC_1_READY_SHIFT                                1
#define TMC6460_ADC_STATUS_ADC_1_READY_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_1_READY_MASK, .shift=TMC6460_ADC_STATUS_ADC_1_READY_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I1_CLIPPED_MASK                                  0x00000004
#define TMC6460_ADC_STATUS_I1_CLIPPED_SHIFT                                 2
#define TMC6460_ADC_STATUS_I1_CLIPPED_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I1_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_I1_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I2_CLIPPED_MASK                                  0x00000008
#define TMC6460_ADC_STATUS_I2_CLIPPED_SHIFT                                 3
#define TMC6460_ADC_STATUS_I2_CLIPPED_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I2_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_I2_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I3_CLIPPED_MASK                                  0x00000010
#define TMC6460_ADC_STATUS_I3_CLIPPED_SHIFT                                 4
#define TMC6460_ADC_STATUS_I3_CLIPPED_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I3_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_I3_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_U_CLIPPED_MASK                               0x00000020
#define TMC6460_ADC_STATUS_AIN_U_CLIPPED_SHIFT                              5
#define TMC6460_ADC_STATUS_AIN_U_CLIPPED_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_U_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_AIN_U_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_V_CLIPPED_MASK                               0x00000040
#define TMC6460_ADC_STATUS_AIN_V_CLIPPED_SHIFT                              6
#define TMC6460_ADC_STATUS_AIN_V_CLIPPED_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_V_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_AIN_V_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_W_CLIPPED_MASK                               0x00000080
#define TMC6460_ADC_STATUS_AIN_W_CLIPPED_SHIFT                              7
#define TMC6460_ADC_STATUS_AIN_W_CLIPPED_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_W_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_AIN_W_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_CLIPPED_MASK                                 0x00000100
#define TMC6460_ADC_STATUS_AIN_CLIPPED_SHIFT                                8
#define TMC6460_ADC_STATUS_AIN_CLIPPED_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_AIN_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_VM_CLIPPED_MASK                                  0x00000200
#define TMC6460_ADC_STATUS_VM_CLIPPED_SHIFT                                 9
#define TMC6460_ADC_STATUS_VM_CLIPPED_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_VM_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_VM_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_VM_DONE_MASK                                     0x00000400
#define TMC6460_ADC_STATUS_VM_DONE_SHIFT                                    10
#define TMC6460_ADC_STATUS_VM_DONE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_VM_DONE_MASK, .shift=TMC6460_ADC_STATUS_VM_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_TEMP_INT_CLIPPED_MASK                            0x00000800
#define TMC6460_ADC_STATUS_TEMP_INT_CLIPPED_SHIFT                           11
#define TMC6460_ADC_STATUS_TEMP_INT_CLIPPED_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_TEMP_INT_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_TEMP_INT_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_TEMP_INT_DONE_MASK                               0x00001000
#define TMC6460_ADC_STATUS_TEMP_INT_DONE_SHIFT                              12
#define TMC6460_ADC_STATUS_TEMP_INT_DONE_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_TEMP_INT_DONE_MASK, .shift=TMC6460_ADC_STATUS_TEMP_INT_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_TEMP_EXT_CLIPPED_MASK                            0x00002000
#define TMC6460_ADC_STATUS_TEMP_EXT_CLIPPED_SHIFT                           13
#define TMC6460_ADC_STATUS_TEMP_EXT_CLIPPED_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_TEMP_EXT_CLIPPED_MASK, .shift=TMC6460_ADC_STATUS_TEMP_EXT_CLIPPED_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_TEMP_EXT_DONE_MASK                               0x00004000
#define TMC6460_ADC_STATUS_TEMP_EXT_DONE_SHIFT                              14
#define TMC6460_ADC_STATUS_TEMP_EXT_DONE_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_TEMP_EXT_DONE_MASK, .shift=TMC6460_ADC_STATUS_TEMP_EXT_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I1_DONE_MASK                                     0x00008000
#define TMC6460_ADC_STATUS_I1_DONE_SHIFT                                    15
#define TMC6460_ADC_STATUS_I1_DONE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I1_DONE_MASK, .shift=TMC6460_ADC_STATUS_I1_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I2_DONE_MASK                                     0x00010000
#define TMC6460_ADC_STATUS_I2_DONE_SHIFT                                    16
#define TMC6460_ADC_STATUS_I2_DONE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I2_DONE_MASK, .shift=TMC6460_ADC_STATUS_I2_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I3_DONE_MASK                                     0x00020000
#define TMC6460_ADC_STATUS_I3_DONE_SHIFT                                    17
#define TMC6460_ADC_STATUS_I3_DONE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I3_DONE_MASK, .shift=TMC6460_ADC_STATUS_I3_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_U_DONE_MASK                                  0x00040000
#define TMC6460_ADC_STATUS_AIN_U_DONE_SHIFT                                 18
#define TMC6460_ADC_STATUS_AIN_U_DONE_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_U_DONE_MASK, .shift=TMC6460_ADC_STATUS_AIN_U_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_V_DONE_MASK                                  0x00080000
#define TMC6460_ADC_STATUS_AIN_V_DONE_SHIFT                                 19
#define TMC6460_ADC_STATUS_AIN_V_DONE_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_V_DONE_MASK, .shift=TMC6460_ADC_STATUS_AIN_V_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_W_DONE_MASK                                  0x00100000
#define TMC6460_ADC_STATUS_AIN_W_DONE_SHIFT                                 20
#define TMC6460_ADC_STATUS_AIN_W_DONE_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_W_DONE_MASK, .shift=TMC6460_ADC_STATUS_AIN_W_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_AIN_DONE_MASK                                    0x00200000
#define TMC6460_ADC_STATUS_AIN_DONE_SHIFT                                   21
#define TMC6460_ADC_STATUS_AIN_DONE_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_AIN_DONE_MASK, .shift=TMC6460_ADC_STATUS_AIN_DONE_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_ADC_I_VALID_MASK                                 0x00400000
#define TMC6460_ADC_STATUS_ADC_I_VALID_SHIFT                                22
#define TMC6460_ADC_STATUS_ADC_I_VALID_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_I_VALID_MASK, .shift=TMC6460_ADC_STATUS_ADC_I_VALID_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_MASK                               0x00800000
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_SHIFT                              23
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_EXT_VALID_MASK, .shift=TMC6460_ADC_STATUS_ADC_EXT_VALID_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_ADC_I_VALID_EXT_MASK                             0x01000000
#define TMC6460_ADC_STATUS_ADC_I_VALID_EXT_SHIFT                            24
#define TMC6460_ADC_STATUS_ADC_I_VALID_EXT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_I_VALID_EXT_MASK, .shift=TMC6460_ADC_STATUS_ADC_I_VALID_EXT_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_USE_ADC_I_VALID_EXT_MASK                         0x02000000
#define TMC6460_ADC_STATUS_USE_ADC_I_VALID_EXT_SHIFT                        25
#define TMC6460_ADC_STATUS_USE_ADC_I_VALID_EXT_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_USE_ADC_I_VALID_EXT_MASK, .shift=TMC6460_ADC_STATUS_USE_ADC_I_VALID_EXT_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_EXT_MASK                           0x04000000
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_EXT_SHIFT                          26
#define TMC6460_ADC_STATUS_ADC_EXT_VALID_EXT_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_ADC_EXT_VALID_EXT_MASK, .shift=TMC6460_ADC_STATUS_ADC_EXT_VALID_EXT_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_USE_ADC_EXT_VALID_EXT_MASK                       0x08000000
#define TMC6460_ADC_STATUS_USE_ADC_EXT_VALID_EXT_SHIFT                      27
#define TMC6460_ADC_STATUS_USE_ADC_EXT_VALID_EXT_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_USE_ADC_EXT_VALID_EXT_MASK, .shift=TMC6460_ADC_STATUS_USE_ADC_EXT_VALID_EXT_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_NO_ACK_ADC_MASK                                  0x40000000
#define TMC6460_ADC_STATUS_NO_ACK_ADC_SHIFT                                 30
#define TMC6460_ADC_STATUS_NO_ACK_ADC_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_NO_ACK_ADC_MASK, .shift=TMC6460_ADC_STATUS_NO_ACK_ADC_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=false })
#define TMC6460_ADC_STATUS_I123_FAIL_MASK                                   0x80000000
#define TMC6460_ADC_STATUS_I123_FAIL_SHIFT                                  31
#define TMC6460_ADC_STATUS_I123_FAIL_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_ADC_STATUS_I123_FAIL_MASK, .shift=TMC6460_ADC_STATUS_I123_FAIL_SHIFT, .addr=TMC6460_ADC_STATUS, .isSigned=true })

// ADC.I123 fields
#define TMC6460_ADC_I123_I123_MASK                                          0x0000FFFF
#define TMC6460_ADC_I123_I123_SHIFT                                         0
#define TMC6460_ADC_I123_I123_FIELD                                         ((TMC6460RegisterField) {.mask=TMC6460_ADC_I123_I123_MASK, .shift=TMC6460_ADC_I123_I123_SHIFT, .addr=TMC6460_ADC_I123, .isSigned=true })
#define TMC6460_ADC_I123_I123_LIMIT_MASK                                    0xFFFF0000
#define TMC6460_ADC_I123_I123_LIMIT_SHIFT                                   16
#define TMC6460_ADC_I123_I123_LIMIT_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_ADC_I123_I123_LIMIT_MASK, .shift=TMC6460_ADC_I123_I123_LIMIT_SHIFT, .addr=TMC6460_ADC_I123, .isSigned=false })

// MCC_ADC.I_GEN_CONFIG fields
#define TMC6460_MCC_ADC_I_GEN_CONFIG_MEAS_MODE_MASK                         0x00000001
#define TMC6460_MCC_ADC_I_GEN_CONFIG_MEAS_MODE_SHIFT                        0
#define TMC6460_MCC_ADC_I_GEN_CONFIG_MEAS_MODE_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_I_GEN_CONFIG_MEAS_MODE_MASK, .shift=TMC6460_MCC_ADC_I_GEN_CONFIG_MEAS_MODE_SHIFT, .addr=TMC6460_MCC_ADC_I_GEN_CONFIG, .isSigned=false })
#define TMC6460_MCC_ADC_I_GEN_CONFIG_STATUS_MASK                            0x00003000
#define TMC6460_MCC_ADC_I_GEN_CONFIG_STATUS_SHIFT                           12
#define TMC6460_MCC_ADC_I_GEN_CONFIG_STATUS_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_I_GEN_CONFIG_STATUS_MASK, .shift=TMC6460_MCC_ADC_I_GEN_CONFIG_STATUS_SHIFT, .addr=TMC6460_MCC_ADC_I_GEN_CONFIG, .isSigned=false })

// MCC_ADC.IW_IU fields
#define TMC6460_MCC_ADC_IW_IU_IU_MASK                                       0x0000FFFF
#define TMC6460_MCC_ADC_IW_IU_IU_SHIFT                                      0
#define TMC6460_MCC_ADC_IW_IU_IU_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_IW_IU_IU_MASK, .shift=TMC6460_MCC_ADC_IW_IU_IU_SHIFT, .addr=TMC6460_MCC_ADC_IW_IU, .isSigned=true })
#define TMC6460_MCC_ADC_IW_IU_IW_MASK                                       0xFFFF0000
#define TMC6460_MCC_ADC_IW_IU_IW_SHIFT                                      16
#define TMC6460_MCC_ADC_IW_IU_IW_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_IW_IU_IW_MASK, .shift=TMC6460_MCC_ADC_IW_IU_IW_SHIFT, .addr=TMC6460_MCC_ADC_IW_IU, .isSigned=true })

// MCC_ADC.IV fields
#define TMC6460_MCC_ADC_IV_MASK                                             0x0000FFFF
#define TMC6460_MCC_ADC_IV_SHIFT                                            0
#define TMC6460_MCC_ADC_IV_FIELD                                            ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_IV_MASK, .shift=TMC6460_MCC_ADC_IV_SHIFT, .addr=TMC6460_MCC_ADC_IV, .isSigned=true })

// MCC_ADC.CSA_GAIN fields
#define TMC6460_MCC_ADC_CSA_GAIN_CSA_GAIN_MASK                              0x00000003
#define TMC6460_MCC_ADC_CSA_GAIN_CSA_GAIN_SHIFT                             0
#define TMC6460_MCC_ADC_CSA_GAIN_CSA_GAIN_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_CSA_GAIN_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_CSA_GAIN_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_ACT_MASK                          0x0000000C
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_ACT_SHIFT                         2
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_ACT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_ACT_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_ACT_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_2X_EN_MASK                        0x00000010
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_2X_EN_SHIFT                       4
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_2X_EN_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_2X_EN_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_2X_EN_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_3X_EN_MASK                        0x00000020
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_3X_EN_SHIFT                       5
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_3X_EN_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_3X_EN_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_3X_EN_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_4X_EN_MASK                        0x00000040
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_4X_EN_SHIFT                       6
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_4X_EN_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_4X_EN_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_4X_EN_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_HYST_MASK                         0x0000FF00
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_HYST_SHIFT                        8
#define TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_HYST_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_HYST_MASK, .shift=TMC6460_MCC_ADC_CSA_GAIN_DYN_GAIN_HYST_SHIFT, .addr=TMC6460_MCC_ADC_CSA_GAIN, .isSigned=false })

// MCC_ADC.EVENTS fields
#define TMC6460_MCC_ADC_EVENTS_ADC_CLIPPED_MASK                             0x00000001
#define TMC6460_MCC_ADC_EVENTS_ADC_CLIPPED_SHIFT                            0
#define TMC6460_MCC_ADC_EVENTS_ADC_CLIPPED_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_EVENTS_ADC_CLIPPED_MASK, .shift=TMC6460_MCC_ADC_EVENTS_ADC_CLIPPED_SHIFT, .addr=TMC6460_MCC_ADC_EVENTS, .isSigned=false })
#define TMC6460_MCC_ADC_EVENTS_MEAS_DONE_MASK                               0x00000002
#define TMC6460_MCC_ADC_EVENTS_MEAS_DONE_SHIFT                              1
#define TMC6460_MCC_ADC_EVENTS_MEAS_DONE_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_EVENTS_MEAS_DONE_MASK, .shift=TMC6460_MCC_ADC_EVENTS_MEAS_DONE_SHIFT, .addr=TMC6460_MCC_ADC_EVENTS, .isSigned=false })
#define TMC6460_MCC_ADC_EVENTS_TEMP_EXT_LIMIT_EXCEEDED_MASK                 0x00000010
#define TMC6460_MCC_ADC_EVENTS_TEMP_EXT_LIMIT_EXCEEDED_SHIFT                4
#define TMC6460_MCC_ADC_EVENTS_TEMP_EXT_LIMIT_EXCEEDED_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_EVENTS_TEMP_EXT_LIMIT_EXCEEDED_MASK, .shift=TMC6460_MCC_ADC_EVENTS_TEMP_EXT_LIMIT_EXCEEDED_SHIFT, .addr=TMC6460_MCC_ADC_EVENTS, .isSigned=false })
#define TMC6460_MCC_ADC_EVENTS_TEMP_INT_LIMIT_EXCEEDED_MASK                 0x00000020
#define TMC6460_MCC_ADC_EVENTS_TEMP_INT_LIMIT_EXCEEDED_SHIFT                5
#define TMC6460_MCC_ADC_EVENTS_TEMP_INT_LIMIT_EXCEEDED_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_EVENTS_TEMP_INT_LIMIT_EXCEEDED_MASK, .shift=TMC6460_MCC_ADC_EVENTS_TEMP_INT_LIMIT_EXCEEDED_SHIFT, .addr=TMC6460_MCC_ADC_EVENTS, .isSigned=false })
#define TMC6460_MCC_ADC_EVENTS_CURRENT_OVERLOAD_STATUS_MASK                 0x00000040
#define TMC6460_MCC_ADC_EVENTS_CURRENT_OVERLOAD_STATUS_SHIFT                6
#define TMC6460_MCC_ADC_EVENTS_CURRENT_OVERLOAD_STATUS_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_EVENTS_CURRENT_OVERLOAD_STATUS_MASK, .shift=TMC6460_MCC_ADC_EVENTS_CURRENT_OVERLOAD_STATUS_SHIFT, .addr=TMC6460_MCC_ADC_EVENTS, .isSigned=false })

// MCC_ADC.DYN_GAIN_LIMITS_4X_3X fields
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_3X_MASK        0x0000FFFF
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_3X_SHIFT       0
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_3X_FIELD       ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_3X_MASK, .shift=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_3X_SHIFT, .addr=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X, .isSigned=false })
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_4X_MASK        0xFFFF0000
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_4X_SHIFT       16
#define TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_4X_FIELD       ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_4X_MASK, .shift=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X_DYN_GAIN_LIMIT_4X_SHIFT, .addr=TMC6460_MCC_ADC_DYN_GAIN_LIMITS_4X_3X, .isSigned=false })

// MCC_ADC.DYN_GAIN_LIMIT_2X fields
#define TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X_MASK                              0x0000FFFF
#define TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X_SHIFT                             0
#define TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X_MASK, .shift=TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X_SHIFT, .addr=TMC6460_MCC_ADC_DYN_GAIN_LIMIT_2X, .isSigned=false })

// MCC_ADC.TEMP_LIMITS fields
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_EXT_LIMIT_MASK                     0x0000FFFF
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_EXT_LIMIT_SHIFT                    0
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_EXT_LIMIT_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_EXT_LIMIT_MASK, .shift=TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_EXT_LIMIT_SHIFT, .addr=TMC6460_MCC_ADC_TEMP_LIMITS, .isSigned=false })
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_INT_LIMIT_MASK                     0xFFFF0000
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_INT_LIMIT_SHIFT                    16
#define TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_INT_LIMIT_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_INT_LIMIT_MASK, .shift=TMC6460_MCC_ADC_TEMP_LIMITS_TEMP_INT_LIMIT_SHIFT, .addr=TMC6460_MCC_ADC_TEMP_LIMITS, .isSigned=false })

// MCC_ADC.CURRENT_OVERLOAD fields
#define TMC6460_MCC_ADC_CURRENT_OVERLOAD_MASK                               0x0000FFFF
#define TMC6460_MCC_ADC_CURRENT_OVERLOAD_SHIFT                              0
#define TMC6460_MCC_ADC_CURRENT_OVERLOAD_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_MCC_ADC_CURRENT_OVERLOAD_MASK, .shift=TMC6460_MCC_ADC_CURRENT_OVERLOAD_SHIFT, .addr=TMC6460_MCC_ADC_CURRENT_OVERLOAD, .isSigned=false })

// MCC_CONFIG.MOTOR_MOTION fields
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_N_POLE_PAIRS_MASK                   0x0000007F
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_N_POLE_PAIRS_SHIFT                  0
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_N_POLE_PAIRS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_N_POLE_PAIRS_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_N_POLE_PAIRS_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTOR_TYPE_MASK                     0x00000180
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTOR_TYPE_SHIFT                    7
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTOR_TYPE_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTOR_TYPE_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTOR_TYPE_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTION_MODE_MASK                    0x00001E00
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTION_MODE_SHIFT                   9
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTION_MODE_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTION_MODE_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_MOTION_MODE_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_MODE_MASK                      0x00002000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_MODE_SHIFT                     13
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_MODE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_MODE_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_MODE_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_EN_MASK                        0x00004000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_EN_SHIFT                       14
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_EN_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_EN_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_USE_PHI_E_MASK                 0x00008000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_USE_PHI_E_SHIFT                15
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_USE_PHI_E_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_USE_PHI_E_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_RAMP_USE_PHI_E_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_ACC_EN_MASK               0x00010000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_ACC_EN_SHIFT              16
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_ACC_EN_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_ACC_EN_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_ACC_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_COULOMB_FRICTION_EN_MASK  0x00020000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_COULOMB_FRICTION_EN_SHIFT 17
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_COULOMB_FRICTION_EN_FIELD ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_COULOMB_FRICTION_EN_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_COULOMB_FRICTION_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_VISC_FRIC_EN_MASK         0x00040000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_VISC_FRIC_EN_SHIFT        18
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_VISC_FRIC_EN_FIELD        ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_VISC_FRIC_EN_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_TORQUE_FF_VISC_FRIC_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_VELOCITY_FF_EN_MASK                 0x00080000
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_VELOCITY_FF_EN_SHIFT                19
#define TMC6460_MCC_CONFIG_MOTOR_MOTION_VELOCITY_FF_EN_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MOTOR_MOTION_VELOCITY_FF_EN_MASK, .shift=TMC6460_MCC_CONFIG_MOTOR_MOTION_VELOCITY_FF_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_MOTOR_MOTION, .isSigned=false })

// MCC_CONFIG.GDRV fields
#define TMC6460_MCC_CONFIG_GDRV_SLEW_RATE_MASK                              0x00000003
#define TMC6460_MCC_CONFIG_GDRV_SLEW_RATE_SHIFT                             0
#define TMC6460_MCC_CONFIG_GDRV_SLEW_RATE_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_SLEW_RATE_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_SLEW_RATE_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_LS_RES_ON_MASK                              0x00000030
#define TMC6460_MCC_CONFIG_GDRV_LS_RES_ON_SHIFT                             4
#define TMC6460_MCC_CONFIG_GDRV_LS_RES_ON_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_LS_RES_ON_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_LS_RES_ON_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_OCP_DETECTION_MODE_MASK                     0x00000200
#define TMC6460_MCC_CONFIG_GDRV_OCP_DETECTION_MODE_SHIFT                    9
#define TMC6460_MCC_CONFIG_GDRV_OCP_DETECTION_MODE_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_OCP_DETECTION_MODE_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_OCP_DETECTION_MODE_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_OCP_DEGLITCH_MASK                           0x00000C00
#define TMC6460_MCC_CONFIG_GDRV_OCP_DEGLITCH_SHIFT                          10
#define TMC6460_MCC_CONFIG_GDRV_OCP_DEGLITCH_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_OCP_DEGLITCH_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_OCP_DEGLITCH_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_OCP_AUTORETRY_MASK                          0x00003000
#define TMC6460_MCC_CONFIG_GDRV_OCP_AUTORETRY_SHIFT                         12
#define TMC6460_MCC_CONFIG_GDRV_OCP_AUTORETRY_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_OCP_AUTORETRY_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_OCP_AUTORETRY_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_DRV_EN_BIT_MASK                             0x00010000
#define TMC6460_MCC_CONFIG_GDRV_DRV_EN_BIT_SHIFT                            16
#define TMC6460_MCC_CONFIG_GDRV_DRV_EN_BIT_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_DRV_EN_BIT_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_DRV_EN_BIT_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_OVERTEMP_LATCH_MASK                         0x00100000
#define TMC6460_MCC_CONFIG_GDRV_OVERTEMP_LATCH_SHIFT                        20
#define TMC6460_MCC_CONFIG_GDRV_OVERTEMP_LATCH_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_OVERTEMP_LATCH_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_OVERTEMP_LATCH_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_USE_INTERNAL_R_REF_MASK                     0x01000000
#define TMC6460_MCC_CONFIG_GDRV_USE_INTERNAL_R_REF_SHIFT                    24
#define TMC6460_MCC_CONFIG_GDRV_USE_INTERNAL_R_REF_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_USE_INTERNAL_R_REF_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_USE_INTERNAL_R_REF_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_LP_MODE_EN_MASK                             0x10000000
#define TMC6460_MCC_CONFIG_GDRV_LP_MODE_EN_SHIFT                            28
#define TMC6460_MCC_CONFIG_GDRV_LP_MODE_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_LP_MODE_EN_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_LP_MODE_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })
#define TMC6460_MCC_CONFIG_GDRV_CHARGE_PUMP_EN_MASK                         0x80000000
#define TMC6460_MCC_CONFIG_GDRV_CHARGE_PUMP_EN_SHIFT                        31
#define TMC6460_MCC_CONFIG_GDRV_CHARGE_PUMP_EN_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_GDRV_CHARGE_PUMP_EN_MASK, .shift=TMC6460_MCC_CONFIG_GDRV_CHARGE_PUMP_EN_SHIFT, .addr=TMC6460_MCC_CONFIG_GDRV, .isSigned=false })

// MCC_CONFIG.PWM fields
#define TMC6460_MCC_CONFIG_PWM_CHOP_MASK                                    0x00000007
#define TMC6460_MCC_CONFIG_PWM_CHOP_SHIFT                                   0
#define TMC6460_MCC_CONFIG_PWM_CHOP_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_PWM_CHOP_MASK, .shift=TMC6460_MCC_CONFIG_PWM_CHOP_SHIFT, .addr=TMC6460_MCC_CONFIG_PWM, .isSigned=false })
#define TMC6460_MCC_CONFIG_PWM_SV_MODE_MASK                                 0x00000030
#define TMC6460_MCC_CONFIG_PWM_SV_MODE_SHIFT                                4
#define TMC6460_MCC_CONFIG_PWM_SV_MODE_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_PWM_SV_MODE_MASK, .shift=TMC6460_MCC_CONFIG_PWM_SV_MODE_SHIFT, .addr=TMC6460_MCC_CONFIG_PWM, .isSigned=false })
#define TMC6460_MCC_CONFIG_PWM_FLAT_BOTTOM_OFFSET_MASK                      0xFFFF0000
#define TMC6460_MCC_CONFIG_PWM_FLAT_BOTTOM_OFFSET_SHIFT                     16
#define TMC6460_MCC_CONFIG_PWM_FLAT_BOTTOM_OFFSET_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_PWM_FLAT_BOTTOM_OFFSET_MASK, .shift=TMC6460_MCC_CONFIG_PWM_FLAT_BOTTOM_OFFSET_SHIFT, .addr=TMC6460_MCC_CONFIG_PWM, .isSigned=false })

// MCC_CONFIG.PWM_PERIOD fields
#define TMC6460_MCC_CONFIG_PWM_PERIOD_MAX_COUNT_MASK                        0x0000FFFF
#define TMC6460_MCC_CONFIG_PWM_PERIOD_MAX_COUNT_SHIFT                       0
#define TMC6460_MCC_CONFIG_PWM_PERIOD_MAX_COUNT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_PWM_PERIOD_MAX_COUNT_MASK, .shift=TMC6460_MCC_CONFIG_PWM_PERIOD_MAX_COUNT_SHIFT, .addr=TMC6460_MCC_CONFIG_PWM_PERIOD, .isSigned=false })
#define TMC6460_MCC_CONFIG_PWM_PERIOD_AUTO_KIRCHOFF_LIM_MASK                0xFFFF0000
#define TMC6460_MCC_CONFIG_PWM_PERIOD_AUTO_KIRCHOFF_LIM_SHIFT               16
#define TMC6460_MCC_CONFIG_PWM_PERIOD_AUTO_KIRCHOFF_LIM_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_PWM_PERIOD_AUTO_KIRCHOFF_LIM_MASK, .shift=TMC6460_MCC_CONFIG_PWM_PERIOD_AUTO_KIRCHOFF_LIM_SHIFT, .addr=TMC6460_MCC_CONFIG_PWM_PERIOD, .isSigned=false })

// MCC_CONFIG.BRAKE_CHOPPER_LIMITS fields
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_LOWER_SWITCH_LIM_MASK       0x0000FFFF
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_LOWER_SWITCH_LIM_SHIFT      0
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_LOWER_SWITCH_LIM_FIELD      ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_LOWER_SWITCH_LIM_MASK, .shift=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_LOWER_SWITCH_LIM_SHIFT, .addr=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS, .isSigned=false })
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_UPPER_SWITCH_LIM_MASK       0xFFFF0000
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_UPPER_SWITCH_LIM_SHIFT      16
#define TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_UPPER_SWITCH_LIM_FIELD      ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_UPPER_SWITCH_LIM_MASK, .shift=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS_UPPER_SWITCH_LIM_SHIFT, .addr=TMC6460_MCC_CONFIG_BRAKE_CHOPPER_LIMITS, .isSigned=false })

// MCC_CONFIG.MCC_STATUS fields
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_STATUS_MASK                0x00000001
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_STATUS_SHIFT               0
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_STATUS_MASK                0x00000002
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_STATUS_SHIFT               1
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_STATUS_MASK                0x00000004
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_STATUS_SHIFT               2
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_STATUS_MASK                0x00000008
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_STATUS_SHIFT               3
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_STATUS_MASK                0x00000010
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_STATUS_SHIFT               4
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_STATUS_MASK                0x00000020
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_STATUS_SHIFT               5
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_STATUS_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_STATUS_MASK              0x00000040
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_STATUS_SHIFT             6
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_STATUS_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_STATUS_MASK              0x00000080
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_STATUS_SHIFT             7
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_STATUS_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_STATUS_MASK              0x00000100
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_STATUS_SHIFT             8
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_STATUS_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_STATUS_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_STATUS_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_EVENT_MASK                 0x00010000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_EVENT_SHIFT                16
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH1_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_EVENT_MASK                 0x00020000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_EVENT_SHIFT                17
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH2_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_EVENT_MASK                 0x00040000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_EVENT_SHIFT                18
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2G_CH3_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_EVENT_MASK                 0x00080000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_EVENT_SHIFT                19
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH1_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_EVENT_MASK                 0x00100000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_EVENT_SHIFT                20
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH2_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_EVENT_MASK                 0x00200000
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_EVENT_SHIFT                21
#define TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_EVENT_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_SHRT2V_CH3_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_EVENT_MASK               0x00400000
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_EVENT_SHIFT              22
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_EVENT_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH1_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_EVENT_MASK               0x00800000
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_EVENT_SHIFT              23
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_EVENT_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH2_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_EVENT_MASK               0x01000000
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_EVENT_SHIFT              24
#define TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_EVENT_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_EVENT_MASK, .shift=TMC6460_MCC_CONFIG_MCC_STATUS_OVERTEMP_CH3_EVENT_SHIFT, .addr=TMC6460_MCC_CONFIG_MCC_STATUS, .isSigned=false })

// MCC_CONFIG.TORQUE_FF_ACC_CONFIG fields
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_GAIN_MASK          0x0000FFFF
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_GAIN_SHIFT         0
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_GAIN_FIELD         ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_GAIN_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_GAIN_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG, .isSigned=true })
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_SHIFT_MASK         0x00070000
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_SHIFT_SHIFT        16
#define TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_SHIFT_FIELD        ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_SHIFT_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG_RAMP_ACC_SHIFT_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FF_ACC_CONFIG, .isSigned=false })

// MCC_CONFIG.TORQUE_FF_VISC_FRIC_CONFIG fields
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_GAIN_MASK    0x0000FFFF
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_GAIN_SHIFT   0
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_GAIN_FIELD   ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_GAIN_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_GAIN_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG, .isSigned=true })
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_SHIFT_MASK   0x00070000
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_SHIFT_SHIFT  16
#define TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_SHIFT_FIELD  ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_SHIFT_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG_RAMP_VEL_SHIFT_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FF_VISC_FRIC_CONFIG, .isSigned=false })

// MCC_CONFIG.TORQUE_FF_COULOMB_FRIC fields
#define TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC_MASK                      0x0000FFFF
#define TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC_SHIFT                     0
#define TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FF_COULOMB_FRIC, .isSigned=true })

// MCC_CONFIG.TORQUE_FEEDFORWARD fields
#define TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD_MASK                          0x0000FFFF
#define TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD_SHIFT                         0
#define TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD_MASK, .shift=TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD_SHIFT, .addr=TMC6460_MCC_CONFIG_TORQUE_FEEDFORWARD, .isSigned=true })

// FOC.PID_CONFIG fields
#define TMC6460_FOC_PID_CONFIG_KEEP_POS_TARGET_MASK                         0x00000001
#define TMC6460_FOC_PID_CONFIG_KEEP_POS_TARGET_SHIFT                        0
#define TMC6460_FOC_PID_CONFIG_KEEP_POS_TARGET_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_KEEP_POS_TARGET_MASK, .shift=TMC6460_FOC_PID_CONFIG_KEEP_POS_TARGET_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_OVERWRITE_TARGET_MASK                        0x00000002
#define TMC6460_FOC_PID_CONFIG_OVERWRITE_TARGET_SHIFT                       1
#define TMC6460_FOC_PID_CONFIG_OVERWRITE_TARGET_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_OVERWRITE_TARGET_MASK, .shift=TMC6460_FOC_PID_CONFIG_OVERWRITE_TARGET_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_P_MASK                          0x00000004
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_P_SHIFT                         2
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_P_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_CURRENT_NORM_P_MASK, .shift=TMC6460_FOC_PID_CONFIG_CURRENT_NORM_P_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_I_MASK                          0x00000008
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_I_SHIFT                         3
#define TMC6460_FOC_PID_CONFIG_CURRENT_NORM_I_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_CURRENT_NORM_I_MASK, .shift=TMC6460_FOC_PID_CONFIG_CURRENT_NORM_I_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_P_MASK                         0x00000030
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_P_SHIFT                        4
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_P_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_P_MASK, .shift=TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_P_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_I_MASK                         0x000000C0
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_I_SHIFT                        6
#define TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_I_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_I_MASK, .shift=TMC6460_FOC_PID_CONFIG_VELOCITY_NORM_I_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_P_MASK                         0x00000300
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_P_SHIFT                        8
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_P_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_POSITION_NORM_P_MASK, .shift=TMC6460_FOC_PID_CONFIG_POSITION_NORM_P_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_I_MASK                         0x00000C00
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_I_SHIFT                        10
#define TMC6460_FOC_PID_CONFIG_POSITION_NORM_I_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_POSITION_NORM_I_MASK, .shift=TMC6460_FOC_PID_CONFIG_POSITION_NORM_I_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_VELOCITY_SHIFT_MASK                          0x0000F000
#define TMC6460_FOC_PID_CONFIG_VELOCITY_SHIFT_SHIFT                         12
#define TMC6460_FOC_PID_CONFIG_VELOCITY_SHIFT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_VELOCITY_SHIFT_MASK, .shift=TMC6460_FOC_PID_CONFIG_VELOCITY_SHIFT_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })
#define TMC6460_FOC_PID_CONFIG_POSITION_SAMPLING_MASK                       0x007F0000
#define TMC6460_FOC_PID_CONFIG_POSITION_SAMPLING_SHIFT                      16
#define TMC6460_FOC_PID_CONFIG_POSITION_SAMPLING_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_CONFIG_POSITION_SAMPLING_MASK, .shift=TMC6460_FOC_PID_CONFIG_POSITION_SAMPLING_SHIFT, .addr=TMC6460_FOC_PID_CONFIG, .isSigned=false })

// FOC.PID_U_S_MAX fields
#define TMC6460_FOC_PID_U_S_MAX_U_S_MAX_MASK                                0x0000FFFF
#define TMC6460_FOC_PID_U_S_MAX_U_S_MAX_SHIFT                               0
#define TMC6460_FOC_PID_U_S_MAX_U_S_MAX_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_U_S_MAX_U_S_MAX_MASK, .shift=TMC6460_FOC_PID_U_S_MAX_U_S_MAX_SHIFT, .addr=TMC6460_FOC_PID_U_S_MAX, .isSigned=false })

// FOC.PID_FLUX_COEFF fields
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_I_MASK                              0x0000FFFF
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_I_SHIFT                             0
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_I_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FLUX_COEFF_FLUX_I_MASK, .shift=TMC6460_FOC_PID_FLUX_COEFF_FLUX_I_SHIFT, .addr=TMC6460_FOC_PID_FLUX_COEFF, .isSigned=true })
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_P_MASK                              0xFFFF0000
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_P_SHIFT                             16
#define TMC6460_FOC_PID_FLUX_COEFF_FLUX_P_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FLUX_COEFF_FLUX_P_MASK, .shift=TMC6460_FOC_PID_FLUX_COEFF_FLUX_P_SHIFT, .addr=TMC6460_FOC_PID_FLUX_COEFF, .isSigned=true })

// FOC.PID_TORQUE_COEFF fields
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_I_MASK                          0x0000FFFF
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_I_SHIFT                         0
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_I_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_I_MASK, .shift=TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_I_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_COEFF, .isSigned=true })
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_P_MASK                          0xFFFF0000
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_P_SHIFT                         16
#define TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_P_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_P_MASK, .shift=TMC6460_FOC_PID_TORQUE_COEFF_TORQUE_P_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_COEFF, .isSigned=true })

// FOC.PID_FIELDWEAK_COEFF fields
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_I_MASK                    0x0000FFFF
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_I_SHIFT                   0
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_I_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_I_MASK, .shift=TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_I_SHIFT, .addr=TMC6460_FOC_PID_FIELDWEAK_COEFF, .isSigned=true })
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_P_MASK                    0xFFFF0000
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_P_SHIFT                   16
#define TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_P_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_P_MASK, .shift=TMC6460_FOC_PID_FIELDWEAK_COEFF_FIELDWEAK_P_SHIFT, .addr=TMC6460_FOC_PID_FIELDWEAK_COEFF, .isSigned=true })

// FOC.PID_VELOCITY_COEFF fields
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_I_MASK                      0x0000FFFF
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_I_SHIFT                     0
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_I_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_I_MASK, .shift=TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_I_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_COEFF, .isSigned=true })
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_P_MASK                      0xFFFF0000
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_P_SHIFT                     16
#define TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_P_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_P_MASK, .shift=TMC6460_FOC_PID_VELOCITY_COEFF_VELOCITY_P_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_COEFF, .isSigned=true })

// FOC.PID_POSITION_COEFF fields
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_I_MASK                      0x0000FFFF
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_I_SHIFT                     0
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_I_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_COEFF_POSITION_I_MASK, .shift=TMC6460_FOC_PID_POSITION_COEFF_POSITION_I_SHIFT, .addr=TMC6460_FOC_PID_POSITION_COEFF, .isSigned=true })
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_P_MASK                      0xFFFF0000
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_P_SHIFT                     16
#define TMC6460_FOC_PID_POSITION_COEFF_POSITION_P_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_COEFF_POSITION_P_MASK, .shift=TMC6460_FOC_PID_POSITION_COEFF_POSITION_P_SHIFT, .addr=TMC6460_FOC_PID_POSITION_COEFF, .isSigned=true })

// FOC.PID_POSITION_TOLERANCE fields
#define TMC6460_FOC_PID_POSITION_TOLERANCE_MASK                             0x7FFFFFFF
#define TMC6460_FOC_PID_POSITION_TOLERANCE_SHIFT                            0
#define TMC6460_FOC_PID_POSITION_TOLERANCE_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_TOLERANCE_MASK, .shift=TMC6460_FOC_PID_POSITION_TOLERANCE_SHIFT, .addr=TMC6460_FOC_PID_POSITION_TOLERANCE, .isSigned=false })

// FOC.PID_POSITION_TOLERANCE_DELAY fields
#define TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY_MASK                       0x0000FFFF
#define TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY_SHIFT                      0
#define TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY_MASK, .shift=TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY_SHIFT, .addr=TMC6460_FOC_PID_POSITION_TOLERANCE_DELAY, .isSigned=false })

// FOC.PID_UQ_UD_LIMITS fields
#define TMC6460_FOC_PID_UQ_UD_LIMITS_MASK                                   0x0000FFFF
#define TMC6460_FOC_PID_UQ_UD_LIMITS_SHIFT                                  0
#define TMC6460_FOC_PID_UQ_UD_LIMITS_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_UQ_UD_LIMITS_MASK, .shift=TMC6460_FOC_PID_UQ_UD_LIMITS_SHIFT, .addr=TMC6460_FOC_PID_UQ_UD_LIMITS, .isSigned=false })

// FOC.PID_TORQUE_FLUX_LIMITS fields
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_FLUX_MASK                        0x00007FFF
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_FLUX_SHIFT                       0
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_FLUX_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_FLUX_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_FLUX_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS, .isSigned=false })
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_TORQUE_MASK                      0x7FFF0000
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_TORQUE_SHIFT                     16
#define TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_TORQUE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_TORQUE_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS_TORQUE_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_LIMITS, .isSigned=false })

// FOC.PID_VELOCITY_LIMIT fields
#define TMC6460_FOC_PID_VELOCITY_LIMIT_MASK                                 0x7FFFFFFF
#define TMC6460_FOC_PID_VELOCITY_LIMIT_SHIFT                                0
#define TMC6460_FOC_PID_VELOCITY_LIMIT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_LIMIT_MASK, .shift=TMC6460_FOC_PID_VELOCITY_LIMIT_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_LIMIT, .isSigned=false })

// FOC.PID_POSITION_LIMIT_LOW fields
#define TMC6460_FOC_PID_POSITION_LIMIT_LOW_MASK                             0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_LIMIT_LOW_SHIFT                            0
#define TMC6460_FOC_PID_POSITION_LIMIT_LOW_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_LIMIT_LOW_MASK, .shift=TMC6460_FOC_PID_POSITION_LIMIT_LOW_SHIFT, .addr=TMC6460_FOC_PID_POSITION_LIMIT_LOW, .isSigned=true })

// FOC.PID_POSITION_LIMIT_HIGH fields
#define TMC6460_FOC_PID_POSITION_LIMIT_HIGH_MASK                            0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_LIMIT_HIGH_SHIFT                           0
#define TMC6460_FOC_PID_POSITION_LIMIT_HIGH_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_LIMIT_HIGH_MASK, .shift=TMC6460_FOC_PID_POSITION_LIMIT_HIGH_SHIFT, .addr=TMC6460_FOC_PID_POSITION_LIMIT_HIGH, .isSigned=true })

// FOC.PID_TORQUE_FLUX_TARGET fields
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_FLUX_MASK                        0x0000FFFF
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_FLUX_SHIFT                       0
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_FLUX_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_TARGET_FLUX_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_TARGET_FLUX_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_TARGET, .isSigned=true })
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_TORQUE_MASK                      0xFFFF0000
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_TORQUE_SHIFT                     16
#define TMC6460_FOC_PID_TORQUE_FLUX_TARGET_TORQUE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_TARGET_TORQUE_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_TARGET_TORQUE_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_TARGET, .isSigned=true })

// FOC.PID_TORQUE_FLUX_OFFSET fields
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_FLUX_MASK                        0x0000FFFF
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_FLUX_SHIFT                       0
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_FLUX_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_FLUX_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_FLUX_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET, .isSigned=true })
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_TORQUE_MASK                      0xFFFF0000
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_TORQUE_SHIFT                     16
#define TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_TORQUE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_TORQUE_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET_TORQUE_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_OFFSET, .isSigned=true })

// FOC.PID_VELOCITY_TARGET fields
#define TMC6460_FOC_PID_VELOCITY_TARGET_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_VELOCITY_TARGET_SHIFT                               0
#define TMC6460_FOC_PID_VELOCITY_TARGET_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_TARGET_MASK, .shift=TMC6460_FOC_PID_VELOCITY_TARGET_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_TARGET, .isSigned=true })

// FOC.PID_VELOCITY_OFFSET fields
#define TMC6460_FOC_PID_VELOCITY_OFFSET_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_VELOCITY_OFFSET_SHIFT                               0
#define TMC6460_FOC_PID_VELOCITY_OFFSET_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_OFFSET_MASK, .shift=TMC6460_FOC_PID_VELOCITY_OFFSET_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_OFFSET, .isSigned=true })

// FOC.PID_POSITION_TARGET fields
#define TMC6460_FOC_PID_POSITION_TARGET_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_TARGET_SHIFT                               0
#define TMC6460_FOC_PID_POSITION_TARGET_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_TARGET_MASK, .shift=TMC6460_FOC_PID_POSITION_TARGET_SHIFT, .addr=TMC6460_FOC_PID_POSITION_TARGET, .isSigned=true })

// FOC.PID_TORQUE_FLUX_ACTUAL fields
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_FLUX_MASK                        0x0000FFFF
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_FLUX_SHIFT                       0
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_FLUX_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_FLUX_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_FLUX_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL, .isSigned=true })
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_TORQUE_MASK                      0xFFFF0000
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_TORQUE_SHIFT                     16
#define TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_TORQUE_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_TORQUE_MASK, .shift=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL_TORQUE_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_FLUX_ACTUAL, .isSigned=true })

// FOC.PID_VELOCITY_ACTUAL fields
#define TMC6460_FOC_PID_VELOCITY_ACTUAL_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_VELOCITY_ACTUAL_SHIFT                               0
#define TMC6460_FOC_PID_VELOCITY_ACTUAL_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_ACTUAL_MASK, .shift=TMC6460_FOC_PID_VELOCITY_ACTUAL_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_ACTUAL, .isSigned=true })

// FOC.PID_POSITION_ACTUAL fields
#define TMC6460_FOC_PID_POSITION_ACTUAL_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_ACTUAL_SHIFT                               0
#define TMC6460_FOC_PID_POSITION_ACTUAL_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_ACTUAL_MASK, .shift=TMC6460_FOC_PID_POSITION_ACTUAL_SHIFT, .addr=TMC6460_FOC_PID_POSITION_ACTUAL, .isSigned=true })

// FOC.PID_POSITION_ACTUAL_OFFSET fields
#define TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET_MASK                         0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET_SHIFT                        0
#define TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET_MASK, .shift=TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET_SHIFT, .addr=TMC6460_FOC_PID_POSITION_ACTUAL_OFFSET, .isSigned=true })

// FOC.PID_TORQUE_ERROR fields
#define TMC6460_FOC_PID_TORQUE_ERROR_MASK                                   0x0000FFFF
#define TMC6460_FOC_PID_TORQUE_ERROR_SHIFT                                  0
#define TMC6460_FOC_PID_TORQUE_ERROR_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_ERROR_MASK, .shift=TMC6460_FOC_PID_TORQUE_ERROR_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_ERROR, .isSigned=true })

// FOC.PID_FLUX_ERROR fields
#define TMC6460_FOC_PID_FLUX_ERROR_MASK                                     0x0000FFFF
#define TMC6460_FOC_PID_FLUX_ERROR_SHIFT                                    0
#define TMC6460_FOC_PID_FLUX_ERROR_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FLUX_ERROR_MASK, .shift=TMC6460_FOC_PID_FLUX_ERROR_SHIFT, .addr=TMC6460_FOC_PID_FLUX_ERROR, .isSigned=true })

// FOC.PID_VELOCITY_ERROR fields
#define TMC6460_FOC_PID_VELOCITY_ERROR_MASK                                 0xFFFFFFFF
#define TMC6460_FOC_PID_VELOCITY_ERROR_SHIFT                                0
#define TMC6460_FOC_PID_VELOCITY_ERROR_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_ERROR_MASK, .shift=TMC6460_FOC_PID_VELOCITY_ERROR_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_ERROR, .isSigned=true })

// FOC.PID_VELOCITY_ERROR_MAX fields
#define TMC6460_FOC_PID_VELOCITY_ERROR_MAX_MASK                             0x7FFFFFFF
#define TMC6460_FOC_PID_VELOCITY_ERROR_MAX_SHIFT                            0
#define TMC6460_FOC_PID_VELOCITY_ERROR_MAX_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_ERROR_MAX_MASK, .shift=TMC6460_FOC_PID_VELOCITY_ERROR_MAX_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_ERROR_MAX, .isSigned=false })

// FOC.PID_POSITION_ERROR fields
#define TMC6460_FOC_PID_POSITION_ERROR_MASK                                 0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_ERROR_SHIFT                                0
#define TMC6460_FOC_PID_POSITION_ERROR_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_ERROR_MASK, .shift=TMC6460_FOC_PID_POSITION_ERROR_SHIFT, .addr=TMC6460_FOC_PID_POSITION_ERROR, .isSigned=true })

// FOC.PID_POSITION_ERROR_MAX fields
#define TMC6460_FOC_PID_POSITION_ERROR_MAX_MASK                             0x7FFFFFFF
#define TMC6460_FOC_PID_POSITION_ERROR_MAX_SHIFT                            0
#define TMC6460_FOC_PID_POSITION_ERROR_MAX_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_ERROR_MAX_MASK, .shift=TMC6460_FOC_PID_POSITION_ERROR_MAX_SHIFT, .addr=TMC6460_FOC_PID_POSITION_ERROR_MAX, .isSigned=false })

// FOC.PID_TORQUE_INTEGRATOR fields
#define TMC6460_FOC_PID_TORQUE_INTEGRATOR_MASK                              0xFFFFFFFF
#define TMC6460_FOC_PID_TORQUE_INTEGRATOR_SHIFT                             0
#define TMC6460_FOC_PID_TORQUE_INTEGRATOR_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_TORQUE_INTEGRATOR_MASK, .shift=TMC6460_FOC_PID_TORQUE_INTEGRATOR_SHIFT, .addr=TMC6460_FOC_PID_TORQUE_INTEGRATOR, .isSigned=true })

// FOC.PID_FLUX_INTEGRATOR fields
#define TMC6460_FOC_PID_FLUX_INTEGRATOR_MASK                                0xFFFFFFFF
#define TMC6460_FOC_PID_FLUX_INTEGRATOR_SHIFT                               0
#define TMC6460_FOC_PID_FLUX_INTEGRATOR_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_FLUX_INTEGRATOR_MASK, .shift=TMC6460_FOC_PID_FLUX_INTEGRATOR_SHIFT, .addr=TMC6460_FOC_PID_FLUX_INTEGRATOR, .isSigned=true })

// FOC.PID_VELOCITY_INTEGRATOR fields
#define TMC6460_FOC_PID_VELOCITY_INTEGRATOR_MASK                            0xFFFFFFFF
#define TMC6460_FOC_PID_VELOCITY_INTEGRATOR_SHIFT                           0
#define TMC6460_FOC_PID_VELOCITY_INTEGRATOR_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_VELOCITY_INTEGRATOR_MASK, .shift=TMC6460_FOC_PID_VELOCITY_INTEGRATOR_SHIFT, .addr=TMC6460_FOC_PID_VELOCITY_INTEGRATOR, .isSigned=true })

// FOC.PID_POSITION_INTEGRATOR fields
#define TMC6460_FOC_PID_POSITION_INTEGRATOR_MASK                            0xFFFFFFFF
#define TMC6460_FOC_PID_POSITION_INTEGRATOR_SHIFT                           0
#define TMC6460_FOC_PID_POSITION_INTEGRATOR_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_PID_POSITION_INTEGRATOR_MASK, .shift=TMC6460_FOC_PID_POSITION_INTEGRATOR_SHIFT, .addr=TMC6460_FOC_PID_POSITION_INTEGRATOR, .isSigned=true })

// FOC.PIDIN_TORQUE_FLUX_TARGET fields
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_FLUX_MASK                      0x0000FFFF
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_FLUX_SHIFT                     0
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_FLUX_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_FLUX_MASK, .shift=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_FLUX_SHIFT, .addr=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET, .isSigned=true })
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_TORQUE_MASK                    0xFFFF0000
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_TORQUE_SHIFT                   16
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_TORQUE_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_TORQUE_MASK, .shift=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_TORQUE_SHIFT, .addr=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET, .isSigned=true })

// FOC.PIDIN_VELOCITY_TARGET fields
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_MASK                              0xFFFFFFFF
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_SHIFT                             0
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_VELOCITY_TARGET_MASK, .shift=TMC6460_FOC_PIDIN_VELOCITY_TARGET_SHIFT, .addr=TMC6460_FOC_PIDIN_VELOCITY_TARGET, .isSigned=true })

// FOC.PIDIN_POSITION_TARGET fields
#define TMC6460_FOC_PIDIN_POSITION_TARGET_MASK                              0xFFFFFFFF
#define TMC6460_FOC_PIDIN_POSITION_TARGET_SHIFT                             0
#define TMC6460_FOC_PIDIN_POSITION_TARGET_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_POSITION_TARGET_MASK, .shift=TMC6460_FOC_PIDIN_POSITION_TARGET_SHIFT, .addr=TMC6460_FOC_PIDIN_POSITION_TARGET, .isSigned=true })

// FOC.PIDIN_TORQUE_FLUX_TARGET_LIMITED fields
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_FLUX_MASK              0x0000FFFF
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_FLUX_SHIFT             0
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_FLUX_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_FLUX_MASK, .shift=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_FLUX_SHIFT, .addr=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED, .isSigned=true })
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_TORQUE_MASK            0xFFFF0000
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_TORQUE_SHIFT           16
#define TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_TORQUE_FIELD           ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_TORQUE_MASK, .shift=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED_TORQUE_SHIFT, .addr=TMC6460_FOC_PIDIN_TORQUE_FLUX_TARGET_LIMITED, .isSigned=true })

// FOC.PIDIN_VELOCITY_TARGET_LIMITED fields
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED_MASK                      0xFFFFFFFF
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED_SHIFT                     0
#define TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED_MASK, .shift=TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED_SHIFT, .addr=TMC6460_FOC_PIDIN_VELOCITY_TARGET_LIMITED, .isSigned=true })

// FOC.PIDIN_POSITION_TARGET_LIMITED fields
#define TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED_MASK                      0xFFFFFFFF
#define TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED_SHIFT                     0
#define TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED_MASK, .shift=TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED_SHIFT, .addr=TMC6460_FOC_PIDIN_POSITION_TARGET_LIMITED, .isSigned=true })

// FOC.FOC_IBETA_IALPHA fields
#define TMC6460_FOC_FOC_IBETA_IALPHA_IALPHA_MASK                            0x0000FFFF
#define TMC6460_FOC_FOC_IBETA_IALPHA_IALPHA_SHIFT                           0
#define TMC6460_FOC_FOC_IBETA_IALPHA_IALPHA_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_IBETA_IALPHA_IALPHA_MASK, .shift=TMC6460_FOC_FOC_IBETA_IALPHA_IALPHA_SHIFT, .addr=TMC6460_FOC_FOC_IBETA_IALPHA, .isSigned=true })
#define TMC6460_FOC_FOC_IBETA_IALPHA_IBETA_MASK                             0xFFFF0000
#define TMC6460_FOC_FOC_IBETA_IALPHA_IBETA_SHIFT                            16
#define TMC6460_FOC_FOC_IBETA_IALPHA_IBETA_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_IBETA_IALPHA_IBETA_MASK, .shift=TMC6460_FOC_FOC_IBETA_IALPHA_IBETA_SHIFT, .addr=TMC6460_FOC_FOC_IBETA_IALPHA, .isSigned=true })

// FOC.FOC_IQ_ID fields
#define TMC6460_FOC_FOC_IQ_ID_ID_MASK                                       0x0000FFFF
#define TMC6460_FOC_FOC_IQ_ID_ID_SHIFT                                      0
#define TMC6460_FOC_FOC_IQ_ID_ID_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_IQ_ID_ID_MASK, .shift=TMC6460_FOC_FOC_IQ_ID_ID_SHIFT, .addr=TMC6460_FOC_FOC_IQ_ID, .isSigned=true })
#define TMC6460_FOC_FOC_IQ_ID_IQ_MASK                                       0xFFFF0000
#define TMC6460_FOC_FOC_IQ_ID_IQ_SHIFT                                      16
#define TMC6460_FOC_FOC_IQ_ID_IQ_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_IQ_ID_IQ_MASK, .shift=TMC6460_FOC_FOC_IQ_ID_IQ_SHIFT, .addr=TMC6460_FOC_FOC_IQ_ID, .isSigned=true })

// FOC.FOC_UQ_UD fields
#define TMC6460_FOC_FOC_UQ_UD_UD_MASK                                       0x0000FFFF
#define TMC6460_FOC_FOC_UQ_UD_UD_SHIFT                                      0
#define TMC6460_FOC_FOC_UQ_UD_UD_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UQ_UD_UD_MASK, .shift=TMC6460_FOC_FOC_UQ_UD_UD_SHIFT, .addr=TMC6460_FOC_FOC_UQ_UD, .isSigned=true })
#define TMC6460_FOC_FOC_UQ_UD_UQ_MASK                                       0xFFFF0000
#define TMC6460_FOC_FOC_UQ_UD_UQ_SHIFT                                      16
#define TMC6460_FOC_FOC_UQ_UD_UQ_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UQ_UD_UQ_MASK, .shift=TMC6460_FOC_FOC_UQ_UD_UQ_SHIFT, .addr=TMC6460_FOC_FOC_UQ_UD, .isSigned=true })

// FOC.FOC_UQ_UD_LIMITED fields
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UD_LIMITED_MASK                       0x0000FFFF
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UD_LIMITED_SHIFT                      0
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UD_LIMITED_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UQ_UD_LIMITED_UD_LIMITED_MASK, .shift=TMC6460_FOC_FOC_UQ_UD_LIMITED_UD_LIMITED_SHIFT, .addr=TMC6460_FOC_FOC_UQ_UD_LIMITED, .isSigned=true })
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UQ_LIMITED_MASK                       0xFFFF0000
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UQ_LIMITED_SHIFT                      16
#define TMC6460_FOC_FOC_UQ_UD_LIMITED_UQ_LIMITED_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UQ_UD_LIMITED_UQ_LIMITED_MASK, .shift=TMC6460_FOC_FOC_UQ_UD_LIMITED_UQ_LIMITED_SHIFT, .addr=TMC6460_FOC_FOC_UQ_UD_LIMITED, .isSigned=true })

// FOC.FOC_UBETA_UALPHA fields
#define TMC6460_FOC_FOC_UBETA_UALPHA_UALPHA_MASK                            0x0000FFFF
#define TMC6460_FOC_FOC_UBETA_UALPHA_UALPHA_SHIFT                           0
#define TMC6460_FOC_FOC_UBETA_UALPHA_UALPHA_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UBETA_UALPHA_UALPHA_MASK, .shift=TMC6460_FOC_FOC_UBETA_UALPHA_UALPHA_SHIFT, .addr=TMC6460_FOC_FOC_UBETA_UALPHA, .isSigned=true })
#define TMC6460_FOC_FOC_UBETA_UALPHA_UBETA_MASK                             0xFFFF0000
#define TMC6460_FOC_FOC_UBETA_UALPHA_UBETA_SHIFT                            16
#define TMC6460_FOC_FOC_UBETA_UALPHA_UBETA_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UBETA_UALPHA_UBETA_MASK, .shift=TMC6460_FOC_FOC_UBETA_UALPHA_UBETA_SHIFT, .addr=TMC6460_FOC_FOC_UBETA_UALPHA, .isSigned=true })

// FOC.FOC_UW_UU fields
#define TMC6460_FOC_FOC_UW_UU_UU_MASK                                       0x0000FFFF
#define TMC6460_FOC_FOC_UW_UU_UU_SHIFT                                      0
#define TMC6460_FOC_FOC_UW_UU_UU_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UW_UU_UU_MASK, .shift=TMC6460_FOC_FOC_UW_UU_UU_SHIFT, .addr=TMC6460_FOC_FOC_UW_UU, .isSigned=true })
#define TMC6460_FOC_FOC_UW_UU_UW_MASK                                       0xFFFF0000
#define TMC6460_FOC_FOC_UW_UU_UW_SHIFT                                      16
#define TMC6460_FOC_FOC_UW_UU_UW_FIELD                                      ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UW_UU_UW_MASK, .shift=TMC6460_FOC_FOC_UW_UU_UW_SHIFT, .addr=TMC6460_FOC_FOC_UW_UU, .isSigned=true })

// FOC.FOC_UV fields
#define TMC6460_FOC_FOC_UV_UV_MASK                                          0x0000FFFF
#define TMC6460_FOC_FOC_UV_UV_SHIFT                                         0
#define TMC6460_FOC_FOC_UV_UV_FIELD                                         ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_UV_UV_MASK, .shift=TMC6460_FOC_FOC_UV_UV_SHIFT, .addr=TMC6460_FOC_FOC_UV, .isSigned=true })

// FOC.PWM_V_U fields
#define TMC6460_FOC_PWM_V_U_PWM_U_MASK                                      0x0000FFFF
#define TMC6460_FOC_PWM_V_U_PWM_U_SHIFT                                     0
#define TMC6460_FOC_PWM_V_U_PWM_U_FIELD                                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PWM_V_U_PWM_U_MASK, .shift=TMC6460_FOC_PWM_V_U_PWM_U_SHIFT, .addr=TMC6460_FOC_PWM_V_U, .isSigned=false })
#define TMC6460_FOC_PWM_V_U_PWM_V_MASK                                      0xFFFF0000
#define TMC6460_FOC_PWM_V_U_PWM_V_SHIFT                                     16
#define TMC6460_FOC_PWM_V_U_PWM_V_FIELD                                     ((TMC6460RegisterField) {.mask=TMC6460_FOC_PWM_V_U_PWM_V_MASK, .shift=TMC6460_FOC_PWM_V_U_PWM_V_SHIFT, .addr=TMC6460_FOC_PWM_V_U, .isSigned=false })

// FOC.PWM_W fields
#define TMC6460_FOC_PWM_W_MASK                                              0x0000FFFF
#define TMC6460_FOC_PWM_W_SHIFT                                             0
#define TMC6460_FOC_PWM_W_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_FOC_PWM_W_MASK, .shift=TMC6460_FOC_PWM_W_SHIFT, .addr=TMC6460_FOC_PWM_W, .isSigned=false })

// FOC.FOC_STATUS fields
#define TMC6460_FOC_FOC_STATUS_MASK                                         0x0000000F
#define TMC6460_FOC_FOC_STATUS_SHIFT                                        0
#define TMC6460_FOC_FOC_STATUS_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_FOC_STATUS_MASK, .shift=TMC6460_FOC_FOC_STATUS_SHIFT, .addr=TMC6460_FOC_FOC_STATUS, .isSigned=false })

// FOC.U_S_ACTUAL_I_S_ACTUAL fields
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_I_S_ACTUAL_MASK                   0x0000FFFF
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_I_S_ACTUAL_SHIFT                  0
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_I_S_ACTUAL_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_I_S_ACTUAL_MASK, .shift=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_I_S_ACTUAL_SHIFT, .addr=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL, .isSigned=false })
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_U_S_ACTUAL_MASK                   0xFFFF0000
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_U_S_ACTUAL_SHIFT                  16
#define TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_U_S_ACTUAL_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_U_S_ACTUAL_MASK, .shift=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL_U_S_ACTUAL_SHIFT, .addr=TMC6460_FOC_U_S_ACTUAL_I_S_ACTUAL, .isSigned=false })

// FOC.P_MOTOR fields
#define TMC6460_FOC_P_MOTOR_MASK                                            0xFFFFFFFF
#define TMC6460_FOC_P_MOTOR_SHIFT                                           0
#define TMC6460_FOC_P_MOTOR_FIELD                                           ((TMC6460RegisterField) {.mask=TMC6460_FOC_P_MOTOR_MASK, .shift=TMC6460_FOC_P_MOTOR_SHIFT, .addr=TMC6460_FOC_P_MOTOR, .isSigned=false })

// FOC.I_T_ACTUAL fields
#define TMC6460_FOC_I_T_ACTUAL_MASK                                         0x0000FFFF
#define TMC6460_FOC_I_T_ACTUAL_SHIFT                                        0
#define TMC6460_FOC_I_T_ACTUAL_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_FOC_I_T_ACTUAL_MASK, .shift=TMC6460_FOC_I_T_ACTUAL_SHIFT, .addr=TMC6460_FOC_I_T_ACTUAL, .isSigned=false })

// FOC.PRBS_AMPLITUDE fields
#define TMC6460_FOC_PRBS_AMPLITUDE_MASK                                     0xFFFFFFFF
#define TMC6460_FOC_PRBS_AMPLITUDE_SHIFT                                    0
#define TMC6460_FOC_PRBS_AMPLITUDE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_FOC_PRBS_AMPLITUDE_MASK, .shift=TMC6460_FOC_PRBS_AMPLITUDE_SHIFT, .addr=TMC6460_FOC_PRBS_AMPLITUDE, .isSigned=false })

// FOC.PRBS_DOWN_SAMPLING_RATIO fields
#define TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO_MASK                           0x000000FF
#define TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO_SHIFT                          0
#define TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO_MASK, .shift=TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO_SHIFT, .addr=TMC6460_FOC_PRBS_DOWN_SAMPLING_RATIO, .isSigned=false })

// BIQUAD.BIQUAD_EN fields
#define TMC6460_BIQUAD_BIQUAD_EN_VELOCITY_EN_MASK                           0x00000001
#define TMC6460_BIQUAD_BIQUAD_EN_VELOCITY_EN_SHIFT                          0
#define TMC6460_BIQUAD_BIQUAD_EN_VELOCITY_EN_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_BIQUAD_EN_VELOCITY_EN_MASK, .shift=TMC6460_BIQUAD_BIQUAD_EN_VELOCITY_EN_SHIFT, .addr=TMC6460_BIQUAD_BIQUAD_EN, .isSigned=false })
#define TMC6460_BIQUAD_BIQUAD_EN_TORQUE_EN_MASK                             0x00000002
#define TMC6460_BIQUAD_BIQUAD_EN_TORQUE_EN_SHIFT                            1
#define TMC6460_BIQUAD_BIQUAD_EN_TORQUE_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_BIQUAD_EN_TORQUE_EN_MASK, .shift=TMC6460_BIQUAD_BIQUAD_EN_TORQUE_EN_SHIFT, .addr=TMC6460_BIQUAD_BIQUAD_EN, .isSigned=false })

// BIQUAD.VELOCITY_A1 fields
#define TMC6460_BIQUAD_VELOCITY_A1_COEFF_VELOCITY_A1_MASK                   0x00FFFFFF
#define TMC6460_BIQUAD_VELOCITY_A1_COEFF_VELOCITY_A1_SHIFT                  0
#define TMC6460_BIQUAD_VELOCITY_A1_COEFF_VELOCITY_A1_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_VELOCITY_A1_COEFF_VELOCITY_A1_MASK, .shift=TMC6460_BIQUAD_VELOCITY_A1_COEFF_VELOCITY_A1_SHIFT, .addr=TMC6460_BIQUAD_VELOCITY_A1, .isSigned=true })

// BIQUAD.VELOCITY_A2 fields
#define TMC6460_BIQUAD_VELOCITY_A2_COEFF_VELOCITY_A2_MASK                   0x00FFFFFF
#define TMC6460_BIQUAD_VELOCITY_A2_COEFF_VELOCITY_A2_SHIFT                  0
#define TMC6460_BIQUAD_VELOCITY_A2_COEFF_VELOCITY_A2_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_VELOCITY_A2_COEFF_VELOCITY_A2_MASK, .shift=TMC6460_BIQUAD_VELOCITY_A2_COEFF_VELOCITY_A2_SHIFT, .addr=TMC6460_BIQUAD_VELOCITY_A2, .isSigned=true })

// BIQUAD.VELOCITY_B0 fields
#define TMC6460_BIQUAD_VELOCITY_B0_COEFF_VELOCITY_B0_MASK                   0x00FFFFFF
#define TMC6460_BIQUAD_VELOCITY_B0_COEFF_VELOCITY_B0_SHIFT                  0
#define TMC6460_BIQUAD_VELOCITY_B0_COEFF_VELOCITY_B0_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_VELOCITY_B0_COEFF_VELOCITY_B0_MASK, .shift=TMC6460_BIQUAD_VELOCITY_B0_COEFF_VELOCITY_B0_SHIFT, .addr=TMC6460_BIQUAD_VELOCITY_B0, .isSigned=true })

// BIQUAD.VELOCITY_B1 fields
#define TMC6460_BIQUAD_VELOCITY_B1_COEFF_VELOCITY_B1_MASK                   0x00FFFFFF
#define TMC6460_BIQUAD_VELOCITY_B1_COEFF_VELOCITY_B1_SHIFT                  0
#define TMC6460_BIQUAD_VELOCITY_B1_COEFF_VELOCITY_B1_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_VELOCITY_B1_COEFF_VELOCITY_B1_MASK, .shift=TMC6460_BIQUAD_VELOCITY_B1_COEFF_VELOCITY_B1_SHIFT, .addr=TMC6460_BIQUAD_VELOCITY_B1, .isSigned=true })

// BIQUAD.VELOCITY_B2 fields
#define TMC6460_BIQUAD_VELOCITY_B2_COEFF_VELOCITY_B2_MASK                   0x00FFFFFF
#define TMC6460_BIQUAD_VELOCITY_B2_COEFF_VELOCITY_B2_SHIFT                  0
#define TMC6460_BIQUAD_VELOCITY_B2_COEFF_VELOCITY_B2_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_VELOCITY_B2_COEFF_VELOCITY_B2_MASK, .shift=TMC6460_BIQUAD_VELOCITY_B2_COEFF_VELOCITY_B2_SHIFT, .addr=TMC6460_BIQUAD_VELOCITY_B2, .isSigned=true })

// BIQUAD.TORQUE_A1 fields
#define TMC6460_BIQUAD_TORQUE_A1_COEFF_TORQUE_A1_MASK                       0x00FFFFFF
#define TMC6460_BIQUAD_TORQUE_A1_COEFF_TORQUE_A1_SHIFT                      0
#define TMC6460_BIQUAD_TORQUE_A1_COEFF_TORQUE_A1_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_TORQUE_A1_COEFF_TORQUE_A1_MASK, .shift=TMC6460_BIQUAD_TORQUE_A1_COEFF_TORQUE_A1_SHIFT, .addr=TMC6460_BIQUAD_TORQUE_A1, .isSigned=true })

// BIQUAD.TORQUE_A2 fields
#define TMC6460_BIQUAD_TORQUE_A2_COEFF_TORQUE_A2_MASK                       0x00FFFFFF
#define TMC6460_BIQUAD_TORQUE_A2_COEFF_TORQUE_A2_SHIFT                      0
#define TMC6460_BIQUAD_TORQUE_A2_COEFF_TORQUE_A2_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_TORQUE_A2_COEFF_TORQUE_A2_MASK, .shift=TMC6460_BIQUAD_TORQUE_A2_COEFF_TORQUE_A2_SHIFT, .addr=TMC6460_BIQUAD_TORQUE_A2, .isSigned=true })

// BIQUAD.TORQUE_B0 fields
#define TMC6460_BIQUAD_TORQUE_B0_COEFF_TORQUE_B0_MASK                       0x00FFFFFF
#define TMC6460_BIQUAD_TORQUE_B0_COEFF_TORQUE_B0_SHIFT                      0
#define TMC6460_BIQUAD_TORQUE_B0_COEFF_TORQUE_B0_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_TORQUE_B0_COEFF_TORQUE_B0_MASK, .shift=TMC6460_BIQUAD_TORQUE_B0_COEFF_TORQUE_B0_SHIFT, .addr=TMC6460_BIQUAD_TORQUE_B0, .isSigned=true })

// BIQUAD.TORQUE_B1 fields
#define TMC6460_BIQUAD_TORQUE_B1_COEFF_TORQUE_B1_MASK                       0x00FFFFFF
#define TMC6460_BIQUAD_TORQUE_B1_COEFF_TORQUE_B1_SHIFT                      0
#define TMC6460_BIQUAD_TORQUE_B1_COEFF_TORQUE_B1_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_TORQUE_B1_COEFF_TORQUE_B1_MASK, .shift=TMC6460_BIQUAD_TORQUE_B1_COEFF_TORQUE_B1_SHIFT, .addr=TMC6460_BIQUAD_TORQUE_B1, .isSigned=true })

// BIQUAD.TORQUE_B2 fields
#define TMC6460_BIQUAD_TORQUE_B2_COEFF_TORQUE_B2_MASK                       0x00FFFFFF
#define TMC6460_BIQUAD_TORQUE_B2_COEFF_TORQUE_B2_SHIFT                      0
#define TMC6460_BIQUAD_TORQUE_B2_COEFF_TORQUE_B2_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_BIQUAD_TORQUE_B2_COEFF_TORQUE_B2_MASK, .shift=TMC6460_BIQUAD_TORQUE_B2_COEFF_TORQUE_B2_SHIFT, .addr=TMC6460_BIQUAD_TORQUE_B2, .isSigned=true })

// RAMPER.TIME_CONFIG fields
#define TMC6460_RAMPER_TIME_CONFIG_T_ZEROWAIT_MASK                          0x0000FFFF
#define TMC6460_RAMPER_TIME_CONFIG_T_ZEROWAIT_SHIFT                         0
#define TMC6460_RAMPER_TIME_CONFIG_T_ZEROWAIT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_TIME_CONFIG_T_ZEROWAIT_MASK, .shift=TMC6460_RAMPER_TIME_CONFIG_T_ZEROWAIT_SHIFT, .addr=TMC6460_RAMPER_TIME_CONFIG, .isSigned=false })
#define TMC6460_RAMPER_TIME_CONFIG_T_VMAX_MASK                              0xFFFF0000
#define TMC6460_RAMPER_TIME_CONFIG_T_VMAX_SHIFT                             16
#define TMC6460_RAMPER_TIME_CONFIG_T_VMAX_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_TIME_CONFIG_T_VMAX_MASK, .shift=TMC6460_RAMPER_TIME_CONFIG_T_VMAX_SHIFT, .addr=TMC6460_RAMPER_TIME_CONFIG, .isSigned=false })

// RAMPER.SWITCH_MODE fields
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_STOP_EN_MASK                  0x00000001
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_STOP_EN_SHIFT                 0
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_STOP_EN_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_STOP_EN_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_STOP_EN_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_STOP_EN_MASK                  0x00000002
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_STOP_EN_SHIFT                 1
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_STOP_EN_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_STOP_EN_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_STOP_EN_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_STOP_EN_MASK                  0x00000004
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_STOP_EN_SHIFT                 2
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_STOP_EN_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_STOP_EN_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_STOP_EN_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_POL_MASK                      0x00000008
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_POL_SHIFT                     3
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_POL_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_POL_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_L_POL_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_POL_MASK                      0x00000010
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_POL_SHIFT                     4
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_POL_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_POL_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_R_POL_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_POL_MASK                      0x00000020
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_POL_SHIFT                     5
#define TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_POL_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_POL_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_RAMP_REF_H_POL_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_SWAP_RAMP_REF_LR_MASK                    0x00000040
#define TMC6460_RAMPER_SWITCH_MODE_SWAP_RAMP_REF_LR_SHIFT                   6
#define TMC6460_RAMPER_SWITCH_MODE_SWAP_RAMP_REF_LR_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_SWAP_RAMP_REF_LR_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_SWAP_RAMP_REF_LR_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_ACTIVE_MASK                  0x00000080
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_ACTIVE_SHIFT                 7
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_ACTIVE_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_ACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_ACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_INACTIVE_MASK                0x00000100
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_INACTIVE_SHIFT               8
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_INACTIVE_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_INACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_L_INACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_ACTIVE_MASK                  0x00000200
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_ACTIVE_SHIFT                 9
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_ACTIVE_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_ACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_ACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_INACTIVE_MASK                0x00000400
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_INACTIVE_SHIFT               10
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_INACTIVE_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_INACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_R_INACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_ACTIVE_MASK                  0x00000800
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_ACTIVE_SHIFT                 11
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_ACTIVE_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_ACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_ACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_INACTIVE_MASK                0x00001000
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_INACTIVE_SHIFT               12
#define TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_INACTIVE_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_INACTIVE_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_LATCH_REF_H_INACTIVE_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_STALL_STOP_EN_MASK                       0x00004000
#define TMC6460_RAMPER_SWITCH_MODE_STALL_STOP_EN_SHIFT                      14
#define TMC6460_RAMPER_SWITCH_MODE_STALL_STOP_EN_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_STALL_STOP_EN_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_STALL_STOP_EN_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_SOFT_STOP_EN_MASK                        0x00008000
#define TMC6460_RAMPER_SWITCH_MODE_SOFT_STOP_EN_SHIFT                       15
#define TMC6460_RAMPER_SWITCH_MODE_SOFT_STOP_EN_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_SOFT_STOP_EN_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_SOFT_STOP_EN_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_FORCE_HARD_STOP_MASK                     0x00010000
#define TMC6460_RAMPER_SWITCH_MODE_FORCE_HARD_STOP_SHIFT                    16
#define TMC6460_RAMPER_SWITCH_MODE_FORCE_HARD_STOP_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_FORCE_HARD_STOP_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_FORCE_HARD_STOP_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_POS_DEVIATION_MASK               0x00020000
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_POS_DEVIATION_SHIFT              17
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_POS_DEVIATION_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_STOP_ON_POS_DEVIATION_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_STOP_ON_POS_DEVIATION_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_V_DEVIATION_MASK                 0x00040000
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_V_DEVIATION_SHIFT                18
#define TMC6460_RAMPER_SWITCH_MODE_STOP_ON_V_DEVIATION_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_SWITCH_MODE_STOP_ON_V_DEVIATION_MASK, .shift=TMC6460_RAMPER_SWITCH_MODE_STOP_ON_V_DEVIATION_SHIFT, .addr=TMC6460_RAMPER_SWITCH_MODE, .isSigned=false })

// RAMPER.PHI_E fields
#define TMC6460_RAMPER_PHI_E_PHI_E_MASK                                     0x0000FFFF
#define TMC6460_RAMPER_PHI_E_PHI_E_SHIFT                                    0
#define TMC6460_RAMPER_PHI_E_PHI_E_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_PHI_E_PHI_E_MASK, .shift=TMC6460_RAMPER_PHI_E_PHI_E_SHIFT, .addr=TMC6460_RAMPER_PHI_E, .isSigned=false })
#define TMC6460_RAMPER_PHI_E_PHI_E_OFFSET_MASK                              0xFFFF0000
#define TMC6460_RAMPER_PHI_E_PHI_E_OFFSET_SHIFT                             16
#define TMC6460_RAMPER_PHI_E_PHI_E_OFFSET_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_PHI_E_PHI_E_OFFSET_MASK, .shift=TMC6460_RAMPER_PHI_E_PHI_E_OFFSET_SHIFT, .addr=TMC6460_RAMPER_PHI_E, .isSigned=false })

// RAMPER.A1 fields
#define TMC6460_RAMPER_A1_MASK                                              0x007FFFFF
#define TMC6460_RAMPER_A1_SHIFT                                             0
#define TMC6460_RAMPER_A1_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_A1_MASK, .shift=TMC6460_RAMPER_A1_SHIFT, .addr=TMC6460_RAMPER_A1, .isSigned=false })

// RAMPER.A2 fields
#define TMC6460_RAMPER_A2_MASK                                              0x007FFFFF
#define TMC6460_RAMPER_A2_SHIFT                                             0
#define TMC6460_RAMPER_A2_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_A2_MASK, .shift=TMC6460_RAMPER_A2_SHIFT, .addr=TMC6460_RAMPER_A2, .isSigned=false })

// RAMPER.A_MAX fields
#define TMC6460_RAMPER_A_MAX_MASK                                           0x007FFFFF
#define TMC6460_RAMPER_A_MAX_SHIFT                                          0
#define TMC6460_RAMPER_A_MAX_FIELD                                          ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_A_MAX_MASK, .shift=TMC6460_RAMPER_A_MAX_SHIFT, .addr=TMC6460_RAMPER_A_MAX, .isSigned=false })

// RAMPER.D1 fields
#define TMC6460_RAMPER_D1_MASK                                              0x007FFFFF
#define TMC6460_RAMPER_D1_SHIFT                                             0
#define TMC6460_RAMPER_D1_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_D1_MASK, .shift=TMC6460_RAMPER_D1_SHIFT, .addr=TMC6460_RAMPER_D1, .isSigned=false })

// RAMPER.D2 fields
#define TMC6460_RAMPER_D2_MASK                                              0x007FFFFF
#define TMC6460_RAMPER_D2_SHIFT                                             0
#define TMC6460_RAMPER_D2_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_D2_MASK, .shift=TMC6460_RAMPER_D2_SHIFT, .addr=TMC6460_RAMPER_D2, .isSigned=false })

// RAMPER.D_MAX fields
#define TMC6460_RAMPER_D_MAX_MASK                                           0x007FFFFF
#define TMC6460_RAMPER_D_MAX_SHIFT                                          0
#define TMC6460_RAMPER_D_MAX_FIELD                                          ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_D_MAX_MASK, .shift=TMC6460_RAMPER_D_MAX_SHIFT, .addr=TMC6460_RAMPER_D_MAX, .isSigned=false })

// RAMPER.V_START fields
#define TMC6460_RAMPER_V_START_MASK                                         0x007FFFFF
#define TMC6460_RAMPER_V_START_SHIFT                                        0
#define TMC6460_RAMPER_V_START_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V_START_MASK, .shift=TMC6460_RAMPER_V_START_SHIFT, .addr=TMC6460_RAMPER_V_START, .isSigned=false })

// RAMPER.V1 fields
#define TMC6460_RAMPER_V1_MASK                                              0x07FFFFFF
#define TMC6460_RAMPER_V1_SHIFT                                             0
#define TMC6460_RAMPER_V1_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V1_MASK, .shift=TMC6460_RAMPER_V1_SHIFT, .addr=TMC6460_RAMPER_V1, .isSigned=false })

// RAMPER.V2 fields
#define TMC6460_RAMPER_V2_MASK                                              0x07FFFFFF
#define TMC6460_RAMPER_V2_SHIFT                                             0
#define TMC6460_RAMPER_V2_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V2_MASK, .shift=TMC6460_RAMPER_V2_SHIFT, .addr=TMC6460_RAMPER_V2, .isSigned=false })

// RAMPER.V_STOP fields
#define TMC6460_RAMPER_V_STOP_MASK                                          0x007FFFFF
#define TMC6460_RAMPER_V_STOP_SHIFT                                         0
#define TMC6460_RAMPER_V_STOP_FIELD                                         ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V_STOP_MASK, .shift=TMC6460_RAMPER_V_STOP_SHIFT, .addr=TMC6460_RAMPER_V_STOP, .isSigned=false })

// RAMPER.V_MAX fields
#define TMC6460_RAMPER_V_MAX_MASK                                           0x07FFFFFF
#define TMC6460_RAMPER_V_MAX_SHIFT                                          0
#define TMC6460_RAMPER_V_MAX_FIELD                                          ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V_MAX_MASK, .shift=TMC6460_RAMPER_V_MAX_SHIFT, .addr=TMC6460_RAMPER_V_MAX, .isSigned=false })

// RAMPER.ACCELERATION fields
#define TMC6460_RAMPER_ACCELERATION_MASK                                    0x00FFFFFF
#define TMC6460_RAMPER_ACCELERATION_SHIFT                                   0
#define TMC6460_RAMPER_ACCELERATION_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_ACCELERATION_MASK, .shift=TMC6460_RAMPER_ACCELERATION_SHIFT, .addr=TMC6460_RAMPER_ACCELERATION, .isSigned=true })

// RAMPER.V_ACTUAL fields
#define TMC6460_RAMPER_V_ACTUAL_MASK                                        0x0FFFFFFF
#define TMC6460_RAMPER_V_ACTUAL_SHIFT                                       0
#define TMC6460_RAMPER_V_ACTUAL_FIELD                                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_V_ACTUAL_MASK, .shift=TMC6460_RAMPER_V_ACTUAL_SHIFT, .addr=TMC6460_RAMPER_V_ACTUAL, .isSigned=true })

// RAMPER.POSITION fields
#define TMC6460_RAMPER_POSITION_MASK                                        0xFFFFFFFF
#define TMC6460_RAMPER_POSITION_SHIFT                                       0
#define TMC6460_RAMPER_POSITION_FIELD                                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_POSITION_MASK, .shift=TMC6460_RAMPER_POSITION_SHIFT, .addr=TMC6460_RAMPER_POSITION, .isSigned=true })

// RAMPER.POSITION_LATCH fields
#define TMC6460_RAMPER_POSITION_LATCH_MASK                                  0xFFFFFFFF
#define TMC6460_RAMPER_POSITION_LATCH_SHIFT                                 0
#define TMC6460_RAMPER_POSITION_LATCH_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_POSITION_LATCH_MASK, .shift=TMC6460_RAMPER_POSITION_LATCH_SHIFT, .addr=TMC6460_RAMPER_POSITION_LATCH, .isSigned=true })

// RAMPER.POSITION_ACTUAL_LATCH fields
#define TMC6460_RAMPER_POSITION_ACTUAL_LATCH_MASK                           0xFFFFFFFF
#define TMC6460_RAMPER_POSITION_ACTUAL_LATCH_SHIFT                          0
#define TMC6460_RAMPER_POSITION_ACTUAL_LATCH_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_POSITION_ACTUAL_LATCH_MASK, .shift=TMC6460_RAMPER_POSITION_ACTUAL_LATCH_SHIFT, .addr=TMC6460_RAMPER_POSITION_ACTUAL_LATCH, .isSigned=true })

// RAMPER.STATUS fields
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STATUS_MASK                        0x00000001
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STATUS_SHIFT                       0
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STATUS_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_L_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_L_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STATUS_MASK                        0x00000002
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STATUS_SHIFT                       1
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STATUS_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_R_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_R_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STATUS_MASK                        0x00000004
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STATUS_SHIFT                       2
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STATUS_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_H_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_H_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STOP_STATUS_MASK                   0x00000040
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STOP_STATUS_SHIFT                  6
#define TMC6460_RAMPER_STATUS_RAMP_REF_L_STOP_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_L_STOP_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_L_STOP_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STOP_STATUS_MASK                   0x00000080
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STOP_STATUS_SHIFT                  7
#define TMC6460_RAMPER_STATUS_RAMP_REF_R_STOP_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_R_STOP_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_R_STOP_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STOP_STATUS_MASK                   0x00000100
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STOP_STATUS_SHIFT                  8
#define TMC6460_RAMPER_STATUS_RAMP_REF_H_STOP_STATUS_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_RAMP_REF_H_STOP_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_RAMP_REF_H_STOP_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_V_REACHED_STATUS_MASK                         0x00000800
#define TMC6460_RAMPER_STATUS_V_REACHED_STATUS_SHIFT                        11
#define TMC6460_RAMPER_STATUS_V_REACHED_STATUS_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_V_REACHED_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_V_REACHED_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_POSITION_REACHED_STATUS_MASK                  0x00001000
#define TMC6460_RAMPER_STATUS_POSITION_REACHED_STATUS_SHIFT                 12
#define TMC6460_RAMPER_STATUS_POSITION_REACHED_STATUS_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_POSITION_REACHED_STATUS_MASK, .shift=TMC6460_RAMPER_STATUS_POSITION_REACHED_STATUS_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_V_ZERO_MASK                                   0x00002000
#define TMC6460_RAMPER_STATUS_V_ZERO_SHIFT                                  13
#define TMC6460_RAMPER_STATUS_V_ZERO_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_V_ZERO_MASK, .shift=TMC6460_RAMPER_STATUS_V_ZERO_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_T_ZEROWAIT_ACTIVE_MASK                        0x00004000
#define TMC6460_RAMPER_STATUS_T_ZEROWAIT_ACTIVE_SHIFT                       14
#define TMC6460_RAMPER_STATUS_T_ZEROWAIT_ACTIVE_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_T_ZEROWAIT_ACTIVE_MASK, .shift=TMC6460_RAMPER_STATUS_T_ZEROWAIT_ACTIVE_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_STALL_IN_V_ERR_MASK                           0x00010000
#define TMC6460_RAMPER_STATUS_STALL_IN_V_ERR_SHIFT                          16
#define TMC6460_RAMPER_STATUS_STALL_IN_V_ERR_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_STALL_IN_V_ERR_MASK, .shift=TMC6460_RAMPER_STATUS_STALL_IN_V_ERR_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })
#define TMC6460_RAMPER_STATUS_STALL_IN_POSITION_ERR_MASK                    0x00020000
#define TMC6460_RAMPER_STATUS_STALL_IN_POSITION_ERR_SHIFT                   17
#define TMC6460_RAMPER_STATUS_STALL_IN_POSITION_ERR_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_STATUS_STALL_IN_POSITION_ERR_MASK, .shift=TMC6460_RAMPER_STATUS_STALL_IN_POSITION_ERR_SHIFT, .addr=TMC6460_RAMPER_STATUS, .isSigned=false })

// RAMPER.EVENTS fields
#define TMC6460_RAMPER_EVENTS_POSITION_REACHED_EVENT_MASK                   0x00000001
#define TMC6460_RAMPER_EVENTS_POSITION_REACHED_EVENT_SHIFT                  0
#define TMC6460_RAMPER_EVENTS_POSITION_REACHED_EVENT_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_POSITION_REACHED_EVENT_MASK, .shift=TMC6460_RAMPER_EVENTS_POSITION_REACHED_EVENT_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })
#define TMC6460_RAMPER_EVENTS_STALL_STOP_EVENT_MASK                         0x00000002
#define TMC6460_RAMPER_EVENTS_STALL_STOP_EVENT_SHIFT                        1
#define TMC6460_RAMPER_EVENTS_STALL_STOP_EVENT_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_STALL_STOP_EVENT_MASK, .shift=TMC6460_RAMPER_EVENTS_STALL_STOP_EVENT_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })
#define TMC6460_RAMPER_EVENTS_SECOND_MOVE_EVENT_MASK                        0x00000004
#define TMC6460_RAMPER_EVENTS_SECOND_MOVE_EVENT_SHIFT                       2
#define TMC6460_RAMPER_EVENTS_SECOND_MOVE_EVENT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_SECOND_MOVE_EVENT_MASK, .shift=TMC6460_RAMPER_EVENTS_SECOND_MOVE_EVENT_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })
#define TMC6460_RAMPER_EVENTS_LATCH_REF_H_READY_MASK                        0x00000008
#define TMC6460_RAMPER_EVENTS_LATCH_REF_H_READY_SHIFT                       3
#define TMC6460_RAMPER_EVENTS_LATCH_REF_H_READY_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_LATCH_REF_H_READY_MASK, .shift=TMC6460_RAMPER_EVENTS_LATCH_REF_H_READY_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })
#define TMC6460_RAMPER_EVENTS_LATCH_REF_L_READY_MASK                        0x00000010
#define TMC6460_RAMPER_EVENTS_LATCH_REF_L_READY_SHIFT                       4
#define TMC6460_RAMPER_EVENTS_LATCH_REF_L_READY_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_LATCH_REF_L_READY_MASK, .shift=TMC6460_RAMPER_EVENTS_LATCH_REF_L_READY_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })
#define TMC6460_RAMPER_EVENTS_LATCH_REF_R_READY_MASK                        0x00000020
#define TMC6460_RAMPER_EVENTS_LATCH_REF_R_READY_SHIFT                       5
#define TMC6460_RAMPER_EVENTS_LATCH_REF_R_READY_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_RAMPER_EVENTS_LATCH_REF_R_READY_MASK, .shift=TMC6460_RAMPER_EVENTS_LATCH_REF_R_READY_SHIFT, .addr=TMC6460_RAMPER_EVENTS, .isSigned=false })

// EXT_CTRL.VOLTAGE fields
#define TMC6460_EXT_CTRL_VOLTAGE_UD_MASK                                    0x0000FFFF
#define TMC6460_EXT_CTRL_VOLTAGE_UD_SHIFT                                   0
#define TMC6460_EXT_CTRL_VOLTAGE_UD_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_EXT_CTRL_VOLTAGE_UD_MASK, .shift=TMC6460_EXT_CTRL_VOLTAGE_UD_SHIFT, .addr=TMC6460_EXT_CTRL_VOLTAGE, .isSigned=true })
#define TMC6460_EXT_CTRL_VOLTAGE_UQ_MASK                                    0xFFFF0000
#define TMC6460_EXT_CTRL_VOLTAGE_UQ_SHIFT                                   16
#define TMC6460_EXT_CTRL_VOLTAGE_UQ_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_EXT_CTRL_VOLTAGE_UQ_MASK, .shift=TMC6460_EXT_CTRL_VOLTAGE_UQ_SHIFT, .addr=TMC6460_EXT_CTRL_VOLTAGE, .isSigned=true })

// EXT_CTRL.PWM_V_U fields
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_U_MASK                                 0x0000FFFF
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_U_SHIFT                                0
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_U_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_EXT_CTRL_PWM_V_U_PWM_U_MASK, .shift=TMC6460_EXT_CTRL_PWM_V_U_PWM_U_SHIFT, .addr=TMC6460_EXT_CTRL_PWM_V_U, .isSigned=false })
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_V_MASK                                 0xFFFF0000
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_V_SHIFT                                16
#define TMC6460_EXT_CTRL_PWM_V_U_PWM_V_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_EXT_CTRL_PWM_V_U_PWM_V_MASK, .shift=TMC6460_EXT_CTRL_PWM_V_U_PWM_V_SHIFT, .addr=TMC6460_EXT_CTRL_PWM_V_U, .isSigned=false })

// EXT_CTRL.PWM_W fields
#define TMC6460_EXT_CTRL_PWM_W_MASK                                         0x0000FFFF
#define TMC6460_EXT_CTRL_PWM_W_SHIFT                                        0
#define TMC6460_EXT_CTRL_PWM_W_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_EXT_CTRL_PWM_W_MASK, .shift=TMC6460_EXT_CTRL_PWM_W_SHIFT, .addr=TMC6460_EXT_CTRL_PWM_W, .isSigned=false })

// FEEDBACK.CONF_CH_A fields
#define TMC6460_FEEDBACK_CONF_CH_A_CPR_INV_A_MASK                           0x00FFFFFF
#define TMC6460_FEEDBACK_CONF_CH_A_CPR_INV_A_SHIFT                          0
#define TMC6460_FEEDBACK_CONF_CH_A_CPR_INV_A_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CONF_CH_A_CPR_INV_A_MASK, .shift=TMC6460_FEEDBACK_CONF_CH_A_CPR_INV_A_SHIFT, .addr=TMC6460_FEEDBACK_CONF_CH_A, .isSigned=false })
#define TMC6460_FEEDBACK_CONF_CH_A_SRC_SEL_A_MASK                           0x0F000000
#define TMC6460_FEEDBACK_CONF_CH_A_SRC_SEL_A_SHIFT                          24
#define TMC6460_FEEDBACK_CONF_CH_A_SRC_SEL_A_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CONF_CH_A_SRC_SEL_A_MASK, .shift=TMC6460_FEEDBACK_CONF_CH_A_SRC_SEL_A_SHIFT, .addr=TMC6460_FEEDBACK_CONF_CH_A, .isSigned=false })

// FEEDBACK.CONF_CH_B fields
#define TMC6460_FEEDBACK_CONF_CH_B_CPR_INV_B_MASK                           0x00FFFFFF
#define TMC6460_FEEDBACK_CONF_CH_B_CPR_INV_B_SHIFT                          0
#define TMC6460_FEEDBACK_CONF_CH_B_CPR_INV_B_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CONF_CH_B_CPR_INV_B_MASK, .shift=TMC6460_FEEDBACK_CONF_CH_B_CPR_INV_B_SHIFT, .addr=TMC6460_FEEDBACK_CONF_CH_B, .isSigned=false })
#define TMC6460_FEEDBACK_CONF_CH_B_SRC_SEL_B_MASK                           0x0F000000
#define TMC6460_FEEDBACK_CONF_CH_B_SRC_SEL_B_SHIFT                          24
#define TMC6460_FEEDBACK_CONF_CH_B_SRC_SEL_B_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CONF_CH_B_SRC_SEL_B_MASK, .shift=TMC6460_FEEDBACK_CONF_CH_B_SRC_SEL_B_SHIFT, .addr=TMC6460_FEEDBACK_CONF_CH_B, .isSigned=false })

// FEEDBACK.PHI_E_OFFSET fields
#define TMC6460_FEEDBACK_PHI_E_OFFSET_MASK                                  0x0000FFFF
#define TMC6460_FEEDBACK_PHI_E_OFFSET_SHIFT                                 0
#define TMC6460_FEEDBACK_PHI_E_OFFSET_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_E_OFFSET_MASK, .shift=TMC6460_FEEDBACK_PHI_E_OFFSET_SHIFT, .addr=TMC6460_FEEDBACK_PHI_E_OFFSET, .isSigned=false })

// FEEDBACK.LUT fields
#define TMC6460_FEEDBACK_LUT_SPLIT_MODE_EN_MASK                             0x00000001
#define TMC6460_FEEDBACK_LUT_SPLIT_MODE_EN_SHIFT                            0
#define TMC6460_FEEDBACK_LUT_SPLIT_MODE_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_SPLIT_MODE_EN_MASK, .shift=TMC6460_FEEDBACK_LUT_SPLIT_MODE_EN_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_EN_MASK                               0x00000002
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_EN_SHIFT                              1
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_EN_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_LOOKUP_A_EN_MASK, .shift=TMC6460_FEEDBACK_LUT_LOOKUP_A_EN_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_EN_MASK                               0x00000004
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_EN_SHIFT                              2
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_EN_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_LOOKUP_B_EN_MASK, .shift=TMC6460_FEEDBACK_LUT_LOOKUP_B_EN_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_GAIN_MASK                             0x00000700
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_GAIN_SHIFT                            8
#define TMC6460_FEEDBACK_LUT_LOOKUP_A_GAIN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_LOOKUP_A_GAIN_MASK, .shift=TMC6460_FEEDBACK_LUT_LOOKUP_A_GAIN_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_GAIN_MASK                             0x00007000
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_GAIN_SHIFT                            12
#define TMC6460_FEEDBACK_LUT_LOOKUP_B_GAIN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_LOOKUP_B_GAIN_MASK, .shift=TMC6460_FEEDBACK_LUT_LOOKUP_B_GAIN_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_ADDR_MASK                                      0x00FF0000
#define TMC6460_FEEDBACK_LUT_ADDR_SHIFT                                     16
#define TMC6460_FEEDBACK_LUT_ADDR_FIELD                                     ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_ADDR_MASK, .shift=TMC6460_FEEDBACK_LUT_ADDR_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=false })
#define TMC6460_FEEDBACK_LUT_RDATA_MASK                                     0xFF000000
#define TMC6460_FEEDBACK_LUT_RDATA_SHIFT                                    24
#define TMC6460_FEEDBACK_LUT_RDATA_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_RDATA_MASK, .shift=TMC6460_FEEDBACK_LUT_RDATA_SHIFT, .addr=TMC6460_FEEDBACK_LUT, .isSigned=true })

// FEEDBACK.VELOCITY_FRQ_CONF fields
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SYNC_SRC_MASK           0x00000001
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SYNC_SRC_SHIFT          0
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SYNC_SRC_FIELD          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SYNC_SRC_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SYNC_SRC_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SAMPLING_MASK           0x000000FE
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SAMPLING_SHIFT          1
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SAMPLING_FIELD          ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SAMPLING_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SAMPLING_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SCALING_MASK            0x00FFFF00
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SCALING_SHIFT           8
#define TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SCALING_FIELD           ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SCALING_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF_VELOCITY_SCALING_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_FRQ_CONF, .isSigned=false })

// FEEDBACK.VELOCITY_PER_CONF fields
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_MIN_MASK                 0x00007FFF
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_MIN_SHIFT                0
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_MIN_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_MIN_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_MIN_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_PER_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_TIMER_MASK               0xFFFF0000
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_TIMER_SHIFT              16
#define TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_TIMER_FIELD              ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_TIMER_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_PER_CONF_POS_DEV_TIMER_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_PER_CONF, .isSigned=false })

// FEEDBACK.VELOCITY_PER_FILTER fields
#define TMC6460_FEEDBACK_VELOCITY_PER_FILTER_FILTER_WIDTH_MASK              0x00000007
#define TMC6460_FEEDBACK_VELOCITY_PER_FILTER_FILTER_WIDTH_SHIFT             0
#define TMC6460_FEEDBACK_VELOCITY_PER_FILTER_FILTER_WIDTH_FIELD             ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_PER_FILTER_FILTER_WIDTH_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_PER_FILTER_FILTER_WIDTH_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_PER_FILTER, .isSigned=false })

// FEEDBACK.PHI_CONVERTED fields
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_A_MASK                 0x0000FFFF
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_A_SHIFT                0
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_A_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_A_MASK, .shift=TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_A_SHIFT, .addr=TMC6460_FEEDBACK_PHI_CONVERTED, .isSigned=false })
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_B_MASK                 0xFFFF0000
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_B_SHIFT                16
#define TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_B_FIELD                ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_B_MASK, .shift=TMC6460_FEEDBACK_PHI_CONVERTED_PHI_CONVERTED_B_SHIFT, .addr=TMC6460_FEEDBACK_PHI_CONVERTED, .isSigned=false })

// FEEDBACK.CH_A fields
#define TMC6460_FEEDBACK_CH_A_PHI_LOOKUP_A_MASK                             0x0000FFFF
#define TMC6460_FEEDBACK_CH_A_PHI_LOOKUP_A_SHIFT                            0
#define TMC6460_FEEDBACK_CH_A_PHI_LOOKUP_A_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CH_A_PHI_LOOKUP_A_MASK, .shift=TMC6460_FEEDBACK_CH_A_PHI_LOOKUP_A_SHIFT, .addr=TMC6460_FEEDBACK_CH_A, .isSigned=false })
#define TMC6460_FEEDBACK_CH_A_PHI_EXTRAPOLATED_AB_MASK                      0xFFFF0000
#define TMC6460_FEEDBACK_CH_A_PHI_EXTRAPOLATED_AB_SHIFT                     16
#define TMC6460_FEEDBACK_CH_A_PHI_EXTRAPOLATED_AB_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CH_A_PHI_EXTRAPOLATED_AB_MASK, .shift=TMC6460_FEEDBACK_CH_A_PHI_EXTRAPOLATED_AB_SHIFT, .addr=TMC6460_FEEDBACK_CH_A, .isSigned=false })

// FEEDBACK.CH_B fields
#define TMC6460_FEEDBACK_CH_B_PHI_LOOKUP_B_MASK                             0x0000FFFF
#define TMC6460_FEEDBACK_CH_B_PHI_LOOKUP_B_SHIFT                            0
#define TMC6460_FEEDBACK_CH_B_PHI_LOOKUP_B_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_CH_B_PHI_LOOKUP_B_MASK, .shift=TMC6460_FEEDBACK_CH_B_PHI_LOOKUP_B_SHIFT, .addr=TMC6460_FEEDBACK_CH_B, .isSigned=false })

// FEEDBACK.VELOCITY_FRQ fields
#define TMC6460_FEEDBACK_VELOCITY_FRQ_MASK                                  0xFFFFFFFF
#define TMC6460_FEEDBACK_VELOCITY_FRQ_SHIFT                                 0
#define TMC6460_FEEDBACK_VELOCITY_FRQ_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_FRQ_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_FRQ_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_FRQ, .isSigned=true })

// FEEDBACK.VELOCITY_PER fields
#define TMC6460_FEEDBACK_VELOCITY_PER_MASK                                  0xFFFFFFFF
#define TMC6460_FEEDBACK_VELOCITY_PER_SHIFT                                 0
#define TMC6460_FEEDBACK_VELOCITY_PER_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_PER_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_PER_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_PER, .isSigned=true })

// FEEDBACK.LUT_WDATA fields
#define TMC6460_FEEDBACK_LUT_WDATA_WDATA_MASK                               0xFFFFFFFF
#define TMC6460_FEEDBACK_LUT_WDATA_WDATA_SHIFT                              0
#define TMC6460_FEEDBACK_LUT_WDATA_WDATA_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_LUT_WDATA_WDATA_MASK, .shift=TMC6460_FEEDBACK_LUT_WDATA_WDATA_SHIFT, .addr=TMC6460_FEEDBACK_LUT_WDATA, .isSigned=false })

// FEEDBACK.PHI_EXT_A fields
#define TMC6460_FEEDBACK_PHI_EXT_A_MASK                                     0x00FFFFFF
#define TMC6460_FEEDBACK_PHI_EXT_A_SHIFT                                    0
#define TMC6460_FEEDBACK_PHI_EXT_A_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_EXT_A_MASK, .shift=TMC6460_FEEDBACK_PHI_EXT_A_SHIFT, .addr=TMC6460_FEEDBACK_PHI_EXT_A, .isSigned=false })

// FEEDBACK.PHI_EXT_B fields
#define TMC6460_FEEDBACK_PHI_EXT_B_MASK                                     0x00FFFFFF
#define TMC6460_FEEDBACK_PHI_EXT_B_SHIFT                                    0
#define TMC6460_FEEDBACK_PHI_EXT_B_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_EXT_B_MASK, .shift=TMC6460_FEEDBACK_PHI_EXT_B_SHIFT, .addr=TMC6460_FEEDBACK_PHI_EXT_B, .isSigned=false })

// FEEDBACK.VELOCITY_EXT fields
#define TMC6460_FEEDBACK_VELOCITY_EXT_MASK                                  0xFFFFFFFF
#define TMC6460_FEEDBACK_VELOCITY_EXT_SHIFT                                 0
#define TMC6460_FEEDBACK_VELOCITY_EXT_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_VELOCITY_EXT_MASK, .shift=TMC6460_FEEDBACK_VELOCITY_EXT_SHIFT, .addr=TMC6460_FEEDBACK_VELOCITY_EXT, .isSigned=true })

// FEEDBACK.OUTPUT_CONF fields
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_MUL_FACTOR_MASK                  0x000000FF
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_MUL_FACTOR_SHIFT                 0
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_MUL_FACTOR_FIELD                 ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_MUL_FACTOR_MASK, .shift=TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_MUL_FACTOR_SHIFT, .addr=TMC6460_FEEDBACK_OUTPUT_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_SRC_MASK                         0x00030000
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_SRC_SHIFT                        16
#define TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_SRC_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_SRC_MASK, .shift=TMC6460_FEEDBACK_OUTPUT_CONF_PHI_E_SRC_SHIFT, .addr=TMC6460_FEEDBACK_OUTPUT_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_OUTPUT_CONF_POSITION_SRC_MASK                      0x00100000
#define TMC6460_FEEDBACK_OUTPUT_CONF_POSITION_SRC_SHIFT                     20
#define TMC6460_FEEDBACK_OUTPUT_CONF_POSITION_SRC_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_OUTPUT_CONF_POSITION_SRC_MASK, .shift=TMC6460_FEEDBACK_OUTPUT_CONF_POSITION_SRC_SHIFT, .addr=TMC6460_FEEDBACK_OUTPUT_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SRC_MASK                      0x00200000
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SRC_SHIFT                     21
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SRC_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SRC_MASK, .shift=TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SRC_SHIFT, .addr=TMC6460_FEEDBACK_OUTPUT_CONF, .isSigned=false })
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SELECTION_MASK                0x00C00000
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SELECTION_SHIFT               22
#define TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SELECTION_FIELD               ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SELECTION_MASK, .shift=TMC6460_FEEDBACK_OUTPUT_CONF_VELOCITY_SELECTION_SHIFT, .addr=TMC6460_FEEDBACK_OUTPUT_CONF, .isSigned=false })

// FEEDBACK.PHI_E fields
#define TMC6460_FEEDBACK_PHI_E_PHI_E_FOC_MASK                               0x0000FFFF
#define TMC6460_FEEDBACK_PHI_E_PHI_E_FOC_SHIFT                              0
#define TMC6460_FEEDBACK_PHI_E_PHI_E_FOC_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_E_PHI_E_FOC_MASK, .shift=TMC6460_FEEDBACK_PHI_E_PHI_E_FOC_SHIFT, .addr=TMC6460_FEEDBACK_PHI_E, .isSigned=false })

// FEEDBACK.PHI_DIFF_LIMIT fields
#define TMC6460_FEEDBACK_PHI_DIFF_LIMIT_MASK                                0x0000FFFF
#define TMC6460_FEEDBACK_PHI_DIFF_LIMIT_SHIFT                               0
#define TMC6460_FEEDBACK_PHI_DIFF_LIMIT_FIELD                               ((TMC6460RegisterField) {.mask=TMC6460_FEEDBACK_PHI_DIFF_LIMIT_MASK, .shift=TMC6460_FEEDBACK_PHI_DIFF_LIMIT_SHIFT, .addr=TMC6460_FEEDBACK_PHI_DIFF_LIMIT, .isSigned=false })

// ABN.CONFIG fields
#define TMC6460_ABN_CONFIG_COMBINED_N_MASK                                  0x00000001
#define TMC6460_ABN_CONFIG_COMBINED_N_SHIFT                                 0
#define TMC6460_ABN_CONFIG_COMBINED_N_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_ABN_CONFIG_COMBINED_N_MASK, .shift=TMC6460_ABN_CONFIG_COMBINED_N_SHIFT, .addr=TMC6460_ABN_CONFIG, .isSigned=false })
#define TMC6460_ABN_CONFIG_CLN_MASK                                         0x00000002
#define TMC6460_ABN_CONFIG_CLN_SHIFT                                        1
#define TMC6460_ABN_CONFIG_CLN_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_ABN_CONFIG_CLN_MASK, .shift=TMC6460_ABN_CONFIG_CLN_SHIFT, .addr=TMC6460_ABN_CONFIG, .isSigned=false })
#define TMC6460_ABN_CONFIG_INV_DIR_MASK                                     0x00000008
#define TMC6460_ABN_CONFIG_INV_DIR_SHIFT                                    3
#define TMC6460_ABN_CONFIG_INV_DIR_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ABN_CONFIG_INV_DIR_MASK, .shift=TMC6460_ABN_CONFIG_INV_DIR_SHIFT, .addr=TMC6460_ABN_CONFIG, .isSigned=false })
#define TMC6460_ABN_CONFIG_CPR_MASK                                         0xFFFFFF00
#define TMC6460_ABN_CONFIG_CPR_SHIFT                                        8
#define TMC6460_ABN_CONFIG_CPR_FIELD                                        ((TMC6460RegisterField) {.mask=TMC6460_ABN_CONFIG_CPR_MASK, .shift=TMC6460_ABN_CONFIG_CPR_SHIFT, .addr=TMC6460_ABN_CONFIG, .isSigned=false })

// ABN.COUNT fields
#define TMC6460_ABN_COUNT_MASK                                              0x00FFFFFF
#define TMC6460_ABN_COUNT_SHIFT                                             0
#define TMC6460_ABN_COUNT_FIELD                                             ((TMC6460RegisterField) {.mask=TMC6460_ABN_COUNT_MASK, .shift=TMC6460_ABN_COUNT_SHIFT, .addr=TMC6460_ABN_COUNT, .isSigned=false })

// ABN.COUNT_N_CAPTURE fields
#define TMC6460_ABN_COUNT_N_CAPTURE_MASK                                    0x00FFFFFF
#define TMC6460_ABN_COUNT_N_CAPTURE_SHIFT                                   0
#define TMC6460_ABN_COUNT_N_CAPTURE_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_ABN_COUNT_N_CAPTURE_MASK, .shift=TMC6460_ABN_COUNT_N_CAPTURE_SHIFT, .addr=TMC6460_ABN_COUNT_N_CAPTURE, .isSigned=false })

// ABN.COUNT_N_WRITE fields
#define TMC6460_ABN_COUNT_N_WRITE_MASK                                      0x00FFFFFF
#define TMC6460_ABN_COUNT_N_WRITE_SHIFT                                     0
#define TMC6460_ABN_COUNT_N_WRITE_FIELD                                     ((TMC6460RegisterField) {.mask=TMC6460_ABN_COUNT_N_WRITE_MASK, .shift=TMC6460_ABN_COUNT_N_WRITE_SHIFT, .addr=TMC6460_ABN_COUNT_N_WRITE, .isSigned=false })

// ABN.EVENTS fields
#define TMC6460_ABN_EVENTS_INVALID_SIGNAL_EVENT_MASK                        0x00000001
#define TMC6460_ABN_EVENTS_INVALID_SIGNAL_EVENT_SHIFT                       0
#define TMC6460_ABN_EVENTS_INVALID_SIGNAL_EVENT_FIELD                       ((TMC6460RegisterField) {.mask=TMC6460_ABN_EVENTS_INVALID_SIGNAL_EVENT_MASK, .shift=TMC6460_ABN_EVENTS_INVALID_SIGNAL_EVENT_SHIFT, .addr=TMC6460_ABN_EVENTS, .isSigned=false })
#define TMC6460_ABN_EVENTS_N_EVENT_MASK                                     0x00000002
#define TMC6460_ABN_EVENTS_N_EVENT_SHIFT                                    1
#define TMC6460_ABN_EVENTS_N_EVENT_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ABN_EVENTS_N_EVENT_MASK, .shift=TMC6460_ABN_EVENTS_N_EVENT_SHIFT, .addr=TMC6460_ABN_EVENTS, .isSigned=false })

// ABN2.CONFIG fields
#define TMC6460_ABN2_CONFIG_COMBINED_N_MASK                                 0x00000001
#define TMC6460_ABN2_CONFIG_COMBINED_N_SHIFT                                0
#define TMC6460_ABN2_CONFIG_COMBINED_N_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_ABN2_CONFIG_COMBINED_N_MASK, .shift=TMC6460_ABN2_CONFIG_COMBINED_N_SHIFT, .addr=TMC6460_ABN2_CONFIG, .isSigned=false })
#define TMC6460_ABN2_CONFIG_CLN_MASK                                        0x00000002
#define TMC6460_ABN2_CONFIG_CLN_SHIFT                                       1
#define TMC6460_ABN2_CONFIG_CLN_FIELD                                       ((TMC6460RegisterField) {.mask=TMC6460_ABN2_CONFIG_CLN_MASK, .shift=TMC6460_ABN2_CONFIG_CLN_SHIFT, .addr=TMC6460_ABN2_CONFIG, .isSigned=false })
#define TMC6460_ABN2_CONFIG_INV_DIR_MASK                                    0x00000008
#define TMC6460_ABN2_CONFIG_INV_DIR_SHIFT                                   3
#define TMC6460_ABN2_CONFIG_INV_DIR_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_ABN2_CONFIG_INV_DIR_MASK, .shift=TMC6460_ABN2_CONFIG_INV_DIR_SHIFT, .addr=TMC6460_ABN2_CONFIG, .isSigned=false })
#define TMC6460_ABN2_CONFIG_CPR_MASK                                        0xFFFFFF00
#define TMC6460_ABN2_CONFIG_CPR_SHIFT                                       8
#define TMC6460_ABN2_CONFIG_CPR_FIELD                                       ((TMC6460RegisterField) {.mask=TMC6460_ABN2_CONFIG_CPR_MASK, .shift=TMC6460_ABN2_CONFIG_CPR_SHIFT, .addr=TMC6460_ABN2_CONFIG, .isSigned=false })

// ABN2.COUNT fields
#define TMC6460_ABN2_COUNT_MASK                                             0x00FFFFFF
#define TMC6460_ABN2_COUNT_SHIFT                                            0
#define TMC6460_ABN2_COUNT_FIELD                                            ((TMC6460RegisterField) {.mask=TMC6460_ABN2_COUNT_MASK, .shift=TMC6460_ABN2_COUNT_SHIFT, .addr=TMC6460_ABN2_COUNT, .isSigned=false })

// ABN2.COUNT_N_CAPTURE fields
#define TMC6460_ABN2_COUNT_N_CAPTURE_MASK                                   0x00FFFFFF
#define TMC6460_ABN2_COUNT_N_CAPTURE_SHIFT                                  0
#define TMC6460_ABN2_COUNT_N_CAPTURE_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_ABN2_COUNT_N_CAPTURE_MASK, .shift=TMC6460_ABN2_COUNT_N_CAPTURE_SHIFT, .addr=TMC6460_ABN2_COUNT_N_CAPTURE, .isSigned=false })

// ABN2.COUNT_N_WRITE fields
#define TMC6460_ABN2_COUNT_N_WRITE_MASK                                     0x00FFFFFF
#define TMC6460_ABN2_COUNT_N_WRITE_SHIFT                                    0
#define TMC6460_ABN2_COUNT_N_WRITE_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_ABN2_COUNT_N_WRITE_MASK, .shift=TMC6460_ABN2_COUNT_N_WRITE_SHIFT, .addr=TMC6460_ABN2_COUNT_N_WRITE, .isSigned=false })

// ABN2.EVENTS fields
#define TMC6460_ABN2_EVENTS_INVALID_SIGNAL_EVENT_MASK                       0x00000001
#define TMC6460_ABN2_EVENTS_INVALID_SIGNAL_EVENT_SHIFT                      0
#define TMC6460_ABN2_EVENTS_INVALID_SIGNAL_EVENT_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_ABN2_EVENTS_INVALID_SIGNAL_EVENT_MASK, .shift=TMC6460_ABN2_EVENTS_INVALID_SIGNAL_EVENT_SHIFT, .addr=TMC6460_ABN2_EVENTS, .isSigned=false })
#define TMC6460_ABN2_EVENTS_N_EVENT_MASK                                    0x00000002
#define TMC6460_ABN2_EVENTS_N_EVENT_SHIFT                                   1
#define TMC6460_ABN2_EVENTS_N_EVENT_FIELD                                   ((TMC6460RegisterField) {.mask=TMC6460_ABN2_EVENTS_N_EVENT_MASK, .shift=TMC6460_ABN2_EVENTS_N_EVENT_SHIFT, .addr=TMC6460_ABN2_EVENTS, .isSigned=false })

// HALL.MAP_CONFIG fields
#define TMC6460_HALL_MAP_CONFIG_HALL_MAP_MASK                               0x00000007
#define TMC6460_HALL_MAP_CONFIG_HALL_MAP_SHIFT                              0
#define TMC6460_HALL_MAP_CONFIG_HALL_MAP_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_HALL_MAP_CONFIG_HALL_MAP_MASK, .shift=TMC6460_HALL_MAP_CONFIG_HALL_MAP_SHIFT, .addr=TMC6460_HALL_MAP_CONFIG, .isSigned=false })
#define TMC6460_HALL_MAP_CONFIG_ANA_HALL_MAP_MASK                           0x00000070
#define TMC6460_HALL_MAP_CONFIG_ANA_HALL_MAP_SHIFT                          4
#define TMC6460_HALL_MAP_CONFIG_ANA_HALL_MAP_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_HALL_MAP_CONFIG_ANA_HALL_MAP_MASK, .shift=TMC6460_HALL_MAP_CONFIG_ANA_HALL_MAP_SHIFT, .addr=TMC6460_HALL_MAP_CONFIG, .isSigned=false })

// HALL.DIG_COUNT fields
#define TMC6460_HALL_DIG_COUNT_COUNT_MASK                                   0x00000007
#define TMC6460_HALL_DIG_COUNT_COUNT_SHIFT                                  0
#define TMC6460_HALL_DIG_COUNT_COUNT_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_HALL_DIG_COUNT_COUNT_MASK, .shift=TMC6460_HALL_DIG_COUNT_COUNT_SHIFT, .addr=TMC6460_HALL_DIG_COUNT, .isSigned=false })

// HALL.ANA_CONFIG fields
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_THRESHOLD_MASK                      0x0000FFFF
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_THRESHOLD_SHIFT                     0
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_THRESHOLD_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_N_PULSE_THRESHOLD_MASK, .shift=TMC6460_HALL_ANA_CONFIG_N_PULSE_THRESHOLD_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=true })
#define TMC6460_HALL_ANA_CONFIG_ANA_MODE_MASK                               0x00010000
#define TMC6460_HALL_ANA_CONFIG_ANA_MODE_SHIFT                              16
#define TMC6460_HALL_ANA_CONFIG_ANA_MODE_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_ANA_MODE_MASK, .shift=TMC6460_HALL_ANA_CONFIG_ANA_MODE_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_EDGE_MASK                           0x00020000
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_EDGE_SHIFT                          17
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_EDGE_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_N_PULSE_EDGE_MASK, .shift=TMC6460_HALL_ANA_CONFIG_N_PULSE_EDGE_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_POL_MASK                            0x00040000
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_POL_SHIFT                           18
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_POL_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_N_PULSE_POL_MASK, .shift=TMC6460_HALL_ANA_CONFIG_N_PULSE_POL_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_TWO_CYCLE_MODE_EN_MASK                      0x00080000
#define TMC6460_HALL_ANA_CONFIG_TWO_CYCLE_MODE_EN_SHIFT                     19
#define TMC6460_HALL_ANA_CONFIG_TWO_CYCLE_MODE_EN_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_TWO_CYCLE_MODE_EN_MASK, .shift=TMC6460_HALL_ANA_CONFIG_TWO_CYCLE_MODE_EN_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_USE_N_PULSE_MASK                            0x00100000
#define TMC6460_HALL_ANA_CONFIG_USE_N_PULSE_SHIFT                           20
#define TMC6460_HALL_ANA_CONFIG_USE_N_PULSE_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_USE_N_PULSE_MASK, .shift=TMC6460_HALL_ANA_CONFIG_USE_N_PULSE_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_OUT_MASK                            0x00200000
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_OUT_SHIFT                           21
#define TMC6460_HALL_ANA_CONFIG_N_PULSE_OUT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_N_PULSE_OUT_MASK, .shift=TMC6460_HALL_ANA_CONFIG_N_PULSE_OUT_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })
#define TMC6460_HALL_ANA_CONFIG_ADC_CLIPPED_MASK                            0x00400000
#define TMC6460_HALL_ANA_CONFIG_ADC_CLIPPED_SHIFT                           22
#define TMC6460_HALL_ANA_CONFIG_ADC_CLIPPED_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_CONFIG_ADC_CLIPPED_MASK, .shift=TMC6460_HALL_ANA_CONFIG_ADC_CLIPPED_SHIFT, .addr=TMC6460_HALL_ANA_CONFIG, .isSigned=false })

// HALL.ANA_UX_CONFIG fields
#define TMC6460_HALL_ANA_UX_CONFIG_UX_OFFSET_MASK                           0x0000FFFF
#define TMC6460_HALL_ANA_UX_CONFIG_UX_OFFSET_SHIFT                          0
#define TMC6460_HALL_ANA_UX_CONFIG_UX_OFFSET_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_UX_CONFIG_UX_OFFSET_MASK, .shift=TMC6460_HALL_ANA_UX_CONFIG_UX_OFFSET_SHIFT, .addr=TMC6460_HALL_ANA_UX_CONFIG, .isSigned=true })
#define TMC6460_HALL_ANA_UX_CONFIG_UX_SCALE_MASK                            0xFFFF0000
#define TMC6460_HALL_ANA_UX_CONFIG_UX_SCALE_SHIFT                           16
#define TMC6460_HALL_ANA_UX_CONFIG_UX_SCALE_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_UX_CONFIG_UX_SCALE_MASK, .shift=TMC6460_HALL_ANA_UX_CONFIG_UX_SCALE_SHIFT, .addr=TMC6460_HALL_ANA_UX_CONFIG, .isSigned=true })

// HALL.ANA_VN_CONFIG fields
#define TMC6460_HALL_ANA_VN_CONFIG_VN_OFFSET_MASK                           0x0000FFFF
#define TMC6460_HALL_ANA_VN_CONFIG_VN_OFFSET_SHIFT                          0
#define TMC6460_HALL_ANA_VN_CONFIG_VN_OFFSET_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_VN_CONFIG_VN_OFFSET_MASK, .shift=TMC6460_HALL_ANA_VN_CONFIG_VN_OFFSET_SHIFT, .addr=TMC6460_HALL_ANA_VN_CONFIG, .isSigned=true })
#define TMC6460_HALL_ANA_VN_CONFIG_VN_SCALE_MASK                            0xFFFF0000
#define TMC6460_HALL_ANA_VN_CONFIG_VN_SCALE_SHIFT                           16
#define TMC6460_HALL_ANA_VN_CONFIG_VN_SCALE_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_VN_CONFIG_VN_SCALE_MASK, .shift=TMC6460_HALL_ANA_VN_CONFIG_VN_SCALE_SHIFT, .addr=TMC6460_HALL_ANA_VN_CONFIG, .isSigned=true })

// HALL.ANA_WY_CONFIG fields
#define TMC6460_HALL_ANA_WY_CONFIG_WY_OFFSET_MASK                           0x0000FFFF
#define TMC6460_HALL_ANA_WY_CONFIG_WY_OFFSET_SHIFT                          0
#define TMC6460_HALL_ANA_WY_CONFIG_WY_OFFSET_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_WY_CONFIG_WY_OFFSET_MASK, .shift=TMC6460_HALL_ANA_WY_CONFIG_WY_OFFSET_SHIFT, .addr=TMC6460_HALL_ANA_WY_CONFIG, .isSigned=true })
#define TMC6460_HALL_ANA_WY_CONFIG_WY_SCALE_MASK                            0xFFFF0000
#define TMC6460_HALL_ANA_WY_CONFIG_WY_SCALE_SHIFT                           16
#define TMC6460_HALL_ANA_WY_CONFIG_WY_SCALE_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_WY_CONFIG_WY_SCALE_MASK, .shift=TMC6460_HALL_ANA_WY_CONFIG_WY_SCALE_SHIFT, .addr=TMC6460_HALL_ANA_WY_CONFIG, .isSigned=true })

// HALL.ANA_UX_OUT fields
#define TMC6460_HALL_ANA_UX_OUT_UX_OUT_MASK                                 0x0000FFFF
#define TMC6460_HALL_ANA_UX_OUT_UX_OUT_SHIFT                                0
#define TMC6460_HALL_ANA_UX_OUT_UX_OUT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_UX_OUT_UX_OUT_MASK, .shift=TMC6460_HALL_ANA_UX_OUT_UX_OUT_SHIFT, .addr=TMC6460_HALL_ANA_UX_OUT, .isSigned=true })

// HALL.ANA_VN_OUT fields
#define TMC6460_HALL_ANA_VN_OUT_VN_OUT_MASK                                 0x0000FFFF
#define TMC6460_HALL_ANA_VN_OUT_VN_OUT_SHIFT                                0
#define TMC6460_HALL_ANA_VN_OUT_VN_OUT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_VN_OUT_VN_OUT_MASK, .shift=TMC6460_HALL_ANA_VN_OUT_VN_OUT_SHIFT, .addr=TMC6460_HALL_ANA_VN_OUT, .isSigned=true })

// HALL.ANA_WY_OUT fields
#define TMC6460_HALL_ANA_WY_OUT_WY_OUT_MASK                                 0x0000FFFF
#define TMC6460_HALL_ANA_WY_OUT_WY_OUT_SHIFT                                0
#define TMC6460_HALL_ANA_WY_OUT_WY_OUT_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_WY_OUT_WY_OUT_MASK, .shift=TMC6460_HALL_ANA_WY_OUT_WY_OUT_SHIFT, .addr=TMC6460_HALL_ANA_WY_OUT, .isSigned=true })

// HALL.ANA_OUT fields
#define TMC6460_HALL_ANA_OUT_ANA_PHI_N_CAPTURE_MASK                         0x0000FFFF
#define TMC6460_HALL_ANA_OUT_ANA_PHI_N_CAPTURE_SHIFT                        0
#define TMC6460_HALL_ANA_OUT_ANA_PHI_N_CAPTURE_FIELD                        ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_OUT_ANA_PHI_N_CAPTURE_MASK, .shift=TMC6460_HALL_ANA_OUT_ANA_PHI_N_CAPTURE_SHIFT, .addr=TMC6460_HALL_ANA_OUT, .isSigned=false })
#define TMC6460_HALL_ANA_OUT_ANA_PHI_MASK                                   0xFFFF0000
#define TMC6460_HALL_ANA_OUT_ANA_PHI_SHIFT                                  16
#define TMC6460_HALL_ANA_OUT_ANA_PHI_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_HALL_ANA_OUT_ANA_PHI_MASK, .shift=TMC6460_HALL_ANA_OUT_ANA_PHI_SHIFT, .addr=TMC6460_HALL_ANA_OUT, .isSigned=false })

// HALL.DIG_EVENTS fields
#define TMC6460_HALL_DIG_EVENTS_INVALID_SIGNAL_EVENT_MASK                   0x00000001
#define TMC6460_HALL_DIG_EVENTS_INVALID_SIGNAL_EVENT_SHIFT                  0
#define TMC6460_HALL_DIG_EVENTS_INVALID_SIGNAL_EVENT_FIELD                  ((TMC6460RegisterField) {.mask=TMC6460_HALL_DIG_EVENTS_INVALID_SIGNAL_EVENT_MASK, .shift=TMC6460_HALL_DIG_EVENTS_INVALID_SIGNAL_EVENT_SHIFT, .addr=TMC6460_HALL_DIG_EVENTS, .isSigned=false })

// UART.CONTROL fields
#define TMC6460_UART_CONTROL_MANTISSA_LIMIT_MASK                            0x00001FFF
#define TMC6460_UART_CONTROL_MANTISSA_LIMIT_SHIFT                           0
#define TMC6460_UART_CONTROL_MANTISSA_LIMIT_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_MANTISSA_LIMIT_MASK, .shift=TMC6460_UART_CONTROL_MANTISSA_LIMIT_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_TIMEOUT_PRE_DIVIDER_EN_MASK                    0x00010000
#define TMC6460_UART_CONTROL_TIMEOUT_PRE_DIVIDER_EN_SHIFT                   16
#define TMC6460_UART_CONTROL_TIMEOUT_PRE_DIVIDER_EN_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_TIMEOUT_PRE_DIVIDER_EN_MASK, .shift=TMC6460_UART_CONTROL_TIMEOUT_PRE_DIVIDER_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_AUTOBAUD_EN_MASK                               0x00040000
#define TMC6460_UART_CONTROL_AUTOBAUD_EN_SHIFT                              18
#define TMC6460_UART_CONTROL_AUTOBAUD_EN_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_AUTOBAUD_EN_MASK, .shift=TMC6460_UART_CONTROL_AUTOBAUD_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_RX_FILTER_EN_MASK                              0x00080000
#define TMC6460_UART_CONTROL_RX_FILTER_EN_SHIFT                             19
#define TMC6460_UART_CONTROL_RX_FILTER_EN_FIELD                             ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_RX_FILTER_EN_MASK, .shift=TMC6460_UART_CONTROL_RX_FILTER_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_NORMAL_CRC_EN_MASK                             0x00100000
#define TMC6460_UART_CONTROL_NORMAL_CRC_EN_SHIFT                            20
#define TMC6460_UART_CONTROL_NORMAL_CRC_EN_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_NORMAL_CRC_EN_MASK, .shift=TMC6460_UART_CONTROL_NORMAL_CRC_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_RTMI_CRC_EN_MASK                               0x00200000
#define TMC6460_UART_CONTROL_RTMI_CRC_EN_SHIFT                              21
#define TMC6460_UART_CONTROL_RTMI_CRC_EN_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_RTMI_CRC_EN_MASK, .shift=TMC6460_UART_CONTROL_RTMI_CRC_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_RTMI_EN_MASK                                   0x00400000
#define TMC6460_UART_CONTROL_RTMI_EN_SHIFT                                  22
#define TMC6460_UART_CONTROL_RTMI_EN_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_RTMI_EN_MASK, .shift=TMC6460_UART_CONTROL_RTMI_EN_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })
#define TMC6460_UART_CONTROL_RTMI_SAMPLING_MASK                             0xFF000000
#define TMC6460_UART_CONTROL_RTMI_SAMPLING_SHIFT                            24
#define TMC6460_UART_CONTROL_RTMI_SAMPLING_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_UART_CONTROL_RTMI_SAMPLING_MASK, .shift=TMC6460_UART_CONTROL_RTMI_SAMPLING_SHIFT, .addr=TMC6460_UART_CONTROL, .isSigned=false })

// UART.TIMEOUT fields
#define TMC6460_UART_TIMEOUT_LIMIT_MASK                                     0x0000FFFF
#define TMC6460_UART_TIMEOUT_LIMIT_SHIFT                                    0
#define TMC6460_UART_TIMEOUT_LIMIT_FIELD                                    ((TMC6460RegisterField) {.mask=TMC6460_UART_TIMEOUT_LIMIT_MASK, .shift=TMC6460_UART_TIMEOUT_LIMIT_SHIFT, .addr=TMC6460_UART_TIMEOUT, .isSigned=false })
#define TMC6460_UART_TIMEOUT_COUNTER_MASK                                   0xFFFF0000
#define TMC6460_UART_TIMEOUT_COUNTER_SHIFT                                  16
#define TMC6460_UART_TIMEOUT_COUNTER_FIELD                                  ((TMC6460RegisterField) {.mask=TMC6460_UART_TIMEOUT_COUNTER_MASK, .shift=TMC6460_UART_TIMEOUT_COUNTER_SHIFT, .addr=TMC6460_UART_TIMEOUT, .isSigned=false })

// UART.STATUS fields
#define TMC6460_UART_STATUS_RX_ACTIVE_MASK                                  0x00000001
#define TMC6460_UART_STATUS_RX_ACTIVE_SHIFT                                 0
#define TMC6460_UART_STATUS_RX_ACTIVE_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_UART_STATUS_RX_ACTIVE_MASK, .shift=TMC6460_UART_STATUS_RX_ACTIVE_SHIFT, .addr=TMC6460_UART_STATUS, .isSigned=false })
#define TMC6460_UART_STATUS_TX_ACTIVE_MASK                                  0x00000004
#define TMC6460_UART_STATUS_TX_ACTIVE_SHIFT                                 2
#define TMC6460_UART_STATUS_TX_ACTIVE_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_UART_STATUS_TX_ACTIVE_MASK, .shift=TMC6460_UART_STATUS_TX_ACTIVE_SHIFT, .addr=TMC6460_UART_STATUS, .isSigned=false })
#define TMC6460_UART_STATUS_AUTOBAUD_VALID_MASK                             0x00000010
#define TMC6460_UART_STATUS_AUTOBAUD_VALID_SHIFT                            4
#define TMC6460_UART_STATUS_AUTOBAUD_VALID_FIELD                            ((TMC6460RegisterField) {.mask=TMC6460_UART_STATUS_AUTOBAUD_VALID_MASK, .shift=TMC6460_UART_STATUS_AUTOBAUD_VALID_SHIFT, .addr=TMC6460_UART_STATUS, .isSigned=false })

// UART.EVENTS fields
#define TMC6460_UART_EVENTS_UART_SYNC_FAIL_EVENT_MASK                       0x00000001
#define TMC6460_UART_EVENTS_UART_SYNC_FAIL_EVENT_SHIFT                      0
#define TMC6460_UART_EVENTS_UART_SYNC_FAIL_EVENT_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_UART_SYNC_FAIL_EVENT_MASK, .shift=TMC6460_UART_EVENTS_UART_SYNC_FAIL_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_NOISY_DATA_EVENT_MASK                           0x00000004
#define TMC6460_UART_EVENTS_NOISY_DATA_EVENT_SHIFT                          2
#define TMC6460_UART_EVENTS_NOISY_DATA_EVENT_FIELD                          ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_NOISY_DATA_EVENT_MASK, .shift=TMC6460_UART_EVENTS_NOISY_DATA_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_RTMI_INTERRUPT_EVENT_MASK                       0x00000008
#define TMC6460_UART_EVENTS_RTMI_INTERRUPT_EVENT_SHIFT                      3
#define TMC6460_UART_EVENTS_RTMI_INTERRUPT_EVENT_FIELD                      ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_RTMI_INTERRUPT_EVENT_MASK, .shift=TMC6460_UART_EVENTS_RTMI_INTERRUPT_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_RX_IDLE_TIMEOUT_EVENT_MASK                      0x00000010
#define TMC6460_UART_EVENTS_RX_IDLE_TIMEOUT_EVENT_SHIFT                     4
#define TMC6460_UART_EVENTS_RX_IDLE_TIMEOUT_EVENT_FIELD                     ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_RX_IDLE_TIMEOUT_EVENT_MASK, .shift=TMC6460_UART_EVENTS_RX_IDLE_TIMEOUT_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_INVALID_START_BIT_EVENT_MASK                    0x00000020
#define TMC6460_UART_EVENTS_INVALID_START_BIT_EVENT_SHIFT                   5
#define TMC6460_UART_EVENTS_INVALID_START_BIT_EVENT_FIELD                   ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_INVALID_START_BIT_EVENT_MASK, .shift=TMC6460_UART_EVENTS_INVALID_START_BIT_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_INVALID_STOP_BIT_EVENT_MASK                     0x00000040
#define TMC6460_UART_EVENTS_INVALID_STOP_BIT_EVENT_SHIFT                    6
#define TMC6460_UART_EVENTS_INVALID_STOP_BIT_EVENT_FIELD                    ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_INVALID_STOP_BIT_EVENT_MASK, .shift=TMC6460_UART_EVENTS_INVALID_STOP_BIT_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })
#define TMC6460_UART_EVENTS_INVALID_CRC_EVENT_MASK                          0x00000080
#define TMC6460_UART_EVENTS_INVALID_CRC_EVENT_SHIFT                         7
#define TMC6460_UART_EVENTS_INVALID_CRC_EVENT_FIELD                         ((TMC6460RegisterField) {.mask=TMC6460_UART_EVENTS_INVALID_CRC_EVENT_MASK, .shift=TMC6460_UART_EVENTS_INVALID_CRC_EVENT_SHIFT, .addr=TMC6460_UART_EVENTS, .isSigned=false })

// UART.RTMI_CH_0 fields
#define TMC6460_UART_RTMI_CH_0_CH_0_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_0_CH_0_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_0_CH_0_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_0_CH_0_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_0_CH_0_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_0, .isSigned=false })
#define TMC6460_UART_RTMI_CH_0_CH_0_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_0_CH_0_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_0_CH_0_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_0_CH_0_EN_MASK, .shift=TMC6460_UART_RTMI_CH_0_CH_0_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_0, .isSigned=false })

// UART.RTMI_CH_1 fields
#define TMC6460_UART_RTMI_CH_1_CH_1_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_1_CH_1_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_1_CH_1_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_1_CH_1_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_1_CH_1_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_1, .isSigned=false })
#define TMC6460_UART_RTMI_CH_1_CH_1_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_1_CH_1_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_1_CH_1_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_1_CH_1_EN_MASK, .shift=TMC6460_UART_RTMI_CH_1_CH_1_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_1, .isSigned=false })

// UART.RTMI_CH_2 fields
#define TMC6460_UART_RTMI_CH_2_CH_2_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_2_CH_2_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_2_CH_2_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_2_CH_2_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_2_CH_2_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_2, .isSigned=false })
#define TMC6460_UART_RTMI_CH_2_CH_2_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_2_CH_2_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_2_CH_2_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_2_CH_2_EN_MASK, .shift=TMC6460_UART_RTMI_CH_2_CH_2_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_2, .isSigned=false })

// UART.RTMI_CH_3 fields
#define TMC6460_UART_RTMI_CH_3_CH_3_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_3_CH_3_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_3_CH_3_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_3_CH_3_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_3_CH_3_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_3, .isSigned=false })
#define TMC6460_UART_RTMI_CH_3_CH_3_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_3_CH_3_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_3_CH_3_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_3_CH_3_EN_MASK, .shift=TMC6460_UART_RTMI_CH_3_CH_3_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_3, .isSigned=false })

// UART.RTMI_CH_4 fields
#define TMC6460_UART_RTMI_CH_4_CH_4_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_4_CH_4_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_4_CH_4_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_4_CH_4_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_4_CH_4_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_4, .isSigned=false })
#define TMC6460_UART_RTMI_CH_4_CH_4_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_4_CH_4_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_4_CH_4_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_4_CH_4_EN_MASK, .shift=TMC6460_UART_RTMI_CH_4_CH_4_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_4, .isSigned=false })

// UART.RTMI_CH_5 fields
#define TMC6460_UART_RTMI_CH_5_CH_5_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_5_CH_5_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_5_CH_5_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_5_CH_5_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_5_CH_5_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_5, .isSigned=false })
#define TMC6460_UART_RTMI_CH_5_CH_5_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_5_CH_5_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_5_CH_5_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_5_CH_5_EN_MASK, .shift=TMC6460_UART_RTMI_CH_5_CH_5_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_5, .isSigned=false })

// UART.RTMI_CH_6 fields
#define TMC6460_UART_RTMI_CH_6_CH_6_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_6_CH_6_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_6_CH_6_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_6_CH_6_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_6_CH_6_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_6, .isSigned=false })
#define TMC6460_UART_RTMI_CH_6_CH_6_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_6_CH_6_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_6_CH_6_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_6_CH_6_EN_MASK, .shift=TMC6460_UART_RTMI_CH_6_CH_6_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_6, .isSigned=false })

// UART.RTMI_CH_7 fields
#define TMC6460_UART_RTMI_CH_7_CH_7_ADDR_MASK                               0x000003FF
#define TMC6460_UART_RTMI_CH_7_CH_7_ADDR_SHIFT                              0
#define TMC6460_UART_RTMI_CH_7_CH_7_ADDR_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_7_CH_7_ADDR_MASK, .shift=TMC6460_UART_RTMI_CH_7_CH_7_ADDR_SHIFT, .addr=TMC6460_UART_RTMI_CH_7, .isSigned=false })
#define TMC6460_UART_RTMI_CH_7_CH_7_EN_MASK                                 0x00010000
#define TMC6460_UART_RTMI_CH_7_CH_7_EN_SHIFT                                16
#define TMC6460_UART_RTMI_CH_7_CH_7_EN_FIELD                                ((TMC6460RegisterField) {.mask=TMC6460_UART_RTMI_CH_7_CH_7_EN_MASK, .shift=TMC6460_UART_RTMI_CH_7_CH_7_EN_SHIFT, .addr=TMC6460_UART_RTMI_CH_7, .isSigned=false })

// IO_CONTROLLER.CONTROL fields
#define TMC6460_IO_CONTROLLER_CONTROL_RESET_MASK                            0x00000001
#define TMC6460_IO_CONTROLLER_CONTROL_RESET_SHIFT                           0
#define TMC6460_IO_CONTROLLER_CONTROL_RESET_FIELD                           ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_CONTROL_RESET_MASK, .shift=TMC6460_IO_CONTROLLER_CONTROL_RESET_SHIFT, .addr=TMC6460_IO_CONTROLLER_CONTROL, .isSigned=false })

// IO_CONTROLLER.COMMAND fields
#define TMC6460_IO_CONTROLLER_COMMAND_MASK                                  0xFFFFFFFF
#define TMC6460_IO_CONTROLLER_COMMAND_SHIFT                                 0
#define TMC6460_IO_CONTROLLER_COMMAND_FIELD                                 ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_COMMAND_MASK, .shift=TMC6460_IO_CONTROLLER_COMMAND_SHIFT, .addr=TMC6460_IO_CONTROLLER_COMMAND, .isSigned=false })

// IO_CONTROLLER.RESPONSE_0 fields
#define TMC6460_IO_CONTROLLER_RESPONSE_0_MASK                               0xFFFFFFFF
#define TMC6460_IO_CONTROLLER_RESPONSE_0_SHIFT                              0
#define TMC6460_IO_CONTROLLER_RESPONSE_0_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_RESPONSE_0_MASK, .shift=TMC6460_IO_CONTROLLER_RESPONSE_0_SHIFT, .addr=TMC6460_IO_CONTROLLER_RESPONSE_0, .isSigned=false })

// IO_CONTROLLER.RESPONSE_1 fields
#define TMC6460_IO_CONTROLLER_RESPONSE_1_MASK                               0xFFFFFFFF
#define TMC6460_IO_CONTROLLER_RESPONSE_1_SHIFT                              0
#define TMC6460_IO_CONTROLLER_RESPONSE_1_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_RESPONSE_1_MASK, .shift=TMC6460_IO_CONTROLLER_RESPONSE_1_SHIFT, .addr=TMC6460_IO_CONTROLLER_RESPONSE_1, .isSigned=false })

// IO_CONTROLLER.RESPONSE_2 fields
#define TMC6460_IO_CONTROLLER_RESPONSE_2_MASK                               0xFFFFFFFF
#define TMC6460_IO_CONTROLLER_RESPONSE_2_SHIFT                              0
#define TMC6460_IO_CONTROLLER_RESPONSE_2_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_RESPONSE_2_MASK, .shift=TMC6460_IO_CONTROLLER_RESPONSE_2_SHIFT, .addr=TMC6460_IO_CONTROLLER_RESPONSE_2, .isSigned=false })

// IO_CONTROLLER.RESPONSE_3 fields
#define TMC6460_IO_CONTROLLER_RESPONSE_3_MASK                               0xFFFFFFFF
#define TMC6460_IO_CONTROLLER_RESPONSE_3_SHIFT                              0
#define TMC6460_IO_CONTROLLER_RESPONSE_3_FIELD                              ((TMC6460RegisterField) {.mask=TMC6460_IO_CONTROLLER_RESPONSE_3_MASK, .shift=TMC6460_IO_CONTROLLER_RESPONSE_3_SHIFT, .addr=TMC6460_IO_CONTROLLER_RESPONSE_3, .isSigned=false })

#endif /* TMC_IC_TMC6460_HW_ABSTRACTION_H_ */
