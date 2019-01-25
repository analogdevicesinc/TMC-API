/*
 * TMC8461.c
 *
 *  Created on: 30.05.2017
 *      Author: LK
 */

#include "TMC8461.h"

extern u8 tmc8461_readWrite(u8 channel, u8 data, u8 lastTransfer);

void tmc8461_esc_read(TMC8461TypeDef *tmc8461, u16 address)
{
	tmc8461_readWrite(tmc8461->config_esc->channel, address >> 5, FALSE);
	tmc8461_readWrite(tmc8461->config_esc->channel, (address << 3) | TMC8461_CMD_ADDR_EXT, FALSE);
	tmc8461_readWrite(tmc8461->config_esc->channel, ((address >> 8) & 0xE0) | (TMC8461_CMD_READ_WAIT << 2), FALSE);
	tmc8461_readWrite(tmc8461->config_esc->channel, 0xFF, FALSE);
}

void tmc8461_esc_write(TMC8461TypeDef *tmc8461, u16 address)
{
	tmc8461_readWrite(tmc8461->config_esc->channel, address >> 5, FALSE);
	tmc8461_readWrite(tmc8461->config_esc->channel, (address << 3) | TMC8461_CMD_ADDR_EXT, FALSE);
	tmc8461_readWrite(tmc8461->config_esc->channel, ((address >> 8) & 0xE0) | (TMC8461_CMD_WRITE << 2), FALSE);
}

void tmc8461_mfc_read(TMC8461TypeDef *tmc8461, u16 address)
{
	tmc8461_readWrite(tmc8461->config_mfc->channel, address >> 5, FALSE);
	tmc8461_readWrite(tmc8461->config_mfc->channel, (address << 3) | TMC8461_CMD_ADDR_EXT, FALSE);
	tmc8461_readWrite(tmc8461->config_mfc->channel, ((address >> 8) & 0xE0) | (TMC8461_CMD_READ_WAIT << 2), FALSE);
	tmc8461_readWrite(tmc8461->config_mfc->channel, 0xFF, FALSE);
}

void tmc8461_mfc_write(TMC8461TypeDef *tmc8461, u16 address)
{
	tmc8461_readWrite(tmc8461->config_mfc->channel, address >> 5, FALSE);
	tmc8461_readWrite(tmc8461->config_mfc->channel, (address << 3) | TMC8461_CMD_ADDR_EXT, FALSE);
	tmc8461_readWrite(tmc8461->config_mfc->channel, ((address >> 8) & 0xE0) | (TMC8461_CMD_WRITE << 2), FALSE);
}

void tmc8461_esc_read_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len)
{
	tmc8461_esc_read(tmc8461, address);

	for (u16 i = 0; i < len; i++)
		data_ptr[i] = tmc8461_readWrite(tmc8461->config_esc->channel, (i < len - 1) ? 0x00 : 0xFF, (i < len - 1) ? FALSE : TRUE);
}

u8 tmc8461_esc_read_8(TMC8461TypeDef *tmc8461, u16 address)
{
	u8 buffer = 0;

	tmc8461_esc_read_data(tmc8461, &buffer, address, 1);

	return buffer;
}

u16 tmc8461_esc_read_16(TMC8461TypeDef *tmc8461, u16 address)
{
	u8 data[2];

	tmc8461_esc_read_data(tmc8461, data, address, 2);

	return _8_16(data[1], data[0]);
}

u32 tmc8461_esc_read_32(TMC8461TypeDef *tmc8461, u16 address)
{
	u8 data[4];

	tmc8461_esc_read_data(tmc8461, data, address, 4);

	return _8_32(data[3], data[2], data[1], data[0]);
}

void tmc8461_esc_write_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len)
{
	tmc8461_esc_write(tmc8461, address);

	for(u16 i = 0; i < len; i++)
		tmc8461_readWrite(tmc8461->config_esc->channel, data_ptr[i], (i < len - 1) ? FALSE : TRUE);
}

void tmc8461_esc_write_8(TMC8461TypeDef *tmc8461, u16 address, u8 value)
{
	tmc8461_esc_write_data(tmc8461, &value, address, 1);
}

void tmc8461_esc_write_16(TMC8461TypeDef *tmc8461, u16 address, u16 value)
{
	uint8 data[2];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	tmc8461_esc_write_data(tmc8461, data, address, 2);
}

void tmc8461_esc_write_32(TMC8461TypeDef *tmc8461, u16 address, u32 value)
{
	uint8 data[4];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);
	tmc8461_esc_write_data(tmc8461, data, address, 4);
}

void tmc8461_mfc_read_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len)
{
	tmc8461_mfc_read(tmc8461, address);

	for (u16 i = 0; i < len; i++)
		data_ptr[i] = tmc8461_readWrite(tmc8461->config_mfc->channel, (i < len - 1) ? 0x00 : 0xFF, (i < len - 1) ? FALSE : TRUE);
}

void tmc8461_mfc_read_32(TMC8461TypeDef *tmc8461, u16 address, u32 *value)
{
	uint8 data[4];

	tmc8461_mfc_read_data(tmc8461, data, address, 4);

	*value = _8_32(data[3], data[2], data[1], data[0]);
}

void tmc8461_mfc_read_64(TMC8461TypeDef *tmc8461, u16 address, u64 *value)
{
	uint8 data[8];

	tmc8461_mfc_read_data(tmc8461, data, address, 8);

	*value = _8_64((u64)data[7], (u64)data[6], (u64)data[5], (u64)data[4], (u64)data[3], (u64)data[2], (u64)data[1], (u64)data[0]);
}

void tmc8461_mfc_read_auto(TMC8461TypeDef *tmc8461, u16 address, u8 *value)
{
	if(address == TMC8461_MFC_SPI_RX_DATA || address == TMC8461_MFC_SPI_TX_DATA || address == TMC8461_MFC_PWM4) {
		// 64 bit
		tmc8461_mfc_read_data(tmc8461, value, address, 8);
	} else {
		// 32 bit
		tmc8461_mfc_read_data(tmc8461, value, address, 4);
	}
}

void tmc8461_mfc_write_data(TMC8461TypeDef *tmc8461, u8 *data_ptr, u16 address, u16 len)
{
	tmc8461_mfc_write(tmc8461, address);

	for (u16 i = 0; i < len; i++)
		tmc8461_readWrite(tmc8461->config_mfc->channel, data_ptr[i], (i < len - 1) ? FALSE : TRUE);
}

void tmc8461_mfc_write_32(TMC8461TypeDef *tmc8461, u16 address, u32 value)
{
	uint8 data[4];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);

	tmc8461_mfc_write_data(tmc8461, data, address, 4);
}

void tmc8461_mfc_write_64(TMC8461TypeDef *tmc8461, u16 address, u64 value)
{
	uint8 data[8];

	data[0] = BYTE(value, 0);
	data[1] = BYTE(value, 1);
	data[2] = BYTE(value, 2);
	data[3] = BYTE(value, 3);
	data[4] = BYTE(value, 4);
	data[5] = BYTE(value, 5);
	data[6] = BYTE(value, 6);
	data[7] = BYTE(value, 7);

	tmc8461_mfc_write_data(tmc8461, data, address, 8);
}

void tmc8461_mfc_write_auto(TMC8461TypeDef *tmc8461, u16 address, u8 *value)
{
	if(address == TMC8461_MFC_SPI_RX_DATA || address == TMC8461_MFC_SPI_TX_DATA || address == TMC8461_MFC_PWM4) {
		// 64 bit
		tmc8461_mfc_write_data(tmc8461, value, address, 8);
	} else {
		// 32 bit
		tmc8461_mfc_write_data(tmc8461, value, address, 4);
	}
}

void tmc8461_initConfig(TMC8461TypeDef *tmc8461, ConfigurationTypeDef *tmc8461_config_esc, ConfigurationTypeDef *tmc8461_config_mfc)
{
	tmc8461->config_esc = tmc8461_config_esc;
	tmc8461->config_mfc = tmc8461_config_mfc;

	while(TMC8461_FIELD_READ(tmc8461, tmc8461_esc_read_16, TMC8461_ESC_PDI_CTRL, TMC8461_ESC_PDI_MODE_MASK, TMC8461_ESC_PDI_MODE_SHIFT) != TMC8461_PDI_SPI_SLAVE);
	tmc8461_esc_write_16(tmc8461, TMC8461_ESC_AL_STATUS, FIELD_SET(TMC8461_EC_STATE_INIT, TMC8461_ESC_AL_ERROR_MASK, TMC8461_ESC_AL_ERROR_SHIFT, TRUE));
	tmc8461_esc_write_16(tmc8461, TMC8461_ESC_AL_CODE, 0x0000);
	tmc8461_esc_write_16(tmc8461, TMC8461_ESC_AL_EVENT_MASK_LO, 0xFF0E);
}
