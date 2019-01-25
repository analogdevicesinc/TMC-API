/*
 * TMC262.h
 *
 *  Created on: 27.01.2017
 *      Author: BS
 *    Based on: TMC262-K20.h (12.01.2009 OK)
 */

#ifndef TMC_IC_TMC262_H_
#define TMC_IC_TMC262_H_

#include "../../helpers/API_Header.h"
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
void tmc262_setStepDirMStepRes(uint8 MicrostepResolution);
void tmc262_setStepDirInterpolation(uint8 Interpolation);
void tmc262_setStepDirDoubleEdge(uint8 DoubleEdge);
uint8 tmc262_getStepDirMStepRes();
uint8 tmc262_getStepDirInterpolation();
uint8 tmc262_getStepDirDoubleEdge();

void tmc262_setChopperBlankTime(uint8 BlankTime);
void tmc262_setChopperMode(uint8 Mode);
void tmc262_setChopperRandomTOff(uint8 RandomTOff);
void tmc262_setChopperHysteresisDecay(uint8 HysteresisDecay);
void tmc262_setChopperHysteresisEnd(uint8 HysteresisEnd);
void tmc262_setChopperHysteresisStart(uint8 HysteresisStart);
void tmc262_setChopperTOff(uint8 TOff);
uint8 tmc262_getChopperBlankTime();
uint8 tmc262_getChopperMode();
uint8 tmc262_getChopperRandomTOff();
uint8 tmc262_getChopperHysteresisDecay();
uint8 tmc262_getChopperHysteresisEnd();
uint8 tmc262_getChopperHysteresisStart();
uint8 tmc262_getChopperTOff();

void tmc262_setSmartEnergyIMin(uint8 SmartIMin);
void tmc262_setSmartEnergyDownStep(uint8 SmartDownStep);
void tmc262_setSmartEnergyStallLevelMax(uint8 StallLevelMax);
void tmc262_setSmartEnergyUpStep(uint8 SmartUpStep);
void tmc262_setSmartEnergyStallLevelMin(uint8 StallLevelMin);
uint8 tmc262_getSmartEnergyIMin();
uint8 tmc262_getSmartEnergyDownStep();
uint8 tmc262_getSmartEnergyStallLevelMax();
uint8 tmc262_getSmartEnergyUpStep();
uint8 tmc262_getSmartEnergyStallLevelMin();

void tmc262_setStallGuardFilter(uint8 Enable);
void tmc262_setStallGuardThreshold(signed char Threshold);
void tmc262_setStallGuardCurrentScale(uint8 CurrentScale);
uint8 tmc262_getStallGuardFilter();
signed char tmc262_getStallGuardThreshold();
uint8 tmc262_getStallGuardCurrentScale();

void tmc262_setDriverSlopeHighSide(uint8 SlopeHighSide);
void tmc262_setDriverSlopeLowSide(uint8 SlopeLowSide);
void tmc262_setDriverDisableProtection(uint8 DisableProtection);
void tmc262_setDriverProtectionTimer(uint8 ProtectionTimer);
void tmc262_setDriverStepDirectionOff(uint8 SDOff);
void tmc262_setDriverVSenseScale(uint8 Scale);
void tmc262_setDriverReadSelect(uint8 ReadSelect);
uint8 tmc262_getDriverSlopeHighSide();
uint8 tmc262_getDriverSlopeLowSide();
uint8 tmc262_getDriverDisableProtection();
uint8 tmc262_getDriverProtectionTimer();
uint8 tmc262_getDriverStepDirectionOff();
uint8 tmc262_getDriverVSenseScale();
uint8 tmc262_getDriverReadSelect();

void tmc262_disable();
void tmc262_enable();

void tmc262_readState(uint8 *Phases, uint8 *MStep, uint32 *StallGuard, uint8 *SmartEnergy, uint8 *Flags);

void tmc262_getSPIData(uint8 Index, int *Data);

#endif /* TMC_IC_TMC262_H_ */
