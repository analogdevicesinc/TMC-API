/*
 * TMC_LinearRamp.c
 *
 *  Created on: 09.11.2018
 *      Author: LK
 */
#include "LinearRamp1.h"
#include "../helpers/Functions.h"

void tmc_ramp_linear_init(TMC_LinearRamp *linearRamp)
{
	linearRamp->maxVelocity         = 0;
	linearRamp->targetPosition      = 0;
	linearRamp->targetVelocity      = 0;
	linearRamp->rampVelocity        = 0;
	linearRamp->rampPosition        = 0;
	linearRamp->acceleration        = 0;
	linearRamp->rampEnabled         = true;
	linearRamp->accumulatorVelocity = 0;
	linearRamp->accumulatorPosition = 0;
	linearRamp->rampMode            = TMC_RAMP_LINEAR_MODE_VELOCITY;
	linearRamp->dx                  = 0;
	linearRamp->state               = TMC_RAMP_LINEAR_STATE_IDLE;
	linearRamp->homingDistance      = TMC_RAMP_LINEAR_HOMING_DISTANCE;
	linearRamp->stopVelocity        = TMC_RAMP_LINEAR_STOP_VELOCITY;
}

void tmc_ramp_linear_set_enabled(TMC_LinearRamp *linearRamp, bool enabled)
{
	linearRamp->rampEnabled = enabled;
}

void tmc_ramp_linear_set_maxVelocity(TMC_LinearRamp *linearRamp, uint32_t maxVelocity)
{
	linearRamp->maxVelocity = maxVelocity;
}

void tmc_ramp_linear_set_targetPosition(TMC_LinearRamp *linearRamp, int32_t targetPosition)
{
	linearRamp->targetPosition = targetPosition;
}

void tmc_ramp_linear_set_rampPosition(TMC_LinearRamp *linearRamp, int32_t rampPosition)
{
	linearRamp->rampPosition = rampPosition;
}

void tmc_ramp_linear_set_targetVelocity(TMC_LinearRamp *linearRamp, int32_t targetVelocity)
{
	linearRamp->targetVelocity = targetVelocity;
}

void tmc_ramp_linear_set_rampVelocity(TMC_LinearRamp *linearRamp, int32_t rampVelocity)
{
	linearRamp->rampVelocity = rampVelocity;
}

void tmc_ramp_linear_set_acceleration(TMC_LinearRamp *linearRamp, int32_t acceleration)
{
	linearRamp->acceleration = acceleration;
}

void tmc_ramp_linear_set_mode(TMC_LinearRamp *linearRamp, TMC_LinearRamp_Mode mode)
{
	linearRamp->rampMode = mode;
}

void tmc_ramp_linear_set_homingDistance(TMC_LinearRamp *linearRamp, uint32_t homingDistance)
{
	linearRamp->homingDistance = homingDistance;
}

void tmc_ramp_linear_set_stopVelocity(TMC_LinearRamp *linearRamp, uint32_t stopVelocity)
{
	linearRamp->stopVelocity = stopVelocity;
}

bool tmc_ramp_linear_get_enabled(TMC_LinearRamp *linearRamp)
{
	return linearRamp->rampEnabled;
}

uint32_t tmc_ramp_linear_get_maxVelocity(TMC_LinearRamp *linearRamp)
{
	return linearRamp->maxVelocity;
}

int32_t tmc_ramp_linear_get_targetPosition(TMC_LinearRamp *linearRamp)
{
	return linearRamp->targetPosition;
}

int32_t tmc_ramp_linear_get_rampPosition(TMC_LinearRamp *linearRamp)
{
	return linearRamp->rampPosition;
}

int32_t tmc_ramp_linear_get_targetVelocity(TMC_LinearRamp *linearRamp)
{
	return linearRamp->targetVelocity;
}

int32_t tmc_ramp_linear_get_rampVelocity(TMC_LinearRamp *linearRamp)
{
	return linearRamp->rampVelocity;
}

int32_t tmc_ramp_linear_get_acceleration(TMC_LinearRamp *linearRamp)
{
	return linearRamp->acceleration;
}

int32_t tmc_ramp_linear_get_dx(TMC_LinearRamp *linearRamp)
{
	return linearRamp->dx;
}

TMC_LinearRamp_State tmc_ramp_linear_get_state(TMC_LinearRamp *linearRamp)
{
	return linearRamp->state;
}

TMC_LinearRamp_Mode tmc_ramp_linear_get_mode(TMC_LinearRamp *linearRamp)
{
	return linearRamp->rampMode;
}

uint32_t tmc_ramp_linear_get_homingDistance(TMC_LinearRamp *linearRamp)
{
	return linearRamp->homingDistance;
}

uint32_t tmc_ramp_linear_get_stopVelocity(TMC_LinearRamp *linearRamp)
{
	return linearRamp->stopVelocity;
}

void tmc_ramp_linear_reset_dx(TMC_LinearRamp *linearRamp)
{
	linearRamp->dx = 0;
}

void tmc_ramp_linear_compute(TMC_LinearRamp *linearRamp, uint32_t delta)
{
	tmc_ramp_linear_compute_velocity(linearRamp, delta);
	tmc_ramp_linear_compute_position(linearRamp, delta);
}

void tmc_ramp_linear_compute_velocity(TMC_LinearRamp *linearRamp, uint32_t delta)
{
	bool accelerating = linearRamp->rampVelocity != linearRamp->targetVelocity;
	if (linearRamp->rampEnabled)
	{
		// Add current acceleration to accumulator
		linearRamp->accumulatorVelocity += (linearRamp->acceleration * delta);

		// Emit the TMC_RAMP_LINEAR_ACCUMULATOR_DECIMALS decimal places and use the integer as dv
		int32_t dv = linearRamp->accumulatorVelocity >> TMC_RAMP_LINEAR_ACCUMULATOR_VELOCITY_DECIMALS;

		// Reset accumulator
		linearRamp->accumulatorVelocity -= dv << TMC_RAMP_LINEAR_ACCUMULATOR_VELOCITY_DECIMALS;

		// Add dv to rampVelocity, and regulate to target velocity
		if(linearRamp->rampVelocity < linearRamp->targetVelocity)
			linearRamp->rampVelocity = MIN(linearRamp->rampVelocity + dv, linearRamp->targetVelocity);
		else if(linearRamp->rampVelocity > linearRamp->targetVelocity)
			linearRamp->rampVelocity = MAX(linearRamp->rampVelocity - dv, linearRamp->targetVelocity);
	}
	else
	{
		// use target velocity directly
		linearRamp->rampVelocity = linearRamp->targetVelocity;
		// Reset accumulator
		linearRamp->accumulatorVelocity = 0;
	}

	// Accumulate required position change by current velocity
	linearRamp->accumulatorPosition += (linearRamp->rampVelocity * delta);
	linearRamp->dx = linearRamp->accumulatorPosition >> TMC_RAMP_LINEAR_ACCUMULATOR_POSITION_DECIMALS;
	linearRamp->accumulatorPosition -= linearRamp->dx << TMC_RAMP_LINEAR_ACCUMULATOR_POSITION_DECIMALS;

	if(linearRamp->dx == 0)
		return;

	// Change actual position determined by position change and delta-time
	linearRamp->rampPosition += (linearRamp->dx < 0) ? (-1) : (1);
	//linearRamp->rampPosition += (linearRamp->dx * delta);

	// Count acceleration steps needed for decelerating later
	linearRamp->accelerationSteps += (abs(linearRamp->rampVelocity) < abs(linearRamp->targetVelocity)) ? accelerating : -accelerating;
}

void tmc_ramp_linear_compute_position(TMC_LinearRamp *linearRamp, uint32_t delta)
{
	UNUSED(delta);
	if(linearRamp->rampEnabled && linearRamp->rampMode == TMC_RAMP_LINEAR_MODE_POSITION) {
		// Calculate steps needed to target
		int32_t diffx = 0;

		switch(linearRamp->state) {
		case TMC_RAMP_LINEAR_STATE_IDLE:
			if(linearRamp->rampVelocity == 0)
				linearRamp->accelerationSteps = 0;

			if(linearRamp->rampPosition == linearRamp->targetPosition)
				break;

			linearRamp->state = TMC_RAMP_LINEAR_STATE_DRIVING;
			break;
		case TMC_RAMP_LINEAR_STATE_DRIVING:
			// Calculate distance to target (positive = driving towards target)
			if(linearRamp->rampVelocity > 0)
				diffx = linearRamp->targetPosition - linearRamp->rampPosition;
			else if(linearRamp->rampVelocity < 0)
				diffx = -(linearRamp->targetPosition - linearRamp->rampPosition);
			else
				diffx = abs(linearRamp->targetPosition - linearRamp->rampPosition);

			// Steps left required for braking?
			// (+ 1 to compensate rounding (flooring) errors of the position accumulator)
			if(linearRamp->accelerationSteps + 1 >= diffx)
			{
				linearRamp->targetVelocity = 0;
				linearRamp->state = TMC_RAMP_LINEAR_STATE_BRAKING;
			}
			else
			{	// Driving - apply VMAX (this also allows mid-ramp VMAX changes)
				linearRamp->targetVelocity = (linearRamp->targetPosition > linearRamp->rampPosition) ? linearRamp->maxVelocity : -linearRamp->maxVelocity;
			}
			break;
		case TMC_RAMP_LINEAR_STATE_BRAKING:
			if(linearRamp->targetPosition == linearRamp->rampPosition)
			{
				if(abs(linearRamp->rampVelocity) <= linearRamp->stopVelocity)
				{	// Position reached, velocity within cutoff threshold (or zero)
					linearRamp->rampVelocity = 0; // actualVelocity = 0;
					linearRamp->targetVelocity = 0; // currCh->targetVelocity = 0;
					linearRamp->state = TMC_RAMP_LINEAR_STATE_IDLE;
				}
				else
				{
					// We're still too fast, we're going to miss the target position
					// Let the decceleration continue until velocity is zero, then either
					// home when within homing distance or start a new ramp (RAMP_DRIVING)
					// towards the target.
				}
			}
			else
			{
				if(linearRamp->rampVelocity != 0)
				{	// Still deccelerating

					// Calculate distance to target (positive = driving towards target)
					if(linearRamp->rampVelocity > 0)
						diffx = linearRamp->targetPosition - linearRamp->rampPosition;
					else if(linearRamp->rampVelocity < 0)
						diffx = -(linearRamp->targetPosition - linearRamp->rampPosition);
					else
						diffx = abs(linearRamp->targetPosition - linearRamp->rampPosition);

					// Enough space to accelerate again?
					// (+ 1 to compensate rounding (flooring) errors of the position accumulator)
					if(linearRamp->accelerationSteps + 1 < diffx)
					{
						linearRamp->state = TMC_RAMP_LINEAR_STATE_DRIVING;
					}
					break;
				}

				if(abs(linearRamp->targetPosition - linearRamp->rampPosition) <= linearRamp->homingDistance)
				{	// Within homing distance - drive with V_STOP velocity
					linearRamp->targetVelocity = (linearRamp->targetPosition > linearRamp->rampPosition)? linearRamp->stopVelocity : -linearRamp->stopVelocity;
				}
				else
				{	// Not within homing distance - start a new motion by switching to RAMP_IDLE
					// Since (targetPosition != actualPosition) a new ramp will be started.
					linearRamp->state = TMC_RAMP_LINEAR_STATE_IDLE;
				}
			}
			break;
		}
	} else {
		// use target position directly
		linearRamp->rampPosition = linearRamp->targetPosition;
	}
}
