#include "cli.h"
#include "cli_utils.h"
#include "commands.h"
#include <string.h>
#include "../hardware/hardware.h"
#include <stdint.h>

char inputBuffer[MAX_CMD_LENGTH]; // for storing user input
uint8_t index = 0; // current index in inputBuffer

void cli_init() {
    serial_begin(9600);
    shell_init();
    shell_println("UART Shell Ready");
    shell_println("Type 'help' for commands.");
    shell_print(">");
}

void cli_poll(){
    while(serial_available()) {
    char c = serial_read();

    if (c == '\n' || c == '\r') {
      shell_println("");                                 // print a new line
      inputBuffer[index] = '\0';                        // null-terminate the string
      handleCommand(inputBuffer);
      index = 0;                                        // reset index for next command
      shell_println(">");
    }
    else if(c == 8 || c == 127){                        // Detect backspace and overwrite. 
      if(index > 0){
        index--;
        inputBuffer[index]= '\0';
        serial_write('\b');
        serial_write(' ');
        serial_write('\b');
      }
    }
    else if (index < MAX_CMD_LENGTH - 1) {              // prevent buffer overflow
      inputBuffer[index++] = c;                         // store character in buffer
      serial_write(c);                                  // echo character back to terminal    
    }
    else {
      shell_println("Error: Command too long");
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
  char* args = strtok(NULL, "");

  //Debugging output
  if (!command) {
    shell_println("No command entered.");
    return;
  }

  for (int i = 0; commands[i].name != NULL; i++) {
    if (strcmp(command, commands[i].name) == 0) {
      commands[i].function(args);                       // call the command function
      return;
    }
  }

  shell_print("Unknown command: ");
  shell_println(command);
}

