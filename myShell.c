#include "apue.h"
#include "myShell.h"
#include "export.h"
#include "prompt.h"
#include "splitCmdStr.h"
#include <sys/wait.h>

/* shell internal commands */
const char* INTERNAL_COMMANDS[] = {
	"",	/* null command */
	"export",
};

enum INTERNAL_COMMANDS {
	NOTEXIST, /* command not exist */
	EXPORT,
};

/* my SIGINT signal-catching function */
static void sig_int(int);

/* 
	get the index of the internal command
	if it exist, return the index of the command in INTERNAL_COMMANDS
	otherwise, return 0
*/
int get_index_internal_command(char *cmd);

int main(void)
{
	char	buf[MAXLINE];	/* MAXLINE defined in apue.h */
	char	*cmd_argv[MAX_CMD_ARGS];	/* MAX_cmd_argv defined in splitCmdStr.h */
	int 	cmd_argc;
	pid_t	pid;
	int	status;
	int internal_cmd_index;

	/* register a new signal-catching function for SIGINT */
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	print_prompt();

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		/* replace newline with null */
		if (buf[strlen(buf) - 1] == '\n')
		{
			/* if only newline, print prompt again */
			if(strlen(buf) == 1)
			{
				print_prompt();
				continue;
			}
			buf[strlen(buf) - 1] = 0; 	
		}	
		
		/* split command string to args array */
		cmd_argc = split_cmd_str(buf, cmd_argv);

		internal_cmd_index = get_index_internal_command(cmd_argv[0]);
		if (internal_cmd_index != NOTEXIST)
		{
			/* internal command */
			switch (internal_cmd_index)
			{
				case EXPORT:
					/* export environment variable */
					export_env_var(cmd_argv, cmd_argc);
					break;
				default:
					/* wouldn't happen */
					err_ret("unknown internal command: %s", cmd_argv[0]);
					break;
			}
		} else {
			/* external command */
			if ((pid = fork()) < 0) {
				err_sys("fork error");
			} else if (pid == 0) {		/* child */
				execvp(cmd_argv[0], cmd_argv);
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}

			/* parent */
			if ((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");
		}
		
		print_prompt();
	}
	exit(0);
}

void sig_int(int signo)
{
	printf("\n");
	exit(0);
}

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
	return 0;
}
