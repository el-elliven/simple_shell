#include "shell.h"

int display_history(info_t *info)
{
	print_list(info->history);
	return 0;
}

int remove_alias(info_t *info, char *str)
{
	char *p;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	*p = '\0';
	ret = delete_node_at_index(&info->alias, get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = '=';
	return ret;
}

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return 1;
	if (!*++p)
		return remove_alias(info, str);

	remove_alias(info, str);
	return add_node_end(&info->alias, str, 0) == NULL;
}

int print_alias(list_t *node)
{
	if (node)
	{
		char *p = _strchr(node->str, '=');
		_putchar('\'');
		for (char *a = node->str; a <= p; a++)
			_putchar(*a);
		_puts(p + 1);
		_puts("'\n");
		return 0;
	}
	return 1;
}

int handle_alias(info_t *info)
{
	if (info->argc == 1)
	{
		list_t *node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return 0;
	}
	for (int i = 1; info->argv[i]; i++)
	{
		char *p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return 0;
}
