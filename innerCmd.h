#ifndef _INNER_CMD_H
#define _INNER_CMD_H

/* 
	do the internal command.
	if it is internal command, do the command and return 1.
	otherwise, return 0.
*/
int do_inner_command(int cmd_argc, char **cmd_argv);

#endif