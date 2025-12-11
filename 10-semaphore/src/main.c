#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define SIZE 4096 // typically a page size
#define TRAY_SIZE 10

/* item codes */
#define EMPTY_SLOT 0
#define VEG 1
#define NONVEG 2

const char *donatello_items[2] = { "Fettuccine Chicken Alfredo", "Garlic Sirloin Steak" }; // non-veg
const char *portecelli_items[2] = { "Pistachio Pesto Pasta", "Avocado Fruit Salad" };     // vegan

/* Shared memory layout */
typedef struct {
    /* tray buffers (circular) */
    int nonveg_buf[TRAY_SIZE];
    int nonveg_in;
    int nonveg_out;
    int nonveg_count;

    int veg_buf[TRAY_SIZE];
    int veg_in;
    int veg_out;
    int veg_count;

    /* semaphores for nonveg tray */
    sem_t nonveg_mutex;
    sem_t nonveg_empty; // counts empty slots
    sem_t nonveg_full;  // counts filled slots

    /* semaphores for veg tray */
    sem_t veg_mutex;
    sem_t veg_empty;
    sem_t veg_full;
} shared_t;

static shared_t *shm = NULL;
static pid_t children[5];
static int child_count = 0;

int init_shared() {
    shm = mmap(NULL, sizeof(shared_t), PROT_READ | PROT_WRITE,
               MAP_ANONYMOUS | MAP_SHARED, -1, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
        return -1;
    }
	
	for (int i = 0; i < TRAY_SIZE; i++) {
        shm->nonveg_buf[i] = EMPTY_SLOT;
        shm->veg_buf[i] = EMPTY_SLOT;
    }
    shm->nonveg_in = shm->nonveg_out = shm->nonveg_count = 0;
    shm->veg_in = shm->veg_out = shm->veg_count = 0;

    /* initialize semaphores: pshared = 1 (shared between processes) */
    if (sem_init(&shm->nonveg_mutex, 1, 1) == -1) { perror("sem_init nonveg_mutex"); return -1; }
    if (sem_init(&shm->nonveg_empty, 1, TRAY_SIZE) == -1) { perror("sem_init nonveg_empty"); return -1; }
    if (sem_init(&shm->nonveg_full, 1, 0) == -1) { perror("sem_init nonveg_full"); return -1; }

    if (sem_init(&shm->veg_mutex, 1, 1) == -1) { perror("sem_init veg_mutex"); return -1; }
    if (sem_init(&shm->veg_empty, 1, TRAY_SIZE) == -1) { perror("sem_init veg_empty"); return -1; }
    if (sem_init(&shm->veg_full, 1, 0) == -1) { perror("sem_init veg_full"); return -1; }

    return 0;
}

void destroy_shared() {
    if (!shm) return;
    sem_destroy(&shm->nonveg_mutex);
    sem_destroy(&shm->nonveg_empty);
    sem_destroy(&shm->nonveg_full);

    sem_destroy(&shm->veg_mutex);
    sem_destroy(&shm->veg_empty);
    sem_destroy(&shm->veg_full);

    munmap(shm, sizeof(shared_t));
    shm = NULL;
}

int rand_between(int a, int b) {
    return a + rand() % (b - a + 1);
}

/* Producer: non-veg chef Donatello */
void chef_nonveg_loop() {
    pid_t pid = getpid();
    srand(time(NULL) ^ (pid << 16));

    while (1) {
        /* pick random dish */
        int idx = rand_between(0,1);
        const char *dish = donatello_items[idx];

        /* wait for empty slot */
        sem_wait(&shm->nonveg_empty);
        sem_wait(&shm->nonveg_mutex);

        /* add dish */
        int pos = shm->nonveg_in;
        shm->nonveg_buf[pos] = NONVEG;
        shm->nonveg_in = (shm->nonveg_in + 1) % TRAY_SIZE;
        shm->nonveg_count++;
        printf("[Chef Donatello (pid %d)] Placed non-veg: %s. Tray non-veg now: %d/%d\n",
               pid, dish, shm->nonveg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->nonveg_mutex);
        sem_post(&shm->nonveg_full);

        /* sleep 1-5 seconds before next dish */
        sleep(rand_between(1,5));
    }
}

/* Producer: veg chef Portecelli */
void chef_veg_loop() {
    pid_t pid = getpid();
    srand(time(NULL) ^ (pid << 16));

    while (1) {
        int idx = rand_between(0,1);
        const char *dish = portecelli_items[idx];

        sem_wait(&shm->veg_empty);
        sem_wait(&shm->veg_mutex);

        int pos = shm->veg_in;
        shm->veg_buf[pos] = VEG;
        shm->veg_in = (shm->veg_in + 1) % TRAY_SIZE;
        shm->veg_count++;
        printf("[Chef Portecelli (pid %d)] Placed vegan: %s. Tray vegan now: %d/%d\n",
               pid, dish, shm->veg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->veg_mutex);
        sem_post(&shm->veg_full);

        sleep(rand_between(1,5));
    }
}

/* Consumer: customer 1 (non-vegan only) */
void customer_nonveg_loop() {
    pid_t pid = getpid();
    srand(time(NULL) ^ (pid << 16));

    while (1) {
        /* wait until there's at least one nonveg */
        sem_wait(&shm->nonveg_full);
        sem_wait(&shm->nonveg_mutex);

        /* take dish from tray */
        int pos = shm->nonveg_out;
        int code = shm->nonveg_buf[pos];
        shm->nonveg_buf[pos] = EMPTY_SLOT;
        shm->nonveg_out = (shm->nonveg_out + 1) % TRAY_SIZE;
        if (shm->nonveg_count > 0) shm->nonveg_count--;
        printf("[Customer NonVeg (pid %d)] Took NON-VEG dish (code %d). Tray non-veg now: %d/%d\n",
               pid, code, shm->nonveg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->nonveg_mutex);
        sem_post(&shm->nonveg_empty);

        /* eat: wait 10-15 sec before trying next */
        sleep(rand_between(10,15));
    }
}

/* Consumer: customer 2 (vegan only) */
void customer_veg_loop() {
    pid_t pid = getpid();
    srand(time(NULL) ^ (pid << 16));

    while (1) {
        sem_wait(&shm->veg_full);
        sem_wait(&shm->veg_mutex);

        int pos = shm->veg_out;
        int code = shm->veg_buf[pos];
        shm->veg_buf[pos] = EMPTY_SLOT;
        shm->veg_out = (shm->veg_out + 1) % TRAY_SIZE;
        if (shm->veg_count > 0) shm->veg_count--;
        printf("[Customer Veg (pid %d)] Took VEG dish (code %d). Tray vegan now: %d/%d\n",
               pid, code, shm->veg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->veg_mutex);
        sem_post(&shm->veg_empty);

        sleep(rand_between(10,15));
    }
}

/* Consumer: customer 3 (hybrid) - wants one vegan and one non-vegan per cycle */
void customer_hybrid_loop() {
    pid_t pid = getpid();
    srand(time(NULL) ^ (pid << 16));

    while (1) {
        /* First take vegan */
        sem_wait(&shm->veg_full);
        sem_wait(&shm->veg_mutex);

        int posv = shm->veg_out;
        int codev = shm->veg_buf[posv];
        shm->veg_buf[posv] = EMPTY_SLOT;
        shm->veg_out = (shm->veg_out + 1) % TRAY_SIZE;
        if (shm->veg_count > 0) shm->veg_count--;
        printf("[Customer Hybrid (pid %d)] Took VEG dish (code %d). Tray vegan now: %d/%d\n",
               pid, codev, shm->veg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->veg_mutex);
        sem_post(&shm->veg_empty);

        /* Then take non-veg */
        sem_wait(&shm->nonveg_full);
        sem_wait(&shm->nonveg_mutex);

        int posn = shm->nonveg_out;
        int coden = shm->nonveg_buf[posn];
        shm->nonveg_buf[posn] = EMPTY_SLOT;
        shm->nonveg_out = (shm->nonveg_out + 1) % TRAY_SIZE;
        if (shm->nonveg_count > 0) shm->nonveg_count--;
        printf("[Customer Hybrid (pid %d)] Took NON-VEG dish (code %d). Tray non-veg now: %d/%d\n",
               pid, coden, shm->nonveg_count, TRAY_SIZE);
        fflush(stdout);

        sem_post(&shm->nonveg_mutex);
        sem_post(&shm->nonveg_empty);

        /* After getting both, wait 10-15 seconds */
        sleep(rand_between(10,15));
    }
}

/* Parent prints status every 10 seconds */
void parent_status_loop() {
    while (1) {
        sleep(10);
        if (shm) {
            int nv_count, v_count;
            /* Access counts safely by acquiring mutex briefly */
            sem_wait(&shm->nonveg_mutex);
            nv_count = shm->nonveg_count;
            sem_post(&shm->nonveg_mutex);

            sem_wait(&shm->veg_mutex);
            v_count = shm->veg_count;
            sem_post(&shm->veg_mutex);

            printf("[Parent] Items in non-vegan tray: %d/%d, Items in vegan tray: %d/%d\n",
                   nv_count, TRAY_SIZE, v_count, TRAY_SIZE);
            fflush(stdout);
        }
    }
}

/* Signal handler: cleanup (kill children, destroy shared) */
void cleanup_and_exit(int sig) {
    (void)sig;
    printf("\n[Parent] SIGINT received. Cleaning up: killing children and releasing resources...\n");

    /* kill children */
    for (int i = 0; i < child_count; i++) {
        if (children[i] > 0) {
            kill(children[i], SIGTERM);
        }
    }

    /* wait for children to terminate */
    for (int i = 0; i < child_count; i++) {
        if (children[i] > 0) {
            waitpid(children[i], NULL, 0);
        }
    }

    /* destroy semaphores and unmap */
    destroy_shared();

    printf("[Parent] Cleanup done. Exiting.\n");
    exit(0);
}

int main(void) {
    printf("Starting restaurant simulation...\n");

    if (init_shared() != 0) {
        fprintf(stderr, "Failed to init shared memory/semaphores\n");
        exit(1);
    }

    /* install SIGINT handler in parent to cleanup */
    struct sigaction act;
    act.sa_handler = cleanup_and_exit;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);

    /* spawn children: order: chef_nonveg, chef_veg, cust_nonveg, cust_veg, cust_hybrid */
    pid_t pid;
    int idx = 0;

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { chef_nonveg_loop(); exit(0); }
    children[idx++] = pid;

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { chef_veg_loop(); exit(0); }
    children[idx++] = pid;

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { customer_nonveg_loop(); exit(0); }
    children[idx++] = pid;

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { customer_veg_loop(); exit(0); }
    children[idx++] = pid;

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) { customer_hybrid_loop(); exit(0); }
    children[idx++] = pid;

    child_count = idx;

    /* Parent status loop (prints every 10 sec) - run in main thread */
    parent_status_loop();

    /* never reached */
    return 0;
}
