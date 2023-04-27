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

//Searching keyword in given file
void mygrep(char *f1,char *f2) {
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    char line[1500];
    int lnum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            printf("%s: %s",f2, line);
        }
        lnum++;
    }
    fclose(file);
}

//prints the number of lines in which the keyword has appeared
void mygrepc(char *f1, char *f2){
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    int count=0;
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            count++;
        }
        linenum++;
    }
    fclose(file);
    printf("\033[0;35m%s\033[0m:%d\n",f2, count);
}

//The search stops as soon as limit given is reached
void mygrepm(char *f1,char *f2,int f3) {
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    int count=0;
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            printf("\033[0;35m%s\033[0m:%s",f2,line);
            count++;
            if(count==f3)return;
        }
        linenum++;
    }
    fclose(file);
}

//Prints the line number with the line where keyword is found
void mygrepn(char *f1, char *f2){
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", f2);
    }
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            printf("\033[0;35m%s\033[0m: \033[;32m%d\033[0m:%s",f2,linenum, line);
        }
        linenum++;
    }
    fclose(file);
}

//Supresses all the error messages
void mygreps(char *f1,char *f2) {
    FILE *file = fopen(f2, "r");
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            printf("\033[0;35m%s\033[0m:%s",f2,line);
        }
        linenum++;
    }
    fclose(file);
}

//Prints the filename where the keyword is found
void mygrepl(char *f1, char *f2){
    bool flag=false;
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            flag=true;
        }
        linenum++;
    }
    fclose(file);
    if(flag){
        printf("\033[0;35m%s\033[0m\n",f2);
    }
}

//Prints the lines which does not contain the keyword
void mygrepv(char *f1,char *f2) {
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) == NULL) {
            printf("\033[0;35m%s\033[0m: %s",f2, line);
        }
        linenum++;
    }
    fclose(file);
    printf("\n");
}

//Prints the file which does not contain the key word
void mygrepL(char *f1, char *f2){
    bool flag=false;
    FILE *file = fopen(f2, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", f2);
    }
    char line[1500];
    int linenum = 1;
    while (fgets(line, 1500, file)) {
        if (strstr(line, f1) != NULL) {
            flag=true;
        }
        linenum++;
    }
    fclose(file);
    if(!flag){
        printf("\033[0;35m%s\033[0m\n",f2);
    }
}