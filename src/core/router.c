#include "router.h"
#include <string.h>

HttpResponse route_request(HttpRequest* req) {
    HttpResponse response;

    if (strcmp(req->path, "/") == 0) {
        response.status = "200 OK";
        response.content_type = "text/html";
        response.body = "<h1>Welcome to Hydra Server</h1>";
    } else if (strcmp(req->path, "/hello") == 0) {
        response.status = "200 OK";
        response.content_type = "text/plain";
        response.body = "Hello from the server!";
    } else {
        response.status = "404 Not Found";
        response.content_type = "text/html";
        response.body = "<h1>404 - Not Found</h1>";
    }

    return response;
}