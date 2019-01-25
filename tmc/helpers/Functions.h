/*
 * Functions.h
 *
 *  Created on: 23.07.2018
 *      Author: ed
 */

#ifndef TMC_FUNCTIONS_H_
#define TMC_FUNCTIONS_H_

	#include "API_Header.h"

	int tmc_limitInt(int value, int min, int max);
	s64 tmc_limitS64(s64 value, s64 min, s64 max);

	int tmc_sqrti(int x);

#endif /* TMC_FUNCTIONS_H_ */
