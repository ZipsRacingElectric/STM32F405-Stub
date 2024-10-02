# STM32F405 Stub Project
## Dependencies
- make
- arm-none-eabi-gcc
- openocd
- ChibiOS 21.11.3
- FMPP - FreeMark Pre-Processor

## Setup
- Clone this repo using 'git clone <TODO(Barach)>'
- Initialize the repo's submodule using 'git submodule init <TODO(Barach)>'
- Download and extract ChibiOS 21.11.3 (https://github.com/ChibiOS/ChibiOS/releases/tag/ver21.11.3).
- Define the "CHIBIOS_SOURCE_PATH" environment variable to point to the location the ChibiOS source.

### For Windows
Most dependicies of this project are not natively built for Windows. A solution to this is to use MinGW, a <TODO(Barach)> that allows these programs to be used with Windows.
- Install MinGW
- <TODO(Barach)>

### Recommended VS-Code Extensions
- C/C++
- Clangd
- Cortex-Debug
- Doxygen
- Doxygen Documentation Generator
- RedHat XML

## Usage
### Compilation
- Use 'make' to compile the program. Files that have not been modified will not re-compiled.
- Use 'make clean' to delete all build files.

### Programming
- Use 'make flash' to call OpenOCD. If modifications were made, the program will be recompiled.

### Debugging
- In VS-code, use 'Run Debugger'.

## Filesystem
- build - Compilation output, includes the .elf file (the application file).
- config - ChibiOS configuration files.
- src - Project source code.
