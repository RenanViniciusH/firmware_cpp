cmake_minimum_required(VERSION 3.16)

project(firmware LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(central
    firmware/esp32/main.cpp
    firmware/esp32/command_handler.h firmware/esp32/command_handler.cpp
    firmware/esp32/device.h
    firmware/esp32/components/wifi/wifi.h firmware/esp32/components/wifi/wifi.cpp
    firmware/esp32/components/tcp/tcp_server.h firmware/esp32/components/tcp/tcp_server.cpp
    firmware/esp32/components/udp/udp_server.h firmware/esp32/components/udp/udp_server.cpp
    firmware/esp32/components/pwm/pwm_timer.h firmware/esp32/components/pwm/pwm_timer.cpp

    firmware/esp32/components/led/led.h firmware/esp32/components/led/led.cpp
    firmware/esp32/hardware/buzzer.h
    firmware/esp32/hardware/boards_pins.h
    firmware/esp32/hardware/gpio_base.h
    firmware/esp32/CMakeLists.txt
    firmware/esp32/components/pwm/pwm_led.h

)

