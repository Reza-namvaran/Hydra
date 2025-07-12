#ifndef REQUEST_H
#define REQUEST_H

#define METHOD_SIZE 8
#define PATH_SIZE 1024
#define VERSION_SIZE 16

typedef struct {
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    char version[VERSION_SIZE];
    char* body;
    int content_len;

} HttpRequest;

int parse_http_request(char* buffer, int size, HttpRequest *req);

#endif