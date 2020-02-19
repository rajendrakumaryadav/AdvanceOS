#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  struct timeval start, end;
  gettimeofday(&start, NULL);
  sleep(5);
  gettimeofday(&end, NULL);
  long seconds = (end.tv_sec - start.tv_sec);
  printf("Time requires for executions %0.5d\n", seconds);
  return EXIT_SUCCESS;
}