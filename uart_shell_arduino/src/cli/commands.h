#ifndef COMMANDS_H
#define COMMANDS_H

typedef void (*CommandFunction)(char* args);

typedef struct {
  const char* name;               // command name
  CommandFunction function;       // function to call
  const char* description;        // command description
} CommandEntry;

// expose command table
extern CommandEntry commands[];

// Function prototypes
void cmd_help();
void cmd_status(char* args);
void cmd_version();
void cmd_say_hello(char* args);
void cmd_led(char* args);
void cmd_set(char* args);
void cmd_blink(char* args);
void cmd_stop_blink();

#endif
