#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
char *months[] = {
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sept",
    "Oct",
    "Nov",
    "Dec"};
int main(int argc, char **argv)
{
    time_t created_time;
    DIR *dir = NULL;
    struct tm time;
    struct dirent *direntry = NULL;
    struct stat filestat;
    int month = 10;
    dir = opendir("/home/rajendrayadav/Videos");
    if (dir != NULL)
    {

        printf("%-7s\t : %-50s\n", "Months", "File Name");
        for (int i = 0; i < 87; i++)
        {
            printf("-");
        }
        printf("\n");

        while ((direntry = readdir(dir)) != NULL)
        {
            lstat(direntry->d_name, &filestat);
            // Instead of birthtime, I am checking modified time.
            // use filestat.st_ctime for created time.
            created_time = (time_t)filestat.st_mtime;
            time = *localtime(&created_time);
            printf("%-7s\t : %-50s\n", months[(&time)->tm_mon], direntry->d_name);
        }
    }
    else
    {
        perror("Error ");
    }
    exit(EXIT_SUCCESS);
}