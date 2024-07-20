# STM32F405 Stub Project
## Dependencies
- openocd
- arm-none-eabi-gcc
- arm-none-eabi-gdb
- ChibiOS source

## Setup
- Clone the ChibiOS source repo locally.
- Define the "CHIBIOS_SOURCE_PATH" environment variable to point to the location the ChibiOS repo.

## Usage
### Compilation
- 'make'
### Programming
- 'make flash'
### Debugging
- In VS-code, use 'run debugger'

## Filesystem
- build - Compilation output, includes main.elf (the application file).
- cfg - ChibiOS configuration files.
- src - Project source code.
