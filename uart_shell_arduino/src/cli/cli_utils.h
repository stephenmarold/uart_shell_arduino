#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#define MAX_ARGS 8
#define MAX_CMD_LENGTH 64

#define MAX_PINS 13

#ifndef GPIO_LEVELS_H
#define GPIO_LEVELS_H

#define HIGH 1
#define LOW  0

#define OUTPUT 1
#define INPUT  0

#endif

#include <stdbool.h>
#include <stdint.h>

int parse_args(char* args, char** argv, int max_args);
void str_to_upper(char* str);
bool is_valid_pin(int pin);
bool parse_pin_state(const char* str, uint8_t* out_state);
// bool is_number(const char* str);  // Optional for later

#endif