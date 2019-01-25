#ifndef TMC457_REGISTER_H
#define TMC457_REGISTER_H

	// TMC475 Register Set
	#define TMC457_MODE                 0x00
	#define TMC457_XACTUAL              0x01
	#define TMC457_VACTUAL              0x02
	#define TMC457_VMAX                 0x03
	#define TMC457_VTARGET              0x04
	#define TMC457_AMAX                 0x05
	#define TMC457_DMAX                 0x06
	#define TMC457_DSTOP                0x07
	#define TMC457_BOWMAX               0x08
	#define TMC457_XTARGET              0x09
	#define TMC457_XCOMPARE             0x0A
	#define TMC457_STATUS               0x0B
	#define TMC457_AACTUAL              0x0C
	#define TMC457_SDSCALE              0x0D
	#define TMC457_AMAX_DMAX            0x0F

	#define TMC457_ENC_CONST            0x10
	#define TMC457_ENC_X                0x11
	#define TMC457_ENC_CLRMODE          0x12
	#define TMC457_ENC_STATUS           0x13
	#define TMC457_ENC_LATCH            0x14
	#define TMC457_XLATCH               0x15
	#define TMC457_ENC_WARNDIST         0x16

	#define TMC457_VENC_US_CONST        0x17
	#define TMC457_VENC_US_POS          0x18
	#define TMC457_VENC_US_SEL          0x19

	#define TMC457_PID_P                0x20
	#define TMC457_PID_I                0x21
	#define TMC457_PID_D                0x22
	#define TMC457_PID_ICLIP            0x23
	#define TMC457_PID_ISUM             0x24
	#define TMC457_PID_DCLKDIV          0x25
	#define TMC457_PID_DV_CPU           0x26
	#define TMC457_PID_DV_CLIP          0x27
	#define TMC457_PID_E                0x28
	#define TMC457_PID_VACTUAL          0x29
	#define TMC457_PID_TOLERANCE        0x2A

	#define TMC457_PULSE_MAX            0x30
	#define TMC457_PULSE_XSTEP_DIV      0x31
	#define TMC457_STEP_DIR_MODE        0x32
	#define TMC457_MICROSTEP_POS        0x33
	#define TMC457_STDBY_DELAY          0x34
	#define TMC457_PULSE_LENGTH         0x35

	#define TMC457_SWITCH_MODE          0x40
	#define TMC457_SWITCH_STATUS        0x41
	#define TMC457_POSLIM_LEFT          0x42
	#define TMC457_POSLIM_RIGHT         0x43

	#define TMC457_SEQ_MODE             0x54
	#define TMC457_SEQ_DAC_SCALE        0x55
	#define TMC457_SEQ_STALL_THRESHOLD  0x56
	#define TMC457_SEQ_DRIVER_STATUS    0x57
	#define TMC457_CHOP_CLK_DIV         0x59

	#define TMC457_VERSION              0x60
	#define TMC457_INT_MASK             0x61
	#define TMC457_INT_FLAGS            0x62
	#define TMC457_WAVETAB              0x7F

	// Write Bit (to be combined with any register address for write access)
	#define TMC457_WRITE 0x80

	// TMC457 modes (for TMC457_MODE register)
	#define TMC457_RM_POSITION  0x00000000
	#define TMC457_RM_RESERVED  0x00000001
	#define TMC457_RM_VELOCITY  0x00000002
	#define TMC457_RM_HOLD      0x00000003
	#define TMC457_RM_SHAFT     0x00000010  // to be combined with the other modes
	#define TMC457_RM_PID       0x00000100  // to be combined with the other modes
	#define TMC457_RM_PID_BASE  0x00000200  // to be combined with the other modes

	// Status bits (TMC457_STATUS register)
	#define TMC457_ST_X_REACHED  0x00000001
	#define TMC457_ST_V_REACHED  0x00000002
	#define TMC457_ST_V_ZERO     0x00000004
	#define TMC457_ST_ENC_WARN   0x00000010

	// Interrupt bits (TMC457_INT_MASK and TMC457_INT_FLAGS registers)
	#define TMC457_IRQ_TARGET     0x00000001
	#define TMC457_IRQ_DEVIATION  0x00000002
	#define TMC457_IRQ_ENCN       0x00000004
	#define TMC457_IRQ_STOP       0x00000008
	#define TMC457_IRQ_DRVSTATUS  0x00000010
	#define TMC457_IRQ_REFL       0x00000020
	#define TMC457_IRQ_REFR       0x00000040
	#define TMC457_IRQ_XCOMP      0x00000080

	// Driver status bits (TMC457_SEQ_DRIVER_STATUS register)
	#define TMC457_DRV_ERROR  0x00000001
	#define TMC457_DRV_OTPW   0x00000002
	#define TMC457_DRV_STALL  0x00000004

#endif /* TMC457_REGISTER_H */
