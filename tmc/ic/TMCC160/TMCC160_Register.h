/*
* TMCC160_Registers.h
*
*  Created on: 04.11.2015
*      Author: ed
*/

#ifndef TMCC160_REGISTERS_H_
#define TMCC160_REGISTERS_H_

	// ===== TMCC160 register set =====

	// --- status information ---
	#define HARDWARE_VERSION_REG_ADDR                  0x00
	#define SOFTWARE_VERSION_REG_ADDR                  0x01
	#define SUPPLY_VOLTAGE_REG_ADDR                    0x03
	#define TEMPERATURE_REG_ADDR                       0x04
	#define ERROR_STATUS_FLAGS_REG_ADDR                0x05

	// --- general settings ---
	#define    MOTOR_POLE_PAIRS_REG_ADDR               0x08
	#define HALL_INVERT_REG_ADDR                       0x09
	#define HALL_INTERPOLATION_REG_ADDR                0x0A
	#define ENCODER_STEPS_REG_ADDR                     0x0B
	#define ENCODER_OFFSET_REG_ADDR                    0x0C
	#define ENCODER_DIRECTION_REG_ADDR                 0x0D
	#define ENCODER_INIT_MODE_REG_ADDR                 0x0E
	#define ENCODER_INIT_VELOCITY_REG_ADDR             0x0F
	#define ENCODER_INIT_DELAY_REG_ADDR                0x10
	#define COMMUTATION_MODE_REG_ADDR                  0x11
	#define MOTION_MODE_REG_ADDR                       0x12
	#define BLDC_RE_INIT_REG_ADDR                      0x13
	#define ANGLE_HALL_REG_ADDR                        0x14
	#define ANGLE_ENCODER_REG_ADDR                     0x15
	#define ANGLE_CONTROLLED_REG_ADDR                  0x16

	// --- torque regulation ---
	#define CURRENT_MAX_REG_ADDR                       0x20
	#define CURRENT_CONTROLLED_REG_ADDR                0x21
	#define CURRENT_ACTUAL_REG_ADDR                    0x22
	#define CURRENT_TARGET_REG_ADDR                    0x23
	#define CURRENT_LOOP_DELAY_REG_ADDR                0x24
	#define CURRENT_P_REG_ADDR                         0x25
	#define CURRENT_I_REG_ADDR                         0x26
	#define CURRENT_ERROR_REG_ADDR                     0x27
	#define CURRENT_ERROR_SUM_REG_ADDR                 0x28
	#define FLUX_ERROR_REG_ADDR                        0x29
	#define FLUX_ERROR_SUM_REG_ADDR                    0x2A
	#define DUAL_SHUNT_FACTOR_REG_ADDR                 0x2B

	// --- velocity regulation ---
	#define VELOCITY_MAX_REG_ADDR                      0x30
	#define VELOCITY_HALTED_REG_ADDR                   0x31
	#define VELOCITY_ACTUAL_REG_ADDR                   0x32
	#define VELOCITY_TARGET_REG_ADDR                   0x33
	#define VELOCITY_LOOP_DELAY_REG_ADDR               0x34
	#define VELOCITY_P_REG_ADDR                        0x35
	#define VELOCITY_I_REG_ADDR                        0x36
	#define VELOCITY_ERROR_REG_ADDR                    0x37
	#define VELOCITY_ERROR_SUM_REG_ADDR                0x38

	// --- velocity ramp ---
	#define RAMP_ACTIVATED_REG_ADDR                    0x3A
	#define RAMP_ACCELERATION_REG_ADDR                 0x3B
	#define RAMP_ACTUAL_VELOCITY_REG_ADDR              0x3C

	// --- position regulation ---
	#define POSITION_ACTUAL_REG_ADDR                   0x40
	#define POSITION_TARGET_ABS_REG_ADDR               0x41
	#define POSITION_TARGET_REL_REG_ADDR               0x42
	#define POSITION_P_REG_ADDR                        0x43
	#define POSITION_ERROR_REG_ADDR                    0x44
	#define POSITION_TARGET_REACHED_VELOCITY_REG_ADDR  0x45
	#define POSITION_TARGET_REACHED_DISTANCE_REG_ADDR  0x46
	#define ENCODER_SET_NULL_REG_ADDR                  0x47
	#define ENCODER_CLEAR_SET_NULL_REG_ADDR            0x48

	// --- driver diagnostic ---
	#define DRIVER_DIAGNOSTIC_REG_ADDR                 0x50
	#define DRIVER_ACKNOWLEDGE_REG_ADDR                0x51
	//#define DRIVER_ENABLE_SPI_REG_ADDR                 0x52
	//#define DRIVER_STATUS_REGISTER_2_REG_ADDR          0x53
	//#define DRIVER_STATUS_REGISTER_3_REG_ADDR          0x54
	//#define DRIVER_STATUS_REGISTER_4_REG_ADDR          0x55

	// --- brake chopper ---
	#define BRAKE_ENABLED_REG_ADDR                     0x58
	#define BRAKE_VOLTAGE_LIMIT_REG_ADDR               0x59
	#define BRAKE_HYSTERESIS_REG_ADDR                  0x5A

	// --- IIT monitor ---
	#define IIT_TIME_REG_ADDR                          0x60
	#define IIT_LIMIT_REG_ADDR                         0x61
	#define IIT_SUM_REG_ADDR                           0x62
	#define IIT_EXCEEDED_COUNTER_REG_ADDR              0x63
	#define IIT_CLEAR_EXCEEDED_REG_ADDR                0x64

	// --- single shunt current measurement ---
	#define SINGLE_SHUNT_ENABLED_REG_ADDR              0x68
	#define SINGLE_SHUNT_VREF_OFFSET_REG_ADDR          0x69
		// [0..15]     SINGLE_SHUNT_OFFSET
		// [16..31]    SINGLE_SHUNT_VREF

	#define SINGLE_SHUNT_FACTOR_REG_ADDR               0x6A

	// --- IOs ---
	#define ADC_PHASE_A_B_REG_ADDR                     0x75
		// [0..15]     ADC_PHASE_B
		// [16..31]    ADC_PHASE_A

	#define ADC_INPUT_0_SINGLE_SHUNT_REG_ADDR          0x76
		// [0..15]     ADC_SINGLE_SHUNT
		// [16..31]    ANALOG_INPUT_0

	#define ADC_VSUPPLY_TEMP_REG_ADDR                  0x77
		// [0..15]     ADC_TEMP
		// [16..31]    ADC_VSUPPLY

	#define DIGITAL_INPUTS_REG_ADDR                    0x78
		// [0]        DIGITAL_INPUT_ENABLE
		// [1]        DIGITAL_INPUT_REF_R
		// [2]        DIGITAL_INPUT_REF_L

	// --- USER variable access ---
	#define USER_VARIABLE_ADDRESS_REG_ADDR             0x7A
		// [0..7]    USER_VARIABLE_ADDRESS
	#define USER_VARIABLE_VALUE_REG_ADDR               0x7B

	// --- TMCL access ---
	#define TMCL_REQUEST_BYTE_0123_REG_ADDR            0x7C
	#define TMCL_REQUEST_BYTE_4567_REG_ADDR            0x7D
	#define TMCL_REPLY_BYTE_0123_REG_ADDR              0x7E
	#define TMCL_REPLY_BYTE_4567_REG_ADDR              0x7F

#endif /* TMCC160_REGISTERS_H_ */
