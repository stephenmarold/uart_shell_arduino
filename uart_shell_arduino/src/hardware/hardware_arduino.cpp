#include <Arduino.h>
#include "hardware.h"

void gpio_init_output(uint8_t pin) {
  pinMode(pin, OUTPUT);
}

void gpio_set(uint8_t pin, uint8_t state) {
  digitalWrite(pin, state);
}

int analog_read(uint8_t pin) {
  return analogRead(pin);
}

void shell_print(const char* msg) {
  Serial.print(msg);
}

void shell_println(const char* msg) {
  Serial.println(msg);
}

void shell_print_int(int val) {
  Serial.print(val);
}