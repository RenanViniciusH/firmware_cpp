
#include <cstring>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
}
#include "led.h"
#include "driver/gpio.h"
#include "driver/ledc.h"

#include "boards_pins.h"
#include "device.h"

void pwm_timer_init();
void tcp_server_task(void *arg);
void udp_server_task(void *arg);
void wifi_init();

extern "C" void app_main(void)
{
    Led0::init();
    Led1::init();
    Led2::init();
    Led3::init();

    Buzzer::init();

    led_init(GPIO_NUM_2);
    led_set_mode(LedMode::BLINK_FAST);

    wifi_init();
    pwm_timer_init();

    xTaskCreate(
        tcp_server_task,
        "tcp_server",
        5000,
        nullptr,
        5,
        nullptr);

    xTaskCreate(
        udp_server_task,
        "udp_server",
        4096,
        nullptr,
        5,
        nullptr);





}
