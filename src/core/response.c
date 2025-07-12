#include "response.h"
#include <stdio.h>
#include <string.h>

void send_http_response(int client_fd, HttpResponse *res) {
    char header[1024];

    int body_length = strlen(res->body);

    snprintf(header, sizeof(header),
             "HTTP/1.1 %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %d\r\n"
             "Connection: close\r\n"
             "\r\n",
             res->status, res->content_type, body_length);

    send(client_fd, header, strlen(header), 0);
    send(client_fd, res->body, body_length, 0);
}
