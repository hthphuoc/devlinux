#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/*
 * Chương trình minh họa tiến trình Zombie và Orphan
 */

int main(int argc, char *argv[]) {
    pid_t pid;
	
	if(argc == 1) {
	    printf("Run cmd: ./main Zombie or /main Orphan");
		exit(0);
	}

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (strcmp(argv[1], "Zombie") == 0) {
        if (pid == 0) {
            printf("[Child - Zombie] PID = %d, exiting now...\n", getpid());
            exit(0);
        } else {
            printf("[Parent - Zombie demo] PID = %d, Child PID = %d\n", getpid(), pid);
            printf("Parent is sleeping... (child will become zombie)\n");
            sleep(90);
			wait(NULL);
            printf("Parent ends.\n");
        }
    } else if (strcmp(argv[1], "Orphan") == 0) {
        if (pid == 0) {
            for (int i = 0; i < 5; i++) {
                printf("[Child - Orphan] PID = %d, PPID = %d\n", getpid(), getppid());
                sleep(2);
            }
            printf("Child ends.\n");
        } else {
            printf("[Parent - Orphan] PID = %d, Child PID = %d\n", getpid(), pid);
            printf("Parent exits immediately.\n");
            exit(0);
        }
    } else {
        printf("Invalid choosen!\n");
    }

    return 0;
}
