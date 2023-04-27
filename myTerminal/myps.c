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
#include <stdbool.h>

//Lists the running processes
void myps()
{
    DIR *directory;
    struct dirent *directoryptr;
    directory = opendir("/proc");
    int i, file1, file2;
    unsigned long utime, stime;
    char flag;
    char *tty;
    char cmd[512], tty_present[512], time[512], path[512];
    FILE *file;

    file1 = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_present, "%s", ttyname(file1));
    printf("%5s %s\t%8s %s \n", "PID", "TTY", "TIME", "CMD");

    while ((directoryptr = readdir(directory)) != NULL)
    {
        flag = 1;
        for (int i = 0; directoryptr->d_name[i]; i++)
        {
            if (!isdigit(directoryptr->d_name[i]))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            sprintf(path, "/proc/%s/fd/0", directoryptr->d_name);
            file2 = open(path, O_RDONLY);
            tty = ttyname(file2);
            if (tty && strcmp(tty, tty_present) == 0)
            {
                sprintf(path, "/proc/%s/stat", directoryptr->d_name);
                file = fopen(path, "r");
                fscanf(file, "%d%s%c%c%c", &i, cmd, &flag, &flag, &flag);
                cmd[strlen(cmd) - 1] = '\0';
                for (int i = 0; i < 11; i++)
                {
                    fscanf(file, "%lu", &utime);
                }
                fscanf(file, "%lu", &stime);
                utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
                sprintf(time, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                printf("%5s %s\t%8s %s \n", directoryptr->d_name, tty + 5, time, cmd + 1);
                fclose(file);
            }
            close(file2);
        }
    }
    close(file1);
}

//Lists all the processes including the ones running in the background
void mypse()
{
    DIR *directory;
    struct dirent *directoryptr;
    directory = opendir("/proc");
    int i, file1, file2;
    unsigned long int utime, stime;
    char flag;
    char *tty;
    char cmd[512], tty_present[512], time[512], path[512], path2[512];
    FILE *file;

    file1 = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_present, "%s", ttyname(file1));
    printf("%5s %5s\t%8s %s \n", "PID", "TTY", "TIME", "CMD");

    while ((directoryptr = readdir(directory)) != NULL)
    {
        flag = 1;
        for (int i = 0; directoryptr->d_name[i]; i++)
        {
            if (!isdigit(directoryptr->d_name[i]))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            sprintf(path, "/proc/%s/stat", directoryptr->d_name);
            file = fopen(path, "r");
            fscanf(file, "%d%s%c%c%c", &i, cmd, &flag, &flag, &flag);
            cmd[strlen(cmd) - 1] = '\0';
            for (int i = 0; i < 11; i++)
            {
                fscanf(file, "%lu", &utime);
            }
            fscanf(file, "%lu", &stime);

            sprintf(path2, "/proc/%s/fd/0", directoryptr->d_name);
            file2 = open(path2, O_RDONLY);
            tty = ttyname(file2);
            if (tty == NULL)
            {
                tty = "12345?";
            }
            utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
            sprintf(time, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
            printf("%5s %5s         %8s %s \n", directoryptr->d_name, tty + 5, time, cmd + 1);
            fclose(file);
        }
    }
    close(file1);
}

//Lists processes without session leaders
void mypsa()
{
    DIR *dir;
    struct dirent *entry;
    FILE *file;
    int file2, file1;
    char *tty, flag;
    char line[512], cmd[512], time_s[512], path[512], uid[512], tty_present[512], state;
    int pid, ppid, c, sz, rss, psr, sid, ttynr;
    unsigned long utime, stime;
    long long starttime;

    dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("%5s %s\t %8s %s\n", "PID", "TTY", "TIME", "CMD");
    file1 = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_present, "%s", ttyname(file1));

    while ((entry = readdir(dir)) != NULL)
    {
        flag = 1;
        for (int i = 0; entry->d_name[i]; i++)
        {
            if (!isdigit(entry->d_name[i]))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            sprintf(path, "/proc/%s/stat", entry->d_name);
            file = fopen(path, "r");
            if (file)
            {
                sprintf(path, "/proc/%s/fd/0", entry->d_name);
                file2 = open(path, O_RDONLY);
                tty = ttyname(file2);
                if (tty && strcmp(tty, tty_present) == 0)
                {
                    fgets(line, sizeof(line), file);
                    fclose(file);
                    sscanf(line, "%d %s %c %d %*s %d %d %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %d %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %d",
                           &pid, cmd, &state, &ppid, &sid, &ttynr, &utime, &stime, &starttime, &sz, &rss, &psr, &c);
                    if (tty == NULL)
                    {
                        tty = "12345?";
                    }
                    cmd[strlen(cmd) - 1] = '\0';
                    utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
                    sprintf(time_s, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                    if (sid == pid)
                        continue;
                    else
                    {
                        printf("%5d %s\t %8s %s\n", pid, tty + 5, time_s, cmd + 1);
                    }
                }
            }
        }
    }
    closedir(dir);
}

//Lists processes with extra information
void mypsf()
{
    DIR *dir;
    struct dirent *entry;
    FILE *file;
    int file2, file1;
    char *tty, flag;
    char line[512], cmd[512], time_s[512], path[512], tty_present[512], state, file_s[512];
    int pid, ppid, c, rss, psr, sid, ttynr, uid;
    unsigned long utime, stime;
    long long starttime, sz;
    dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("%9s %5s %5s %s  %7s %6s %8s %4s %6s   %6s %20s\n", "UID", "PID", "PPID", "C", "SZ", "RSS", "PSR", "STIME", "TTY", "TIME", "CMD");
    file1 = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_present, "%s", ttyname(file1));

    while ((entry = readdir(dir)) != NULL)
    {
        struct passwd *pw = (struct passwd *)malloc(sizeof(struct passwd));
        flag = 1;
        for (int i = 0; entry->d_name[i]; i++)
        {
            if (!isdigit(entry->d_name[i]))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            sprintf(path, "/proc/%s/stat", entry->d_name);
            file = fopen(path, "r");
            if (file)
            {
                sprintf(path, "/proc/%s/fd/0", entry->d_name);
                file2 = open(path, O_RDONLY);
                tty = ttyname(file2);
                if (tty && strcmp(tty, tty_present) == 0)
                {
                    fgets(line, sizeof(line), file);
                    fclose(file);
                    sscanf(line, "%d %s %c %d %*s %d %d %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %lld %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %d",
                           &pid, cmd, &state, &ppid, &sid, &ttynr, &utime, &stime, &starttime, &sz, &rss, &psr, &c);
                    sprintf(file_s, "/proc/%d/status", pid);
                    FILE *filetemp = fopen(file_s, "r");
                    while (fgets(line, sizeof(line), filetemp))
                    {
                        if (strncmp(line, "Uid:", 4) == 0)
                        {
                            sscanf(line, "Uid:\t%d", &uid);
                            break;
                        }
                    }
                    pw = getpwuid(uid);
                    char *temp = pw->pw_name;
                    if (tty == NULL)
                    {
                        tty = "12345?";
                    }
                    cmd[strlen(cmd) - 1] = '\0';
                    utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
                    sprintf(time_s, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                    printf("%9s %5d %5d %d %7lld %6d %8d %4ld  %6s %6s %20s\n", temp, pid, ppid, c, sz, rss, psr, stime, tty + 5, time_s, cmd + 1);
                }
            }
        }
    }
    closedir(dir);
}

//Lists processes similar to -a but with extra information
void mypsaf()
{
    DIR *dir;
    struct dirent *entry;
    FILE *file;
    int file2, file1;
    char *tty, flag;
    char line[512], cmd[512], time_s[512], path[512], file_s[512], tty_present[512], state;
    int pid, ppid, c, rss, psr, sid, ttynr, uid;
    unsigned long utime, stime;
    long long starttime, sz;

    dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("%9s %5s %5s %s  %7s %6s %8s %4s %6s   %6s %20s\n", "UID", "PID", "PPID", "C", "SZ", "RSS", "PSR", "STIME", "TTY", "TIME", "CMD");
    file1 = open("/proc/self/fd/0", O_RDONLY);
    sprintf(tty_present, "%s", ttyname(file1));

    while ((entry = readdir(dir)) != NULL)
    {
        struct passwd *pw = (struct passwd *)malloc(sizeof(struct passwd));
        flag = 1;
        for (int i = 0; entry->d_name[i]; i++)
        {
            if (!isdigit(entry->d_name[i]))
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            sprintf(path, "/proc/%s/stat", entry->d_name);
            file = fopen(path, "r");
            if (file)
            {
                sprintf(path, "/proc/%s/fd/0", entry->d_name);
                file2 = open(path, O_RDONLY);
                tty = ttyname(file2);
                if (tty && strcmp(tty, tty_present) == 0)
                {
                    fgets(line, sizeof(line), file);
                    fclose(file);
                    sscanf(line, "%d %s %c %d %*s %d %d %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %lld %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %d",
                           &pid, cmd, &state, &ppid, &sid, &ttynr, &utime, &stime, &starttime, &sz, &rss, &psr, &c);
                    sprintf(file_s, "/proc/%d/status", pid);
                    FILE *filetemp = fopen(file_s, "r");
                    while (fgets(line, sizeof(line), filetemp))
                    {
                        if (strncmp(line, "Uid:", 4) == 0)
                        {
                            sscanf(line, "Uid:\t%d", &uid);
                            break;
                        }
                    }
                    pw = getpwuid(uid);
                    char *temp = pw->pw_name;
                    if (tty == NULL)
                    {
                        tty = "12345?";
                    }
                    cmd[strlen(cmd) - 1] = '\0';
                    utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
                    sprintf(time_s, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                    if (sid == pid)
                        continue;
                    else
                    {
                        printf("%9s %5d %5d %d %7lld %6d %8d %4ld  %6s %6s %20s\n", temp, pid, ppid, c, sz, rss, psr, stime, tty + 5, time_s, cmd + 1);
                    }
                }
            }
        }
    }
    closedir(dir);
}

//Lists processes like -e but with extra information
void mypsef()
{
    DIR *dir;
    struct dirent *entry;
    FILE *file;
    int file2;
    char *tty;
    char line[512], cmd[512], time_s[512], path[512], path2[512], file_s[512], state;
    int pid, ppid, c, rss, psr, sid, ttynr, uid;
    unsigned long utime, stime;
    long long int starttime, sz;

    dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    printf("%9s %5s %5s %s  %15s %10s %8s %4s %6s   %6s %10s\n", "UID", "PID", "PPID", "C", "SZ", "RSS", "PSR", "STIME", "TTY", "TIME", "CMD");

    while ((entry = readdir(dir)) != NULL)
    {
        struct passwd *pw = (struct passwd *)malloc(sizeof(struct passwd));
        if (isdigit(*entry->d_name))
        {
            sprintf(path, "/proc/%s/stat", entry->d_name);
            file = fopen(path, "r");
            if (file)
            {
                fgets(line, sizeof(line), file);
                fclose(file);
                sscanf(line, "%d %s %c %d %*s %d %d %*s %*s %*s %*s %*s %*s %lu %lu %*s %*s %*s %*s %*s %*s %llu %lld %d %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d %d",
                       &pid, cmd, &state, &ppid, &sid, &ttynr, &utime, &stime, &starttime, &sz, &rss, &psr, &c);
                sprintf(file_s, "/proc/%d/status", pid);
                FILE *filetemp = fopen(file_s, "r");
                while (fgets(line, sizeof(line), filetemp))
                {
                    if (strncmp(line, "Uid:", 4) == 0)
                    {
                        sscanf(line, "Uid:\t%d", &uid);
                        break;
                    }
                }
                pw = getpwuid(uid);
                char *temp = pw->pw_name;
                sprintf(path2, "/proc/%s/fd/0", entry->d_name);
                file2 = open(path2, O_RDONLY);
                tty = ttyname(file2);
                if (tty == NULL)
                {
                    tty = "12345?";
                }
                cmd[strlen(cmd) - 1] = '\0';
                utime = (int)((double)(utime + stime) / sysconf(_SC_CLK_TCK));
                sprintf(time_s, "%02lu:%02lu:%02lu", (utime / 3600) % 3600, (utime / 60) % 60, utime % 60);
                printf("%9s %5d %5d %d %15lld %10d %8d %4ld  %6s %6s %10s\n", temp, pid, ppid, c, sz, rss, psr, stime, tty + 5, time_s, cmd + 1);
            }
        }
    }
    closedir(dir);
}