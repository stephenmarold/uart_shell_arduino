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

void blink_start(uint8_t pin, int frequency_hz);
void blink_stop(void);
void blink_tick(uint32_t cur_time);

#endif
