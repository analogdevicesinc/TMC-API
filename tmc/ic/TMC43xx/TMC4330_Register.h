#ifndef TMC4330_REGISTER_H
#define TMC4330_REGISTER_H

	#define TMC4330_GENERAL_CONF          0x00
	#define TMC4330_REFERENCE_CONF        0x01
	#define TMC4330_START_CONF            0x02
	#define TMC4330_INPUT_FILT_CONF       0x03
	#define TMC4330_SCALE_VALUES          0x05
	#define TMC4330_ENC_IN_CONF           0x07
	#define TMC4330_ENC_IN_DATA           0x08
	#define TMC4330_STEP_CONF             0x0A
	#define TMC4330_SPI_STATUS_SELECTION  0x0B
	#define TMC4330_EVENT_CLEAR_CONF      0x0C
	#define TMC4330_INTR_CONF             0x0D
	#define TMC4330_EVENTS                0x0E
	#define TMC4330_STATUS                0x0F

	#define TMC4330_STP_LENGTH_ADD        0x10
	#define TMC4330_DIR_SETUP_TIME        0x10
	#define TMC4330_START_OUT_ADD         0x11
	#define TMC4330_GEAR_RATIO            0x12
	#define TMC4330_START_DELAY           0x13
	#define TMC4330_CLK_GATING_DELAY      0x14
	#define TMC4330_STDBY_DELAY           0x15
	#define TMC4330_PWM_VMAX              0x17
	#define TMC4330_CL_BETA               0x1C
	#define TMC4330_CL_GAMMA              0x1C
	#define TMC4330_HOME_SAFETY_MARGIN    0x1E
	#define TMC4330_PWM_FREQ              0x1F

	#define TMC4330_RAMPMODE              0x20
	#define TMC4330_XACTUAL               0x21
	#define TMC4330_VACTUAL               0x22
	#define TMC4330_AACTUAL               0x23
	#define TMC4330_VMAX                  0x24
	#define TMC4330_VSTART                0x25
	#define TMC4330_VSTOP                 0x26
	#define TMC4330_VBREAK                0x27
	#define TMC4330_AMAX                  0x28
	#define TMC4330_DMAX                  0x29
	#define TMC4330_ASTART                0x2A
	#define TMC4330_SIGN_AACT             0x2A
	#define TMC4330_DFINAL                0x2B
	#define TMC4330_DSTOP                 0x2C
	#define TMC4330_BOW1                  0x2D
	#define TMC4330_BOW2                  0x2E
	#define TMC4330_BOW3                  0x2F
	#define TMC4330_BOW4                  0x30
	#define TMC4330_CLK_FREQ              0x31

	#define TMC4330_POS_COMP              0x32
	#define TMC4330_VIRT_STOP_LEFT        0x33
	#define TMC4330_VIRT_STOP_RIGHT       0x34
	#define TMC4330_X_HOME                0x35
	#define TMC4330_X_LATCH_RD            0x36
	#define TMC4330_REV_CNT_RD            0x36
	#define TMC4330_X_RANGE_WR            0x36
	#define TMC4330_X_TARGET              0x37

	#define TMC4330_X_PIPE0               0x38
	#define TMC4330_X_PIPE1               0x39
	#define TMC4330_X_PIPE2               0x3A
	#define TMC4330_X_PIPE3               0x3B
	#define TMC4330_X_PIPE4               0x3C
	#define TMC4330_X_PIPE5               0x3D
	#define TMC4330_X_PIPE6               0x3E
	#define TMC4330_X_PIPE7               0x3F

	#define TMC4330_SH_REG0               0x40
	#define TMC4330_SH_REG1               0x41
	#define TMC4330_SH_REG2               0x42
	#define TMC4330_SH_REG3               0x43
	#define TMC4330_SH_REG4               0x44
	#define TMC4330_SH_REG5               0x45
	#define TMC4330_SH_REG6               0x46
	#define TMC4330_SH_REG7               0x47
	#define TMC4330_SH_REG8               0x48
	#define TMC4330_SH_REG9               0x49
	#define TMC4330_SH_REG10              0x4A
	#define TMC4330_SH_REG11              0x4B
	#define TMC4330_SH_REG12              0x4C
	#define TMC4330_SH_REG13              0x4D

	#define TMC4330_CLK_GATING_REG        0x4F
	#define TMC4330_RESET_REG             0x4F

	#define TMC4330_ENC_POS               0x50
	#define TMC4330_ENC_LATCH_RD          0x51
	#define TMC4330_ENC_RESET_VAL_WR      0x51
	#define TMC4330_ENC_POS_DEV_RD        0x52
	#define TMC4330_CL_TR_TOLERANCE_WR    0x52
	#define TMC4330_ENC_POS_DEV_TOL_WR    0x53
	#define TMC4330_ENC_IN_RES_WR         0x54
	#define TMC4330_ENC_CONST_RD          0x54
	#define TMC4330_MANUAL_ENC_CONST0     0x54
	#define TMC4330_ENC_OUT_RES           0x55
	#define TMC4330_SER_CLK_IN_HIGH_WR    0x56
	#define TMC4330_SER_CLK_IN_LOW_WR     0x56
	#define TMC4330_SSI_IN_CLK_DELAY_WR   0x57
	#define TMC4330_SSI_IN_WTIME_WR       0x57
	#define TMC4330_SER_PTIME_WR          0x58

	#define TMC4330_CL_OFFSET             0x59
	#define TMC4330_PID_P_WR              0x5A
	#define TMC4330_CL_VMAX_CALC_P_WR     0x5A
	#define TMC4330_PID_VEL_RD            0x5A
	#define TMC4330_PID_I_WR              0x5B
	#define TMC4330_CL_VMAX_CALC_I_WR     0x5B
	#define TMC4330_PID_ISUM_RD           0x5B
	#define TMC4330_PID_D_WR              0x5C
	#define TMC4330_CL_DELTA_P_WR         0x5C
	#define TMC4330_PID_I_CLIP_WR         0x5D
	#define TMC4330_PID_D_CLKDIV_WR       0x5D
	#define TMC4330_PID_E_RD              0x5D
	#define TMC4330_PID_DV_CLIP_WR        0x5E
	#define TMC4330_PID_TOLERANCE_WR      0x5F
	#define TMC4330_CL_TOLERANCE_WR       0x5F

	#define TMC4330_FS_VEL_WR             0x60
	#define TMC4330_CL_VMIN_EMF_WR        0x60
	#define TMC4330_CL_VADD_EMF           0x61
	#define TMC4330_ENC_VEL_ZERO_WR       0x62
	#define TMC4330_ENC_VMEAN_WAIT_WR     0x63
	#define TMC4330_ENC_VMEAN_FILTER_WR   0x63
	#define TMC4330_ENC_VMEAN_INT_WR      0x63
	#define TMC4361_SER_ENC_VARIATION_WR  0x63
	#define TMC4361_CL_CYCLE_WR           0x63
	#define TMC4330_SYNCHRO_SET           0x64
	#define TMC4330_V_ENC_RD              0x65
	#define TMC4330_V_ENC_MEAN_RD         0x66

	#define TMC4330_ADDR_TO_ENC           0x68
	#define TMC4330_DATA_TO_ENC           0x69
	#define TMC4330_ADDR_FROM_ENC         0x6A
	#define TMC4330_DATA_FROM_ENC         0x6B

	#define TMC4330_MSLUT_0_WR            0x70
	#define TMC4330_MSLUT_1_WR            0x71
	#define TMC4330_MSLUT_2_WR            0x72
	#define TMC4330_MSLUT_3_WR            0x73
	#define TMC4330_MSLUT_4_WR            0x74
	#define TMC4330_MSLUT_5_WR            0x75
	#define TMC4330_MSLUT_6_WR            0x76
	#define TMC4330_MSLUT_7_WR            0x77
	#define TMC4330_MSLUTSEL_WR           0x78
	#define TMC4330_MSCNT_RD              0x79
	#define TMC4330_USTEPA_RD             0x7A
	#define TMC4330_USTEPB_RD             0x7A
	#define TMC4330_USTEPA_SCALE_RD       0x7B
	#define TMC4330_USTEPB_SCALE_RD       0x7B
	#define TMC4330_TZEROWAIT_WR          0x7B
	#define TMC4330_CIRCULAR_DEC_WR       0x7C
	#define TMC4330_ENC_COMP_XOFFSET      0x7D
	#define TMC4330_ENC_COMP_YOFFSET      0x7D
	#define TMC4330_ENC_COMP_AMPL         0x7D
	#define TMC4330_START_SIN_WR          0x7E
	#define TMC4330_START_SIN90_WR        0x7E

	#define TMC4330_VERSION_NO_RD         0x7F

	#define TMC4330_RAMP_HOLD      0
	#define TMC4330_RAMP_TRAPEZ    1
	#define TMC4330_RAMP_SSHAPE    2
	#define TMC4330_RAMP_POSITION  4

#endif /* TMC4330_REGISTER_H */
