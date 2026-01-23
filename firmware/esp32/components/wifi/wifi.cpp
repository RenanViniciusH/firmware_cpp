#include "wifi.h"
#include "led.h"


extern "C" {
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_log.h"
}

#include <cstring>

static const char* TAG = "WIFI";

/* ===================== EVENT HANDLER ===================== */

static void wifi_event_handler(void* arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void* event_data)
{
    if (event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_STA_START)
    {
        ESP_LOGI(TAG, "WiFi started");
        led_set_mode(LedMode::BLINK_SLOW);   // conectando
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT &&
             event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        wifi_event_sta_disconnected_t* dis =
            (wifi_event_sta_disconnected_t*) event_data;

        ESP_LOGW(TAG, "Disconnected, reason=%d", dis->reason);

        led_set_mode(LedMode::BLINK_ERROR);  // erro
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_wifi_connect();
    }
    else if (event_base == IP_EVENT &&
             event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event =
            (ip_event_got_ip_t*) event_data;

        ESP_LOGI(TAG, "Connected! IP: " IPSTR,
                 IP2STR(&event->ip_info.ip));

        led_set_mode(LedMode::ON); // conectado
    }
}

/* ===================== WIFI INIT ===================== */

void wifi_init()
{
    /* LED init (status visual) */
    led_init(GPIO_NUM_2);              // MUDE para seu pino real
    led_set_mode(LedMode::BLINK_FAST); // boot

    /* NVS */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    /* TCP/IP + Event loop */
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    /* Event handlers */
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            nullptr,
            nullptr
            )
        );

    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            IP_EVENT,
            IP_EVENT_STA_GOT_IP,
            &wifi_event_handler,
            nullptr,
            nullptr
            )
        );

    /* WiFi init */
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config{};
    strcpy((char*)wifi_config.sta.ssid, "SensisDev");
    strcpy((char*)wifi_config.sta.password, "Sd6739753");

    wifi_config.sta.threshold.authmode = WIFI_AUTH_WPA2_PSK;
    wifi_config.sta.pmf_cfg.capable = true;
    wifi_config.sta.pmf_cfg.required = false;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}
