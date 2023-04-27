#include "myShell.h"
int main()
{
    printf("-----------------------------------------------------------------------\n");
    printf("\t\t\tMY SHELL - K S Ananth\n");
    printf("-----------------------------------------------------------------------\n");
    while (1)
    {
        char line[150];
        user = getlogin();
        if (user == NULL)
        {
            printf("USER not found\n");
            exit(EXIT_FAILURE);
        }
        strcpy(line, "\001\033[;32m\002");
        strcat(line, user);
        strcat(line, "@\001\033[0m\002");
        if (gethostname(host, 200) != 0)
        {
            printf("Host not found\n");
            exit(EXIT_FAILURE);
        }
        strcat(line, "\001\033[;32m\002");
        strcat(line, host);
        strcat(line, "\001\033[0m\002");
        strcat(line, ":");
        char cwd[2048];
        getcwd(cwd, sizeof(cwd));
        strcat(line, "\001\033[;34m~\002");
        strcat(line, cwd);
        strcat(line, "\001\033[0m\002");
        strcat(line, "$ ");

        //Taking input
        command = readline(line);
        char copy[1000]="Hello this is myShell made by KSA!";
        int a=split(splits, copy);
        strcpy(copy, command);

        //Splitting the command
        a=split(splits,copy);
        if (splits[0] == NULL)
            continue;
        if (strlen(command) >= 1)
        {
            add_history(command);
        }

        //exit the program
        if (!strcmp(splits[0], "exit"))
        {
            printf("-----------------------------------------------------------------------\n");
            printf("\t\t\tThank you - Good Bye\n");
            printf("-----------------------------------------------------------------------\n");
            break;
        }

        //help
        else if (!strcmp(splits[0], "help"))
        {
            system("bash -c help");
        }

        //changing directory
        else if (command[0] == 'c' && command[1] == 'd' && command[2] == ' ')
        {
            char temp[1000];
            int i = 3, j = 1;
            while (command[i] != '\0')
            {
                temp[j++] = command[i++];
            }
            temp[0] = '/';
            temp[j] = '\0';
            strcat(cwd, temp);
            chdir(cwd);
        }

        //myls help
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "--help") && a == 2)
        {
            size_t length = 0;
            char *line;
            FILE *file = fopen("help/myls.txt", "r");
            while (getline(&line, &length, file) != -1)
            {
                printf("%s", line);
            }
            printf("\n");
        }

        //myls
        else if (!strcmp(splits[0], "myls") && a == 1)
        {
            store(cwd);
            myls();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-l") && a == 2)
        {
            store(cwd);
            mylsl();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-s") && a == 2)
        {
            store(cwd);
            mylss();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-ls") && a == 2)
        {
            store(cwd);
            mylsls();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-S") && a == 2)
        {
            store(cwd);
            mylsS();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-lS") && a == 2)
        {
            store(cwd);
            mylslS();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-a") && a == 2)
        {
            store(cwd);
            mylsa();
        }
        else if (!strcmp(splits[0], "myls") && !strcmp(splits[1], "-m") && a == 2)
        {
            store(cwd);
            mylsm();
        }

        //ps help
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "--help") && a == 2)
        {
            size_t length = 0;
            char *line;
            FILE *file = fopen("help/myps.txt", "r");
            while (getline(&line, &length, file) != -1)
            {
                printf("%s", line);
            }
            printf("\n");
        }

        //ps
        else if (!strcmp(splits[0], "myps") && a == 1)
        {
            myps();
        }
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "-e") && a == 2)
        {
            mypse();
        }
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "-a") && a == 2)
        {
            mypsa();
        }
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "-F") && a == 2)
        {
            mypsf();
        }
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "-aF") && a == 2)
        {
            mypsaf();
        }
        else if (!strcmp(splits[0], "myps") && !strcmp(splits[1], "-eF") && a == 2)
        {
            mypsef();
        }

        //mv help
        else if (!strcmp(splits[0], "mymv") && !strcmp(splits[1], "--help") && a == 2)
        {
            size_t length = 0;
            char *line;
            FILE *file = fopen("help/mymv.txt", "r");
            while (getline(&line, &length, file) != -1)
            {
                printf("%s", line);
            }
            printf("\n");
        }

        //mv
        else if (!strcmp(splits[0], "mymv") && a == 3)
        {
            mymv(splits[1], splits[2]);
        }
        else if (!strcmp(splits[0], "mymv") && !strcmp(splits[1], "-v") && a == 4)
        {
            mymvv(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mymv") && !strcmp(splits[1], "-i") && a == 4)
        {
            mymvi(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mymv") && !strcmp(splits[1], "-n") && a == 4)
        {
            mymvn(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mymv") && !strcmp(splits[1], "-f") && a == 4)
        {
            mymvf(splits[2], splits[3]);
        }

        //cp help
        else if (!strcmp(splits[0], "mycp") && !strcmp(splits[1], "--help") && a == 2)
        {
            size_t length = 0;
            char *line;
            FILE *file = fopen("help/mycp.txt", "r");
            while (getline(&line, &length, file) != -1)
            {
                printf("%s", line);
            }
            printf("\n");
        }

        //cp
        else if (!strcmp(splits[0], "mycp") && a == 3)
        {
            if (mycp(splits[1], splits[2]) != 0)
            {
                printf("Command not executed!\n");
            }
        }
        else if (!strcmp(splits[0], "mycp") && !strcmp(splits[1], "-r") && a == 4)
        {
            copy_directory(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mycp") && !strcmp(splits[1], "-v") && a == 4)
        {
            mycpv(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mycp") && !strcmp(splits[1], "-l") && a == 4)
        {
            mycpl(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mycp") && !strcmp(splits[1], "-s") && a == 4)
        {
            mycps(splits[2], splits[3]);
        }
        else if (!strcmp(splits[0], "mycp"))
        {
            mycpm(splits, a);
        }

        //mygrep help
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "--help") && a == 2)
        {
            size_t length = 0;
            char *line;
            FILE *file = fopen("help/mygrep.txt", "r");
            while (getline(&line, &length, file) != -1)
            {
                printf("%s", line);
            }
            printf("\n");
        }

        //mygrep
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-c") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygrepc(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-m") && a >= 5)
        {
            for (int i = 4; i < a; i++)
            {
                mygrepm(splits[3], splits[i], atoi(splits[2]));
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-n") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygrepn(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-s") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygreps(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-l") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygrepl(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-v") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygrepv(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && !strcmp(splits[1], "-L") && a >= 4)
        {
            for (int i = 3; i < a; i++)
            {
                mygrepL(splits[2], splits[i]);
            }
        }
        else if (!strcmp(splits[0], "mygrep") && a >= 3)
        {
            for (int i = 2; i < a; i++)
            {
                mygrep(splits[1], splits[i]);
            }
        }
        else
        {
            printf("\n\t\t\tNOT A VALID COMMAND!!\n\n");
            // system(command);
        }
    }
    return 0;
}