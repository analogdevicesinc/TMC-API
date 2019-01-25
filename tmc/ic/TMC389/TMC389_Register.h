#ifndef TMC389_REGISTER_H
#define TMC389_REGISTER_H

	// addresses out auf address bits from write datagrams
	#define TMC389_DRVCTRL   0
	#define TMC389_CHOPCONF  4
	#define TMC389_SMARTEN   5
	#define TMC389_SGCSCONF  6
	#define TMC389_DRVCONF   7

	// masks for write datagram values to write certain bits only with 0
	#define TMC389_DRVCTRL_SDOFF_MASK  (0xFFFFF)
	#define TMC389_DRVCTRL_MASK        (0xFFFFF & ~((0x0F<<4) | (0x7F <<10)))
	#define TMC389_CHOPCONF_MASK       (0xFFFFF)
	#define TMC389_SMARTEN_MASK        (0xFFFFF & ~((0x01<<4) | (0x01<<7) | (0x01<<12)))
	#define TMC389_SGCSCONF_MASK       (0xFFFFF & ~((0x07<<5) | (0x01<<15)))
	#define TMC389_DRVCONF_MASK        (0xFFFFF & ~((0x0F<<0) | (0x01<<11)))

	// makro function to determine register address out of write datagram
	#define TMC389_GET_ADDRESS(X) ((uint8) ((((X) >> 18) ? ((X)>>17) : 0) & 0x07))

	// Write-Bit
	#define TMC389_WRITE 0x08


	// makro function to shift register data fields to correct position with masking to add them to a write datagram like :
	// write &= ~TMC389_SET_CB(-1);  // clearing CB field of write datagram to DRVCTRL register
	// write |= TMC389_SET_CB(5);    // setting value 5 to CB field of  write datagram to DRVCTRL register

	// for clearing use:

	#define TMC389_SET_CV(X)        (((X) & 0xFF) << 0)
	#define TMC389_SET_PHV(X)       (((X) & 0x01) << 0)
	#define TMC389_SET_CU(X)        (((X) & 0xFF) << 9)
	#define TMC389_SET_PHU(X)       (((X) & 0xFF) << 17)
	#define TMC389_SET_MRES(X)      (((X) & 0x0F) << 0)

	#define TMC389_SET_DEDGE(X)     (((X) & 0x01) << 8)
	#define TMC389_SET_INTERPOL(X)  (((X) & 0x01) << 9)

	// TMC389_CHOPCONF
	#define TMC389_SET_TOFF(X)      (((X) & 0x0F) << 0)
	#define TMC389_SET_HYST(X)      (((X) & 0x3F) << 4)
	#define TMC389_SET_NOSD(X)      (((X) & 0x01) << 10)
	#define TMC389_SET_CDIR(X)      (((X) & 0x01) << 11)
	#define TMC389_SET_CSYNC(X)     (((X) & 0x01) << 12)
	#define TMC389_SET_RNDTF(X)     (((X) & 0x01) << 13)
	#define TMC389_SET_TBL(X)       (((X) & 0x03) << 15)

	// TMC389_SMARTEN
	#define TMC389_SET_SEMIN(X)     (((X) & 0x0F) << 0)
	#define TMC389_SET_SEUP(X)      (((X) & 0x03) << 5)
	#define TMC389_SET_SEMAX(X)     (((X) & 0x0F) << 8)
	#define TMC389_SET_SEDN(X)      (((X) & 0x03) << 13)
	#define TMC389_SET_SEIMIN(X)    (((X) & 0x01) << 15)


	// TMC389_SGCSCONF
	#define TMC389_SET_CS(X)        (((X) & 0x1F) << 0)
	#define TMC389_SET_SGT(X)       (((X) & 0x7F) << 8)
	#define TMC389_SET_SSPD(X)      (((X) & 0x01) << 15)
	#define TMC389_SET_SFILT(X)     (((X) & 0x01) << 16)

	// TMC389_DRVCONF
	#define TMC389_SET_RDSEL(X)     (((X) & 0x03) << 4)
	#define TMC389_SET_VSENSE(X)    (((X) & 0x01) << 6)
	#define TMC389_SET_SDOFF(X)     (((X) & 0x01) << 7)
	#define TMC389_SET_TS2G(X)      (((X) & 0x03) << 8)
	#define TMC389_SET_DISS2G(X)    (((X) & 0x01) << 10)
	#define TMC389_SET_SLPL(X)      (((X) & 0x03) << 12)
	#define TMC389_SET_SLPH(X)      (((X) & 0x03) << 14)
	#define TMC389_SET_TST(X)       (((X) & 0x01) << 16)

	// makro function to shift register data fields to correct position with masking to read out values out of write datagram

	// cb = TMC389_GET_CB(write);     // reading CB field of write datagram to DRVCTRL register

	// TMC389_DRVCTRL
	#define TMC389_GET_CV(X)        (0xFF & ((X) >> 0))
	#define TMC389_GET_PHV(X)       (0x01 & ((X) >> 0))
	#define TMC389_GET_CU(X)        (0xFF & ((X) >> 9))
	#define TMC389_GET_PHU(X)       (0xFF & ((X) >> 17))
	#define TMC389_GET_MRES(X)      (0x0F & ((X) >> 0))

	#define TMC389_GET_DEDGE(X)     (0x01 & ((X) >> 8))
	#define TMC389_GET_INTERPOL(X)  (0x01 & ((X) >> 9))

	// TMC389_CHOPCONF
	#define TMC389_GET_TOFF(X)      (0x0F & ((X) >> 0))
	#define TMC389_GET_HYST(X)      (0x3F & ((X) >> 4))
	#define TMC389_GET_NOSD(X)      (0x01 & ((X) >> 10))
	#define TMC389_GET_CDIR(X)      (0x01 & ((X) >> 11))
	#define TMC389_GET_CSYNC(X)     (0x01 & ((X) >> 12))
	#define TMC389_GET_RNDTF(X)     (0x01 & ((X) >> 13))
	#define TMC389_GET_TBL(X)       (0x03 & ((X) >> 15))

	// TMC389_SMARTEN
	#define TMC389_GET_SEMIN(X)     (0x0F & ((X) >> 0))
	#define TMC389_GET_SEUP(X)      (0x03 & ((X) >> 5))
	#define TMC389_GET_SEMAX(X)     (0x0F & ((X) >> 8))
	#define TMC389_GET_SEDN(X)      (0x03 & ((X) >> 13))
	#define TMC389_GET_SEIMIN(X)    (0x01 & ((X) >> 15))

	// TMC389_SGCSCONF
	#define TMC389_GET_CS(X)        (0x1F & ((X) >> 0))
	#define TMC389_GET_SGT(X)       (0x7F & ((X) >> 8))
	#define TMC389_GET_SSPD(X)      (0x01 & ((X) >> 15))
	#define TMC389_GET_SFILT(X)     (0x01 & ((X) >> 16))

	// TMC389_DRVCONF
	#define TMC389_GET_RDSEL(X)     (0x03 & ((X) >> 4))
	#define TMC389_GET_VSENSE(X)    (0x01 & ((X) >> 6))
	#define TMC389_GET_SDOFF(X)     (0x01 & ((X) >> 7))
	#define TMC389_GET_TS2G(X)      (0x03 & ((X) >> 8))
	#define TMC389_GET_DISS2G(X)    (0x01 & ((X) >> 10))
	#define TMC389_GET_SLPL(X)      (0x03 & ((X) >> 12))
	#define TMC389_GET_SLPH(X)      (0x03 & ((X) >> 14))
	#define TMC389_GET_TST(X)       (0x01 & ((X) >> 16))

	// read addressescorrespondes with RDSEL, added latest to access latest data of common lower 7 bits
	#define TMC389_RESPONSE0        0
	#define TMC389_RESPONSE1        1
	#define TMC389_RESPONSE2        2
	#define TMC389_RESPONSE_LATEST  3

	// makro function to shift register data fields to correct position with masking to read out values out of read datagram

	// TMC389_RESPONSE0
	#define TMC389_GET_MSTEP(X)  (0x3FF & ((X) >> 10))

	// TMC389_RESPONSE1
	#define TMC389_GET_SG(X)     (0x3FF & ((X) >> 10))

	// TMC389_RESPONSE2
	#define TMC389_GET_SGU(X)    (0x1F & ((X) >> 15))
	#define TMC389_GET_SE(X)     (0x1F & ((X) >> 10))

	// TMC389_RESPONSE_LATEST
	#define TMC389_GET_STST(X)   (0x01 & ((X) >> 7))
	#define TMC389_GET_OL(X)     (0x01 & ((X) >> 5))
	#define TMC389_GET_S2G(X)    (0x01 & ((X) >> 3))
	#define TMC389_GET_OTPW(X)   (0x01 & ((X) >> 2))
	#define TMC389_GET_OT(X)     (0x01 & ((X) >> 1))
	#define TMC389_GET_SG(X)     (0x01 & ((X) >> 0))

#endif /* TMC389_REGISTER_H */
