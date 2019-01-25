#ifndef TMC5072_REGISTER_H
#define TMC5072_REGISTER_H

// ===== TMC5072 register set =====

#define MOTOR_ADDR(m)      (0x20 << m)
#define MOTOR_ADDR_DRV(m)  (m << 4)
#define MOTOR_ADDR_PWM(m)  (m << 3)

#define TMC5072_GCONF      0x00
#define TMC5072_GSTAT      0x01
#define TMC5072_IFCNT      0x02
#define TMC5072_SLAVECONF  0x03
#define TMC5072_INPUT      0x04
#define TMC5072_OUTPUT     0x04
#define TMC5072_X_COMPARE  0x05
																 // motor = 0       motor = 1
#define TMC5072_PWMCONF(motor)     (0x10|MOTOR_ADDR_PWM(motor))  //      0x10            0x18
#define TMC5072_PWM_STATUS(motor)  (0x11|MOTOR_ADDR_PWM(motor))  //      0x11            0x19

																 // motor = 0       motor = 1
#define TMC5072_RAMPMODE(motor)    (0x00|MOTOR_ADDR(motor))      //      0x20            0x40
#define TMC5072_XACTUAL(motor)     (0x01|MOTOR_ADDR(motor))      //      0x21            0x41
#define TMC5072_VACTUAL(motor)     (0x02|MOTOR_ADDR(motor))      //      0x22            0x42
#define TMC5072_VSTART(motor)      (0x03|MOTOR_ADDR(motor))      //      0x23            0x43
#define TMC5072_A1(motor)          (0x04|MOTOR_ADDR(motor))      //      0x24            0x44
#define TMC5072_V1(motor)          (0x05|MOTOR_ADDR(motor))      //      0x25            0x45
#define TMC5072_AMAX(motor)        (0x06|MOTOR_ADDR(motor))      //      0x26            0x46
#define TMC5072_VMAX(motor)        (0x07|MOTOR_ADDR(motor))      //      0x27            0x47
#define TMC5072_DMAX(motor)        (0x08|MOTOR_ADDR(motor))      //      0x28            0x48
#define TMC5072_D1(motor)          (0x0A|MOTOR_ADDR(motor))      //      0x2A            0x4A
#define TMC5072_VSTOP(motor)       (0x0B|MOTOR_ADDR(motor))      //      0x2B            0x4B
#define TMC5072_TZEROWAIT(motor)   (0x0C|MOTOR_ADDR(motor))      //      0x2C            0x4C
#define TMC5072_XTARGET(motor)     (0x0D|MOTOR_ADDR(motor))      //      0x2D            0x4D
#define TMC5072_IHOLD_IRUN(motor)  (0x10|MOTOR_ADDR(motor))      //      0x30            0x50
#define TMC5072_VCOOLTHRS(motor)   (0x11|MOTOR_ADDR(motor))      //      0x31            0x51
#define TMC5072_VHIGH(motor)       (0x12|MOTOR_ADDR(motor))      //      0x32            0x52
#define TMC5072_VDCMIN(motor)      (0x13|MOTOR_ADDR(motor))      //      0x33            0x53
#define TMC5072_SWMODE(motor)      (0x14|MOTOR_ADDR(motor))      //      0x34            0x54
#define TMC5072_RAMPSTAT(motor)    (0x15|MOTOR_ADDR(motor))      //      0x35            0x55
#define TMC5072_XLATCH(motor)      (0x16|MOTOR_ADDR(motor))      //      0x36            0x56
#define TMC5072_ENCMODE(motor)     (0x18|MOTOR_ADDR(motor))      //      0x38            0x58
#define TMC5072_XENC(motor)        (0x19|MOTOR_ADDR(motor))      //      0x39            0x59
#define TMC5072_ENC_CONST(motor)   (0x1A|MOTOR_ADDR(motor))      //      0x3A            0x5A
#define TMC5072_ENC_STATUS(motor)  (0x1B|MOTOR_ADDR(motor))      //      0x3B            0x5B
#define TMC5072_ENC_LATCH(motor)   (0x1C|MOTOR_ADDR(motor))      //      0x3C            0x5C

#define TMC5072_MSLUT0             0x60
#define TMC5072_MSLUT1             0x61
#define TMC5072_MSLUT2             0x62
#define TMC5072_MSLUT3             0x63
#define TMC5072_MSLUT4             0x64
#define TMC5072_MSLUT5             0x65
#define TMC5072_MSLUT6             0x66
#define TMC5072_MSLUT7             0x67
#define TMC5072_MSLUTSEL           0x68
#define TMC5072_MSLUTSTART         0x69
																 // motor = 0       motor = 1
#define TMC5072_MSCNT(motor)       (0x6A|MOTOR_ADDR_DRV(motor))  //      0x6A            0x7A
#define TMC5072_MSCURACT(motor)    (0x6B|MOTOR_ADDR_DRV(motor))  //      0x6B            0x7B
#define TMC5072_CHOPCONF(motor)    (0x6C|MOTOR_ADDR_DRV(motor))  //      0x6C            0x7C
#define TMC5072_COOLCONF(motor)    (0x6D|MOTOR_ADDR_DRV(motor))  //      0x6D            0x7D
#define TMC5072_DCCTRL(motor)      (0x6E|MOTOR_ADDR_DRV(motor))  //      0x6E            0x7E
#define TMC5072_DRVSTATUS(motor)   (0x6F|MOTOR_ADDR_DRV(motor))  //      0x6F            0x7F

#endif /* TMC5072_REGISTER_H */
