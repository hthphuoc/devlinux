#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {

        close(pipefd[0]);

        // Chuyển hướng stdout -> pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Đóng đầu ghi sau khi dup2
        close(pipefd[1]);

        // Thực thi ls -l
        execlp("ls", "ls", "-l", NULL);

        // Nếu execlp thất bại:
        perror("execlp ls");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {

        close(pipefd[1]);

        // Chuyển hướng stdin -> pipe
        dup2(pipefd[0], STDIN_FILENO);

        // Đóng đầu đọc sau khi dup2
        close(pipefd[0]);

        // Thực thi wc -l
        execlp("wc", "wc", "-l", NULL);

        // Nếu execlp thất bại:
        perror("execlp wc");
        exit(1);
    }


    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
