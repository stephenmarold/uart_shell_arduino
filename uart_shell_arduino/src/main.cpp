#include <Arduino.h>

typedef void (*CommandFunction)(char* args);

struct CommandEntry {
  const char* name;               // command name
  CommandFunction function;       // function to call
};

#define MAX_CMD_LENGTH 64

char inputBuffer[MAX_CMD_LENGTH]; // for storing user input
uint8_t index = 0; // current index in inputBuffer

// Function prototypes
void handleCommand(char* cmd);
void cmd_help(char* args);
void cmd_status(char* args);
void cmd_version(char* args);

// command table
CommandEntry commands[] = {
  {"help", cmd_help},
  {"status", cmd_status},
  {"version", cmd_version},
  {nullptr, nullptr} // end marker
};

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  Serial.println("UART Shell Ready");
  Serial.println(">");
}

void loop() {
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

// put function definitions here:
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

// Add more command functions here as needed
void cmd_help(char* args) {
  Serial.println("Available commands:");
  Serial.println("  help - Show this help message");
  Serial.println("  status - Show system status");
  Serial.println("  version - Show version information");
}

void cmd_status(char* args) {
  Serial.println("Status: All systems go.");
}

void cmd_version(char* args) {
  Serial.println("UART Shell v0.1.0");
}