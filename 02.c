#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SIZE 255

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s \"<Text Here>\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int fd[2];  // fd[0] - reading end of pipe | fd[1] - writing end of pipe
    char buf[MAX_SIZE];
    if (pipe(fd) == -1) {  // unnamed pipe |  named used mkfifo()
        perror("Failed to create pipe ");
        exit(1);
    }
    switch (fork()) {
        case -1:
            perror("Failure on creating a process");
            break;
        case 0:
            close(fd[0]);  // Close read end of pipe
            if (write(fd[1], argv[1], MAX_SIZE) == -1) {
                perror("Writting to pipe error.");
                exit(1);
            }
            break;
        default:
            close(fd[1]);  // Close write end of pipe
            if (read(fd[0], buf, MAX_SIZE) == -1) {
                perror("Reading from pipe error  ");
                exit(1);
            }
            printf("Data from the pipe : %s\n", buf);
            break;
    }
    exit(EXIT_SUCCESS);
}