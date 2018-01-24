#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <cshell.h>

//This is the list of built in cmds
char *built_cmnds[] = {"pwd","echo","cd","ls","pinfo", "quit", "setenv", "unsetenv",
 "jobs", "kjob", "fg", "bg" ,"overkill"};


//Helper to run a function based on its position in the list
int exec_builtin(int id,char ** args)
{
    if (id == 0)return pwd(args);
    else if (id ==1 )
        return echo(args);
    else if (id == 2)
        return change_dir(args);
    else if (id ==3 )
        return ls(args);
    else if ( id == 4)
        return pinfo_id(args);
    else if (id == 5)
        return exit_shell(args);
    else if (id == 6)
        return setVar(args);
    else if (id == 7)
        return unsetVar(args);
    else if (id == 8)
        return jobs(args);
    else if (id == 9)
        return kjob(args);
    else if (id == 10)
        return fg(args);
    else if (id == 11)
        return bg(args);
    else if (id == 12)
        return overkill(args);
    return 0;
}

//Returns the current length of builtin commands 
int num_builtins() {
    return sizeof(built_cmnds) / sizeof(char *);
}

int execute(char ** args)
{    
    //Check if any command was entered
    if (args[0] == NULL){

        return 1;
    }
    int i =0;
    char * cur;
    for ( cur = args[i];cur;cur=args[++i])
        if (strncmp(cur,"|",1)==0)return piping(args);

    //Check if it was a built in command
    int n =num_builtins();
    for (int i=0; i <n;i++){
        if(!strcmp(args[0], built_cmnds[i]))
            return exec_builtin(i,args);
    }

    return launch(args);

}
