#include "shell.h"

/**
 * read_file - file is now read
 *
 * @filename:Filename
 *
 * @argv: argument name
 *
 * Return: -1 if success, and 0 if fail
 *
 */
void read_file(char *filename, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		treat_file(line, counter, fp, argv);
	}
	if (line)
		free(line);
	fclose(fp);
	exit(0);
}
/**
 * treat_file - first line parsed for check
 *
 * @line: line counter
 *
 * @counter: counter checked
 *
 * @fp:File Descriptor
 *
 * @argv: name of program
 *
 * Return : line void executed
 */
void treat_file(char *line, int counter, FILE *fp, char **argv)
{
	char **cmd;
	int st = 0;

	cmd = parse_cmd(line);
	if (_strncmp(cmd[0], "exit", 4) == 0)
	{
		exit_bul_for_file(cmd, line, fp);
	}
	else if (check_builtin(cmd) == 0)
	{
		st = handle_builtin(cmd, st);
		free(cmd);
	}
	else
	{
		st = check_cmd(cmd, line, counter, argv);
		free(cmd);
	}
}
/**
 * exit_bul_for_file - bul exited
 *
 * @line: line pass
 *
 * @cmd: Parsed Command
 *
 * @fd:File Descriptor
 *
 * Return : Case Of Exit in A File Line
 *
 */
void exit_bul_for_file(char **cmd, char *line, FILE *fd)
{
	int statue, i = 0;

	if (cmd[1] == NULL)
	{
		free(line);
		free(cmd);
		fclose(fd);
		exit(errno);
	}
	while (cmd[1][i])
	{
		if (_isalpha(cmd[1][i++]) < 0)
		{
			perror("illegal number");
		}
	}
	statue = _atoi(cmd[1]);
	free(line);
	free(cmd);
	fclose(fd);
	exit(statue);
}
