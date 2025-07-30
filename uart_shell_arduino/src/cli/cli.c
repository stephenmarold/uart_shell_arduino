#include "cli.h"
#include "cli_utils.h"
#include "commands.h"
#include <string.h>
#include "../hardware/hardware.h"
#include <stdint.h>

#include "features/blink.h"

char inputBuffer[MAX_CMD_LENGTH]; // for storing user input
uint8_t buffer_index = 0; // current index in inputBuffer

void cli_init() {
    serial_begin(9600);
    shell_init();
    shell_println("UART Shell Ready");
    shell_println("Type 'help' for commands.");
    shell_print(">");

    gpio_init_output(blink_state.pin);
}

void cli_poll(){
    while(serial_available()) {
      get_user_input();
  }

      // blink logic. Move to a tick func after testing. 
      if(blink_state.active) {
        uint64_t cur_time = get_time_ms();
        uint64_t diff = cur_time - blink_state.last_toggle_time;
        if((cur_time - blink_state.last_toggle_time) > blink_state.interval_ms){
          blink_state.state = blink_state.state == HIGH ? LOW : HIGH;
          blink_state.last_toggle_time = cur_time;
          gpio_set(blink_state.pin, blink_state.state);
        }
      }
}

void get_user_input(){
    char c = serial_read();

    if (c == '\n' || c == '\r') {
      shell_println("");                                 // print a new line
      inputBuffer[buffer_index] = '\0';                        // null-terminate the string
      handle_command(inputBuffer);
      buffer_index = 0;                                        // reset index for next command
      shell_println(">");
    }
    else if(c == 8 || c == 127){                        // Detect backspace and overwrite. 
      if(buffer_index > 0){
        buffer_index--;
        inputBuffer[buffer_index]= '\0';
        serial_write('\b');
        serial_write(' ');
        serial_write('\b');
      }
    }
    else if (buffer_index < MAX_CMD_LENGTH - 1) {              // prevent buffer overflow
      inputBuffer[buffer_index++] = c;                         // store character in buffer
      serial_write(c);                                  // echo character back to terminal    
    }
    else {
      shell_println("Error: Command too long");
      buffer_index = 0;                                        // reset index to avoid overflow
    }
}

void handle_command(char* input) {
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

