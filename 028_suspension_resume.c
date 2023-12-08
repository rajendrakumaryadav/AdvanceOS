#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int is_suspended = 0;

void sigstop_handler(int sig) {
  is_suspended = 1;
}

void sigcont_handler(int sig) {
  is_suspended = 0;
}

int main() {
  // Install signal handlers
  signal(SIGSTOP, sigstop_handler); // Ctrl + S - To Stop
  signal(SIGCONT, sigcont_handler); // Ctrl + Q to continue

  while (1) {
    // Check if process is suspended
    if (is_suspended) {
      printf("Process is suspended. Waiting for SIGCONT...\n");
      pause(); // Suspend execution until SIGCONT is received
    } else {
      printf("Process is running...\n");
      sleep(1); // Do some work
    }
  }

  return 0;
}
