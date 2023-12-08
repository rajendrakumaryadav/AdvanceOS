// Print the input file type
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/stat.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: '%s' filename\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];
  struct stat file_info;

  if (stat(filename, &file_info) == -1) {
    perror("stat");
    return 1;
  }

  switch (file_info.st_mode & S_IFMT) {
    case S_IFREG:
      printf("'%s' is a regular file.\n", filename);
      break;
    case S_IFDIR:
      printf("'%s' is a directory.\n", filename);
      break;
    case S_IFLNK:
      printf("'%s' is a symbolic link.\n", filename);
      break;
    case S_IFSOCK:
      printf("'%s' is a socket.\n", filename);
      break;
    case S_IFCHR:
      printf("'%s' is a character device.\n", filename);
      break;
    case S_IFBLK:
      printf("'%s' is a block device.\n", filename);
      break;
    default:
      printf("'%s' is an unknown file type.\n", filename);
      break;
  }

  return 0;
}
