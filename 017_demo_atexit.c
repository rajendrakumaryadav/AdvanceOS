// 017 - Demonstrate atexit
// Rajendra Kumar R Yadav
#include <stdio.h>
#include <stdlib.h>

void cleanup(FILE *fp)
{
    if (fp)
    {
        fclose(fp);
    }
}

int main()
{
    FILE *fp = fopen("myfile.txt", "r");
    if (!fp)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    // Register the cleanup function to be called when the program terminates
    atexit(cleanup);
    // other file related options

    return 0;
}
