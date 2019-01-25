#ifndef TMC2041_REGISTER_H
#define TMC2041_REGISTER_H

// Helper macros to determine motor-dependant addresses
#define MOTOR_ADDR(m)      (0x20 << m )
#define MOTOR_ADDR_DRV(m)  (m << 4)

// ===== TMC2041 register set =====
#define TMC2041_GCONF              0x00
#define TMC2041_GSTAT              0x01
#define TMC2041_IFCNT              0x02
#define TMC2041_SLAVECONF          0x03
#define TMC2041_INPUT              0x04 // Read only
#define TMC2041_OUTPUT             0x04 // Write only
																 // motor = 0       motor = 1
#define TMC2041_IHOLD_IRUN(motor)  (0x10|MOTOR_ADDR(motor))      //      0x30            0x50

#define TMC2041_MSCNT(motor)       (0x6A|MOTOR_ADDR_DRV(motor))  //      0x6A            0x7A
#define TMC2041_MSCURACT(motor)    (0x6B|MOTOR_ADDR_DRV(motor))  //      0x6B            0x7B
#define TMC2041_CHOPCONF(motor)    (0x6C|MOTOR_ADDR_DRV(motor))  //      0x6C            0x7C
#define TMC2041_COOLCONF(motor)    (0x6D|MOTOR_ADDR_DRV(motor))  //      0x6D            0x7D
#define TMC2041_DRVSTATUS(motor)   (0x6F|MOTOR_ADDR_DRV(motor))  //      0x6F            0x7F

#endif /* TMC2041_REGISTER_H */
