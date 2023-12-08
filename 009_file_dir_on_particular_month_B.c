#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>

#define TARGET_MONTH 10 // October (October is the 10th month)

int main()
{
    int target_month;
    printf("Enter the month [0-11]: ");
    scanf("%d", &target_month);
    // Get the current month
    time_t t = time(NULL);
    struct tm *ltm = localtime(&t);
    int currentMonth = ltm->tm_mon + 1;

    // Open the current directory
    DIR *dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Get file information
        struct stat fileInfo;
        if (stat(entry->d_name, &fileInfo) == -1)
        {
            perror("stat");
            continue;
        }

        // Check if the file is a regular file
        if (!S_ISREG(fileInfo.st_mode))
        {
            continue;
        }

        // Get the file creation month
        struct tm *creationTime = localtime(&fileInfo.st_ctime);
        int creationMonth = creationTime->tm_mon + 1;

        // Check if the file was created in the target month
        if (creationMonth == target_month)
        {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
