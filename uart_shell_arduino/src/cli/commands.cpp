#include "commands.h"
#include <Arduino.h>

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
  Serial.println("Status: All systems go.");
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

// command table
CommandEntry commands[] = {
  {"help", cmd_help, "List available commands"},
  {"status", cmd_status, "Show system status"},
  {"version", cmd_version, "Show version information"},
  {"say_hello", cmd_say_hello, "Say hello to someone"},
  {nullptr, nullptr} // end marker
};