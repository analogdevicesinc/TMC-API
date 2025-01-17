/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5130_Simple_Rotation.h"

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void TMC5130initAllMotors(uint16_t icID)
{
    tmc5130_writeRegister(icID, TMC5130_GCONF, 0x00000000);  // Digital current scaling, SpreadCycle mode
    
    // IHOLD_IRUN: Set max current (IRUN = 31), and hold current (~30% of IRUN)
    tmc5130_writeRegister(icID, TMC5130_IHOLD_IRUN, 0x0000AF08); // Max run current, 30% hold current
    
    // CHOPCONF: VSENSE = 1, microstepping 1/16, TOFF = 3
    tmc5130_writeRegister(icID, TMC5130_CHOPCONF, 0x000101D5);
    
    // PWMCONF: Enable StealthChop, autoscale PWM, amplitude ~ moderate
    tmc5130_writeRegister(icID, TMC5130_PWMCONF, 0x000500C8);
    
    // AMAX: Setting the acceleration
    tmc5130_writeRegister(icID, TMC5130_AMAX, 10000);
}
