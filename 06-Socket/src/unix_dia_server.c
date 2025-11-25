#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SOCK "unix_dgram_server.sock"

int main() {
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un addr = {0};

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_SOCK);
    unlink(SERVER_SOCK);

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    char buffer[100];
    int n = recv(sockfd, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    printf("UNIX DGRAM Received: %s\n", buffer);

    close(sockfd);
    unlink(SERVER_SOCK);
    return 0;
}
