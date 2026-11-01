#ifndef SIMPLE_AVR_DELAY_H
#define SIMPLE_AVR_DELAY_H

// TODO:
// Move this definition to a configuration file that would inject the F_CPU from the configurations here
#define F_CPU 10000000UL

#include <util/delay.h>

#define delay(milli) (_delay_ms(milli))
#define delay_us(micro) (_delay_us(micro))

#endif // SIMPLE_AVR_DELAY_H