/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC5272_H_

#include "tmc/helpers/API_Header.h"
#include "tmc/helpers/Constants.h"
#include "../TMC5272/TMC5272_Register.h"
#include "TMC5272_Constants.h"
#include "../TMC5272/TMC5272_Fields.h"

// Helper macros
#define TMC5272_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc5272_readInt(tdef, address), mask, shift)
#define TMC5272_FIELD_WRITE(tdef, address, mask, shift, value) \
	(tmc5272_writeInt(tdef, address, FIELD_SET(tmc5272_readInt(tdef, address), mask, shift, value)))

// Typedefs
typedef struct
{
	ConfigurationTypeDef *config;
	int32_t oldX[TMC5272_MOTORS];
	int32_t velocity[TMC5272_MOTORS];
	uint32_t oldTick;
	int32_t registerResetState[TMC5272_REGISTER_COUNT];
	uint8_t registerAccess[TMC5272_REGISTER_COUNT];
	uint8_t slaveAddress;
} TMC5272TypeDef;

typedef void (*tmc5272_callback)(TMC5272TypeDef*, ConfigState);

// Default Register values
#define R00 0x00000008  // GCONF
#define R0A 0x00000020  // DRVCONF
#define R10 0x00070A03  // IHOLD_IRUN
#define R11 0x0000000A  // TPOWERDOWN
#define R2A 0x0000000A  // D1
#define R2B 0x0000000A  // VSTOP
#define R30 0x0000000A  // D2

#define R3A 0x00010000  // ENC_CONST

#define R52 0x0B920F25  // OTW_OV_VTH
#define R60 0xAAAAB554  // MSLUT[0]
#define R61 0x4A9554AA  // MSLUT[1]
#define R62 0x24492929  // MSLUT[2]
#define R63 0x10104222  // MSLUT[3]
#define R64 0xFBFFFFFF  // MSLUT[4]
#define R65 0xB5BB777D  // MSLUT[5]
#define R66 0x49295556  // MSLUT[6]
#define R67 0x00404222  // MSLUT[7]
#define R68 0xFFFF8056  // MSLUT[8]
#define R69 0x00F70000  // MSLUT[9]

#define R6C 0x00410153  // CHOPCONF
#define R70 0xC44C001E  // PWMCONF
#define R74 0x00000000  // PWMCONF


//void tmc5272_writeDatagram(TMC5272TypeDef *tmc5272, uint8_t address, uint8_t x1, uint8_t x2, uint8_t x3, uint8_t x4);
void tmc5272_writeInt(TMC5272TypeDef *tmc5272, uint8_t address, int32_t value);
int32_t tmc5272_readInt(TMC5272TypeDef *tmc5272, uint8_t address);

void tmc5272_init(TMC5272TypeDef *tmc5272, uint8_t channel, ConfigurationTypeDef *config);
//void tmc5272_fillShadowRegisters(TMC5272TypeDef *tmc5272);
uint8_t tmc5272_reset(TMC5272TypeDef *tmc5272);
uint8_t tmc5272_restore(TMC5272TypeDef *tmc5272);
uint8_t tmc5272_getSlaveAddress(TMC5272TypeDef *tmc5272);
void tmc5272_setSlaveAddress(TMC5272TypeDef *tmc5272, uint8_t slaveAddress);
void tmc5272_setRegisterResetState(TMC5272TypeDef *tmc5272, const int32_t *resetState);
void tmc5272_setCallback(TMC5272TypeDef *tmc5272, tmc5272_callback callback);
void tmc5272_periodicJob(TMC5272TypeDef *tmc5272, uint32_t tick);

void tmc5272_rotate(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity);
void tmc5272_right(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity);
void tmc5272_left(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t velocity);
void tmc5272_stop(TMC5272TypeDef *tmc5272, uint8_t motor);
void tmc5272_moveTo(TMC5272TypeDef *tmc5272, uint8_t motor, int32_t position, uint32_t velocityMax);
void tmc5272_moveBy(TMC5272TypeDef *tmc5272, uint8_t motor, uint32_t velocityMax, int32_t *ticks);


uint8_t tmc5272_consistencyCheck(TMC5272TypeDef *tmc5272);

#endif /* TMC_IC_TMC5272_H_ */
