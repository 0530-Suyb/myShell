#ifndef _SPLIT_CMD_STR_H_
#define _SPLIT_CMD_STR_H_

#define MAX_CMD_ARGS 2
#define DELIM " "

char **split_cmd_str(char *cmd_str, char **cmd_args);

#endif
