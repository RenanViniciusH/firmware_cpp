#include "pwm_timer.h"
#include "driver/ledc.h"

void pwm_timer_init()
{
    ledc_timer_config_t timer{};
    timer.speed_mode       = LEDC_LOW_SPEED_MODE;
    timer.timer_num        = LEDC_TIMER_0;
    timer.duty_resolution  = LEDC_TIMER_10_BIT;
    timer.freq_hz          = 5000;
    timer.clk_cfg          = LEDC_AUTO_CLK;
    timer.deconfigure      = false;

    ledc_timer_config(&timer);
}
