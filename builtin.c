#include "shell.h"

int _myexit(info_t *info)
{
int exitcheck;
 if (info->argv[1])
{
	exitcheck = _erratoi(info->argv[1]);
	if (exitcheck == -1)
	{
		info->status = 2;
		print_error(info, "Illegal number: ");
		_eputs(info->argv[1]);
		_eputchar('\n');
		return 1;
	}
	info->err_num = exitcheck;
	return -2;
}
info->err_num = -1;
return -2;
}

int _mycd(info_t *info)
{
char *dir, buffer[1024];
int chdir_ret;
 if (!info->argv[1])
{
	dir = _getenv(info, "HOME=");
	chdir_ret = chdir(dir ? dir : _getenv(info, "PWD="));
}
else if (_strcmp(info->argv[1], "-") == 0)
{
	dir = _getenv(info, "OLDPWD=");
	if (!dir)
	{
		_puts(getcwd(buffer, 1024));
		_putchar('\n');
		return 1;
	}
	_puts(dir);
	_putchar('\n');
	chdir_ret = chdir(dir);
}
else
	chdir_ret = chdir(info->argv[1]);

if (chdir_ret == -1)
{
	print_error(info, "can't cd to ");
	_eputs(info->argv[1]);
	_eputchar('\n');
}
else
{
	_setenv(info, "OLDPWD", _getenv(info, "PWD="));
	_setenv(info, "PWD", getcwd(buffer, 1024));
}
return 0;
}

int _myhelp(info_t *info)
{
_puts("help call works. Function not yet implemented \n");
return 0;
}
