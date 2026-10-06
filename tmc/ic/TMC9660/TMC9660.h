/*******************************************************************************
* Copyright © 2025 Analog Devices, Inc.
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

// Set this if your application uses multiple Trinamic ICs with the same
// CRC polynomials and you want to save data size.
// When set, the TMC-API expects the required CRC tables to defined in your
// application. The tables needed by this IC are tmcCRCTable_Poly7Reflected
// and tmcCRCTable_Poly104C11DB7Reflected. See TMC9660.c for their full definition.
#ifndef TMC_API_EXTERNAL_CRC_TABLE
//#define TMC_API_EXTERNAL_CRC_TABLE 1
#define TMC_API_EXTERNAL_CRC_TABLE 0
#endif

// If your application includes a monitoring connection of the FAULTN pin
// of the TMC9660 and you want to use functions related to it in the TMC-API.
// When enabled, this allows for faster runtime bootstrapping by having the
// TMC9660 signal completion of bootstrap steps via the FAULTN pin.
// If you set this define, you must supply the tmc9660_isFaultPinAsserted
// wrapper function.
#ifndef TMC_API_TMC9660_FAULT_PIN_SUPPORTED
//#define TMC_API_TMC9660_FAULT_PIN_SUPPORTED 1
#define TMC_API_TMC9660_FAULT_PIN_SUPPORTED 0
#endif

// Set this if you want to have SPI polling continue the polling
// transaction after receiving a non-BUSY reply. This requires your
// SPI wrapper function implementation (tmc9660_readWriteSPI) to be capable
// of keeping an SPI transaction going (aka. chip select staying asserted)
// while returning the first byte of data to the TMC-API. Refer to
// the "keepCSNAsserted" parameter of the function for more details.
#ifndef TMC_API_TMC9660_ENABLE_SPI_POLL_RESUMING
//#define TMC_API_TMC9660_ENABLE_SPI_POLL_RESUMING 1
#define TMC_API_TMC9660_ENABLE_SPI_POLL_RESUMING 0
#endif


/*** TMC9660 constants ********************************************************/
typedef enum TMC9660APIError_ {
    // General API errors
    TMC9660_ERROR_INVALID_BUS           = -1,
    TMC9660_ERROR_TIMEOUT               = -2,
    TMC9660_ERROR_WRONG_ADDR            = -3,
    TMC9660_ERROR_INVALID_REPLY         = -4,
    // Note: This reports invalid reply checksums.
    // Invalid request checksums get reported in the reply's status,
    // not the TMC-API access function error code.
    TMC9660_ERROR_INVALID_CHECKSUM      = -5,

    // Chip-specific API errors
    TMC9660_ERROR_FAULTN_TIMEOUT        = -16, // Note: Used in UblTools code generation
    TMC9660_ERROR_INVALID_ADDON         = -17,
    TMC9660_ERROR_NO_ADDON_SPACE        = -18,
    TMC9660_ERROR_INVALID_ADDON_INSTALL = -19, // Note: Used in UblTools code generation
} TMC9660APIError;

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
    TMC9660_BLCMD_WRITE_CHECKSUM     = 26,
    TMC9660_BLCMD_START_APP          = 27,
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

typedef enum TMC9660BlStatus_ {
    TMC9660_BLSTATUS_OK                 = 0,
    TMC9660_BLSTATUS_CMD_NOT_FOUND      = 1,
    TMC9660_BLSTATUS_INVALID_ADDR       = 3,
    TMC9660_BLSTATUS_INVALID_VALUE      = 4,
    TMC9660_BLSTATUS_INVALID_BANK       = 14,
    TMC9660_BLSTATUS_BUSY               = 15,
    TMC9660_BLSTATUS_MEM_UNCONFIGURED   = 17,
    TMC9660_BLSTATUS_OTP_ERROR          = 18,
    TMC9660_BLSTATUS_SESSION_START      = 19,
    TMC9660_BLSTATUS_CMD_NOT_AVAILABLE  = 20
} TMC9660BlStatus;

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

typedef enum TMC9660ParamSPIStatus_ {
    TMC9660_PARAMSPISTATUS_OK             = 0xAD,
    TMC9660_PARAMSPISTATUS_FIRST_CMD      = 0x0C,
    TMC9660_PARAMSPISTATUS_NOT_READY      = 0x00,
} TMC9660ParamSPIStatus;


/*** TMC-API wrapper functions ************************************************/
// These function must be implemented in your application

/**
 * @brief SPI wrapper function to be implemented in the user application.
 *
 * This function serves as the TMC-API's access to the real SPI hardware inside
 * the application. The TMC-API functions will call this function every time
 * they have to interact with SPI hardware.
 * Your application code must provide this function.
 *
 * @param icID
 *             The IC to communicate with. This will be set to the icID you pass
 *             into all the other TMC-API TMC9660 functions.
 * @param data
 *             The IC to communicate with. This will be set to the icID you pass
 *             into all the other TMC-API TMC9660 functions.
 * @param dataLength
 *             The amount of bytes to send & receive
 * @param keepCSNAsserted
 *             Whether to keep the chip select signal asserted after the bytes
 *             were sent & received.
 *             If TMC_API_TMC9660_ENABLE_SPI_POLL_RESUMING == 0 (the default),
 *             this parameter will always be false and you can ignore it.
 *             If you defined TMC_API_TMC9660_ENABLE_SPI_POLL_RESUMING == 1,
 *             you must support it, including this function being called
 *             with dataLength=0 and keepCSNAsserted=false to finish an
 *             ongoing SPI transaction without sending any further data.
 */
extern void tmc9660_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength, bool keepCSNAsserted);

/**
 * @brief UART wrapper function:
 *
 * This function serves as the TMC-API's access to the real UART hardware inside
 * the application. The TMC-API functions will call this function every time
 * they have to interact with UART hardware.
 * Your application code must provide this function.
 *
 * @param icID
 *        The IC to communicate with. This will be set to the icID you pass
 *        into all the other TMC-API TMC9660 functions.
 * @param data
 *        A pointer to the data bytes to send out via UART.
 *        The reply data must be written into this buffer
 * @param writeLength
 *        The amount of bytes to send
 * @param readLength
 *        The amount of bytes to receive
 *
 * @return Return false if receiving the requested data failed, true otherwise.
 */
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
bool tmc9660_waitForFaultDeassertion(uint16_t icID, uint32_t timeout_us);
#endif

/*** TMC9660 Bootloader Mode functions ****************************************/
int32_t tmc9660_bl_sendCommand(uint16_t icID, uint8_t cmd, uint32_t writeValue, uint32_t *readValue);

// Addon upload
int32_t tmc9660_bl_installAddon(uint16_t icID, const uint8_t *addon, uint32_t addonSize);

// Addon verification
// Returns a negative value on error, 0 if no addon is installed, 1 if an addon is installed.
// The id and version are only written if an addon is installed (return value 1).
int32_t tmc9660_bl_getAddonInfo(uint16_t icID, uint32_t *id, uint32_t *version);

/*** TMC9660 Parameter Mode functions *****************************************/
int32_t tmc9660_param_sendCommand(uint16_t icID, uint8_t cmd, uint16_t type, uint8_t index, uint32_t writeValue, uint32_t *readValue);

// Special case commands: These functions run commands that are edge cases of the underlying protocol
// Note: readTMCLMemory is only available when communicating via UART.
int32_t tmc9660_param_getVersionASCII(uint16_t icID, uint8_t *versionString);
int32_t tmc9660_param_readTMCLMemory(uint16_t icID, uint32_t cmdIndex, uint8_t *command);
int32_t tmc9660_param_returnToBootloader(uint16_t icID);

/**
 * @brief SPI pipeline access function
 *
 * This function serves as a low level access function to implement fast, pipelined
 * SPI communication. Each call corresponds to one SPI request to the TMC9660.
 *
 * @param icID
 *        The IC to communicate with. This gets forwarded to callback functions.
 * @param cmd
 *        The parameter mode command to send.
 * @param type
 *        The parameter mode type to send.
 * @param index
 *        The parameter mode index to send.
 * @param requestValue
 *        The parameter mode value to send.
 * @param replyValue
 *        The reply value to receive. This function will write the received reply word
 *        into this pointer. If the pointer is NULL, this will be skipped.
 *        Note that when requireReply is false, no reply is guaranteed to actually arrive.
 * @param requireReply
 *        Whether to poll the TMC9660 to receive a reply. Only set this if a prior request
 *        was sent that did not yet get a reply.
 * @param timeout_us
 *        The timeout for the polling done when requireReply is set.
 *
 * @return Returns a negative error status code, or the positive TMCL reply status byte.
 */
int32_t tmc9660_param_sendPipelinedSPICommand(
        uint16_t icID,
        uint8_t cmd,
        uint16_t type,
        uint8_t index,
        uint32_t requestValue,
        uint32_t *replyValue,
        bool requireReply,
        uint32_t timeout_us
        );

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
