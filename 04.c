#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    struct stat file_stat;
    // process writing in

    for (int i = 1; i < argc; i++) {
        lstat(argv[i], &file_stat);
        // use ls -li to display long format with inode
        // 5248664 -rwxr-xr-x 1 username 20K Feb 14 00:19 04
        printf("File Name : %4s, inode - # : %llu\n", argv[i], (long long) (&file_stat)->st_ino);
        // Program output : File Name :         04, inode - # : 5248664
    }
    printf("\n");
    return EXIT_SUCCESS;
}