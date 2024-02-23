/*******************************************************************************
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2262_REGISTERS
#define TMC2262_REGISTERS

#define TMC2262_GCONF                      0x00
#define TMC2262_GSTAT                      0x01
#define TMC2262_DIAG_CONF                  0x02
#define TMC2262_DIAG_DAC_CONF              0x03
#define TMC2262_IOIN                       0x04
#define TMC2262_DRV_CONF                   0x0A
#define TMC2262_PLL                        0x0B
#define TMC2262_IHOLD_IRUN                 0x10
#define TMC2262_TPOWERDOWN                 0x11
#define TMC2262_TSTEP                      0x12
#define TMC2262_TPWMTHRS                   0x13
#define TMC2262_TCOOLTHRS                  0x14
#define TMC2262_THIGH                      0x15
#define TMC2262_TSGP_LOW_VEL_THRS          0x16
#define TMC2262_T_RCOIL_MEAS               0x17
#define TMC2262_TUDCSTEP                   0x18
#define TMC2262_UDC_CONF                   0x19
#define TMC2262_STEPS_LOST                 0x1A
#define TMC2262_SW_MODE                    0x34
#define TMC2262_SG_SEQ_STOP_STAT           0x35
#define TMC2262_ENCMODE                    0x38
#define TMC2262_X_ENC                      0x39
#define TMC2262_ENC_CONST                  0x3A
#define TMC2262_ENC_STATUS                 0x3B
#define TMC2262_ENC_LATCH                  0x3C
#define TMC2262_ENC_DEVIATION              0x3D
#define TMC2262_CURRENT_PI_REG             0x40
#define TMC2262_ANGLE_PI_REG               0x41
#define TMC2262_CUR_ANGLE_LIMIT            0x42
#define TMC2262_ANGLE_LOWER_LIMIT          0x43
#define TMC2262_CUR_ANGLE_MEAS             0x44
#define TMC2262_PI_RESULTS                 0x45
#define TMC2262_COIL_INDUCT                0x46
#define TMC2262_R_COIL                     0x47
#define TMC2262_R_COIL_USER                0x48
#define TMC2262_SGP_CONF                   0x49
#define TMC2262_SGP_IND_2_3                0x4A
#define TMC2262_SGP_IND_0_1                0x4B
#define TMC2262_INDUCTANCE_VOLTAGE         0x4C
#define TMC2262_SGP_BEMF                   0x4D
#define TMC2262_COOLSTEPPLUS_CONF          0x4E
#define TMC2262_COOLSTEPPLUS_PI_REG        0x4F
#define TMC2262_COOLSTEPPLUS_PI_DOWN       0x50
#define TMC2262_COOLSTEPPLUS_RESERVE_CONF  0x51
#define TMC2262_COOLSTEPPLUS_LOAD_RESERVE  0x52
#define TMC2262_TSTEP_VELOCITY             0x53
#define TMC2262_ADC_VSUPPLY_TEMP           0x58
#define TMC2262_ADC_I                      0x59
#define TMC2262_OTW_OV_VTH                 0x5A
#define TMC2262_MSLUT__                    0x60
//#define TMC2262_MSLUT__                    0x61
//#define TMC2262_MSLUT__                    0x62
//#define TMC2262_MSLUT__                    0x63
//#define TMC2262_MSLUT__                    0x64
//#define TMC2262_MSLUT__                    0x65
//#define TMC2262_MSLUT__                    0x66
//#define TMC2262_MSLUT__                    0x67
#define TMC2262_MSLUTSEL                   0x68
#define TMC2262_MSLUTSTART                 0x69
#define TMC2262_MSCNT                      0x6A
#define TMC2262_MSCURACT                   0x6B
#define TMC2262_CHOPCONF                   0x6C
#define TMC2262_COOLCONF                   0x6D
#define TMC2262_DRV_STATUS                 0x6F
#define TMC2262_PWMCONF                    0x70

#endif
