#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "unix_stream.sock"

int main() {
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    struct sockaddr_un addr = {0};

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);
    unlink(SOCK_PATH);

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 1);

    printf("Unix Stream Server listening...\n");
    int client = accept(sockfd, NULL, NULL);

    char buffer[100];
    int n = read(client, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    close(client);
    close(sockfd);
    unlink(SOCK_PATH);
    return 0;
}
