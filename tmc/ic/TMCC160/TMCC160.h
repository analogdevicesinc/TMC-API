/*
 * TMCC160.h
 *
 *  Created on: 06.10.2016
 *      Author: ed
 */

#ifndef TMC_IC_TMCC160_H_
#define TMC_IC_TMCC160_H_

	#include "../../helpers/API_Header.h"
	#include "TMCC160_Register.h"

	void tmcc160_init();
	void tmcc160_periodicJob(u32 actualSystick);

	// spi access functions
	void tmcc160_writeInt(uint8 address, int value);
	int tmcc160_readInt(uint8 address);
	void tmcc160_writeDatagram(uint8 address, uint8 x3, uint8 x2, uint8 x1, uint8 x0);
	void tmcc160_default_spi_delay();

	// === modes of operation ===

	// torque mode
	void tmcc160_setTargetTorque_raw(s32 targetTorque);
	s32 tmcc160_getTargetTorque_raw();
	s32 tmcc160_getActualTorque_raw();
	s32 tmcc160_getActualRampTorque_raw();

	void tmcc160_setTargetTorque_mA(s32 targetTorque);
	s32 tmcc160_getTargetTorque_mA();
	s32 tmcc160_getActualTorque_mA();
	s32 tmcc160_getActualRampTorque_mA();

	// velocity mode
	void tmcc160_setTargetVelocity(s32 targetVelocity);
	s32 tmcc160_getTargetVelocity();
	s32 tmcc160_getActualVelocity();
	s32 tmcc160_getActualRampVelocity();

	// position mode
	void tmcc160_setAbsolutTargetPosition(s32 targetPosition);
	void tmcc160_setRelativeTargetPosition(s32 relativePosition);
	s32 tmcc160_getTargetPosition();
	void tmcc160_setActualPosition(s32 actualPosition);
	s32 tmcc160_getActualPosition();
	s32 tmcc160_getActualRampPosition();

#endif /* TMC_IC_TMCC160_H_ */
