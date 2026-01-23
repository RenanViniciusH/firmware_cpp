idf_component_register(
    SRCS
        "main.cpp"
        "command_handler.cpp"
        "components/wifi/wifi.cpp"
        "components/tcp/tcp_server.cpp"
        "components/udp/udp_server.cpp"
        "components/pwm/pwm_timer.cpp"
        "components/led/led.cpp"
    INCLUDE_DIRS
        "."
        "components/wifi"
        "components/tcp"
        "components/udp"
        "components/pwm"
        "components/led"
        "hardware"
    REQUIRES
        esp_driver_gpio     # <- adicionado
        esp_driver_ledc     # se você usa PWM via LEDC
        esp_wifi
        esp_netif
        nvs_flash
        lwip
)
