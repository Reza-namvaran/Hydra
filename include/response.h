#ifndef RESPONSE_H
#define RESPONSE_H

#include "router.h"
#include <sys/socket.h>

void send_http_response(int client_fd, HttpResponse *res);

#endif
