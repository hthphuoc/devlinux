#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        exit(10);
    } 
    else {
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exited with code = %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit normally.\n");
        }
    }

    return 0;
}
