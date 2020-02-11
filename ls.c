#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char **argv) {
    
    FILE *file;
    DIR *dir;
    struct dirent *dirent;
    struct stat filestat;

    if(argc < 2) {
        dir = opendir(".");
        if(dir == NULL) {
            printf("error here : current");
            perror("Error ");
        }
    }
    if (argc >= 2) {
        dir = opendir(argv[1]);
        if(dir == NULL) {
            printf("error here %s\n", argv[1] );
            perror("Error ");
        }
    }
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    while((dirent = readdir(dir)) != NULL) {
        
        if((strncmp(dirent->d_name, ".", 2) == 0) || (strncmp(dirent->d_name, "..", 2) == 0)) {
            continue;
        }

        if((file = fopen(dirent->d_name, "r"))) {
            lstat(dirent->d_name, &filestat);
            printf("File Name               : %-10s\n", dirent->d_name);
            printf("Size                    : %lluB\n", (&filestat)->st_size);
            printf("User ID                 : %-10u\n", (&filestat)->st_uid);
            printf("GROUP ID                : %-10u\n", (&filestat)->st_gid);
            printf("File Created At         : %-10s", ctime(&filestat.st_birthtime));
            printf("Last file modification  : %-10s", ctime(&filestat.st_ctime));
            printf("Last Accessed Time      : %-10s", ctime(&filestat.st_atime));
            printf("Permission              : %o\n", filestat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        } else {
            perror("Error ");
        }
    }
    return EXIT_SUCCESS;
}