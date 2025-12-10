#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

#define QUEUE_NAME "/my_task_queue"
#define MAX_MSG_SIZE 256

mqd_t mq;

void cleanup_and_exit(int sig) {
    printf("\nSIGINT received. Cleaning up...\n");

    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    printf("Message queue closed and unlinked. Exiting.\n");
    exit(0);
}

int main() {

    signal(SIGINT, cleanup_and_exit);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    printf("task_worker is running...\n");
    printf("Listening for tasks from queue: %s\n", QUEUE_NAME);

    char buffer[MAX_MSG_SIZE];
    unsigned int prio;

    while (1) {
        sleep(10);
        ssize_t bytes = mq_receive(mq, buffer, MAX_MSG_SIZE, &prio);
        if (bytes < 0) {
            perror("mq_receive");
            continue;
        }

        buffer[bytes] = '\0';

        printf("Processing task (Priority: %u): %s\n", prio, buffer);
    }

    return 0;
}
