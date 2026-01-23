// tcp_server.cpp
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "command_handler.h"

#define TCP_PORT 50000
#define FRAME_SIZE 5

void tcp_server_task(void*)
{
    int listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(TCP_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listen_sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        close(listen_sock);
        vTaskDelete(nullptr);
    }

    if (listen(listen_sock, 1) < 0) {
        close(listen_sock);
        vTaskDelete(nullptr);
    }


    while (true) {
        int client = accept(listen_sock, nullptr, nullptr);
        if (client < 0) continue;

        uint8_t frame[FRAME_SIZE];
        int received = 0;

        while (true) {
            int len = recv(client, frame + received,
                           FRAME_SIZE - received, 0);

            if (len <= 0) break;

            received += len;

            if (received == FRAME_SIZE) {
                handle_command(frame);
                received = 0; // pronto para próximo frame
            }
        }

        close(client);
    }
}
