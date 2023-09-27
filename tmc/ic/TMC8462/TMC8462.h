/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC8462_H_
#define TMC_IC_TMC8462_H_

#include "tmc/helpers/Constants.h"
#include "tmc/helpers/API_Header.h"
#include "TMC8462_Register.h"
#include "TMC8462_Constants.h"
#include "TMC8462_Fields.h"

// Helper macros
#define TMC8462_FIELD_READ(tdef, read, address, mask, shift) \
	FIELD_GET(read(tdef, address), mask, shift)
#define TMC8462_FIELD_WRITE(tdef, read, write, address, mask, shift, value) \
	(write(tdef, address, FIELD_SET(read(tdef, address), mask, shift, value)))

typedef struct {
	ConfigurationTypeDef *config_esc;
	ConfigurationTypeDef *config_mfc;
} TMC8462TypeDef;

// Preparation functions to prepare r/w access on specific registers
void tmc8462_esc_read(TMC8462TypeDef *tmc8462, uint16_t address);
void tmc8462_esc_write(TMC8462TypeDef *tmc8462, uint16_t address);
void tmc8462_mfc_read(TMC8462TypeDef *tmc8462, uint16_t address);
void tmc8462_mfc_write(TMC8462TypeDef *tmc8462, uint16_t address);

void tmc8462_esc_read_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len);
uint8_t tmc8462_esc_read_8(TMC8462TypeDef *tmc8462, uint16_t address);
uint16_t tmc8462_esc_read_16(TMC8462TypeDef *tmc8462, uint16_t address);
uint32_t tmc8462_esc_read_32(TMC8462TypeDef *tmc8462, uint16_t address);
void tmc8462_esc_write_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len);
void tmc8462_esc_write_8(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t value);
void tmc8462_esc_write_16(TMC8462TypeDef *tmc8462, uint16_t address, uint16_t value);
void tmc8462_esc_write_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t value);

void tmc8462_mfc_read_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len);
void tmc8462_mfc_read_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t *value);
void tmc8462_mfc_read_64(TMC8462TypeDef *tmc8462, uint16_t address, uint64_t *value);
void tmc8462_mfc_read_auto(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t *value);
void tmc8462_mfc_write_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len);
void tmc8462_mfc_write_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t value);
void tmc8462_mfc_write_64(TMC8462TypeDef *tmc8462, uint16_t address, uint64_t value);
void tmc8462_mfc_write_auto(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t *value);

/**
 * Initializes configurations for both, ESC and MFC block
 * @param tmc8462 Your TMC8462 instance
 * @param tmc8462_config_esc The configuration for the ESC
 * @param tmc8462_config_mfc The configuration for the MFC block
 */
void tmc8462_initConfig(TMC8462TypeDef *tmc8462, ConfigurationTypeDef *tmc8462_config_esc, ConfigurationTypeDef *tmc8462_config_mfc);

#endif /* TMC_IC_TMC8462_H_ */
