#include "redirect.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

/*
    redirect input and output.
    if redirect fail return -1.
    if success return the length of the new argv 
    which has removed redirect symbol and file name. 
*/
int redirect(int argc, char **argv)
{
    int i, j;
    int fd;
    int dup2_flag;

    for (i = 0; i < argc; )
    {
        if (strcmp(argv[i], ">") == 0) /* output redirect, cover */
        {
            if (i + 1 >= argc)
            {
                printf("redirect: no file to redirect\n");
                return -1;
            }

            fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                printf("redirect: open file %s err\n", argv[i + 1]);
                return -1;
            }

            dup2_flag = dup2(fd, STDOUT_FILENO);
            if (dup2_flag == -1)
            {
                close(fd);
                printf("redirect: dup2 err\n");
                return -1;
            }
        } 
        else if (strcmp(argv[i], ">>") == 0) /* output redirect, append */
        {
            if (i + 1 >= argc)
            {
                printf("redirect: no file to redirect\n");
                return -1;
            }

            fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
            {
                printf("redirect: open file %s err\n", argv[i + 1]);
                return -1;
            }

            dup2_flag = dup2(fd, STDOUT_FILENO);
            if (dup2_flag == -1)
            {
                close(fd);
                printf("redirect: dup2 err\n");
                return -1;
            }
        } 
        else if (strcmp(argv[i], "<") == 0) /* input redirect */
        {
            if (i + 1 >= argc)
            {
                printf("redirect: no file to redirect\n");
                return -1;
            }

            fd = open(argv[i + 1], O_RDONLY);
            if (fd == -1)
            {
                printf("redirect: open file %s err\n", argv[i + 1]);
                return -1;
            }

            dup2_flag = dup2(fd, STDIN_FILENO);
            if (dup2_flag == -1)
            {
                close(fd);
                printf("redirect: dup2 err");
                return -1;
            }
        } 
        else
        {
            /* not redirect symbol */
	    i++;
            continue;
        } 

        close(fd);
        
        /* remove redirect symbol and file name */
        argc = argc - 2;
        for (j = i; j < argc; j++)
        {
            argv[j] = argv[j + 2];
        }
        argv[argc] = NULL;
    }

    return argc;
}
