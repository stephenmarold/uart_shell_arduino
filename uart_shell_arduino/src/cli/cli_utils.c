#include "cli_utils.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int parse_args(char* args, char** argsv, int max_args){
  int count = 0;

  if (!args || strlen(args) == 0) {                     // check if args is null or empty
    return 0;                                          // return 0 if no arguments
  }

  // tokenize the input string using space as delimiter
  // strtok modifies the input string, so we work on a copy
  static char tempBuffer[MAX_CMD_LENGTH];
  strncpy(tempBuffer, args, MAX_CMD_LENGTH);
  tempBuffer[MAX_CMD_LENGTH - 1] = '\0';                // ensure null termination

  char* token = strtok(tempBuffer, " ");
  while (token != NULL && count < max_args) {
    argsv[count++] = token;                            // store the argument
    token = strtok(NULL, " ");                      // get next argument
  }
  return count;                                        // return number of arguments parsed
}

void str_to_upper(char* str){
  while(*str != '\0'){void serial_begin(int baudrate);
int serial_available(void);
char serial_read(void);

    *str = toupper((unsigned char)*str);
    str++;
  }
}

bool is_valid_pin(int pin){
    return (pin > 1 && pin <= MAX_PINS);
}

bool parse_pin_state(const char* str, uint8_t* out_state) {
    if (!str) return false;

    if (strcasecmp(str, "HIGH") == 0) {
        *out_state = HIGH;
        return true;
    } else if (strcasecmp(str, "LOW") == 0) {
        *out_state = LOW;
        return true;
    }

    return false;
}