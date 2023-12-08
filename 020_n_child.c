#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>


int main() {
  // Get the number of child processes to create
  int n = 0;
  printf("Enter the number of child processes to create: ");
  scanf("%d", &n);

  // Create n child processes
  int childPids[n];
  for (int i = 0; i < n; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      // Child process
      // Simulate some workload to spend some time
      for (int j = 0; j < 1000000; j++) {
        for (int k = 0; k < 1000; k++) {
          // Do some dummy computation
        }
      }
      exit(0);
    } else if (pid > 0) {
      // Parent process
      childPids[i] = pid;
    } else {
      // Fork failed
      perror("fork");
      exit(EXIT_FAILURE);
    }
  }

  // Wait for all child processes to terminate
  int childPid;
  struct rusage usage;
  long totalUserTime = 0, totalKernelTime = 0;
  while ((childPid = wait3(&usage, WUNTRACED, NULL)) != -1) {
    // Accumulate user and kernel times from each child process
    totalUserTime += usage.ru_utime;
    totalKernelTime += usage.ru_stime;
  }

  // Calculate total cumulative time in user and kernel mode
  double totalUserTimeSeconds = totalUserTime / (double)sysconf(_SC_CLK_TCK);
  double totalKernelTimeSeconds = totalKernelTime / (double)sysconf(_SC_CLK_TCK);

  // Display total cumulative time
  printf("Total cumulative user time: %fs\n", totalUserTimeSeconds);
  printf("Total cumulative kernel time: %fs\n", totalKernelTimeSeconds);

  return 0;
}
