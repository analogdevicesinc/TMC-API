/*
 * TMC262.c
 *
 *  Created on: 27.01.2017
 *      Author: BS
 *    Based on: TMC262-K20.c (12.01.2009 OK)
 */

#include "TMC262.h"

// Data structs for TMC262 Shadowregister
typedef struct
{
	uint8 Intpol;
	uint8 DEdge;
	uint8 MRes;
} TStepDirConfig;

typedef struct
{
	uint8 BlankTime;
	uint8 ChopperMode;
	uint8 HysteresisDecay;
	uint8 RandomTOff;
	uint8 HysteresisEnd;
	uint8 HysteresisStart;
	uint8 TOff;
	uint8 DisableFlag;
} TChopperConfig;

typedef struct
{
	uint8 SmartIMin;
	uint8 SmartDownStep;
	uint8 SmartStallLevelMax;
	uint8 SmartUpStep;
	uint8 SmartStallLevelMin;
} TSmartEnergyControl;

typedef struct
{
	uint8 FilterEnable;
	int8 StallGuardThreshold;
	uint8 CurrentScale;
} TStallGuardConfig;


typedef struct
{
	uint8 SlopeHighSide;
	uint8 SlopeLowSide;
	uint8 ProtectionDisable;
	uint8 ProtectionTimer;
	uint8 StepDirectionDisable;
	uint8 VSenseScale;
	uint8 ReadBackSelect;
} TDriverConfig;

typedef enum {
	RB_CHOPPER,
	RB_DRIVER,
	RB_SMART_ENERGY,
	RB_STALL_GUARD,
	RB_STEP_DIR
} TReadBackDatagram;

// Variablen
static TStepDirConfig StepDirConfig;            // Shadowregister of DRVCTRL-Register
static TChopperConfig ChopperConfig;            // Shadowregister of CHOPCONF-Register
static TSmartEnergyControl SmartEnergyControl;  // Shadowregister of SMARTEN-Register
static TStallGuardConfig StallGuardConfig;      // Shadowregister of SGSCONF-Register
static TDriverConfig DriverConfig;              // Shadowregister of DRVCONF-Register
static TReadBackDatagram ReadBackDatagram;      // Next telegram to be used to read the state
static uint32 SPIReadInt;
static uint32 SPIWriteInt;

static uint32 SPIStepDirConf;
static uint32 SPIChopperConf;
static uint32 SPISmartConf;
static uint32 SPISGConf;
static uint32 SPIDriverConf;

// Choose the configuration that suits your board // todo API 2: configuration should be chosen outside API e.g. in TMC-EvalSystem
#define DEVTYPE_TMC428 // Direct SPI communication if TMC262 is connected to the processor
//#define DEVTYPE_TMC43xx // Communication is forwarded to TMC262 by TMC43xx with "cover datagrams"

#if defined(DEVTYPE_TMC428)
	// => SPI wrapper
	extern uint8 tmc5130_spi_readWrite(uint8 data, uint8 lastTransfer);
	// <= SPI wrapper
#elif defined(DEVTYPE_TMC43xx)
	#include "../TMC43xx/TMC4361A_Register.h"
	// => Cover data wrapper
	extern int32 tmc43xx_readInt(uint8 address);
	extern int32 tmc43xx_writeInt(uint8 address, uint32 data);
	// <= Cover data wrapper
#else
#error "Device not supported!"
#endif

// Functions

/*******************************************************************
	 Function: ReadWrite262()
	 Parameter: Read: Pointer to int for result
	            Write: Array with 3 bytes to be written in TMC262

	 Returns: ---

	 Purpose: SPI-Communication with TMC262. The datagrams are shifted
	          to the correct position.
********************************************************************/
static void ReadWrite262(uint32 *ReadInt, uint32 WriteInt)
{
#if defined(DEVTYPE_TMC428)
	*ReadInt = tmc5130_spi_readWrite(WriteInt>>16, FALSE);
	*ReadInt <<= 8;
	*ReadInt |= tmc5130_spi_readWrite(WriteInt>>8, FALSE);
	*ReadInt <<= 8;
	*ReadInt |= tmc5130_spi_readWrite(WriteInt & 0xFF, TRUE);
	*ReadInt >>= 4;

#elif defined(DEVTYPE_TMC43xx)
	tmc43xx_writeInt(TMC4361A_EVENT_CLEAR_CONF, ~TMC4361A_COVER_DONE);
	tmc43xx_readInt(TMC4361A_EVENTS);
	tmc43xx_writeInt(TMC4361A_COVER_LOW_WR, WriteInt);
	while(!(tmc43xx_readInt(TMC4361A_EVENTS) & TMC4361A_COVER_DONE)) {};
	*ReadInt = tmc43xx_readInt(TMC4361A_COVER_DRV_LOW_RD);

#else
#error "Device not supported!"
#endif
}


/*******************************************************************
	 Function: WriteStepDirConfig()
	 Parameter: ---

	 Returns: ---

	 Purpose: Write register DRVCTRL of TMC262 in Step/Dir Mode.
	          The parameters must be pre-configured in the StepDirConfig
	          global variables.
********************************************************************/
static void WriteStepDirConfig()
{
	SPIWriteInt = 0;
	if(StepDirConfig.Intpol)
		SPIWriteInt |= BIT9;
	if(StepDirConfig.DEdge)
		SPIWriteInt |= BIT8;
	if(StepDirConfig.MRes > 15)
		StepDirConfig.MRes = 15;
	SPIWriteInt |= StepDirConfig.MRes;

	ReadWrite262(&SPIReadInt, SPIWriteInt);
	SPIStepDirConf = SPIWriteInt;
}


/*******************************************************************
	 Function: WriteChopperConfig()
	 Parameter: ---

	 Returns: ---

	 Purpose: Write register CHOPCONF of TMC262 in Step/Dir Mode.
	          The parameters must be pre-configured in the ChopperConfig
	          global variables.
********************************************************************/
static void WriteChopperConfig()
{
	ChopperConfig.BlankTime        = MIN(ChopperConfig.BlankTime, 3);
	ChopperConfig.HysteresisDecay  = MIN(ChopperConfig.HysteresisDecay, 3);
	ChopperConfig.HysteresisEnd    = MIN(ChopperConfig.HysteresisEnd, 15);
	ChopperConfig.HysteresisStart  = MIN(ChopperConfig.HysteresisStart, 7);
	ChopperConfig.TOff             = MIN(ChopperConfig.TOff, 15);

	SPIWriteInt = 0;
	SPIWriteInt |= BIT19;  // Registeraddresse CHOPCONF;
	SPIWriteInt |= ((uint32) ChopperConfig.BlankTime) << 15;
	if(ChopperConfig.ChopperMode)
		SPIWriteInt |= BIT14;
	if(ChopperConfig.RandomTOff)
		SPIWriteInt |= BIT13;
	SPIWriteInt |= ((uint32) ChopperConfig.HysteresisDecay) << 11;
	SPIWriteInt |= ((uint32) ChopperConfig.HysteresisEnd) << 7;
	SPIWriteInt |= ((uint32) ChopperConfig.HysteresisStart) << 4;
	if(!ChopperConfig.DisableFlag)
		SPIWriteInt |= ((uint32) ChopperConfig.TOff);  // wenn DisableFlag gesetzt wird 0 gesendet

	ReadWrite262(&SPIReadInt, SPIWriteInt);
	SPIChopperConf = SPIWriteInt;
}


/*******************************************************************
	 Function: WriteSmartEnergyControl()
	 Parameter: ---

	 Returns: ---

	 Purpose: Write register SMARTEN of TMC262 in Step/Dir Mode.
	          The parameters must be pre-configured in the
	          SmartEnergyControl global variables.
********************************************************************/
static void WriteSmartEnergyControl()
{
	SmartEnergyControl.SmartIMin           = MIN(SmartEnergyControl.SmartIMin, 1);
	SmartEnergyControl.SmartDownStep       = MIN(SmartEnergyControl.SmartDownStep, 3);
	SmartEnergyControl.SmartStallLevelMax  = MIN(SmartEnergyControl.SmartStallLevelMax, 15);
	SmartEnergyControl.SmartUpStep         = MIN(SmartEnergyControl.SmartUpStep, 3);
	SmartEnergyControl.SmartStallLevelMin  = MIN(SmartEnergyControl.SmartStallLevelMin, 15);

	SPIWriteInt =  0;
	SPIWriteInt |= BIT19 | BIT17;  // Register address SMARTEN
	SPIWriteInt |= ((uint32) SmartEnergyControl.SmartIMin) << 15;
	SPIWriteInt |= ((uint32) SmartEnergyControl.SmartDownStep)  << 13;
	SPIWriteInt |= ((uint32) SmartEnergyControl.SmartStallLevelMax) << 8;
	SPIWriteInt |= ((uint32) SmartEnergyControl.SmartUpStep) << 5;
	SPIWriteInt |= ((uint32) SmartEnergyControl.SmartStallLevelMin);

	ReadWrite262(&SPIReadInt, SPIWriteInt);
	SPISmartConf = SPIWriteInt;
}


/*******************************************************************
	 Function: WriteStallGuardConfig()
	 Parameter: ---

	 Returns: ---

	 Purpose: Write register SGCSCONF of TMC262 in Step/Dir Mode.
	          The parameters must be pre-configured in the
	          StallGuardConfig global variables.
********************************************************************/
static void WriteStallGuardConfig()
{
	if(abs(StallGuardConfig.StallGuardThreshold) > 63)
		StallGuardConfig.StallGuardThreshold = (StallGuardConfig.StallGuardThreshold > 0)? 63:-63;
	StallGuardConfig.CurrentScale = MIN(StallGuardConfig.CurrentScale, 31);

	SPIWriteInt = 0;
	SPIWriteInt |= BIT19 | BIT18;  // Register address SGSCONF
	if(StallGuardConfig.FilterEnable == 1)
		SPIWriteInt |= BIT16;
	SPIWriteInt |= ((uint32) StallGuardConfig.StallGuardThreshold & 0x7F) << 8;
	SPIWriteInt |= ((uint32) StallGuardConfig.CurrentScale);

	ReadWrite262(&SPIReadInt, SPIWriteInt);
	SPISGConf = SPIWriteInt;
}


/*******************************************************************
	 Function: WriteDriverConfig()
	 Parameter: ---

	 Returns: ---

	 Purpose: Write register DRVCONF of TMC262 in Step/Dir Mode.
	          The parameters must be pre-configured in the DriverConfig
	          global variables.
********************************************************************/
static void WriteDriverConfig()
{
	SPIWriteInt = 0;
	SPIWriteInt |= BIT19 | BIT18 | BIT17;  // Register address DRVCONF
	SPIWriteInt |= ((uint32) DriverConfig.SlopeHighSide) << 14;
	SPIWriteInt |= ((uint32) DriverConfig.SlopeLowSide) << 12;
	if(DriverConfig.ProtectionDisable == 1)
		SPIWriteInt |= BIT10;
	SPIWriteInt |= ((uint32) DriverConfig.ProtectionTimer) << 8;
	if(DriverConfig.StepDirectionDisable == 1)
		SPIWriteInt |= BIT7;
	if(DriverConfig.VSenseScale == 1)
		SPIWriteInt |= BIT6;
	SPIWriteInt |= ((uint32) DriverConfig.ReadBackSelect) << 4;

	ReadWrite262(&SPIReadInt, SPIWriteInt);
	SPIDriverConf = SPIWriteInt;
}

/*******************************************************************
	 Function: tmc262_initMotorDrivers()
	 Parameter: ---

	 Returns: ---

	 Purpose: Initialization of TMC262 and its variables
********************************************************************/
void tmc262_initMotorDrivers(void)
{
	// Initialize data structs
	// Parameter "non cool"
	StallGuardConfig.FilterEnable         = 1;
	StallGuardConfig.StallGuardThreshold  = 5;
#if defined(DEVTYPE_TMC43xx)
	StallGuardConfig.CurrentScale         = 31;
#else
	StallGuardConfig.CurrentScale         = 5; //16;
#endif

	DriverConfig.SlopeHighSide         = 3;
	DriverConfig.SlopeLowSide          = 3;
	DriverConfig.ProtectionDisable     = 0;
	DriverConfig.ProtectionTimer       = 0;
#if defined(DEVTYPE_TMC43xx)
	DriverConfig.StepDirectionDisable  = 1;
#else
	DriverConfig.StepDirectionDisable  = 0;
#endif

	DriverConfig.VSenseScale     = 1;
	DriverConfig.ReadBackSelect  = TMC262_RB_SMART_ENERGY;

	SmartEnergyControl.SmartIMin           = 0;
	SmartEnergyControl.SmartDownStep       = 0;
	SmartEnergyControl.SmartStallLevelMax  = 0;
	SmartEnergyControl.SmartUpStep         = 0;
	SmartEnergyControl.SmartStallLevelMin  = 0;

	StepDirConfig.Intpol  = 0;
	StepDirConfig.DEdge   = 0;
	StepDirConfig.MRes    = 0;

	ChopperConfig.BlankTime        = 2;
	ChopperConfig.ChopperMode      = 0;
	ChopperConfig.RandomTOff       = 0;
	ChopperConfig.HysteresisDecay  = 0;
	ChopperConfig.HysteresisEnd    = 2;
	ChopperConfig.HysteresisStart  = 3;
	ChopperConfig.TOff             = 5;
	ChopperConfig.DisableFlag      = FALSE;

	// Send initial values to TMC262
	WriteSmartEnergyControl();
	WriteStallGuardConfig();
	WriteDriverConfig();
	WriteStepDirConfig();
	WriteChopperConfig();
}

void tmc262_setStepDirMStepRes(uint8 MicrostepResolution)
{
	StepDirConfig.MRes = MicrostepResolution;
	if(MicrostepResolution != 4)
		StepDirConfig.Intpol = 0;
	WriteStepDirConfig();
}

void tmc262_setStepDirInterpolation(uint8 Interpolation)
{
	StepDirConfig.Intpol = Interpolation;
	if(Interpolation)
		StepDirConfig.MRes = 4;
	WriteStepDirConfig();
}

void tmc262_setStepDirDoubleEdge(uint8 DoubleEdge)
{
	StepDirConfig.DEdge = DoubleEdge;
	WriteStepDirConfig();
}

uint8 tmc262_getStepDirMStepRes()
{
	return StepDirConfig.MRes;
}

uint8 tmc262_getStepDirInterpolation()
{
	return StepDirConfig.Intpol;
}

uint8 tmc262_getStepDirDoubleEdge()
{
	return StepDirConfig.DEdge;
}


void tmc262_setChopperBlankTime(uint8 BlankTime)
{
	ChopperConfig.BlankTime = BlankTime;
	WriteChopperConfig();
}

void tmc262_setChopperMode(uint8 Mode)
{
	ChopperConfig.ChopperMode = Mode;
	WriteChopperConfig();
}

void tmc262_setChopperRandomTOff(uint8 RandomTOff)
{
	ChopperConfig.RandomTOff = RandomTOff;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisDecay(uint8 HysteresisDecay)
{
	ChopperConfig.HysteresisDecay = HysteresisDecay;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisEnd(uint8 HysteresisEnd)
{
	ChopperConfig.HysteresisEnd = HysteresisEnd;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisStart(uint8 HysteresisStart)
{
	ChopperConfig.HysteresisStart = HysteresisStart;
	WriteChopperConfig();
}

void tmc262_setChopperTOff(uint8 TOff)
{
	ChopperConfig.TOff = TOff;
	WriteChopperConfig();
}

uint8 tmc262_getChopperBlankTime()
{
	return ChopperConfig.BlankTime;
}

uint8 tmc262_getChopperMode()
{
	return ChopperConfig.ChopperMode;
}

uint8 tmc262_getChopperRandomTOff()
{
	return ChopperConfig.RandomTOff;
}

uint8 tmc262_getChopperHysteresisDecay()
{
	return ChopperConfig.HysteresisDecay;
}

uint8 tmc262_getChopperHysteresisEnd()
{
	return ChopperConfig.HysteresisEnd;
}

uint8 tmc262_getChopperHysteresisStart()
{
	return ChopperConfig.HysteresisStart;
}

uint8 tmc262_getChopperTOff()
{
	return ChopperConfig.TOff;
}


void tmc262_setSmartEnergyIMin(uint8 SmartIMin)
{
	SmartEnergyControl.SmartIMin = SmartIMin;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyDownStep(uint8 SmartDownStep)
{
	SmartEnergyControl.SmartDownStep = SmartDownStep;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyStallLevelMax(uint8 StallLevelMax)
{
	SmartEnergyControl.SmartStallLevelMax = StallLevelMax;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyUpStep(uint8 SmartUpStep)
{
	SmartEnergyControl.SmartUpStep = SmartUpStep;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyStallLevelMin(uint8 StallLevelMin)
{
	SmartEnergyControl.SmartStallLevelMin = StallLevelMin;
	WriteSmartEnergyControl();
}

uint8 tmc262_getSmartEnergyIMin()
{
	return SmartEnergyControl.SmartIMin;
}

uint8 tmc262_getSmartEnergyDownStep()
{
	return SmartEnergyControl.SmartDownStep;
}

uint8 tmc262_getSmartEnergyStallLevelMax()
{
	return SmartEnergyControl.SmartStallLevelMax;
}

uint8 tmc262_getSmartEnergyUpStep()
{
	return SmartEnergyControl.SmartUpStep;
}

uint8 tmc262_getSmartEnergyStallLevelMin()
{
	return SmartEnergyControl.SmartStallLevelMin;
}


void tmc262_setStallGuardFilter(uint8 Enable)
{
	StallGuardConfig.FilterEnable = Enable;
	WriteStallGuardConfig();
}

void tmc262_setStallGuardThreshold(int8 Threshold)
{
	StallGuardConfig.StallGuardThreshold = Threshold;
	WriteStallGuardConfig();
}

void tmc262_setStallGuardCurrentScale(uint8 CurrentScale)
{
	StallGuardConfig.CurrentScale = CurrentScale;
	WriteStallGuardConfig();
}

uint8 tmc262_getStallGuardFilter()
{
	return StallGuardConfig.FilterEnable;
}

int8 tmc262_getStallGuardThreshold()
{
	return StallGuardConfig.StallGuardThreshold;
}

uint8 tmc262_getStallGuardCurrentScale()
{
	return StallGuardConfig.CurrentScale;
}


void tmc262_setDriverSlopeHighSide(uint8 SlopeHighSide)
{
	DriverConfig.SlopeHighSide = SlopeHighSide;
	WriteDriverConfig();
}

void tmc262_setDriverSlopeLowSide(uint8 SlopeLowSide)
{
	DriverConfig.SlopeLowSide = SlopeLowSide;
	WriteDriverConfig();
}

void tmc262_setDriverDisableProtection(uint8 DisableProtection)
{
	DriverConfig.ProtectionDisable = DisableProtection;
	WriteDriverConfig();
}

void tmc262_setDriverProtectionTimer(uint8 ProtectionTimer)
{
	DriverConfig.ProtectionTimer = ProtectionTimer;
	WriteDriverConfig();
}

void tmc262_setDriverStepDirectionOff(uint8 SDOff)
{
	DriverConfig.StepDirectionDisable = SDOff;
	WriteDriverConfig();
}

void tmc262_setDriverVSenseScale(uint8 Scale)
{
	DriverConfig.VSenseScale = Scale;
	WriteDriverConfig();
}

void tmc262_setDriverReadSelect(uint8 ReadSelect)
{
	DriverConfig.ReadBackSelect = ReadSelect;
	WriteDriverConfig();
}

uint8 tmc262_getDriverSlopeHighSide()
{
	return DriverConfig.SlopeHighSide;
}

uint8 tmc262_getDriverSlopeLowSide()
{
	return DriverConfig.SlopeLowSide;
}

uint8 tmc262_getDriverDisableProtection()
{
	return DriverConfig.ProtectionDisable;
}

uint8 tmc262_getDriverProtectionTimer()
{
	return DriverConfig.ProtectionTimer;
}

uint8 tmc262_getDriverStepDirectionOff()
{
	return DriverConfig.StepDirectionDisable;
}

uint8 tmc262_getDriverVSenseScale()
{
	return DriverConfig.VSenseScale;
}

uint8 tmc262_getDriverReadSelect()
{
	return DriverConfig.ReadBackSelect;
}


/*******************************************************************
	 Function: tmc262_readState()
	 Parameter: Phases: Pointer to state variable of phase bits
	            MStep: Pointer to variable for microstep-position
	            StallGuard: Pointer to variable for stallGuard
	            SmartEnergy: Pointer to variable for SmartEnergy
	            Flags: Pointer to variable for error-flags

	 Returns: ---

	 Purpose: Read out TMC262-state. Depending on RDSEL, the read back
	          values are extracted accordingly from the SPI telegram.
	          NULL can be used for values that are not required.
********************************************************************/
void tmc262_readState(uint8 *Phases, uint8 *MStep, uint32 *StallGuard, uint8 *SmartEnergy, uint8 *Flags)
{
	// Alternately use all datagram types of the TMC26x to read out the states.
	// This ensures that all registers are always written with the correct values
	// (if there should be a TMC26x reset between them).
	switch(ReadBackDatagram)
	{
	case RB_CHOPPER:
		WriteChopperConfig();
		ReadBackDatagram = RB_DRIVER;
		break;
	case RB_DRIVER:
		WriteDriverConfig();
		ReadBackDatagram = RB_SMART_ENERGY;
		break;
	case RB_SMART_ENERGY:
		WriteSmartEnergyControl();
		ReadBackDatagram = RB_STALL_GUARD;
		break;
	case RB_STALL_GUARD:
		WriteStallGuardConfig();
		ReadBackDatagram = RB_STEP_DIR;
		break;
	case RB_STEP_DIR:
		WriteStepDirConfig();
		ReadBackDatagram = RB_CHOPPER;
		break;
	default:
		ReadBackDatagram = RB_CHOPPER;
		break;
	}

	// Decode read values depending on selected type
	switch(DriverConfig.ReadBackSelect)
	{
	case TMC262_RB_MSTEP:
		if(Phases != NULL)
			*Phases = SPIReadInt >> 18;
		if(MStep != NULL)
			*MStep = SPIReadInt >> 10;
		break;
	case TMC262_RB_STALL_GUARD:
		if(StallGuard != NULL)
			*StallGuard=SPIReadInt >> 10;
		break;
	case TMC262_RB_SMART_ENERGY:
		if(StallGuard != NULL)
		{
			*StallGuard = SPIReadInt >> 15;
			*StallGuard <<= 5;
		}
		if(SmartEnergy != NULL)
		{
			*SmartEnergy = (SPIReadInt >> 10) & 0x1F;
		}
		break;
	}

	if(Flags != NULL)
		*Flags = SPIReadInt & 0xFF;
}


#if defined(DEVTYPE_TMC43xx)
/*******************************************************************
	 Function: tmc262_readStateNoCoverData()
	 Parameter: Phases: Pointer to state variable of phase bits
	            MStep: Pointer to variable for microstep-position
	            StallGuard: Pointer to variable for stallGuard
	            SmartEnergy: Pointer to variable for SmartEnergy
	            Flags: Pointer to variable for error-flags

	 Returns: ---


	 Purpose: Read out TMC262-state, without sending a cover datagram
	          and thus without disturbing SPI communication.
	          Depending on RDSEL, the read back
	          values are extracted accordingly from the SPI telegram.
	          NULL can be used for values that are not required.
********************************************************************/
void tmc262_readStateNoCoverData(uint8 *Phases, uint16 *MStep, uint32 *StallGuard, uint8 *SmartEnergy, uint8 *Flags)
{
	uint32 SPIReadData;

	SPIReadData = tmc43xx_readInt(TMC4361A_POLLING_STATUS_RD);

	// Decode read values depending on selected type
	switch(DriverConfig.ReadBackSelect)
	{
	case TMC262_RB_MSTEP:
		if(Phases != NULL)
			*Phases = SPIReadData >> 18;
		if(MStep != NULL)
			*MStep = (SPIReadData >> 10) & 0x3FF;
		break;
	case TMC262_RB_STALL_GUARD:
		if(StallGuard != NULL)
			*StallGuard = SPIReadData >> 10;
		break;
	case TMC262_RB_SMART_ENERGY:
		if(StallGuard != NULL)
		{
			*StallGuard = SPIReadData >> 15;
			*StallGuard <<= 5;
		}
		if(SmartEnergy != NULL)
		{
			*SmartEnergy = (SPIReadData >> 10) & 0x1F;
		}
		break;
	}

	if(Flags != NULL)
		*Flags = SPIReadData & 0xFF;
}
#endif



/*******************************************************************
	 Function: tmc262_disable()
	 Parameter: ---

	 Returns: ---

	 Purpose: Disconnect motor from current. This is done by setting
	          TOff-Time to 0 (altough the last TOff value which was set
	          with tmc262_setChopperTOff() is still available.
********************************************************************/
void tmc262_disable()
{
	if(!ChopperConfig.DisableFlag)
	{
		ChopperConfig.DisableFlag = TRUE;
		WriteChopperConfig();
	}
}


/*******************************************************************
	 Function: Enable262()
	 Parameter: ---

	 Returns: ---

	 Purpose: turn on motor. This is done by setting the TOff-Time
	          with the value which was written the last time by
	          tmc262_setChopperTOff()
********************************************************************/
void tmc262_enable()
{
	if(ChopperConfig.DisableFlag)
	{
		ChopperConfig.DisableFlag = FALSE;
		WriteChopperConfig();
	}
}

void tmc262_getSPIData(uint8 Index, int *Data)
{
	switch(Index)
	{
	case 0:
		*Data = SPIReadInt;
		break;
	case 1:
		*Data = SPIStepDirConf;
		break;
	case 2:
		*Data = SPIChopperConf;
		break;
	case 3:
		*Data = SPISmartConf;
		break;
	case 4:
		*Data = SPISGConf;
		break;
	case 5:
		*Data = SPIDriverConf;
		break;
	case 6:
		*Data = ChopperConfig.DisableFlag;
		break;
	}
}
