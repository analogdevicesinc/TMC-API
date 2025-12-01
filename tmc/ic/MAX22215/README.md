# max22215


## How to use

To access the max22215's registers, the TMC-API offers two functions: **max22215_readRegister** and **max22215_writeRegister**.
Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/max22215 folder into the custom project.
2. Include the max22215.h file in the custom source code.
3. Implement the necessary callback functions (see below).
4. (optional): Take a look at the Examples subfolder for ready-made examples of the TMC-API usage.

## Accessing the max22215 via I2C
The following diagram depicts how to access the MAX22200 via I2C using the TMC-API.

![screenshot](registercall_hierarchy_flowchart_I2C.svg)

The description of the functions, in the above flowchart, are as follows:
- The functions max22215_readRegister and max22215_writeRegister are used to read and write the registers respectively. These functions check the current active bus and call the bus-specific function i.e readRegisterI2C or writeRegisterI2C.
- These bus specific functions construct the datagram and further call the bus specific callback 'max22215_readWriteI2C'.
- This callback function further calls the hardware specific read/write function for I2C and needs to be implemented externally.

### How to integrate: Callback functions
Implement the following callback functions to access the chip via I2C:
1. **max22215_readWriteI2C()**, which is a HAL wrapper function that provides the necessary hardware access. 

## Further info
### Dependency graph for the ICs with new register R/W mechanism
This graph illustrates the relationships between files within the TMC-API library, highlighting dependencies and identifying the files that are essential for integrating the library into the custom projects.

![screenshot](uml-tmc-api.svg)

### Example usage: TMC-Evalsystem
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

## Migration status
The max22215 has been reworked to the access system described above. For more infos on the status of this and other ICs, check out the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).


