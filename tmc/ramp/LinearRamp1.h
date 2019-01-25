/*
 * LinearRamp.h
 *
 *  Created on: 09.11.2018
 *      Author: LK
 */

#ifndef TMC_RAMP_LINEARRAMP_H_
#define TMC_RAMP_LINEARRAMP_H_

#include "../helpers/API_Header.h"
#include "Ramp.h"

// Position mode: When hitting the target position a velocity below the V_STOP threshold will be cut off to velocity 0
#define TMC_RAMP_LINEAR_HOMING_DISTANCE 5

// Position mode: When barely missing the target position by HOMING_DISTANCE or less, the remainder will be driven with V_STOP velocity
#define TMC_RAMP_LINEAR_STOP_VELOCITY 5

#define TMC_RAMP_LINEAR_ACCUMULATOR_VELOCITY_DECIMALS 17
#define TMC_RAMP_LINEAR_ACCUMULATOR_POSITION_DECIMALS 17

typedef enum {
	TMC_RAMP_LINEAR_MODE_VELOCITY,
	TMC_RAMP_LINEAR_MODE_POSITION
} TMC_LinearRamp_Mode;

typedef enum {
	TMC_RAMP_LINEAR_STATE_IDLE,
	TMC_RAMP_LINEAR_STATE_DRIVING,
	TMC_RAMP_LINEAR_STATE_BRAKING
} TMC_LinearRamp_State;

typedef struct
{
	uint32 maxVelocity;
	int32 targetPosition;
	int32 rampPosition;
	int32 targetVelocity;
	int32 rampVelocity;
	int32 acceleration;
	bool rampEnabled;
	int32 accumulatorVelocity;
	int32 accumulatorPosition;
	TMC_LinearRamp_Mode rampMode;
	int32 dx;
	TMC_LinearRamp_State state;
	int32 accelerationSteps;
	uint32 homingDistance;
	uint32 stopVelocity;
} TMC_LinearRamp;

void tmc_ramp_linear_init(TMC_LinearRamp *linearRamp);
void tmc_ramp_linear_compute(TMC_LinearRamp *linearRamp, uint32 delta);
void tmc_ramp_linear_compute_velocity(TMC_LinearRamp *linearRamp, uint32 delta);
void tmc_ramp_linear_compute_position(TMC_LinearRamp *linearRamp, uint32 delta);

void tmc_ramp_linear_set_enabled(TMC_LinearRamp *linearRamp, bool enabled);
void tmc_ramp_linear_set_maxVelocity(TMC_LinearRamp *linearRamp, uint32 maxVelocity);
void tmc_ramp_linear_set_targetPosition(TMC_LinearRamp *linearRamp, int32 targetPosition);
void tmc_ramp_linear_set_rampPosition(TMC_LinearRamp *linearRamp, int32 rampPosition);
void tmc_ramp_linear_set_targetVelocity(TMC_LinearRamp *linearRamp, int32 targetVelocity);
void tmc_ramp_linear_set_rampVelocity(TMC_LinearRamp *linearRamp, int32 rampVelocity);
void tmc_ramp_linear_set_acceleration(TMC_LinearRamp *linearRamp, int32 acceleration);
void tmc_ramp_linear_set_mode(TMC_LinearRamp *linearRamp, TMC_LinearRamp_Mode mode);
void tmc_ramp_linear_set_homingDistance(TMC_LinearRamp *linearRamp, uint32 homingDistance);
void tmc_ramp_linear_set_stopVelocity(TMC_LinearRamp *linearRamp, uint32 stopVelocity);

bool tmc_ramp_linear_get_enabled(TMC_LinearRamp *linearRamp);
uint32 tmc_ramp_linear_get_maxVelocity(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_targetPosition(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_rampPosition(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_targetVelocity(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_rampVelocity(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_acceleration(TMC_LinearRamp *linearRamp);
int32 tmc_ramp_linear_get_dx(TMC_LinearRamp *linearRamp);
TMC_LinearRamp_State tmc_ramp_linear_get_state(TMC_LinearRamp *linearRamp);
TMC_LinearRamp_Mode tmc_ramp_linear_get_mode(TMC_LinearRamp *linearRamp);
uint32 tmc_ramp_linear_get_homingDistance(TMC_LinearRamp *linearRamp);
uint32 tmc_ramp_linear_get_stopVelocity(TMC_LinearRamp *linearRamp);

void tmc_ramp_linear_reset_dx(TMC_LinearRamp *linearRamp);

#endif /* TMC_RAMP_LINEARRAMP_H_ */
