#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>
#include <unistd.h>

void sighup_handler(int sig) {
  printf("Child process received SIGHUP signal\n");
}

void sigint_handler(int sig) {
  printf("Child process received SIGINT signal\n");
}

void sigquit_handler(int sig) {
  printf("My Papa has Killed me!!!\n");
  exit(0);
}

int main() {
  int pid = fork();

  if (pid == 0) { // Child process
    // Set signal handlers
    signal(SIGHUP, sighup_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    // Infinite loop
    while (1) {
      sleep(1);
    }
  } else if (pid > 0) { // Parent process
    int i;
    for (i = 0; i < 5; i++) {
      sleep(3);
      // Send SIGHUP or SIGINT randomly
      if (rand() % 2 == 0) {
        kill(pid, SIGHUP);
      } else {
        kill(pid, SIGINT);
      }
    }
    sleep(3);
    kill(pid, SIGQUIT);
    wait(NULL);
  } else { // Fork error
    perror("Fork error");
    return 1;
  }

  return 0;
}
