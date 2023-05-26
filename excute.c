
#include "shell.h"
/**
 * handle_builtin - builtin command
 *
 * @cmd: Parsed command
 *
 * @er:statue of last Executable file
 *
 * Return: - on fail then 1, otherwise 0
 *
 */
int handle_builtin(char **cmd, int er)
{
	bul_t bil[] = {
		{"cd", change_dir},
		{"env", dis_env},
		{"help", display_help},
		{"echo", echo_bul},
		{"history", history_dis},
		{NULL, NULL}
	};
	int i = 0;

	while ((bil + i)->command)
	{
		if (_strcmp(cmd[0], (bil + i)->command) == 0)
		{
			return ((bil + i)->fun(cmd, er));
		}
		i++;
	}
	return (-1);
}
/**
 * check_cmd - check command that has been parsed
 *
 * @cmd: parse cmd
 *
 * @input: User Input
 *
 * @c:Shell Excution 
 *
 * @argv: argument Name
 *
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 *
 */
int check_cmd(char **cmd, char *input, int c, char **argv)
{
	int status;

	pid_t pid;
	if (*cmd == NULL)
	{
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (pid == 0)
	{
		if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
		{
			path_cmd(cmd);
		}
		if (execve(*cmd, cmd, environ) == -1)
		{
			print_error(cmd[0], c, argv);
			free(input);
			free(cmd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&status);
	return (0);
}
/**
 * signal_to_handel - you know it
 *
 * @sig: signal captured
 *
 * Return: Void
 *
 */
void signal_to_handel(int sig)
{
	if (sig == SIGINT)
	{
		PRINTER("\n$ ");
	}
}
