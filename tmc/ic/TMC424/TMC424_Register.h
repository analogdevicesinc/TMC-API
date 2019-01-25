#ifndef TMC424_REGISTER_H
#define TMC424_REGISTER_H

	// TMC424 Encoder Configuration Registers
	#define TMC424_ENC_CONF_1    0x00
	#define TMC424_ENC_CONF_2    0x02
	#define TMC424_ENC_CONF_3    0x04
	#define TMC424_ENC_CONF_ALL  0x06

	// TMC424 Encoder Counter Registers
	#define TMC424_ENC_DATA_1  0x08
	#define TMC424_ENC_DATA_2  0x0A
	#define TMC424_ENC_DATA_3  0x0C

	// TMC424 Step/Direction Converter Registers
	#define TMC424_STEP_PULSE_DELAY 0x07

	// TMC424 Interrupt configuration register
	#define TMC424_INT_CTRL 0x10

	// Write bit (to be combined with a register address for write access to a register)
	#define TMC424_WRITE 0x01

	// Encooder configuration bits (for TMC424_ENC_CONF_x registers)
	#define TMC424_POL_ACTHI    0x08
	#define TMC424_HOLD_ON_N    0x04
	#define TMC424_CLEAR_ON_N   0x02
	#define TMC424_TRIG_ALWAYS  0x01
	#define TMC424_ADD_CCW      0x80

	// Interrupt configuration bits (for TMC424_INT_CTRL register)
	#define TMC424_FREEZE     0x80
	#define TMC424_INT_ON_N   0x40
	#define TMC424_CLR_FLAGS  0x20

#endif /* TMC424_REGISTER_H */
