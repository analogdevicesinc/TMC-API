/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5271_Simple_Rotation.h"

/*
 * Configures the registers with the right settings that are needed for rotating the motor.
 * E.g Enabling driver, setting IRUN current etc.
 */
void initMotor(uint16_t icID)
{
  // Set IREF_R2 and IREF_R3 to High for setting the REF resistor to 10k.
  // Run Current = 0.2A rms
  // Hold Current = 0.14A rms
  // Chopper Mode = SpreadCycle

  // Disable motor driver
  tmc5271_writeRegister(icID, TMC5271_GCONF, 0x10024002); // writing value 0x10020002 = 268582914 = 0.0 to address 0 = 0x00(GCONF)

  tmc5271_writeRegister(icID, TMC5271_DRV_CONF, 0x0000000C); // writing value 0x0000000C = 12 = 0.0 to address 1 = 0x05(DRV_CONF)
  tmc5271_writeRegister(icID, TMC5271_GLOBAL_SCALER, 0x0000FAFA); // writing value 0x0000FAFA = 64250 = 0.0 to address 2 = 0x06(GLOBAL_SCALER)
  tmc5271_writeRegister(icID, TMC5271_IHOLD_IRUN, 0x04011F0A);  // writing value 0x04011F0A = 67182346 = 0.0 to address 3 = 0x12(IHOLD_IRUN)
  tmc5271_writeRegister(icID, TMC5271_CHOPCONF, 0x10410153);  // writing value 0x10410153 = 272695635 = 0.0 to address 4 = 0x38(CHOPCONF)
  tmc5271_writeRegister(icID, TMC5271_AMAX, 51200);  // writing value to address 5 = 0x20(AMAX)

  // Enable motor driver
  tmc5271_writeRegister(icID, TMC5271_GCONF, 0x10020002);  // writing value 0x10020002 = 268566530 = 0.0 to address 0 = 0x00(GCONF)
}
