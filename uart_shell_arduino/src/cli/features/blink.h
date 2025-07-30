#ifndef BLINK_H
#define BLINK_H

#include <stdint.h>

typedef struct {
    uint8_t pin;
    uint8_t active;
    uint8_t interval_ms;
    uint8_t last_toggle_time;
    uint8_t state; // 0 = LOW, 1 = HIGH
} BlinkState;

extern BlinkState blink_state;

#endif