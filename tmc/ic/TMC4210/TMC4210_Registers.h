#ifndef TMC4210_REGISTERS_H
#define TMC4210_REGISTERS_H

// TMC4210 Motor Register Set
#define TMC4210_IDX_XTARGET            0x00
#define TMC4210_IDX_XACTUAL            0x02
#define TMC4210_IDX_VMIN               0x04
#define TMC4210_IDX_VMAX               0x06
#define TMC4210_IDX_VTARGET            0x08
#define TMC4210_IDX_VACTUAL            0x0A
#define TMC4210_IDX_AMAX               0x0C
#define TMC4210_IDX_AACTUAL            0x0E
#define TMC4210_IDX_AGTAT_ALEAT        0x10
#define TMC4210_IDX_PMUL_PDIV          0x12
#define TMC4210_IDX_REFCONF_RM         0x14
#define TMC4210_IDX_IMASK_IFLAGS       0x16
#define TMC4210_IDX_PULSEDIV_RAMPDIV   0x18
#define TMC4210_IDX_DX_REFTOLERANCE    0x1A
#define TMC4210_IDX_XLATCHED           0x1C
#define TMC4210_IDX_USTEP_COUNT_4210   0x1E

// Other TMC4210 registers
#define TMC4210_IDX_LOW_WORD           0x60
#define TMC4210_IDX_HIGH_WORD          0x62
#define TMC4210_IDX_COVER_POS_LEN      0x64
#define TMC4210_IDX_COVER_DATA         0x66

#define TMC4210_IDX_IF_CONFIG_4210     0x68
#define TMC4210_IDX_POS_COMP_4210      0x6A
#define TMC4210_IDX_POS_COMP_INT_4210  0x6C
#define TMC4210_IDX_TYPE_VERSION_4210  0x72

#define TMC4210_IDX_REF_SWITCHES       0x7C
#define TMC4210_IDX_SMGP               0x7E

// TMC4210 read bit: combine this with any register address for reading from that
// register (otherwise it will be a write).
// e.g. TMC4210_IDX_XACTUAL|TMC429_READ
#define TMC4210_READ 0x01

// TMC4210 ramp modes
#define TMC4210_RM_RAMP      0
#define TMC4210_RM_SOFT      1
#define TMC4210_RM_VELOCITY  2
#define TMC4210_RM_HOLD      3

// TMC4210 stop switch modes
#define TMC4210_NO_REF    0x03
#define TMC4210_SOFT_REF  0x04

#define TMC4210_NO_LIMIT    0
#define TMC4210_HARD_LIMIT  1
#define TMC4210_SOFT_LIMIT  2

// TMC4210 stop switch flags
#define TMC4210_REFSW_LEFT   0x02
#define TMC4210_REFSW_RIGHT  0x01

// Flags of the TMC4210 status byte
#define TMC4210_POS_REACHED  0x01
#define TMC4210_STATUS_CDGW  0x40
#define TMC4210_STATUS_INT   0x80

// TMC4210 interrupt flags
#define TMC4210_IFLAG_POS_REACHED      0x01
#define TMC4210_IFLAG_REF_WRONG        0x02
#define TMC4210_IFLAG_REF_MISS         0x04
#define TMC4210_IFLAG_STOP             0x08
#define TMC4210_IFLAG_STOP_LEFT_LOW    0x10
#define TMC4210_IFLAG_STOP_RIGHT_LOW   0x20
#define TMC4210_IFLAG_STOP_LEFT_HIGH   0x40
#define TMC4210_IFLAG_STOP_RIGHT_HIGH  0x80

// TMC4210 interface configuration bits
#define TMC4210_IFCONF_INV_REF       0x0001
#define TMC4210_IFCONF_SDO_INT       0x0002
#define TMC4210_IFCONF_STEP_HALF     0x0004
#define TMC4210_IFCONF_INV_STEP      0x0008
#define TMC4210_IFCONF_INV_DIR       0x0010
#define TMC4210_IFCONF_EN_SD         0x0020
#define TMC4210_IFCONF_POS_COMP_0    0x0000
#define TMC4210_IFCONF_POS_COMP_1    0x0040
#define TMC4210_IFCONF_POS_COMP_2    0x0080
#define TMC4210_IFCONF_POS_COMP_OFF  0x00C0
#define TMC4210_IFCONF_EN_REFR       0x0100

#endif /* TMC4210_REGISTERS_H */
