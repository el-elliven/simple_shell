#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>


/* in case of any buffer*/
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

/* commands define */
#define CMD_CHAIN	3
#define CMD_OR		1
#define CMD_NORM	0
#define CMD_AND		2


/* converting numbers */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* another unruly comment */
#define USE_STRTOK 0
#define USE_GETLINE 0


#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - linked that are linked in a single way
 * @next: check out the next node
 * @num: num just stands for number
 * @str: strings defined
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - pass information,
 * @path: path to command
 * @argc: count the arguments
 * @line_count: count lines
 * allowing uniform prototype for function pointer struct
 * @arg: just do it
 * @argv:an array of strings generated from arg
 * @err_num: numerical error
 * @environ: environment 
 * @linecount_flag: count them flags
 * @fname: define the file name
 * @env: environmental variables
 * @history: history channel
 * @alias: define alias
 * @cmd_buf: buffer command
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: just read
 * @env_changed: environment status
 * @status: whats the status?
 * @histcount: count school
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - build a structure
 * @type: do you have a type?
 * @func: free function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* stereotype */
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);
int find_builtin(info_t *);

/* every level */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);

/* california_breeze*/
int loophsh(char **);

/* chill_out */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
int _eputchar(char);

/* character_statement */
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
int _strlen(char *);
int _strcmp(char *, char *);

/* defined_string */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);

/* cool_aid */
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

/* generate_token */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* reallocate_character */
char *_memset(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **);

/* send_to_memory */
int bfree(void **);

/* toem_briefly.c */
int alfayo(int);
int briefly(char *);
int is_interactive(info_t *);
int is_delim(char, char *);

/* toem_laylow.c */
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);

/* toem_grind.c */
int _mycd(info_t *);
int _myhelp(info_t *);
int _myexit(info_t *);

/* toem_steer.c */
int _myalias(info_t *);
int _myhistory(info_t *);

/*toem_location.c */
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/* toem_maybach.c */
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/* toem_payback.c */
char *_getenv(info_t *, const char *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myenv(info_t *);

/* toem_golden.c */
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);

/* toem_deal.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
int read_history(info_t *info);

/* toem_year.c */
list_t *add_node(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);

/* toem_trae.c */
size_t list_len(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);

/* toem_label.c */
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int is_chain(info_t *, char *, size_t *);
int replace_alias(info_t *);
int replace_string(char **, char *);
int replace_vars(info_t *);


#endif
