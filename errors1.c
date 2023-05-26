#include "shell.h"

int convert_string_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}
	return (int)result;
}

void print_error_message(info_t *info, char *error_string)
{
	print_string_to_stderr(info->fname);
	print_string_to_stderr(": ");
	print_decimal_to_stderr(info->line_count);
	print_string_to_stderr(": ");
	print_string_to_stderr(info->argv[0]);
	print_string_to_stderr(": ");
	print_string_to_stderr(error_string);
}

int print_decimal_to_fd(int input, int fd)
{
	int (*write_character)(char, int) = write_character_to_fd;
	int i, count = 0;
	unsigned int absolute_value, current;

	if (fd == STDERR_FILENO)
		write_character = write_character_to_stderr;

	if (input < 0)
	{
		absolute_value = (unsigned int)-input;
		write_character('-', fd);
		count++;
	}
	else
		absolute_value = (unsigned int)input;

	current = absolute_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute_value / i)
		{
			write_character('0' + current / i, fd);
			count++;
		}
		current %= i;
	}
	write_character('0' + current, fd);
	count++;

	return count;
}

char *convert_number_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (unsigned long)num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = (unsigned long)-num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

void remove_comments_from_string(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
