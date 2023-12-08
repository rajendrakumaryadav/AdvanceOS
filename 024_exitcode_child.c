#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  // Fork a child process
  pid_t child_pid = fork();
  if (child_pid == -1) {
    perror("fork");
    exit(1);
  }

  // Parent process
  if (child_pid > 0) {
    int status;
    // Wait for the child process to finish
    waitpid(child_pid, &status, 0);

    // Check the child's exit status
    if (WIFEXITED(status)) {
      printf("Child exited successfully with status %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
      printf("Child exited abnormally due to signal %d\n", WTERMSIG(status));
    } else {
      printf("Unexpected child termination status: %d\n", status);
    }
  } else { // Child process
    // Sleep for a while to simulate execution
    sleep(1);
    
    // Exit with a status code
    exit(5);
  }

  return 0;
}
