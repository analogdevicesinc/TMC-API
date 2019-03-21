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
		uint32_t maxVelocity;
		int32_t targetPosition;
		int32_t rampPosition;
		int32_t targetVelocity;
		int32_t rampVelocity;
		int32_t acceleration;
		int lastdVRest;
		int lastdXRest;
		uint8_t rampEnabled;
	} TMC_LinearRamp;

	void tmc_linearRamp_init(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampVelocity(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampPosition(TMC_LinearRamp *linearRamp);

#endif /* TMC_LINEAR_RAMP_H_ */
