/*
 * LinearRamp.h
 *
 *  Created on: 23.07.2018
 *      Author: ed
 */

#ifndef TMC_LINEAR_RAMP_H_
#define TMC_LINEAR_RAMP_H_

	#include "../helpers/API_Header.h"
	#include "../helpers/Functions.h"

	typedef struct
	{
		u32 maxVelocity;
		s32 targetPosition;
		s32 rampPosition;
		s32 targetVelocity;
		s32 rampVelocity;
		s32 acceleration;
		int lastdVRest;
		int lastdXRest;
		u8 rampEnabled;
	} TMC_LinearRamp;

	void tmc_linearRamp_init(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampVelocity(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampPosition(TMC_LinearRamp *linearRamp);

#endif /* TMC_LINEAR_RAMP_H_ */
