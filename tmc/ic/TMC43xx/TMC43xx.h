/*
 * TMC43xx.h
 *
 *  Created on: 30.01.2017
 *      Author: BS
 *    Based on: TMC43xx-MK20.h (17.10.2014 OK)
 */

#ifndef TMC_IC_TMC43xx_H_
#define TMC_IC_TMC43xx_H_

#include "../../helpers/API_Header.h"

#define TMC43xx_WRITE 0x80

// TMC43xx GENERAL_CONFIG bits
#define TMC43xx_GCONF_USE_AVSTART          0x00000001
#define TMC43xx_GCONF_DIRECT_ACC_EN        0x00000002
#define TMC43xx_GCONF_DIRECT_BOW_EN        0x00000004
#define TMC43xx_GCONF_STEP_INACT_POL       0x00000008
#define TMC43xx_GCONF_TOGGLE_STEP          0x00000010
#define TMC43xx_GCONF_POL_DIR_OUT          0x00000020
#define TMC43xx_GCONF_INT_SD               0x00000000
#define TMC43xx_GCONF_EXT_SD_HIGH          0x00000040
#define TMC43xx_GCONF_EXT_SD_LOW           0x00000080
#define TMC43xx_GCONF_EXT_SD_TOGGLE        0x000000C0
#define TMC43xx_GCONF_DIR_IN_POL           0x00000100
#define TMC43xx_GCONF_SD_INDIRECT          0x00000200
#define TMC43xx_GCONF_ENC_INC              0x00000000
#define TMC43xx_GCONF_ENC_SSI              0x00000400
#define TMC43xx_GCONF_ENC_BISS             0x00000800
#define TMC43xx_GCONF_ENC_SPI              0x00000C00
#define TMC43xx_GCONF_ENC_DIFF_DIS         0x00001000
#define TMC43xx_GCONF_STDBY_CLOCK_LOW      0x00000000
#define TMC43xx_GCONF_STDBY_CLOCK_HIGH     0x00002000
#define TMC43xx_GCONF_STDBY_CHOPSYNC       0x00004000
#define TMC43xx_GCONF_STDBY_CLOCK_INT      0x00006000
#define TMC43xx_GCONF_INTR_POL             0x00008000
#define TMC43xx_GCONF_TARGET_REACHED_POL   0x00010000
#define TMC43xx_GCONF_CLK_GATING_EN        0x00020000
#define TMC43xx_GCONF_CLK_GATING_STDBY_EN  0x00040000
#define TMC43xx_GCONF_FS_EN                0x00080000
#define TMC43xx_GCONF_FS_SDOUT             0x00100000
#define TMC43xx_GCONF_DCSTEP_OFF           0x00000000
#define TMC43xx_GCONF_DCSTEP_AUTO          0x00200000
#define TMC43xx_GCONF_DCSTEP_TMC21xx       0x00400000
#define TMC43xx_GCONF_DCSTEP_TMC26x        0x00600000
#define TMC43xx_GCONF_PWM_OUT_EN           0x00800000
#define TMC43xx_GCONF_SER_ENC_OUT_EN       0x01000000
#define TMC43xx_GCONF_SER_ENC_OUT_DIFF     0x02000000
#define TMC43xx_GCONF_AUTO_DIRECT_SD_OFF   0x04000000
#define TMC43xx_GCONF_CIRC_CNT_XLATCH      0x08000000
#define TMC43xx_GCONF_REV_DIR              0x10000000
#define TMC43xx_GCONF_INTR_TR_PU_PD_EN     0x20000000
#define TMC43xx_GCONF_INTR_WIRED_AND       0x40000000
#define TMC43xx_GCONF_TR_WIRED_AND         0x80000000

// TMC43xx_SPI_OUT_CONF bits
#define TMC43xx_SPIOUT_OFF                         0x00000000
#define TMC43xx_SPIOUT_TMC23x                      0x00000008
#define TMC43xx_SPIOUT_TMC24x                      0x00000009
#define TMC43xx_SPIOUT_TMC26x_389                  0x0000000A
#define TMC43xx_SPIOUT_TMC26x_389_SD               0x0000000B
#define TMC43xx_SPIOUT_TMC21xx_SD                  0x0000000C
#define TMC43xx_SPIOUT_TMC21xx                     0x0000000D
#define TMC43xx_SPIOUT_SCALE                       0x00000004
#define TMC43xx_SPIOUT_SINLUT                      0x00000005
#define TMC43xx_SPIOUT_DACADDR                     0x00000006
#define TMC43xx_SPIOUT_DAC                         0x00000002
#define TMC43xx_SPIOUT_DAC_INV                     0x00000003
#define TMC43xx_SPIOUT_DAC_MAPPED                  0x00000001
#define TMC43xx_SPIOUT_COVER_ONLY                  0x0000000F
#define TMC43xx_SPIOUT_MD_OFF                      0x00000000
#define TMC43xx_SPIOUT_MD_FALLING                  0x00000010
#define TMC43xx_SPIOUT_MD_NO_STANDBY               0x00000020
#define TMC43xx_SPIOUT_MD_ALWAYS                   0x00000030
#define TMC43xx_SPIOUT_STDBY_ON_STALL              0x00000040
#define TMC43xx_SPIOUT_STALL_FLAG                  0x00000080
#define TMC43xx_STALL_LOAD_LIMIT(x)                ((x & 0x07) << 8)
#define TMC43xx_SPIOUT_PHASE_SHIFT                 0x00000100
#define TMC43xx_SPIOUT_THREE_PHASE_EN              0x00000010
#define TMC43xx_SPIOUT_SCALE_VAL_TR_EN             0x00000020
#define TMC43xx_SPIOUT_DISABLE_POLLING             0x00000040
#define TMC43xx_SPIOUT_ENABLE_SHADOW_DATAGRAMS     0x00000080
#define TMC43xx_SPIOUT_POLL_BLOCK_MULTI(x)         (((x) & 0x0F) << 8)
#define TMC43xx_SPIOUT_COVER_DONE_NOT_FOR_CURRENT  0x00001000

// TMC43xx ENC_IN configuration bits
#define TMC43xx_ENC_IN_MODE_OL            0x00000000
#define TMC43xx_ENC_IN_MODE_CL            0x00400000
#define TMC43xx_ENC_IN_MODE_PID_0         0x00800000
#define TMC43xx_ENC_IN_MODE PID_V         0x00C00000
#define TMC43xx_ENC_IN_CL_CALIBRATION_EN  0x01000000
#define TMC43xx_ENC_IN_CL_EMF_EN          0x02000000
#define TMC43xx_ENC_IN_CL_VLIMIT_EN       0x08000000
#define TMC43xx_ENC_IN_CL_VELOCITY_EN     0x10000000
#define TMC43xx_ENC_IN_SER_VAR_LIMIT      0x80000000

// TMC43xx_CURRENT_CONF bits
#define TMC43xx_CURCONF_HOLD_EN          0x00000001
#define TMC43xx_CURCONF_DRIVE_EN         0x00000002
#define TMC43xx_CURCONF_BOOST_ACC_EN     0x00000004
#define TMC43xx_CURCONF_BOOST_DEC_EN     0x00000008
#define TMC43xx_CURCONF_BOOST_START_EN   0x00000010
#define TMC43xx_CURCONF_SEC_DRIVE_EN     0x00000020
#define TMC43xx_CURCONF_FREEWHEELING_EN  0x00000040
#define TMC43xx_CURCONF_CL_SCALE_EN      0x00000080
#define TMC43xx_CURCONF_PWM_SCALE_REF    0x00000100
#define TMC43xx_CURCONF_PWM_AMPL(x)      (x<<16)

// TMC43xx_SCALE_VALUES bits
#define TMC43xx_SCALEVAL_BOOST(x)  (x & 0xFF)
#define TMC43xx_SCALEVAL_DRV1(x)   ((x & 0xFF) << 8)
#define TMC43xx_SCALEVAL_DRV2(x)   ((x & 0xFF) << 16)
#define TMC43xx_SCALEVAL_HOLD(x)   ((x & 0xFF) << 24)

// TMC43xx_EVENTS register bits
#define TMC43xx_EV_TARGET_REACHED     0x00000001
#define TMC43xx_EV_POSCOMP_REACHED    0x00000002
#define TMC43xx_EV_VELOCITY_REACHED   0x00000004
#define TMC43xx_EV_VZERO              0x00000008
#define TMC43xx_EV_VPOSITIVE          0x00000010
#define TMC43xx_EV_VNEGATIVE          0x00000020
#define TMC43xx_EV_AZERO              0x00000040
#define TMC43xx_EV_APOSITIVE          0x00000080
#define TMC43xx_EV_ANEGATIVE          0x00000100
#define TMC43xx_EV_MAX_PHASE_TRAP     0x00000200
#define TMC43xx_EV_FROZEN             0x00000400
#define TMC43xx_EV_STOP_LEFT          0x00000800
#define TMC43xx_EV_STOP_RIGHT         0x00001000
#define TMC43xx_EV_VIRT_STOP_LEFT     0x00002000
#define TMC43xx_EV_VIRT_STOP_RIGHT    0x00004000
#define TMC43xx_EV_HOME_ERROR         0x00008000
#define TMC43xx_EV_XLATCH_DONE        0x00010000
#define TMC43xx_EV_FS_ACTIVE          0x00020000
#define TMC43xx_EV_ENC_FAIL           0x00040000
#define TMC43xx_EV_N_ACTIVE           0x00080000
#define TMC43xx_EV_ENC_DONE           0x00100000
#define TMC43xx_EV_SER_ENC_DATA_FAIL  0x00200000
#define TMC43xx_EV_CRC_FAIL           0x00400000
#define TMC43xx_EV_SER_DATA_DONE      0x00800000
#define TMC43xx_EV_BISS_FLAG          0x01000000
#define TMC43xx_EV_COVER_DONE         0x02000000
#define TMC43xx_EV_ENC_VZERO          0x04000000
#define TMC43xx_EV_CL_MAX             0x08000000
#define TMC43xx_EV_CL_FIT             0x10000000
#define TMC43xx_EV_STOP_ON_STALL      0x20000000
#define TMC43xx_EV_MOTOR              0x40000000
#define TMC43xx_EV_RST                0x80000000

// TMC43xx_STATUS register bits
#define TMC43xx_ST_TARGET_REACHED          0x00000001
#define TMC43xx_ST_POSCOMP_REACHED         0x00000002
#define TMC43xx_ST_VEL_REACHED             0x00000004
#define TMC43xx_ST_VEL_POS                 0x00000008
#define TMC43xx_ST_VEL_NEG                 0x00000010
#define TMC43xx_ST_RAMP_ACC                0x00000020
#define TMC43xx_ST_RAMP_DEC                0x00000040
#define TMC43xx_ST_STOP_LEFT_ACTIVE        0x00000080
#define TMC43xx_ST_STOP_RIGHT_ACTIVE       0x00000100
#define TMC43xx_ST_VIRT_STOP_LEFT_ACTIVE   0x00000200
#define TMC43xx_ST_VIRT_STOP_RIGHT_ACTIVE  0x00000400
#define TMC43xx_ST_HOME_ERROR              0x00001000
#define TMC43xx_ST_ENC_FAIL                0x00004000

// TMC43xx ramp modes
#define TMC43xx_RAMPMODE_VEL_HOLD    0
#define TMC43xx_RAMPMODE_VEL_TRAPEZ  1
#define TMC43xx_RAMPMODE_VEL_SSHAPE  2
#define TMC43xx_RAMPMODE_POS_HOLD    4
#define TMC43xx_RAMPMODE_POS_TRAPEZ  5
#define TMC43xx_RAMPMODE_POS_SSHAPE  6

// TMC43xx reference switch configuration
#define TMC43xx_REFCONF_STOP_LEFT_EN       0x00000001
#define TMC43xx_REFCONF_STOP_RIGHT_EN      0x00000002
#define TMC43xx_REFCONF_POL_STOP_LEFT      0x00000004
#define TMC43xx_REFCONF_POL_STOP_RIGHT     0x00000008
#define TMC43xx_REFCONF_INV_STOP_DIR       0x00000010
#define TMC43xx_REFCONF_SOFT_STOP_EN       0x00000020
#define TMC43xx_REFCONF_VIRT_LEFT_LIM_EN   0x00000040
#define TMC43xx_REFCONF_VIRT_RIGHT_LIM_EN  0x00000080
#define TMC43xx_REFCONF_VIRT_STOP_HARD     0x00000100
#define TMC43xx_REFCONF_VIRT_STOP_LINEAR   0x00000200
#define TMC43xx_REFCONF_CIRCULAR           0x00400000
#define TMC43xx_REFCONF_STOP_ON_STALL      0x04000000
#define TMC43xx_REFCONF_DRV_AFTER_STALL    0x08000000
#define TMC43xx_REFCONF_CIRCULAR_ENC_EN    0x80000000

// TMC43xx access functions
void tmc43xx_writeBytes(uint8 Axis, uint8 Address, uint8 x1, uint8 x2, uint8 x3, uint8 x4);
void tmc43xx_writeInt(uint8 Axis, uint8 Address, int32 Value);
int32 tmc43xx_readInt(uint8 Axis, uint8 Address);
void tmc43xx_setBits(uint8 Axis, uint8 Address, uint32 BitMask);
void tmc43xx_clearBits(uint8 Axis, uint8 Address, uint32 BitMask);
void tmc43xx_writeBits(uint8 Axis, uint8 Address, uint32 Value, uint8 Start, uint8 Size);
uint32 tmc43xx_peekEvents(uint8 Axis);
uint32 tmc43xx_readAndClearEvents(uint8 Axis, uint32 EventMask);
uint8 tmc43xx_getHomeInput(uint8 Motor);
uint8 tmc43xx_moveToNextFullstep(uint8 Axis);
void tmc43xx_hardStop(uint8 Axis);
void tmc43xx_init(uint8 numberOfMotors);

typedef struct
{
	uint8 IRun;
	uint8 IStandby;
	uint16 SettingDelay;
	uint8 BoostCurrent;
} TMotorConfig;

typedef struct
{
	uint8 ClosedLoopMode;
	uint32 GammaVMin;
	uint32 GammaVAdd;
	uint8 Gamma;
	uint16 Beta;
	uint32 Offset;
	uint8 CurrentScalerMinimum;
	uint8 CurrentScalerMaximum;
	uint8 CurrentScalerStartUp;
	uint32 UpscaleDelay;
	uint32 DownscaleDelay;
	uint32 CorrectionVelocityP;
	uint32 CorrectionVelocityI;
	uint32 CorrectionVelocityIClip;
	uint32 CorrectionVelocityDClk;
	uint32 CorrectionVelocityDClip;
	uint32 PositionCorrectionP;
	uint32 PositionCorrectionTolerance;
	uint32 PositionWindow;
	uint8 EncVMeanWait;
	uint8 EncVMeanFilter;
	uint32 EncVMeanInt;
	int8 EncoderCorrectionYOffset;
} TClosedLoopConfig;

#endif /* TMC_IC_TMC43xx_H_ */
