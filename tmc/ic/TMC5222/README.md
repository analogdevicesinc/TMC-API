# TMC5222


## How to use

To access the TMC5222's registers, the TMC-API offers two functions: **tmc5222_readRegister** and **tmc5222_writeRegister**.
Each of these functions takes in an **icID**, which is used to identify the IC when multiple ICs are connected. This identifier is passed down to the callback functions (see How to Integrate).

## How to integrate: overview

1. Include all the files of the TMC-API/ic/tmc/TMC5222 folder into the custom project.
2. Include the TMC5222.h file in the custom source code.
3. Implement the necessary callback functions (see below).
4. (optional): Take a look at the Examples subfolder for ready-made examples of the TMC-API usage.

## Accessing the TMC5222 via I2C
The following diagram depicts how to access the TMC5222 via I2C using the TMC-API.
ToDo: Add I2C flowchart! (AS)

### How to integrate: Callback functions
To communicate with TMC5222 IC, the TMC-API library needs to know which bus (I2C, SPI) it shall use. For that, the callback function **'tmc5222_getBusType()'** needs to be implemented.


## Further info
### Dependency graph for the ICs with new register R/W mechanism
This graph illustrates the relationships between files within the TMC-API library, highlighting dependencies and identifying the files that are essential for integrating the library into the custom projects.
![screenshot](uml-tmc-api.png)

### Example usage: TMC-Evalsystem
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

## Migration status
The TMC5222 has been reworked to the access system described above. For more infos on the status of this and other ICs, check out the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).


