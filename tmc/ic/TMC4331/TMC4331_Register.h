/*
 * TMC4331_Register.h
 *
 *  Created on: 17.07.2017
 *      Author: LK
 */

#ifndef TMC4331_REGISTER_H
#define TMC4331_REGISTER_H

#define TMC4331_GENERAL_CONF          0x00
#define TMC4331_REFERENCE_CONF        0x01
#define TMC4331_START_CONF            0x02
#define TMC4331_INPUT_FILT_CONF       0x03
#define TMC4331_SPIOUT_CONF           0x04
#define TMC4331_CURRENT_CONF          0x05
#define TMC4331_SCALE_VALUES          0x06
#define TMC4331_STEP_CONF             0x0A
#define TMC4331_SPI_STATUS_SELECTION  0x0B
#define TMC4331_EVENT_CLEAR_CONF      0x0C
#define TMC4331_INTR_CONF             0x0D
#define TMC4331_EVENTS                0x0E
#define TMC4331_STATUS                0x0F

#define TMC4331_STP_LENGTH_ADD        0x10
#define TMC4331_DIR_SETUP_TIME        0x10
#define TMC4331_START_OUT_ADD         0x11
#define TMC4331_GEAR_RATIO            0x12
#define TMC4331_START_DELAY           0x13
#define TMC4331_CLK_GATING_DELAY      0x14
#define TMC4331_STDBY_DELAY           0x15
#define TMC4331_FREEWHEEL_DELAY       0x16
#define TMC4331_VDRV_SCALE_LIMIT      0x17
#define TMC4331_PWM_VMAX              0x17
#define TMC4331_UP_SCALE_DELAY        0x18
#define TMC4331_HOLD_SCALE_DELAY      0x19
#define TMC4331_DRV_SCALE_DELAY       0x1A
#define TMC4331_BOOST_TIME            0x1B
#define TMC4331_DAC_ADDR_A            0x1D
#define TMC4331_DAC_ADDR_B            0x1D
#define TMC4331_SPI_SWITCH_VEL        0x1D
#define TMC4331_HOME_SAFETY_MARGIN    0x1E
#define TMC4331_PWM_FREQ              0x1F
#define TMC4331_CHOPSYNC_DIV          0x1F

#define TMC4331_RAMPMODE              0x20
#define TMC4331_XACTUAL               0x21
#define TMC4331_VACTUAL               0x22
#define TMC4331_AACTUAL               0x23
#define TMC4331_VMAX                  0x24
#define TMC4331_VSTART                0x25
#define TMC4331_VSTOP                 0x26
#define TMC4331_VBREAK                0x27
#define TMC4331_AMAX                  0x28
#define TMC4331_DMAX                  0x29
#define TMC4331_ASTART                0x2A
#define TMC4331_SIGN_AACT             0x2A
#define TMC4331_DFINAL                0x2B
#define TMC4331_DSTOP                 0x2C
#define TMC4331_BOW1                  0x2D
#define TMC4331_BOW2                  0x2E
#define TMC4331_BOW3                  0x2F
#define TMC4331_BOW4                  0x30
#define TMC4331_CLK_FREQ              0x31

#define TMC4331_POS_COMP              0x32
#define TMC4331_VIRT_STOP_LEFT        0x33
#define TMC4331_VIRT_STOP_RIGHT       0x34
#define TMC4331_X_HOME                0x35
#define TMC4331_X_LATCH_RD            0x36
#define TMC4331_REV_CNT_RD            0x36
#define TMC4331_X_RANGE_WR            0x36
#define TMC4331_X_TARGET              0x37

#define TMC4331_X_PIPE0               0x38
#define TMC4331_X_PIPE1               0x39
#define TMC4331_X_PIPE2               0x3A
#define TMC4331_X_PIPE3               0x3B
#define TMC4331_X_PIPE4               0x3C
#define TMC4331_X_PIPE5               0x3D
#define TMC4331_X_PIPE6               0x3E
#define TMC4331_X_PIPE7               0x3F

#define TMC4331_SH_REG0               0x40
#define TMC4331_SH_REG1               0x41
#define TMC4331_SH_REG2               0x42
#define TMC4331_SH_REG3               0x43
#define TMC4331_SH_REG4               0x44
#define TMC4331_SH_REG5               0x45
#define TMC4331_SH_REG6               0x46
#define TMC4331_SH_REG7               0x47
#define TMC4331_SH_REG8               0x48
#define TMC4331_SH_REG9               0x49
#define TMC4331_SH_REG10              0x4A
#define TMC4331_SH_REG11              0x4B
#define TMC4331_SH_REG12              0x4C
#define TMC4331_SH_REG13              0x4D

#define TMC4331_CLK_GATING_REG        0x4F
#define TMC4331_RESET_REG             0x4F

#define TMC4331_FS_VEL_WR             0x60
#define TMC4331_DC_VEL_WR             0x60
#define TMC4331_DC_TIME_WR            0x61
#define TMC4331_DC_SG_WR              0x61
#define TMC4331_DC_BLKTIME_WR         0x61
#define TMC4331_DC_LSPTM_WR           0x62
#define TMC4331_SYNCHRO_SET           0x64
#define TMC4331_VSTALL_LIMIT_WR       0x67

#define TMC4331_COVER_LOW_WR          0x6C
#define TMC4331_POLLING_STATUS_RD     0x6C
#define TMC4331_COVER_HIGH_WR         0x6D
#define TMC4331_POLLING_REG_WR        0x6D
#define TMC4331_COVER_DRV_LOW_RD      0x6E
#define TMC4331_COVER_DRV_HIGH_RD     0x6F

#define TMC4331_MSLUT_0_WR            0x70
#define TMC4331_MSLUT_1_WR            0x71
#define TMC4331_MSLUT_2_WR            0x72
#define TMC4331_MSLUT_3_WR            0x73
#define TMC4331_MSLUT_4_WR            0x74
#define TMC4331_MSLUT_5_WR            0x75
#define TMC4331_MSLUT_6_WR            0x76
#define TMC4331_MSLUT_7_WR            0x77
#define TMC4331_MSLUTSEL_WR           0x78
#define TMC4331_MSCNT_RD              0x79
#define TMC4331_MSOFFSET_WR           0x79
#define TMC4331_CURRENTA_RD           0x7A
#define TMC4331_CURRENTB_RD           0x7A
#define TMC4331_CURRENTA_SPI_RD       0x7B
#define TMC4331_CURRENTB_SPI_RD       0x7B
#define TMC4331_TZEROWAIT_WR          0x7B
#define TMC4331_SCALE_PARAM_RD        0x7C
#define TMC4331_CIRCULAR_DEC_WR       0x7C
#define TMC4331_START_SIN_WR          0x7E
#define TMC4331_START_SIN90_120_WR    0x7E
#define TMC4331_DAC_OFFSET_WR         0x7E
#define TMC4331_VERSION_NO_RD         0x7F

//TMC4331_SCALE_VALUES bits
#define TMC4331_SCALEVAL_BOOST(x)  (x & 0xFF)
#define TMC4331_SCALEVAL_DRV1(x)   ((x & 0xFF) << 8)
#define TMC4331_SCALEVAL_DRV2(x)   ((x & 0xFF) << 16)
#define TMC4331_SCALEVAL_HOLD(x)   ((x & 0xFF) << 24)

#endif /* TMC4331_REGISTER_H */
