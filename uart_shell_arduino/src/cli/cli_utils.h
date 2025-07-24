#ifndef CLI_UTILS_H
#define CLI_UTILS_H

#define MAX_ARGS 8
#define MAX_CMD_LENGTH 64

#define MAX_ARGS 10
#define MAX_PINS 13

int parse_args(char* args, char** argv, int max_args);
void str_to_upper(char* str);
bool is_valid_pin(int pin);
int parse_pin_state(const char* str);
// bool is_number(const char* str);  // Optional for later

#endif