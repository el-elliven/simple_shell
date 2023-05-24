#include "shell.h"

/**
 * interactive - beautiful code that passes the Betty checks
 * @info: money checks
 *
 * Return: either return 1 for success or 0 for non interactive
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - verifies if character delimeters
 * @d: this is the character that is checked obviously
 * @del: string delimeters
 * Return: In case of true, return 1 else return 0.
 */
int is_delim(char d, char *del)
{
	while (*del)
		if (*del++ == d)
			return (1);
	return (0);
}

/**
 * alfayo - spots character that is alphabetic
 * @d: The character to input
 * Return: check if d is alphabetic and return 1 else return 0 if d is not alphabetic
 */

int alfayo(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * briefly - string is made to be an integer through conversion
 * @w: this is the  string to be converted
 * Return: youll know what to return
 */

int briefly(char *w)
{
	int i, goof = 1, drag = 0, output;
	unsigned int result = 0;

	for (i = 0; w[i] != '\0' && drag != 2; i++)
	{
		if (w[i] == '-')
			goof *= -1;

		if (w[i] >= '0' && w[i] <= '9')
		{
			drag = 1;
			result *= 10;
			result += (w[i] - '0');
		}
		else if (drag == 1)
			drag = 2;
	}

	if (goof == -1)
		output = -result;
	else
		output = result;

	return (output);
}
