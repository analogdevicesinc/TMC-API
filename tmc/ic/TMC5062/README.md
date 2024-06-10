# TMC5062


## How to use

To access the TMC5062's registers, the TMC-API offers two functions: **tmc5062_readRegister** and **tmc5062_writeRegister**.
Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/TMC5062 folder into the custom project.
2. Include the TMC5062.h file in the custom source code.
3. Implement the necessary callback functions (see below).
4. (optional): Take a look at the Examples subfolder for ready-made examples of the TMC-API usage.

## Accessing the TMC5062 via UART
The following diagram depicts how to access the TMC5062 via UART using the TMC-API.

![screenshot](registercall_hierarchy_flowchart_UART.png)

The description of the functions, in the above flowchart, are as follows:
- The functions tmc5062_readRegister and tmc5062_writeRegister are used to read and write the registers respectively. These functions check the current active bus and calls the bus-specific function i.e readRegisterUART or writeRegisterUART.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmcXXXX_readWriteUART.
- This callback function further calls the hardware specific read/write function for UART and needs to be implemented externally.

### How to integrate: Callback functions
To communicate with TMC5062 IC, the TMC-API library needs to know which bus (UART, SPI) it shall use. For that, the callback function **'tmc5062_getBusType()'** needs to be implemented.
Additionally, implement the following callback functions to access the chip via UART:
1. **tmc5062_readWriteUART()**, which is a HAL wrapper function that provides the necessary hardware access.

### Sharing the CRC table with other TMC-API chips
The TMC5062 UART protocol uses an 8 bit CRC. For calculating this, a table-based algorithm is used. This table (tmcCRCTable_Poly7Reflected[256]) is 256 bytes big and identical across multiple different Trinamic chips (i.e. TMC2209).
If multiple Trinamic chips are being used in the same project, avoiding redundant copies of this table could save memory. It is possible to substitute this CRC table with another CRC table.

## Accessing the TMC5062 via SPI
The following diagram depicts how to access the TMC5062 via SPI using the TMC-API.

![screenshot](registercall_hierarchy_flowchart_SPI.png)

The description of the functions, in the above flowchart, are as follows:
- The functions tmc5062_readRegister and tmc5062_writeRegister are used to read and write the registers respectively. These functions check the current active bus and calls the bus-specific function i.e readRegisterSPI or writeRegisterSPI.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmcXXXX_readWriteSPI.
- This callback function further calls the hardware specific read/write function for SPI and needs to be implemented externally.

### How to integrate: Callback functions
To communicate with TMC5062 IC, the TMC-API library needs to know which bus (UART, SPI) it shall use. For that, the callback function **'tmc5062_getBusType()'** needs to be implemented.
Additionally, implement the following callback functions to access the chip via SPI:
1. **tmc5062_readWriteSPI()**, which is a HAL wrapper function that provides the necessary hardware access. This function should also set the chip select pin CSN to low before starting the data transfer and set to high upon completion. Please refer to the datasheet of the IC for further details.

## Further info
### Dependency graph for the ICs with new register R/W mechanism
This graph illustrates the relationships between files within the TMC-API library, highlighting dependencies and identifying the files that are essential for integrating the library into the custom projects.
![screenshot](uml-tmc-api.png)

### Example usage: TMC-Evalsystem
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

## Migration status
The TMC5062 has been reworked to the access system described above. For more infos on the status of this and other ICs, check out the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).


