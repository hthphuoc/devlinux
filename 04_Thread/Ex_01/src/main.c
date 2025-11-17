#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_func() {
    pthread_t tid = pthread_self();

    printf("Thread với ID %lu đang chạy!\n", tid);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
