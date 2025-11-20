#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int sigint_count = 0;

void sigint_handler(int signum) {
    sigint_count++;
    printf("SIGINT received (%d/3)\n", sigint_count);

    if (sigint_count >= 3) {
        printf("Received SIGINT 3 times. Exiting...\n");
        exit(0);
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    printf("Chương trình đang chạy. Nhấn Ctrl+C...\n");

    while (1);

    return 0;
}
