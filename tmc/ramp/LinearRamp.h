/*******************************************************************************
* Copyright © 2018 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_LINEAR_RAMP_H_
#define TMC_LINEAR_RAMP_H_

	#include "tmc/helpers/API_Header.h"
	#include "tmc/helpers/Functions.h"

	typedef struct
	{
		uint32_t maxVelocity;
		int32_t targetPosition;
		int32_t rampPosition;
		int32_t targetVelocity;
		int32_t rampVelocity;
		int32_t acceleration;
		uint16_t encoderSteps;
		int32_t lastdVRest;
		int32_t lastdXRest;
		uint8_t rampEnabled;
	} TMC_LinearRamp;

	#ifdef __cplusplus
	extern "C" {
	#endif

	void tmc_linearRamp_init(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampVelocity(TMC_LinearRamp *linearRamp);
	void tmc_linearRamp_computeRampPosition(TMC_LinearRamp *linearRamp);

	#ifdef __cplusplus
	}
	#endif

#endif /* TMC_LINEAR_RAMP_H_ */
