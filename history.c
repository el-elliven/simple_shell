#include "shell.h"

/**
 * history - you’ll go down in history
 *
 * @input: input by user
 * Return: - success -0 fail-1
 *
 */
int history(char *input)
{
	char *filename = ".simple_shell_history";
	ssize_t fd, w;
	int len = 0;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (fd < 0)
		return (-1);
	if (input)
	{
		while (input[len])
			len++;
		w = write(fd, input, len);
		if (w < 0)
			return (-1);
	}
	return (1);
}
/**
 * free_env - variable (environment) that is free
 *
 * @env:  Environment variables.
 *
 * Return: Void
 *
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		free(env[i]);
	}
}
