/*******************************************************************************
* Copyright © 2017 TRINAMIC Motion Control GmbH & Co. KG
* (now owned by Analog Devices Inc.),
*
* Copyright © 2023 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#include "TMC2660.h"
//-----------------------------------NEW CODE----------------------------------------------//
TMC2660TypeDef TMC2660;
#define DEFAULT_ICID 0

static void readWrite(uint32_t value);
static void readImmediately(uint8_t rdsel);

void readWrite(uint32_t datagram)
{
    uint8_t data[3]= {0};
void readWrite(uint8_t icID, uint32_t datagram)
{
    uint8_t data[3] = {0};
    uint32_t reply;
    uint8_t rdsel = TMC2660_GET_RDSEL(datagram);

    data[0] = 0xFF & (datagram >> 16);
    data[1] = 0xFF & (datagram >> 8);
    data[2] = 0xFF & (datagram >> 0);

    // Send 24 bytes of data and receive reply
    tmc2660_readWriteSPI(icID, &data[0], sizeof(data));

    reply = (data[0] << 16 | data[1] << 8 | data[2]) >> 4;

    // write value to response shadow register
    tmc2660_shadowRegister[icID][rdsel] = reply;

    // Store the latest response value to extract status bits in tmc2660_getStatusBits()
    tmc2660_shadowRegister[icID][TMC2660_RESPONSE_LATEST] = reply;

    // write value to response shadow register
    if (TMC2660_GET_ADDRESS(datagram) == TMC2660_DRVCONF)
        rdsel = TMC2660_GET_RDSEL(datagram);

    // write value to shadow register
    tmc2660_shadowRegister[icID][TMC2660_GET_ADDRESS(datagram) | TMC2660_WRITE_BIT] = datagram;
}

void readImmediately(uint8_t icID, uint8_t rdsel)
{
    // sets desired reply in DRVCONF register, resets it to previous settings whilst reading desired reply
    uint32_t value, drvConf;

    // additional reading to keep all replies up to date
    value   = tmc2660_readRegister(0, TMC2660_DRVCONF); // buffer (value and drvConf) to write back later
    drvConf = value;
    value &= ~TMC2660_SET_RDSEL(-1);       // clear RDSEL bits
    value |= TMC2660_SET_RDSEL(rdsel % 3); // set rdsel
    readWrite(icID, value);                // write to chip and readout reply
    readWrite(icID, value);              // write to chip and return desired reply
}

void tmc2660_writeRegister(uint8_t icID, uint8_t address, uint32_t value)
{
    // Don't write to read-only registers
    if (TMC2660_IS_READONLY_REGISTER(address))
        return;

    // Extract 20 bits of valid data
    value &= 0x0FFFFF;

    //Cache the registers with write-only access
    tmc2660_cache(icID, TMC2660_CACHE_WRITE, address, &value);

    // 0XF7 to mask the write bit
    if (!tmc2660_getcontinuousModeEnable(icID))
        readWrite(icID, TMC2660_DATAGRAM((address & 0xF7), value));
}

uint32_t tmc2660_readRegister(uint8_t icID, uint8_t address)
{
    uint32_t value;

    // Read from cache for registers with write-only access
    if (tmc2660_cache(icID, TMC2660_CACHE_READ, address, &value))
        return value;

    if (!tmc2660_getcontinuousModeEnable(icID))
    {
        // Read the read-only register, refreshing the cache
        readImmediately(icID, address);
    }

    // Return the read-only register from cache
    return tmc2660_shadowRegister[icID][address];
}

uint8_t tmc2660_getStatusBits(uint8_t icID)
uint8_t tmc2660_getStatusBits()
{
    // Grab the status bits from the last request
    return tmc2660_shadowRegister[icID][TMC2660_RESPONSE_LATEST] & TMC2660_STATUS_MASK;
    return TMC2660.config->shadowRegister[TMC2660_RESPONSE_LATEST] & TMC2660_STATUS_MASK; // Todo update rdsel register bits in the cache
}

void tmc2660_readWrite(uint8_t motor, uint32_t value)
{
    UNUSED(motor);

    static uint8_t rdsel = 0; // number of expected read response

    // if SGCONF should be written, check whether stand still, or run current should be used
//  if(TMC2660_GET_ADDRESS(value) == TMC2660_SGCSCONF)
//  {
//      value &= ~TMC2660_SET_CS(-1); // clear CS field
//      value |= (TMC2660.isStandStillCurrentLimit) ?  TMC2660_SET_CS(TMC2660.standStillCurrentScale) : TMC2660_SET_CS(TMC2660.runCurrentScale); // set current
//  }

    // write value and read reply to shadow register
    TMC2660.config->shadowRegister[rdsel] = tmc2660_readWriteSPI(DEFAULT_ICID, value>>16, 0);
    TMC2660.config->shadowRegister[rdsel] <<= 8;
    TMC2660.config->shadowRegister[rdsel] |= tmc2660_readWriteSPI(DEFAULT_ICID, value>>8, 0);
    TMC2660.config->shadowRegister[rdsel] <<= 8;
    TMC2660.config->shadowRegister[rdsel] |= tmc2660_readWriteSPI(DEFAULT_ICID, value & 0xFF, 1);
    TMC2660.config->shadowRegister[rdsel] >>= 4;

    TMC2660.config->shadowRegister[TMC2660_RESPONSE_LATEST] = TMC2660.config->shadowRegister[rdsel]; // copy value to latest field
    // set virtual read address for next reply given by RDSEL, can only change by setting RDSEL in DRVCONF
    if(TMC2660_GET_ADDRESS(value) == TMC2660_DRVCONF)
        rdsel = TMC2660_GET_RDSEL(value);

    // write store written value to shadow register
    TMC2660.config->shadowRegister[TMC2660_GET_ADDRESS(value) | TMC2660_WRITE_BIT ] = value;
}
//------------------------------------------------------------NEW CODE-----------------------------------//


// Currently unused, we write the whole configuration as part of the reset/restore functions
void tmc2660_writeConfiguration(TMC2660TypeDef *tmc2660, ConfigurationTypeDef *TMC2660_config)
{
	// write one writeable register at a time - backwards to hit DRVCONF before DRVCTRL
	UNUSED(tmc2660);
	UNUSED(TMC2660_config);

	//uint8_t *ptr = &TMC2660.config->configIndex;
	//const int32_t *settings = (TMC2660.config->state == CONFIG_RESTORE) ? TMC2660.config->shadowRegister : tmc2660->registerResetState;

	//while((*ptr >= 0) && !IS_WRITEABLE(tmc2660->registerAccess[*ptr]))
		//(*ptr)--;

	//if(*ptr >= 0)
	//{
		//tmc2660_writeInt(0, *ptr, settings[*ptr]);
		//(*ptr)--;
	//}
	//else
	//{
		//TMC2660.config->state = CONFIG_READY;
	//}
}
