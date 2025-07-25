#include "cli/cli.h"
// #include "hardware/hardware.h"

void setup() {
  cli_init();
  // shell_println("Initialized...");
}

void loop() {
  cli_poll(); // Poll for user input
}