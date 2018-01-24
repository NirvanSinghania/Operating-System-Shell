#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "cshell.h"

int sigsize = 0;

void setshellid(int cur_id)
{
	char temp[10];
	int j = 0;
	for (int i=cur_id;i>0;i=i/10) temp[j++] = (i%10) + '0';
	temp[j] = '\0';
	int k = 0;
	for (int i=j-1;i>=0;i--) shellid[k++] = temp[i];
	shellid[k] = '\0';
}

int main(int argc, char const *argv[])
{
	
	int cur_id = getpid();
	setshellid(cur_id);

    char * myline;
    char ** arg_array;
    char ** args;
    getcwd(myhome, sizeof(myhome));
    myname = getpwuid(getuid());
    gethostname(hostname, 29);

    print_prompt();

    // Signal handler for CTRL-C
    signal(SIGINT, signalhandler);
    signal(SIGTSTP, sigz);
    
    while(1)
    {
        myline = read_line();
        //if (strncmp(myline,"exit",4)==0)break;
        arg_array = split_line(myline,";");
        for(int i=0;arg_array[i];i++)
        {    args = split_line(arg_array[i],NULL);
            execute(args);
        }
        print_prompt();  
    }
    return 0;
}
