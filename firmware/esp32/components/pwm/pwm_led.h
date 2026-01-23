#ifndef PWM_LED_H
#define PWM_LED_H

#include "driver/ledc.h"

template<
    gpio_num_t Pin,
    ledc_channel_t Channel,
    ledc_timer_t Timer = LEDC_TIMER_0
    >
class PwmLed {
public:
    static void init() {
        ledc_channel_config_t ch{
            .gpio_num   = Pin,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel    = Channel,
            .timer_sel  = Timer,
            .duty       = 0,
            .hpoint     = 0
        };
        ledc_channel_config(&ch);
    }

    static void setDuty(uint32_t duty) {
        ledc_set_duty(LEDC_LOW_SPEED_MODE, Channel, duty);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, Channel);
    }
};
#endif // PWM_LED_H
