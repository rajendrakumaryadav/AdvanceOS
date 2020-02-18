#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv)
{
    FILE *file;
    DIR *dir;
    struct dirent *dirent;
    struct stat filestat;
    struct passwd *pwd;
    struct group *grp;

    if (argc > 2)
    {
        dir = opendir(argv[1]);
        if (dir == NULL)
        {
            perror("Error ");
        }
    }

    return EXIT_SUCCESS;
}