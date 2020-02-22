#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main (int argc, char **argv)
{
    int number_of_ch = 0;
    printf ("Enter number of child(ern) : ");
    scanf ("%d", &number_of_ch);
    for (int i = 0; i < number_of_ch; i++)    // loop will run n times (n=5)c
        {
            if (fork () == 0)
                {
                    printf ("[Child] PID [%d] from [Parent] PID [%d]\n", getpid (), getppid ());
                    exit (0);
                }
        }
    for (int i = 0; i < number_of_ch; i++)    // loop will run n times (n=5)
        // wait((void *)2);
        wait (NULL);
}
