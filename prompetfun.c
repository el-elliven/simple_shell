#include "shell.h"
/**
 * prompt - shell prompt to be displayed
 */
void prompt(void)
{
	PRINTER("$ ");
}
/**
 * print_error - Display each and every Error Based on Command and the number of Time Shell Looped
 *
 * @input:User Input
 *
 * @counter:Simple Shell Count Loop
 *
 * @argv: name of program
 *
 * Return: Void
 */
void print_error(char *input, int counter, char **argv)
{
	char *er;

	PRINTER(argv[0]);
	PRINTER(": ");
	er = _itoa(counter);
	PRINTER(er);
	free(er);
	PRINTER(": ");
	PRINTER(input);
	PRINTER(": not found\n");
}
