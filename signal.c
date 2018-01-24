#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include "cshell.h"

void signalhandler()
{
    printf("Terminator salvtion -Ctrl C \n");

}

void sigh(int signum)
{
    pid_t wpid;
    int procstatus;
    int status;
    wpid=waitpid(-1,&status,WNOHANG);
    if(wpid>0   && (WIFEXITED(status)!=0))
    {
        for(int i =1 ;i<= sigsize;i++)
        {
            if (proc[i]->num == wpid )
            {    proc[i]->state = 0;
                 break;
             }
        }   
        fprintf(stderr, "\nProcess with pid %d exited normally\n",wpid);
    }
    if(wpid >0 && WIFSIGNALED(status)!=0)
    {
        fprintf(stderr, "\nProcess with pid %d exited due to a user-defined signal\n",wpid);

    }
    return;

}
void sigz(int signum)
{
    pid_t wpid;
    int procstatus;
    int status;
    if (foreground_id == 0)
        return;
    if (kill(foreground_id ,19)<0)
        return;
     sigsize++;
    proc[sigsize] = (process *)(malloc(sizeof(process)));
    proc[sigsize]->num = foreground_id;
    strcpy((proc[sigsize])->pname, curname);
    proc[sigsize]->state = 1;
    foreground_id = 0;
    return;

}
