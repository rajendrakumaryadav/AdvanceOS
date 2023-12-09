#include <stdio.h>
#include <unistd.h>

int main() {
  int pipefds[2]; // Array to store read and write file descriptors
  int return_status; // Variable to store return values
  char message1[] = "Hello World";
  char message2[] = "Hello SPPU";
  char message3[] = "Linux is Funny";
  char read_message[50]; // Buffer to read messages

  // Create an unnamed pipe
  return_status = pipe(pipefds);
  if (return_status == -1) {
    printf("Error creating pipe\n");
    return 1;
  }

  // Fork a child process
  int child_pid = fork();
  if (child_pid == 0) { // Child process
    printf("Child is writing to pipe:\n");

    // Write messages to the pipe
    write(pipefds[1], message1, sizeof(message1));
    printf("Message 1: %s\n", message1);

    write(pipefds[1], message2, sizeof(message2));
    printf("Message 2: %s\n", message2);
    write(pipefds[1], message3, sizeof(message3));
    printf("Message 3: %s\n", message3);
  } else if (child_pid > 0) { // Parent process
    // Read messages from the pipe
    read(pipefds[0], read_message, sizeof(read_message));
    printf("Parent Process is Reading from pipe: %s\n", read_message);

    read(pipefds[0], read_message, sizeof(read_message));
    printf("Parent Process is Reading from pipe: %s\n", read_message);

    ssize_t data_len = read(pipefds[0], read_message, sizeof(read_message));
    printf("Parent Process is Reading from pipe: %s\n", read_message);
  } else { // Fork error
    printf("Error forking child process\n");
    return 1;
  }
  return 0;
}