#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

static int COUNT = 0;

int main(int argc, char **argv)
{
    DIR *          dir;
    struct dirent *dirent;

    char d_type;
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error ");
    }
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_type == DT_REG) {
            printf("%s\n", dirent->d_name);
            COUNT++;
        }
    }
    printf("Total File(s) : %d\n", COUNT);
    return EXIT_SUCCESS;
}