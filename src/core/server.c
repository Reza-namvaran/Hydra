#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"
#include "request.h"

void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    int received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
    if (received <= 0) {
        close(client_fd);
        return;
    }
    buffer[received] = '\0';

    HttpRequest req;
    if (parse_http_request(buffer, received, &req) == 0) {
        printf("Method: %s\nPath: %s\nVersion: %s\nContent-Length: %d\n", req.method, req.path, req.version, req.content_len);
        if (req.content_len > 0) {
            printf("Body: %.*s\n", req.content_len, req.body);
        }
        /// TODO: route request and send response here
    } else {
        const char *bad_req = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\n";
        send(client_fd, bad_req, strlen(bad_req), 0);
    }

    close(client_fd);
}

void start_server() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    socklen_t addr_len = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket fail");
        exit(EXIT_FAILURE);
    }

    // Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listening
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Main loop
    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&address, &addr_len)) == -1) {
            perror("accept");
            continue;
        }
        handle_request(client_fd);
    }

}
