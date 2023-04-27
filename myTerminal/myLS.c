#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <math.h>

// Function to convert string to all lowercase
void lower(char *temp)
{
    int size = strlen(temp);
    for (int i = 0; i < size; i++)
    {
        if (temp[i] >= 65 && temp[i] <= 90)
        {
            temp[i] += 32;
        }
    }
}

// Struct to store the data
struct info
{
    char parr[10];
    int link;
    char *owner;
    char *group;
    long long int size;
    char modification_time[50];
    char *filename;
};
int count = 0;
struct info arr[100];

// Storing the data in an array of struct
void store(char *cwd)
{
    char *current_directory = NULL;
    DIR *dp = NULL;
    struct dirent *directoryptr = NULL;
    struct stat fileInfo;

    current_directory = cwd;
    if (current_directory == NULL)
    {
        printf("\nThe present directory could not be found!!\n");
        exit(EXIT_FAILURE);
    }

    dp = opendir((const char *)current_directory);
    if (dp == NULL)
    {
        printf("\nThe present directory could not be opened!!\n");
        exit(EXIT_FAILURE);
    }

    for (count = 0; (directoryptr = readdir(dp)) != NULL; count++)
    {
        char *temp = directoryptr->d_name;
        stat(directoryptr->d_name, &fileInfo);
        (S_ISDIR(fileInfo.st_mode)) ? (arr[count].parr[0] = 'd') : (arr[count].parr[0] = '-');
        (fileInfo.st_mode & S_IRUSR) ? (arr[count].parr[1] = 'r') : (arr[count].parr[1] = '-');
        (fileInfo.st_mode & S_IWUSR) ? (arr[count].parr[2] = 'w') : (arr[count].parr[2] = '-');
        (fileInfo.st_mode & S_IXUSR) ? (arr[count].parr[3] = 'x') : (arr[count].parr[3] = '-');
        (fileInfo.st_mode & S_IRGRP) ? (arr[count].parr[4] = 'r') : (arr[count].parr[4] = '-');
        (fileInfo.st_mode & S_IWGRP) ? (arr[count].parr[5] = 'w') : (arr[count].parr[5] = '-');
        (fileInfo.st_mode & S_IXGRP) ? (arr[count].parr[6] = 'x') : (arr[count].parr[6] = '-');
        (fileInfo.st_mode & S_IROTH) ? (arr[count].parr[7] = 'r') : (arr[count].parr[7] = '-');
        (fileInfo.st_mode & S_IWOTH) ? (arr[count].parr[8] = 'w') : (arr[count].parr[8] = '-');
        (fileInfo.st_mode & S_IXOTH) ? (arr[count].parr[9] = 'x') : (arr[count].parr[9] = '-');
        arr[count].link = fileInfo.st_nlink;
        arr[count].owner = getpwuid(fileInfo.st_uid)->pw_name;
        arr[count].group = getgrgid(fileInfo.st_gid)->gr_name;
        arr[count].size = fileInfo.st_size;
        struct tm *time = localtime(&fileInfo.st_mtime);
        char timestring[80];
        strftime(timestring, sizeof(timestring), "%b %d %H:%M", time);
        strcpy(arr[count].modification_time, timestring);
        arr[count].filename = directoryptr->d_name;
    }
    closedir(dp);
}

// Listing the filenames in lexografic order
void myls()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        printf("%s  ", arr[i].filename);
    }
    printf("\n");
}

// Listing with extra information
void mylsl()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    long long int sum = 0, val = 0;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = arr[i].size / 4096 + 1;
        }
        sum += val * 4;
    }
    printf("total %lld\n", sum);
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        printf("%c", arr[i].parr[0]);
        printf("%c", arr[i].parr[1]);
        printf("%c", arr[i].parr[2]);
        printf("%c", arr[i].parr[3]);
        printf("%c", arr[i].parr[4]);
        printf("%c", arr[i].parr[5]);
        printf("%c", arr[i].parr[6]);
        printf("%c", arr[i].parr[7]);
        printf("%c", arr[i].parr[8]);
        printf("%c  ", arr[i].parr[9]);
        printf("%d  ", arr[i].link);
        printf("%s  ", arr[i].owner);
        printf("%s  ", arr[i].group);
        printf("%7lld  ", arr[i].size);
        printf("%9s  ", arr[i].modification_time);
        printf("%s  ", arr[i].filename);
        printf("\n");
    }
}

// Listing filenames with sizes before the filenames
void mylss()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    long long int sum = 0, val = 0;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = arr[i].size / 4096 + 1;
        }
        sum += val * 4;
    }
    printf("total %lld\n", sum);
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        long long int val;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = (arr[i].size / 4096) + 1;
        }
        printf("%lld ", val * 4);
        printf("%s\t", arr[i].filename);
    }
    printf("\n");
}

// Listing all information of files with block sizes also
void mylsls()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    long long int sum = 0, val = 0;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = arr[i].size / 4096 + 1;
        }
        sum += val * 4;
    }
    printf("total %lld\n", sum);
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        long long int val;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = (arr[i].size / 4096) + 1;
        }
        printf("%4lld  ", val * 4);
        printf("%c", arr[i].parr[0]);
        printf("%c", arr[i].parr[1]);
        printf("%c", arr[i].parr[2]);
        printf("%c", arr[i].parr[3]);
        printf("%c", arr[i].parr[4]);
        printf("%c", arr[i].parr[5]);
        printf("%c", arr[i].parr[6]);
        printf("%c", arr[i].parr[7]);
        printf("%c", arr[i].parr[8]);
        printf("%c  ", arr[i].parr[9]);
        printf("%d  ", arr[i].link);
        printf("%s  ", arr[i].owner);
        printf("%s  ", arr[i].group);
        printf("%7lld  ", arr[i].size);
        printf("%9s  ", arr[i].modification_time);
        printf("%s  ", arr[i].filename);
        printf("\n");
    }
}

// Lists the filenames sorted eith respect to size
void mylsS()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (arr[i].size >= arr[j].size)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        printf("%s  ", arr[i].filename);
    }
    printf("\n");
}

// Lists all the file's info sorted by size
void mylslS()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (arr[i].size >= arr[j].size)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    long long int sum = 0, val = 0;
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        if (arr[i].size % 4096 == 0)
        {
            val = arr[i].size / 4096;
        }
        else
        {
            val = arr[i].size / 4096 + 1;
        }
        sum += val * 4;
    }
    printf("total %lld\n", sum);
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        printf("%c", arr[i].parr[0]);
        printf("%c", arr[i].parr[1]);
        printf("%c", arr[i].parr[2]);
        printf("%c", arr[i].parr[3]);
        printf("%c", arr[i].parr[4]);
        printf("%c", arr[i].parr[5]);
        printf("%c", arr[i].parr[6]);
        printf("%c", arr[i].parr[7]);
        printf("%c", arr[i].parr[8]);
        printf("%c  ", arr[i].parr[9]);
        printf("%d  ", arr[i].link);
        printf("%s  ", arr[i].owner);
        printf("%s  ", arr[i].group);
        printf("%7lld  ", arr[i].size);
        printf("%9s  ", arr[i].modification_time);
        printf("%s  ", arr[i].filename);
        printf("\n");
    }
}

// Listing all file including the ones starting with "."
void mylsa()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
        {
            printf("\033[0;34m%s\033[0m ", arr[i].filename);
        }
        else
        {
            printf("%s  ", arr[i].filename);
        }
    }
    printf("\n");
}

// Lists files seperated by commas
void mylsm()
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            char temp1[4096];
            char temp2[4096];
            strcpy(temp1, arr[i].filename);
            strcpy(temp2, arr[j].filename);

            lower(temp1);
            lower(temp2);

            if (strcmp(temp1, temp2) > 0)
            {
                struct info temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for (int i = 0; i < count; i++)
    {
        if (arr[i].filename[0] == '.')
            continue;
        printf("%s", arr[i].filename);
        if(i!=(count-1)){
            printf(", ");
        }
    }
    printf("\n");
}