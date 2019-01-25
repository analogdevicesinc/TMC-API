/*
 * TMC43xx.c
 *
 *  Created on: 30.01.2017
 *      Author: BS
 *    Based on: TMC43xx-MK20.c (17.10.2014 OK)
 */

#include "TMC43xx.h"
#include "TMC4361A_Register.h"

// Comment out your module // todo API 2: decide if these variables go here (API) or in Evalboard/Module
//#define TMC4330A
//#define TMC4331A
//#define TMC4361
#define TMC4361A

#ifdef TMC4330A
	#include "TMC4330A_Register.h"
#endif

// Comment out the type of driver // todo API 2: decide if these variables go here (API) or in Evalboard/Module
//#define DRVTYPE_TMC262
#define DRVTYPE_TMC5130

// => Shared variables // todo API 2: decide if these variables go here (API) or in Evalboard/Module
//extern int tmc43xx_VMax;
extern u8 tmc43xx_VMaxModified;
//extern int tmc43xx_AMax;
//extern u8 tmc43xx_AMaxModified;
// <= Shared variables

// => SPI wrapper
extern int tmc43xx_spi_readInt(uint8 axis, uint8 address);
extern void tmc43xx_spi_writeInt(uint8 axis, uint8 address, int32 value);
//extern u16 tmc43xx_spi_readRegister16BitValue(uint8 axis, uint8 address, uint8 channel);
//extern void tmc43xx_spi_writeRegister16BitValue(uint8 axis, uint8 address, uint8 channel, uint16 value);
// <= SPI wrapper

const TMotorConfig MotorConfig=
{
	64,   // IRun
	8,    // IStandby
	200,  // Setting Delay
	0     // BoostCurrent
};

const TClosedLoopConfig ClosedLoopConfig=
{
	0,           // ClosedLoopMode
	300000,      // GammaVMin
	600000,      // GammaVAdd
	255,         // Gamma
	256,         // Beta
	0,           // Offset
	100,         // CurrentScalerMinimum
	240,         // CurrentScalerMaximum
	0,           // CurrentScalerStartUp
	1000,        // UpscaleDelay
	10000,       // DownscaleDelay
	10000,       // CorrectionVelocityP
	20,          // CorrectionVelocityI
	10,          // CorrectionVelocityIClip
	0,           // CorrectionVelocityDClk
	1073741823,  // CorrectionVelocityDClip
	65536,       // PositionCorrectionP
	100,         // PositionCorrectionTolerance
	100,         // PositionWindow
	0,           // EncVMeanWait
	7,           // EncVMeanFilter
	500,         // EncVMeanInt
	0,           // EncoderCorrectionYOffset
};

/*******************************************************************
	 Function: tmc43xx_writeBytes()
	 Parameter: Address: Register address
	            x1, x2, x3, x4: bytes to be written

	 Returns: ---

	 Purpose: Write 4 bytes in a TMC43xx register
********************************************************************/
void tmc43xx_writeBytes(uint8 Axis, uint8 Address, uint8 x1, uint8 x2, uint8 x3, uint8 x4)
{
	uint32 Value;

	Value  = x1 << 24;
	Value |= x2 << 16;
	Value |= x3 << 8;
	Value |= x4;

	tmc43xx_spi_writeInt(Axis, Address|TMC43xx_WRITE, Value);
}


/*******************************************************************
	 Function: tmc43xx_writeInt()
	 Parameter: Address: Register address
	            Value: value to be written

	 Returns: ---

	 Purpose: Write a 32-Bit value in a TMC43xx register.
********************************************************************/
void tmc43xx_writeInt(uint8 Axis, uint8 Address, int32 Value)
{
	tmc43xx_spi_writeInt(Axis, Address|TMC43xx_WRITE, Value);
}


/*******************************************************************
	 Function: tmc43xx_readInt()
	 Parameter: Address: Register address

	 Returns: read value

	 Purpose: Read a 32-bit value from a TMC43xx register
********************************************************************/
int32 tmc43xx_readInt(uint8 Axis, uint8 Address)
{
	tmc43xx_spi_readInt(Axis, Address);
	return tmc43xx_spi_readInt(Axis, Address);
}


void tmc43xx_setBits(uint8 Axis, uint8 Address, uint32 BitMask)
{
	uint32 Value;

	Value = tmc43xx_readInt(Axis, Address);
	Value |= BitMask;
	tmc43xx_writeInt(Axis, Address, Value);
}


void tmc43xx_clearBits(uint8 Axis, uint8 Address, uint32 BitMask)
{
	uint32 Value;

	Value = tmc43xx_readInt(Axis, Address);
	Value &= ~BitMask;
	tmc43xx_writeInt(Axis, Address, Value);
}


void tmc43xx_writeBits(uint8 Axis, uint8 Address, uint32 Value, uint8 Start, uint8 Size)
{
	uint32 RegVal;
	uint32 Mask;

	RegVal = tmc43xx_readInt(Axis, Address);

	Mask = 0;
	uint32 i;
	for(i = Start; i < Start+Size; i++)
		Mask |= (1<<i);
	RegVal &= ~Mask;
	RegVal |= (Value << Start) & Mask;

	tmc43xx_writeInt(Axis, Address, RegVal);
}


uint32 tmc43xx_peekEvents(uint8 Axis)
{
	tmc43xx_writeInt(Axis, TMC4361A_EVENT_CLEAR_CONF, 0xFFFFFFFF);
	return tmc43xx_readInt(Axis, TMC4361A_EVENTS);
}


uint32 tmc43xx_readAndClearEvents(uint8 Axis, uint32 EventMask)
{
	tmc43xx_writeInt(Axis, TMC4361A_EVENT_CLEAR_CONF, ~EventMask);
	return tmc43xx_readInt(Axis, TMC4361A_EVENTS);
}


/*******************************************************************
	 Function: tmc43xx_hardStop()
	 Parameter: ---
	 Returns: ---

	 Purpose: Stop the motor immediately
********************************************************************/
void tmc43xx_hardStop(uint8 Axis)
{
	tmc43xx_VMaxModified = TRUE;
	tmc43xx_writeInt(Axis, TMC4361A_RAMPMODE, TMC43xx_RAMPMODE_VEL_HOLD);
	tmc43xx_writeInt(Axis, TMC4361A_VMAX, 0);
}


/*******************************************************************
	 Function: tmc43xx_init
	 Parameter: ---
	 Returns: ---

	 Purpose: Initialize TMC43xx
********************************************************************/
void tmc43xx_init(uint8 numberOfMotors)
{
	uint8 Axis;
	for(Axis = 0; Axis < numberOfMotors; Axis++)
	{
		tmc43xx_writeInt(Axis, TMC4361A_GENERAL_CONF, TMC43xx_GCONF_ENC_INC|TMC43xx_GCONF_ENC_DIFF_DIS);
#if defined(DRVTYPE_TMC262)
	#if defined(TMC4331A) || defined(TMC4361) || defined(TMC4361A)
		tmc43xx_writeInt(Axis, TMC4361A_SPIOUT_CONF, TMC43xx_SPIOUT_TMC26x_389
							  |TMC43xx_SPIOUT_ENABLE_SHADOW_DATAGRAMS);  // TMC26x SPI
	#endif
#elif defined(DRVTYPE_TMC5130)
		tmc43xx_writeInt(Axis, TMC4361A_STP_LENGTH_ADD, 0x00050005);
	#if defined(TMC4331A) || defined(TMC4361) || defined(TMC4361A)
		tmc43xx_writeInt(Axis, TMC4361A_SPIOUT_CONF, 0x83300000|TMC43xx_SPIOUT_TMC21xx
					|TMC43xx_SPIOUT_POLL_BLOCK_MULTI(2)
					//|TMC43xx_SPIOUT_DISABLE_POLLING
					|TMC43xx_SPIOUT_ENABLE_SHADOW_DATAGRAMS
					|TMC43xx_SPIOUT_COVER_DONE_NOT_FOR_CURRENT
					);
	#endif
		tmc43xx_writeInt(Axis, TMC4361A_EVENT_CLEAR_CONF, ~TMC43xx_EV_COVER_DONE);  // Read event register deletes only the cover-done bit
		tmc43xx_readInt(Axis, TMC4361A_EVENTS);
		tmc43xx_writeBytes(Axis, TMC4361A_COVER_HIGH_WR, 0, 0, 0, 0);
		tmc43xx_writeInt(Axis, TMC4361A_COVER_LOW_WR, 0);
#else
#error "Driver type not supported"
#endif

#if defined(TMC4331A) || defined(TMC4361) || defined(TMC4361A)
		tmc43xx_writeInt(Axis, TMC4361A_CURRENT_CONF, TMC43xx_CURCONF_HOLD_EN|TMC43xx_CURCONF_DRIVE_EN);  // Current settings through TMC43xx
#endif
		tmc43xx_writeInt(Axis, TMC4361A_RAMPMODE, TMC43xx_RAMPMODE_POS_HOLD);
		tmc43xx_writeInt(Axis, TMC4361A_X_TARGET, 0);
		tmc43xx_writeInt(Axis, TMC4361A_XACTUAL, 0);

		tmc43xx_writeInt(Axis, TMC4361A_VMAX, 51200 << 8);
		tmc43xx_writeInt(Axis, TMC4361A_AMAX, 51200 << 2);
		tmc43xx_writeInt(Axis, TMC4361A_DMAX, 51200 << 2);

		tmc43xx_writeBytes(Axis, TMC4361A_SCALE_VALUES, MotorConfig.IStandby, 0, MotorConfig.IRun, MotorConfig.BoostCurrent);
		tmc43xx_writeInt(Axis, TMC4361A_STDBY_DELAY, MotorConfig.SettingDelay*160000);

#if defined(TMC4361) || defined(TMC4361A)
		tmc43xx_writeInt(Axis, TMC4361A_CL_VMIN_EMF_WR, ClosedLoopConfig.GammaVMin);
		tmc43xx_writeInt(Axis, TMC4361A_CL_VADD_EMF, ClosedLoopConfig.GammaVAdd);
		tmc43xx_writeInt(Axis, TMC4361A_CL_BETA, (ClosedLoopConfig.Gamma<<16)|ClosedLoopConfig.Beta);
		tmc43xx_writeInt(Axis, TMC4361A_CL_OFFSET, ClosedLoopConfig.Offset);
		tmc43xx_writeInt(Axis, TMC4361A_CL_VMAX_CALC_P_WR, ClosedLoopConfig.CorrectionVelocityP);
		tmc43xx_writeInt(Axis, TMC4361A_CL_VMAX_CALC_I_WR, ClosedLoopConfig.CorrectionVelocityI);
		tmc43xx_writeBytes(Axis, TMC4361A_PID_I_CLIP_WR, 0, ClosedLoopConfig.CorrectionVelocityDClk,
		ClosedLoopConfig.CorrectionVelocityIClip >> 8, ClosedLoopConfig.CorrectionVelocityIClip & 0xFF);
		tmc43xx_writeInt(Axis, TMC4361A_PID_DV_CLIP_WR, ClosedLoopConfig.CorrectionVelocityDClip);
		tmc43xx_writeInt(Axis, TMC4361A_CL_UPSCALE_DELAY, ClosedLoopConfig.UpscaleDelay);
		tmc43xx_writeInt(Axis, TMC4361A_CL_DOWNSCALE_DELAY, ClosedLoopConfig.DownscaleDelay);
		tmc43xx_writeInt(Axis, TMC4361A_CL_DELTA_P_WR, ClosedLoopConfig.PositionCorrectionP);
		tmc43xx_writeInt(Axis, TMC4361A_PID_TOLERANCE_WR, ClosedLoopConfig.PositionCorrectionTolerance);
		tmc43xx_writeInt(Axis, TMC4361A_CL_TR_TOLERANCE_WR, ClosedLoopConfig.PositionWindow);
		tmc43xx_writeBytes(Axis, TMC4361A_ENC_VMEAN_WAIT_WR, ClosedLoopConfig.EncVMeanInt >> 8,
		ClosedLoopConfig.EncVMeanInt & 0xFF, ClosedLoopConfig.EncVMeanFilter,
		ClosedLoopConfig.EncVMeanWait);

		tmc43xx_writeBytes(Axis, TMC4361A_ENC_COMP_XOFFSET, 0, ClosedLoopConfig.EncoderCorrectionYOffset, 0, 0);
#endif

		// Für Home-Switch-Abfrage
		tmc43xx_writeInt(Axis, TMC4361A_REFERENCE_CONF, BIT17|BIT16);
		tmc43xx_writeInt(Axis, TMC4361A_X_HOME, 0x7FFFFFFF);
	}
}

/*******************************************************************
	 Function: tmc43xx_getHomeInput
	 Parameter: ---
	 Returns: State of home input

	 Purpose: Polls home-input. Works only if bits 17 and 16 in
	          REFERENCE_CONF are set and XHOME of INT_MAX as well (trick)
********************************************************************/
uint8 tmc43xx_getHomeInput(uint8 Motor)
{
	if(tmc43xx_readInt(Motor, TMC4361A_STATUS) & TMC43xx_ST_HOME_ERROR)
		return TRUE;
	else
		return FALSE;
}

/*******************************************************************
	 Function: tmc43xx_moveToNextFullstep
	 Parameter: ---
	 Returns: 0 - moving to fullstep, 1 - already fullstep

	 Purpose: Moves from the current position to the next fullstep
********************************************************************/
uint8 tmc43xx_moveToNextFullstep(uint8 Axis)
{
	int32 value;
	int32 mscnt;

	if(tmc43xx_readInt(Axis, TMC4361A_VACTUAL) != 0) // motor must be stopped
		return 0;

	tmc43xx_writeInt(Axis, TMC4361A_RAMPMODE, TMC43xx_RAMPMODE_POS_HOLD);  // positioning & hold mode
	tmc43xx_writeInt(Axis, TMC4361A_VMAX, 10000<<8);                       // low velocity

	mscnt = tmc43xx_readInt(Axis, TMC4361A_MSCNT_RD) & 0x3FF;              // position in microstep table
	value = mscnt & 0xFF;                                                  // if last 8 bits are 0 its a multiple of 256
	value = 128-value;                                                     // assuming 256 µsteps fullsteps are 128+n*256

	if(!value) // fullstep position reached
		return 1;

	value = tmc43xx_readInt(Axis, TMC4361A_XACTUAL) + value;               // distance to next fullstep, assume 256 µsteps resolution
	tmc43xx_writeInt(Axis, TMC4361A_X_TARGET, value);                      // move to next fullstep

	return 0;
}
