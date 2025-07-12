#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "request.h"
#include "router.h"
#include "response.h"

void handle_request(int client_fd) {
    char buffer[4096];
    int received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (received <= 0) {
        close(client_fd);
        return;
    }
    buffer[received] = '\0';

    HttpRequest req;
    if (parse_http_request(buffer, received, &req) == 0) {
        HttpResponse res = route_request(&req);
        send_http_response(client_fd, &res);
    } else {
        const char *error_response = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n";
        send(client_fd, error_response, strlen(error_response), 0);
    }

    close(client_fd);
}

void start_server() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket fail");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address, &addr_len)) == -1) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

}
