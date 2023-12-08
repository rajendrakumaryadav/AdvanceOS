// Rajendra Kumar R Yadav
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main()
{
  // Create a pipe for inter-process communication
  int pipefd[2];
  if (pipe(pipefd) == -1)
  {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  // Fork a child process
  pid_t pid = fork();
  if (pid == -1)
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  { // Child process
    // Close the unused read end of the pipe
    close(pipefd[0]);

    // Duplicate the write end of the pipe to standard output
    dup2(pipefd[1], STDOUT_FILENO);

    // Close the write end of the pipe
    close(pipefd[1]);

    // Execute the 'ls -l' command
    execlp("ls", "ls", "-l", NULL);
  }
  else
  { // Parent process
    // Close the unused write end of the pipe
    close(pipefd[1]);

    // Read the output of the 'ls -l' command and count the lines
    int numLines = 0;
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
    {
      for (int i = 0; i < bytesRead; i++)
      {
        if (buffer[i] == '\n')
        {
          numLines++;
        }
      }
    }

    if (bytesRead == -1)
    {
      perror("read");
      exit(EXIT_FAILURE);
    }

    // Close the read end of the pipe
    close(pipefd[0]);

    // Print the number of lines
    printf("Total lines: %d\n", numLines);

    // Wait for the child process to finish
    waitpid(pid, NULL, 0);
  }

  return 0;
}
