#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 1);

    printf("TCP Server listening...\n");
    int client = accept(sockfd, NULL, NULL);

    char buffer[100];
    int n = read(client, buffer, sizeof(buffer));
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);

    close(client);
    close(sockfd);
    return 0;
}
