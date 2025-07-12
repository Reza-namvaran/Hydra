#include "request.h"

#include <stdio.h>
#include <string.h>


int parse_http_request(char* buffer, int size, HttpRequest *req) {
    if (!buffer || size <= 0 || !req) {
        return -1;
    }

    if (buffer[size - 1] != '\0') {
        if (size < 4096) {
            buffer[size] = '\0';
        }
    }

    int ret = sscanf(buffer, "%7s %1023s %15s", req->method, req->path, req->version);
    if (ret != 3) {
        return -1;
    }

    char *headers_end = strstr(buffer, "\r\n\r\n");
    if (!headers_end) {
        return -1;
    }

    req->content_len = 0;

    char *c_len = strstr(buffer, "Content-Length:");
    if (c_len && c_len < headers_end) {
        sscanf(c_len, "Content-Length: %d", &req->content_len);
    }
    return 0;
}