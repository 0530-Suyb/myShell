#include "apue.h"
#include "prompt.h"
#include "splitCmdStr.h"
#include <sys/wait.h>

/* my SIGINT signal-catching function */
static void sig_int(int);

int main(void)
{
	char	buf[MAXLINE];	/* MAXLINE defined in apue.h */
	char	**cmd_args;	/* MAX_CMD_ARGS defined in splitCmdStr.h */
	pid_t	pid;
	int	status;

	/* register a new signal-catching function for SIGINT */
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	print_prompt();		/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; 	/* replace newline with null */
		
		/* split command string to args array */
		cmd_args = split_cmd_str(buf, cmd_args);

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
		print_prompt();
	}
	exit(0);
}

void sig_int(int signo)
{
	printf("\n");
	exit(0);
}
