#include <stdio.h>
#include <pthread.h>

#define COUNT_VAL 1000000

long long counter = 0;
pthread_mutex_t lock;

void* increase_counter(void* arg) {
    for (int i = 0; i < COUNT_VAL; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t tid[3];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, increase_counter, NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Giá trị cuối cùng của counter = %lld\n", counter);
    return 0;
}
