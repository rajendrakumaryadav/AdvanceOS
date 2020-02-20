#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define errorhandle()                      \
    {                                      \
        printf("\nNull Pointer Error!\n"); \
        exit(EXIT_FAILURE);                \
    }

int main(void) {
    DIR *dir = NULL;
    struct dirent *direntry = NULL;
    struct stat filestat;
    int minimum_file_size;

    printf("Enter the Minimum file Size : ");
    scanf("%d", &minimum_file_size);

    if ((dir = opendir(".")) != NULL) {
        while ((direntry = readdir(dir)) != NULL) {
            if ((strncmp(direntry->d_name, ".", 1) == 0) ||
                (strncmp(direntry->d_name, "..", 2) == 0)) {
                continue;
            }
            lstat(direntry->d_name, &filestat);
            if ((&filestat)->st_size >= minimum_file_size) {
                printf("%-20s%-5lld\n ", direntry->d_name, (long long)filestat.st_size);
            }
        }
    } else {
        printf("Error No      : %d\n", errno);
        perror("Error Message ");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}