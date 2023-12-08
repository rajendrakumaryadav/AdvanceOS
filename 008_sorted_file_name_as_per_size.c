// Sorted file name as per size
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILES 400

typedef struct {
  char filename[256];
  size_t size;
} FileInfo;

int compareFileInfo(const void *a, const void *b) {
  FileInfo *fa = (FileInfo *)a;
  FileInfo *fb = (FileInfo *)b;

  if (fa->size < fb->size) {
    return -1;
  } else if (fa->size > fb->size) {
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char *argv[]) {
    printf("Total nos of file can be handled %d\n", MAX_FILES);
    if (argc < 2)
    {
        printf("Usage: %s filename1 filename2 ...\n", argv[0]);
        return 1;
    }

  int numFiles = argc - 1;
  if (numFiles > MAX_FILES) {
    printf("Error: Too many files. Maximum allowed is %d.\n", MAX_FILES);
    return 1;
  }

  FileInfo fileInfos[MAX_FILES];
  for (int i = 1; i < argc; i++) {
    struct stat st;
    if (stat(argv[i], &st) == -1) {
      printf("Error: Unable to stat file %s.\n", argv[i]);
      return 1;
    }

    strcpy(fileInfos[i - 1].filename, argv[i]);
    fileInfos[i - 1].size = st.st_size;
  }

  qsort(fileInfos, numFiles, sizeof(FileInfo), compareFileInfo);

  for (int i = 0; i < numFiles; i++) {
    printf("%s: %zu bytes\n", fileInfos[i].filename, fileInfos[i].size);
  }

  return 0;
}
