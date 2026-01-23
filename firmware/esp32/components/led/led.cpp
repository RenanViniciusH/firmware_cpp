#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static gpio_num_t led_pin;
static LedMode current_mode = LedMode::OFF;

static void led_task(void* arg) {
    while (true) {
        switch (current_mode) {
        case LedMode::ON: gpio_set_level(led_pin, 1); vTaskDelay(pdMS_TO_TICKS(1000)); break;
        case LedMode::OFF: gpio_set_level(led_pin, 0); vTaskDelay(pdMS_TO_TICKS(1000)); break;
        case LedMode::BLINK_FAST: gpio_set_level(led_pin, 1); vTaskDelay(pdMS_TO_TICKS(200)); gpio_set_level(led_pin, 0); vTaskDelay(pdMS_TO_TICKS(200)); break;
        case LedMode::BLINK_SLOW: gpio_set_level(led_pin, 1); vTaskDelay(pdMS_TO_TICKS(800)); gpio_set_level(led_pin, 0); vTaskDelay(pdMS_TO_TICKS(800)); break;
        case LedMode::BLINK_ERROR: gpio_set_level(led_pin, 1); vTaskDelay(pdMS_TO_TICKS(100)); gpio_set_level(led_pin, 0); vTaskDelay(pdMS_TO_TICKS(100)); break;
        }
    }
}

void led_init(gpio_num_t pin) {
    led_pin = pin;
    gpio_config_t cfg{};
    cfg.pin_bit_mask = 1ULL << pin;
    cfg.mode = GPIO_MODE_OUTPUT;
    cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
    cfg.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&cfg);

    xTaskCreate(led_task, "led_task", 2048, nullptr, 1, nullptr);
}

void led_set_mode(LedMode mode) {
    current_mode = mode;
}
