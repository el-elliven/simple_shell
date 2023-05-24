#include "shell.h"

/**
 * main - this is our  main header file
 * @vk: count of arguments involved
 * @bb: vector count
 *
 * Return: on success we return 0 otherwise return 1
 */
int main(int vk, char **bb)
{
	int gg = 2;	
	info_t info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (gg)
			: "r" (gg));

	if (vk == 2)
	{
		gg = open(bb[1], O_RDONLY);
		if (gg == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(bb[0]);
				_eputs(": 0: Can't open ");
				_eputs(bb[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readgg = gg;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, bb);
	return (EXIT_SUCCESS);
}
