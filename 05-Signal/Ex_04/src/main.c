#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/select.h>

volatile sig_atomic_t sigint_flag = 0;
volatile sig_atomic_t sigterm_flag = 0;

void sig_handler(int signo) {
    if (signo == SIGINT) {
        sigint_flag = 1;
    } else if (signo == SIGTERM) {
        sigterm_flag = 1;
    }
}

int main() {
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    printf("Program running. Type something or press Ctrl+C.\n");

    char buffer[256];

    while (1) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

        if (sigint_flag) {
            printf("SIGINT received.\n");
            sigint_flag = 0;
        }

        if (sigterm_flag) {
            printf("SIGTERM received. Exiting...\n");
            exit(0);
        }

        if (ret > 0 && FD_ISSET(STDIN_FILENO, &readfds)) {
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                printf("You typed: %s", buffer);
            }
        }
    }

    return 0;
}
