# STM32F405 Stub Project
## Dependencies (Required)
- openocd
- arm-none-eabi-gcc
- ChibiOS source

## Dependencies (Optional)
- Cortex Debug
- arm-none-eabi-gdb

## Setup
- Clone the ChibiOS source repo locally.
- Define the "CHIBIOS_SOURCE_PATH" environment variable to point to the location the ChibiOS repo.

## Usage
### Compilation
- 'make'

### Programming
- 'make flash'

### Debugging
- In VS-code, use 'Run Debugger'

## Filesystem
- build - Compilation output, includes main.elf (the application file).
- config - ChibiOS configuration files.
- src - Project source code.