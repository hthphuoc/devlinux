#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_mem"

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    ftruncate(shm_fd, sizeof(Product));

    Product *p = mmap(NULL, sizeof(Product),
                      PROT_READ | PROT_WRITE, MAP_SHARED,
                      shm_fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    p->id = 1;
    strcpy(p->name, "C program book");
    p->price = 200;

    printf("Producer: Written product info to shared memory\n");

    // 5. Giữ chương trình chạy (tùy chọn)
    printf("Producer is done.\n");

    // Không unlink: để consumer đọc được
    close(shm_fd);

    return 0;
}
