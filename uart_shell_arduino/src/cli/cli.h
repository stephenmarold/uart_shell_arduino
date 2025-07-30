#ifndef CLI_H
#define CLI_H

// cli.h
// Initializes UART CLI — also calls Serial.begin()
void cli_init();

// Handles UART input and command dispatch — call this in loop()
void cli_poll();

// util funcs
void get_user_input();
void handle_command(char* input);
#endif