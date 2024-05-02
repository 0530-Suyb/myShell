#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prompt.h"

const char *ENV_PROMPT = "SHELL_PROMPT";
const char *DEFAULT_PROMPT = "->";

void print_prompt(void)
{
	char *prompt_string = getenv(ENV_PROMPT);

	if (prompt_string == NULL || strlen(prompt_string) == 0)
		printf("%s ", DEFAULT_PROMPT);
	else
		printf("%s ", prompt_string);
}

