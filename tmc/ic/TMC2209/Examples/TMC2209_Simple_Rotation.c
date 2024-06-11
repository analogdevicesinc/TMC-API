/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2209_Simple_Rotation.h"

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void initAllMotors(uint16_t icID)
{
    tmc2209_writeRegister(icID, TMC2209_GCONF, 0x00000040);
    tmc2209_writeRegister(icID, TMC2209_IHOLD_IRUN, 0x00071703);
    tmc2209_writeRegister(icID, TMC2209_TPOWERDOWN, 0x00000014);
    tmc2209_writeRegister(icID, TMC2209_CHOPCONF, 0x10000053);
    tmc2209_writeRegister(icID, TMC2209_PWMCONF, 0xC10D0024);

    // Generate step pulse (S/D) externally via the connected microcontroller.
}
