/*
 * TMC2590_Macros.h
 *
 *  Created on: 09.01.2019
 *      Author: LK
 */

#ifndef TMC_IC_TMC2590_TMC2590_MACROS_H_
#define TMC_IC_TMC2590_TMC2590_MACROS_H_

#include "TMC2590_Constants.h"

#define TMC2590_VALUE(x) ((x) & 0x000FFFFF)

// makro function to determine register address out of write datagram
#define TMC2590_GET_ADDRESS(X) ((uint8_t) ((((X) >> (TMC2590_ADDRESS_SHIFT + 1)) ? ((X) >> TMC2590_ADDRESS_SHIFT) : 0) & TMC2590_ADDRESS_MASK))

// makro function to shift register data fields to correct position with masking to add them to a write datagram like :
// write &= ~TMC2590_SET_CB(-1); // clearing CB field of write datagram to DRVCTRL register
// write |= TMC2590_SET_CB(5); // setting value 5 to CB field of  write datagram to DRVCTRL register

// for clearing use:

#define TMC2590_SET_CB(X)        (((X) & 0xFF) << 0)
#define TMC2590_SET_PHB(X)       (((X) & 0x01) << 0)
#define TMC2590_SET_CA(X)        (((X) & 0xFF) << 9)
#define TMC2590_SET_PHA(X)       (((X) & 0xFF) << 17)
#define TMC2590_SET_MRES(X)      (((X) & 0x0F) << 0)

#define TMC2590_SET_DEDGE(X)     (((X) & 0x01) << 8)
#define TMC2590_SET_INTERPOL(X)  (((X) & 0x01) << 9)

// TMC2590_CHOPCONF
#define TMC2590_SET_TOFF(X)      (((X) & 0x0F) << 0)
#define TMC2590_SET_HSTRT(X)     (((X) & 0x07) << 4)
#define TMC2590_SET_HEND(X)      (((X) & 0x0F) << 7)
#define TMC2590_SET_HDEC(X)      (((X) & 0x03) << 11)
#define TMC2590_SET_RNDTF(X)     (((X) & 0x01) << 13)
#define TMC2590_SET_CHM(X)       (((X) & 0x01) << 14)
#define TMC2590_SET_TBL(X)       (((X) & 0x03) << 15)

// TMC2590_SMARTEN
#define TMC2590_SET_SEMIN(X)     (((X) & 0x0F) << 0)
#define TMC2590_SET_SEUP(X)      (((X) & 0x03) << 5)
#define TMC2590_SET_SEMAX(X)     (((X) & 0x0F) << 8)
#define TMC2590_SET_SEDN(X)      (((X) & 0x03) << 13)
#define TMC2590_SET_SEIMIN(X)    (((X) & 0x01) << 15)


// TMC2590_SGCSCONF
#define TMC2590_SET_CS(X)        (((X) & 0x1F) << 0)
#define TMC2590_SET_SGT(X)       (((X) & 0x7F) << 8)
#define TMC2590_SET_SFILT(X)     (((X) & 0x01) << 16)

// TMC2590_DRVCONF
#define TMC2590_SET_RDSEL(X)     (((X) & 0x03) << 4)
#define TMC2590_SET_VSENSE(X)    (((X) & 0x01) << 6)
#define TMC2590_SET_SDOFF(X)     (((X) & 0x01) << 7)
#define TMC2590_SET_TS2G(X)      (((X) & 0x03) << 8)
#define TMC2590_SET_DISS2G(X)    (((X) & 0x01) << 10)
#define TMC2590_SET_SLPL(X)      (((X) & 0x03) << 12)
#define TMC2590_SET_SLPH(X)      (((X) & 0x03) << 14)
#define TMC2590_SET_TST(X)       (((X) & 0x01) << 16)

// makro function to shift register data fields to correct position with masking to read out values out of write datagram

// cb = TMC2590_GET_CB(write); // reading CB field of write datagram to DRVCTRL register

// TMC2590_DRVCTRL
#define TMC2590_GET_CB(X)        (0xFF & ((X) >> 0))
#define TMC2590_GET_PHB(X)       (0x01 & ((X) >> 0))
#define TMC2590_GET_CA(X)        (0xFF & ((X) >> 9))
#define TMC2590_GET_PHA(X)       (0xFF & ((X) >> 17))
#define TMC2590_GET_MRES(X)      (0x0F & ((X) >> 0))

#define TMC2590_GET_DEDGE(X)     (0x01 & ((X) >> 8))
#define TMC2590_GET_INTERPOL(X)  (0x01 & ((X) >> 9))

// TMC2590_CHOPCONF
#define TMC2590_GET_TOFF(X)      (0x0F & ((X) >> 0))
#define TMC2590_GET_HSTRT(X)     (0x07 & ((X) >> 4))
#define TMC2590_GET_HEND(X)      (0x0F & ((X) >> 7))
#define TMC2590_GET_HDEC(X)      (0x03 & ((X) >> 11))
#define TMC2590_GET_RNDTF(X)     (0x01 & ((X) >> 13))
#define TMC2590_GET_CHM(X)       (0x01 & ((X) >> 14))
#define TMC2590_GET_TBL(X)       (0x03 & ((X) >> 15))

// TMC2590_SMARTEN
#define TMC2590_GET_SEMIN(X)     (0x0F & ((X) >> 0))
#define TMC2590_GET_SEUP(X)      (0x03 & ((X) >> 5))
#define TMC2590_GET_SEMAX(X)     (0x0F & ((X) >> 8))
#define TMC2590_GET_SEDN(X)      (0x03 & ((X) >> 13))
#define TMC2590_GET_SEIMIN(X)    (0x01 & ((X) >> 15))

// TMC2590_SGCSCONF
#define TMC2590_GET_CS(X)        (0x1F & ((X) >> 0))
#define TMC2590_GET_SGT(X)       (0x7F & ((X) >> 8))
#define TMC2590_GET_SFILT(X)     (0x01 & ((X) >> 16))

// TMC2590_DRVCONF
#define TMC2590_GET_RDSEL(X)     (0x03 & ((X) >> 4))
#define TMC2590_GET_VSENSE(X)    (0x01 & ((X) >> 6))
#define TMC2590_GET_SDOFF(X)     (0x01 & ((X) >> 7))
#define TMC2590_GET_TS2G(X)      (0x03 & ((X) >> 8))
#define TMC2590_GET_DISS2G(X)    (0x01 & ((X) >> 10))
#define TMC2590_GET_SLPL(X)      (0x03 & ((X) >> 12))
#define TMC2590_GET_SLPH(X)      (0x03 & ((X) >> 14))
#define TMC2590_GET_TST(X)       (0x01 & ((X) >> 16))

// makro function to shift register data fields to correct position with masking to read out values out of read datagram

// TMC2590_RESPONSE0
#define TMC2590_GET_MSTEP(X)  (0x3FF & ((X) >> 10))

// TMC2590_RESPONSE1
#define TMC2590_GET_SG(X)     (0x3FF & ((X) >> 10))

// TMC2590_RESPONSE2
#define TMC2590_GET_SGU(X)    (0x1F & ((X) >> 15))
#define TMC2590_GET_SE(X)     (0x1F & ((X) >> 10))

// TMC2590_RESPONSE_LATEST
#define TMC2590_GET_STST(X)   (0x01 & ((X) >> 7))
#define TMC2590_GET_OLB(X)    (0x01 & ((X) >> 6))
#define TMC2590_GET_OLA(X)    (0x01 & ((X) >> 5))
#define TMC2590_GET_S2GB(X)   (0x01 & ((X) >> 4))
#define TMC2590_GET_S2GA(X)   (0x01 & ((X) >> 3))
#define TMC2590_GET_OTPW(X)   (0x01 & ((X) >> 2))
#define TMC2590_GET_OT(X)     (0x01 & ((X) >> 1))
#define TMC2590_GET_SGF(X)    (0x01 & ((X) >> 0))

#endif /* TMC_IC_TMC2590_TMC2590_MACROS_H_ */
