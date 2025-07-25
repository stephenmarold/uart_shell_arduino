#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

// GPIO functions
void gpio_init_output(uint8_t pin);
void gpio_set(uint8_t pin, uint8_t state);

// Analog
int analog_read(uint8_t pin);

// Shell output
void shell_print(const char* msg);
void shell_println(const char* msg);
void shell_print_int(int val);

#endif