#include <stdio.h>
#include <sys/resource.h>

int main() {
  struct rlimit rlim;

  // Get current file limit
  int resource = RLIMIT_NOFILE;
  if (getrlimit(resource, &rlim) == -1) {
    perror("getrlimit");
    return 1;
  }

  printf("Current soft limit for open files: %ld\n", rlim.rlim_cur);
  printf("Current hard limit for open files: %ld\n", rlim.rlim_max);

  // Set new soft limit for open files
  rlim.rlim_cur = 1024;
  if (setrlimit(resource, &rlim) == -1) {
    perror("setrlimit");
    return 1;
  }

  printf("New soft limit for open files: %ld\n", rlim.rlim_cur);

  // Get current memory limit
  resource = RLIMIT_DATA;
  if (getrlimit(resource, &rlim) == -1) {
    perror("getrlimit");
    return 1;
  }

  printf("Current soft limit for memory: %ld bytes\n", rlim.rlim_cur);
  printf("Current hard limit for memory: %ld bytes\n", rlim.rlim_max);

  // Set new soft limit for memory
  rlim.rlim_cur = 1024 * 1024;  // 1 MB
  if (setrlimit(resource, &rlim) == -1) {
    perror("setrlimit");
    return 1;
  }

  printf("New soft limit for memory: %ld bytes\n", rlim.rlim_cur);

  return 0;
}
