/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2660_HW_ABSTRACTION
#define TMC2660_HW_ABSTRACTION

#define TMC2660_MSTEP_MASK                   0x000FFC00
#define TMC2660_MSTEP_SHIFT                  10
#define TMC2660_MSTEP_FIELD                  ((RegisterField) {TMC2660_MSTEP_MASK, TMC2660_MSTEP_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_STST_MASK                    0x00000080
#define TMC2660_STST_SHIFT                   7
#define TMC2660_STST_FIELD                   ((RegisterField) {TMC2660_STST_MASK, TMC2660_STST_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_OLB_MASK                     0x00000040
#define TMC2660_OLB_SHIFT                    6
#define TMC2660_OLB_FIELD                    ((RegisterField) {TMC2660_OLB_MASK, TMC2660_OLB_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_OLA_MASK                     0x00000020
#define TMC2660_OLA_SHIFT                    5
#define TMC2660_OLA_FIELD                    ((RegisterField) {TMC2660_OLA_MASK, TMC2660_OLA_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_S2GB_MASK                    0x00000010
#define TMC2660_S2GB_SHIFT                   4
#define TMC2660_S2GB_FIELD                   ((RegisterField) {TMC2660_S2GB_MASK, TMC2660_S2GB_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_S2GA_MASK                    0x00000008
#define TMC2660_S2GA_SHIFT                   3
#define TMC2660_S2GA_FIELD                   ((RegisterField) {TMC2660_S2GA_MASK, TMC2660_S2GA_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_OTPW_MASK                    0x00000004
#define TMC2660_OTPW_SHIFT                   2
#define TMC2660_OTPW_FIELD                   ((RegisterField) {TMC2660_OTPW_MASK, TMC2660_OTPW_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_OT_MASK                      0x00000002
#define TMC2660_OT_SHIFT                     1
#define TMC2660_OT_FIELD                     ((RegisterField) {TMC2660_OT_MASK, TMC2660_OT_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
#define TMC2660_SG_MASK                      0x00000001
#define TMC2660_SG_SHIFT                     0
#define TMC2660_SG_FIELD                     ((RegisterField) {TMC2660_SG_MASK, TMC2660_SG_SHIFT, TMC2660_DRVSTATUS / MSTEP, false})
//#define TMC2660_SG_MASK                      0x000FFC00
//#define TMC2660_SG_SHIFT                     10
//#define TMC2660_SG_FIELD                     ((RegisterField) {TMC2660_SG_MASK, TMC2660_SG_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_STST_MASK                    0x00000080
//#define TMC2660_STST_SHIFT                   7
//#define TMC2660_STST_FIELD                   ((RegisterField) {TMC2660_STST_MASK, TMC2660_STST_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_OLB_MASK                     0x00000040
//#define TMC2660_OLB_SHIFT                    6
//#define TMC2660_OLB_FIELD                    ((RegisterField) {TMC2660_OLB_MASK, TMC2660_OLB_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_OLA_MASK                     0x00000020
//#define TMC2660_OLA_SHIFT                    5
//#define TMC2660_OLA_FIELD                    ((RegisterField) {TMC2660_OLA_MASK, TMC2660_OLA_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_S2GB_MASK                    0x00000010
//#define TMC2660_S2GB_SHIFT                   4
//#define TMC2660_S2GB_FIELD                   ((RegisterField) {TMC2660_S2GB_MASK, TMC2660_S2GB_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_S2GA_MASK                    0x00000008
//#define TMC2660_S2GA_SHIFT                   3
//#define TMC2660_S2GA_FIELD                   ((RegisterField) {TMC2660_S2GA_MASK, TMC2660_S2GA_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_OTPW_MASK                    0x00000004
//#define TMC2660_OTPW_SHIFT                   2
//#define TMC2660_OTPW_FIELD                   ((RegisterField) {TMC2660_OTPW_MASK, TMC2660_OTPW_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_OT_MASK                      0x00000002
//#define TMC2660_OT_SHIFT                     1
//#define TMC2660_OT_FIELD                     ((RegisterField) {TMC2660_OT_MASK, TMC2660_OT_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_SG_MASK                      0x00000001
//#define TMC2660_SG_SHIFT                     0
//#define TMC2660_SG_FIELD                     ((RegisterField) {TMC2660_SG_MASK, TMC2660_SG_SHIFT, TMC2660_DRVSTATUS / SG, false})
//#define TMC2660_SG_MASK                      0x000F8000
//#define TMC2660_SG_SHIFT                     15
//#define TMC2660_SG_FIELD                     ((RegisterField) {TMC2660_SG_MASK, TMC2660_SG_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
#define TMC2660_SE_MASK                      0x00007C00
#define TMC2660_SE_SHIFT                     10
#define TMC2660_SE_FIELD                     ((RegisterField) {TMC2660_SE_MASK, TMC2660_SE_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_STST_MASK                    0x00000080
//#define TMC2660_STST_SHIFT                   7
//#define TMC2660_STST_FIELD                   ((RegisterField) {TMC2660_STST_MASK, TMC2660_STST_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_OLB_MASK                     0x00000040
//#define TMC2660_OLB_SHIFT                    6
//#define TMC2660_OLB_FIELD                    ((RegisterField) {TMC2660_OLB_MASK, TMC2660_OLB_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_OLA_MASK                     0x00000020
//#define TMC2660_OLA_SHIFT                    5
//#define TMC2660_OLA_FIELD                    ((RegisterField) {TMC2660_OLA_MASK, TMC2660_OLA_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_S2GB_MASK                    0x00000010
//#define TMC2660_S2GB_SHIFT                   4
//#define TMC2660_S2GB_FIELD                   ((RegisterField) {TMC2660_S2GB_MASK, TMC2660_S2GB_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_S2GA_MASK                    0x00000008
//#define TMC2660_S2GA_SHIFT                   3
//#define TMC2660_S2GA_FIELD                   ((RegisterField) {TMC2660_S2GA_MASK, TMC2660_S2GA_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_OTPW_MASK                    0x00000004
//#define TMC2660_OTPW_SHIFT                   2
//#define TMC2660_OTPW_FIELD                   ((RegisterField) {TMC2660_OTPW_MASK, TMC2660_OTPW_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_OT_MASK                      0x00000002
//#define TMC2660_OT_SHIFT                     1
//#define TMC2660_OT_FIELD                     ((RegisterField) {TMC2660_OT_MASK, TMC2660_OT_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
//#define TMC2660_SG_MASK                      0x00000001
//#define TMC2660_SG_SHIFT                     0
//#define TMC2660_SG_FIELD                     ((RegisterField) {TMC2660_SG_MASK, TMC2660_SG_SHIFT, TMC2660_DRVSTATUS / SG_SE, false})
#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000C0000
#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  18
#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_INTPOL_MASK                  0x00000200
#define TMC2660_INTPOL_SHIFT                 9
#define TMC2660_INTPOL_FIELD                 ((RegisterField) {TMC2660_INTPOL_MASK, TMC2660_INTPOL_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_DEDGE_MASK                   0x00000100
#define TMC2660_DEDGE_SHIFT                  8
#define TMC2660_DEDGE_FIELD                  ((RegisterField) {TMC2660_DEDGE_MASK, TMC2660_DEDGE_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_MRES_MASK                    0x0000000F
#define TMC2660_MRES_SHIFT                   0
#define TMC2660_MRES_FIELD                   ((RegisterField) {TMC2660_MRES_MASK, TMC2660_MRES_SHIFT, TMC2660_DRVCTRL, false})
//#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000E0000
//#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  17
//#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_PHA_MASK                     0x00020000
#define TMC2660_PHA_SHIFT                    17
#define TMC2660_PHA_FIELD                    ((RegisterField) {TMC2660_PHA_MASK, TMC2660_PHA_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_CA_MASK                      0x0001FE00
#define TMC2660_CA_SHIFT                     9
#define TMC2660_CA_FIELD                     ((RegisterField) {TMC2660_CA_MASK, TMC2660_CA_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_PHB_MASK                     0x00000100
#define TMC2660_PHB_SHIFT                    8
#define TMC2660_PHB_FIELD                    ((RegisterField) {TMC2660_PHB_MASK, TMC2660_PHB_SHIFT, TMC2660_DRVCTRL, false})
#define TMC2660_CB_MASK                      0x000000FF
#define TMC2660_CB_SHIFT                     0
#define TMC2660_CB_FIELD                     ((RegisterField) {TMC2660_CB_MASK, TMC2660_CB_SHIFT, TMC2660_DRVCTRL, false})
//#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000E0000
//#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  17
//#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_TBL_MASK                     0x00018000
#define TMC2660_TBL_SHIFT                    15
#define TMC2660_TBL_FIELD                    ((RegisterField) {TMC2660_TBL_MASK, TMC2660_TBL_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_CHM_MASK                     0x00004000
#define TMC2660_CHM_SHIFT                    14
#define TMC2660_CHM_FIELD                    ((RegisterField) {TMC2660_CHM_MASK, TMC2660_CHM_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_RNDTF_MASK                   0x00002000
#define TMC2660_RNDTF_SHIFT                  13
#define TMC2660_RNDTF_FIELD                  ((RegisterField) {TMC2660_RNDTF_MASK, TMC2660_RNDTF_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_HDEC_MASK                    0x00001800
#define TMC2660_HDEC_SHIFT                   11
#define TMC2660_HDEC_FIELD                   ((RegisterField) {TMC2660_HDEC_MASK, TMC2660_HDEC_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_HEND_MASK                    0x00000780
#define TMC2660_HEND_SHIFT                   7
#define TMC2660_HEND_FIELD                   ((RegisterField) {TMC2660_HEND_MASK, TMC2660_HEND_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_HSTRT_MASK                   0x00000070
#define TMC2660_HSTRT_SHIFT                  4
#define TMC2660_HSTRT_FIELD                  ((RegisterField) {TMC2660_HSTRT_MASK, TMC2660_HSTRT_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_HDEC1_MASK                   0x00001000
#define TMC2660_HDEC1_SHIFT                  12
#define TMC2660_HDEC1_FIELD                  ((RegisterField) {TMC2660_HDEC1_MASK, TMC2660_HDEC1_SHIFT, TMC2660_CHOPCONF, false})
//#define TMC2660_HEND_MASK                    0x00000780
//#define TMC2660_HEND_SHIFT                   7
//#define TMC2660_HEND_FIELD                   ((RegisterField) {TMC2660_HEND_MASK, TMC2660_HEND_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_HDEC0_MASK                   0x00000800
#define TMC2660_HDEC0_SHIFT                  11
#define TMC2660_HDEC0_FIELD                  ((RegisterField) {TMC2660_HDEC0_MASK, TMC2660_HDEC0_SHIFT, TMC2660_CHOPCONF, false})
//#define TMC2660_HSTRT_MASK                   0x00000070
//#define TMC2660_HSTRT_SHIFT                  4
//#define TMC2660_HSTRT_FIELD                  ((RegisterField) {TMC2660_HSTRT_MASK, TMC2660_HSTRT_SHIFT, TMC2660_CHOPCONF, false})
#define TMC2660_TOFF_MASK                    0x0000000F
#define TMC2660_TOFF_SHIFT                   0
#define TMC2660_TOFF_FIELD                   ((RegisterField) {TMC2660_TOFF_MASK, TMC2660_TOFF_SHIFT, TMC2660_CHOPCONF, false})
//#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000E0000
//#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  17
//#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_SMARTEN, false})
#define TMC2660_SEIMIN_MASK                  0x00008000
#define TMC2660_SEIMIN_SHIFT                 15
#define TMC2660_SEIMIN_FIELD                 ((RegisterField) {TMC2660_SEIMIN_MASK, TMC2660_SEIMIN_SHIFT, TMC2660_SMARTEN, false})
#define TMC2660_SEDN_MASK                    0x00006000
#define TMC2660_SEDN_SHIFT                   13
#define TMC2660_SEDN_FIELD                   ((RegisterField) {TMC2660_SEDN_MASK, TMC2660_SEDN_SHIFT, TMC2660_SMARTEN, false})
#define TMC2660_SEUP_MASK                    0x00000060
#define TMC2660_SEUP_SHIFT                   5
#define TMC2660_SEUP_FIELD                   ((RegisterField) {TMC2660_SEUP_MASK, TMC2660_SEUP_SHIFT, TMC2660_SMARTEN, false})
#define TMC2660_SEMAX_MASK                   0x00000F00
#define TMC2660_SEMAX_SHIFT                  8
#define TMC2660_SEMAX_FIELD                  ((RegisterField) {TMC2660_SEMAX_MASK, TMC2660_SEMAX_SHIFT, TMC2660_SMARTEN, false})
#define TMC2660_SEMIN_MASK                   0x0000000F
#define TMC2660_SEMIN_SHIFT                  0
#define TMC2660_SEMIN_FIELD                  ((RegisterField) {TMC2660_SEMIN_MASK, TMC2660_SEMIN_SHIFT, TMC2660_SMARTEN, false})
//#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000E0000
//#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  17
//#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_SGCSCONF, false})
#define TMC2660_SFILT_MASK                   0x00010000
#define TMC2660_SFILT_SHIFT                  16
#define TMC2660_SFILT_FIELD                  ((RegisterField) {TMC2660_SFILT_MASK, TMC2660_SFILT_SHIFT, TMC2660_SGCSCONF, false})
#define TMC2660_SGT_MASK                     0x00007F00
#define TMC2660_SGT_SHIFT                    8
#define TMC2660_SGT_FIELD                    ((RegisterField) {TMC2660_SGT_MASK, TMC2660_SGT_SHIFT, TMC2660_SGCSCONF, false})
#define TMC2660_CS_MASK                      0x0000001F
#define TMC2660_CS_SHIFT                     0
#define TMC2660_CS_FIELD                     ((RegisterField) {TMC2660_CS_MASK, TMC2660_CS_SHIFT, TMC2660_SGCSCONF, false})
//#define TMC2660_REGISTER_ADDRESS_BITS_MASK   0x000E0000
//#define TMC2660_REGISTER_ADDRESS_BITS_SHIFT  17
//#define TMC2660_REGISTER_ADDRESS_BITS_FIELD  ((RegisterField) {TMC2660_REGISTER_ADDRESS_BITS_MASK, TMC2660_REGISTER_ADDRESS_BITS_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_TST_MASK                     0x00010000
#define TMC2660_TST_SHIFT                    16
#define TMC2660_TST_FIELD                    ((RegisterField) {TMC2660_TST_MASK, TMC2660_TST_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_SLPH_MASK                    0x0000C000
#define TMC2660_SLPH_SHIFT                   14
#define TMC2660_SLPH_FIELD                   ((RegisterField) {TMC2660_SLPH_MASK, TMC2660_SLPH_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_SLPL_MASK                    0x00003000
#define TMC2660_SLPL_SHIFT                   12
#define TMC2660_SLPL_FIELD                   ((RegisterField) {TMC2660_SLPL_MASK, TMC2660_SLPL_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_DISS2G_MASK                  0x00000400
#define TMC2660_DISS2G_SHIFT                 10
#define TMC2660_DISS2G_FIELD                 ((RegisterField) {TMC2660_DISS2G_MASK, TMC2660_DISS2G_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_TS2G_MASK                    0x00000300
#define TMC2660_TS2G_SHIFT                   8
#define TMC2660_TS2G_FIELD                   ((RegisterField) {TMC2660_TS2G_MASK, TMC2660_TS2G_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_SDOFF_MASK                   0x00000080
#define TMC2660_SDOFF_SHIFT                  7
#define TMC2660_SDOFF_FIELD                  ((RegisterField) {TMC2660_SDOFF_MASK, TMC2660_SDOFF_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_VSENSE_MASK                  0x00000040
#define TMC2660_VSENSE_SHIFT                 6
#define TMC2660_VSENSE_FIELD                 ((RegisterField) {TMC2660_VSENSE_MASK, TMC2660_VSENSE_SHIFT, TMC2660_DRVCONF, false})
#define TMC2660_RDSEL_MASK                   0x00000030
#define TMC2660_RDSEL_SHIFT                  4
#define TMC2660_RDSEL_FIELD                  ((RegisterField) {TMC2660_RDSEL_MASK, TMC2660_RDSEL_SHIFT, TMC2660_DRVCONF, false})

#endif
