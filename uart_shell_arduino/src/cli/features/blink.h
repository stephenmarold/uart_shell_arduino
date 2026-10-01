#ifndef BLINK_H
#define BLINK_H

#include <stdint.h>

typedef struct {
    uint32_t pin;
    uint32_t active;
    uint32_t interval_ms;
    uint32_t last_toggle_time;
    uint32_t state; // 0 = LOW, 1 = HIGH
} BlinkState;

extern BlinkState blink_state;

#endif