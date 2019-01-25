/*
 * CRC.h
 *
 *  Created on: 04.12.2017
 *      Author: LH
 */

#ifndef TMC_HELPERS_CRC_H_
#define TMC_HELPERS_CRC_H_

	#include "Types.h"

	// Amount of CRC tables available
	// Each table takes ~260 bytes (257 bytes, one bool and structure padding)
	#define CRC_TABLE_COUNT 2

	uint8 tmc_fillCRC8Table(uint8 polynomial, bool isReflected, uint8 index);
	uint8 tmc_CRC8(uint8 *data, uint32 bytes, uint8 index);

	uint8 tmc_tableGetPolynomial(uint8 index);
	bool  tmc_tableIsReflected(uint8 index);

#endif /* TMC_HELPERS_CRC_H_ */
