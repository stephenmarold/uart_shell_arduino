#include "blink.h"

// initialize blink state

BlinkState blink_state = {
    .active = 0,
    .pin = 13, //default
    .state = 0,
    .interval_ms = 500, //default
    .last_toggle_time = 0
};