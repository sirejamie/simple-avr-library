#ifndef SIMPLE_AVR_GPIO_H
#define SIMPLE_AVR_GPIO_H

#include <avr/io.h>

#include "simple_avr/typedef.h"

#define PINMODE_OUTPUT 0
#define PINMODE_INPUT 1
#define PINMODE_INPUT_PULLUP 2

void pin_mode(u8 pin, u8 mode);

#define LOW 0
#define HIGH 1

void write_digital(u8 pin, u8 value);
u8 read_digital(u8 pin);

#endif // SIMPLE_AVR_GPIO_H