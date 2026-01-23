#ifndef BOARDS_PINS_H
#define BOARDS_PINS_H


#include "driver/gpio.h"
struct BoardPins
{
    static constexpr gpio_num_t LED0 = GPIO_NUM_0;
    static constexpr gpio_num_t LED1 = GPIO_NUM_22;
    static constexpr gpio_num_t LED2 = GPIO_NUM_2;
    static constexpr gpio_num_t LED3 = GPIO_NUM_23;

    static constexpr gpio_num_t BUZZER = GPIO_NUM_18;
    static constexpr gpio_num_t BUTTON = GPIO_NUM_5;
};
#endif // BOARDS_PINS_H
