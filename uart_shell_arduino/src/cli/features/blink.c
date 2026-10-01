#include "blink.h"
#include "../../hardware/hardware.h"

// initialize blink state

BlinkState blink_state = {
    .active = 0,
    .pin = 13, //default
    .state = 0,
    .interval_ms = 1000, //default
    .last_toggle_time = 0
};

void blink_start(uint8_t pin, int frequency_hz) {
    gpio_init_output(pin);
    blink_state.pin = pin;
    blink_state.interval_ms = (uint32_t)(1000.0 / (2.0 * frequency_hz));
    blink_state.last_toggle_time = get_time_ms();
    blink_state.active = 1;
}

void blink_stop(void) {
    blink_state.active = 0;
    blink_state.state = 0; // LOW
    gpio_set(blink_state.pin, blink_state.state);
}

void blink_tick(uint32_t cur_time) {
    if (blink_state.active) {
        if ((cur_time - blink_state.last_toggle_time) > blink_state.interval_ms) {
            blink_state.state = blink_state.state == 1 ? 0 : 1; // toggle state
            blink_state.last_toggle_time = cur_time;
            gpio_set(blink_state.pin, blink_state.state);
        }
    }
}
