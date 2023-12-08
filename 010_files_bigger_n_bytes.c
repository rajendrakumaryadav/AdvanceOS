// Show the file bigger than n bytes in C Program
// Created by Rajendra Kumar R Yadav
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    // Get the size threshold from the user
    int sizeThreshold;
    printf("Enter the size threshold (in bytes): ");
    scanf("%d", &sizeThreshold);

    // Open the current directory
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Get file information
        struct stat fileInfo;
        if (stat(entry->d_name, &fileInfo) == -1) {
            perror("stat");
            continue;
        }

        // Check if the file is a regular file
        if (!S_ISREG(fileInfo.st_mode)) {
            continue;
        }

        // Check if the file size is greater than the threshold
        if (fileInfo.st_size > sizeThreshold) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
