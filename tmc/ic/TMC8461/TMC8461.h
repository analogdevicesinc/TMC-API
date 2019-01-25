/*
 * TMC8461.h
 *
 *  Created on: 30.05.2017
 *      Author: LK
 */

#ifndef TMC_IC_TMC8461_H_
#define TMC_IC_TMC8461_H_

#include "../../helpers/Constants.h"
#include "../../helpers/API_Header.h"
#include "TMC8461_Register.h"
#include "TMC8461_Constants.h"
#include "TMC8461_Fields.h"

// Helper macros
#define TMC8461_FIELD_READ(tdef, read, address, mask, shift) \
	FIELD_GET(read(tdef, address), mask, shift)
#define TMC8461_FIELD_UPDATE(tdef, read, write, address, mask, shift, value) \
	(write(tdef, address, FIELD_SET(read(tdef, address), mask, shift, value)))

typedef struct {
	ConfigurationTypeDef *config_esc;
	ConfigurationTypeDef *config_mfc;
} TMC8461TypeDef;

// Preparation functions to prepare r/w access on specific registers
void tmc8461_esc_read(TMC8461TypeDef *tmc8461, u16 address);
void tmc8461_esc_write(TMC8461TypeDef *tmc8461, u16 address);
void tmc8461_mfc_read(TMC8461TypeDef *tmc8461, u16 address);
void tmc8461_mfc_write(TMC8461TypeDef *tmc8461, u16 address);

void tmc8461_esc_read_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len);
u8 tmc8461_esc_read_8(TMC8461TypeDef *tmc8461, u16 address);
u16 tmc8461_esc_read_16(TMC8461TypeDef *tmc8461, u16 address);
u32 tmc8461_esc_read_32(TMC8461TypeDef *tmc8461, u16 address);
void tmc8461_esc_write_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len);
void tmc8461_esc_write_8(TMC8461TypeDef *tmc8461, u16 address, u8 value);
void tmc8461_esc_write_16(TMC8461TypeDef *tmc8461, u16 address, u16 value);
void tmc8461_esc_write_32(TMC8461TypeDef *tmc8461, u16 address, u32 value);

void tmc8461_mfc_read_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len);
void tmc8461_mfc_read_32(TMC8461TypeDef *tmc8461, u16 address, u32 *value);
void tmc8461_mfc_read_64(TMC8461TypeDef *tmc8461, u16 address, u64 *value);
void tmc8461_mfc_read_auto(TMC8461TypeDef *tmc8461, u16 address, u8 *value);
void tmc8461_mfc_write_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len);
void tmc8461_mfc_write_32(TMC8461TypeDef *tmc8461, u16 address, u32 value);
void tmc8461_mfc_write_64(TMC8461TypeDef *tmc8461, u16 address, u64 value);
void tmc8461_mfc_write_auto(TMC8461TypeDef *tmc8461, u16 address, u8 *value);

/**
 * Initializes configurations for both, ESC and MFC block
 * @param tmc8461 Your TMC8461 instance
 * @param tmc8461_config_esc The configuration for the ESC
 * @param tmc8461_config_mfc The configuration for the MFC block
 */
void tmc8461_initConfig(TMC8461TypeDef *tmc8461, ConfigurationTypeDef *tmc8461_config_esc, ConfigurationTypeDef *tmc8461_config_mfc);

#endif /* TMC_IC_TMC8461_H_ */
