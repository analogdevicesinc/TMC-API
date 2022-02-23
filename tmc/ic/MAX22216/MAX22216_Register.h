/*
 * MAX22216_Registers.h
 *
 *  Created on: 04.09.2018
 *      Author: LK
 */

#ifndef MAX22216_REGISTERS_H
#define MAX22216_REGISTERS_H

// ===== MAX22216 register set =====

#define MAX22216_CHIPINFO_DATA                      0x00
#define MAX22216_CHIPINFO_ADDR                      0x01

#define MAX22216_dsADC_MCFG_B_MCFG_A                0x04
#define MAX22216_dsADC_MCLK_A                       0x05
#define MAX22216_dsADC_MCLK_B                       0x06
#define MAX22216_dsADC_MDEC_B_MDEC_A                0x07

#define MAX22216_ADC_I0_SCALE_OFFSET                0x09
#define MAX22216_COIL                               0x10

#define MAX22216_ADC_I0                             0x12
#define MAX22216_ADC_VM_RAW                         0x14

#define MAX22216_PWM_POLARITIES                     0x17
#define MAX22216_PWM_MAXCNT                         0x18
#define MAX22216_PWM_BBM_H_BBM_L                    0x19
#define MAX22216_PWM_SV_CHOP                        0x1A

#define MAX22216_CARRIER_FRQ                        0x21
#define MAX22216_CARRIER_AMP                        0x24

#define MAX22216_PWM_CNTL_L2H_TIME_L2H              0x41
#define MAX22216_PWM_CNTL_H2L_TIME_H2L              0x42
#define MAX22216_PWM_CNTL_HL                        0x43
#define MAX22216_I_DC_I_AC                          0x45
#define MAX22216_I_DC_I_AC_THRESHOLDS               0x46
#define MAX22216_TRAVEL_TIME                        0x47
#define MAX22216_IDCxIAC                            0x4D
#define MAX22216_IDCxIAC_THRESHOLD                  0x4E
#define MAX22216_IDCxIAC_TRAVELTIME                 0x4F

#define MAX22216_UART_BPS                           0x79
#define MAX22216_STATUS_IO                          0x7E

#define MAX22216_STATUS_FLAGS_REF_MASK   0x00700000
#define MAX22216_STATUS_FLAGS_REF_SHIFT  20

#endif /* MAX22216_REGISTERS_H */
