set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/avr-toolchain-win32.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.20..3.41)
project(simple-avr-library
    VERSION 1.0.0
    DESCRIPTION "A small library built on top of AVR."
    LANGUAGES C
)

# ---
set(AVR_FCPU "10000000" CACHE STRING "CPU Frequency")
set(AVR_MCU "atmega328p" CACHE STRING "Device type")
set(AVR_PROGRAMMING_PARTNO "m328p" CACHE STRING "Part Number (avrdude)")
set(AVR_PROGRAMMING_PORT "COM8" CACHE STRING "Programming Port (avrdude)")
set(AVR_PROGRAMMING_BAUD "115200" CACHE STRING "Baud rate (avrdude)")

# ---
set(endeavor-definitions FCPU=${AVR_FCPU})
set(endeavor-compile-options -mmcu=${AVR_MCU} -Os -Wall -Wextra -Wpedantic)
set(endeavor-link-options -mmcu=${AVR_MCU} -Wl,--gc-sections,--relax)

# ---
add_library(simple-avr-library OBJECT 
    include/simple_avr/gpio.h 
    include/simple_avr/delay.h
    include/simple_avr/typedef.h
    
    src/simple_avr/gpio.c
)
target_include_directories(simple-avr-library PRIVATE src PUBLIC include PUBLIC vendor/avr-toolchain/avr-win32/avr/include)
target_compile_features(simple-avr-library PRIVATE c_std_11)

target_compile_definitions(simple-avr-library PRIVATE ${endeavor-definitions})
target_compile_options(simple-avr-library PUBLIC ${endeavor-compile-options})
target_link_options(simple-avr-library PUBLIC ${endeavor-link-options})

# ---
add_executable(simple-avr-example src/main.c)
target_compile_features(simple-avr-example PRIVATE c_std_11)
set_target_properties(simple-avr-example PROPERTIES SUFFIX ".elf")
target_link_libraries(simple-avr-example simple-avr-library)

add_custom_command(
    TARGET simple-avr-example
    POST_BUILD
    COMMENT "[simple-avr-example] Generating hex file and writing to AVR device..."
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom $<TARGET_FILE:simple-avr-example> $<TARGET_FILE_BASE_NAME:simple-avr-example>.hex
    COMMAND ${AVR_SIZE} $<TARGET_FILE:simple-avr-example>
    COMMAND ${AVR_DUDE} -c stk500v2 -p ${AVR_MCU} -P ${AVR_PROGRAMMING_PORT} -b ${AVR_PROGRAMMING_BAUD} -U flash:w:$<TARGET_FILE_BASE_NAME:simple-avr-example>.hex:i
    VERBATIM
)

# ---
# cmake -G "Ninja" -B build -S .
# cmake --build build