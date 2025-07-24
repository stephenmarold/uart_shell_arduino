#include "commands.h"
#include <Arduino.h>
#include "cli.h"
#include "cli_utils.h"

// Add more command functions here as needed
void cmd_help(char* args) {
  Serial.println("Available commands:");
    for (int i = 0; commands[i].name != nullptr; i++) {
        Serial.print(" ");
        Serial.print(commands[i].name);
        Serial.print(" - ");
        Serial.println(commands[i].description);
    }
}

void cmd_status(char* args) {
  if(args){
    char* argv[MAX_ARGS];
    int argc = parse_args(args, argv, MAX_ARGS);

    if(argc > 0) {
      Serial.println("Received arguments:");
      for (int i = 0; i < argc; ++i) {
        Serial.print("  [");
        Serial.print(i);
        Serial.print("]: ");
        Serial.println(argv[i]);
      } 
    } else {
      Serial.println("No arguments specified.");
    }
  }
}

void cmd_version(char* args) {
  Serial.println("UART Shell v0.1.0");
}

void cmd_say_hello(char* args) {
  if (args && strlen(args) > 0) {
    Serial.print("Hello, ");
    Serial.println(args);
  } else {
    Serial.println("Hello, World!");
  }
}

void cmd_led(char* args) {
  if(!args || strlen(args) == 0) {
    Serial.println("Usage: led <on|off>");
    return;
  }
  char* argsv[MAX_ARGS];
  int argc = parse_args(args, argsv, MAX_ARGS);
  if (argc == 0) {
    Serial.println("Usage: led <on|off>");
    return;
  }

  if (strcmp(args, "on") == 0) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED turned ON");
  } else if (strcmp(args, "off") == 0) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED turned OFF");
  } else {
    Serial.println("Invalid argument. Use 'on' or 'off'.");
  }
}

void cmd_set(char* args){
  if(!args || strlen(args) == 0){
    Serial.println("Usage: <pin_num> <HIGH|LOW>");
    return;
  }

  char* argsv[MAX_ARGS];
  int argc = parse_args(args, argsv, MAX_ARGS);
  if (argc != 3) {
    Serial.println("Usage: <pin_num> <HIGH|LOW>");
    return;
  }

  // Argument validation
  if(strcmp(argsv[0], "pin") != 0){
    Serial.println("Unsupported command. Try Again");
    return;
  }

  int pin = atoi(argsv[1]);
  if(!is_valid_pin(pin)){
    Serial.println("Invalid pin number. Try Again");
    return;
  }

  char* comm = argsv[2];
  str_to_upper(comm);

  // Parse comm
  uint8_t comm_int = parse_pin_state(comm);

  //TODO: Refactor to configure pins with hardware, like in cli.cpp
  Serial.println("Setting PinMode to OUTPUT");
  pinMode(pin, OUTPUT);
  Serial.print("Setting Pin ");
  Serial.println(comm);
  digitalWrite(pin, comm_int);

}

// command table
CommandEntry commands[] = {
  {"help", cmd_help, "List available commands"},
  {"status", cmd_status, "Show system status"},
  {"version", cmd_version, "Show version information"},
  {"say_hello", cmd_say_hello, "Say hello to someone"},
  {"led", cmd_led, "Control the LED (on/off)"},
  {"set", cmd_set, "Set's high or low state of a pin"},
  {nullptr, nullptr} // end marker
};