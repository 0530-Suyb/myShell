#include "apue.h"
#include "export.h"

void export_env_var(char **cmd_args)
{
    if (sizeof(cmd_args) / sizeof(char *) != 3)
    {
        err_ret("export: too few or too many arguments\nusage: export VAR=VALUE");
    } 

    if (putenv(cmd_args[1]) != 0)
    {
        err_ret("export: putenv error");
    }
}