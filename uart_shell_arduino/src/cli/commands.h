#ifndef COMMANDS_H
#define COMMANDS_H

#define MAX_ARGS 10
#define MAX_PINS 13

typedef void (*CommandFunction)(char* args);

struct CommandEntry {
  const char* name;               // command name
  CommandFunction function;       // function to call
  const char* description;        // command description
};

// expose command table
extern CommandEntry commands[];

// Function prototypes
void handleCommand(char* cmd);
void cmd_help(char* args);
void cmd_status(char* args);
void cmd_version(char* args);
void cmd_say_hello(char* args);
void cmd_led(char* args);
void cmd_set(char* args);

//move later
void str_to_upper(char* str);

#endif
