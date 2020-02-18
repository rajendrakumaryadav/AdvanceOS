#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv) {
  struct stat file_stat;

  for (int i = 1; i < argc; i++) {
    lstat(argv[i], &file_stat);
    printf("File Name : %10s, File Size : %7lluBytes\n", argv[i],
           (long long)(&file_stat)->st_size);
  }
  printf("\n");
  return EXIT_SUCCESS;
}