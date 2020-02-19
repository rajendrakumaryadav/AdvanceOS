#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  struct stat file_stat;
  if (argc < 2) {
    printf("%s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {
    lstat(argv[i], &file_stat);
    if (!S_ISREG((&file_stat)->st_mode)) {
      printf("Error : Not a File.\n");
      exit(0);
    }
    printf("File Name : %10s, File Size : %7lluBytes\n", argv[i],
           (long long)(&file_stat)->st_size);
  }
  printf("\n");
  return EXIT_SUCCESS;
}