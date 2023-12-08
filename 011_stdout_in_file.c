// Created by Rajendra Kumar R Yadav

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("All the information will be kept in 'output.txt' file after this line.\n");

    // Redirect standard output to a file named "output.txt"
    freopen("output.txt", "w", stdout);

    // Print some text to the standard output
    printf("This text will be written to the file.\n");
    printf("All the printf message will be written in output.txt automatically.");
    // Close the file
    fclose(stdout);

    return EXIT_SUCCESS;
}
