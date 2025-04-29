# TMC-API

The TMC-API is a portable C library for working with Trinamic ICs in embedded projects.
It is CPU-independent and self-contained (no external dependencies).

The TMC-API is getting a rework of its core structure. This will include new mechanisms for reading and writing the registers. The new mechanism is designed to provide easy access to the registers of Trinamic ICs. It offers convenient read and write functions along with registers and their bitfields definitions that simplify the process of interacting with the registers. Users can quickly and effortlessly retrieve information from registers or modify their values with just a few lines of code. These functions greatly simplify the process of working with IC registers, allowing developers to harness the full potential of the ICs' capabilities and save valuable developer time.

To further aid developers in utilizing our API, we have started to include an examples folder for each IC. This folder contains a collection of functions that showcase specific functionalities of the IC. Each example serves as a sample code, helping developers understand how to utilize the API for different purposes. It also serves as a comprehensive resource that accelerates the learning curve and assists in building robust applications.

For the details on which ICs currently feature the new mechanism as well as the details on upcoming releases, please consult the [migration page](https://github.com/analogdevicesinc/TMC-API/issues/53).

## New Mechanism
The new mechanism  makes the register access simpler while still allowing higher level functionality.For details of the migration to the new mechanism, [see here](https://github.com/analogdevicesinc/TMC-API/issues/53).

## Installation
To set up your project, first consult the README page of the particular IC. For the ICs with the old mechanism, simply copy the source files you need:
- **tmc/helpers/** contains helper files needed by all other TMC-API source files.
- **tmc/ic/** contains all the files for different ICs. For each IC you want to use, copy the corresponding folder.
- **tmc/ramp/** contains simple software linear ramp functions that can be used in applications. Copy them if needed by your project.

For the ICs with the new implementation, please consult their [README](https://github.com/analogdevicesinc/TMC-API/blob/master/tmc/ic/TMC5272/README.md) page.

## Usage
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/analogdevicesinc/TMC-EvalSystem)

**To use the new feature of TMC-API**, please refer to the specific IC's README page.

**For the old implementation**, perform the following steps in your code:
- Implement the tmcXXXX_readWriteArray() function in in your code. This function provides the necessary hardware access to the TMC-API.
- Call tmcXXXX_init() once for each Trinamic IC in your design. This function initializes an IC object which represents one physical IC.
- Call tmcXXXX_periodicJob() periodically. Pass a millisecond timestamp as the tick parameter.
- After initializing, calling tmcXXXX_reset() or tmcXXXX_restore(), the TMC-API will write multiple registers to the IC (referred to as IC configuration). Per call to tmcXXXX_periodicJob(), one register will be written until IC configuration is completed.
- Once the IC configuration is completed, you can use tmcXXXX_readInt() and tmcXXXX_writeInt() to read and write registers.

## Changelog

**Version 3.11.1: (WIP)**
- Reworked MAX22216 CRC calculation to be more efficient. This is a backwards-incompatible change for anyone using the CRC calculation function max22216_CRC() directly.

**Version 3.11.0: (Released)**
- Added MAX22215 to the API.
- Various bug fixes and code cleanup.

**Version 3.10.10: (Released)**
- Completed API rework for TMC4361A.

**Version 3.10.9: (Released)**
- Completed API rework for TMC2660 and MAX22216.

**Version 3.10.5: (Released)**
 - Removed TMC2590 from the API because the IC is available for last time buy only and going to be deprecated soon.

**Version 3.10.4: (Released)**
 - Finished the API rework for TMC5160, TMC5130, TMC5062, TMC5072, TMC5240, TMC2224, TMC2225, TMC2226, TMC2130, TMC2160, TMC5031, TMC2208, TMC5041, TMC2300, TMC2240, TMC7300, TMC6100, TMC6200 and TMC4671. For further information click [here](https://github.com/analogdevicesinc/TMC-API/issues/53).
 - Various bugfixes for MAX22204 and MAX22210.
 - Code cleanup.
 
**Version 3.10.3: (Released)**
- Completed API rework for TMC2209.

**Version 3.10.2: (Released)**
- Completed API rework phase-1 for TMC2262,TMC5262.

**Version 3.10.1: (Released)**
- Removed obselete ICs i.e; TMC846X,TMC389,TMC457,TMC4210,TMC424,TMC429,TMC4330,TMC4331 & TMC43XX.
- Added simpler register Read/Write mechanism for TMC5271
- Various bugfixes

**Version 3.10: (Released)**
- Added TMC2262 and TMC5262
- Added simpler register Read/Write mechanism for TMC5272
- Various bugfixes
