# TMC-API

The TMC-API is a portable C library for working with Trinamic ICs in embedded projects.
It is CPU-independent and self-contained (no external dependencies).

The TMC-API is designed to provide easy access to the registers of Trinamic ICs. It offers convenient read and write functions along with registers and their bitfields definitions that simplify the process of interacting with the registers. Users can quickly and effortlessly retrieve information from registers or modify their values with just a few lines of code. These functions greatly simplify the process of working with IC registers, allowing developers to harness the full potential of the ICs' capabilities and save valuable developer time.

To further aid developers in utilizing our API, we have included an examples folder for each IC. This folder contains a collection of functions that showcase specific functionalities of the IC. Each example serves as a sample code, helping developers understand how to utilize the API for different purposes. It also serves as a comprehensive resource that accelerates the learning curve and assists in building robust applications.

## Installation
To set up your project to use the TMC-API, simply copy the source files you need:
- **tmc/ic/** contains all the files for different ICs along with **Examples** subfolder that further contains sample functions that serve as a valuable reference, offering developers ready-to-use sample codes for  specific functionalities. For each IC you want to use, copy the corresponding folder.
- **tmc/ramp/** contains simple software linear ramp functions that can be used in applications. Copy them if needed by your project.

## Usage
**For a reference usage of the TMC-API**, visit the [TMC-Evalsystem](https://github.com/trinamic/TMC-EvalSystem)

**To use the TMC-API**, include the chip headers and implement the following functions and add them to your code:
- The function **tmcXXXX_readWriteSPI()** and/or **tmcXXXX_readWriteUART()**, depending on which communication protocols are supported by the IC. These functions provides the necessary hardware access to the TMC-API.
- If the chip supports more than one communication protocol then implement **tmcXXXX_getBusType()** that returns the active bus type.
- If UART is also suppoted by the IC then implement **tmcXXXX_getNodeAddress()** that returns the node/slave address. You also need to copy the CRC table stored in **tmcCRCTable_Poly7Reflected[256]** from the **TMCXXXX** source file to your code or add your own CRC table.

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
