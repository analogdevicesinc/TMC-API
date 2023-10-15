/*******************************************************************************
* Copyright © 2019 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC2300_FIELDS_H
#define TMC2300_FIELDS_H

/*
* 
*/
/*!
 * @brief GCONF // PWM_direct (Reset default=0)
 */
#define TMC2300_PWM_DIRECT_MASK 0x01
/*!
 * @brief PWM_direct (Reset default=0)
 */
#define TMC2300_PWM_DIRECT_SHIFT 0
/*!
 * @brief GCONF // extcap (Reset default=0)
 */
#define TMC2300_EXTCAP_MASK 0x02
/*!
 * @brief extcap (Reset default=0)
 */
#define TMC2300_EXTCAP_SHIFT 1
/*!
 * @brief GCONF // par_mode (Reset default=0)
 */
#define TMC2300_EN_SPREADCYCLE_MASK 0x04
/*!
 * @brief par_mode (Reset default=0)
 */
#define TMC2300_EN_SPREADCYCLE_SHIFT 2
/*!
 * @brief GCONF // Inverse motor direction
 */
#define TMC2300_SHAFT_MASK 0x08
/*!
 * @brief Inverse motor direction
 */
#define TMC2300_SHAFT_SHIFT 3
/*!
 * @brief GCONF // diag_index
 */
#define TMC2300_DIAG_INDEX_MASK 0x10
/*!
 * @brief diag_index
 */
#define TMC2300_DIAG_INDEX_SHIFT 4
/*!
 * @brief GCONF // diag_step
 */
#define TMC2300_DIAG_STEP_MASK 0x20
/*!
 * @brief diag_step
 */
#define TMC2300_DIAG_STEP_SHIFT 5
/*!
 * @brief GCONF // pdn_disable
 */
#define TMC2300_PDN_DISABLE_MASK 0x40
/*!
 * @brief pdn_disable
 */
#define TMC2300_PDN_DISABLE_SHIFT 6
/*!
 * @brief GCONF // mstep_reg_select
 */
#define TMC2300_MSTEP_REG_SELECT_MASK 0x80
/*!
 * @brief mstep_reg_select
 */
#define TMC2300_MSTEP_REG_SELECT_SHIFT 7
/*!
 * @brief GCONF // multistep_filt (Reset default=1)
 */
#define TMC2300_MULTISTEP_FILT_MASK 0x100
/*!
 * @brief multistep_filt (Reset default=1)
 */
#define TMC2300_MULTISTEP_FILT_SHIFT 8
/*!
 * @brief GCONF // test_mode 0
 */
#define TMC2300_TEST_MODE_MASK 0x200
/*!
 * @brief test_mode 0
 */
#define TMC2300_TEST_MODE_SHIFT 9
/*!
 * @brief GSTAT // reset
 */
#define TMC2300_RESET_MASK 0x01
/*!
 * @brief reset
 */
#define TMC2300_RESET_SHIFT 0
/*!
 * @brief GSTAT // drv_err
 */
#define TMC2300_DRV_ERR_MASK 0x02
/*!
 * @brief drv_err
 */
#define TMC2300_DRV_ERR_SHIFT 1
/*!
 * @brief GSTAT // Actual state of the supply voltage comparator
 */
#define TMC2300_U3V5_MASK 0x04
/*!
 * @brief Actual state of the supply voltage comparator
 */
#define TMC2300_U3V5_SHIFT 2
/*!
 * @brief IFCNT // Interface transmission counter
 */
#define TMC2300_IFCNT_MASK 0xFF
/*!
 * @brief Interface transmission counter
 */
#define TMC2300_IFCNT_SHIFT 0
/*!
 * @brief SLAVECONF // SENDDELAY for read access
 */
#define TMC2300_SLAVECONF_MASK 0xF00
/*!
 * @brief SENDDELAY for read access
 */
#define TMC2300_SLAVECONF_SHIFT 8
/*!
 * @brief IOIN // EN
 */
#define TMC2300_EN_MASK 0x01
/*!
 * @brief EN
 */
#define TMC2300_EN_SHIFT 0
/*!
 * @brief IOIN // NSTDBY
 */
#define TMC2300_NSTDBY_MASK 0x02
/*!
 * @brief NSTDBY
 */
#define TMC2300_NSTDBY_SHIFT 1
/*!
 * @brief IOIN // MS1
 */
#define TMC2300_MS1_MASK 0x04
/*!
 * @brief MS1
 */
#define TMC2300_MS1_SHIFT 2
/*!
 * @brief IOIN // MS2
 */
#define TMC2300_MS2_MASK 0x08
/*!
 * @brief MS2
 */
#define TMC2300_MS2_SHIFT 3
/*!
 * @brief IOIN // DIAG
 */
#define TMC2300_DIAG_MASK 0x10
/*!
 * @brief DIAG
 */
#define TMC2300_DIAG_SHIFT 4
/*!
 * @brief IOIN // STEPPER/CLK Input
 */
#define TMC2300_STEPPERCLK_INPUT_MASK 0x20
/*!
 * @brief STEPPER/CLK Input
 */
#define TMC2300_STEPPERCLK_INPUT_SHIFT 5
/*!
 * @brief IOIN // PDN_UART
 */
#define TMC2300_PDN_UART_MASK 0x40
/*!
 * @brief PDN_UART
 */
#define TMC2300_PDN_UART_SHIFT 6
/*!
 * @brief IOIN // MODE Input
 */
#define TMC2300_MODE_INPUT_MASK 0x80
/*!
 * @brief MODE Input
 */
#define TMC2300_MODE_INPUT_SHIFT 7
/*!
 * @brief IOIN // STEP
 */
#define TMC2300_STEP_MASK 0x100
/*!
 * @brief STEP
 */
#define TMC2300_STEP_SHIFT 8
/*!
 * @brief IOIN // DIR
 */
#define TMC2300_DIR_MASK 0x200
/*!
 * @brief DIR
 */
#define TMC2300_DIR_SHIFT 9
/*!
 * @brief IOIN // COMP_A1A2
 */
#define TMC2300_COMP_A1A2_MASK 0x400
/*!
 * @brief COMP_A1A2
 */
#define TMC2300_COMP_A1A2_SHIFT 10
/*!
 * @brief IOIN // COMP_B1B2
 */
#define TMC2300_COMP_B1B2_MASK 0x800
/*!
 * @brief COMP_B1B2
 */
#define TMC2300_COMP_B1B2_SHIFT 7
/*!
 * @brief IOIN // VERSION: 0x40=first version of the IC Identical numbers mean full digital compatibility.
 */
#define TMC2300_VERSION_MASK 0xFF000000
/*!
 * @brief VERSION: 0x40=first version of the IC Identical numbers mean full digital compatibility.
 */
#define TMC2300_VERSION_SHIFT 24
/*!
 * @brief IHOLD_IRUN // Standstill current
 */
#define TMC2300_IHOLD_MASK 0x1F
/*!
 * @brief Standstill current
 */
#define TMC2300_IHOLD_SHIFT 0
/*!
 * @brief IHOLD_IRUN // Motor run current
 */
#define TMC2300_IRUN_MASK 0x1F00
/*!
 * @brief Motor run current
 */
#define TMC2300_IRUN_SHIFT 8
/*!
 * @brief IHOLD_IRUN // Controls the number of clock cycles for motor power down after standstill is detected
 */
#define TMC2300_IHOLDDELAY_MASK 0xF0000
/*!
 * @brief Controls the number of clock cycles for motor power down after standstill is detected
 */
#define TMC2300_IHOLDDELAY_SHIFT 16
/*!
 * @brief TPOWERDOWN // Delay time from stand still (stst) detection to motor current power down
 */
#define TMC2300_TPOWERDOWN_MASK 0xFF
/*!
 * @brief Delay time from stand still (stst) detection to motor current power down
 */
#define TMC2300_TPOWERDOWN_SHIFT 0
/*!
 * @brief TSTEP // Actual measured time between two 1/256 microsteps
 */
#define TMC2300_TSTEP_MASK 0xFFFFF
/*!
 * @brief Actual measured time between two 1/256 microsteps
 */
#define TMC2300_TSTEP_SHIFT 0
/*!
 * @brief TCOOLTHRS // This is the lower threshold velocity for switching on smart energy coolStep and stallGuard feature.
 */
#define TMC2300_TCOOLTHRS_MASK 0xFFFFFFFF
/*!
 * @brief This is the lower threshold velocity for switching on smart energy coolStep and stallGuard feature.
 */
#define TMC2300_TCOOLTHRS_SHIFT 0
/*!
 * @brief VACTUAL // VACTUAL allows moving the motor by UART control
 */
#define TMC2300_VACTUAL_MASK 0xFFFFFF
/*!
 * @brief VACTUAL allows moving the motor by UART control
 */
#define TMC2300_VACTUAL_SHIFT 0
/*!
 * @brief SGTHRS // Detection threshold for stall.
 */
#define TMC2300_SGTHRS_MASK 0xFF
/*!
 * @brief Detection threshold for stall.
 */
#define TMC2300_SGTHRS_SHIFT 0
/*!
 * @brief SG_VALUE // SG_VALUE result.
 */
#define TMC2300_SG_VALUE_MASK 0x3FF
/*!
 * @brief SG_VALUE result.
 */
#define TMC2300_SG_VALUE_SHIFT 0
/*!
 * @brief COOLCONF // minimum stallGuard2 value - If the stallGuard2 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle. 0: smart current control coolStep off
 */
#define TMC2300_SEMIN_MASK 0x0F
/*!
 * @brief minimum stallGuard2 value - If the stallGuard2 result falls below SEMIN*32, the motor current becomes increased to reduce motor load angle. 0: smart current control coolStep off
 */
#define TMC2300_SEMIN_SHIFT 0
/*!
 * @brief COOLCONF // Current increment steps per measured stallGuard2 value
 */
#define TMC2300_SEUP_MASK 0x60
/*!
 * @brief Current increment steps per measured stallGuard2 value
 */
#define TMC2300_SEUP_SHIFT 5
/*!
 * @brief COOLCONF // stallGuard2 hysteresis value - If the stallGuard2 result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.
 */
#define TMC2300_SEMAX_MASK 0xF00
/*!
 * @brief stallGuard2 hysteresis value - If the stallGuard2 result is equal to or above (SEMIN+SEMAX+1)*32, the motor current becomes decreased to save energy.
 */
#define TMC2300_SEMAX_SHIFT 8
/*!
 * @brief COOLCONF // Current down step speed; For each n stallGuard2 values decrease by one
 */
#define TMC2300_SEDN_MASK 0x6000
/*!
 * @brief Current down step speed; For each n stallGuard2 values decrease by one
 */
#define TMC2300_SEDN_SHIFT 13
/*!
 * @brief COOLCONF // minimum current for smart current control
 */
#define TMC2300_SEIMIN_MASK 0x8000
/*!
 * @brief minimum current for smart current control
 */
#define TMC2300_SEIMIN_SHIFT 15
/*!
 * @brief MSCNT // Microstep counter
 */
#define TMC2300_MSCNT_MASK 0x3FF
/*!
 * @brief Microstep counter
 */
#define TMC2300_MSCNT_SHIFT 0
/*!
 * @brief MSCURACT // Actual  microstep current for motor phase A
 */
#define TMC2300_CUR_A_MASK 0x1FF
/*!
 * @brief Actual  microstep current for motor phase A
 */
#define TMC2300_CUR_A_SHIFT 0
/*!
 * @brief MSCURACT // Actual  microstep current for motor phase B
 */
#define TMC2300_CUR_B_MASK 0x1FF0000
/*!
 * @brief Actual  microstep current for motor phase B
 */
#define TMC2300_CUR_B_SHIFT 16
/*!
 * @brief CHOPCONF // driver enable
 */
#define TMC2300_ENABLEDRV_MASK 0x01
/*!
 * @brief driver enable
 */
#define TMC2300_ENABLEDRV_SHIFT 0
/*!
 * @brief CHOPCONF // blank time select
 */
#define TMC2300_TBL_MASK 0x18000
/*!
 * @brief blank time select
 */
#define TMC2300_TBL_SHIFT 15
/*!
 * @brief CHOPCONF // MRES micro step resolution
 */
#define TMC2300_MRES_MASK 0xF000000
/*!
 * @brief MRES micro step resolution
 */
#define TMC2300_MRES_SHIFT 24
/*!
 * @brief CHOPCONF // interpolation to 256 microsteps
 */
#define TMC2300_INTPOL_MASK 0x10000000
/*!
 * @brief interpolation to 256 microsteps
 */
#define TMC2300_INTPOL_SHIFT 28
/*!
 * @brief CHOPCONF // enable double edge step pulses
 */
#define TMC2300_DEDGE_MASK 0x20000000
/*!
 * @brief enable double edge step pulses
 */
#define TMC2300_DEDGE_SHIFT 29
/*!
 * @brief CHOPCONF // short to GND protection disable
 */
#define TMC2300_DISS2G_MASK 0x40000000
/*!
 * @brief short to GND protection disable
 */
#define TMC2300_DISS2G_SHIFT 30
/*!
 * @brief CHOPCONF // Low side short protection disable
 */
#define TMC2300_DISS2VS_MASK 0x80000000
/*!
 * @brief Low side short protection disable
 */
#define TMC2300_DISS2VS_SHIFT 31
/*!
 * @brief DRV_STATUS // overtemperature prewarning flag
 */
#define TMC2300_OTPW_MASK 0x01
/*!
 * @brief overtemperature prewarning flag
 */
#define TMC2300_OTPW_SHIFT 0
/*!
 * @brief DRV_STATUS // overtemperature flag
 */
#define TMC2300_OT_MASK 0x02
/*!
 * @brief overtemperature flag
 */
#define TMC2300_OT_SHIFT 1
/*!
 * @brief DRV_STATUS // short to ground indicator phase A
 */
#define TMC2300_S2GA_MASK 0x04
/*!
 * @brief short to ground indicator phase A
 */
#define TMC2300_S2GA_SHIFT 2
/*!
 * @brief DRV_STATUS // short to ground indicator phase B
 */
#define TMC2300_S2GB_MASK 0x08
/*!
 * @brief short to ground indicator phase B
 */
#define TMC2300_S2GB_SHIFT 3
/*!
 * @brief DRV_STATUS // low side short indicator phase A
 */
#define TMC2300_S2VSA_MASK 0x10
/*!
 * @brief low side short indicator phase A
 */
#define TMC2300_S2VSA_SHIFT 4
/*!
 * @brief DRV_STATUS // low side short indicator phase B
 */
#define TMC2300_S2VSB_MASK 0x20
/*!
 * @brief low side short indicator phase B
 */
#define TMC2300_S2VSB_SHIFT 5
/*!
 * @brief DRV_STATUS // open load indicator phase A
 */
#define TMC2300_OLA_MASK 0x40
/*!
 * @brief open load indicator phase A
 */
#define TMC2300_OLA_SHIFT 6
/*!
 * @brief DRV_STATUS // open load indicator phase B
 */
#define TMC2300_OLB_MASK 0x80
/*!
 * @brief open load indicator phase B
 */
#define TMC2300_OLB_SHIFT 7
/*!
 * @brief DRV_STATUS // 120�C comparator
 */
#define TMC2300_T120_MASK 0x100
/*!
 * @brief 120�C comparator
 */
#define TMC2300_T120_SHIFT 8
/*!
 * @brief DRV_STATUS // 143�C comparator
 */
#define TMC2300_T143_MASK 0x200
/*!
 * @brief 143�C comparator
 */
#define TMC2300_T143_SHIFT 9
/*!
 * @brief DRV_STATUS // 150�C comparator
 */
#define TMC2300_T150_MASK 0x400
/*!
 * @brief 150�C comparator
 */
#define TMC2300_T150_SHIFT 10
/*!
 * @brief DRV_STATUS // 157�C comparator
 */
#define TMC2300_T157_MASK 0x800
/*!
 * @brief 157�C comparator
 */
#define TMC2300_T157_SHIFT 11
/*!
 * @brief DRV_STATUS // actual motor current
 */
#define TMC2300_CS_ACTUAL_MASK 0x1F0000
/*!
 * @brief actual motor current
 */
#define TMC2300_CS_ACTUAL_SHIFT 16
/*!
 * @brief DRV_STATUS // standstill indicator
 */
#define TMC2300_STST_MASK 0x80000000
/*!
 * @brief standstill indicator
 */
#define TMC2300_STST_SHIFT 31
/*!
 * @brief PWMCONF // User defined PWM amplitude offset (0-255)
 */
#define TMC2300_PWM_OFS_MASK 0xFF
/*!
 * @brief User defined PWM amplitude offset (0-255)
 */
#define TMC2300_PWM_OFS_SHIFT 0
/*!
 * @brief PWMCONF // Velocity dependent gradient for PWM amplitude
 */
#define TMC2300_PWM_GRAD_MASK 0xFF00
/*!
 * @brief Velocity dependent gradient for PWM amplitude
 */
#define TMC2300_PWM_GRAD_SHIFT 8
/*!
 * @brief PWMCONF // %00: fPWM=2/1024 fCLK; %01: fPWM=2/683 fCLK; %10: fPWM=2/512 fCLK; %11: fPWM=2/410 fCLK;
 */
#define TMC2300_PWM_FREQ_MASK 0x30000
/*!
 * @brief %00: fPWM=2/1024 fCLK; %01: fPWM=2/683 fCLK; %10: fPWM=2/512 fCLK; %11: fPWM=2/410 fCLK;
 */
#define TMC2300_PWM_FREQ_SHIFT 16
/*!
 * @brief PWMCONF //
 */
#define TMC2300_PWM_AUTOSCALE_MASK 0x40000
/*!
 * @brief 
 */
#define TMC2300_PWM_AUTOSCALE_SHIFT 18
/*!
 * @brief PWMCONF //
 */
#define TMC2300_PWM_AUTOGRAD_MASK 0x80000
/*!
 * @brief 
 */
#define TMC2300_PWM_AUTOGRAD_SHIFT 19
/*!
 * @brief PWMCONF // Stand still option when motor current setting is zero (I_HOLD=0)
 */
#define TMC2300_FREEWHEEL_MASK 0x300000
/*!
 * @brief Stand still option when motor current setting is zero (I_HOLD=0)
 */
#define TMC2300_FREEWHEEL_SHIFT 20
/*!
 * @brief PWMCONF // User defined maximum PWM amplitude change per half wave when using pwm_autoscale=1
 */
#define TMC2300_PWM_REG_MASK 0xF000000
/*!
 * @brief User defined maximum PWM amplitude change per half wave when using pwm_autoscale=1
 */
#define TMC2300_PWM_REG_SHIFT 24
/*!
 * @brief PWMCONF // Limit  for  PWM_SCALE_AUTO  when  switching  back  from spreadCycle to stealthChop
 */
#define TMC2300_PWM_LIM_MASK 0xF0000000
/*!
 * @brief Limit  for  PWM_SCALE_AUTO  when  switching  back  from spreadCycle to stealthChop
 */
#define TMC2300_PWM_LIM_SHIFT 28
/*!
 * @brief PWM_SCALE // Actual  PWM  duty  cycle.  This value  is  used  for  scaling  the values  CUR_A  and  CUR_B  read from the sine wave table.
 */
#define TMC2300_PWM_SCALE_SUM_MASK 0xFF
/*!
 * @brief Actual  PWM  duty  cycle.  This value  is  used  for  scaling  the values  CUR_A  and  CUR_B  read from the sine wave table.
 */
#define TMC2300_PWM_SCALE_SUM_SHIFT 0
/*!
 * @brief PWM_SCALE // 9 Bit signed offset added to the calculated  PWM  duty  cycle.  This is  the  result  of  the  automatic amplitude  regulation  based  on current measurement.
 */
#define TMC2300_PWM_SCALE_AUTO_MASK 0x1FF0000
/*!
 * @brief 9 Bit signed offset added to the calculated  PWM  duty  cycle.  This is  the  result  of  the  automatic amplitude  regulation  based  on current measurement.
 */
#define TMC2300_PWM_SCALE_AUTO_SHIFT 16
/*!
 * @brief PWM_AUTO // Automatically  determined  offset value
 */
#define TMC2300_PWM_OFS_AUTO_MASK 0xFF
/*!
 * @brief Automatically  determined  offset value
 */
#define TMC2300_PWM_OFS_AUTO_SHIFT 0
/*!
 * @brief PWM_AUTO // Automatically  determined gradient value
 */
#define TMC2300_PWM_GRAD_AUTO_MASK 0xFF0000
/*!
 * @brief Automatically  determined gradient value
 */
#define TMC2300_PWM_GRAD_AUTO_SHIFT 16

#endif /* TMC2300_FIELDS_H */
