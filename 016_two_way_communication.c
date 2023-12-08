// 016 - Two Way communication
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main() {

  // Create two pipes for two-way communication
  int parent_to_child[2];
  int child_to_parent[2];

  // Create pipes
  if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  //Fork a child process
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) { // Child process
    // Close unused read end
    close(parent_to_child[0]);
    close(child_to_parent[1]);

    // Read message from parent
    char message[1024];
    read(child_to_parent[0], message, sizeof(message));
    printf("Child received: %s\n", message);

    // Respond back to parent
    char response[] = "This is a response from child!";
    write(parent_to_child[1], response, sizeof(response));

    // Close pipes
    close(parent_to_child[1]);
    close(child_to_parent[0]);
  } else { // Parent process
    // Close unused write end
    close(parent_to_child[1]);
    close(child_to_parent[0]);

    // Send message to child
    char message[] = "Hello from parent!";
    write(child_to_parent[1], message, sizeof(message));

    // Read response from child
    char response[1024];
    read(parent_to_child[0], response, sizeof(response));
    printf("Parent received: %s\n", response);

    // Close pipes
    close(parent_to_child[0]);
    close(child_to_parent[1]);

    // Wait for child process to finish
    waitpid(pid, NULL, 0);
  }

  return 0;
}
