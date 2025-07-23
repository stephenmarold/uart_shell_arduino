UART Shell for Arduino

A lightweight, modular command-line interface (CLI) over UART for embedded development, designed to run on the Arduino Uno. This project is focused on building a professional-grade shell environment for embedded systems, showcasing low-level programming, input parsing, and hardware control via serial commands.
🧰 Features

    Command registry with function pointer dispatch

    Token-based command parsing with arguments

    Modular code structure (cli/, commands/)

    Serial echo and prompt system

    Built-in commands:

        hello – friendly greeting

        status – basic system status

        version – firmware version string

        help – lists available commands

📦 File Structure

src/
├── main.cpp # Entry point, delegates to CLI
├── cli/
│ ├── cli.cpp # Core UART shell: parsing, input, dispatch
│ ├── cli.h
│ ├── commands.cpp # Command implementations
│ └── commands.h

🚀 Getting Started
Requirements

    Arduino Uno

    PlatformIO with VSCode (recommended)

    USB connection for serial communication

Setup

    Clone this repo:

git clone https://github.com/stephenmarold/uart_shell_arduino
cd uart-shell_arduino

Upload firmware:

pio run --target upload

Open serial monitor:

    pio device monitor

Example Usage

> hello
> Hello, user.

> status
> Status: All systems nominal.

> version
> UART Shell v0.1.0

🛠 Planned Features

Argument parsing for multiple values (e.g., set pin 13 high)

Hardware interaction commands (GPIO, ADC, timers)

Command aliases

ANSI terminal enhancements (optional)

Help with command descriptions

    Bare-metal UART driver (no Serial library)

📚 Learning Goals

This project is part of a personal journey toward embedded systems mastery, including:

    Writing drivers

    Low-level hardware control

    Building real-time command systems

    Demonstrating hands-on C/C++ embedded design

📜 License

MIT License – free to use, learn from, and build upon.
