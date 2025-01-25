#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>

#define PORT 8080
#define BUFFER_SIZE 2048

void handle_request(int client_fd);

void start_server();

#endif // !SERVER_H