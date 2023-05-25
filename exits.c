#include "shell.h"

char *copy_string(char *dest, const char *src, int n)
{
	int i;
	char *result = dest;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];
	if (i < n)
	{
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return result;
}

char *concatenate_strings(char *dest, const char *src, int n)
{
	int dest_len, i;
	char *result = dest;

	dest_len = 0;
	while (dest[dest_len] != '\0')
		dest_len++;
	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[dest_len++] = src[i];
	if (i < n)
		dest[dest_len] = '\0';
	return result;
}

char *find_character(const char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (char *)s;
		s++;
	}
	return NULL;
}
