/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC6200_H_
#define TMC_IC_TMC6200_H_

#include "tmc/helpers/API_Header.h"
#include "TMC6200_Register.h"
#include "TMC6200_Constants.h"
#include "TMC6200_Fields.h"

// Helper macros
#define TMC6200_FIELD_READ(tdef, address, mask, shift) \
	FIELD_GET(tmc6200_readInt(tdef, address), mask, shift)
#define TMC6200_FIELD_UPDATE(tdef, address, mask, shift, value) \
	(tmc6200_writeInt(tdef, address, FIELD_SET(tmc6200_readInt(tdef, address), mask, shift, value)))

int32_t tmc6200_readInt(uint8_t motor, uint8_t address);
void tmc6200_writeInt(uint8_t motor, uint8_t address, int32_t value);

#endif /* TMC_IC_TMC6630_H_ */
