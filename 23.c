#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    int out = open("cout.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (-1 == out)
    {
        perror("opening cout.log");
        return -1;
    }

    int save_out = dup(fileno(stdout));

    if (-1 == dup2(out, fileno(stdout)))
    {
        perror("cannot redirect stdout");
        return -1;
    }

    puts("doing an ls or something now");

    fflush(stdout);
    close(out);
    
    dup2(save_out, fileno(stdout));
    close(save_out);
    puts("back to normal output");

    return 0;
}