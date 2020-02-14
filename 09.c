#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
    struct stat file_stat;
    FILE *file;
    for (int i = 1; i < argc; i++)
    {
        lstat(argv[i], &file_stat);
        if(fopen(argv[i], "r") == NULL) {
            perror("Error   ");
            exit(EXIT_FAILURE);
        }
        if (((&file_stat)->st_size) > 1024)
        {
            printf("File Name : %4s, File Size : %0.2lf KiloByte\n", argv[i], (double)(&file_stat)->st_size / 1024);
        }
        else
        {
            printf("File Name : %4s, File Size : %.2lld Byte\n", argv[i], (long long)(&file_stat)->st_size);
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}