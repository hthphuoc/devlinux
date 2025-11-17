#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rdlock;
pthread_rwlock_t wrlock;

void* reader(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        pthread_rwlock_rdlock(&rdlock);

        printf("[Reader %d] Đọc data = %d\n", id, data);

        pthread_rwlock_unlock(&rdlock);
        usleep(100000);
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 5; i++) {
        pthread_rwlock_wrlock(&wrlock);

        data++;
        printf(">>> [Writer %d] Ghi data = %d\n", id, data);

        pthread_rwlock_unlock(&wrlock);
        usleep(200000);
    }

    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_id[5], writer_id[2];

    pthread_rwlock_init(&rdlock, NULL);
	pthread_rwlock_init(&wrlock, NULL);

    for (int i = 0; i < 5; i++) {
        reader_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    for (int i = 0; i < 2; i++) {
        writer_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }


    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rdlock);
	pthread_rwlock_destroy(&wrlock);

    return 0;
}
