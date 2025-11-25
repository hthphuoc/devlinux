#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr, client;
    socklen_t len = sizeof(client);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8081);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    char buffer[100];
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&client, &len);

    buffer[n] = '\0';
    printf("UDP Received: %s\n", buffer);

    close(sockfd);
    return 0;
}
