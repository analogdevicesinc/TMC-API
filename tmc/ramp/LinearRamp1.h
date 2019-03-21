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
	uint32_t maxVelocity;
	int32_t targetPosition;
	int32_t rampPosition;
	int32_t targetVelocity;
	int32_t rampVelocity;
	int32_t acceleration;
	bool rampEnabled;
	int32_t accumulatorVelocity;
	int32_t accumulatorPosition;
	TMC_LinearRamp_Mode rampMode;
	int32_t dx;
	TMC_LinearRamp_State state;
	int32_t accelerationSteps;
	uint32_t homingDistance;
	uint32_t stopVelocity;
} TMC_LinearRamp;

void tmc_ramp_linear_init(TMC_LinearRamp *linearRamp);
void tmc_ramp_linear_compute(TMC_LinearRamp *linearRamp, uint32_t delta);
void tmc_ramp_linear_compute_velocity(TMC_LinearRamp *linearRamp, uint32_t delta);
void tmc_ramp_linear_compute_position(TMC_LinearRamp *linearRamp, uint32_t delta);

void tmc_ramp_linear_set_enabled(TMC_LinearRamp *linearRamp, bool enabled);
void tmc_ramp_linear_set_maxVelocity(TMC_LinearRamp *linearRamp, uint32_t maxVelocity);
void tmc_ramp_linear_set_targetPosition(TMC_LinearRamp *linearRamp, int32_t targetPosition);
void tmc_ramp_linear_set_rampPosition(TMC_LinearRamp *linearRamp, int32_t rampPosition);
void tmc_ramp_linear_set_targetVelocity(TMC_LinearRamp *linearRamp, int32_t targetVelocity);
void tmc_ramp_linear_set_rampVelocity(TMC_LinearRamp *linearRamp, int32_t rampVelocity);
void tmc_ramp_linear_set_acceleration(TMC_LinearRamp *linearRamp, int32_t acceleration);
void tmc_ramp_linear_set_mode(TMC_LinearRamp *linearRamp, TMC_LinearRamp_Mode mode);
void tmc_ramp_linear_set_homingDistance(TMC_LinearRamp *linearRamp, uint32_t homingDistance);
void tmc_ramp_linear_set_stopVelocity(TMC_LinearRamp *linearRamp, uint32_t stopVelocity);

bool tmc_ramp_linear_get_enabled(TMC_LinearRamp *linearRamp);
uint32_t tmc_ramp_linear_get_maxVelocity(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_targetPosition(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_rampPosition(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_targetVelocity(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_rampVelocity(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_acceleration(TMC_LinearRamp *linearRamp);
int32_t tmc_ramp_linear_get_dx(TMC_LinearRamp *linearRamp);
TMC_LinearRamp_State tmc_ramp_linear_get_state(TMC_LinearRamp *linearRamp);
TMC_LinearRamp_Mode tmc_ramp_linear_get_mode(TMC_LinearRamp *linearRamp);
uint32_t tmc_ramp_linear_get_homingDistance(TMC_LinearRamp *linearRamp);
uint32_t tmc_ramp_linear_get_stopVelocity(TMC_LinearRamp *linearRamp);

void tmc_ramp_linear_reset_dx(TMC_LinearRamp *linearRamp);

#endif /* TMC_RAMP_LINEARRAMP_H_ */
