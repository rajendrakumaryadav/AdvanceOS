/**
 *  @author Rajendra Kumar Yadav
 * @date Feb 19 2020
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * Step 1 − Create pipe1 for the parent process to write and the child process
 * to read.
 * Step 2 − Create pipe2 for the child process to write and the parent process
 * to read.
 * Step 3 − Close the unwanted ends of the pipe from the parent and child side.
 * Step 4 − Parent process to write a message and child process to read and
 * display on the screen. Step 5 − Child process to write a message and parent
 * process to read and display on the screen.
 * */

int main() {
  int pipefds1[2], pipefds2[2];
  int pid;

  char pipe1writemessage[20] = "Hi";
  char pipe2writemessage[20] = "Hello";

  char readmessage[20];

  if ((pipe(pipefds1)) == -1) {
    printf("Unable to create pipe 1 \n");
    perror("Error ");
    return 1;
  }

  if ((pipe(pipefds2)) == -1) {
    printf("Unable to create pipe 2 \n");
    perror("Error ");
    return 1;
  }
  pid = fork();
  /*************************************
   *    if pid == 0                     *
   *        It is Child                 *
   *    else                            *
   *        Parent;                     *
   * ***********************************/

  if (pid != 0) {
    close(pipefds1[0]);  // closing pipe1 read end
    close(pipefds2[1]);  // closing pipe2 write end

    printf("In Parent: Writing to pipe 1 – Message is %s\n", pipe1writemessage);

    /************************************
     * Writing into pipe1 from child   *
     * *********************************/
    if (write(pipefds1[1], pipe1writemessage, sizeof(pipe1writemessage)) == -1)
      perror("Error ");

    /************************************
     * Writing into pipe2 from parent   *
     * *********************************/
    if ((read(pipefds2[0], readmessage, sizeof(readmessage))) != -1) {
      printf("In Parent: Reading from pipe 2 – Message is %s\n", readmessage);
    }
  } else {
    close(pipefds1[1]);  // closing pipe1 write end
    close(pipefds2[0]);  // closing pipe2 read end

    /************************************
     * read from pipe1 in parent...     *
     * *********************************/

    if (read(pipefds1[0], readmessage, sizeof(readmessage)) != -1) {
      // Read failed if -1
      printf("In Child: Reading from pipe 1 – Message is %s\n", readmessage);
      printf("In Child: Writing to pipe 2 – Message is %s\n",
             pipe2writemessage);
      /************************************
       * Writing into pipe2 from parent   *
       * *********************************/
    }
    if (write(pipefds2[1], pipe2writemessage, sizeof(pipe2writemessage)) ==
        -1) {
      perror("Error ");
    }
  }

  return EXIT_SUCCESS;
}