// udp_server.cpp
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include <cstring>

extern "C" {
#include "esp_log.h"
}

#define DISCOVERY_PORT 25205
#define DISCOVERY_RESPONSE "SCENARIO_ESP32"

static const char* TAG = "UDP";

void udp_server_task(void*)
{
    ESP_LOGI(TAG, "UDP task started");

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock < 0) {
        ESP_LOGE(TAG, "Failed to create socket");
        vTaskDelete(nullptr);
        return;
    }

    ESP_LOGI(TAG, "Socket created: %d", sock);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(DISCOVERY_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int err = bind(sock, (sockaddr*)&addr, sizeof(addr));
    if (err < 0) {
        ESP_LOGE(TAG, "Socket bind failed");
        close(sock);
        vTaskDelete(nullptr);
        return;
    }

    ESP_LOGI(TAG, "UDP listening on port %d", DISCOVERY_PORT);

    uint8_t rx[32];
    sockaddr_in from{};
    socklen_t fromlen = sizeof(from);

    while (true) {
        int len = recvfrom(sock,
                           rx,
                           sizeof(rx),
                           0,
                           (sockaddr*)&from,
                           &fromlen);

        if (len > 0) {
            ESP_LOGI(TAG,
                     "Discovery packet from %s:%d (%d bytes)",
                     inet_ntoa(from.sin_addr),
                     ntohs(from.sin_port),
                     len);

            sendto(sock,
                   DISCOVERY_RESPONSE,
                   strlen(DISCOVERY_RESPONSE),
                   0,
                   (sockaddr*)&from,
                   fromlen);
        }
    }
}
