/*
 * Ramp.c
 *
 *  Created on: 09.11.2018
 *      Author: LK
 */

#include "Ramp.h"

void tmc_ramp_init(void *ramp, TMC_RampType type)
{
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		tmc_ramp_linear_init((TMC_LinearRamp *)ramp);
		break;
	}
}

void tmc_ramp_compute(void *ramp, TMC_RampType type, uint32 delta)
{
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		tmc_ramp_linear_compute((TMC_LinearRamp *)ramp, delta);
		break;
	}
}

int32 tmc_ramp_get_rampVelocity(void *ramp, TMC_RampType type)
{
	int32 v = 0;
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
		v = tmc_ramp_linear_get_rampVelocity((TMC_LinearRamp *)ramp);
		break;
	}
	return v;
}

int32 tmc_ramp_get_rampPosition(void *ramp, TMC_RampType type)
{
	int32 x = 0;
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
		x = tmc_ramp_linear_get_rampPosition((TMC_LinearRamp *)ramp);
		break;
	}
	return x;
}

bool tmc_ramp_get_enabled(void *ramp, TMC_RampType type)
{
	bool enabled = FALSE;
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
		enabled = tmc_ramp_linear_get_enabled((TMC_LinearRamp *)ramp);
		break;
	}
	return enabled;
}

void tmc_ramp_set_enabled(void *ramp, TMC_RampType type, bool enabled)
{
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		tmc_ramp_linear_set_enabled((TMC_LinearRamp *)ramp, enabled);
		break;
	}
}

void tmc_ramp_toggle_enabled(void *ramp, TMC_RampType type)
{
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		tmc_ramp_linear_set_enabled((TMC_LinearRamp *)ramp, !tmc_ramp_get_enabled(ramp, type));
		break;
	}
}

int32 tmc_ramp_get_dx(void *ramp, TMC_RampType type)
{
	int32 dx = 0;
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		dx = tmc_ramp_linear_get_dx((TMC_LinearRamp *)ramp);
		break;
	}
	return dx;
}

void tmc_ramp_reset_dx(void *ramp, TMC_RampType type)
{
	switch(type) {
	case TMC_RAMP_TYPE_LINEAR:
	default:
		tmc_ramp_linear_reset_dx((TMC_LinearRamp *)ramp);
		break;
	}
}
