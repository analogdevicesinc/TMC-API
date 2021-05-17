# TMC-API

The TMC-API is a portable C library for working with Trinamic ICs in embedded projects.
It is CPU-independent and self-contained (no external dependencies).

The TMC-API allows easy access to the registers of Trinamic ICs. It provides definitions for all IC
registers and their bitfields.

## Installation
To set up your project to use the TMC-API, simply copy the source files you need:
- **tmc/helpers/** contains helper files needed by all other TMC-API source files. Always copy this folder.
- **tmc/ic/** contains all the files for different ICs. For each IC you want to use, copy the corresponding folder.
- **tmc/ramp/** contains simple software linear ramp functions that can be used in applications. Copy them if needed by your project.

## Usage
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/trinamic/TMC-EvalSystem)

**To use the TMC-API**, perform the following steps in your code:
- Implement the **tmcXXXX_readWriteArray()** function in **in your code**. This function provides the necessary hardware access to the TMC-API.
- Call **tmcXXXX_init()** once for each Trinamic IC in your design. This function initializes an *IC object* which represents one physical IC.
- Call **tmcXXXX_periodicJob()** periodically. Pass a millisecond timestamp as the *tick* parameter.
- After initializing, calling **tmcXXXX_reset()** or **tmcXXXX_restore()**, the TMC-API will write multiple registers to the IC (referred to as *IC configuration*). Per call to **tmcXXXX_periodicJob()**, one register will be written until IC configuration is completed.
- Once the IC configuration is completed, you can use **tmcXXXX_readInt()** and **tmcXXXX_writeInt()** to read and write registers.

## Changelog
**Version 3.06: (Beta)**
- Full TMC2160 support
- Begin TMC7531 support
- Begin TMC4672 support
- Begin TMC2590 support
- Added new software ramp generator (linear)
- TMC2041 fixed missing register fields
- Various bugfixes
- Internal optimizations

**Version 3.05: (Released)**
