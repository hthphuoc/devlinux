#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    struct stat filestat;

    if (lstat(path, &filestat) < 0) {
        perror("Error reading file info");
        return 1;
    }

    printf("File Path: %s\n", path);

    printf("File Type: ");
    if (S_ISREG(filestat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(filestat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(filestat.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }

    printf("Size: %ld bytes\n", filestat.st_size);

    printf("Last Modified: %s\n", ctime(&filestat.st_mtime));

    return 0;
}
