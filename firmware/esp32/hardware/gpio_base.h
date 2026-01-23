#ifndef GPIO_BASE_H
#define GPIO_BASE_H

#include "driver/gpio.h"

template<typename Derived>
class GpioBase{
public:
    static void init(){
        gpio_set_direction(Derived::pin, Derived::mode);
    }
    static void set(bool value) {
        gpio_set_level(Derived::pin, value);
    }

    static bool get() {
        return gpio_get_level(Derived::pin);
    }
};

#endif // GPIO_BASE_H
