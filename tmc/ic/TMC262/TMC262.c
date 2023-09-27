/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC262.h"

// Data structs for TMC262 Shadowregister
typedef struct
{
	uint8_t Intpol;
	uint8_t DEdge;
	uint8_t MRes;
} TStepDirConfig;

typedef struct
{
	uint8_t BlankTime;
	uint8_t ChopperMode;
	uint8_t HysteresisDecay;
	uint8_t RandomTOff;
	uint8_t HysteresisEnd;
	uint8_t HysteresisStart;
	uint8_t TOff;
	uint8_t DisableFlag;
} TChopperConfig;

typedef struct
{
	uint8_t SmartIMin;
	uint8_t SmartDownStep;
	uint8_t SmartStallLevelMax;
	uint8_t SmartUpStep;
	uint8_t SmartStallLevelMin;
} TSmartEnergyControl;

typedef struct
{
	uint8_t FilterEnable;
	int8_t StallGuardThreshold;
	uint8_t CurrentScale;
} TStallGuardConfig;


typedef struct
{
	uint8_t SlopeHighSide;
	uint8_t SlopeLowSide;
	uint8_t ProtectionDisable;
	uint8_t ProtectionTimer;
	uint8_t StepDirectionDisable;
	uint8_t VSenseScale;
	uint8_t ReadBackSelect;
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
static uint32_t SPIReadInt;
static uint32_t SPIWriteInt;

static uint32_t SPIStepDirConf;
static uint32_t SPIChopperConf;
static uint32_t SPISmartConf;
static uint32_t SPISGConf;
static uint32_t SPIDriverConf;

// Choose the configuration that suits your board // todo API 2: configuration should be chosen outside API e.g. in TMC-EvalSystem
#define DEVTYPE_TMC428 // Direct SPI communication if TMC262 is connected to the processor
//#define DEVTYPE_TMC43xx // Communication is forwarded to TMC262 by TMC43xx with "cover datagrams"

#if defined(DEVTYPE_TMC428)
	// => SPI wrapper
	extern uint8_t tmc5130_spi_readWrite(uint8_t data, uint8_t lastTransfer);
	// <= SPI wrapper
#elif defined(DEVTYPE_TMC43xx)
	#include "tmc/ic/TMC43xx/TMC4361A_Register.h"
	// => Cover data wrapper
	extern int32_t tmc43xx_readInt(uint8_t address);
	extern int32_t tmc43xx_writeInt(uint8_t address, uint32_t data);
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
static void ReadWrite262(uint32_t *ReadInt, uint32_t WriteInt)
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
	SPIWriteInt |= ((uint32_t) ChopperConfig.BlankTime) << 15;
	if(ChopperConfig.ChopperMode)
		SPIWriteInt |= BIT14;
	if(ChopperConfig.RandomTOff)
		SPIWriteInt |= BIT13;
	SPIWriteInt |= ((uint32_t) ChopperConfig.HysteresisDecay) << 11;
	SPIWriteInt |= ((uint32_t) ChopperConfig.HysteresisEnd) << 7;
	SPIWriteInt |= ((uint32_t) ChopperConfig.HysteresisStart) << 4;
	if(!ChopperConfig.DisableFlag)
		SPIWriteInt |= ((uint32_t) ChopperConfig.TOff);  // wenn DisableFlag gesetzt wird 0 gesendet

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
	SPIWriteInt |= ((uint32_t) SmartEnergyControl.SmartIMin) << 15;
	SPIWriteInt |= ((uint32_t) SmartEnergyControl.SmartDownStep)  << 13;
	SPIWriteInt |= ((uint32_t) SmartEnergyControl.SmartStallLevelMax) << 8;
	SPIWriteInt |= ((uint32_t) SmartEnergyControl.SmartUpStep) << 5;
	SPIWriteInt |= ((uint32_t) SmartEnergyControl.SmartStallLevelMin);

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
	SPIWriteInt |= ((uint32_t) StallGuardConfig.StallGuardThreshold & 0x7F) << 8;
	SPIWriteInt |= ((uint32_t) StallGuardConfig.CurrentScale);

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
	SPIWriteInt |= ((uint32_t) DriverConfig.SlopeHighSide) << 14;
	SPIWriteInt |= ((uint32_t) DriverConfig.SlopeLowSide) << 12;
	if(DriverConfig.ProtectionDisable == 1)
		SPIWriteInt |= BIT10;
	SPIWriteInt |= ((uint32_t) DriverConfig.ProtectionTimer) << 8;
	if(DriverConfig.StepDirectionDisable == 1)
		SPIWriteInt |= BIT7;
	if(DriverConfig.VSenseScale == 1)
		SPIWriteInt |= BIT6;
	SPIWriteInt |= ((uint32_t) DriverConfig.ReadBackSelect) << 4;

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

void tmc262_setStepDirMStepRes(uint8_t MicrostepResolution)
{
	StepDirConfig.MRes = MicrostepResolution;
	if(MicrostepResolution != 4)
		StepDirConfig.Intpol = 0;
	WriteStepDirConfig();
}

void tmc262_setStepDirInterpolation(uint8_t Interpolation)
{
	StepDirConfig.Intpol = Interpolation;
	if(Interpolation)
		StepDirConfig.MRes = 4;
	WriteStepDirConfig();
}

void tmc262_setStepDirDoubleEdge(uint8_t DoubleEdge)
{
	StepDirConfig.DEdge = DoubleEdge;
	WriteStepDirConfig();
}

uint8_t tmc262_getStepDirMStepRes()
{
	return StepDirConfig.MRes;
}

uint8_t tmc262_getStepDirInterpolation()
{
	return StepDirConfig.Intpol;
}

uint8_t tmc262_getStepDirDoubleEdge()
{
	return StepDirConfig.DEdge;
}


void tmc262_setChopperBlankTime(uint8_t BlankTime)
{
	ChopperConfig.BlankTime = BlankTime;
	WriteChopperConfig();
}

void tmc262_setChopperMode(uint8_t Mode)
{
	ChopperConfig.ChopperMode = Mode;
	WriteChopperConfig();
}

void tmc262_setChopperRandomTOff(uint8_t RandomTOff)
{
	ChopperConfig.RandomTOff = RandomTOff;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisDecay(uint8_t HysteresisDecay)
{
	ChopperConfig.HysteresisDecay = HysteresisDecay;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisEnd(uint8_t HysteresisEnd)
{
	ChopperConfig.HysteresisEnd = HysteresisEnd;
	WriteChopperConfig();
}

void tmc262_setChopperHysteresisStart(uint8_t HysteresisStart)
{
	ChopperConfig.HysteresisStart = HysteresisStart;
	WriteChopperConfig();
}

void tmc262_setChopperTOff(uint8_t TOff)
{
	ChopperConfig.TOff = TOff;
	WriteChopperConfig();
}

uint8_t tmc262_getChopperBlankTime()
{
	return ChopperConfig.BlankTime;
}

uint8_t tmc262_getChopperMode()
{
	return ChopperConfig.ChopperMode;
}

uint8_t tmc262_getChopperRandomTOff()
{
	return ChopperConfig.RandomTOff;
}

uint8_t tmc262_getChopperHysteresisDecay()
{
	return ChopperConfig.HysteresisDecay;
}

uint8_t tmc262_getChopperHysteresisEnd()
{
	return ChopperConfig.HysteresisEnd;
}

uint8_t tmc262_getChopperHysteresisStart()
{
	return ChopperConfig.HysteresisStart;
}

uint8_t tmc262_getChopperTOff()
{
	return ChopperConfig.TOff;
}


void tmc262_setSmartEnergyIMin(uint8_t SmartIMin)
{
	SmartEnergyControl.SmartIMin = SmartIMin;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyDownStep(uint8_t SmartDownStep)
{
	SmartEnergyControl.SmartDownStep = SmartDownStep;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyStallLevelMax(uint8_t StallLevelMax)
{
	SmartEnergyControl.SmartStallLevelMax = StallLevelMax;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyUpStep(uint8_t SmartUpStep)
{
	SmartEnergyControl.SmartUpStep = SmartUpStep;
	WriteSmartEnergyControl();
}

void tmc262_setSmartEnergyStallLevelMin(uint8_t StallLevelMin)
{
	SmartEnergyControl.SmartStallLevelMin = StallLevelMin;
	WriteSmartEnergyControl();
}

uint8_t tmc262_getSmartEnergyIMin()
{
	return SmartEnergyControl.SmartIMin;
}

uint8_t tmc262_getSmartEnergyDownStep()
{
	return SmartEnergyControl.SmartDownStep;
}

uint8_t tmc262_getSmartEnergyStallLevelMax()
{
	return SmartEnergyControl.SmartStallLevelMax;
}

uint8_t tmc262_getSmartEnergyUpStep()
{
	return SmartEnergyControl.SmartUpStep;
}

uint8_t tmc262_getSmartEnergyStallLevelMin()
{
	return SmartEnergyControl.SmartStallLevelMin;
}


void tmc262_setStallGuardFilter(uint8_t Enable)
{
	StallGuardConfig.FilterEnable = Enable;
	WriteStallGuardConfig();
}

void tmc262_setStallGuardThreshold(int8_t Threshold)
{
	StallGuardConfig.StallGuardThreshold = Threshold;
	WriteStallGuardConfig();
}

void tmc262_setStallGuardCurrentScale(uint8_t CurrentScale)
{
	StallGuardConfig.CurrentScale = CurrentScale;
	WriteStallGuardConfig();
}

uint8_t tmc262_getStallGuardFilter()
{
	return StallGuardConfig.FilterEnable;
}

int8_t tmc262_getStallGuardThreshold()
{
	return StallGuardConfig.StallGuardThreshold;
}

uint8_t tmc262_getStallGuardCurrentScale()
{
	return StallGuardConfig.CurrentScale;
}


void tmc262_setDriverSlopeHighSide(uint8_t SlopeHighSide)
{
	DriverConfig.SlopeHighSide = SlopeHighSide;
	WriteDriverConfig();
}

void tmc262_setDriverSlopeLowSide(uint8_t SlopeLowSide)
{
	DriverConfig.SlopeLowSide = SlopeLowSide;
	WriteDriverConfig();
}

void tmc262_setDriverDisableProtection(uint8_t DisableProtection)
{
	DriverConfig.ProtectionDisable = DisableProtection;
	WriteDriverConfig();
}

void tmc262_setDriverProtectionTimer(uint8_t ProtectionTimer)
{
	DriverConfig.ProtectionTimer = ProtectionTimer;
	WriteDriverConfig();
}

void tmc262_setDriverStepDirectionOff(uint8_t SDOff)
{
	DriverConfig.StepDirectionDisable = SDOff;
	WriteDriverConfig();
}

void tmc262_setDriverVSenseScale(uint8_t Scale)
{
	DriverConfig.VSenseScale = Scale;
	WriteDriverConfig();
}

void tmc262_setDriverReadSelect(uint8_t ReadSelect)
{
	DriverConfig.ReadBackSelect = ReadSelect;
	WriteDriverConfig();
}

uint8_t tmc262_getDriverSlopeHighSide()
{
	return DriverConfig.SlopeHighSide;
}

uint8_t tmc262_getDriverSlopeLowSide()
{
	return DriverConfig.SlopeLowSide;
}

uint8_t tmc262_getDriverDisableProtection()
{
	return DriverConfig.ProtectionDisable;
}

uint8_t tmc262_getDriverProtectionTimer()
{
	return DriverConfig.ProtectionTimer;
}

uint8_t tmc262_getDriverStepDirectionOff()
{
	return DriverConfig.StepDirectionDisable;
}

uint8_t tmc262_getDriverVSenseScale()
{
	return DriverConfig.VSenseScale;
}

uint8_t tmc262_getDriverReadSelect()
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
void tmc262_readState(uint8_t *Phases, uint8_t *MStep, uint32_t *StallGuard, uint8_t *SmartEnergy, uint8_t *Flags)
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
void tmc262_readStateNoCoverData(uint8_t *Phases, uint16_t *MStep, uint32_t *StallGuard, uint8_t *SmartEnergy, uint8_t *Flags)
{
	uint32_t SPIReadData;

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

void tmc262_getSPIData(uint8_t Index, int32_t *Data)
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
