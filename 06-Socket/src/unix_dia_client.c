#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SOCK "unix_dgram_server.sock"
#define CLIENT_SOCK "unix_dgram_client.sock"

int main() {
    int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    struct sockaddr_un server = {0}, client = {0};

    client.sun_family = AF_UNIX;
    strcpy(client.sun_path, CLIENT_SOCK);
    unlink(CLIENT_SOCK);
    bind(sockfd, (struct sockaddr*)&client, sizeof(client));

    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, SERVER_SOCK);

    char *msg = "Hello from client";
    sendto(sockfd, msg, strlen(msg), 0,
           (struct sockaddr*)&server, sizeof(server));

    close(sockfd);
    unlink(CLIENT_SOCK);
    return 0;
}
