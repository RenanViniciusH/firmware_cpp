#pragma once
#include "driver/gpio.h"

enum class LedMode {
    OFF,
    ON,
    BLINK_FAST,
    BLINK_SLOW,
    BLINK_ERROR
};

void led_init(gpio_num_t pin);
void led_set_mode(LedMode mode);
