/*
 * TMC8690_Registers.h
 *
 *  Created on: 18.07.2016
 *      Author: bs, ed
 */

#ifndef TMC8690_REGISTERS_H_
#define TMC8690_REGISTERS_H_

// ===== TMC8690 register set =====

// --- status information ---
	#define CHIPINFO_DATA               0x00
	#define CHIPINFO_ADDR               0x01
	#define STATUS_WORD                 0x02
	#define COMMAND_WORD                0x03
	#define P_FAK_BRAKE                 0x04
	#define I_FAK_BRAKE                 0x05
	#define P_FAK_HEAT                  0x06
	#define I_FAK_HEAT                  0x07
	#define P_FAK_VEL                   0x08
	#define I_FAK_VEL                   0x09
	#define P_FAK_POS                   0x0A
	#define ENC_Z_COMP_VAL              0x0B
	#define TORQUE_TARGET               0x0C
	#define VELOCITY_TARGET             0x0D
	#define POSITION_TARGET             0x0E
	#define TEMPERATURE_TARGET          0x0F
	#define OSCI_MAIN_CONFIG_REG        0x10
	#define OSCI_PRETRIGGER_CONFIG_REG  0x11
	#define OSCI_DATA_ADDRESS           0x12
	#define OSCI_STATUS                 0x13
	#define OSCI_OUTPUT_DATA            0x14
	#define ADC_ENC_TRACK_A             0x15
	#define ADC_ENC_TRACK_B             0x16
	#define ADC_ENC_TRACK_Z             0x17
	#define ADC_I_U                     0x18
	#define ADC_I_V                     0x19
	#define ADC_I_W                     0x20
	#define ADC_I_SUPPLY                0x21
	#define ADC_I_SUPPLY_FILT           0x22
	#define ADC_TORQUE                  0x23
	#define ADC_TEMP                    0x24
	#define ADC_MICROPHONE              0x25
	#define ADC_I_BRAKE                 0x26
	#define TRACK_A_OFFSET              0x30
	#define TRACK_B_OFFSET              0x31
	#define DAC_V_REF                   0x32
	#define T_PT1_FILTER_VEL            0x33
	#define T_PT1_FILTER_I_SUPPLY       0x34
	#define DAC_BRAKE                   0x35
	#define DAC_BRAKE_TARGET            0x36
	#define VELOCITY_ACTUAL             0x37
	#define VELOCITY_IN_RPM_ACTUAL      0x38
	#define VELOCITY_IN_RPM_ACTUAL_PT1  0x39
	#define VELOCITY_IN_RPM_ACTUAL_MAV  0x3A
	#define POSITION_ACTUAL             0x3B
	#define VEL_CTRL_TORQUE_TARGET      0x3C
	#define POS_CTRL_VEL_TARGET         0x3D
	#define PWM_HEATER                  0x3E
	#define U_BRAKE                     0x3F
	#define DEBUG_AXIS_PARAM_0          0x50
	#define DEBUG_AXIS_PARAM_1          0x51
	#define DEBUG_AXIS_PARAM_2          0x52
	#define DEBUG_AXIS_PARAM_3          0x53
	#define DEBUG_AXIS_PARAM_4          0x54
	#define DEBUG_AXIS_PARAM_5          0x55
	#define DEBUG_AXIS_PARAM_6          0x56
	#define DEBUG_AXIS_PARAM_7          0x57
	#define STATE_VAR_PARAM_0           0x58
	#define STATE_VAR_PARAM_1           0x59
	#define STATE_VAR_PARAM_2           0x5A
	#define STATE_VAR_PARAM_3           0x5B
	#define STATE_VAR_PARAM_4           0x5C
	#define STATE_VAR_PARAM_5           0x5D
	#define STATE_VAR_PARAM_6           0x5E
	#define STATE_VAR_PARAM_7           0x5F
	#define SAMP_INPUTS_RAW             0x76
	#define SAMP_OUTPUTS_RAW            0x77
	#define STATUS_FLAGS                0x7C
	#define WARNING_MASK                0x7D
	#define ERROR_MASK                  0x7E

#endif /* TMC8690_REGISTERS_H_ */
