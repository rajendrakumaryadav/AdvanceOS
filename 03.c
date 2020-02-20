#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistdio.h>
int create_sparse_file(char *, uint64_t);
int main() {
    char *filename;
    uint64_t size;
    printf("Enter the file Path : ");
    scanf("%s", filename);
    printf("Enter Size : ");
    scanf("%llu", &size);

    if (create_sparse_file(filename, size) == 0) {
        printf("Hole file is created!\n");
    } else {
        perror("Error ");
    }
    return 0;
}

int create_sparse_file(char *path, uint64_t size) {
    int fd = 0;
    fd = open(path, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        return -1;
    }
    if (lseek(fd, size - 1, SEEK_CUR) == -1) {
        return -1;
    }
    write(fd, "\0", 1);
    close(fd);
    return 0;
}