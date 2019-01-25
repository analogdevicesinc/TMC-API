/*
 * TMC8690.h
 *
 *  Created on: 18.07.2016
 *      Author: bs, ed
 */

#ifndef TMC_IC_TMC8690_H_
#define TMC_IC_TMC8690_H_
	#define ENABLE_IC_SCOPE

	#include "../../helpers/API_Header.h"
	#include "TMC8690_Register.h"
	#include "TMC8690_Mask_Shift.h"

	// Helper macros
	#define TMC8690_FIELD_READ(address, mask, shift) \
		FIELD_GET(tmc8690_readInt(address), mask, shift)
	#define TMC8690_FIELD_UPDATE(address, mask, shift, value) \
		(tmc8690_writeInt(address, FIELD_SET(tmc8690_readInt(address), mask, shift, value)))

	//void tmc8690_init();
	//void tmc8690_periodicJob(u32 actualSystick);

#endif /* TMC_IC_TMC8690_H_ */
