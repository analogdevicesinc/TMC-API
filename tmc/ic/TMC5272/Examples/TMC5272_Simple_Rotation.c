/*******************************************************************************
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC5272_Simple_Rotation.h"

/*
 * Configures the registers with the right settings that are needed for rotating both motors.
 * E.g Enabling drivers, setting IRUN current etc.
 */
void initAllMotors(uint16_t icID)
{
  // Set IREF_R2 and IREF_R3 to High for setting the REF resistor to 10k.
  // Run Current = 0.2A rms
  // Hold Current = 0.14A rms
  // Chopper Mode = SpreadCycle

  // For Motor 0 & 1
  tmc5272_writeRegister(icID, TMC5272_GCONF, 0x10024002);  // writing value 0x10024002 = 268582914 = 0.0 to address 0 = 0x00(GCONF)
  tmc5272_writeRegister(icID, TMC5272_DRV_CONF, 0x0000034D);  // writing value 0x0000034D = 845 = 0.0 to address 3 = 0x05(DRV_CONF)
  tmc5272_writeRegister(icID, TMC5272_GLOBAL_SCALER, 0xFBFBFBFB); 		// writing value 0xFBFBFBFB = 0 = 0.0 to address 4 = 0x06(GLOBAL_SCALER)

  // For Motor 0
  tmc5272_writeRegister(icID, TMC5272_IHOLD_IRUN(0), 0x04010F0A);  // writing value 0x04011F0A = 67182346 = 0.0 to address 10 = 0x12(M0_IHOLD_IRUN)
  tmc5272_writeRegister(icID, TMC5272_CHOPCONF(0), 0x10410153);  // writing value 0x10410153 = 272695635 = 0.0 to address 39 = 0x38(M0_CHOPCONF)
  tmc5272_writeRegister(icID, TMC5272_AMAX(0), 51200);  // writing value to address 21 = 0x20(M0_AMAX)

  // For Motor 1
  tmc5272_writeRegister(icID, TMC5272_IHOLD_IRUN(1), 0x04010F0A);  // writing value 0x04011F0A = 67182346 = 0.0 to address 10 = 0x12(M0_IHOLD_IRUN)
  tmc5272_writeRegister(icID, TMC5272_CHOPCONF(1), 0x10410153);  // writing value 0x10410153 = 272695635 = 0.0 to address 39 = 0x38(M0_CHOPCONF)
  tmc5272_writeRegister(icID, TMC5272_AMAX(1), 51200);  // writing value to address 21 = 0x20(M0_AMAX)

  // Enable Motor 0 & 1
  tmc5272_writeRegister(icID, TMC5272_GCONF, 0x00020002);  // writing value 0x00020002 = 131074 = 0.0 to address 0 = 0x00(GCONF)
}
