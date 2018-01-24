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
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <sys/utsname.h>


#include "cshell.h"


int launch(char **args)
{
    
    pid_t pid, wpid, ind=0;
    int status, back_ground=0;

    //Check if background process is to be run
    //by finding if there is an & at the end
    
    for(int i=1;args[i];i++)
        ind=i;
    if (ind && strcmp(args[ind],"&")==0)back_ground=1;

    pid=fork();
    // parent process in background adding it to the proc array
    if (pid > 0 && back_ground == 1){
        signal(SIGCHLD, sigh);
        sigsize++;
        proc[sigsize] = (process *)(malloc(sizeof(process)));
        proc[sigsize]->num = pid;
        strcpy((proc[sigsize])->pname, args[0]);
        proc[sigsize]->state = 1;
        printf("\n");

        return 1;
    } 
 
    //Error handler
    if ((pid)<0)
    {

        fprintf(stderr, "Error cannot initiate process!\n");
    }
    else if (pid==0)
    {
        args = redirect(args);
        //Child process

        if(execvp(args[0],args) == -1)
        {
          fprintf(stderr, "Error in executing command\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);


    }

    else {
        // Parent process
        // If process is foreground then wait else return
        if (!back_ground)
        {
             foreground_id = pid;
            curname = args[0];
            signal(SIGTSTP, sigz);
            
            wpid = waitpid(pid, &status, WUNTRACED);
            // while (!WIFEXITED(status) && !WIFSIGNALED(status));
            //printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
        }
    }
    return 1;
}
