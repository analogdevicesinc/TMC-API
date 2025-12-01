# TMC5160


## How to use

To access the TMC5160's registers, the TMC-API offers two functions: **tmc5160_readRegister** and **tmc5160_writeRegister**.
Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/TMC5160 folder into the custom project.
2. Include the TMC5160.h file in the custom source code.
3. Implement the necessary callback functions (see below).
4. (optional): Take a look at the Examples subfolder for ready-made examples of the TMC-API usage.

## Accessing the TMC5160 via UART
The following diagram depicts how to access the TMC5160 via UART using the TMC-API.

![screenshot](registercall_hierarchy_flowchart_UART.svg)

The description of the functions, in the above flowchart, are as follows:
- The functions tmc5160_readRegister and tmc5160_writeRegister are used to read and write the registers respectively. These functions check the current active bus and calls the bus-specific function i.e readRegisterUART or writeRegisterUART.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmcXXXX_readWriteUART.
- This callback function further calls the hardware specific read/write function for UART and needs to be implemented externally.

### Necessary hardware modification to use UART
To use UART with the Eval-Kit: pin 39 (DIO17) and 40 (DIO18) should be connected with a 1k ohm resistor. Pin 37 (DIO15) and 40(DIO18) should be shorted. Additionally bend the 37 and 38 on the Landungsbrücke side of the Eselsbrücke out. For more information checkout the latest TMC5160-EVAL UART Info Application Note at https://www.analog.com/en/resources/evaluation-hardware-and-software/evaluation-boards-kits/tmc5160-eval.html

### How to integrate: Callback functions
To communicate with TMC5160 IC, the TMC-API library needs to know which bus (UART, SPI) it shall use. For that, the callback function **'tmc5160_getBusType()'** needs to be implemented.
Additionally, implement the following callback functions to access the chip via UART:
1. **tmc5160_readWriteUART()**, which is a HAL wrapper function that provides the necessary hardware access.
2. **tmc5160_getNodeAddress()**, that returns the node/slave address. Node address could be set in NODECONF (0x3) register and the address could be incremented as defined by AD0, AD1 and AD2. (Node address + ADx) must be less than 255. For further details please consult the datasheet of TMC5160.

### Sharing the CRC table with other TMC-API chips
The TMC5160 UART protocol uses an 8 bit CRC. For calculating this, a table-based algorithm is used. This table (tmcCRCTable_Poly7Reflected[256]) is 256 bytes big and identical across multiple different Trinamic chips (i.e. TMC2209).
If multiple Trinamic chips are being used in the same project, avoiding redundant copies of this table could save memory. It is possible to substitute this CRC table with another CRC table.

## Accessing the TMC5160 via SPI
The following diagram depicts how to access the TMC5160 via SPI using the TMC-API.

![screenshot](registercall_hierarchy_flowchart_SPI.svg)

The description of the functions, in the above flowchart, are as follows:
- The functions tmc5160_readRegister and tmc5160_writeRegister are used to read and write the registers respectively. These functions check the current active bus and calls the bus-specific function i.e readRegisterSPI or writeRegisterSPI.
- These bus specific functions constructs the datagram and further calls the bus specific callback 'tmcXXXX_readWriteSPI.
- This callback function further calls the hardware specific read/write function for SPI and needs to be implemented externally.

### How to integrate: Callback functions
To communicate with TMC5160 IC, the TMC-API library needs to know which bus (UART, SPI) it shall use. For that, the callback function **'tmc5160_getBusType()'** needs to be implemented.
Additionally, implement the following callback functions to access the chip via SPI:
1. **tmc5160_readWriteSPI()**, which is a HAL wrapper function that provides the necessary hardware access. This function should also set the chip select pin CSN to low before starting the data transfer and set to high upon completion. Please refer to the datasheet of the IC for further details.

### Option to use the cache logic for Write-Only registers
The chip features write-only registers that are unable to be read, necessitating the creation of a shadow copy to cache their contents. This copy is automatically updated whenever data is written to these registers. This cache logic could be enabled by setting the macro **TMC5160_CACHE** to **'1'** or disabled by setting to **'0'** respectively. If this feature is enabled then there comes another option to use **tmc5160_cache** function, which is already implemeted in the API, by defining **TMC5160_ENABLE_TMC_CACHE** macro to **'1'** or one can implement their own function. The function **tmc5160_cache** works for both reading from and writing to the shadow array. It first checks whether the register has write-only access and data needs to be read from the hadow copy. On the basis of that, it returns **true** or **false**. The shadowRegisters on the premade cache implementation need to be one per chip. **TMC5160_IC_CACHE_COUNT** is set to '1' by default and is user-overwritable. If multiple chips are being used in the same project, increment its value to the number of chips connected.

## Further info
### Dependency graph for the ICs with new register R/W mechanism
This graph illustrates the relationships between files within the TMC-API library, highlighting dependencies and identifying the files that are essential for integrating the library into the custom projects.

![screenshot](uml-tmc-api.svg)

### Example usage: TMC-Evalsystem
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

## Migration status
The TMC5160 has been reworked to the access system described above. For more infos on the status of this and other ICs, check out the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).

