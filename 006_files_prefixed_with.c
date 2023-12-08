// File Prefixed with provided values
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s prefix\n", argv[0]);
    return 1;
  }

  char *prefix = argv[1];
  DIR *dir = opendir(".");
  if (!dir) {
    perror("opendir");
    return 1;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
      printf("%s\n", entry->d_name);
    }
  }

  closedir(dir);
  return 0;
}
