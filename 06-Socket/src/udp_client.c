#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8081);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    char *msg = "Hello from client";
    sendto(sockfd, msg, strlen(msg), 0,
           (struct sockaddr*)&addr, sizeof(addr));

    close(sockfd);
    return 0;
}
