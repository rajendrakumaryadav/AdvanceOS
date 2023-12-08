#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
  printf("Alarm fired! Received signal: %d\n", signum);
}

int main() {
  int child_pid = fork();

  if (child_pid == 0) { // Child process
    printf("Child process: Sleeping for 5 seconds...\n");
    sleep(5);
    // Send SIGALRM to parent process
    kill(getppid(), SIGALRM);
  } else if (child_pid > 0) { // Parent process
    // Set signal handler for SIGALRM
    signal(SIGALRM, alarm_handler);

    printf("Parent process: Waiting for alarm...\n");
    // Wait for SIGALRM signal
    pause();
  } else {
    perror("Fork error");
    return 1;
  }

  return 0;
}
