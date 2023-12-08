// Check if file exists or not
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  struct stat file_info;

  if (stat(filename, &file_info) == 0) {
    printf("'%s' exists in the current directory.\n", filename);
    return 0;
  } else {
    printf("'%s' does not exist in the current directory.\n", filename);
    return 1;
  }
}
