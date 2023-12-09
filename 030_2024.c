// Date: 09-12-2023
// Created by: Rajendra Kumar Yadav

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void handle_signal_int(int sig)
{
    printf("Signal [%d] Received, But ignored!", sig);
} // Ctrl + c - SIGINT | Ctrl + \ - SIGQUIT

int main(int argc, char **argv)
{
    signal(SIGINT, handle_signal_int);
    signal(SIGQUIT, handle_signal_int);
    
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("Pipe creation failed!");
        exit(-1);
    }
    // Registering signal handlers
    sleep(3);

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Failed to created child");
        exit(-1);
    }
    else if (pid == 0)
    { // if child process is created
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        exit(1);
    }
    else
    {                     // Parent process
        close(pipefd[1]); // closeing the write end of program.
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // after reading closing the pipe reading end.
        execlp("wc", "wc", "-l", NULL);
        exit(1);
    }
    wait(NULL);
    return EXIT_SUCCESS;
}
