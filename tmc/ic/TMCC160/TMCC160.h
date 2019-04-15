/*
 * TMCC160.h
 *
 *  Created on: 06.10.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMCC160_H_
#define TMC_IC_TMCC160_H_

	#include "tmc/helpers/API_Header.h"
	#include "TMCC160_Register.h"

	void tmcc160_init();
	void tmcc160_periodicJob(uint32_t actualSystick);

	// spi access functions
	void tmcc160_writeInt(uint8_t address, int value);
	int tmcc160_readInt(uint8_t address);
	void tmcc160_writeDatagram(uint8_t address, uint8_t x3, uint8_t x2, uint8_t x1, uint8_t x0);
	void tmcc160_default_spi_delay();

	// === modes of operation ===

	// torque mode
	void tmcc160_setTargetTorque_raw(int32_t targetTorque);
	int32_t tmcc160_getTargetTorque_raw();
	int32_t tmcc160_getActualTorque_raw();
	int32_t tmcc160_getActualRampTorque_raw();

	void tmcc160_setTargetTorque_mA(int32_t targetTorque);
	int32_t tmcc160_getTargetTorque_mA();
	int32_t tmcc160_getActualTorque_mA();
	int32_t tmcc160_getActualRampTorque_mA();

	// velocity mode
	void tmcc160_setTargetVelocity(int32_t targetVelocity);
	int32_t tmcc160_getTargetVelocity();
	int32_t tmcc160_getActualVelocity();
	int32_t tmcc160_getActualRampVelocity();

	// position mode
	void tmcc160_setAbsolutTargetPosition(int32_t targetPosition);
	void tmcc160_setRelativeTargetPosition(int32_t relativePosition);
	int32_t tmcc160_getTargetPosition();
	void tmcc160_setActualPosition(int32_t actualPosition);
	int32_t tmcc160_getActualPosition();
	int32_t tmcc160_getActualRampPosition();

#endif /* TMC_IC_TMCC160_H_ */
