#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, const char *argv[])
{
    if (fopen ("/tmp/outfile", "r") == NULL)
        {
            unlink ("/tmp/outfile");
        }
    if (freopen ("/tmp/outfile", "w", stdout) == NULL)
        {
            perror ("Error ");
            exit (-1);
        }
    execvp ("ls", ( const char * ) argv);

    return EXIT_SUCCESS;
}