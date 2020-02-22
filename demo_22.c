/**********************************************
 * @author Rajendra Kumar R Yadav             *
 * @date Feb 22, 2020                         *
 * @file demo_22.c                            *
 * *******************************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void catch_signal(int sigstatus)
{
    if (sigstatus == SIGINT)
        printf("SIGINT CAUGHT : CTRL + C\n");

    if (sigstatus == SIGQUIT)
        printf("SIGQUIT CAUGHT : CTRL + \\ \n");
}
int main()
{
    signal(SIGINT, catch_signal);
    signal(SIGQUIT, catch_signal);

    for (;;)
        ;

    exit(EXIT_SUCCESS);
}
