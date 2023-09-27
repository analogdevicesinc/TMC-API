/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC262_H_
#define TMC_IC_TMC262_H_

#include "tmc/helpers/API_Header.h"
#include "TMC262_Register.h"

#define TMC262_RB_MSTEP         0
#define TMC262_RB_STALL_GUARD   1
#define TMC262_RB_SMART_ENERGY  2
#define TMC262_RB_ENCODER       3

#define TMC262_FLAG_STST  0x80
#define TMC262_FLAG_OLB   0x40
#define TMC262_FLAG_OLA   0x20
#define TMC262_FLAG_S2GB  0x10
#define TMC262_FLAG_S2GA  0x08
#define TMC262_FLAG_OTPW  0x04
#define TMC262_FLAG_OT    0x02
#define TMC262_FLAG_SG    0x01

// Access functions for TMC262
void tmc262_initMotorDrivers(void);
void tmc262_setStepDirMStepRes(uint8_t MicrostepResolution);
void tmc262_setStepDirInterpolation(uint8_t Interpolation);
void tmc262_setStepDirDoubleEdge(uint8_t DoubleEdge);
uint8_t tmc262_getStepDirMStepRes();
uint8_t tmc262_getStepDirInterpolation();
uint8_t tmc262_getStepDirDoubleEdge();

void tmc262_setChopperBlankTime(uint8_t BlankTime);
void tmc262_setChopperMode(uint8_t Mode);
void tmc262_setChopperRandomTOff(uint8_t RandomTOff);
void tmc262_setChopperHysteresisDecay(uint8_t HysteresisDecay);
void tmc262_setChopperHysteresisEnd(uint8_t HysteresisEnd);
void tmc262_setChopperHysteresisStart(uint8_t HysteresisStart);
void tmc262_setChopperTOff(uint8_t TOff);
uint8_t tmc262_getChopperBlankTime();
uint8_t tmc262_getChopperMode();
uint8_t tmc262_getChopperRandomTOff();
uint8_t tmc262_getChopperHysteresisDecay();
uint8_t tmc262_getChopperHysteresisEnd();
uint8_t tmc262_getChopperHysteresisStart();
uint8_t tmc262_getChopperTOff();

void tmc262_setSmartEnergyIMin(uint8_t SmartIMin);
void tmc262_setSmartEnergyDownStep(uint8_t SmartDownStep);
void tmc262_setSmartEnergyStallLevelMax(uint8_t StallLevelMax);
void tmc262_setSmartEnergyUpStep(uint8_t SmartUpStep);
void tmc262_setSmartEnergyStallLevelMin(uint8_t StallLevelMin);
uint8_t tmc262_getSmartEnergyIMin();
uint8_t tmc262_getSmartEnergyDownStep();
uint8_t tmc262_getSmartEnergyStallLevelMax();
uint8_t tmc262_getSmartEnergyUpStep();
uint8_t tmc262_getSmartEnergyStallLevelMin();

void tmc262_setStallGuardFilter(uint8_t Enable);
void tmc262_setStallGuardThreshold(signed char Threshold);
void tmc262_setStallGuardCurrentScale(uint8_t CurrentScale);
uint8_t tmc262_getStallGuardFilter();
signed char tmc262_getStallGuardThreshold();
uint8_t tmc262_getStallGuardCurrentScale();

void tmc262_setDriverSlopeHighSide(uint8_t SlopeHighSide);
void tmc262_setDriverSlopeLowSide(uint8_t SlopeLowSide);
void tmc262_setDriverDisableProtection(uint8_t DisableProtection);
void tmc262_setDriverProtectionTimer(uint8_t ProtectionTimer);
void tmc262_setDriverStepDirectionOff(uint8_t SDOff);
void tmc262_setDriverVSenseScale(uint8_t Scale);
void tmc262_setDriverReadSelect(uint8_t ReadSelect);
uint8_t tmc262_getDriverSlopeHighSide();
uint8_t tmc262_getDriverSlopeLowSide();
uint8_t tmc262_getDriverDisableProtection();
uint8_t tmc262_getDriverProtectionTimer();
uint8_t tmc262_getDriverStepDirectionOff();
uint8_t tmc262_getDriverVSenseScale();
uint8_t tmc262_getDriverReadSelect();

void tmc262_disable();
void tmc262_enable();

void tmc262_readState(uint8_t *Phases, uint8_t *MStep, uint32_t *StallGuard, uint8_t *SmartEnergy, uint8_t *Flags);

void tmc262_getSPIData(uint8_t Index, int32_t *Data);

#endif /* TMC_IC_TMC262_H_ */
