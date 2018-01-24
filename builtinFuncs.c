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
#include "cshell.h"


/*
    Function - "cd"
    Input - "Directory to change to "
    Output - "Terminal goes to the specified directory"
*/

int change_dir(char **args)
{

    if (args[1]==NULL)
    {           chdir(myhome);
        return 1;
    }
    if(args[1][0] == '~'){
        char path[1000];
        int j = 0;
        for(int i=0;myhome[i];i++){
            path[j++] = myhome[i];
        }
        path[j++] = '/';
        for (int i=1;args[1][i]!='\0';i++){
            path[j++] = args[1][i];
        }
        path[j++]='\0';
        if ( chdir(path)==-1)
            printf("Error! Directory does not exist\n");
    }

    else if(chdir(args[1])==-1)
        printf("Error! Directory does not exist part 2\n");

    return 1;
} 



/*
    Function - echo
    Input - A string 
    Output - It prints the string onto the terminal

*/
int echo(char ** args)
{
    if (args[1]==NULL)
    {
        printf("Nothing to print\n");
        return 1;
    }
    for(int i=1;args[i];i++)
        printf("%s ",args[i]);
    printf("\n");
    return 1;
}


/* 
    Function - pwd
    Input - Just command 
    Output - Current working directory

*/

int pwd(char **args){
    char cwd[1024];
    if (args[1] != NULL){
        printf("No such command exists\n");
        return 1;
    }
    printf("%s\n", getcwd(cwd, sizeof(cwd)));
    return 1;
}
int exit_shell(char ** args)
{
    printf("Visit again!!!!\n");
    exit(EXIT_SUCCESS);
    return 0;
}

int setVar(char **args){
    int argc = 0;
    while (args[argc]!=NULL)
        argc++;

    if (argc == 2 || argc == 3){
        if (strcmp(args[0], "setenv")){
            char  c;
            if (argc == 2) 
                if (setenv(args[1], &c, 1) != 0)
                    printf("Error in executing command\n"); 
            if (argc == 3)
                if (setenv(args[1], args[2], 1) != 0)
                    printf("Error in executing command\n");
        }
        // else{
        //  printf("No such command exits\n");
        // }
    }
    else {
        printf("Usage error\n");
        return 1;
    }
}

int unsetVar(char **args) {
    int argc = 0;
    while(args[argc])
        argc++;

    if (argc == 2) {
        if (unsetenv(args[1])!=0)
            printf("Error in executing command\n");
    }
    else {
        printf("Usage error\n");
    }
}

int jobs(char **args){
    int iter=1 , cnt =0;
    while(iter<=sigsize){


        if(proc[iter] && proc[iter]->state){
            cnt++;
            printf("[%d] ",  cnt );
            printf ("%s" , pinfostate(proc[iter]->num));
            printf(" %s ", (proc[iter])->pname );
            printf("[%d]\n", (proc[iter])->num );
            proc[cnt]= proc[iter];
        }
        iter++;
    }
    sigsize = cnt;




    return 1;
}

int kjob(char **args){
 
  if (args[1]==NULL || args[2]==NULL)
    perror("Usage: Error");
  
  int iter =1 ,cnt =0;
  int signum = atoi(args[2]), procnum =atoi(args[1]);
  while(iter <= sigsize)
  {
    if (proc[iter] && proc[iter]->state)cnt++;
    if (cnt == procnum)break;
    iter ++ ;
  }
  

  //Fix segmentation fault
  if(procnum>sigsize || proc[iter]==NULL || proc[iter]->state==0){
    printf("The process does not exist.\n" );
    return 1;
  }
  int id = proc[iter]->num;
  if (id == 9 || id== 2 || id == 15 )
   {
     proc[iter]=NULL;
     proc[iter]->state =0;
 }

  kill(id, signum); 

  return 1;
}

int fg(char **args){

    if(args[1]==NULL){
        printf("Usage: fg [process no.]\n");
    }
    int i =0;

    int procnum = atoi(args[1]);
    int iter = 1 ,  cnt = 0;
    while(iter <= sigsize)
    {
    if (proc[iter] && proc[iter]->state)cnt++;
    if (cnt == procnum)break;
    iter ++ ;
    }
    if(procnum>sigsize || proc[iter]==NULL || proc[iter]->state==0){
    perror("No such process exists.\n" );
    return 1;
    }

    
    int id = proc[iter]->num;
    proc[iter]= NULL;

    int status  = 0, lol = 1;
    pid_t wpid;
    if (kill(id ,18 )!=0)
        lol =1 ;
    wpid = waitpid(id, &status, WUNTRACED);
    //while (!WIFEXITED(status) && !WIFSIGNALED(status));
    
    return 1;
}

int bg(char **args){

    if(args[1]==NULL){
        printf("Usage: bg [process no.]\n");
    }
    int i=0;
    int procnum = atoi(args[1]);
    int iter = 1 ,  cnt = 0;
    while(iter <= sigsize)
    {
    if (proc[iter] && proc[iter]->state)cnt++;
    if (cnt == procnum)break;
    iter ++ ;
    }

    if(procnum>sigsize || proc[iter]==NULL || proc[iter]->state==0){
    perror("No such  process exists.\n" );
    return 1;
      }

    //kill(id, 18);
    int id = proc[iter]->num;
    kill(id, 18);
    return 1;
}
int overkill(char **args)
{

   for(int iter =1;iter <= sigsize ;iter++)
  {
    if(proc[iter])
    {
      if (kill(proc[iter]->num,9)!=0)
        perror("Error in killing process");
      proc[iter]=NULL;
    }
  }
  sigsize= 0;

  return 1;

}
