#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pfd[2]; /* Pipe file descriptors */

    if (pipe(pfd) == -1) /* Create pipe */
        perror("Error [Pipe cannot create] ");

    switch (fork()) {
        case -1:
            perror("Error [Fork Can not created!] ");
        case 0:                      /* First child: exec 'ls' to write to pipe */
            if (close(pfd[0]) == -1) /* Read end is unused */
                perror("Error [Read node couldn't closed!] ");

            /* Duplicate stdout on write end of pipe; close duplicated descriptor */

            if (pfd[1] != STDOUT_FILENO) { /* Defensive check
                                          | File descriptor type check */
                // dup2(oldfile, newfile);
                if (dup2(pfd[1], STDOUT_FILENO) == -1) perror("duplicating STDOUTDATA");
                if (close(pfd[1]) == -1) perror("close 2");
            }

            execlp("ls", "ls", "-l", (char *)NULL); /* Writes to pipe */
            perror("Cannot Execute ls");
        default: /* Parent falls through to create next child */
            break;
    }

    switch (fork()) {
        case -1:
            perror("Error [Fork Can not created!] ");

        case 0:                      /* Second child: exec 'wc' to read from pipe */
            if (close(pfd[1]) == -1) /* Write end is unused */
                perror("Error [write node couldn't close!] ");

            /* Duplicate stdin on read end of pipe; close duplicated descriptor */

            if (pfd[0] != STDIN_FILENO) { /* Defensive check */
                if (dup2(pfd[0], STDIN_FILENO) == -1)
                    perror("Error [Duplicating from pfd[0] into STD Input");
                if (close(pfd[0]) == -1) perror("close 4");
            }

            execlp("wc", "wc", "-l", (char *)NULL);
            perror("Cannot execute wc");

        default: /* Parent falls through */
            break;
    }

    /* Parent closes unused file descriptors for pipe, and waits for children */

    if (close(pfd[0]) == -1) perror("Cann't closing Pipe Read end");
    if (close(pfd[1]) == -1) perror("Cann't closing Pipe Write end");
    if (wait(NULL) == -1) perror("Error During wait 1 for fork[1]");
    if (wait(NULL) == -1) perror("Error During wait 2 for fork[2]");

    exit(EXIT_SUCCESS);
}