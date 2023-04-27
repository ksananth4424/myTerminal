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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Renaming the files
void mymv(char *f1, char *f2)
{
    if (access(f1, F_OK) != 0) {
        printf("mv: cannot stat '%s': No such file or directory\n", f1);
        return;
    }
    if (rename(f1, f2) != 0) {
        printf("mv: cannot move '%s' to '%s': \n", f1, f2);
        return;
    }
}

//Renaming the files and printing what is being done
void mymvv(char *f1, char *f2)
{
    if (access(f1, F_OK) != 0) {
        printf("mv: cannot stat '%s': No such file or directory\n", f1);
        return;
    }
    if (rename(f1, f2) != 0) {
        printf("mv: cannot move file\n");
        return;
    }
    printf("renamed: '%s' -> '%s'\n",f1,f2);
}

//Gives a prompt before overwriting
void mymvi(char *f1, char *f2)
{
    if (access(f1, F_OK) != 0) {
        printf("mv: cannot stat '%s': No such file or directory\n", f1);
        return;
    }
    if(access(f2,F_OK)==0){
        printf("mv: overwrite '%s'? ",f2);
        char c;
        scanf("%c",&c);
        if(c!='Y' && c!='y'){
            return;
        }
    }
    if (rename(f1, f2) != 0) {
        printf("mv: cannot move file\n");
        return;
    }
    
}

//Does not overwrite if the file already exists
void mymvn(char *f1, char *f2)
{
    if (access(f1, F_OK) != 0) {
        printf("mv: cannot stat '%s': No such file or directory\n", f1);
        return;
    }
    if(access(f2,F_OK)==0){
        return;
    }
    if (rename(f1, f2) != 0) {
        printf("mv: cannot move file\n");
        return;
    }   
}

//Forces the overwriting if the file already exists, no prompt will be seen
void mymvf(char *f1, char *f2)
{
    if (access(f1, F_OK) != 0) {
        printf("mv: cannot stat '%s': No such file or directory\n", f1);
        return;
    }
    if (rename(f1, f2) != 0) {
        printf("mv: cannot move '%s' to '%s': \n", f1, f2);
        return;
    }
}