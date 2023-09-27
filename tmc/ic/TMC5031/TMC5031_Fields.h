/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC5031_FIELDS_H
#define TMC5031_FIELDS_H

#define TMC5031_POSCMP_ENABLE_MASK       0x08 // GCONF //
#define TMC5031_POSCMP_ENABLE_SHIFT      3 // min.: 0, max.: 1, default: 0
#define TMC5031_TEST_MODE_MASK           0x80 // GCONF //
#define TMC5031_TEST_MODE_SHIFT          7 // min.: 0, max.: 1, default: 0
#define TMC5031_SHAFT1_MASK              0x0100 // GCONF //
#define TMC5031_SHAFT1_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_SHAFT2_MASK              0x0200 // GCONF //
#define TMC5031_SHAFT2_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_LOCK_GCONF_MASK          0x0400 // GCONF //
#define TMC5031_LOCK_GCONF_SHIFT         10 // min.: 0, max.: 1, default: 0
#define TMC5031_RESET_MASK               0x01 // GSTAT //
#define TMC5031_RESET_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_DRV_ERR1_MASK            0x02 // GSTAT //
#define TMC5031_DRV_ERR1_SHIFT           1 // min.: 0, max.: 1, default: 0
//#define TMC5031_DRV_ERR1_MASK          0x04 // GSTAT //
//#define TMC5031_DRV_ERR1_SHIFT         2 // min.: 0, max.: 1, default: 0
#define TMC5031_UV_CP_MASK               0x08 // GSTAT //
#define TMC5031_UV_CP_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_TEST_SEL_MASK            0x0F // SLAVECONF // Selects the function of REFR2 in test mode: 0...4: T120, DAC1, VDDH1, DAC2, VDDH2; Attention: Not for user, set to 0 for normal operation!
#define TMC5031_TEST_SEL_SHIFT           0 // min.: 0, max.: 4, default: 0
#define TMC5031_DRV_ENN_MASK             0x80 // INPUT //
#define TMC5031_DRV_ENN_SHIFT            7 // min.: 0, max.: 1, default: 0
#define TMC5031_VERSION_MASK             0xFF000000 // INPUT // VERSION: 0x01=first version of the IC; Identical numbers mean full digital compatibility.
#define TMC5031_VERSION_SHIFT            24 // min.: 0, max.: 255, default: 0
#define TMC5031_X_COMPARE_MASK           0xFFFFFFFF // X_COMPARE // Position comparison register for motion controller position strobe. The Position pulse is available on output SWP_DIAG1.
#define TMC5031_X_COMPARE_SHIFT          0 // min.: 0, max.: 4294967295, default: 0
#define TMC5031_RAMPMODE_MASK            0x03 // RAMPMODE_M1 // 0: Positioning mode (using all A, D and V parameters) 1: Velocity mode to positive VMAX (using AMAX acceleration) 2: Velocity mode to negative VMAX (using AMAX acceleration) 3: Hold mode (velocity remains unchanged, unless stop event occurs)
#define TMC5031_RAMPMODE_SHIFT           0 // min.: 0, max.: 3, default: 0
#define TMC5031_XACTUAL_MASK             0xFFFFFFFF // XACTUAL_M1 // Actual motor position (signed) Hint: This value normally should only be modified, when homing the drive. In positioning mode, modifying the register content will start a motion.
#define TMC5031_XACTUAL_SHIFT            0 // min.: -2147483648, max.: 2147483647, default: 0
#define TMC5031_VACTUAL_MASK             0xFFFFFF // VACTUAL_M1 // Actual motor velocity from ramp generator (signed) The sign matches the motion direction. A negative sign means motion to lower XACTUAL.
#define TMC5031_VACTUAL_SHIFT            0 // min.: -8388607, max.: 8388607, default: 0
#define TMC5031_VSTART_MASK              0x03FFFF // VSTART_M1 // Motor start velocity (unsigned) Set VSTOP = VSTART!
#define TMC5031_VSTART_SHIFT             0 // min.: 0, max.: 262143, default: 0
#define TMC5031_A1_MASK                  0xFFFF // A1_M1 // First acceleration between VSTART and V1 (unsigned)
#define TMC5031_A1_SHIFT                 0 // min.: 0, max.: 65535, default: 0
#define TMC5031_V1__MASK                 0x0FFFFF // V1_M1 // First acceleration / deceleration phase threshold velocity (unsigned) 0: Disables A1 and D1 phase, use AMAX, DMAX only
#define TMC5031_V1__SHIFT                0 // min.: 0, max.: 1048575, default: 0
#define TMC5031_AMAX_MASK                0xFFFF // AMAX_M1 // Second acceleration between V1 and VMAX (unsigned) This is the acceleration and deceleration value for velocity mode.
#define TMC5031_AMAX_SHIFT               0 // min.: 0, max.: 65535, default: 0
#define TMC5031_VMAX_MASK                0x7FFFFF // VMAX_M1 // Motion ramp target velocity (for positioning ensure VMAX = VSTART) (unsigned) This is the target velocity in velocity mode. It can be changed any time during a motion.
#define TMC5031_VMAX_SHIFT               0 // min.: 0, max.: 8388096, default: 0
#define TMC5031_DMAX_MASK                0xFFFF // DMAX_M1 // Deceleration between VMAX and V1 (unsigned)
#define TMC5031_DMAX_SHIFT               0 // min.: 0, max.: 65535, default: 0
#define TMC5031_D1_MASK                  0xFFFF // D1_M1 // Deceleration between V1 and VSTOP (unsigned) Attention: Do not set 0 in positioning mode, even if V1=0!
#define TMC5031_D1_SHIFT                 0 // min.: 1, max.: 65535, default: 0
#define TMC5031_VSTOP_MASK               0x03FFFF // VSTOP_M1 // Motor stop velocity (unsigned) Attention: Set VSTOP = VSTART! Attention: Do not set 0 in positioning mode, minimum 10 recommend!
#define TMC5031_VSTOP_SHIFT              0 // min.: 1, max.: 262143, default: 0
#define TMC5031_TZEROWAIT_MASK           0xFFFF // TZEROWAIT_M1 // Defines the waiting time after ramping down to zero velocity before next movement or direction inversion can start. Time range is about 0 to 2 seconds. This setting avoids excess acceleration e.g. from VSTOP to -VSTART.
#define TMC5031_TZEROWAIT_SHIFT          0 // min.: 0, max.: 65535, default: 0
#define TMC5031_XTARGET_MASK             0xFFFFFFFF // XTARGET_M1 // Target position for ramp mode (signed). Write a new target position to this register in order to activate the ramp generator positioning in RAMPMODE=0. Initialize all velocity, acceleration and deceleration parameters before. Hint: The position is allowed to wrap around, thus, XTARGET value optionally can be treated as an unsigned number. Hint: The maximum possible displacement is +/-((2^31)-1). Hint: When increasing V1, D1 or DMAX during a motion, rewrite XTARGET afterwards in order to trigger a second acceleration phase, if desired.
#define TMC5031_XTARGET_SHIFT            0 // min.: -2147483648, max.: 2147483647, default: 0
#define TMC5031_RAMPMODE_MASK            0x03 // RAMPMODE_M2 // 0: Positioning mode (using all A, D and V parameters) 1: Velocity mode to positive VMAX (using AMAX acceleration) 2: Velocity mode to negative VMAX (using AMAX acceleration) 3: Hold mode (velocity remains unchanged, unless stop event occurs)
#define TMC5031_RAMPMODE_SHIFT           0 // min.: 0, max.: 3, default: 0
#define TMC5031_XACTUAL_MASK             0xFFFFFFFF // XACTUAL_M2 // Actual motor position (signed) Hint: This value normally should only be modified, when homing the drive. In positioning mode, modifying the register content will start a motion.
#define TMC5031_XACTUAL_SHIFT            0 // min.: -2147483648, max.: 2147483647, default: 0
#define TMC5031_VACTUAL_MASK             0xFFFFFF // VACTUAL_M2 // Actual motor velocity from ramp generator (signed) The sign matches the motion direction. A negative sign means motion to lower XACTUAL.
#define TMC5031_VACTUAL_SHIFT            0 // min.: -8388607, max.: 8388607, default: 0
#define TMC5031_VSTART_MASK              0x03FFFF // VSTART_M2 // Motor start velocity (unsigned) Set VSTOP = VSTART!
#define TMC5031_VSTART_SHIFT             0 // min.: 0, max.: 262143, default: 0
#define TMC5031_A1_MASK                  0xFFFF // A1_M2 // First acceleration between VSTART and V1 (unsigned)
#define TMC5031_A1_SHIFT                 0 // min.: 0, max.: 65535, default: 0
#define TMC5031_V1__MASK                 0x0FFFFF // V1_M2 // First acceleration / deceleration phase threshold velocity (unsigned) 0: Disables A1 and D1 phase, use AMAX, DMAX only
#define TMC5031_V1__SHIFT                0 // min.: 0, max.: 1048575, default: 0
#define TMC5031_AMAX_MASK                0xFFFF // AMAX_M2 // Second acceleration between V1 and VMAX (unsigned) This is the acceleration and deceleration value for velocity mode.
#define TMC5031_AMAX_SHIFT               0 // min.: 0, max.: 65535, default: 0
#define TMC5031_VMAX_MASK                0x7FFFFF // VMAX_M2 // Motion ramp target velocity (for positioning ensure VMAX = VSTART) (unsigned) This is the target velocity in velocity mode. It can be changed any time during a motion.
#define TMC5031_VMAX_SHIFT               0 // min.: 0, max.: 8388096, default: 0
#define TMC5031_DMAX_MASK                0xFFFF // DMAX_M2 // Deceleration between VMAX and V1 (unsigned)
#define TMC5031_DMAX_SHIFT               0 // min.: 0, max.: 65535, default: 0
#define TMC5031_D1_MASK                  0xFFFF // D1_M2 // Deceleration between V1 and VSTOP (unsigned) Attention: Do not set 0 in positioning mode, even if V1=0!
#define TMC5031_D1_SHIFT                 0 // min.: 1, max.: 65535, default: 0
#define TMC5031_VSTOP_MASK               0x03FFFF // VSTOP_M2 // Motor stop velocity (unsigned) Attention: Set VSTOP = VSTART! Attention: Do not set 0 in positioning mode, minimum 10 recommend!
#define TMC5031_VSTOP_SHIFT              0 // min.: 1, max.: 262143, default: 0
#define TMC5031_TZEROWAIT_MASK           0xFFFF // TZEROWAIT_M2 // Defines the waiting time after ramping down to zero velocity before next movement or direction inversion can start. Time range is about 0 to 2 seconds. This setting avoids excess acceleration e.g. from VSTOP to -VSTART.
#define TMC5031_TZEROWAIT_SHIFT          0 // min.: 0, max.: 65535, default: 0
#define TMC5031_XTARGET_MASK             0xFFFFFFFF // XTARGET_M2 // Target position for ramp mode (signed). Write a new target position to this register in order to activate the ramp generator positioning in RAMPMODE=0. Initialize all velocity, acceleration and deceleration parameters before. Hint: The position is allowed to wrap around, thus, XTARGET value optionally can be treated as an unsigned number. Hint: The maximum possible displacement is +/-((2^31)-1). Hint: When increasing V1, D1 or DMAX during a motion, rewrite XTARGET afterwards in order to trigger a second acceleration phase, if desired.
#define TMC5031_XTARGET_SHIFT            0 // min.: -2147483648, max.: 2147483647, default: 0
#define TMC5031_IHOLD_MASK               0x1F // IHOLD_IRUN_M1 // Standstill current (0=1/32...31=32/32)
#define TMC5031_IHOLD_SHIFT              0 // min.: 0, max.: 31, default: 0
#define TMC5031_IRUN_MASK                0x1F00 // IHOLD_IRUN_M1 // Motor run current (0=1/32...31=32/32) Hint: Choose sense resistors in a way, that normal IRUN is 16 to 31 for best microstep performance.
#define TMC5031_IRUN_SHIFT               8 // min.: 0, max.: 31, default: 0
#define TMC5031_IHOLDDELAY_MASK          0x0F0000 // IHOLD_IRUN_M1 // Controls the number of clock cycles for motor power down after standstill is detected (stst=1) and TPOWERDOWN has expired. The smooth transition avoids a motor jerk upon power down. 0: instant power down 1..15: Delay per current reduction step in multiple of 2^18 clocks
#define TMC5031_IHOLDDELAY_SHIFT         16 // min.: 0, max.: 15, default: 0
#define TMC5031_VCOOLTHRS_MASK           0x7FFFFF // VCOOLTHRS_M1 // This is the lower threshold velocity for switching on smart energy coolStep. Set this parameter to disable coolStep at low speeds, where it cannot work reliably. VHIGH = |VACT| = VCOOLTHRS: coolStep is enabled, if configured; (Only bits 22..8 are used for value and for comparison)
#define TMC5031_VCOOLTHRS_SHIFT          0 // min.: 0, max.: 8388607, default: 0
#define TMC5031_VHIGH_MASK               0x7FFFFF // VHIGH_M1 // This velocity setting allows velocity dependent switching into a different chopper mode and fullstepping to maximize torque. |VACT| = VHIGH: coolStep is disabled (motor runs with normal current scale), If vhighchm is set, the chopper switches to chm=1 with TFD=0 (constant off time with slow decay, only), chopSync2 is switched off (SYNC=0), If vhighfs is set, the motor operates in fullstep mode; (Only bits 22..8 are used for value and for comparison)
#define TMC5031_VHIGH_SHIFT              0 // min.: 0, max.: 8388607, default: 0
#define TMC5031_STOP_L_ENABLE_MASK       0x01 // SW_MODE_M1 //
#define TMC5031_STOP_L_ENABLE_SHIFT      0 // min.: 0, max.: 1, default: 0
#define TMC5031_STOP_R_ENABLE_MASK       0x02 // SW_MODE_M1 //
#define TMC5031_STOP_R_ENABLE_SHIFT      1 // min.: 0, max.: 1, default: 0
#define TMC5031_POL_STOP_L_MASK          0x04 // SW_MODE_M1 // Sets the active polarity of the left reference switch input
#define TMC5031_POL_STOP_L_SHIFT         2 // min.: 0, max.: 1, default: 0
#define TMC5031_POL_STOP_R_MASK          0x08 // SW_MODE_M1 // Sets the active polarity of the right reference switch input
#define TMC5031_POL_STOP_R_SHIFT         3 // min.: 0, max.: 1, default: 0
#define TMC5031_SWAP_LR_MASK             0x10 // SW_MODE_M1 //
#define TMC5031_SWAP_LR_SHIFT            4 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_L_ACTIVE_MASK      0x20 // SW_MODE_M1 //
#define TMC5031_LATCH_L_ACTIVE_SHIFT     5 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_L_INACTIVE_MASK    0x40 // SW_MODE_M1 //
#define TMC5031_LATCH_L_INACTIVE_SHIFT   6 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_R_ACTIVE_MASK      0x80 // SW_MODE_M1 //
#define TMC5031_LATCH_R_ACTIVE_SHIFT     7 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_R_INACTIVE_MASK    0x0100 // SW_MODE_M1 //
#define TMC5031_LATCH_R_INACTIVE_SHIFT   8 // min.: 0, max.: 1, default: 0
#define TMC5031_SG_STOP_MASK             0x0400 // SW_MODE_M1 //
#define TMC5031_SG_STOP_SHIFT            10 // min.: 0, max.: 1, default: 0
#define TMC5031_EN_SOFTSTOP_MASK         0x0800 // SW_MODE_M1 // The soft stop mode always uses the deceleration ramp settings DMAX, V1, D1, VSTOP and TZEROWAIT for stopping the motor. A stop occurs when the velocity sign matches the reference switch position (REFL for negative velocities, REFR for positive velocities) and the respective switch stop function is enabled. A hard stop also uses TZEROWAIT before the motor becomes released. Attention: Do not use soft stop in combination with stallGuard2.
#define TMC5031_EN_SOFTSTOP_SHIFT        11 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_STOP_L_MASK       0x01 // RAMP_STAT_M1 //
#define TMC5031_STATUS_STOP_L_SHIFT      0 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_STOP_R_MASK       0x02 // RAMP_STAT_M1 //
#define TMC5031_STATUS_STOP_R_SHIFT      1 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_LATCH_L_MASK      0x04 // RAMP_STAT_M1 //
#define TMC5031_STATUS_LATCH_L_SHIFT     2 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_LATCH_R_MASK      0x08 // RAMP_STAT_M1 //
#define TMC5031_STATUS_LATCH_R_SHIFT     3 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_L_MASK        0x10 // RAMP_STAT_M1 //
#define TMC5031_EVENT_STOP_L_SHIFT       4 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_R_MASK        0x20 // RAMP_STAT_M1 //
#define TMC5031_EVENT_STOP_R_SHIFT       5 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_SG_MASK       0x40 // RAMP_STAT_M1 //
#define TMC5031_EVENT_STOP_SG_SHIFT      6 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_POS_REACHED_MASK   0x80 // RAMP_STAT_M1 //
#define TMC5031_EVENT_POS_REACHED_SHIFT  7 // min.: 0, max.: 1, default: 0
#define TMC5031_VELOCITY_REACHED_MASK    0x0100 // RAMP_STAT_M1 //
#define TMC5031_VELOCITY_REACHED_SHIFT   8 // min.: 0, max.: 1, default: 0
#define TMC5031_POSITION_REACHED_MASK    0x0200 // RAMP_STAT_M1 //
#define TMC5031_POSITION_REACHED_SHIFT   9 // min.: 0, max.: 1, default: 0
#define TMC5031_VZERO_MASK               0x0400 // RAMP_STAT_M1 //
#define TMC5031_VZERO_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_T_ZEROWAIT_ACTIVE_MASK   0x0800 // RAMP_STAT_M1 //
#define TMC5031_T_ZEROWAIT_ACTIVE_SHIFT  11 // min.: 0, max.: 1, default: 0
#define TMC5031_SECOND_MOVE_MASK         0x1000 // RAMP_STAT_M1 //
#define TMC5031_SECOND_MOVE_SHIFT        12 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_SG_MASK           0x2000 // RAMP_STAT_M1 //
#define TMC5031_STATUS_SG_SHIFT          13 // min.: 0, max.: 1, default: 0
#define TMC5031_XLATCH_MASK              0xFFFFFFFF // XLATCH_M1 // Ramp generator latch position, latches XACTUAL upon a programmable switch event (see SW_MODE).
#define TMC5031_XLATCH_SHIFT             0 // min.: 0, max.: 4294967295, default: 0
#define TMC5031_IHOLD_MASK               0x1F // IHOLD_IRUN_M2 // Standstill current (0=1/32...31=32/32)
#define TMC5031_IHOLD_SHIFT              0 // min.: 0, max.: 31, default: 0
#define TMC5031_IRUN_MASK                0x1F00 // IHOLD_IRUN_M2 // Motor run current (0=1/32...31=32/32) Hint: Choose sense resistors in a way, that normal IRUN is 16 to 31 for best microstep performance.
#define TMC5031_IRUN_SHIFT               8 // min.: 0, max.: 31, default: 0
#define TMC5031_IHOLDDELAY_MASK          0x0F0000 // IHOLD_IRUN_M2 // Controls the number of clock cycles for motor power down after standstill is detected (stst=1) and TPOWERDOWN has expired. The smooth transition avoids a motor jerk upon power down. 0: instant power down 1..15: Delay per current reduction step in multiple of 2^18 clocks
#define TMC5031_IHOLDDELAY_SHIFT         16 // min.: 0, max.: 15, default: 0
#define TMC5031_VCOOLTHRS_MASK           0x7FFFFF // VCOOLTHRS_M2 // This is the lower threshold velocity for switching on smart energy coolStep. Set this parameter to disable coolStep at low speeds, where it cannot work reliably. VHIGH = |VACT| = VCOOLTHRS: coolStep is enabled, if configured; (Only bits 22..8 are used for value and for comparison)
#define TMC5031_VCOOLTHRS_SHIFT          0 // min.: 0, max.: 8388607, default: 0
#define TMC5031_VHIGH_MASK               0x7FFFFF // VHIGH_M2 // This velocity setting allows velocity dependent switching into a different chopper mode and fullstepping to maximize torque. |VACT| = VHIGH: coolStep is disabled (motor runs with normal current scale), If vhighchm is set, the chopper switches to chm=1 with TFD=0 (constant off time with slow decay, only), chopSync2 is switched off (SYNC=0), If vhighfs is set, the motor operates in fullstep mode; (Only bits 22..8 are used for value and for comparison)
#define TMC5031_VHIGH_SHIFT              0 // min.: 0, max.: 8388607, default: 0
#define TMC5031_STOP_L_ENABLE_MASK       0x01 // SW_MODE_M2 //
#define TMC5031_STOP_L_ENABLE_SHIFT      0 // min.: 0, max.: 1, default: 0
#define TMC5031_STOP_R_ENABLE_MASK       0x02 // SW_MODE_M2 //
#define TMC5031_STOP_R_ENABLE_SHIFT      1 // min.: 0, max.: 1, default: 0
#define TMC5031_POL_STOP_L_MASK          0x04 // SW_MODE_M2 // Sets the active polarity of the left reference switch input
#define TMC5031_POL_STOP_L_SHIFT         2 // min.: 0, max.: 1, default: 0
#define TMC5031_POL_STOP_R_MASK          0x08 // SW_MODE_M2 // Sets the active polarity of the right reference switch input
#define TMC5031_POL_STOP_R_SHIFT         3 // min.: 0, max.: 1, default: 0
#define TMC5031_SWAP_LR_MASK             0x10 // SW_MODE_M2 //
#define TMC5031_SWAP_LR_SHIFT            4 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_L_ACTIVE_MASK      0x20 // SW_MODE_M2 //
#define TMC5031_LATCH_L_ACTIVE_SHIFT     5 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_L_INACTIVE_MASK    0x40 // SW_MODE_M2 //
#define TMC5031_LATCH_L_INACTIVE_SHIFT   6 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_R_ACTIVE_MASK      0x80 // SW_MODE_M2 //
#define TMC5031_LATCH_R_ACTIVE_SHIFT     7 // min.: 0, max.: 1, default: 0
#define TMC5031_LATCH_R_INACTIVE_MASK    0x0100 // SW_MODE_M2 //
#define TMC5031_LATCH_R_INACTIVE_SHIFT   8 // min.: 0, max.: 1, default: 0
#define TMC5031_SG_STOP_MASK             0x0400 // SW_MODE_M2 //
#define TMC5031_SG_STOP_SHIFT            10 // min.: 0, max.: 1, default: 0
#define TMC5031_EN_SOFTSTOP_MASK         0x0800 // SW_MODE_M2 // The soft stop mode always uses the deceleration ramp settings DMAX, V1, D1, VSTOP and TZEROWAIT for stopping the motor. A stop occurs when the velocity sign matches the reference switch position (REFL for negative velocities, REFR for positive velocities) and the respective switch stop function is enabled. A hard stop also uses TZEROWAIT before the motor becomes released. Attention: Do not use soft stop in combination with stallGuard2.
#define TMC5031_EN_SOFTSTOP_SHIFT        11 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_STOP_L_MASK       0x01 // RAMP_STAT_M2 //
#define TMC5031_STATUS_STOP_L_SHIFT      0 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_STOP_R_MASK       0x02 // RAMP_STAT_M2 //
#define TMC5031_STATUS_STOP_R_SHIFT      1 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_LATCH_L_MASK      0x04 // RAMP_STAT_M2 //
#define TMC5031_STATUS_LATCH_L_SHIFT     2 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_LATCH_R_MASK      0x08 // RAMP_STAT_M2 //
#define TMC5031_STATUS_LATCH_R_SHIFT     3 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_L_MASK        0x10 // RAMP_STAT_M2 //
#define TMC5031_EVENT_STOP_L_SHIFT       4 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_R_MASK        0x20 // RAMP_STAT_M2 //
#define TMC5031_EVENT_STOP_R_SHIFT       5 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_STOP_SG_MASK       0x40 // RAMP_STAT_M2 //
#define TMC5031_EVENT_STOP_SG_SHIFT      6 // min.: 0, max.: 1, default: 0
#define TMC5031_EVENT_POS_REACHED_MASK   0x80 // RAMP_STAT_M2 //
#define TMC5031_EVENT_POS_REACHED_SHIFT  7 // min.: 0, max.: 1, default: 0
#define TMC5031_VELOCITY_REACHED_MASK    0x0100 // RAMP_STAT_M2 //
#define TMC5031_VELOCITY_REACHED_SHIFT   8 // min.: 0, max.: 1, default: 0
#define TMC5031_POSITION_REACHED_MASK    0x0200 // RAMP_STAT_M2 //
#define TMC5031_POSITION_REACHED_SHIFT   9 // min.: 0, max.: 1, default: 0
#define TMC5031_VZERO_MASK               0x0400 // RAMP_STAT_M2 //
#define TMC5031_VZERO_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_T_ZEROWAIT_ACTIVE_MASK   0x0800 // RAMP_STAT_M2 //
#define TMC5031_T_ZEROWAIT_ACTIVE_SHIFT  11 // min.: 0, max.: 1, default: 0
#define TMC5031_SECOND_MOVE_MASK         0x1000 // RAMP_STAT_M2 //
#define TMC5031_SECOND_MOVE_SHIFT        12 // min.: 0, max.: 1, default: 0
#define TMC5031_STATUS_SG_MASK           0x2000 // RAMP_STAT_M2 //
#define TMC5031_STATUS_SG_SHIFT          13 // min.: 0, max.: 1, default: 0
#define TMC5031_XLATCH_MASK              0xFFFFFFFF // XLATCH_M2 // Ramp generator latch position, latches XACTUAL upon a programmable switch event (see SW_MODE).
#define TMC5031_XLATCH_SHIFT             0 // min.: 0, max.: 4294967295, default: 0
#define TMC5031_OFS0_MASK                0x01 // MSLUT[0]_M1 // microstep table entry 0
#define TMC5031_OFS0_SHIFT               0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS1_MASK                0x02 // MSLUT[0]_M1 // microstep table entry 1
#define TMC5031_OFS1_SHIFT               1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS2_MASK                0x04 // MSLUT[0]_M1 // microstep table entry 2
#define TMC5031_OFS2_SHIFT               2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS3_MASK                0x08 // MSLUT[0]_M1 // microstep table entry 3
#define TMC5031_OFS3_SHIFT               3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS4_MASK                0x10 // MSLUT[0]_M1 // microstep table entry 4
#define TMC5031_OFS4_SHIFT               4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS5_MASK                0x20 // MSLUT[0]_M1 // microstep table entry 5
#define TMC5031_OFS5_SHIFT               5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS6_MASK                0x40 // MSLUT[0]_M1 // microstep table entry 6
#define TMC5031_OFS6_SHIFT               6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS7_MASK                0x80 // MSLUT[0]_M1 // microstep table entry 7
#define TMC5031_OFS7_SHIFT               7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS8_MASK                0x0100 // MSLUT[0]_M1 // microstep table entry 8
#define TMC5031_OFS8_SHIFT               8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS9_MASK                0x0200 // MSLUT[0]_M1 // microstep table entry 9
#define TMC5031_OFS9_SHIFT               9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS10_MASK               0x0400 // MSLUT[0]_M1 // microstep table entry 10
#define TMC5031_OFS10_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS11_MASK               0x0800 // MSLUT[0]_M1 // microstep table entry 11
#define TMC5031_OFS11_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS12_MASK               0x1000 // MSLUT[0]_M1 // microstep table entry 12
#define TMC5031_OFS12_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS13_MASK               0x2000 // MSLUT[0]_M1 // microstep table entry 13
#define TMC5031_OFS13_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS14_MASK               0x4000 // MSLUT[0]_M1 // microstep table entry 14
#define TMC5031_OFS14_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS15_MASK               0x8000 // MSLUT[0]_M1 // microstep table entry 15
#define TMC5031_OFS15_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS16_MASK               0x010000 // MSLUT[0]_M1 // microstep table entry 16
#define TMC5031_OFS16_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS17_MASK               0x020000 // MSLUT[0]_M1 // microstep table entry 17
#define TMC5031_OFS17_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS18_MASK               0x040000 // MSLUT[0]_M1 // microstep table entry 18
#define TMC5031_OFS18_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS19_MASK               0x080000 // MSLUT[0]_M1 // microstep table entry 19
#define TMC5031_OFS19_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS20_MASK               0x100000 // MSLUT[0]_M1 // microstep table entry 20
#define TMC5031_OFS20_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS21_MASK               0x200000 // MSLUT[0]_M1 // microstep table entry 21
#define TMC5031_OFS21_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS22_MASK               0x400000 // MSLUT[0]_M1 // microstep table entry 22
#define TMC5031_OFS22_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS23_MASK               0x800000 // MSLUT[0]_M1 // microstep table entry 23
#define TMC5031_OFS23_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS24_MASK               0x01000000 // MSLUT[0]_M1 // microstep table entry 24
#define TMC5031_OFS24_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS25_MASK               0x02000000 // MSLUT[0]_M1 // microstep table entry 25
#define TMC5031_OFS25_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS26_MASK               0x04000000 // MSLUT[0]_M1 // microstep table entry 26
#define TMC5031_OFS26_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS27_MASK               0x08000000 // MSLUT[0]_M1 // microstep table entry 27
#define TMC5031_OFS27_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS28_MASK               0x10000000 // MSLUT[0]_M1 // microstep table entry 28
#define TMC5031_OFS28_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS29_MASK               0x20000000 // MSLUT[0]_M1 // microstep table entry 29
#define TMC5031_OFS29_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS30_MASK               0x40000000 // MSLUT[0]_M1 // microstep table entry 30
#define TMC5031_OFS30_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS31_MASK               0x80000000 // MSLUT[0]_M1 // microstep table entry 31
#define TMC5031_OFS31_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS32_MASK               0x01 // MSLUT[1]_M1 // microstep table entry 32
#define TMC5031_OFS32_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS33_MASK               0x02 // MSLUT[1]_M1 // microstep table entry 33
#define TMC5031_OFS33_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS34_MASK               0x04 // MSLUT[1]_M1 // microstep table entry 34
#define TMC5031_OFS34_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS35_MASK               0x08 // MSLUT[1]_M1 // microstep table entry 35
#define TMC5031_OFS35_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS36_MASK               0x10 // MSLUT[1]_M1 // microstep table entry 36
#define TMC5031_OFS36_SHIFT              4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS37_MASK               0x20 // MSLUT[1]_M1 // microstep table entry 37
#define TMC5031_OFS37_SHIFT              5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS38_MASK               0x40 // MSLUT[1]_M1 // microstep table entry 38
#define TMC5031_OFS38_SHIFT              6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS39_MASK               0x80 // MSLUT[1]_M1 // microstep table entry 39
#define TMC5031_OFS39_SHIFT              7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS40_MASK               0x0100 // MSLUT[1]_M1 // microstep table entry 40
#define TMC5031_OFS40_SHIFT              8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS41_MASK               0x0200 // MSLUT[1]_M1 // microstep table entry 41
#define TMC5031_OFS41_SHIFT              9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS42_MASK               0x0400 // MSLUT[1]_M1 // microstep table entry 42
#define TMC5031_OFS42_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS43_MASK               0x0800 // MSLUT[1]_M1 // microstep table entry 43
#define TMC5031_OFS43_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS44_MASK               0x1000 // MSLUT[1]_M1 // microstep table entry 44
#define TMC5031_OFS44_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS45_MASK               0x2000 // MSLUT[1]_M1 // microstep table entry 45
#define TMC5031_OFS45_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS46_MASK               0x4000 // MSLUT[1]_M1 // microstep table entry 46
#define TMC5031_OFS46_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS47_MASK               0x8000 // MSLUT[1]_M1 // microstep table entry 47
#define TMC5031_OFS47_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS48_MASK               0x010000 // MSLUT[1]_M1 // microstep table entry 48
#define TMC5031_OFS48_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS49_MASK               0x020000 // MSLUT[1]_M1 // microstep table entry 49
#define TMC5031_OFS49_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS50_MASK               0x040000 // MSLUT[1]_M1 // microstep table entry 50
#define TMC5031_OFS50_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS51_MASK               0x080000 // MSLUT[1]_M1 // microstep table entry 51
#define TMC5031_OFS51_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS52_MASK               0x100000 // MSLUT[1]_M1 // microstep table entry 52
#define TMC5031_OFS52_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS53_MASK               0x200000 // MSLUT[1]_M1 // microstep table entry 53
#define TMC5031_OFS53_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS54_MASK               0x400000 // MSLUT[1]_M1 // microstep table entry 54
#define TMC5031_OFS54_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS55_MASK               0x800000 // MSLUT[1]_M1 // microstep table entry 55
#define TMC5031_OFS55_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS56_MASK               0x01000000 // MSLUT[1]_M1 // microstep table entry 56
#define TMC5031_OFS56_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS57_MASK               0x02000000 // MSLUT[1]_M1 // microstep table entry 57
#define TMC5031_OFS57_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS58_MASK               0x04000000 // MSLUT[1]_M1 // microstep table entry 58
#define TMC5031_OFS58_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS59_MASK               0x08000000 // MSLUT[1]_M1 // microstep table entry 59
#define TMC5031_OFS59_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS60_MASK               0x10000000 // MSLUT[1]_M1 // microstep table entry 60
#define TMC5031_OFS60_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS61_MASK               0x20000000 // MSLUT[1]_M1 // microstep table entry 61
#define TMC5031_OFS61_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS62_MASK               0x40000000 // MSLUT[1]_M1 // microstep table entry 62
#define TMC5031_OFS62_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS63_MASK               0x80000000 // MSLUT[1]_M1 // microstep table entry 63
#define TMC5031_OFS63_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS64_MASK               0x01 // MSLUT[2]_M1 // microstep table entry 64
#define TMC5031_OFS64_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS65_MASK               0x02 // MSLUT[2]_M1 // microstep table entry 65
#define TMC5031_OFS65_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS66_MASK               0x04 // MSLUT[2]_M1 // microstep table entry 66
#define TMC5031_OFS66_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS67_MASK               0x08 // MSLUT[2]_M1 // microstep table entry 67
#define TMC5031_OFS67_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS68_MASK               0x10 // MSLUT[2]_M1 // microstep table entry 68
#define TMC5031_OFS68_SHIFT              4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS69_MASK               0x20 // MSLUT[2]_M1 // microstep table entry 69
#define TMC5031_OFS69_SHIFT              5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS70_MASK               0x40 // MSLUT[2]_M1 // microstep table entry 70
#define TMC5031_OFS70_SHIFT              6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS71_MASK               0x80 // MSLUT[2]_M1 // microstep table entry 71
#define TMC5031_OFS71_SHIFT              7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS72_MASK               0x0100 // MSLUT[2]_M1 // microstep table entry 72
#define TMC5031_OFS72_SHIFT              8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS73_MASK               0x0200 // MSLUT[2]_M1 // microstep table entry 73
#define TMC5031_OFS73_SHIFT              9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS74_MASK               0x0400 // MSLUT[2]_M1 // microstep table entry 74
#define TMC5031_OFS74_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS75_MASK               0x0800 // MSLUT[2]_M1 // microstep table entry 75
#define TMC5031_OFS75_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS76_MASK               0x1000 // MSLUT[2]_M1 // microstep table entry 76
#define TMC5031_OFS76_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS77_MASK               0x2000 // MSLUT[2]_M1 // microstep table entry 77
#define TMC5031_OFS77_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS78_MASK               0x4000 // MSLUT[2]_M1 // microstep table entry 78
#define TMC5031_OFS78_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS79_MASK               0x8000 // MSLUT[2]_M1 // microstep table entry 79
#define TMC5031_OFS79_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS80_MASK               0x010000 // MSLUT[2]_M1 // microstep table entry 80
#define TMC5031_OFS80_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS81_MASK               0x020000 // MSLUT[2]_M1 // microstep table entry 81
#define TMC5031_OFS81_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS82_MASK               0x040000 // MSLUT[2]_M1 // microstep table entry 82
#define TMC5031_OFS82_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS83_MASK               0x080000 // MSLUT[2]_M1 // microstep table entry 83
#define TMC5031_OFS83_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS84_MASK               0x100000 // MSLUT[2]_M1 // microstep table entry 84
#define TMC5031_OFS84_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS85_MASK               0x200000 // MSLUT[2]_M1 // microstep table entry 85
#define TMC5031_OFS85_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS86_MASK               0x400000 // MSLUT[2]_M1 // microstep table entry 86
#define TMC5031_OFS86_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS87_MASK               0x800000 // MSLUT[2]_M1 // microstep table entry 87
#define TMC5031_OFS87_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS88_MASK               0x01000000 // MSLUT[2]_M1 // microstep table entry 88
#define TMC5031_OFS88_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS89_MASK               0x02000000 // MSLUT[2]_M1 // microstep table entry 89
#define TMC5031_OFS89_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS90_MASK               0x04000000 // MSLUT[2]_M1 // microstep table entry 90
#define TMC5031_OFS90_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS91_MASK               0x08000000 // MSLUT[2]_M1 // microstep table entry 91
#define TMC5031_OFS91_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS92_MASK               0x10000000 // MSLUT[2]_M1 // microstep table entry 92
#define TMC5031_OFS92_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS93_MASK               0x20000000 // MSLUT[2]_M1 // microstep table entry 93
#define TMC5031_OFS93_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS94_MASK               0x40000000 // MSLUT[2]_M1 // microstep table entry 94
#define TMC5031_OFS94_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS95_MASK               0x80000000 // MSLUT[2]_M1 // microstep table entry 95
#define TMC5031_OFS95_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS96_MASK               0x01 // MSLUT[3]_M1 // microstep table entry 96
#define TMC5031_OFS96_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS97_MASK               0x02 // MSLUT[3]_M1 // microstep table entry 97
#define TMC5031_OFS97_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS98_MASK               0x04 // MSLUT[3]_M1 // microstep table entry 98
#define TMC5031_OFS98_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS99_MASK               0x08 // MSLUT[3]_M1 // microstep table entry 99
#define TMC5031_OFS99_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS100_MASK              0x10 // MSLUT[3]_M1 // microstep table entry 100
#define TMC5031_OFS100_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS101_MASK              0x20 // MSLUT[3]_M1 // microstep table entry 101
#define TMC5031_OFS101_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS102_MASK              0x40 // MSLUT[3]_M1 // microstep table entry 102
#define TMC5031_OFS102_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS103_MASK              0x80 // MSLUT[3]_M1 // microstep table entry 103
#define TMC5031_OFS103_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS104_MASK              0x0100 // MSLUT[3]_M1 // microstep table entry 104
#define TMC5031_OFS104_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS105_MASK              0x0200 // MSLUT[3]_M1 // microstep table entry 105
#define TMC5031_OFS105_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS106_MASK              0x0400 // MSLUT[3]_M1 // microstep table entry 106
#define TMC5031_OFS106_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS107_MASK              0x0800 // MSLUT[3]_M1 // microstep table entry 107
#define TMC5031_OFS107_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS108_MASK              0x1000 // MSLUT[3]_M1 // microstep table entry 108
#define TMC5031_OFS108_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS109_MASK              0x2000 // MSLUT[3]_M1 // microstep table entry 109
#define TMC5031_OFS109_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS110_MASK              0x4000 // MSLUT[3]_M1 // microstep table entry 110
#define TMC5031_OFS110_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS111_MASK              0x8000 // MSLUT[3]_M1 // microstep table entry 111
#define TMC5031_OFS111_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS112_MASK              0x010000 // MSLUT[3]_M1 // microstep table entry 112
#define TMC5031_OFS112_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS113_MASK              0x020000 // MSLUT[3]_M1 // microstep table entry 113
#define TMC5031_OFS113_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS114_MASK              0x040000 // MSLUT[3]_M1 // microstep table entry 114
#define TMC5031_OFS114_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS115_MASK              0x080000 // MSLUT[3]_M1 // microstep table entry 115
#define TMC5031_OFS115_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS116_MASK              0x100000 // MSLUT[3]_M1 // microstep table entry 116
#define TMC5031_OFS116_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS117_MASK              0x200000 // MSLUT[3]_M1 // microstep table entry 117
#define TMC5031_OFS117_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS118_MASK              0x400000 // MSLUT[3]_M1 // microstep table entry 118
#define TMC5031_OFS118_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS119_MASK              0x800000 // MSLUT[3]_M1 // microstep table entry 119
#define TMC5031_OFS119_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS120_MASK              0x01000000 // MSLUT[3]_M1 // microstep table entry 120
#define TMC5031_OFS120_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS121_MASK              0x02000000 // MSLUT[3]_M1 // microstep table entry 121
#define TMC5031_OFS121_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS122_MASK              0x04000000 // MSLUT[3]_M1 // microstep table entry 122
#define TMC5031_OFS122_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS123_MASK              0x08000000 // MSLUT[3]_M1 // microstep table entry 123
#define TMC5031_OFS123_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS124_MASK              0x10000000 // MSLUT[3]_M1 // microstep table entry 124
#define TMC5031_OFS124_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS125_MASK              0x20000000 // MSLUT[3]_M1 // microstep table entry 125
#define TMC5031_OFS125_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS126_MASK              0x40000000 // MSLUT[3]_M1 // microstep table entry 126
#define TMC5031_OFS126_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS127_MASK              0x80000000 // MSLUT[3]_M1 // microstep table entry 127
#define TMC5031_OFS127_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS128_MASK              0x01 // MSLUT[4]_M1 // microstep table entry 128
#define TMC5031_OFS128_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS129_MASK              0x02 // MSLUT[4]_M1 // microstep table entry 129
#define TMC5031_OFS129_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS130_MASK              0x04 // MSLUT[4]_M1 // microstep table entry 130
#define TMC5031_OFS130_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS131_MASK              0x08 // MSLUT[4]_M1 // microstep table entry 131
#define TMC5031_OFS131_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS132_MASK              0x10 // MSLUT[4]_M1 // microstep table entry 132
#define TMC5031_OFS132_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS133_MASK              0x20 // MSLUT[4]_M1 // microstep table entry 133
#define TMC5031_OFS133_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS134_MASK              0x40 // MSLUT[4]_M1 // microstep table entry 134
#define TMC5031_OFS134_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS135_MASK              0x80 // MSLUT[4]_M1 // microstep table entry 135
#define TMC5031_OFS135_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS136_MASK              0x0100 // MSLUT[4]_M1 // microstep table entry 136
#define TMC5031_OFS136_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS137_MASK              0x0200 // MSLUT[4]_M1 // microstep table entry 137
#define TMC5031_OFS137_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS138_MASK              0x0400 // MSLUT[4]_M1 // microstep table entry 138
#define TMC5031_OFS138_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS139_MASK              0x0800 // MSLUT[4]_M1 // microstep table entry 139
#define TMC5031_OFS139_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS140_MASK              0x1000 // MSLUT[4]_M1 // microstep table entry 140
#define TMC5031_OFS140_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS141_MASK              0x2000 // MSLUT[4]_M1 // microstep table entry 141
#define TMC5031_OFS141_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS142_MASK              0x4000 // MSLUT[4]_M1 // microstep table entry 142
#define TMC5031_OFS142_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS143_MASK              0x8000 // MSLUT[4]_M1 // microstep table entry 143
#define TMC5031_OFS143_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS144_MASK              0x010000 // MSLUT[4]_M1 // microstep table entry 144
#define TMC5031_OFS144_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS145_MASK              0x020000 // MSLUT[4]_M1 // microstep table entry 145
#define TMC5031_OFS145_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS146_MASK              0x040000 // MSLUT[4]_M1 // microstep table entry 146
#define TMC5031_OFS146_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS147_MASK              0x080000 // MSLUT[4]_M1 // microstep table entry 147
#define TMC5031_OFS147_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS148_MASK              0x100000 // MSLUT[4]_M1 // microstep table entry 148
#define TMC5031_OFS148_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS149_MASK              0x200000 // MSLUT[4]_M1 // microstep table entry 149
#define TMC5031_OFS149_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS150_MASK              0x400000 // MSLUT[4]_M1 // microstep table entry 150
#define TMC5031_OFS150_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS151_MASK              0x800000 // MSLUT[4]_M1 // microstep table entry 151
#define TMC5031_OFS151_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS152_MASK              0x01000000 // MSLUT[4]_M1 // microstep table entry 152
#define TMC5031_OFS152_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS153_MASK              0x02000000 // MSLUT[4]_M1 // microstep table entry 153
#define TMC5031_OFS153_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS154_MASK              0x04000000 // MSLUT[4]_M1 // microstep table entry 154
#define TMC5031_OFS154_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS155_MASK              0x08000000 // MSLUT[4]_M1 // microstep table entry 155
#define TMC5031_OFS155_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS156_MASK              0x10000000 // MSLUT[4]_M1 // microstep table entry 156
#define TMC5031_OFS156_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS157_MASK              0x20000000 // MSLUT[4]_M1 // microstep table entry 157
#define TMC5031_OFS157_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS158_MASK              0x40000000 // MSLUT[4]_M1 // microstep table entry 158
#define TMC5031_OFS158_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS159_MASK              0x80000000 // MSLUT[4]_M1 // microstep table entry 159
#define TMC5031_OFS159_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS160_MASK              0x01 // MSLUT[5]_M1 // microstep table entry 160
#define TMC5031_OFS160_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS161_MASK              0x02 // MSLUT[5]_M1 // microstep table entry 161
#define TMC5031_OFS161_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS162_MASK              0x04 // MSLUT[5]_M1 // microstep table entry 162
#define TMC5031_OFS162_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS163_MASK              0x08 // MSLUT[5]_M1 // microstep table entry 163
#define TMC5031_OFS163_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS164_MASK              0x10 // MSLUT[5]_M1 // microstep table entry 164
#define TMC5031_OFS164_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS165_MASK              0x20 // MSLUT[5]_M1 // microstep table entry 165
#define TMC5031_OFS165_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS166_MASK              0x40 // MSLUT[5]_M1 // microstep table entry 166
#define TMC5031_OFS166_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS167_MASK              0x80 // MSLUT[5]_M1 // microstep table entry 167
#define TMC5031_OFS167_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS168_MASK              0x0100 // MSLUT[5]_M1 // microstep table entry 168
#define TMC5031_OFS168_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS169_MASK              0x0200 // MSLUT[5]_M1 // microstep table entry 169
#define TMC5031_OFS169_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS170_MASK              0x0400 // MSLUT[5]_M1 // microstep table entry 170
#define TMC5031_OFS170_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS171_MASK              0x0800 // MSLUT[5]_M1 // microstep table entry 171
#define TMC5031_OFS171_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS172_MASK              0x1000 // MSLUT[5]_M1 // microstep table entry 172
#define TMC5031_OFS172_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS173_MASK              0x2000 // MSLUT[5]_M1 // microstep table entry 173
#define TMC5031_OFS173_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS174_MASK              0x4000 // MSLUT[5]_M1 // microstep table entry 174
#define TMC5031_OFS174_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS175_MASK              0x8000 // MSLUT[5]_M1 // microstep table entry 175
#define TMC5031_OFS175_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS176_MASK              0x010000 // MSLUT[5]_M1 // microstep table entry 176
#define TMC5031_OFS176_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS177_MASK              0x020000 // MSLUT[5]_M1 // microstep table entry 177
#define TMC5031_OFS177_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS178_MASK              0x040000 // MSLUT[5]_M1 // microstep table entry 178
#define TMC5031_OFS178_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS179_MASK              0x080000 // MSLUT[5]_M1 // microstep table entry 179
#define TMC5031_OFS179_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS180_MASK              0x100000 // MSLUT[5]_M1 // microstep table entry 180
#define TMC5031_OFS180_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS181_MASK              0x200000 // MSLUT[5]_M1 // microstep table entry 181
#define TMC5031_OFS181_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS182_MASK              0x400000 // MSLUT[5]_M1 // microstep table entry 182
#define TMC5031_OFS182_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS183_MASK              0x800000 // MSLUT[5]_M1 // microstep table entry 183
#define TMC5031_OFS183_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS184_MASK              0x01000000 // MSLUT[5]_M1 // microstep table entry 184
#define TMC5031_OFS184_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS185_MASK              0x02000000 // MSLUT[5]_M1 // microstep table entry 185
#define TMC5031_OFS185_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS186_MASK              0x04000000 // MSLUT[5]_M1 // microstep table entry 186
#define TMC5031_OFS186_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS187_MASK              0x08000000 // MSLUT[5]_M1 // microstep table entry 187
#define TMC5031_OFS187_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS188_MASK              0x10000000 // MSLUT[5]_M1 // microstep table entry 188
#define TMC5031_OFS188_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS189_MASK              0x20000000 // MSLUT[5]_M1 // microstep table entry 189
#define TMC5031_OFS189_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS190_MASK              0x40000000 // MSLUT[5]_M1 // microstep table entry 190
#define TMC5031_OFS190_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS191_MASK              0x80000000 // MSLUT[5]_M1 // microstep table entry 191
#define TMC5031_OFS191_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS192_MASK              0x01 // MSLUT[6]_M1 // microstep table entry 192
#define TMC5031_OFS192_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS193_MASK              0x02 // MSLUT[6]_M1 // microstep table entry 193
#define TMC5031_OFS193_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS194_MASK              0x04 // MSLUT[6]_M1 // microstep table entry 194
#define TMC5031_OFS194_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS195_MASK              0x08 // MSLUT[6]_M1 // microstep table entry 195
#define TMC5031_OFS195_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS196_MASK              0x10 // MSLUT[6]_M1 // microstep table entry 196
#define TMC5031_OFS196_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS197_MASK              0x20 // MSLUT[6]_M1 // microstep table entry 197
#define TMC5031_OFS197_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS198_MASK              0x40 // MSLUT[6]_M1 // microstep table entry 198
#define TMC5031_OFS198_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS199_MASK              0x80 // MSLUT[6]_M1 // microstep table entry 199
#define TMC5031_OFS199_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS200_MASK              0x0100 // MSLUT[6]_M1 // microstep table entry 200
#define TMC5031_OFS200_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS201_MASK              0x0200 // MSLUT[6]_M1 // microstep table entry 201
#define TMC5031_OFS201_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS202_MASK              0x0400 // MSLUT[6]_M1 // microstep table entry 202
#define TMC5031_OFS202_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS203_MASK              0x0800 // MSLUT[6]_M1 // microstep table entry 203
#define TMC5031_OFS203_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS204_MASK              0x1000 // MSLUT[6]_M1 // microstep table entry 204
#define TMC5031_OFS204_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS205_MASK              0x2000 // MSLUT[6]_M1 // microstep table entry 205
#define TMC5031_OFS205_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS206_MASK              0x4000 // MSLUT[6]_M1 // microstep table entry 206
#define TMC5031_OFS206_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS207_MASK              0x8000 // MSLUT[6]_M1 // microstep table entry 207
#define TMC5031_OFS207_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS208_MASK              0x010000 // MSLUT[6]_M1 // microstep table entry 208
#define TMC5031_OFS208_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS209_MASK              0x020000 // MSLUT[6]_M1 // microstep table entry 209
#define TMC5031_OFS209_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS210_MASK              0x040000 // MSLUT[6]_M1 // microstep table entry 210
#define TMC5031_OFS210_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS211_MASK              0x080000 // MSLUT[6]_M1 // microstep table entry 211
#define TMC5031_OFS211_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS212_MASK              0x100000 // MSLUT[6]_M1 // microstep table entry 212
#define TMC5031_OFS212_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS213_MASK              0x200000 // MSLUT[6]_M1 // microstep table entry 213
#define TMC5031_OFS213_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS214_MASK              0x400000 // MSLUT[6]_M1 // microstep table entry 214
#define TMC5031_OFS214_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS215_MASK              0x800000 // MSLUT[6]_M1 // microstep table entry 215
#define TMC5031_OFS215_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS216_MASK              0x01000000 // MSLUT[6]_M1 // microstep table entry 216
#define TMC5031_OFS216_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS217_MASK              0x02000000 // MSLUT[6]_M1 // microstep table entry 217
#define TMC5031_OFS217_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS218_MASK              0x04000000 // MSLUT[6]_M1 // microstep table entry 218
#define TMC5031_OFS218_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS219_MASK              0x08000000 // MSLUT[6]_M1 // microstep table entry 219
#define TMC5031_OFS219_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS220_MASK              0x10000000 // MSLUT[6]_M1 // microstep table entry 220
#define TMC5031_OFS220_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS221_MASK              0x20000000 // MSLUT[6]_M1 // microstep table entry 221
#define TMC5031_OFS221_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS222_MASK              0x40000000 // MSLUT[6]_M1 // microstep table entry 222
#define TMC5031_OFS222_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS223_MASK              0x80000000 // MSLUT[6]_M1 // microstep table entry 223
#define TMC5031_OFS223_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS224_MASK              0x01 // MSLUT[7]_M1 // microstep table entry 224
#define TMC5031_OFS224_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS225_MASK              0x02 // MSLUT[7]_M1 // microstep table entry 225
#define TMC5031_OFS225_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS226_MASK              0x04 // MSLUT[7]_M1 // microstep table entry 226
#define TMC5031_OFS226_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS227_MASK              0x08 // MSLUT[7]_M1 // microstep table entry 227
#define TMC5031_OFS227_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS228_MASK              0x10 // MSLUT[7]_M1 // microstep table entry 228
#define TMC5031_OFS228_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS229_MASK              0x20 // MSLUT[7]_M1 // microstep table entry 229
#define TMC5031_OFS229_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS230_MASK              0x40 // MSLUT[7]_M1 // microstep table entry 230
#define TMC5031_OFS230_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS231_MASK              0x80 // MSLUT[7]_M1 // microstep table entry 231
#define TMC5031_OFS231_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS232_MASK              0x0100 // MSLUT[7]_M1 // microstep table entry 232
#define TMC5031_OFS232_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS233_MASK              0x0200 // MSLUT[7]_M1 // microstep table entry 233
#define TMC5031_OFS233_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS234_MASK              0x0400 // MSLUT[7]_M1 // microstep table entry 234
#define TMC5031_OFS234_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS235_MASK              0x0800 // MSLUT[7]_M1 // microstep table entry 235
#define TMC5031_OFS235_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS236_MASK              0x1000 // MSLUT[7]_M1 // microstep table entry 236
#define TMC5031_OFS236_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS237_MASK              0x2000 // MSLUT[7]_M1 // microstep table entry 237
#define TMC5031_OFS237_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS238_MASK              0x4000 // MSLUT[7]_M1 // microstep table entry 238
#define TMC5031_OFS238_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS239_MASK              0x8000 // MSLUT[7]_M1 // microstep table entry 239
#define TMC5031_OFS239_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS240_MASK              0x010000 // MSLUT[7]_M1 // microstep table entry 240
#define TMC5031_OFS240_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS241_MASK              0x020000 // MSLUT[7]_M1 // microstep table entry 241
#define TMC5031_OFS241_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS242_MASK              0x040000 // MSLUT[7]_M1 // microstep table entry 242
#define TMC5031_OFS242_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS243_MASK              0x080000 // MSLUT[7]_M1 // microstep table entry 243
#define TMC5031_OFS243_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS244_MASK              0x100000 // MSLUT[7]_M1 // microstep table entry 244
#define TMC5031_OFS244_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS245_MASK              0x200000 // MSLUT[7]_M1 // microstep table entry 245
#define TMC5031_OFS245_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS246_MASK              0x400000 // MSLUT[7]_M1 // microstep table entry 246
#define TMC5031_OFS246_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS247_MASK              0x800000 // MSLUT[7]_M1 // microstep table entry 247
#define TMC5031_OFS247_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS248_MASK              0x01000000 // MSLUT[7]_M1 // microstep table entry 248
#define TMC5031_OFS248_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS249_MASK              0x02000000 // MSLUT[7]_M1 // microstep table entry 249
#define TMC5031_OFS249_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS250_MASK              0x04000000 // MSLUT[7]_M1 // microstep table entry 250
#define TMC5031_OFS250_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS251_MASK              0x08000000 // MSLUT[7]_M1 // microstep table entry 251
#define TMC5031_OFS251_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS252_MASK              0x10000000 // MSLUT[7]_M1 // microstep table entry 252
#define TMC5031_OFS252_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS253_MASK              0x20000000 // MSLUT[7]_M1 // microstep table entry 253
#define TMC5031_OFS253_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS254_MASK              0x40000000 // MSLUT[7]_M1 // microstep table entry 254
#define TMC5031_OFS254_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS255_MASK              0x80000000 // MSLUT[7]_M1 // microstep table entry 255
#define TMC5031_OFS255_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_W0_MASK                  0x03 // MSLUTSEL_M1 // LUT width select from ofs0 to ofs(X1-1)
#define TMC5031_W0_SHIFT                 0 // min.: 0, max.: 3, default: 0
#define TMC5031_W1_MASK                  0x0C // MSLUTSEL_M1 // LUT width select from ofs(X1) to ofs(X2-1)
#define TMC5031_W1_SHIFT                 2 // min.: 0, max.: 3, default: 0
#define TMC5031_W2_MASK                  0x30 // MSLUTSEL_M1 // LUT width select from ofs(X2) to ofs(X3-1)
#define TMC5031_W2_SHIFT                 4 // min.: 0, max.: 3, default: 0
#define TMC5031_W3_MASK                  0xC0 // MSLUTSEL_M1 // LUT width select from ofs(X3) to ofs255
#define TMC5031_W3_SHIFT                 6 // min.: 0, max.: 3, default: 0
#define TMC5031_X1_MASK                  0xFF00 // MSLUTSEL_M1 // LUT segment 1 start
#define TMC5031_X1_SHIFT                 8 // min.: 0, max.: 255, default: 0
#define TMC5031_X2_MASK                  0xFF0000 // MSLUTSEL_M1 // LUT segment 2 start
#define TMC5031_X2_SHIFT                 16 // min.: 0, max.: 255, default: 0
#define TMC5031_X3_MASK                  0xFF000000 // MSLUTSEL_M1 // LUT segment 3 start
#define TMC5031_X3_SHIFT                 24 // min.: 0, max.: 255, default: 0
#define TMC5031_START_SIN_MASK           0xFF // MSLUTSTART_M1 // Absolute current at microstep table entry 0.
#define TMC5031_START_SIN_SHIFT          0 // min.: 0, max.: 255, default: 0
#define TMC5031_START_SIN90_MASK         0xFF0000 // MSLUTSTART_M1 // Absolute current for microstep table entry at positions 256.
#define TMC5031_START_SIN90_SHIFT        16 // min.: 0, max.: 255, default: 0
#define TMC5031_MSCNT_MASK               0x03FF // MSCNT_M1 // Microstep counter. Indicates actual position in the microstep table for CUR_A. CUR_B uses an offset of 256 (2 phase motor). Hint: Move to a position where MSCNT is zero before re-initializing MSLUTSTART or MSLUT and MSLUTSEL.
#define TMC5031_MSCNT_SHIFT              0 // min.: 0, max.: 1023, default: 0
#define TMC5031_CUR_A_MASK               0x01FF // MSCURACT_M1 // Actual microstep current for motor phase A as read from MSLUT (not scaled by current)
#define TMC5031_CUR_A_SHIFT              0 // min.: -256, max.: 255, default: 0
#define TMC5031_CUR_B_MASK               0x01FF0000 // MSCURACT_M1 // Actual microstep current for motor phase B as read from MSLUT (not scaled by current)
#define TMC5031_CUR_B_SHIFT              16 // min.: -256, max.: 255, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M1 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_ALL_MASK             0x70 // CHOPCONF_M1 // fast decay time setting
#define TMC5031_TFD_ALL_SHIFT            4 // min.: 0, max.: 7, default: 0
#define TMC5031_OFFSET_MASK              0x0780 // CHOPCONF_M1 // sine wave offset
#define TMC5031_OFFSET_SHIFT             7 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_3_MASK               0x0800 // CHOPCONF_M1 // MSB of fast decay time setting
#define TMC5031_TFD_3_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_DISFDCC_MASK             0x1000 // CHOPCONF_M1 // fast decay mode
#define TMC5031_DISFDCC_SHIFT            12 // min.: 0, max.: 1, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M1 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M1 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M1 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M1 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M1 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M1 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M1 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M1 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M1 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_ALL_MASK             0x70 // CHOPCONF_M1 // fast decay time setting
#define TMC5031_TFD_ALL_SHIFT            4 // min.: 0, max.: 7, default: 0
#define TMC5031_OFFSET_MASK              0x0780 // CHOPCONF_M1 // sine wave offset
#define TMC5031_OFFSET_SHIFT             7 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_3_MASK               0x0800 // CHOPCONF_M1 // MSB of fast decay time setting
#define TMC5031_TFD_3_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_DISFDCC_MASK             0x1000 // CHOPCONF_M1 // fast decay mode
#define TMC5031_DISFDCC_SHIFT            12 // min.: 0, max.: 1, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M1 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M1 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M1 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M1 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M1 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M1 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M1 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M1 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M1 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M1 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_HSTRT_MASK               0x70 // CHOPCONF_M1 // hysteresis start value added to HEND; Attention: Effective HEND+HSTRT less than or equal to 16. Hint: Hysteresis decrement is done each 16 clocks
#define TMC5031_HSTRT_SHIFT              4 // min.: 0, max.: 7, default: 0
#define TMC5031_HEND_MASK                0x0780 // CHOPCONF_M1 // hysteresis low value
#define TMC5031_HEND_SHIFT               7 // min.: 0, max.: 15, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M1 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M1 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M1 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M1 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M1 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M1 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M1 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M1 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M1 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_SEMIN_MASK               0x0F // COOLCONF_M1 // minimum stallGuard2 value - If the stallGuard2 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle. 0: smart current control coolStep off
#define TMC5031_SEMIN_SHIFT              0 // min.: 0, max.: 15, default: 0
#define TMC5031_SEUP_MASK                0x60 // COOLCONF_M1 // Current increment steps per measured stallGuard2 value
#define TMC5031_SEUP_SHIFT               5 // min.: 0, max.: 3, default: 0
#define TMC5031_SEMAX_MASK               0x0F00 // COOLCONF_M1 // stallGuard2 hysteresis value - If the stallGuard2 result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.
#define TMC5031_SEMAX_SHIFT              8 // min.: 0, max.: 15, default: 0
#define TMC5031_SEDN_MASK                0x6000 // COOLCONF_M1 // Current down step speed; For each n stallGuard2 values decrease by one
#define TMC5031_SEDN_SHIFT               13 // min.: 0, max.: 3, default: 0
#define TMC5031_SEIMIN_MASK              0x8000 // COOLCONF_M1 // minimum current for smart current control
#define TMC5031_SEIMIN_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_SGT_MASK                 0x7F0000 // COOLCONF_M1 // stallGuard2 threshold value This signed value controls stallGuard2 level for stall output and sets the optimum measurement range for readout. A lower value gives a higher sensitivity. Zero is the starting value working with most motors. A higher value makes stallGuard2 less sensitive and requires more torque to indicate a stall.
#define TMC5031_SGT_SHIFT                16 // min.: -64, max.: 63, default: 0
#define TMC5031_SFILT_MASK               0x01000000 // COOLCONF_M1 // stallGuard2 filter enable
#define TMC5031_SFILT_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_SG_RESULT_MASK           0x03FF // DRV_STATUS_M1 // Mechanical load measurement: The stallGuard2 result gives a means to measure mechanical motor load. A higher value means lower mechanical load. A value of 0 signals highest load. With optimum SGT setting, this is an indicator for a motor stall. The stall detection compares SG_RESULT to 0 in order to detect a stall. SG_RESULT is used as a base for coolStep operation, by comparing it to a programmable upper and a lower limit. It is not applicable in stealthChop mode. SG_RESULT is ALSO applicable when dcStep is active. stallGuard2 works best with microstep operation. Temperature measurement: In standstill, no stallGuard2 result can be obtained. SG_RESULT shows the chopper on-time for motor coil A instead. If the motor is moved to a determined microstep position at a certain current setting, a comparison of the chopper on-time can help to get a rough estimation of motor temperature. As the motor heats up, its coil resistance rises and the chopper on-time increases.
#define TMC5031_SG_RESULT_SHIFT          0 // min.: 0, max.: 511, default: 0
#define TMC5031_FSACTIVE_MASK            0x8000 // DRV_STATUS_M1 //
#define TMC5031_FSACTIVE_SHIFT           15 // min.: 0, max.: 1, default: 0
#define TMC5031_CS_ACTUAL_MASK           0x1F0000 // DRV_STATUS_M1 //
#define TMC5031_CS_ACTUAL_SHIFT          16 // min.: 0, max.: 31, default: 0
#define TMC5031_STALLGUARD_MASK          0x01000000 // DRV_STATUS_M1 //
#define TMC5031_STALLGUARD_SHIFT         24 // min.: 0, max.: 1, default: 0
#define TMC5031_OT_MASK                  0x02000000 // DRV_STATUS_M1 //
#define TMC5031_OT_SHIFT                 25 // min.: 0, max.: 1, default: 0
#define TMC5031_OTPW_MASK                0x04000000 // DRV_STATUS_M1 //
#define TMC5031_OTPW_SHIFT               26 // min.: 0, max.: 1, default: 0
#define TMC5031_S2GA_MASK                0x08000000 // DRV_STATUS_M1 //
#define TMC5031_S2GA_SHIFT               27 // min.: 0, max.: 1, default: 0
#define TMC5031_S2GB_MASK                0x10000000 // DRV_STATUS_M1 //
#define TMC5031_S2GB_SHIFT               28 // min.: 0, max.: 1, default: 0
#define TMC5031_OLA_MASK                 0x20000000 // DRV_STATUS_M1 //
#define TMC5031_OLA_SHIFT                29 // min.: 0, max.: 1, default: 0
#define TMC5031_OLB_MASK                 0x40000000 // DRV_STATUS_M1 //
#define TMC5031_OLB_SHIFT                30 // min.: 0, max.: 1, default: 0
#define TMC5031_STST_MASK                0x80000000 // DRV_STATUS_M1 //
#define TMC5031_STST_SHIFT               31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS0_MASK                0x01 // MSLUT[0]_M2 // microstep table entry 0
#define TMC5031_OFS0_SHIFT               0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS1_MASK                0x02 // MSLUT[0]_M2 // microstep table entry 1
#define TMC5031_OFS1_SHIFT               1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS2_MASK                0x04 // MSLUT[0]_M2 // microstep table entry 2
#define TMC5031_OFS2_SHIFT               2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS3_MASK                0x08 // MSLUT[0]_M2 // microstep table entry 3
#define TMC5031_OFS3_SHIFT               3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS4_MASK                0x10 // MSLUT[0]_M2 // microstep table entry 4
#define TMC5031_OFS4_SHIFT               4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS5_MASK                0x20 // MSLUT[0]_M2 // microstep table entry 5
#define TMC5031_OFS5_SHIFT               5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS6_MASK                0x40 // MSLUT[0]_M2 // microstep table entry 6
#define TMC5031_OFS6_SHIFT               6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS7_MASK                0x80 // MSLUT[0]_M2 // microstep table entry 7
#define TMC5031_OFS7_SHIFT               7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS8_MASK                0x0100 // MSLUT[0]_M2 // microstep table entry 8
#define TMC5031_OFS8_SHIFT               8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS9_MASK                0x0200 // MSLUT[0]_M2 // microstep table entry 9
#define TMC5031_OFS9_SHIFT               9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS10_MASK               0x0400 // MSLUT[0]_M2 // microstep table entry 10
#define TMC5031_OFS10_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS11_MASK               0x0800 // MSLUT[0]_M2 // microstep table entry 11
#define TMC5031_OFS11_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS12_MASK               0x1000 // MSLUT[0]_M2 // microstep table entry 12
#define TMC5031_OFS12_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS13_MASK               0x2000 // MSLUT[0]_M2 // microstep table entry 13
#define TMC5031_OFS13_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS14_MASK               0x4000 // MSLUT[0]_M2 // microstep table entry 14
#define TMC5031_OFS14_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS15_MASK               0x8000 // MSLUT[0]_M2 // microstep table entry 15
#define TMC5031_OFS15_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS16_MASK               0x010000 // MSLUT[0]_M2 // microstep table entry 16
#define TMC5031_OFS16_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS17_MASK               0x020000 // MSLUT[0]_M2 // microstep table entry 17
#define TMC5031_OFS17_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS18_MASK               0x040000 // MSLUT[0]_M2 // microstep table entry 18
#define TMC5031_OFS18_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS19_MASK               0x080000 // MSLUT[0]_M2 // microstep table entry 19
#define TMC5031_OFS19_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS20_MASK               0x100000 // MSLUT[0]_M2 // microstep table entry 20
#define TMC5031_OFS20_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS21_MASK               0x200000 // MSLUT[0]_M2 // microstep table entry 21
#define TMC5031_OFS21_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS22_MASK               0x400000 // MSLUT[0]_M2 // microstep table entry 22
#define TMC5031_OFS22_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS23_MASK               0x800000 // MSLUT[0]_M2 // microstep table entry 23
#define TMC5031_OFS23_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS24_MASK               0x01000000 // MSLUT[0]_M2 // microstep table entry 24
#define TMC5031_OFS24_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS25_MASK               0x02000000 // MSLUT[0]_M2 // microstep table entry 25
#define TMC5031_OFS25_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS26_MASK               0x04000000 // MSLUT[0]_M2 // microstep table entry 26
#define TMC5031_OFS26_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS27_MASK               0x08000000 // MSLUT[0]_M2 // microstep table entry 27
#define TMC5031_OFS27_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS28_MASK               0x10000000 // MSLUT[0]_M2 // microstep table entry 28
#define TMC5031_OFS28_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS29_MASK               0x20000000 // MSLUT[0]_M2 // microstep table entry 29
#define TMC5031_OFS29_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS30_MASK               0x40000000 // MSLUT[0]_M2 // microstep table entry 30
#define TMC5031_OFS30_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS31_MASK               0x80000000 // MSLUT[0]_M2 // microstep table entry 31
#define TMC5031_OFS31_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS32_MASK               0x01 // MSLUT[1]_M2 // microstep table entry 32
#define TMC5031_OFS32_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS33_MASK               0x02 // MSLUT[1]_M2 // microstep table entry 33
#define TMC5031_OFS33_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS34_MASK               0x04 // MSLUT[1]_M2 // microstep table entry 34
#define TMC5031_OFS34_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS35_MASK               0x08 // MSLUT[1]_M2 // microstep table entry 35
#define TMC5031_OFS35_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS36_MASK               0x10 // MSLUT[1]_M2 // microstep table entry 36
#define TMC5031_OFS36_SHIFT              4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS37_MASK               0x20 // MSLUT[1]_M2 // microstep table entry 37
#define TMC5031_OFS37_SHIFT              5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS38_MASK               0x40 // MSLUT[1]_M2 // microstep table entry 38
#define TMC5031_OFS38_SHIFT              6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS39_MASK               0x80 // MSLUT[1]_M2 // microstep table entry 39
#define TMC5031_OFS39_SHIFT              7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS40_MASK               0x0100 // MSLUT[1]_M2 // microstep table entry 40
#define TMC5031_OFS40_SHIFT              8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS41_MASK               0x0200 // MSLUT[1]_M2 // microstep table entry 41
#define TMC5031_OFS41_SHIFT              9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS42_MASK               0x0400 // MSLUT[1]_M2 // microstep table entry 42
#define TMC5031_OFS42_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS43_MASK               0x0800 // MSLUT[1]_M2 // microstep table entry 43
#define TMC5031_OFS43_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS44_MASK               0x1000 // MSLUT[1]_M2 // microstep table entry 44
#define TMC5031_OFS44_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS45_MASK               0x2000 // MSLUT[1]_M2 // microstep table entry 45
#define TMC5031_OFS45_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS46_MASK               0x4000 // MSLUT[1]_M2 // microstep table entry 46
#define TMC5031_OFS46_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS47_MASK               0x8000 // MSLUT[1]_M2 // microstep table entry 47
#define TMC5031_OFS47_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS48_MASK               0x010000 // MSLUT[1]_M2 // microstep table entry 48
#define TMC5031_OFS48_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS49_MASK               0x020000 // MSLUT[1]_M2 // microstep table entry 49
#define TMC5031_OFS49_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS50_MASK               0x040000 // MSLUT[1]_M2 // microstep table entry 50
#define TMC5031_OFS50_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS51_MASK               0x080000 // MSLUT[1]_M2 // microstep table entry 51
#define TMC5031_OFS51_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS52_MASK               0x100000 // MSLUT[1]_M2 // microstep table entry 52
#define TMC5031_OFS52_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS53_MASK               0x200000 // MSLUT[1]_M2 // microstep table entry 53
#define TMC5031_OFS53_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS54_MASK               0x400000 // MSLUT[1]_M2 // microstep table entry 54
#define TMC5031_OFS54_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS55_MASK               0x800000 // MSLUT[1]_M2 // microstep table entry 55
#define TMC5031_OFS55_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS56_MASK               0x01000000 // MSLUT[1]_M2 // microstep table entry 56
#define TMC5031_OFS56_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS57_MASK               0x02000000 // MSLUT[1]_M2 // microstep table entry 57
#define TMC5031_OFS57_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS58_MASK               0x04000000 // MSLUT[1]_M2 // microstep table entry 58
#define TMC5031_OFS58_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS59_MASK               0x08000000 // MSLUT[1]_M2 // microstep table entry 59
#define TMC5031_OFS59_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS60_MASK               0x10000000 // MSLUT[1]_M2 // microstep table entry 60
#define TMC5031_OFS60_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS61_MASK               0x20000000 // MSLUT[1]_M2 // microstep table entry 61
#define TMC5031_OFS61_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS62_MASK               0x40000000 // MSLUT[1]_M2 // microstep table entry 62
#define TMC5031_OFS62_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS63_MASK               0x80000000 // MSLUT[1]_M2 // microstep table entry 63
#define TMC5031_OFS63_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS64_MASK               0x01 // MSLUT[2]_M2 // microstep table entry 64
#define TMC5031_OFS64_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS65_MASK               0x02 // MSLUT[2]_M2 // microstep table entry 65
#define TMC5031_OFS65_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS66_MASK               0x04 // MSLUT[2]_M2 // microstep table entry 66
#define TMC5031_OFS66_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS67_MASK               0x08 // MSLUT[2]_M2 // microstep table entry 67
#define TMC5031_OFS67_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS68_MASK               0x10 // MSLUT[2]_M2 // microstep table entry 68
#define TMC5031_OFS68_SHIFT              4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS69_MASK               0x20 // MSLUT[2]_M2 // microstep table entry 69
#define TMC5031_OFS69_SHIFT              5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS70_MASK               0x40 // MSLUT[2]_M2 // microstep table entry 70
#define TMC5031_OFS70_SHIFT              6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS71_MASK               0x80 // MSLUT[2]_M2 // microstep table entry 71
#define TMC5031_OFS71_SHIFT              7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS72_MASK               0x0100 // MSLUT[2]_M2 // microstep table entry 72
#define TMC5031_OFS72_SHIFT              8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS73_MASK               0x0200 // MSLUT[2]_M2 // microstep table entry 73
#define TMC5031_OFS73_SHIFT              9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS74_MASK               0x0400 // MSLUT[2]_M2 // microstep table entry 74
#define TMC5031_OFS74_SHIFT              10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS75_MASK               0x0800 // MSLUT[2]_M2 // microstep table entry 75
#define TMC5031_OFS75_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS76_MASK               0x1000 // MSLUT[2]_M2 // microstep table entry 76
#define TMC5031_OFS76_SHIFT              12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS77_MASK               0x2000 // MSLUT[2]_M2 // microstep table entry 77
#define TMC5031_OFS77_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS78_MASK               0x4000 // MSLUT[2]_M2 // microstep table entry 78
#define TMC5031_OFS78_SHIFT              14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS79_MASK               0x8000 // MSLUT[2]_M2 // microstep table entry 79
#define TMC5031_OFS79_SHIFT              15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS80_MASK               0x010000 // MSLUT[2]_M2 // microstep table entry 80
#define TMC5031_OFS80_SHIFT              16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS81_MASK               0x020000 // MSLUT[2]_M2 // microstep table entry 81
#define TMC5031_OFS81_SHIFT              17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS82_MASK               0x040000 // MSLUT[2]_M2 // microstep table entry 82
#define TMC5031_OFS82_SHIFT              18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS83_MASK               0x080000 // MSLUT[2]_M2 // microstep table entry 83
#define TMC5031_OFS83_SHIFT              19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS84_MASK               0x100000 // MSLUT[2]_M2 // microstep table entry 84
#define TMC5031_OFS84_SHIFT              20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS85_MASK               0x200000 // MSLUT[2]_M2 // microstep table entry 85
#define TMC5031_OFS85_SHIFT              21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS86_MASK               0x400000 // MSLUT[2]_M2 // microstep table entry 86
#define TMC5031_OFS86_SHIFT              22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS87_MASK               0x800000 // MSLUT[2]_M2 // microstep table entry 87
#define TMC5031_OFS87_SHIFT              23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS88_MASK               0x01000000 // MSLUT[2]_M2 // microstep table entry 88
#define TMC5031_OFS88_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS89_MASK               0x02000000 // MSLUT[2]_M2 // microstep table entry 89
#define TMC5031_OFS89_SHIFT              25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS90_MASK               0x04000000 // MSLUT[2]_M2 // microstep table entry 90
#define TMC5031_OFS90_SHIFT              26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS91_MASK               0x08000000 // MSLUT[2]_M2 // microstep table entry 91
#define TMC5031_OFS91_SHIFT              27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS92_MASK               0x10000000 // MSLUT[2]_M2 // microstep table entry 92
#define TMC5031_OFS92_SHIFT              28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS93_MASK               0x20000000 // MSLUT[2]_M2 // microstep table entry 93
#define TMC5031_OFS93_SHIFT              29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS94_MASK               0x40000000 // MSLUT[2]_M2 // microstep table entry 94
#define TMC5031_OFS94_SHIFT              30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS95_MASK               0x80000000 // MSLUT[2]_M2 // microstep table entry 95
#define TMC5031_OFS95_SHIFT              31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS96_MASK               0x01 // MSLUT[3]_M2 // microstep table entry 96
#define TMC5031_OFS96_SHIFT              0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS97_MASK               0x02 // MSLUT[3]_M2 // microstep table entry 97
#define TMC5031_OFS97_SHIFT              1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS98_MASK               0x04 // MSLUT[3]_M2 // microstep table entry 98
#define TMC5031_OFS98_SHIFT              2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS99_MASK               0x08 // MSLUT[3]_M2 // microstep table entry 99
#define TMC5031_OFS99_SHIFT              3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS100_MASK              0x10 // MSLUT[3]_M2 // microstep table entry 100
#define TMC5031_OFS100_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS101_MASK              0x20 // MSLUT[3]_M2 // microstep table entry 101
#define TMC5031_OFS101_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS102_MASK              0x40 // MSLUT[3]_M2 // microstep table entry 102
#define TMC5031_OFS102_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS103_MASK              0x80 // MSLUT[3]_M2 // microstep table entry 103
#define TMC5031_OFS103_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS104_MASK              0x0100 // MSLUT[3]_M2 // microstep table entry 104
#define TMC5031_OFS104_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS105_MASK              0x0200 // MSLUT[3]_M2 // microstep table entry 105
#define TMC5031_OFS105_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS106_MASK              0x0400 // MSLUT[3]_M2 // microstep table entry 106
#define TMC5031_OFS106_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS107_MASK              0x0800 // MSLUT[3]_M2 // microstep table entry 107
#define TMC5031_OFS107_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS108_MASK              0x1000 // MSLUT[3]_M2 // microstep table entry 108
#define TMC5031_OFS108_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS109_MASK              0x2000 // MSLUT[3]_M2 // microstep table entry 109
#define TMC5031_OFS109_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS110_MASK              0x4000 // MSLUT[3]_M2 // microstep table entry 110
#define TMC5031_OFS110_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS111_MASK              0x8000 // MSLUT[3]_M2 // microstep table entry 111
#define TMC5031_OFS111_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS112_MASK              0x010000 // MSLUT[3]_M2 // microstep table entry 112
#define TMC5031_OFS112_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS113_MASK              0x020000 // MSLUT[3]_M2 // microstep table entry 113
#define TMC5031_OFS113_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS114_MASK              0x040000 // MSLUT[3]_M2 // microstep table entry 114
#define TMC5031_OFS114_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS115_MASK              0x080000 // MSLUT[3]_M2 // microstep table entry 115
#define TMC5031_OFS115_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS116_MASK              0x100000 // MSLUT[3]_M2 // microstep table entry 116
#define TMC5031_OFS116_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS117_MASK              0x200000 // MSLUT[3]_M2 // microstep table entry 117
#define TMC5031_OFS117_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS118_MASK              0x400000 // MSLUT[3]_M2 // microstep table entry 118
#define TMC5031_OFS118_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS119_MASK              0x800000 // MSLUT[3]_M2 // microstep table entry 119
#define TMC5031_OFS119_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS120_MASK              0x01000000 // MSLUT[3]_M2 // microstep table entry 120
#define TMC5031_OFS120_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS121_MASK              0x02000000 // MSLUT[3]_M2 // microstep table entry 121
#define TMC5031_OFS121_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS122_MASK              0x04000000 // MSLUT[3]_M2 // microstep table entry 122
#define TMC5031_OFS122_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS123_MASK              0x08000000 // MSLUT[3]_M2 // microstep table entry 123
#define TMC5031_OFS123_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS124_MASK              0x10000000 // MSLUT[3]_M2 // microstep table entry 124
#define TMC5031_OFS124_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS125_MASK              0x20000000 // MSLUT[3]_M2 // microstep table entry 125
#define TMC5031_OFS125_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS126_MASK              0x40000000 // MSLUT[3]_M2 // microstep table entry 126
#define TMC5031_OFS126_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS127_MASK              0x80000000 // MSLUT[3]_M2 // microstep table entry 127
#define TMC5031_OFS127_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS128_MASK              0x01 // MSLUT[4]_M2 // microstep table entry 128
#define TMC5031_OFS128_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS129_MASK              0x02 // MSLUT[4]_M2 // microstep table entry 129
#define TMC5031_OFS129_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS130_MASK              0x04 // MSLUT[4]_M2 // microstep table entry 130
#define TMC5031_OFS130_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS131_MASK              0x08 // MSLUT[4]_M2 // microstep table entry 131
#define TMC5031_OFS131_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS132_MASK              0x10 // MSLUT[4]_M2 // microstep table entry 132
#define TMC5031_OFS132_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS133_MASK              0x20 // MSLUT[4]_M2 // microstep table entry 133
#define TMC5031_OFS133_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS134_MASK              0x40 // MSLUT[4]_M2 // microstep table entry 134
#define TMC5031_OFS134_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS135_MASK              0x80 // MSLUT[4]_M2 // microstep table entry 135
#define TMC5031_OFS135_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS136_MASK              0x0100 // MSLUT[4]_M2 // microstep table entry 136
#define TMC5031_OFS136_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS137_MASK              0x0200 // MSLUT[4]_M2 // microstep table entry 137
#define TMC5031_OFS137_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS138_MASK              0x0400 // MSLUT[4]_M2 // microstep table entry 138
#define TMC5031_OFS138_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS139_MASK              0x0800 // MSLUT[4]_M2 // microstep table entry 139
#define TMC5031_OFS139_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS140_MASK              0x1000 // MSLUT[4]_M2 // microstep table entry 140
#define TMC5031_OFS140_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS141_MASK              0x2000 // MSLUT[4]_M2 // microstep table entry 141
#define TMC5031_OFS141_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS142_MASK              0x4000 // MSLUT[4]_M2 // microstep table entry 142
#define TMC5031_OFS142_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS143_MASK              0x8000 // MSLUT[4]_M2 // microstep table entry 143
#define TMC5031_OFS143_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS144_MASK              0x010000 // MSLUT[4]_M2 // microstep table entry 144
#define TMC5031_OFS144_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS145_MASK              0x020000 // MSLUT[4]_M2 // microstep table entry 145
#define TMC5031_OFS145_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS146_MASK              0x040000 // MSLUT[4]_M2 // microstep table entry 146
#define TMC5031_OFS146_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS147_MASK              0x080000 // MSLUT[4]_M2 // microstep table entry 147
#define TMC5031_OFS147_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS148_MASK              0x100000 // MSLUT[4]_M2 // microstep table entry 148
#define TMC5031_OFS148_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS149_MASK              0x200000 // MSLUT[4]_M2 // microstep table entry 149
#define TMC5031_OFS149_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS150_MASK              0x400000 // MSLUT[4]_M2 // microstep table entry 150
#define TMC5031_OFS150_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS151_MASK              0x800000 // MSLUT[4]_M2 // microstep table entry 151
#define TMC5031_OFS151_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS152_MASK              0x01000000 // MSLUT[4]_M2 // microstep table entry 152
#define TMC5031_OFS152_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS153_MASK              0x02000000 // MSLUT[4]_M2 // microstep table entry 153
#define TMC5031_OFS153_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS154_MASK              0x04000000 // MSLUT[4]_M2 // microstep table entry 154
#define TMC5031_OFS154_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS155_MASK              0x08000000 // MSLUT[4]_M2 // microstep table entry 155
#define TMC5031_OFS155_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS156_MASK              0x10000000 // MSLUT[4]_M2 // microstep table entry 156
#define TMC5031_OFS156_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS157_MASK              0x20000000 // MSLUT[4]_M2 // microstep table entry 157
#define TMC5031_OFS157_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS158_MASK              0x40000000 // MSLUT[4]_M2 // microstep table entry 158
#define TMC5031_OFS158_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS159_MASK              0x80000000 // MSLUT[4]_M2 // microstep table entry 159
#define TMC5031_OFS159_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS160_MASK              0x01 // MSLUT[5]_M2 // microstep table entry 160
#define TMC5031_OFS160_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS161_MASK              0x02 // MSLUT[5]_M2 // microstep table entry 161
#define TMC5031_OFS161_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS162_MASK              0x04 // MSLUT[5]_M2 // microstep table entry 162
#define TMC5031_OFS162_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS163_MASK              0x08 // MSLUT[5]_M2 // microstep table entry 163
#define TMC5031_OFS163_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS164_MASK              0x10 // MSLUT[5]_M2 // microstep table entry 164
#define TMC5031_OFS164_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS165_MASK              0x20 // MSLUT[5]_M2 // microstep table entry 165
#define TMC5031_OFS165_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS166_MASK              0x40 // MSLUT[5]_M2 // microstep table entry 166
#define TMC5031_OFS166_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS167_MASK              0x80 // MSLUT[5]_M2 // microstep table entry 167
#define TMC5031_OFS167_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS168_MASK              0x0100 // MSLUT[5]_M2 // microstep table entry 168
#define TMC5031_OFS168_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS169_MASK              0x0200 // MSLUT[5]_M2 // microstep table entry 169
#define TMC5031_OFS169_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS170_MASK              0x0400 // MSLUT[5]_M2 // microstep table entry 170
#define TMC5031_OFS170_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS171_MASK              0x0800 // MSLUT[5]_M2 // microstep table entry 171
#define TMC5031_OFS171_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS172_MASK              0x1000 // MSLUT[5]_M2 // microstep table entry 172
#define TMC5031_OFS172_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS173_MASK              0x2000 // MSLUT[5]_M2 // microstep table entry 173
#define TMC5031_OFS173_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS174_MASK              0x4000 // MSLUT[5]_M2 // microstep table entry 174
#define TMC5031_OFS174_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS175_MASK              0x8000 // MSLUT[5]_M2 // microstep table entry 175
#define TMC5031_OFS175_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS176_MASK              0x010000 // MSLUT[5]_M2 // microstep table entry 176
#define TMC5031_OFS176_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS177_MASK              0x020000 // MSLUT[5]_M2 // microstep table entry 177
#define TMC5031_OFS177_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS178_MASK              0x040000 // MSLUT[5]_M2 // microstep table entry 178
#define TMC5031_OFS178_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS179_MASK              0x080000 // MSLUT[5]_M2 // microstep table entry 179
#define TMC5031_OFS179_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS180_MASK              0x100000 // MSLUT[5]_M2 // microstep table entry 180
#define TMC5031_OFS180_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS181_MASK              0x200000 // MSLUT[5]_M2 // microstep table entry 181
#define TMC5031_OFS181_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS182_MASK              0x400000 // MSLUT[5]_M2 // microstep table entry 182
#define TMC5031_OFS182_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS183_MASK              0x800000 // MSLUT[5]_M2 // microstep table entry 183
#define TMC5031_OFS183_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS184_MASK              0x01000000 // MSLUT[5]_M2 // microstep table entry 184
#define TMC5031_OFS184_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS185_MASK              0x02000000 // MSLUT[5]_M2 // microstep table entry 185
#define TMC5031_OFS185_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS186_MASK              0x04000000 // MSLUT[5]_M2 // microstep table entry 186
#define TMC5031_OFS186_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS187_MASK              0x08000000 // MSLUT[5]_M2 // microstep table entry 187
#define TMC5031_OFS187_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS188_MASK              0x10000000 // MSLUT[5]_M2 // microstep table entry 188
#define TMC5031_OFS188_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS189_MASK              0x20000000 // MSLUT[5]_M2 // microstep table entry 189
#define TMC5031_OFS189_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS190_MASK              0x40000000 // MSLUT[5]_M2 // microstep table entry 190
#define TMC5031_OFS190_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS191_MASK              0x80000000 // MSLUT[5]_M2 // microstep table entry 191
#define TMC5031_OFS191_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS192_MASK              0x01 // MSLUT[6]_M2 // microstep table entry 192
#define TMC5031_OFS192_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS193_MASK              0x02 // MSLUT[6]_M2 // microstep table entry 193
#define TMC5031_OFS193_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS194_MASK              0x04 // MSLUT[6]_M2 // microstep table entry 194
#define TMC5031_OFS194_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS195_MASK              0x08 // MSLUT[6]_M2 // microstep table entry 195
#define TMC5031_OFS195_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS196_MASK              0x10 // MSLUT[6]_M2 // microstep table entry 196
#define TMC5031_OFS196_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS197_MASK              0x20 // MSLUT[6]_M2 // microstep table entry 197
#define TMC5031_OFS197_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS198_MASK              0x40 // MSLUT[6]_M2 // microstep table entry 198
#define TMC5031_OFS198_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS199_MASK              0x80 // MSLUT[6]_M2 // microstep table entry 199
#define TMC5031_OFS199_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS200_MASK              0x0100 // MSLUT[6]_M2 // microstep table entry 200
#define TMC5031_OFS200_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS201_MASK              0x0200 // MSLUT[6]_M2 // microstep table entry 201
#define TMC5031_OFS201_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS202_MASK              0x0400 // MSLUT[6]_M2 // microstep table entry 202
#define TMC5031_OFS202_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS203_MASK              0x0800 // MSLUT[6]_M2 // microstep table entry 203
#define TMC5031_OFS203_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS204_MASK              0x1000 // MSLUT[6]_M2 // microstep table entry 204
#define TMC5031_OFS204_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS205_MASK              0x2000 // MSLUT[6]_M2 // microstep table entry 205
#define TMC5031_OFS205_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS206_MASK              0x4000 // MSLUT[6]_M2 // microstep table entry 206
#define TMC5031_OFS206_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS207_MASK              0x8000 // MSLUT[6]_M2 // microstep table entry 207
#define TMC5031_OFS207_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS208_MASK              0x010000 // MSLUT[6]_M2 // microstep table entry 208
#define TMC5031_OFS208_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS209_MASK              0x020000 // MSLUT[6]_M2 // microstep table entry 209
#define TMC5031_OFS209_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS210_MASK              0x040000 // MSLUT[6]_M2 // microstep table entry 210
#define TMC5031_OFS210_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS211_MASK              0x080000 // MSLUT[6]_M2 // microstep table entry 211
#define TMC5031_OFS211_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS212_MASK              0x100000 // MSLUT[6]_M2 // microstep table entry 212
#define TMC5031_OFS212_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS213_MASK              0x200000 // MSLUT[6]_M2 // microstep table entry 213
#define TMC5031_OFS213_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS214_MASK              0x400000 // MSLUT[6]_M2 // microstep table entry 214
#define TMC5031_OFS214_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS215_MASK              0x800000 // MSLUT[6]_M2 // microstep table entry 215
#define TMC5031_OFS215_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS216_MASK              0x01000000 // MSLUT[6]_M2 // microstep table entry 216
#define TMC5031_OFS216_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS217_MASK              0x02000000 // MSLUT[6]_M2 // microstep table entry 217
#define TMC5031_OFS217_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS218_MASK              0x04000000 // MSLUT[6]_M2 // microstep table entry 218
#define TMC5031_OFS218_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS219_MASK              0x08000000 // MSLUT[6]_M2 // microstep table entry 219
#define TMC5031_OFS219_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS220_MASK              0x10000000 // MSLUT[6]_M2 // microstep table entry 220
#define TMC5031_OFS220_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS221_MASK              0x20000000 // MSLUT[6]_M2 // microstep table entry 221
#define TMC5031_OFS221_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS222_MASK              0x40000000 // MSLUT[6]_M2 // microstep table entry 222
#define TMC5031_OFS222_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS223_MASK              0x80000000 // MSLUT[6]_M2 // microstep table entry 223
#define TMC5031_OFS223_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS224_MASK              0x01 // MSLUT[7]_M2 // microstep table entry 224
#define TMC5031_OFS224_SHIFT             0 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS225_MASK              0x02 // MSLUT[7]_M2 // microstep table entry 225
#define TMC5031_OFS225_SHIFT             1 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS226_MASK              0x04 // MSLUT[7]_M2 // microstep table entry 226
#define TMC5031_OFS226_SHIFT             2 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS227_MASK              0x08 // MSLUT[7]_M2 // microstep table entry 227
#define TMC5031_OFS227_SHIFT             3 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS228_MASK              0x10 // MSLUT[7]_M2 // microstep table entry 228
#define TMC5031_OFS228_SHIFT             4 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS229_MASK              0x20 // MSLUT[7]_M2 // microstep table entry 229
#define TMC5031_OFS229_SHIFT             5 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS230_MASK              0x40 // MSLUT[7]_M2 // microstep table entry 230
#define TMC5031_OFS230_SHIFT             6 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS231_MASK              0x80 // MSLUT[7]_M2 // microstep table entry 231
#define TMC5031_OFS231_SHIFT             7 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS232_MASK              0x0100 // MSLUT[7]_M2 // microstep table entry 232
#define TMC5031_OFS232_SHIFT             8 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS233_MASK              0x0200 // MSLUT[7]_M2 // microstep table entry 233
#define TMC5031_OFS233_SHIFT             9 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS234_MASK              0x0400 // MSLUT[7]_M2 // microstep table entry 234
#define TMC5031_OFS234_SHIFT             10 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS235_MASK              0x0800 // MSLUT[7]_M2 // microstep table entry 235
#define TMC5031_OFS235_SHIFT             11 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS236_MASK              0x1000 // MSLUT[7]_M2 // microstep table entry 236
#define TMC5031_OFS236_SHIFT             12 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS237_MASK              0x2000 // MSLUT[7]_M2 // microstep table entry 237
#define TMC5031_OFS237_SHIFT             13 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS238_MASK              0x4000 // MSLUT[7]_M2 // microstep table entry 238
#define TMC5031_OFS238_SHIFT             14 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS239_MASK              0x8000 // MSLUT[7]_M2 // microstep table entry 239
#define TMC5031_OFS239_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS240_MASK              0x010000 // MSLUT[7]_M2 // microstep table entry 240
#define TMC5031_OFS240_SHIFT             16 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS241_MASK              0x020000 // MSLUT[7]_M2 // microstep table entry 241
#define TMC5031_OFS241_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS242_MASK              0x040000 // MSLUT[7]_M2 // microstep table entry 242
#define TMC5031_OFS242_SHIFT             18 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS243_MASK              0x080000 // MSLUT[7]_M2 // microstep table entry 243
#define TMC5031_OFS243_SHIFT             19 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS244_MASK              0x100000 // MSLUT[7]_M2 // microstep table entry 244
#define TMC5031_OFS244_SHIFT             20 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS245_MASK              0x200000 // MSLUT[7]_M2 // microstep table entry 245
#define TMC5031_OFS245_SHIFT             21 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS246_MASK              0x400000 // MSLUT[7]_M2 // microstep table entry 246
#define TMC5031_OFS246_SHIFT             22 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS247_MASK              0x800000 // MSLUT[7]_M2 // microstep table entry 247
#define TMC5031_OFS247_SHIFT             23 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS248_MASK              0x01000000 // MSLUT[7]_M2 // microstep table entry 248
#define TMC5031_OFS248_SHIFT             24 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS249_MASK              0x02000000 // MSLUT[7]_M2 // microstep table entry 249
#define TMC5031_OFS249_SHIFT             25 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS250_MASK              0x04000000 // MSLUT[7]_M2 // microstep table entry 250
#define TMC5031_OFS250_SHIFT             26 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS251_MASK              0x08000000 // MSLUT[7]_M2 // microstep table entry 251
#define TMC5031_OFS251_SHIFT             27 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS252_MASK              0x10000000 // MSLUT[7]_M2 // microstep table entry 252
#define TMC5031_OFS252_SHIFT             28 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS253_MASK              0x20000000 // MSLUT[7]_M2 // microstep table entry 253
#define TMC5031_OFS253_SHIFT             29 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS254_MASK              0x40000000 // MSLUT[7]_M2 // microstep table entry 254
#define TMC5031_OFS254_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_OFS255_MASK              0x80000000 // MSLUT[7]_M2 // microstep table entry 255
#define TMC5031_OFS255_SHIFT             31 // min.: 0, max.: 1, default: 0
#define TMC5031_W0_MASK                  0x03 // MSLUTSEL_M2 // LUT width select from ofs0 to ofs(X1-1)
#define TMC5031_W0_SHIFT                 0 // min.: 0, max.: 3, default: 0
#define TMC5031_W1_MASK                  0x0C // MSLUTSEL_M2 // LUT width select from ofs(X1) to ofs(X2-1)
#define TMC5031_W1_SHIFT                 2 // min.: 0, max.: 3, default: 0
#define TMC5031_W2_MASK                  0x30 // MSLUTSEL_M2 // LUT width select from ofs(X2) to ofs(X3-1)
#define TMC5031_W2_SHIFT                 4 // min.: 0, max.: 3, default: 0
#define TMC5031_W3_MASK                  0xC0 // MSLUTSEL_M2 // LUT width select from ofs(X3) to ofs255
#define TMC5031_W3_SHIFT                 6 // min.: 0, max.: 3, default: 0
#define TMC5031_X1_MASK                  0xFF00 // MSLUTSEL_M2 // LUT segment 1 start
#define TMC5031_X1_SHIFT                 8 // min.: 0, max.: 255, default: 0
#define TMC5031_X2_MASK                  0xFF0000 // MSLUTSEL_M2 // LUT segment 2 start
#define TMC5031_X2_SHIFT                 16 // min.: 0, max.: 255, default: 0
#define TMC5031_X3_MASK                  0xFF000000 // MSLUTSEL_M2 // LUT segment 3 start
#define TMC5031_X3_SHIFT                 24 // min.: 0, max.: 255, default: 0
#define TMC5031_START_SIN_MASK           0xFF // MSLUTSTART_M2 // Absolute current at microstep table entry 0.
#define TMC5031_START_SIN_SHIFT          0 // min.: 0, max.: 255, default: 0
#define TMC5031_START_SIN90_MASK         0xFF0000 // MSLUTSTART_M2 // Absolute current for microstep table entry at positions 256.
#define TMC5031_START_SIN90_SHIFT        16 // min.: 0, max.: 255, default: 0
#define TMC5031_MSCNT_MASK               0x03FF // MSCNT_M2 // Microstep counter. Indicates actual position in the microstep table for CUR_A. CUR_B uses an offset of 256 (2 phase motor). Hint: Move to a position where MSCNT is zero before re-initializing MSLUTSTART or MSLUT and MSLUTSEL.
#define TMC5031_MSCNT_SHIFT              0 // min.: 0, max.: 1023, default: 0
#define TMC5031_CUR_A_MASK               0x01FF // MSCURACT_M2 // Actual microstep current for motor phase A as read from MSLUT (not scaled by current)
#define TMC5031_CUR_A_SHIFT              0 // min.: -256, max.: 255, default: 0
#define TMC5031_CUR_B_MASK               0x01FF0000 // MSCURACT_M2 // Actual microstep current for motor phase B as read from MSLUT (not scaled by current)
#define TMC5031_CUR_B_SHIFT              16 // min.: -256, max.: 255, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M2 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_ALL_MASK             0x70 // CHOPCONF_M2 // fast decay time setting
#define TMC5031_TFD_ALL_SHIFT            4 // min.: 0, max.: 7, default: 0
#define TMC5031_OFFSET_MASK              0x0780 // CHOPCONF_M2 // sine wave offset
#define TMC5031_OFFSET_SHIFT             7 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_3_MASK               0x0800 // CHOPCONF_M2 // MSB of fast decay time setting
#define TMC5031_TFD_3_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_DISFDCC_MASK             0x1000 // CHOPCONF_M2 // fast decay mode
#define TMC5031_DISFDCC_SHIFT            12 // min.: 0, max.: 1, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M2 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M2 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M2 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M2 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M2 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M2 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M2 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M2 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M2 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M2 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_ALL_MASK             0x70 // CHOPCONF_M2 // fast decay time setting
#define TMC5031_TFD_ALL_SHIFT            4 // min.: 0, max.: 7, default: 0
#define TMC5031_OFFSET_MASK              0x0780 // CHOPCONF_M2 // sine wave offset
#define TMC5031_OFFSET_SHIFT             7 // min.: 0, max.: 15, default: 0
#define TMC5031_TFD_3_MASK               0x0800 // CHOPCONF_M2 // MSB of fast decay time setting
#define TMC5031_TFD_3_SHIFT              11 // min.: 0, max.: 1, default: 0
#define TMC5031_DISFDCC_MASK             0x1000 // CHOPCONF_M2 // fast decay mode
#define TMC5031_DISFDCC_SHIFT            12 // min.: 0, max.: 1, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M2 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M2 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M2 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M2 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M2 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M2 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M2 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M2 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M2 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_TOFF_MASK                0x0F // CHOPCONF_M2 // off time and driver enable
#define TMC5031_TOFF_SHIFT               0 // min.: 0, max.: 15, default: 0
#define TMC5031_HSTRT_MASK               0x70 // CHOPCONF_M2 // hysteresis start value added to HEND; Attention: Effective HEND+HSTRT less than or equal to 16. Hint: Hysteresis decrement is done each 16 clocks
#define TMC5031_HSTRT_SHIFT              4 // min.: 0, max.: 7, default: 0
#define TMC5031_HEND_MASK                0x0780 // CHOPCONF_M2 // hysteresis low value
#define TMC5031_HEND_SHIFT               7 // min.: 0, max.: 15, default: 0
#define TMC5031_RNDTF_MASK               0x2000 // CHOPCONF_M2 // random TOFF time
#define TMC5031_RNDTF_SHIFT              13 // min.: 0, max.: 1, default: 0
#define TMC5031_CHM_MASK                 0x4000 // CHOPCONF_M2 // chopper mode
#define TMC5031_CHM_SHIFT                14 // min.: 0, max.: 1, default: 0
#define TMC5031_TBL_MASK                 0x018000 // CHOPCONF_M2 // blank time select
#define TMC5031_TBL_SHIFT                15 // min.: 0, max.: 3, default: 0
#define TMC5031_VSENSE_MASK              0x020000 // CHOPCONF_M2 // sense resistor voltage based current scaling
#define TMC5031_VSENSE_SHIFT             17 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHFS_MASK             0x040000 // CHOPCONF_M2 // high velocity fullstep selection
#define TMC5031_VHIGHFS_SHIFT            18 // min.: 0, max.: 1, default: 0
#define TMC5031_VHIGHCHM_MASK            0x080000 // CHOPCONF_M2 // high velocity chopper mode
#define TMC5031_VHIGHCHM_SHIFT           19 // min.: 0, max.: 1, default: 0
#define TMC5031_SYNC_MASK                0xF00000 // CHOPCONF_M2 // PWM synchronization clock
#define TMC5031_SYNC_SHIFT               20 // min.: 0, max.: 15, default: 0
#define TMC5031_MRES_MASK                0x0F000000 // CHOPCONF_M2 // Microstep Resolution (manually added)
#define TMC5031_MRES_SHIFT               24 // min.: 1, max.: 256, default: 256
#define TMC5031_DISS2G_MASK              0x40000000 // CHOPCONF_M2 // short to GND protection disable
#define TMC5031_DISS2G_SHIFT             30 // min.: 0, max.: 1, default: 0
#define TMC5031_SEMIN_MASK               0x0F // COOLCONF_M2 // minimum stallGuard2 value - If the stallGuard2 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle. 0: smart current control coolStep off
#define TMC5031_SEMIN_SHIFT              0 // min.: 0, max.: 15, default: 0
#define TMC5031_SEUP_MASK                0x60 // COOLCONF_M2 // Current increment steps per measured stallGuard2 value
#define TMC5031_SEUP_SHIFT               5 // min.: 0, max.: 3, default: 0
#define TMC5031_SEMAX_MASK               0x0F00 // COOLCONF_M2 // stallGuard2 hysteresis value - If the stallGuard2 result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.
#define TMC5031_SEMAX_SHIFT              8 // min.: 0, max.: 15, default: 0
#define TMC5031_SEDN_MASK                0x6000 // COOLCONF_M2 // Current down step speed; For each n stallGuard2 values decrease by one
#define TMC5031_SEDN_SHIFT               13 // min.: 0, max.: 3, default: 0
#define TMC5031_SEIMIN_MASK              0x8000 // COOLCONF_M2 // minimum current for smart current control
#define TMC5031_SEIMIN_SHIFT             15 // min.: 0, max.: 1, default: 0
#define TMC5031_SGT_MASK                 0x7F0000 // COOLCONF_M2 // stallGuard2 threshold value This signed value controls stallGuard2 level for stall output and sets the optimum measurement range for readout. A lower value gives a higher sensitivity. Zero is the starting value working with most motors. A higher value makes stallGuard2 less sensitive and requires more torque to indicate a stall.
#define TMC5031_SGT_SHIFT                16 // min.: -64, max.: 63, default: 0
#define TMC5031_SFILT_MASK               0x01000000 // COOLCONF_M2 // stallGuard2 filter enable
#define TMC5031_SFILT_SHIFT              24 // min.: 0, max.: 1, default: 0
#define TMC5031_SG_RESULT_MASK           0x03FF // DRV_STATUS_M2 // Mechanical load measurement: The stallGuard2 result gives a means to measure mechanical motor load. A higher value means lower mechanical load. A value of 0 signals highest load. With optimum SGT setting, this is an indicator for a motor stall. The stall detection compares SG_RESULT to 0 in order to detect a stall. SG_RESULT is used as a base for coolStep operation, by comparing it to a programmable upper and a lower limit. It is not applicable in stealthChop mode. SG_RESULT is ALSO applicable when dcStep is active. stallGuard2 works best with microstep operation. Temperature measurement: In standstill, no stallGuard2 result can be obtained. SG_RESULT shows the chopper on-time for motor coil A instead. If the motor is moved to a determined microstep position at a certain current setting, a comparison of the chopper on-time can help to get a rough estimation of motor temperature. As the motor heats up, its coil resistance rises and the chopper on-time increases.
#define TMC5031_SG_RESULT_SHIFT          0 // min.: 0, max.: 511, default: 0
#define TMC5031_FSACTIVE_MASK            0x8000 // DRV_STATUS_M2 //
#define TMC5031_FSACTIVE_SHIFT           15 // min.: 0, max.: 1, default: 0
#define TMC5031_CS_ACTUAL_MASK           0x1F0000 // DRV_STATUS_M2 //
#define TMC5031_CS_ACTUAL_SHIFT          16 // min.: 0, max.: 31, default: 0
#define TMC5031_STALLGUARD_MASK          0x01000000 // DRV_STATUS_M2 //
#define TMC5031_STALLGUARD_SHIFT         24 // min.: 0, max.: 1, default: 0
#define TMC5031_OT_MASK                  0x02000000 // DRV_STATUS_M2 //
#define TMC5031_OT_SHIFT                 25 // min.: 0, max.: 1, default: 0
#define TMC5031_OTPW_MASK                0x04000000 // DRV_STATUS_M2 //
#define TMC5031_OTPW_SHIFT               26 // min.: 0, max.: 1, default: 0
#define TMC5031_S2GA_MASK                0x08000000 // DRV_STATUS_M2 //
#define TMC5031_S2GA_SHIFT               27 // min.: 0, max.: 1, default: 0
#define TMC5031_S2GB_MASK                0x10000000 // DRV_STATUS_M2 //
#define TMC5031_S2GB_SHIFT               28 // min.: 0, max.: 1, default: 0
#define TMC5031_OLA_MASK                 0x20000000 // DRV_STATUS_M2 //
#define TMC5031_OLA_SHIFT                29 // min.: 0, max.: 1, default: 0
#define TMC5031_OLB_MASK                 0x40000000 // DRV_STATUS_M2 //
#define TMC5031_OLB_SHIFT                30 // min.: 0, max.: 1, default: 0
#define TMC5031_STST_MASK                0x80000000 // DRV_STATUS_M2 //
#define TMC5031_STST_SHIFT               31 // min.: 0, max.: 1, default: 0

#endif /* TMC5031_FIELDS_H */
