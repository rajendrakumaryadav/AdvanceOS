/******************************************************************
 * @author Rajendra Kumar R. Yadav <rajendra.ecti@gmail.com>      *
 * @date Feb 2020, 21                                             *
 * @file 20.c                                                     *
 **************************************************************** */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    errno = EACCES;
    perror (argv[0]);
    exit (EXIT_SUCCESS);
}