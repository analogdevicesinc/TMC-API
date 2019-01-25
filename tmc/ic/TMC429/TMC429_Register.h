#ifndef TMC429_REGISTER_H
#define TMC429_REGISTER_H

	// TMC429 Motor numbers to be combined with the addresses of the motor register set
	// (e.g. TMC429_IDX_XTARGET|TMC429_MOTOR1).
	#define TMC429_MOTOR0        0
	#define TMC429_MOTOR1        0x20
	#define TMC429_MOTOR2        0x40
	#define TMC429_MOTOR(motor)  (motor<<5)

	// TMC429 Motor Register Set
	#define TMC429_IDX_XTARGET(motor)           (0x00|TMC429_MOTOR(motor))
	#define TMC429_IDX_XACTUAL(motor)           (0x02|TMC429_MOTOR(motor))
	#define TMC429_IDX_VMIN(motor)              (0x04|TMC429_MOTOR(motor))
	#define TMC429_IDX_VMAX(motor)              (0x06|TMC429_MOTOR(motor))
	#define TMC429_IDX_VTARGET(motor)           (0x08|TMC429_MOTOR(motor))
	#define TMC429_IDX_VACTUAL(motor)           (0x0A|TMC429_MOTOR(motor))
	#define TMC429_IDX_AMAX(motor)              (0x0C|TMC429_MOTOR(motor))
	#define TMC429_IDX_AACTUAL(motor)           (0x0E|TMC429_MOTOR(motor))
	#define TMC429_IDX_AGTAT_ALEAT(motor)       (0x10|TMC429_MOTOR(motor))
	#define TMC429_IDX_PMUL_PDIV(motor)         (0x12|TMC429_MOTOR(motor))
	#define TMC429_IDX_REFCONF_RM(motor)        (0x14|TMC429_MOTOR(motor))
	#define TMC429_IDX_IMASK_IFLAGS(motor)      (0x16|TMC429_MOTOR(motor))
	#define TMC429_IDX_PULSEDIV_RAMPDIV(motor)  (0x18|TMC429_MOTOR(motor))
	#define TMC429_IDX_DX_REFTOLERANCE(motor)   (0x1A|TMC429_MOTOR(motor))
	#define TMC429_IDX_XLATCHED(motor)          (0x1C|TMC429_MOTOR(motor))
	#define TMC429_IDX_USTEP_COUNT_429(motor)   (0x1E|TMC429_MOTOR(motor))

	// Other TMC429 registers (these exist only once)
	#define TMC429_IDX_LOW_WORD          0x60
	#define TMC429_IDX_HIGH_WORD         0x62
	#define TMC429_IDX_COVER_POS_LEN     0x64
	#define TMC429_IDX_COVER_DATA        0x66

	#define TMC429_IDX_IF_CONFIG_429     0x68
	#define TMC429_IDX_POS_COMP_429      0x6A
	#define TMC429_IDX_POS_COMP_INT_429  0x6C
	#define TMC429_IDX_TYPE_VERSION_429  0x72

	#define TMC429_IDX_REF_SWITCHES      0x7C
	#define TMC429_IDX_SMGP              0x7E

	// TMC429 read bit: combine this with any register address for reading from that
	// register (otherwise it will be a write).
	// e.g. TMC429_IDX_XACTUAL|TMC429_MOTOR0|TMC429_READ
	#define TMC429_READ 0x01

	// TMC429 ramp modes
	#define TMC429_RM_RAMP      0
	#define TMC429_RM_SOFT      1
	#define TMC429_RM_VELOCITY  2
	#define TMC429_RM_HOLD      3

	// TMC429 stop switch modes
	#define TMC429_NO_REF    0x03
	#define TMC429_SOFT_REF  0x04

	#define TMC429_NO_LIMIT    0
	#define TMC429_HARD_LIMIT  1
	#define TMC429_SOFT_LIMIT  2

	// TMC429 stop switch flags
	#define TMC429_REFSW_LEFT   0x02
	#define TMC429_REFSW_RIGHT  0x01

	// Flags of the TMC429 status byte
	#define TMC429_M0_POS_REACHED  0x01
	#define TMC429_M1_POS_REACHED  0x04
	#define TMC429_M2_POS_REACHED  0x10
	#define TMC429_STATUS_CDGW     0x40
	#define TMC429_STATUS_INT      0x80

	// TMC429 interrupt flags
	#define TMC429_IFLAG_POS_REACHED      0x01
	#define TMC429_IFLAG_REF_WRONG        0x02
	#define TMC429_IFLAG_REF_MISS         0x04
	#define TMC429_IFLAG_STOP             0x08
	#define TMC429_IFLAG_STOP_LEFT_LOW    0x10
	#define TMC429_IFLAG_STOP_RIGHT_LOW   0x20
	#define TMC429_IFLAG_STOP_LEFT_HIGH   0x40
	#define TMC429_IFLAG_STOP_RIGHT_HIGH  0x80

	// TMC429 interface configuration bits
	#define TMC429_IFCONF_INV_REF       0x0001
	#define TMC429_IFCONF_SDO_INT       0x0002
	#define TMC429_IFCONF_STEP_HALF     0x0004
	#define TMC429_IFCONF_INV_STEP      0x0008
	#define TMC429_IFCONF_INV_DIR       0x0010
	#define TMC429_IFCONF_EN_SD         0x0020
	#define TMC429_IFCONF_POS_COMP_0    0x0000
	#define TMC429_IFCONF_POS_COMP_1    0x0040
	#define TMC429_IFCONF_POS_COMP_2    0x0080
	#define TMC429_IFCONF_POS_COMP_OFF  0x00C0
	#define TMC429_IFCONF_EN_REFR       0x0100

#endif /* TMC429_REGISTER_H */
