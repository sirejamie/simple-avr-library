# Simple AVR Library

Simple AVR Library is a small programming library built for AVR-based Microcontroller Units.

## Commands

### Configure & Build

Configure and Build CMake:

> This uses the default configurations with F_CPU=10MHz and MCU=atmega328p. Be sure to change the AVR_PROGRAMMING_* configurations before exporting with avrdude.

```sh
cmake -G "Ninja" -B build -S .
```

### Exporting & Programming (with avrdude)

Build and Generate with CMake:

```sh
cmake --build build
```

## Platforms

Supported platforms are shown below:

* Windows x64

## License

[MIT](./LICENSE)
