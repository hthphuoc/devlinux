#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    setenv("MY_COMMAND", "ls -l", 1);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());

        char *cmd = getenv("MY_COMMAND");

        if (cmd == NULL) {
            fprintf(stderr, "No MY_COMMAND found in environment!\n");
            exit(1);
        }

        printf("Executing command: %s\n\n", cmd);

        execlp(cmd, cmd, NULL);

        perror("execlp failed");
        exit(1);
    } 
    else {
        int status;
        wait(&status);
        printf("\nParent process: Child has finished.\n");

        if (WIFEXITED(status)) {
            printf("Child exited with code %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
