#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigusr1_handler(int signum) {
    printf("Child: Received signal from parent\n");
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    // ------------------ CHILD PROCESS ------------------
    if (pid == 0) {
        signal(SIGUSR1, sigusr1_handler);

        while (1);
    }

    // ------------------ PARENT PROCESS ------------------
    else {
        for (int i = 1; i <= 5; i++) {
            sleep(2);
            printf("Parent: Sending SIGUSR1 to child (%d/5)\n", i);
            kill(pid, SIGUSR1);
        }

        printf("Parent: Done sending signals. Exiting...\n");
        exit(0);
    }

    return 0;
}
