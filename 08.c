#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  // for sleep()

int main(int argc, char **argv)
{
    FILE *fp = NULL;
    if ((fp = fopen("./08.c", "r")) != NULL) {
        printf("Waiting for 15 seconds...\n");
        sleep(15);  // Time in seconds should be pass in sleep(time_in_sec).
    } else
        perror("Error (File cannot open) ");

    if (fp != NULL)
        fclose(fp);
    return EXIT_SUCCESS;
}