# TMC2226


## How to use

To access the TMC2226's registers, the TMC-API offers two functions: **tmc2226_readRegister** and **tmc2226_writeRegister**.
Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/TMC2226 folder into the custom project.
2. Include the TMC2226.h file in the custom source code.
3. Implement the necessary callback functions (see below).
4. (optional): Take a look at the Examples subfolder for ready-made examples of the TMC-API usage.

## Accessing the TMC2226 via UART
The following diagram depicts how to access the TMC2226 via UART using the TMC-API.

![screenshot](registercall_hierarchy_flowchar_UART.png)

The description of the functions, in the above flowchart, are as follows:
- The functions tmc2226_readRegister and tmc2226_writeRegister are used to read and write the registers respectively. These functions check the current active bus and calls the bus-specific function i.e readRegisterUART or writeRegisterUART.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmcXXXX_readWriteUART.
- This callback function further calls the hardware specific read/write function for UART and needs to be implemented externally.

### How to integrate: Callback functions
To communicate with TMC2226 IC, the TMC-API library needs to know which bus (UART, SPI) it shall use. For that, the callback function **'tmc2226_getBusType()'** needs to be implemented.
Additionally, implement the following callback functions to access the chip via UART:
1. **tmc2226_readWriteUART()**, which is a HAL wrapper function that provides the necessary hardware access.
2. **tmc2226_getNodeAddress()**, that returns the node/slave address. Node address could be set in NODECONF (0x3) register and the address could be incremented as defined by AD0, AD1 and AD2. (Node address + ADx) must be less than 255. For further details please consult the datasheet of TMC2226.

### Sharing the CRC table with other TMC-API chips
The TMC2226 UART protocol uses an 8 bit CRC. For calculating this, a table-based algorithm is used. This table (tmcCRCTable_Poly7Reflected[256]) is 256 bytes big and identical across multiple different Trinamic chips (i.e. TMC2209).
If multiple Trinamic chips are being used in the same project, avoiding redundant copies of this table could save memory. It is possible to substitute this CRC table with another CRC table.

## Further info
### Dependency graph for the ICs with new register R/W mechanism
This graph illustrates the relationships between files within the TMC-API library, highlighting dependencies and identifying the files that are essential for integrating the library into the custom projects.
![screenshot](uml-tmc-api.png)

### Example usage: TMC-Evalsystem
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

## Migration status
The TMC2226 has been reworked to the access system described above. For more infos on the status of this and other ICs, check out the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).


