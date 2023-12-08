#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int caught_sigint = 0;

void sigint_handler(int signo) {
  if (caught_sigint) {
    printf("\nSIGINT received again. Exiting...\n");
    exit(1);
  } else {
    caught_sigint = 1;
    printf("\nSIGINT received. Press Ctrl-C again to exit.\n");
  }
}

int main() {
  // Install signal handler for SIGINT
  signal(SIGINT, sigint_handler);

  // Keep the program running until a SIGINT is received twice
  while (!caught_sigint) {
    // Do your main program logic here
    printf("Program running...\n");
    sleep(1);
  }

  return 0;
}
