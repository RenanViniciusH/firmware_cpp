#ifndef DEVICES_H
#define DEVICES_H

#include "hardware/boards_pins.h"
#include "hardware/buzzer.h"
#include "components/led/led.h"
#include "components/pwm/pwm_timer.h"
#include "components/pwm/pwm_led.h"

using Led0 = PwmLed<BoardPins::LED0, static_cast<ledc_channel_t>(LEDC_CHANNEL_0)>;
using Led1 = PwmLed<BoardPins::LED1, static_cast<ledc_channel_t>(LEDC_CHANNEL_1)>;
using Led2 = PwmLed<BoardPins::LED2, static_cast<ledc_channel_t>(LEDC_CHANNEL_2)>;
using Led3 = PwmLed<BoardPins::LED3, static_cast<ledc_channel_t>(LEDC_CHANNEL_3)>;

#endif // DEVICES_H
