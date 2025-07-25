#include "cli/cli.h"

void setup() {
  cli_init();
}

void loop() {
  cli_poll(); // Poll for user input
}