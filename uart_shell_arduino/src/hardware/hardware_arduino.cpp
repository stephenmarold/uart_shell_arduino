#ifdef TARGET_ARDUINO
#include <Arduino.h>
#include "hardware.h"
// TODO: Move to config.h or similar

void shell_init(){
      // TODO: Move to hardware init func once more hardware is handled. 
    pinMode(LED_PIN, OUTPUT); // Initialize LED pin
    digitalWrite(LED_PIN, LOW); // Ensure LED is off initially
}

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


void serial_begin(int baudrate) {
    Serial.begin(baudrate);
}

int serial_available(void) {
    return Serial.available();
}

char serial_read(void) {
    return Serial.read();
}

void serial_write(char c) {
    Serial.write(c);
}

uint64_t get_time_ms(){
  return (uint64_t)millis();
}

#endif