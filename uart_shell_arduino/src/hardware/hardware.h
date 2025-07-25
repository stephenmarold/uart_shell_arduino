#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// temp for testing
#define LED_PIN 13 

void shell_init();

// GPIO functions
void gpio_init_output(uint8_t pin);
void gpio_set(uint8_t pin, uint8_t state);

// Analog
int analog_read(uint8_t pin);

// Shell output
void shell_print(const char* msg);
void shell_println(const char* msg);
void shell_print_int(int val);

// Serial functions
void serial_begin(int baudrate);
int serial_available(void);
char serial_read(void);

void serial_write(char c); // for low-level output (rarely needed)

#ifdef __cplusplus
}
#endif

#endif