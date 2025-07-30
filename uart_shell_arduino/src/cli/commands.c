#include "commands.h"
#include "cli.h"
#include "cli_utils.h"
#include "features/blink.h"
#include "hardware/hardware.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Add more command functions here as needed
void cmd_help() {
  shell_println("Available commands:");
    for (int i = 0; commands[i].name != NULL; i++) {
        shell_print(" ");
        shell_print(commands[i].name);
        shell_print(" - ");
        shell_println(commands[i].description);
    }
}

void cmd_status(char* args) {
  if(args){
    char* argv[MAX_ARGS];
    int argc = parse_args(args, argv, MAX_ARGS);

    if(argc > 0) {
      shell_println("Received arguments:");
      for (int i = 0; i < argc; ++i) {
        char num_str[4];
        snprintf(num_str, sizeof(num_str), "%d", i);

        shell_print("  [");
        shell_print(num_str);
        shell_print("]: ");
        shell_println(argv[i]);
      } 
    } else {
      shell_println("No arguments specified.");
    }
  }
}

void cmd_version() {
  shell_println("UART Shell v0.1.0");
}

void cmd_say_hello(char* args) {
  if (args && strlen(args) > 0) {
    shell_print("Hello, ");
    shell_println(args);
  } else {
    shell_println("Hello, World!");
  }
}

void cmd_led(char* args) {
  if(!args || strlen(args) == 0) {
    shell_println("Usage: led <on|off>");
    return;
  }
  char* argsv[MAX_ARGS];
  int argc = parse_args(args, argsv, MAX_ARGS);
  if (argc == 0) {
    shell_println("Usage: led <on|off>");
    return;
  }

  if (strcmp(args, "on") == 0) {
    gpio_set(LED_PIN, HIGH);
    shell_println("LED turned ON");
  } else if (strcmp(args, "off") == 0) {
    gpio_set(LED_PIN, LOW);
    shell_println("LED turned OFF");
  } else {
    shell_println("Invalid argument. Use 'on' or 'off'.");
  }
}

void cmd_set(char* args){
  if(!args || strlen(args) == 0){
    shell_println("Usage: <pin_num> <HIGH|LOW>");
    return;
  }

  char* argsv[MAX_ARGS];
  int argc = parse_args(args, argsv, MAX_ARGS);
  if (argc != 2) {
    shell_println("Usage: <pin_num> <HIGH|LOW>");
    return;
  }

  // Argument validation
  int pin = atoi(argsv[0]);
  if(!is_valid_pin(pin)){
    shell_println("Invalid pin number. Try Again");
    return;
  }

  char* comm = argsv[1];
  str_to_upper(comm);

  // Parse comm
  uint8_t comm_int;
  if(!parse_pin_state(comm, &comm_int)){
    shell_println("Invalid pin state. Use HIGH or LOW.");
    return;
  }

  //TODO: Refactor to configure pins with hardware, like in cli.cpp
  shell_println("Setting PinMode to OUTPUT");
  gpio_init_output(pin);
  shell_print("Setting Pin ");
  shell_println(comm);
  gpio_set(pin, comm_int);

}

void cmd_blink(char* args){
    if(!args || strlen(args) == 0){
    shell_println("Usage: <pin_num> <freq>");
    return;
  }

  char* argsv[MAX_ARGS];
  int argc = parse_args(args, argsv, MAX_ARGS);
  if (argc != 2) {
    shell_println("Usage: <pin_num> <freq>");
    return;
  }

  // Argument validation
  int pin = atoi(argsv[0]);
  if(!is_valid_pin(pin)){
    shell_println("Invalid pin number. Try Again");
    return;
  }

  int freq = atoi(argsv[1]);
  if(freq == 0){
    shell_println("Invalid frequency number. Try Again");
    return;
  }
  
  // Start blinking
  shell_println("Starting Blink");
  blink_state.active = 1;
  blink_state.pin = 13;
  blink_state.interval_ms = 1000 / (2 * freq);
  blink_state.last_toggle_time = get_time_ms();
}

void cmd_stop_blink(){
  shell_print("Stopping Blink");
  blink_state.active = 0;
}

// command table
CommandEntry commands[] = {
  {"help", cmd_help, "List available commands"},
  {"status", cmd_status, "Show system status"},
  {"version", cmd_version, "Show version information"},
  {"say_hello", cmd_say_hello, "Say hello to someone"},
  {"led", cmd_led, "Control the LED (on/off)"},
  {"set", cmd_set, "Set's high or low state of a pin"},
  {"blink", cmd_blink, "Starts blinking the LED at [pin] [input]/sec"},
  {"stop_blink", cmd_stop_blink, "Stops blinking the LED at [pin]"},
  {NULL, NULL} // end marker
};