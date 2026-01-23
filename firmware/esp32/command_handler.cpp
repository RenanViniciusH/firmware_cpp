#include "command_handler.h"
#include "device.h"

constexpr uint32_t PWM_MAX = 4095; // ajuste ao seu timer

void handle_command(const uint8_t* f)
{
    uint8_t  type    = f[0];
    uint8_t  channel = f[1];
    uint16_t value   = (f[2] << 8) | f[3];
    // uint8_t time  = f[4]; // ainda não usado

    switch (type) {

    // ================= DIGITAL =================
    case 0x50: {
        uint32_t duty = (value != 0) ? PWM_MAX : 0;

        if (channel == 0) Led0::setDuty(duty);
        if (channel == 1) Led1::setDuty(duty);
        if (channel == 2) Led2::setDuty(duty);
        if (channel == 3) Led3::setDuty(duty);
        break;
    }

    // ================= ANALÓGICO =================
    case 0x20:
        if (channel == 0) Led0::setDuty(value);
        if (channel == 1) Led1::setDuty(value);
        if (channel == 2) Led2::setDuty(value);
        if (channel == 3) Led3::setDuty(value);
        break;

    case 0x51: // buzzer
        gpio_set_level(BoardPins::BUZZER, value ? 1 : 0);
        break;


    default:
        // comando inválido → ignore
        break;
    }
}
