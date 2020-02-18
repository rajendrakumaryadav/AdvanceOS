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
  char f_created_time[50];

  grp = getgrgid(filestat->st_gid);
  pwd = getpwuid(filestat->st_uid);
  struct tm c_time;
  c_time = *localtime(&filestat->st_ctime);
  strftime(f_created_time, sizeof(f_created_time), "%b %2d %R", &c_time);

  printf((S_ISDIR(filestat->st_mode)) ? "d" : "-");
  printf((filestat->st_mode & S_IRUSR) ? "r" : "-");
  printf((filestat->st_mode & S_IWUSR) ? "w" : "-");
  printf((filestat->st_mode & S_IXUSR) ? "x" : "-");
  printf((filestat->st_mode & S_IRGRP) ? "r" : "-");
  printf((filestat->st_mode & S_IWGRP) ? "w" : "-");
  printf((filestat->st_mode & S_IXGRP) ? "x" : "-");
  printf((filestat->st_mode & S_IROTH) ? "r" : "-");
  printf((filestat->st_mode & S_IWOTH) ? "w" : "-");
  printf((filestat->st_mode & S_IXOTH) ? "x" : "-");
  printf(" ");

  printf("%2lu %14.32s %14.32s % ld %12.14s %s\n",
         filestat->st_nlink, pwd->pw_name,
         grp->gr_name, filestat->st_size, f_created_time, fileName);
}