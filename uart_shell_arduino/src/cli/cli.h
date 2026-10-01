#ifndef CLI_H
#define CLI_H

#define CLI_MAX_CHARS_PER_POLL 16U // Maximum input characters processed per cli_poll() call

// cli.h
// Initializes UART CLI — also calls Serial.begin()
void cli_init();

// Handles bounded UART input, command dispatch, and blink updates — call this in loop()
void cli_poll();

// util funcs
void get_user_input();
void handle_command(char* input);
#endif
