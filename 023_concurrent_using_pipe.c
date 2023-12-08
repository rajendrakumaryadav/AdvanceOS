#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  // Define safe commands
  char *command1 = "/bin/ls";
  char *command2[] = {"wc", "-l", NULL};

  // Validate commands
  if (!command1 || !command2) {
    printf("Invalid command provided.\n");
    return 1;
  }

  // Create a pipe
  int pipefds[2];
  if (pipe(pipefds) == -1) {
    perror("pipe");
    exit(1);
  }

  // Fork a child process
  int pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(1);
  }

  // Child process
  if (pid == 0) {
    // Close the read end of the pipe
    close(pipefds[0]);

    // Duplicate the write end of the pipe to standard output
    dup2(pipefds[1], STDOUT_FILENO);
    close(pipefds[1]);

    // Execute the first command
    if (execv(command1, (char *[]) {command1, "-l", NULL}) == -1) {
      perror("execv");
      exit(1);
    }
  }

  // Parent process
  if (pid > 0) {
    // Close the write end of the pipe
    close(pipefds[1]);

    // Duplicate the read end of the pipe to standard input
    dup2(pipefds[0], STDIN_FILENO);
    close(pipefds[0]);

    // Execute the second command
    if (execvp(command2[0], command2) == -1) {
      perror("execvp");
      exit(1);
    }
  }

  // Wait for the child process to finish
  wait(NULL);

  return 0;
}
