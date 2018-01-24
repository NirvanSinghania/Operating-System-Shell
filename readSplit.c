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



#define TOKEN_BUFFERSIZE 64



char **split_line(char *line, char * TOK_DELIM)
{
    if (TOK_DELIM==NULL)
        TOK_DELIM=" \t\r\n\a";
        
    int bufsize = TOKEN_BUFFERSIZE, position = 0;
    char ** tokens =(char **) malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    for(token = strtok(line, TOK_DELIM);token;)
    {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += TOKKEN_BUFFERSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
char * read_line()
{
    char * ln = NULL;
    size_t bufsize=0;
    getline(&ln,&bufsize,stdin);
    return ln;
}
