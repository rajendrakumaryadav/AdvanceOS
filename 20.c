/******************************************************************
 * @author Rajendra Kumar R. Yadav <rajendra.ecti@gmail.com>      *
 * @date Feb 2020, 21                                             *
 * @file 20.c                                                     *
 **************************************************************** */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char *Argv[])
{
    char *input[BUFSIZ];
    int   pfd[2];
    if (pipe(pfd) == -1) {
        perror("Error [Pipe cann't created] \n");
        exit(-1);
    }
    if (argc < 3) {
        fprintf(stderr, "Usage : %s <filename1> <filename2> ...\n", Argv[0]);
        exit(-1);
    }
    int i = 0;
    do {
        input[i] = Argv[i + 1];
        i++;
    } while (argc != i);
    makeToken(input);

    printf("Process ID : %ld, Parent PID : %ld\n", getpid(), getppid());

    switch (fork()) {
        case -1:
            fprintf(stderr, "Error : Child could not created!\n");
            exit(-1);
        case 0:
            printf("Process ID : %ld, Parent PID : %ld\n", getpid(), getppid());
            printf("Parent Process!\n");
            break;
        default:
            printf("Process ID : %ld, Parent PID : %ld\n", getpid(), getppid());
            break;
    }
    exit(EXIT_SUCCESS);
}