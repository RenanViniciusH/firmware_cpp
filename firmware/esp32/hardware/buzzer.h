#ifndef BUZZER_H
#define BUZZER_H

#include "gpio_base.h"
#include "boards_pins.h"

class Buzzer : public GpioBase<Buzzer> {
public:
    static constexpr gpio_num_t pin  = BoardPins::BUZZER;
    static constexpr gpio_mode_t mode = GPIO_MODE_OUTPUT;
};

#endif // BUZZER_H
