#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "splitCmdStr.h"

/* split command string to args array, end with NULL */
char **split_cmd_str(char *cmd_str, char **cmd_args)
{
    int i = 0;
    char *p = strtok(cmd_str, DELIM);

    /* plus 1 for end arg NULL */
    cmd_args = (char **)malloc(sizeof(char *) * (MAX_CMD_ARGS + 1));
    
    while (p != NULL)
    {
        if(i >= MAX_CMD_ARGS)
        {
            printf("Too many arguments, MAX_CMD_ARGS = %d\n", MAX_CMD_ARGS);
            break;
        }
        cmd_args[i++] = p;
        p = strtok(NULL, DELIM);
    }
    cmd_args[i] = NULL;
    return cmd_args;
}
