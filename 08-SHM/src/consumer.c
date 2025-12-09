#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define SHM_NAME "/my_shared_mem"

typedef struct {
    int id;
    char name[50];
    float price;
} Product;

int main() {

    int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    Product *p = mmap(NULL, sizeof(Product),
                      PROT_READ, MAP_SHARED,
                      shm_fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Consumer: Product info:\n");
    printf("  ID: %d\n", p->id);
    printf("  Name: %s\n", p->name);
    printf("  Price: %.2f\n", p->price);

    shm_unlink(SHM_NAME);

    close(shm_fd);
    return 0;
}
