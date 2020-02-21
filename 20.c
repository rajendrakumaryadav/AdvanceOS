/******************************************************************
 * @author Rajendra Kumar R. Yadav <rajendra.ecti@gmail.com>      *
 * @date Feb 2020, 21                                             *
 * @file 20.c                                                     *
 **************************************************************** */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
    int count_of_argc = 0;
    if (argc < 2) {
        printf("Usages : %s <filename(s)>\n", argv[0]);
        exit(-127);
    }
    do {
        printf("Argument [%d] : %s\n", count_of_argc, argv[count_of_argc]);
        count_of_argc += 1;
    } while (count_of_argc < argc);

    exit(EXIT_SUCCESS);
}
