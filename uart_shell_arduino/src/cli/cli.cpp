#include "cli.h"
#include "commands.h"
#include <Arduino.h>
#include <string.h>

#define MAX_CMD_LENGTH 64

char inputBuffer[MAX_CMD_LENGTH]; // for storing user input
uint8_t index = 0; // current index in inputBuffer

void cli_init() {
    Serial.begin(9600);
    Serial.println("UART Shell Ready");
    Serial.println("Type 'help' for commands.");
    Serial.print(">");
}

void cli_poll(){
    while(Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      Serial.println();                                 // print a new line
      inputBuffer[index] = '\0';                        // null-terminate the string
      handleCommand(inputBuffer);
      index = 0;                                        // reset index for next command
      Serial.println(">");
    }
    else if (index < MAX_CMD_LENGTH - 1) {              // prevent buffer overflow
      inputBuffer[index++] = c;                         // store character in buffer
      Serial.print(c);                                  // echo character back to terminal    
    }
    else {
      Serial.println("Error: Command too long");
      index = 0;                                        // reset index to avoid overflow
    }
  }
}

void handleCommand(char* input) {
  if(!input || strlen(input) == 0) return;

  char tempBuffer[MAX_CMD_LENGTH];                      // temporary buffer for command processing
  strncpy(tempBuffer, input, MAX_CMD_LENGTH);           // copy input to buffer
  tempBuffer[MAX_CMD_LENGTH - 1] = '\0';                // ensure null termination
  
  // split the input into command and arguments
  char* command = strtok(tempBuffer, " ");
  char* args = strtok(NULL, " ");

  //Debugging output
  if (!command) {
    Serial.println("No command entered.");
    return;
  }

  for (int i = 0; commands[i].name != nullptr; i++) {
    if (strcmp(command, commands[i].name) == 0) {
      commands[i].function(args);                       // call the command function
      return;
    }
  }

  Serial.print("Unknown command: ");
  Serial.println(command);
}