#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

void handle_request(int client_fd) {
    const char *response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"  // Specify the content type
        "Connection: close\r\n"
        "\r\n"  // End of headers
        "Hello, Server!\r\n";  // Response body

    // Send the response
    send(client_fd, response, strlen(response), 0);

    // Close the connection
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
