/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC8462.h"

extern uint8_t tmc8462_readWrite(uint8_t channel, uint8_t data, uint8_t lastTransfer);

void tmc8462_esc_read(TMC8462TypeDef *tmc8462, uint16_t address)
{
	tmc8462_readWrite(tmc8462->config_esc->channel, address >> 5, false);
	tmc8462_readWrite(tmc8462->config_esc->channel, (address << 3) | TMC8462_CMD_ADDR_EXT, false);
	tmc8462_readWrite(tmc8462->config_esc->channel, ((address >> 8) & 0xE0) | (TMC8462_CMD_READ_WAIT << 2), false);
	tmc8462_readWrite(tmc8462->config_esc->channel, 0xFF, false);
}

void tmc8462_esc_write(TMC8462TypeDef *tmc8462, uint16_t address)
{
	tmc8462_readWrite(tmc8462->config_esc->channel, address >> 5, false);
	tmc8462_readWrite(tmc8462->config_esc->channel, (address << 3) | TMC8462_CMD_ADDR_EXT, false);
	tmc8462_readWrite(tmc8462->config_esc->channel, ((address >> 8) & 0xE0) | (TMC8462_CMD_WRITE << 2), false);
}

void tmc8462_mfc_read(TMC8462TypeDef *tmc8462, uint16_t address)
{
	tmc8462_readWrite(tmc8462->config_mfc->channel, address >> 5, false);
	tmc8462_readWrite(tmc8462->config_mfc->channel, (address << 3) | TMC8462_CMD_ADDR_EXT, false);
	tmc8462_readWrite(tmc8462->config_mfc->channel, ((address >> 8) & 0xE0) | (TMC8462_CMD_READ_WAIT << 2), false);
	tmc8462_readWrite(tmc8462->config_mfc->channel, 0xFF, false);
}

void tmc8462_mfc_write(TMC8462TypeDef *tmc8462, uint16_t address)
{
	tmc8462_readWrite(tmc8462->config_mfc->channel, address >> 5, false);
	tmc8462_readWrite(tmc8462->config_mfc->channel, (address << 3) | TMC8462_CMD_ADDR_EXT, false);
	tmc8462_readWrite(tmc8462->config_mfc->channel, ((address >> 8) & 0xE0) | (TMC8462_CMD_WRITE << 2), false);
}

void tmc8462_esc_read_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len)
{
	tmc8462_esc_read(tmc8462, address);

	for (uint16_t i = 0; i < len; i++)
		data_ptr[i] = tmc8462_readWrite(tmc8462->config_esc->channel, (i < len - 1) ? 0x00 : 0xFF, (i < len - 1) ? false : true);
}

uint8_t tmc8462_esc_read_8(TMC8462TypeDef *tmc8462, uint16_t address)
{
	uint8_t buffer = 0;

	tmc8462_esc_read_data(tmc8462, &buffer, address, 1);

	return buffer;
}

uint16_t tmc8462_esc_read_16(TMC8462TypeDef *tmc8462, uint16_t address)
{
	uint8_t data[2];

	tmc8462_esc_read_data(tmc8462, data, address, 2);

	return _8_16(data[1], data[0]);
}

uint32_t tmc8462_esc_read_32(TMC8462TypeDef *tmc8462, uint16_t address)
{
	uint8_t data[4];

	tmc8462_esc_read_data(tmc8462, data, address, 4);

	return _8_32(data[3], data[2], data[1], data[0]);
}

void tmc8462_esc_write_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len)
{
	tmc8462_esc_write(tmc8462, address);

	for(uint16_t i = 0; i < len; i++)
		tmc8462_readWrite(tmc8462->config_esc->channel, data_ptr[i], (i < len - 1) ? false : true);
}

void tmc8462_esc_write_8(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t value)
{
	tmc8462_esc_write_data(tmc8462, &value, address, 1);
}

void tmc8462_esc_write_16(TMC8462TypeDef *tmc8462, uint16_t address, uint16_t value)
{
	uint8_t data[2];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	tmc8462_esc_write_data(tmc8462, data, address, 2);
}

void tmc8462_esc_write_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t value)
{
	uint8_t data[4];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);
	tmc8462_esc_write_data(tmc8462, data, address, 4);
}

void tmc8462_mfc_read_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len)
{
	tmc8462_mfc_read(tmc8462, address);

	for (uint16_t i = 0; i < len; i++)
		data_ptr[i] = tmc8462_readWrite(tmc8462->config_mfc->channel, (i < len - 1) ? 0x00 : 0xFF, (i < len - 1) ? false : true);
}

void tmc8462_mfc_read_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t *value)
{
	uint8_t data[4];

	tmc8462_mfc_read_data(tmc8462, data, address, 4);

	*value = _8_32(data[3], data[2], data[1], data[0]);
}

void tmc8462_mfc_read_64(TMC8462TypeDef *tmc8462, uint16_t address, uint64_t *value)
{
	uint8_t data[8];

	tmc8462_mfc_read_data(tmc8462, data, address, 8);

	*value = _8_64((uint64_t)data[7], (uint64_t)data[6], (uint64_t)data[5], (uint64_t)data[4], (uint64_t)data[3], (uint64_t)data[2], (uint64_t)data[1], (uint64_t)data[0]);
}

void tmc8462_mfc_read_auto(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t *value)
{
	if(address == TMC8462_MFC_SPI_RX_DATA || address == TMC8462_MFC_SPI_TX_DATA || address == TMC8462_MFC_PWM4) {
		// 64 bit
		tmc8462_mfc_read_data(tmc8462, value, address, 8);
	} else {
		// 32 bit
		tmc8462_mfc_read_data(tmc8462, value, address, 4);
	}
}

void tmc8462_mfc_write_data(TMC8462TypeDef *tmc8462, uint8_t *data_ptr, uint16_t address, uint16_t len)
{
	tmc8462_mfc_write(tmc8462, address);

	for (uint16_t i = 0; i < len; i++)
		tmc8462_readWrite(tmc8462->config_mfc->channel, data_ptr[i], (i < len - 1) ? false : true);
}

void tmc8462_mfc_write_32(TMC8462TypeDef *tmc8462, uint16_t address, uint32_t value)
{
	uint8_t data[4];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);

	tmc8462_mfc_write_data(tmc8462, data, address, 4);
}

void tmc8462_mfc_write_64(TMC8462TypeDef *tmc8462, uint16_t address, uint64_t value)
{
	uint8_t data[8];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);
	data[4] = BYTE(value, 4);
	data[5] = BYTE(value, 5);
	data[6] = BYTE(value, 6);
	data[7] = BYTE(value, 7);

	tmc8462_mfc_write_data(tmc8462, data, address, 8);
}

void tmc8462_mfc_write_auto(TMC8462TypeDef *tmc8462, uint16_t address, uint8_t *value)
{
	if(address == TMC8462_MFC_SPI_RX_DATA || address == TMC8462_MFC_SPI_TX_DATA || address == TMC8462_MFC_PWM4) {
		// 64 bit
		tmc8462_mfc_write_data(tmc8462, value, address, 8);
	} else {
		// 32 bit
		tmc8462_mfc_write_data(tmc8462, value, address, 4);
	}
}

void tmc8462_initConfig(TMC8462TypeDef *tmc8462, ConfigurationTypeDef *tmc8462_config_esc, ConfigurationTypeDef *tmc8462_config_mfc)
{
	tmc8462->config_esc = tmc8462_config_esc;
	tmc8462->config_mfc = tmc8462_config_mfc;

	while(TMC8462_FIELD_READ(tmc8462, tmc8462_esc_read_16, TMC8462_ESC_PDI_CTRL, TMC8462_ESC_PDI_MODE_MASK, TMC8462_ESC_PDI_MODE_SHIFT) != TMC8462_PDI_SPI_SLAVE);
	tmc8462_esc_write_16(tmc8462, TMC8462_ESC_AL_STATUS, FIELD_SET(TMC8462_EC_STATE_INIT, TMC8462_ESC_AL_ERROR_MASK, TMC8462_ESC_AL_ERROR_SHIFT, true));
	tmc8462_esc_write_16(tmc8462, TMC8462_ESC_AL_CODE, 0x0000);
	tmc8462_esc_write_16(tmc8462, TMC8462_ESC_AL_EVENT_MASK_LO, 0xFF0E);
}
