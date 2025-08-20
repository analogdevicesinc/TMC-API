/*******************************************************************************
* Copyright © 2025 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC9660_H_
#define TMC_IC_TMC9660_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

// Uncomment if you want to save space.....
// and put the table into your own .c file
//#define TMC_API_EXTERNAL_CRC_TABLE 1

// Uncomment if you want to use fault pin related features
// If enabled, this requires an additional wrapper function
//#define TMC_API_TMC9660_FAULT_PIN_SUPPORTED 1

/*** TMC9660 constants ********************************************************/
typedef enum TMC9660BusType_ {
    TMC9660_BUS_SPI,
    TMC9660_BUS_UART,
} TMC9660BusType;

typedef struct TMC9660BusAddresses_ {
    uint8_t device;
    uint8_t host;
} TMC9660BusAddresses;

typedef enum TMC9660BlCommand_ {
    TMC9660_BLCMD_GET_INFO           = 0,
    TMC9660_BLCMD_GET_BANK           = 8,
    TMC9660_BLCMD_SET_BANK           = 9,
    TMC9660_BLCMD_GET_ADDRESS        = 10,
    TMC9660_BLCMD_SET_ADDRESS        = 11,
    TMC9660_BLCMD_READ_32            = 12,
    TMC9660_BLCMD_READ_32_INC        = 13,
    TMC9660_BLCMD_READ_16            = 14,
    TMC9660_BLCMD_READ_16_INC        = 15,
    TMC9660_BLCMD_READ_8             = 16,
    TMC9660_BLCMD_READ_8_INC         = 17,
    TMC9660_BLCMD_WRITE_32           = 18,
    TMC9660_BLCMD_WRITE_32_INC       = 19,
    TMC9660_BLCMD_WRITE_16           = 20,
    TMC9660_BLCMD_WRITE_16_INC       = 21,
    TMC9660_BLCMD_WRITE_8            = 22,
    TMC9660_BLCMD_WRITE_8_INC        = 23,
    TMC9660_BLCMD_NO_OP              = 29,
    TMC9660_BLCMD_OTP_LOAD           = 30,
    TMC9660_BLCMD_OTP_BURN           = 31,
    TMC9660_BLCMD_MEM_ISCONFIGURED   = 32,
    TMC9660_BLCMD_MEM_ISCONNECTED    = 33,
    TMC9660_BLCMD_FLASH_SENDCMD      = 36,
    TMC9660_BLCMD_FLASH_ERASE_SECTOR = 37,
    TMC9660_BLCMD_MEM_IS_BUSY        = 40,
    TMC9660_BLCMD_BOOTSTRAP_RS485    = 0xFF,
} TMC9660BlCommand;

typedef enum TMC9660Command_ {
    TMC9660_CMD_MST             = 3,

    TMC9660_CMD_SAP             = 5,
    TMC9660_CMD_GAP             = 6,
    TMC9660_CMD_STAP            = 7,

    TMC9660_CMD_SGP             = 9,
    TMC9660_CMD_GGP             = 10,

    TMC9660_CMD_RFS             = 13,
    TMC9660_CMD_SIO             = 14,
    TMC9660_CMD_GIO             = 15,

    TMC9660_CMD_CALC            = 19,
    TMC9660_CMD_COMP            = 20,
    TMC9660_CMD_JC              = 21,
    TMC9660_CMD_JA              = 22,
    TMC9660_CMD_CSUB            = 23,
    TMC9660_CMD_RSUB            = 24,
    TMC9660_CMD_EI              = 25,
    TMC9660_CMD_DI              = 26,
    TMC9660_CMD_WAIT            = 27,
    TMC9660_CMD_STOP            = 28,

    TMC9660_CMD_CALCX           = 33,
    TMC9660_CMD_AAP             = 34,
    TMC9660_CMD_AGP             = 35,
    TMC9660_CMD_CLE             = 36,
    TMC9660_CMD_VECT            = 37,
    TMC9660_CMD_RETI            = 38,

    TMC9660_CMD_CALCVV          = 40,
    TMC9660_CMD_CALCVA          = 41,
    TMC9660_CMD_CALCAV          = 42,
    TMC9660_CMD_CALCVX          = 43,
    TMC9660_CMD_CALCXV          = 44,
    TMC9660_CMD_CALCV           = 45,

    TMC9660_CMD_RST             = 48,
    TMC9660_CMD_DJNZ            = 49,

    TMC9660_CMD_SIV             = 55,
    TMC9660_CMD_GIV             = 56,
    TMC9660_CMD_AIV             = 57,

    TMC9660_CMD_APPL_STOP       = 128,
    TMC9660_CMD_APPL_RUN        = 129,
    TMC9660_CMD_APPL_STEP       = 130,
    TMC9660_CMD_APPL_RESET      = 131,
    TMC9660_CMD_DOWNLOAD_START  = 132,
    TMC9660_CMD_DOWNLOAD_END    = 133,
    TMC9660_CMD_READ_MEM        = 134,
    TMC9660_CMD_GET_STATUS      = 135,
    TMC9660_CMD_GET_VERSION     = 136,
    TMC9660_CMD_FACTORY_DEFAULT = 137,

    TMC9660_CMD_BREAKPOINT      = 141,
    TMC9660_CMD_RAMDEBUG        = 142,

    TMC9660_CMD_GET_INFO        = 157,

    TMC9660_CMD_BOOT            = 242,
} TMC9660Command;

typedef enum TMC9660ParamStatus_ {
    TMC9660_PARAMSTATUS_CHKERROR                  = 1,  // Checksum error during communication
    TMC9660_PARAMSTATUS_INVALID_CMD               = 2,  // Invalid command number
    TMC9660_PARAMSTATUS_WRONG_TYPE                = 3,  // Invalid type number
    TMC9660_PARAMSTATUS_INVALID_VALUE             = 4,  // Invalid value
    TMC9660_PARAMSTATUS_CMD_NOT_AVAILABLE         = 6,  // Command currently not available
    TMC9660_PARAMSTATUS_CMD_LOAD_ERROR            = 7,  // Failed to load command into script memory
    TMC9660_PARAMSTATUS_MAX_EXCEEDED              = 9,  // Maximum exceeded
    TMC9660_PARAMSTATUS_CMD_DOWNLOAD_NOT_POSSIBLE = 10, // Loading into script memory not available

    TMC9660_PARAMSTATUS_OK                        = 100, // Success
    TMC9660_PARAMSTATUS_CMD_LOADED                = 101, // Command successfully loaded into script memory
} TMC9660ParamStatus;

/*** TMC-API wrapper functions ************************************************/
//extern void tmc9660_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);
extern bool tmc9660_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);

#if TMC_API_TMC9660_FAULT_PIN_SUPPORTED != 0
extern bool tmc9660_isFaultPinAsserted(uint16_t icID);
#endif

extern TMC9660BusType tmc9660_getBusType(uint16_t icID);
extern TMC9660BusAddresses tmc9660_getBusAddresses(uint16_t icID);

// ToDo: Make the timing function & callback usable with multiple TMC-API chips in use.
extern uint32_t tmc_getMicrosecondTimestamp();

/*** TMC-API shared functions *************************************************/

// ToDo: Make the timing function & callback usable with multiple TMC-API chips in use.
void tmc_delayMicroseconds(uint32_t microseconds);

/*** TMC9660 general functions ************************************************/
#if TMC_API_TMC9660_FAULT_PIN_SUPPORTED != 0
void tmc9660_waitForFaultDeassertion(uint16_t icID);
#endif

/*** TMC9660 Bootloader Mode functions ****************************************/
int32_t tmc9660_bl_sendCommand(uint16_t icID, uint8_t cmd, uint32_t writeValue, uint32_t *readValue);

/*** TMC9660 Parameter Mode functions *****************************************/
int32_t tmc9660_param_sendCommand(uint16_t icID, uint8_t cmd, uint16_t type, uint8_t index, uint32_t writeValue, uint32_t *readValue);

// Special case commands: These two functions run commands that are edge cases of the underlying protocol
int32_t tmc9660_param_getVersionASCII(uint16_t icID, uint8_t *versionString);
int32_t tmc9660_param_returnToBootloader(uint16_t icID);

uint32_t tmc9660_param_getParameter(uint16_t icID, uint16_t type);
bool tmc9660_param_setParameter(uint16_t icID, uint16_t type, uint32_t value);

uint32_t tmc9660_param_getGlobalParameter(uint16_t icID, uint16_t index);
bool tmc9660_param_setGlobalParameter(uint16_t icID, uint16_t index, uint32_t value);

/*** TMC9660 Register Mode functions *****************************************/
int32_t tmc9660_reg_sendCommand(uint16_t icID, uint8_t cmd, uint16_t registerOffset, uint8_t registerBlock, uint32_t writeValue, uint32_t *readValue);

// Special case commands: These two functions run commands that are edge cases of the underlying protocol
int32_t tmc9660_reg_getVersionASCII(uint16_t icID, uint8_t *versionString);
int32_t tmc9660_reg_returnToBootloader(uint16_t icID);

/******************************************************************************/

#endif /* TMC_IC_TMC9660_H_ */
