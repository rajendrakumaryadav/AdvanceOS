// file in asc order
// Created by: Rajendra Kumar R Yadav

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int compare(const int *a, const int *b)
{
  const struct dirent **p1 = (const struct dirent **)a;
  const struct dirent **p2 = (const struct dirent **)b;

  return strcmp((*p1)->d_name, (*p2)->d_name);
}

int main(void)
{
  struct dirent **namelist;
  int n;
  int i = 0;

  // Use scandir() to get an array of dirent structures
  n = scandir(".", &namelist, NULL, (int (*)(const struct dirent **, const struct dirent **))compare);
  if (n < 0)
  {
    perror("scandir");
    return 1;
  }

  // Print only directories
  while (i < n)
  {
    if (namelist[i]->d_type == DT_DIR)
    {
      printf("%s\n", namelist[i]->d_name);
    }
    free(namelist[i]);
    i++;
  }

  // Free the namelist array
  free(namelist);

  return 0;
}
