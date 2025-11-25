#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "unix_stream.sock"

int main() {
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {0};

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    char *msg = "Hello from client";
    write(sockfd, msg, strlen(msg));

    close(sockfd);
    return 0;
}
