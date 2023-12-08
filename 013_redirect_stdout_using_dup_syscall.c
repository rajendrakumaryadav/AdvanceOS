// Created by: Rajendra Kumar R Yadav
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
  // Open the file "output.txt" in append mode
  int outputFile = open("output.txt", O_WR | O_APPEND);
  if (outputFile == -1) {
    perror("open");
    return 1;
  }

  // Redirect standard output to the file descriptor
  int originalStdout = dup(stdout);
  if (dup2(outputFile, stdout) == -1) {
    perror("dup2");
    close(outputFile);
    return 1;
  }

  // Print some text to standard output
  printf("This text will be written to the file.\n");

  // Restore standard output
  dup2(originalStdout, stdout);
  close(originalStdout);

  // Close the file
  close(outputFile);

  return EXIT_SUCCESS;
}
