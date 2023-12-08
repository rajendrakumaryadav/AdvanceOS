// Create a file with hole in it.
// Created by Rajendra Kumar R Yadav

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#define MAX_PATH_LENGTH 300
int create_sparse_file(char *, uint64_t);
int main()
{
    char filename[MAX_PATH_LENGTH];
    uint64_t size;
    long long unsigned int size_in_mb;
    printf("Enter the file Path : ");
    scanf("%s", filename);
    // By default it is Bytes
    printf("Enter Size (IN MB) : ");
    scanf("%lu", &size);
    size_in_mb = size * 1024 * 1024;
    printf("Creating a sparse file of size %lld.\n", size_in_mb);
    if (create_sparse_file(filename, size_in_mb) == 0)
    {
        printf("Hole file is created!\n");
    }
    else {
        perror("Error ");
    }
    return 0;
}

int create_sparse_file(char *path, uint64_t size)
{
    int fd = 0;
    fd     = open(path, O_RDWR | O_CREAT, 0666);
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