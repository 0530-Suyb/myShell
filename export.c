#include <stdio.h>
#include <stdlib.h>
#include "export.h"

void export_env_var(char **cmd_args, int num)
{
    if (num != 2)
    {
        printf("export: too few or too many arguments\nusage: export VAR=VALUE\n");
	return;
    } 

    if (putenv(cmd_args[1]) != 0)
    {
        printf("export: putenv error\n");
	return;
    }
}
