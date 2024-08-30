/*******************************************************************************
* Copyright © 2026 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/


#ifndef TMC_IC_TMC6460_H_
#define TMC_IC_TMC6460_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "TMC6460_HW_Abstraction.h"

/*******************************************************************************
* API Configuration Defines
* These control optional features of the TMC-API implementation.
* These can be commented in/out here or defined from the build system.
*******************************************************************************/

#ifndef TMC_API_TMC6460_RTMI_SUPPORT
//#define TMC_API_TMC6460_RTMI_SUPPORT 1
#define TMC_API_TMC6460_RTMI_SUPPORT 0
#endif

#ifndef TMC_API_TMC6460_CRC_SUPPORT
//#define TMC_API_TMC6460_CRC_SUPPORT 1
#define TMC_API_TMC6460_CRC_SUPPORT 0
#endif

/*** TMC9660 constants ********************************************************/
enum TMC6460BusType {
    TMC6460_BUS_SPI,
    TMC6460_BUS_UART,

    TMC6460_BUS_END_
};

/*** TMC-API wrapper functions ************************************************/
// Each callback function has an [icID] parameter. Calling TMC-API functions
// that interact with a TMC6460 IC (such as tmc6460_readRegister) always take
// an icID argument. The value of that argument gets passed to the callback
// functions to allow distinguishing between multiple TMC6460 ICs. If your
// application only uses a single TMC6460, the callback functions may ignore
// their icID parameter.


// The TMC-API will call this function for every SPI transaction to a TMC6460.
// Each call to this function shall send a single SPI transaction (a sequence
// of chip select assertion, data transmission, and chip select de-assertion).
//
// This function shall send the bytes from the [data] array and write the received
// bytes back into the [data] array. The amount of bytes to send and receive is
// specified by [dataLength]. Note that the TMC6460 SPI protocol always uses
// datagrams of 6 bytes.
extern void tmc6460_readWriteSPI(uint16_t icID, uint8_t *data, size_t dataLength);


// The TMC-API will call this function for every UART transaction to a TMC6460.
// Each call to this function shall first send the amount of bytes specified by
// [writeLength] out through a UART interface to the TMC6460. Then it shall read
// bytes coming back from the TMC6460, the amount being specified by [readLength].
// If no data shall be received, readLength will be zero.
// If read data is requested but does not arrive after a timeout interval, this
// function shall flush any UART receive buffers, and signal failure by returning false.
// On successful reception of data, or if no read data was requested, it shall return true.
// Data to be sent shall be read out of the [data] array. Read data shall be written
// back into the [data] array (overwriting the write data).
extern bool tmc6460_readWriteUART(uint16_t icID, uint8_t *data, size_t writeLength, size_t readLength);

// The TMC-API will call this function every time an API function is called
// that interacts with a TMC6460 IC.
// This function shall return the physical bus to use for the given [icID].
extern enum TMC6460BusType tmc6460_getBusType(uint16_t icID);

#if TMC_API_TMC6460_RTMI_SUPPORT
// The TMC-API will call this function every time an RTMI packet has been received.
// This function shall take the RTMI data for further use.
// If no further data shall be gathered, return true, otherwise false.
extern bool tmc6460_RTMIDataCallback(uint16_t icID, uint8_t status, uint32_t data);

// This function shall indicate whether the RTMI transfer has been enabled or not.
// It must not call any register access functions, as this function gets called
// by these register access functions!
extern bool tmc6460_isRTMIEnabled(uint16_t icID);

// This function shall return the amount of bytes received from the TMC6460 through
// UART that have not yet been handed to the TMC-API.
extern uint32_t tmc6460_availableBytes(uint16_t icID);

#endif /* TMC_API_TMC6460_RTMI_SUPPORT */

#if TMC_API_TMC6460_CRC_SUPPORT
// This function shall indicate whether the normal CRC setting has been enabled or not.
// It must not call any register access functions, as this function gets called
// by these register access functions!
extern bool tmc6460_isNormalCRCEnabled(uint16_t icID);

// This function shall indicate whether the RTMI CRC setting has been enabled or not.
// It must not call any register access functions, as this function gets called
// by these register access functions!
extern bool tmc6460_isRTMICRCEnabled(uint16_t icID);
#endif
// <= TMC-API wrapper

/*** TMC9660 general functions ************************************************/
int32_t tmc6460_readRegister(uint16_t icID, uint16_t address, uint32_t *readValue);
int32_t tmc6460_writeRegister(uint16_t icID, uint16_t address, uint32_t writeValue);

// This function allows using the TMC6460's special write request.
// Since this datagram structure is UART-specific, it will always use UART,
// it will not check the bus mode - hence it won't call tmc6460_getBusType().
int32_t tmc6460_writeRTMIStreamedRegister(uint16_t icID, uint8_t rtmi_index, uint32_t value);

#if TMC_API_TMC6460_RTMI_SUPPORT
bool tmc6460_processRTMI(uint16_t icID, uint32_t packetLimit);
#endif

static inline uint32_t tmc6460_extractField(uint32_t registerValue, TMC6460RegisterField field)
{
    uint32_t fieldValue = (registerValue & field.mask) >> field.shift;

    if (field.isSigned)
    {
        // Apply signedness conversion
        uint32_t baseMask = field.mask >> field.shift;
        uint32_t signMask = baseMask & (~baseMask >> 1);
        fieldValue = (fieldValue ^ signMask) - signMask;
    }

    return fieldValue;
}

static inline int32_t tmc6460_readField(uint16_t icID, TMC6460RegisterField field, uint32_t *readValue)
{
    int32_t err = tmc6460_readRegister(icID, field.addr, readValue);
    if (err < 0)
        return err;

    *readValue = tmc6460_extractField(*readValue, field);

    return 0;
}

static inline uint32_t tmc6460_updateField(uint32_t registerValue, TMC6460RegisterField field, uint32_t writeValue)
{
    registerValue &= ~field.mask;
    registerValue |= (writeValue << field.shift) & field.mask;

    return registerValue;
}

static inline int32_t tmc6460_writeField(uint16_t icID, TMC6460RegisterField field, uint32_t writeValue)
{
    uint32_t value = 0;
    int32_t err = tmc6460_readRegister(icID, field.addr, &value);
    if (err < 0)
        return err;

    value = tmc6460_updateField(value, field, writeValue);

    return tmc6460_writeRegister(icID, field.addr, value);
}

static inline bool tmc6460_fieldInRange(TMC6460RegisterField field, uint32_t fieldValue)
{
    if (field.isSigned)
    {
        if ((int32_t) fieldValue > (int32_t) (field.mask >> (field.shift + 1)))
            return false;

        if ((int32_t) fieldValue < (int32_t) (~(field.mask >> (field.shift + 1))))
            return false;
    }
    else
    {
        if (fieldValue > (field.mask >> field.shift))
            return false;
    }

    return true;
}

#endif /* TMC_IC_TMC6460_H_ */
