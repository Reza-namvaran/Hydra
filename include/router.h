#ifndef ROUTER_H
#define ROUTER_H

#include "request.h"

typedef struct {
    const char *status;
    const char *content_type;
    const char *body;
} HttpResponse;

HttpResponse route_request(HttpRequest* req);

#endif