#ifndef MYSHELL_H
#define MYSHELL_H
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

const unsigned char *command;
unsigned char *user;
unsigned char host[200];

//Splitting command
char *splits[100];
int split(char *splits[],unsigned char *command){
    char *token=strtok(command," ");
    int a=0;
    while(token!=NULL){
        splits[a++]=token;
        token=strtok(NULL," ");
    }
    return a;
}

//ps
void myps();
void mypse();
void mypsa();
void mypsf();
void mypsaf();
void mypsef();

//mv
void mymv(char *f1,char *f2); 
void mymvv(char *f1, char *f2);
void mymvi(char *f1, char *f2);
void mymvn(char *f1, char *f2);
void mymvf(char *f1, char *f2);

//cp
int mycp(char *f1, char *f2);
void mycpm(char *splits[],int a);
void copy_file(char *src_path, char *dst_path);
void copy_directory(const char *src_path, const char *dst_path);
void mycpl(char *f1,char *f2);
void mycps(char *f1, char *f2);
void mycpv(char *f1,char *f2);

//grep
void mygrep(char *f1,char *f2);
void mygrepc(char *f1, char *f2);
void mygrepm(char *f1,char *f2,int f3);
void mygrepn(char *f1, char *f2);
void mygreps(char *f1,char *f2);
void mygrepl(char *f1, char *f2);
void mygrepv(char *f1,char *f2);
void mygrepL(char *f1, char *f2);

//ls
void myls();
void mylsl();
void mylss();
void mylsls();
void mylsS();
void mylslS();
void mylsa();
void mylsm();
void store(char *cwd);
#endif