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
#include <errno.h>
#include <fcntl.h>

//copy files
int mycp(char *f1, char *f2)
{
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    files[0] = open(f1, O_RDONLY);
    if (files[0] == -1) /* Check if file opened */
        return -1;
    files[1] = open(f2, O_RDWR | O_CREAT, S_IRUSR);

    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        return -1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

    return 0;
}

//copy file
void copy_file(char *src_path, char *dst_path)
{
    FILE *src_file, *dst_file;
    char buffer[BUFSIZ];
    size_t size;

    src_file = fopen(src_path, "rb");
    if (src_file == NULL)
    {
        fprintf(stderr, "Error: cannot open source file %s\n", src_path);
        return;
    }

    dst_file = fopen(dst_path, "wb");
    if (dst_file == NULL)
    {
        fprintf(stderr, "Error: cannot create destination file %s\n", dst_path);
        fclose(src_file);
        return;
    }

    while ((size = fread(buffer, 1, BUFSIZ, src_file)) > 0)
    {
        fwrite(buffer, 1, size, dst_file);
    }

    fclose(src_file);
    fclose(dst_file);
}

//copy directories recurcively 
void copy_directory(const char *src_path, const char *dst_path)
{
    DIR *directory;
    struct dirent *directoryptr;
    struct stat st;
    char src_file_path[1000], dst_file_path[1000];

    if ((directory = opendir(src_path)) == NULL)
    {
        fprintf(stderr, "Error: Failed to open source directory '%s': %s\n", src_path, strerror(errno));
        return;
    }

    if (mkdir(dst_path, 0755) == -1 && errno != EEXIST)
    {
        closedir(directory);
        fprintf(stderr, "Error: Failed to create destination directory '%s': %s\n", dst_path, strerror(errno));
        return;
    }

    while ((directoryptr = readdir(directory)) != NULL)
    {
        if (strcmp(directoryptr->d_name, ".") == 0 || strcmp(directoryptr->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(src_file_path, sizeof(src_file_path), "%s/%s", src_path, directoryptr->d_name);
        snprintf(dst_file_path, sizeof(dst_file_path), "%s/%s", dst_path, directoryptr->d_name);

        if (lstat(src_file_path, &st) == -1)
        {
            fprintf(stderr, "Error: Failed to stat source file '%s': %s\n", src_file_path, strerror(errno));
            continue;
        }

        if (S_ISREG(st.st_mode))
        {
            copy_file(src_file_path, dst_file_path);
        }
        else if (S_ISDIR(st.st_mode))
        {
            copy_directory(src_file_path, dst_file_path);
        }
        else
        {
            fprintf(stderr, "Warning: Skipped unsupported file '%s'\n", src_file_path);
        }
    }

    closedir(directory);
}

//copy multiple files from one directory to another directory
void mycpm(char *splits[], int a)
{
    for(int i=1;i<a-1;i++){
        char dest_path[512];
        snprintf(dest_path,sizeof(dest_path),"%s/%s",splits[a-1],splits[i]);
        copy_file(splits[i],dest_path);
    }
}

//creates herdlink between files
void mycpl(char *f1, char *f2)
{
    struct stat st;
    if (lstat(f1, &st) == -1)
    {
        perror("lstat");
    }

    if (S_ISREG(st.st_mode))
    {
        if (link(f1, f2) == -1)
        {
            perror("link");
        }
    }
    else if (S_ISDIR(st.st_mode))
    {
        fprintf(stderr, "cp: omitting directory '%s'\n", f1);
    }
    else
    {
        fprintf(stderr, "cp: invalid file type '%s'\n", f1);
    }
}

//creates symbolic links between files
void mycps(char *f1, char *f2)
{
    if (symlink(f1, f2))
    {
        perror("Error creating symbolic link");
    }
}

//copy files and tell what is being done
void mycpv(char *f1, char *f2)
{
    char size[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    files[0] = open(f1, O_RDONLY);
    if (files[0] == -1) /* Check if file opened */
        perror("Opening file");
    files[1] = open(f2, O_RDWR | O_CREAT, S_IRUSR);

    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        perror("Opening file");
    }

    while ((count = read(files[0], size, sizeof(size))) != 0)
        write(files[1], size, count);

    printf("'%s' -> '%s'\n", f1, f2);
}