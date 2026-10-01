# UART Shell

A modular UART command-line interface for embedded systems. UART Shell provides serial access to GPIO control, LED blinking, and command diagnostics through a command registry and a hardware abstraction layer.

The shell runs as firmware on the microcontroller. A connected computer sends commands and receives responses through a serial terminal. After upload, VS Code and build tools are not required to use the shell.

## Features

- Command registry with function-pointer dispatch and built-in command descriptions.
- Space-delimited command and argument parsing.
- Serial input echo, backspace handling, and an interactive prompt.
- GPIO output control and built-in LED control.
- Nonblocking LED blinking with frequency specified in hertz.
- Runtime debug output that can be enabled or disabled from the shell.
- A C shell implementation with platform-specific hardware access behind a shared interface.

## Platform support

| Target | Status |
| --- | --- |
| Arduino Uno / Uno R3 (ATmega328P) | Implemented and verified on hardware. PlatformIO environment: `uno`. |
| Host simulator | Planned integration with a companion simulator in a separate repository. The simulator backend here is a placeholder. |
| STM32 | Planned. The STM32 backend is currently a placeholder. |
| Additional microcontrollers | Future support through dedicated hardware backends and build configurations. |

Firmware is built for a specific board. Uno firmware is not interchangeable with firmware for Uno R4, STM32, or other microcontroller families.

## Getting started

### Requirements

- Arduino Uno / Uno R3 and a USB data cable.
- [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html), or [PlatformIO IDE for VS Code](https://docs.platformio.org/en/latest/integration/ide/vscode.html).
- A serial terminal, such as PlatformIO's device monitor.

For VS Code, install **PlatformIO IDE** (`platformio.platformio-ide`) and its **Microsoft C/C++** dependency (`ms-vscode.cpptools`). PlatformIO IDE manages its own Core installation and the board's compiler and framework packages.

### Clone and build

These commands check out `develop`, which contains the current implementation. The PlatformIO project is inside the repository's `uart_shell_arduino` directory.

```sh
git clone --branch develop https://github.com/stephenmarold/uart_shell_arduino.git
cd uart_shell_arduino/uart_shell_arduino
pio run -e uno
```

Run these commands from a terminal where `pio` is available. PlatformIO IDE provides a **PlatformIO Core CLI** terminal in VS Code.

### Upload

Connect the board, then upload:

```sh
pio run -e uno -t upload
```

PlatformIO detects the upload port automatically. To select a specific connection:

```sh
pio device list
pio run -e uno -t upload --upload-port COM3
```

`COM3` is an example Windows port. On macOS, use the board's `/dev/cu.usbmodem...` or `/dev/cu.usbserial...` device; on Linux, use its `/dev/ttyACM...` or `/dev/ttyUSB...` device.

Uploading installs UART Shell as the board's application firmware, replacing its existing sketch.

### Connect to the shell

```sh
pio device monitor -e uno --baud 9600 --eol LF
```

To select a specific port:

```sh
pio device monitor --port COM3 --baud 9600 --eol LF
```

Use these settings with other serial terminals:

| Setting | Value |
| --- | --- |
| Baud rate | 9600 |
| Data bits | 8 |
| Parity | None |
| Stop bits | 1 |
| Flow control | None |
| Command terminator | LF or CR |
| Local echo | Off; the firmware echoes input |

Close any other serial monitor before opening the same port. Once connected, press Enter if necessary and type `help`.

On macOS, `screen` can connect directly from Terminal:

```sh
ls /dev/cu.*
screen /dev/cu.usbmodemXXXX 9600
```

Replace the device path with the connected board's port. To exit `screen`, press **Ctrl+A**, release the keys, press **K**, and confirm with **Y** if prompted. In PlatformIO's monitor, **Ctrl+C** closes the connection. Disconnecting the terminal leaves the firmware running.

## Commands

Command names are case-sensitive. The built-in LED is pin 13; `set` accepts pins 2 through 13.

| Command | Behavior |
| --- | --- |
| `help` | Lists registered commands and descriptions. |
| `version` | Prints the firmware version string, currently `UART Shell v0.1.0`. |
| `say_hello [name]` | Prints a greeting using the supplied text, or `Hello, World!` without arguments. |
| `status [args...]` | Prints supplied arguments and their indexes. Without arguments, produces no status output. |
| `led on` / `led off` | Sets the built-in LED high or low. Does not cancel an active blink operation. |
| `set <pin> <HIGH\|LOW>` | Configures the pin as an output and sets its level. State names are case-insensitive. |
| `blink <pin> <frequency>` | Starts blinking at the requested frequency in complete on/off cycles per second. Currently always targets pin 13. |
| `stop_blink` | Stops toggling and sets the blink pin LOW (off). |
| `debug on` / `debug off` | Enables or disables debug output. Currently controls diagnostic messages from `set` only. Defaults to off after reset. |

### Blink example

Enter each command separately in the serial terminal:

```text
blink 13 10
stop_blink
```

`blink 13 10` requests **10 complete flashes per second**. The interval between state changes is calculated as:

```text
interval_ms = 1000 / (2 * frequency)
```

At 10 Hz, this is 50 ms on and 50 ms off. Use a positive integer frequency. Timing is limited by millisecond resolution and the polling loop, so the actual rate is approximate. Only one blink operation is tracked at a time; a new `blink` command replaces its configuration.

Use `stop_blink` to stop blinking and turn the LED off.

### Debug output

```text
debug on
set 13 HIGH
debug off
```

With debug enabled, `set` prints additional messages about output configuration and the requested pin state. Other command responses remain visible regardless of debug mode. Blink timing and command parsing do not currently emit debug diagnostics.

## Architecture

```text
src/
├── main.c                         # Arduino setup/loop entry points
├── cli/
│   ├── cli.c / cli.h              # Serial input and command dispatch
│   ├── commands.c / commands.h    # Command handlers and registry
│   ├── cli_utils.c / cli_utils.h  # Argument parsing and debug utilities
│   └── features/
│       └── blink.c / blink.h      # Blink state
└── hardware/
    ├── hardware.h                 # Shared hardware interface
    ├── hardware_arduino.cpp        # Arduino implementation
    ├── hardware_sim.c              # Simulator placeholder
    └── hardware_stm32.c            # STM32 placeholder
```

The main loop calls `cli_poll()` to process input and update blinking without a blocking delay. Command handlers access serial I/O, GPIO, and the clock through `hardware.h`. The Arduino backend uses the Arduino framework and is selected with `TARGET_ARDUINO`.

The interface also declares analog input access, but an ADC shell command is not yet implemented. Simulator and STM32 support require backend implementations and build configuration; changing the target flag alone does not enable those platforms.

To embed the shell in another firmware application, integrate its sources, initialize it with `cli_init()`, and call `cli_poll()` regularly from the application loop.

## Roadmap

- **Companion simulator:** Integrate the shell with a simulator in a separate repository, using the shared hardware interface for serial I/O, GPIO, and time. Keep the simulator and firmware interfaces aligned for repeatable command and timing tests without physical hardware.
- **STM32 support:** Implement the hardware backend and add board-specific build and upload configurations.
- **Additional microcontrollers:** Extend platform support through new backends while preserving the command interface.
- **Blink improvements:** Honor the requested pin, isolate timing updates in a dedicated tick function, and strengthen frequency validation.
- **Diagnostics:** Add useful system status, broader debug output, and automated parser and timing tests.
- **Hardware commands:** Expose analog reads and expand GPIO and timer controls.
- **Terminal usability:** Add command history, tab completion, aliases, and optional ANSI terminal formatting.
- **Distribution:** Publish versioned firmware artifacts with board-specific flashing instructions and compatibility information.

## License

MIT. A standalone `LICENSE` file is not currently included in the repository.
