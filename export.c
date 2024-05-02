#include <stdio.h>
#include <stdlib.h>
#include "export.h"

void export_env_var(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("export: too few or too many arguments\nusage: export VAR=VALUE\n");
	return;
    } 

    if (putenv(argv[1]) != 0)
    {
        printf("export: putenv error\n");
	return;
    }
}
