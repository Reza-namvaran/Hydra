#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 4096

int send_request_and_check(const char *path, const char *expected_substring) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int match = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return 0;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 0;
    }

    char request[1024];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: localhost\r\n"
             "Connection: close\r\n"
             "\r\n", path);

    send(sock, request, strlen(request), 0);

    int bytes_read;
    while ((bytes_read = read(sock, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        if (strstr(buffer, expected_substring)) {
            match = 1;
        }
    }

    close(sock);
    return match;
}

int main() {
    struct {
        const char *path;
        const char *expected;
        const char *description;
    } tests[] = {
        {"/", "<h1>Welcome to Hydra Server</h1>", "Root Path (/)" },
        {"/hello", "Hello from the server!", "Hello Path (/hello)" },
        {"/not_exist", "404", "Nonexistent Path (/not_exist)" },
        {NULL, NULL, NULL}
    };

    int passed = 0, total = 0;

    for (int i = 0; tests[i].path != NULL; ++i) {
        total++;
        printf("Test %d: %s ... ", i + 1, tests[i].description);
        int result = send_request_and_check(tests[i].path, tests[i].expected);
        if (result) {
            printf("PASS\n");
            passed++;
        } else {
            printf("FAIL\n");
        }
    }

    printf("\n%d/%d tests passed.\n", passed, total);
    return (passed == total) ? EXIT_SUCCESS : EXIT_FAILURE;
}