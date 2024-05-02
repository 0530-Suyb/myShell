#include "apue.h"
#include "myShell.h"
#include "export.h"
#include "prompt.h"
#include "splitCmdStr.h"
#include <sys/wait.h>

/* shell internal commands */
const char* INTERNAL_COMMANDS[] = {
	"export",
};

/* my SIGINT signal-catching function */
static void sig_int(int);

/* check if the command is an internal command */
bool is_internal_command(char *cmd);

int main(void)
{
	char	buf[MAXLINE];	/* MAXLINE defined in apue.h */
	char	**cmd_args;	/* MAX_CMD_ARGS defined in splitCmdStr.h */
	pid_t	pid;
	int	status;

	/* register a new signal-catching function for SIGINT */
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	print_prompt();

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		/* replace newline with null */
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; 	
		
		/* split command string to args array */
		cmd_args = split_cmd_str(buf, cmd_args);

		if (is_internal_command(cmd_args[0]))
		{
			/* internal command */
			switch (cmd_args[0])
			{
				case 'export':
					/* export environment variable */
					export_env_var(cmd_args);
					break;
				default:
					/* wouldn't happen */
					err_ret("unknown internal command: %s", cmd_args[0]);
					break;
			}
		} else {
			/* external command */
			if ((pid = fork()) < 0) {
				err_sys("fork error");
			} else if (pid == 0) {		/* child */
				execvp(cmd_args[0], cmd_args);
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

bool is_internal_command(char *cmd)
{
	int i;
	for (i = 0; i < sizeof(INTERNAL_COMMANDS) / sizeof(INTERNAL_COMMANDS[0]); i++)
	{
		if (strcmp(cmd, INTERNAL_COMMANDS[i]) == 0)
		{
			return true;
		}
	}
	return false;
}
