#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

#define QUEUE_NAME "/my_task_queue"


int main(int argc, char *argv[]) {
if (argc < 3) {
printf("Usage: %s <priority> <task_description>\n", argv[0]);
return 1;
}


int priority = atoi(argv[1]);
const char *task = argv[2];


mqd_t mq = mq_open(QUEUE_NAME, O_WRONLY);
if (mq == (mqd_t)-1) {
perror("mq_open");
return 1;
}


if (mq_send(mq, task, strlen(task) + 1, priority) == -1) {
perror("mq_send");
mq_close(mq);
return 1;
}


printf("Dispatched task with priority %d: %s\n", priority, task);
mq_close(mq);
return 0;
}