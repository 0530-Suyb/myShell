#include "apue.h"
#include "myShell.h"
#include "export.h"
#include "prompt.h"
#include "splitCmdStr.h"
#include <sys/wait.h>

/* my SIGINT signal-catching function */
static void sig_int(int);

int main(void)
{
	char	buf[MAXLINE];	/* MAXLINE defined in apue.h */
	char	*cmd_argv[MAX_CMD_ARGS];	/* MAX_cmd_argv defined in splitCmdStr.h */
	int 	cmd_argc;
	pid_t	pid;
	int	status;
	int isInnerCmd;
	int bg_flag;

	/* register a new signal-catching function for SIGINT */
	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	print_prompt();

	while (fgets(buf, MAXLINE, stdin) != NULL) {
		/* if only newline, print prompt again */
		if(buf[0] == '\n')
		{
			print_prompt();
			continue;
		}

		/* replace newline with null */
		if (buf[strlen(buf) - 1] == '\n')
		{
			buf[strlen(buf) - 1] = 0; 	
		}	
		
		/* split command string to args array */
		cmd_argc = split_cmd_str(buf, cmd_argv);

		/* set bg_flag to 1 if need execute in background */
		if (strcmp(cmd_argv[cmd_argc - 1], "&") == 0)
		{
			/* command end with & */
			cmd_argv[cmd_argc - 1] = NULL;
			bg_flag = 1;
		}

		/* do inner command, if not inner command return 0 */
		isInnerCmd = do_inner_command(cmd_argc, cmd_argv);

		if (isInnerCmd == 0)
		{
			/* external command */
			if ((pid = fork()) < 0) {
				err_sys("fork error");
			} else if (pid == 0) {		/* child */
				/* redirect just take effect in child process */
				redirect(cmd_argc, cmd_argv);
				execvp(cmd_argv[0], cmd_argv);
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}

			/* parent */
			if (bg_flag == 0)
			{
				/* 
					command needn't execute in background.
					wait for the child to terminate.
				*/
				if ((pid = waitpid(pid, &status, 0)) < 0)
					err_sys("waitpid error");
			}
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