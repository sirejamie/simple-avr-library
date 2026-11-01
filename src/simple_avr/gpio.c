#include "simple_avr/gpio.h"

#include "simple_avr/delay.h"

void pin_mode(u8 pin, u8 mode) {
  /*
    pin should fall between 0 and 13; guards and edge-case resolution are
    necessary but coming soon.

    pins 0-7:   DDRD
    pins 8-13:  DDRB
  */

  if (mode == PINMODE_OUTPUT) {
    if (pin < 8)
      DDRD |= (1 << pin);
    else
      DDRB |= (1 << (pin - 8));
  } else if (mode == PINMODE_INPUT) {
    if (pin < 8)
      DDRD &= ~(1 << pin);
    else
      DDRB &= ~(1 << (pin - 8));
  } else if (mode == PINMODE_INPUT_PULLUP) {
    if (pin < 8) {
      DDRD &= ~(1 << pin);
      PORTD |= (1 << pin);
    } else {
      DDRB &= ~(1 << (pin - 8));
      PORTB |= (1 << (pin - 8));
    }
  }
}

void write_digital(u8 pin, u8 value) {
  /*
    pin should fall between 0 and 13; guards and edge-case resolution are
    necessary but coming soon.

    pins 0-7:   DDRD
    pins 8-13:  DDRB
  */

  if (value == HIGH) {
    if (pin < 8)
      PORTD |= (1 << pin);
    else
      PORTB |= (1 << (pin - 8));
  } else if (value == LOW) {
    if (pin < 8)
      PORTD &= ~(1 << pin);
    else
      PORTB &= ~(1 << (pin - 8));
  }
}

u8 read_digital(u8 pin) {
  /*
    pin should fall between 0 and 13; guards and edge-case resolution are
    necessary but coming soon.

    pins 0-7:   DDRD
    pins 8-13:  DDRB
  */

  u8 value = LOW;

  delay(2); // small debounce

  if (pin < 8)
    value = (!(PIND & (1 << pin)));
  else
    value = (!(PINB & (1 << (pin - 8))));

  return value;
}