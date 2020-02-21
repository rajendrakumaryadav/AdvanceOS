/******************************************************************
 * @author Rajendra Kumar R. Yadav <rajendra.ecti@gmail.com>      *
 * @date Feb 2020, 21                                             *
 * @file 20.c                                                     *
 **************************************************************** */
#include <errno.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *Argv[])
{
    if (argc < 3) {
        printf("Usage : %s <filename1> <filename2> ...\n", Argv[0]);
        exit(-1);
    }
    exit(EXIT_SUCCESS);
}