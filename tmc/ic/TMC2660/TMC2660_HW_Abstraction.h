/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

#ifndef TMC2660_HW_ABSTRACTION
#define TMC2660_HW_ABSTRACTION

//Constants

#define TMC2660_REGISTER_COUNT   16 // Actual Count is 8, but due to mapping, we write 16
#define TMC2660_MOTORS           1
#define TMC2660_WRITE_BIT        0x08
#define TMC2660_ADDRESS_MASK     0x07
#define TMC2660_ADDRESS_SHIFT    20
#define TMC2660_STATUS_MASK      0xFF
#define TMC2660_VALUE_MASK       0xFFFFF
#define TMC2660_VALUE_SHIFT      0
#define TMC2660_MAX_VELOCITY     (int32_t)  2147483647
#define TMC2660_MAX_ACCELERATION (uint32_t)  16777215uL

#define TMC2660_IS_WRITEONLY_REGISTER(addr) ((addr & TMC2660_WRITE_BIT) == 1)
#define TMC2660_IS_READONLY_REGISTER(addr) ((addr & TMC2660_WRITE_BIT) == 0)

#define TMC2660_IS_WRITE(datagram) ((datagram) >> (TMC2660_ADDRESS_SHIFT + 3))
#define TMC2660_ADDRESS(datagram) (((datagram) >> TMC2660_ADDRESS_SHIFT) & TMC2660_ADDRESS_MASK)
#define TMC2660_VALUE(datagram) ((datagram) & TMC2660_VALUE_MASK)

// Helper macro to determine register address out of write datagram
#define TMC2660_GET_ADDRESS(datagram)  ((uint8_t) ((((datagram) >> 18) ? ((datagram)>>17) : 0) & 0x07))

// Helper macro to construct the datagram out of the address and the value
#define TMC2660_DATAGRAM(addr, value)  (((addr) << 17) | (value))

//registers definitions

// addresses out auf address bits from write datagrams
#define TMC2660_RESPONSE0       0x00
#define TMC2660_RESPONSE1       0x01
#define TMC2660_RESPONSE2       0x02
#define TMC2660_RESPONSE_LATEST 0x03

// Addresses of the write-only registers
// Note: This software abstraction maps the registers to addresses 8 and up
#define TMC2660_WRITE_ONLY_REGISTER 0x08
#define TMC2660_DRVCTRL   (0x00 | TMC2660_WRITE_ONLY_REGISTER) // 8
#define TMC2660_CHOPCONF  (0x04 | TMC2660_WRITE_ONLY_REGISTER) // C
#define TMC2660_SMARTEN   (0x05 | TMC2660_WRITE_ONLY_REGISTER) // D
#define TMC2660_SGCSCONF  (0x06 | TMC2660_WRITE_ONLY_REGISTER) // E
#define TMC2660_DRVCONF   (0x07 | TMC2660_WRITE_ONLY_REGISTER) // F


//fields definitions

#define TMC2660_MSTEP_MASK                   0x000FFC00
#define TMC2660_MSTEP_SHIFT                  10
#define TMC2660_MSTEP_FIELD                  ((RegisterField) {TMC2660_MSTEP_MASK, TMC2660_MSTEP_SHIFT, TMC2660_RESPONSE0, false})
#define TMC2660_SE_MASK                      0x00007C00
#define TMC2660_SE_SHIFT                     10
#define TMC2660_SE_FIELD                     ((RegisterField) {TMC2660_SE_MASK, TMC2660_SE_SHIFT, TMC2660_RESPONSE2, false})
#define TMC2660_SGU_MASK                     0x0F8000
#define TMC2660_SGU_SHIFT                    15
#define TMC2660_SGU_FIELD                    ((RegisterField) {TMC2660_SGU_MASK, TMC2660_SGU_SHIFT, TMC2660_RESPONSE2, false})
#define TMC2660_SG2_MASK                     0x0FFC00
#define TMC2660_SG2_SHIFT                    10
#define TMC2660_SG2_FIELD                    ((RegisterField) {TMC2660_SG2_MASK, TMC2660_SG2_SHIFT, TMC2660_RESPONSE1, false})
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
#define TMC2660_HDEC0_MASK                   0x00000800
#define TMC2660_HDEC0_SHIFT                  11
#define TMC2660_HDEC0_FIELD                  ((RegisterField) {TMC2660_HDEC0_MASK, TMC2660_HDEC0_SHIFT, TMC2660_CHOPCONF, false})
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

// makro function to shift register data fields to correct position with masking to add them to a write datagram like :
// write &= ~TMC2660_SET_CB(-1); // clearing CB field of write datagram to DRVCTRL register
// write |= TMC2660_SET_CB(5); // setting value 5 to CB field of  write datagram to DRVCTRL register

// for clearing use:

#define TMC2660_SET_CB(X)        (((X) & 0xFF) << 0)
#define TMC2660_SET_PHB(X)       (((X) & 0x01) << 0)
#define TMC2660_SET_CA(X)        (((X) & 0xFF) << 9)
#define TMC2660_SET_PHA(X)       (((X) & 0xFF) << 17)
#define TMC2660_SET_MRES(X)      (((X) & 0x0F) << 0)

#define TMC2660_SET_DEDGE(X)     (((X) & 0x01) << 8)
#define TMC2660_SET_INTERPOL(X)  (((X) & 0x01) << 9)

// TMC2660_CHOPCONF
#define TMC2660_SET_TOFF(X)      (((X) & 0x0F) << 0)
#define TMC2660_SET_HSTRT(X)     (((X) & 0x07) << 4)
#define TMC2660_SET_HEND(X)      (((X) & 0x0F) << 7)
#define TMC2660_SET_HDEC(X)      (((X) & 0x03) << 11)
#define TMC2660_SET_RNDTF(X)     (((X) & 0x01) << 13)
#define TMC2660_SET_CHM(X)       (((X) & 0x01) << 14)
#define TMC2660_SET_TBL(X)       (((X) & 0x03) << 15)

// TMC2660_SMARTEN
#define TMC2660_SET_SEMIN(X)     (((X) & 0x0F) << 0)
#define TMC2660_SET_SEUP(X)      (((X) & 0x03) << 5)
#define TMC2660_SET_SEMAX(X)     (((X) & 0x0F) << 8)
#define TMC2660_SET_SEDN(X)      (((X) & 0x03) << 13)
#define TMC2660_SET_SEIMIN(X)    (((X) & 0x01) << 15)


// TMC2660_SGCSCONF
#define TMC2660_SET_CS(X)        (((X) & 0x1F) << 0)
#define TMC2660_SET_SGT(X)       (((X) & 0x7F) << 8)
#define TMC2660_SET_SFILT(X)     (((X) & 0x01) << 16)

// TMC2660_DRVCONF
#define TMC2660_SET_RDSEL(X)     (((X) & 0x03) << 4)
#define TMC2660_SET_VSENSE(X)    (((X) & 0x01) << 6)
#define TMC2660_SET_SDOFF(X)     (((X) & 0x01) << 7)
#define TMC2660_SET_TS2G(X)      (((X) & 0x03) << 8)
#define TMC2660_SET_DISS2G(X)    (((X) & 0x01) << 10)
#define TMC2660_SET_SLPL(X)      (((X) & 0x03) << 12)
#define TMC2660_SET_SLPH(X)      (((X) & 0x03) << 14)
#define TMC2660_SET_TST(X)       (((X) & 0x01) << 16)

// makro function to shift register data fields to correct position with masking to read out values out of write datagram

// cb = TMC2660_GET_CB(write); // reading CB field of write datagram to DRVCTRL register

// TMC2660_DRVCTRL
#define TMC2660_GET_CB(X)        (0xFF & ((X) >> 0))
#define TMC2660_GET_PHB(X)       (0x01 & ((X) >> 0))
#define TMC2660_GET_CA(X)        (0xFF & ((X) >> 9))
#define TMC2660_GET_PHA(X)       (0xFF & ((X) >> 17))
#define TMC2660_GET_MRES(X)      (0x0F & ((X) >> 0))

#define TMC2660_GET_DEDGE(X)     (0x01 & ((X) >> 8))
#define TMC2660_GET_INTERPOL(X)  (0x01 & ((X) >> 9))

// TMC2660_CHOPCONF
#define TMC2660_GET_TOFF(X)      (0x0F & ((X) >> 0))
#define TMC2660_GET_HSTRT(X)     (0x07 & ((X) >> 4))
#define TMC2660_GET_HEND(X)      (0x0F & ((X) >> 7))
#define TMC2660_GET_HDEC(X)      (0x03 & ((X) >> 11))
#define TMC2660_GET_RNDTF(X)     (0x01 & ((X) >> 13))
#define TMC2660_GET_CHM(X)       (0x01 & ((X) >> 14))
#define TMC2660_GET_TBL(X)       (0x03 & ((X) >> 15))

// TMC2660_SMARTEN
#define TMC2660_GET_SEMIN(X)     (0x0F & ((X) >> 0))
#define TMC2660_GET_SEUP(X)      (0x03 & ((X) >> 5))
#define TMC2660_GET_SEMAX(X)     (0x0F & ((X) >> 8))
#define TMC2660_GET_SEDN(X)      (0x03 & ((X) >> 13))
#define TMC2660_GET_SEIMIN(X)    (0x01 & ((X) >> 15))

// TMC2660_SGCSCONF
#define TMC2660_GET_CS(X)        (0x1F & ((X) >> 0))
#define TMC2660_GET_SGT(X)       (0x7F & ((X) >> 8))
#define TMC2660_GET_SFILT(X)     (0x01 & ((X) >> 16))

// TMC2660_DRVCONF
#define TMC2660_GET_RDSEL(X)     (0x03 & ((X) >> 4))
#define TMC2660_GET_VSENSE(X)    (0x01 & ((X) >> 6))
#define TMC2660_GET_SDOFF(X)     (0x01 & ((X) >> 7))
#define TMC2660_GET_TS2G(X)      (0x03 & ((X) >> 8))
#define TMC2660_GET_DISS2G(X)    (0x01 & ((X) >> 10))
#define TMC2660_GET_SLPL(X)      (0x03 & ((X) >> 12))
#define TMC2660_GET_SLPH(X)      (0x03 & ((X) >> 14))
#define TMC2660_GET_TST(X)       (0x01 & ((X) >> 16))

// makro function to shift register data fields to correct position with masking to read out values out of read datagram

// TMC2660_RESPONSE0
#define TMC2660_GET_MSTEP(X)  (0x3FF & ((X) >> 10))

// TMC2660_RESPONSE1
#define TMC2660_GET_SG(X)     (0x3FF & ((X) >> 10))

// TMC2660_RESPONSE2
#define TMC2660_GET_SGU(X)    (0x1F & ((X) >> 15))
#define TMC2660_GET_SE(X)     (0x1F & ((X) >> 10))

// General status bits (contained in all TMC2660_RESPONSE0, 1 and 2)
#define TMC2660_GET_STST(X)   (0x01 & ((X) >> 7))
#define TMC2660_GET_OLB(X)    (0x01 & ((X) >> 6))
#define TMC2660_GET_OLA(X)    (0x01 & ((X) >> 5))
#define TMC2660_GET_S2GB(X)   (0x01 & ((X) >> 4))
#define TMC2660_GET_S2GA(X)   (0x01 & ((X) >> 3))
#define TMC2660_GET_OTPW(X)   (0x01 & ((X) >> 2))
#define TMC2660_GET_OT(X)     (0x01 & ((X) >> 1))
#define TMC2660_GET_SGF(X)    (0x01 & ((X) >> 0))
#endif
