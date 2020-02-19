#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_SIZE 255
int main(int argc, char **argv) {
  int fd[2];  // fd[0] - reading end of pipe | fd[1] - writing end of pipe
  char buf[MAX_SIZE];
  if (pipe(fd) == -1) {
    perror("Failed to create pipe ");
    exit(1);
  }
  switch (fork()) {
    case -1:
      perror("Failure on creating a process");
      break;
    case 0:
      close(fd[0]);
      if (write(fd[1], argv[1], MAX_SIZE) == -1) {
        perror("Writting to pipe error.");
        exit(1);
      }
      break;
    default:
      close(fd[1]);
      if (read(fd[0], buf, MAX_SIZE) == -1) {
        perror("Reading from pipe error  ");
        exit(1);
      }
      printf("Data from the pipe : %s\n", buf);
  }
  exit(EXIT_SUCCESS);
}