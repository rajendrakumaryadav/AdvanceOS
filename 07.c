#include <stdio.h>
#include <stdlib.h>

void done () { printf ("Exiting Successfully\n"); }

int main ()
{
    int value;
    value = atexit (done);

    if (value != 0)
        {
            printf ("atexit () function registration failed");
            exit (1);
        }
    printf ("Registration successful.\n");
    return 0;
}