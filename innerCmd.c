#include "innerCmd.h"
#include "export.h"
#include <stdlib.h>
#include <string.h>

/* shell internal commands */
const char* INTERNAL_COMMANDS[] = {
	"export",
	"exit",
};

enum INTERNAL_COMMANDS {
	EXPORT, /* 0 */
	EXIT,
};

/* 
	get the index of the internal command.
	if it exist, return the index of the command in INTERNAL_COMMANDS.
	otherwise, return -1.
*/
int get_index_internal_command(char *cmd)
{
	int i;
	for (i = 0; i < sizeof(INTERNAL_COMMANDS) / sizeof(INTERNAL_COMMANDS[0]); i++)
	{
		if (strcmp(cmd, INTERNAL_COMMANDS[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

/* 
	do the internal command.
	if it is internal command, do the command and return 1.
	otherwise, return 0.
*/
int do_inner_command(int cmd_argc, char **cmd_argv)
{
	int isInnerCmd;
	int index = get_index_internal_command(cmd_argv[0]);

    	switch (index)
	{
		case EXPORT:
			/* export environment variable */
			export_env_var(cmd_argc, cmd_argv);
			isInnerCmd = 1;
			break;
		case EXIT:
			/* exit shell */
			exit(0);
		default:
			/* not inner command */
			isInnerCmd = 0;
			break;
	}

	return isInnerCmd;
}
