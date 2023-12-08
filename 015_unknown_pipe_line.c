// Unknown pipeline
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {
    int pipefd[2];
    pid_t pid;

    // Create an unnamed pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Write data to the pipe
        char message[] = "Hello from the child process!";
        if (write(pipefd[1], message, sizeof(message)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        close(pipefd[1]);
    } else { // Parent process
        // Read data from the pipe
        char message[1024];
        int bytesRead = read(pipefd[0], message, sizeof(message));
        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Print the data read from the pipe
        printf("Received data from child process: %s\n", message);

        // Close the read end of the pipe
        close(pipefd[0]);
    }

    // Wait for the child process to finish
    waitpid(pid, NULL, 0);

    return 0;
}
