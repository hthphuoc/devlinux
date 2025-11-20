#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int counter = 0;

void alarm_handler(int signum) {
    counter++;
    printf("Timer: %d seconds\n", counter);

    if (counter >= 10) {
        printf("Finished after 10 seconds. Exiting...\n");
        exit(0);
    }

    alarm(1);
}

int main() {

    signal(SIGALRM, alarm_handler
	alarm(1);

    while (1);

    return 0;
}