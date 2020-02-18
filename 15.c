#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
void printInfo(struct stat *, const char *);

int main(int argc, const char **argv)
{
  struct stat filestat;
  stat(argv[1], &filestat);
  printInfo(&filestat, argv[1]);
  return EXIT_SUCCESS;
}

void printInfo(struct stat *filestat, const char *fileName)
{
  struct passwd *pwd;
  struct group *grp;
  grp = getgrgid(filestat->st_gid);
  pwd = getpwuid(filestat->st_uid);
  printf("%lu\t%12.32s\t%12.32s\t%ld\t\n",
         filestat->st_nlink, pwd->pw_name,
         grp->gr_name, filestat->st_size);
}