# TMC9660

Note: Currently only UART is supported

## How to use

To access the TMC9660 in bootloader, paramater or register mode, the TMC-API offers **tmc9660_bl_sendCommand**, **tmc9660_param_sendCommand** and **tmc9660_reg_sendCommand** functions respectively.

Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/TMC9660 folder into your project.
2. Include the TMC9660.h file in your source code.
3. Include TMC9660_BL_HW_Abstraction.h if your code interacts with the TMC9660 bootloader.
4. Include TMC9660_PARAM_HW_Abstraction.h if your code interacts with the parameter mode.
5. Implement the necessary callback functions (see below).

## Accessing the TMC9660 via UART

- The function tmc9660_bl_sendCommand is used to send commands to the chip in bootloader mode. Bootloader commands are available as the TMC9660BlCommand enum type. Similarly the functions tmc9660_param_sendCommand and tmc9660_reg_sendCommand are used to access APs or registers in parameter or register mode respectively.
- These functions check the current active bus and calls the bus-specific function i.e tmc9660_bl_sendCommand_UART, tmc9660_param_sendCommand_UART or tmc9660_reg_sendCommand_UART.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmc9660_readWriteUART.
- This callback function further calls the hardware specific read/write function for UART and needs to be implemented externally.
- All of these functions return a 32-bit status integer. Possible status error codes for Parameter mode are enumerated as TMC9660ParamStatus.


### How to integrate: Callback functions

The following callback functions must be implemented your code:
1. **'tmc9660_getBusType()'** that returns the bus to use for the given icID.
2. **tmc9660_getBusAddresses()** that returns device and host addresses e.g; device=1, host=255.
3. **tmc_getMicrosecondTimestamp()** that returns a system timestamp in microseconds.
4. **tmc9660_readWriteUART()** that sends data via UART and, if requested, reads back data and returns it to the TMC-API.

Additionally, the following function may be implemented if your application intents to use the TMC9660 fault pin:
- **tmc9660_isFaultPinAsserted()** that returns whether the TMC9660 fault pin is asserted.

Note that in order to enable the TMC-API support for using the fault pin, the define TMC_API_TMC9660_FAULT_PIN_SUPPORTED must be set to 1. This can be done either by uncommenting the define at the top of the TMC9660.h header file, or by setting it as part of your build system.


### Sharing the CRC table with other TMC-API chips
The TMC9660 UART protocol uses an 8 bit CRC. For calculating this, a table-based algorithm is used. This table (tmcCRCTable_Poly7Reflected[256]) is 256 bytes big and identical across multiple different Trinamic chips (i.e. TMC2209).
If multiple Trinamic chips are being used in the same project, avoiding redundant copies of this table could save memory. It is possible to substitute this CRC table with another CRC table.
