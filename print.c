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


void print_prompt()
{
    printf("%s@%s:",myname->pw_name,hostname);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        int ret = strcmp(cwd,myhome);
        if (ret==0)
            printf("~> ");
        else if (ret<0)
            printf("%s> ",cwd);
        else
        {
            int len =strlen(myhome);
            printf("~%s> ",cwd+len);
        }
    }
    else
        perror("error in accessing directory");
}

