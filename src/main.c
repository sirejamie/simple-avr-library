#include "simple_avr/gpio.h"
#include "simple_avr/delay.h"

#define BUILTIN_LED 13

int main(void) {
  pin_mode(BUILTIN_LED, PINMODE_OUTPUT);

  while (1) {
    write_digital(BUILTIN_LED, HIGH);
    delay(250);
    write_digital(BUILTIN_LED, LOW);
    delay(250);
  }

  return 0;
}
