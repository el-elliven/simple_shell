#include "shell.h"

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);
        r = getline(buf, &len_p, stdin);
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);
        }
    }
    return r;
}

ssize_t get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH);
    r = input_buf(info, &buf, &len);
    if (r == -1)
        return -1;
    if (len)
    {
        j = i;
        p = buf + i;
        check_command_chain(info, buf, &j, i, len);
        while (j < len)
        {
            if (is_command_chain(info, buf, &j))
                break;
            j++;
        }
        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }
        *buf_p = p;
        return _strlen(p);
    }
    *buf_p = buf;
    return r;
}

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = find_character(buf + i, '\n');
    k = c ? 1 + (size_t)(c - buf) : len;
    new_p = custom_realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return p ? (free(p), -1) : -1;

    if (s)
        concatenate_strings(new_p, buf + i, k - i);
    else
        copy_string(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

void sigintHandler(__attribute__((unused)) int sig_num)
{
  _puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

/* Additional utility functions */

void remove_comments(char buf)
{
/ Implementation of removing comments /
/ ... */
}

void build_history_list(info_t *info, char buf, int histcount)
{
/ Implementation of building history list /
/ ... */
}

void check_command_chain(info_t *info, char *buf, size_t j, size_t i, size_t len)
{
/ Implementation of checking command chain /
/ ... */
}

int is_command_chain(info_t *info, char *buf, size_t j)
{
/ Implementation of checking if it is a command chain /
/ ... */
}

char *find_character(char *s, char c)
{
while (*s != '\0') {
if (*s == c)
return s;
s++;
}
return NULL;
}

void concatenate_strings(char *dest, const char *src, size_t n)
{
size_t dest_len = _strlen(dest);
size_t i;
 for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
}
dest[dest_len + i] = '\0';
}

void copy_string(char *dest, const char *src, size_t n)
{
size_t i;
 for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
}
dest[i] = '\0';
}

size_t _strlen(const char *s)
{
size_t len = 0;
 while (s[len] != '\0') {
    len++;
}
return len;
}

char *custom_realloc(char *ptr, size_t old_size, size_t new_size)
{
char *new_ptr = NULL;
 if (new_size == 0) {
    free(ptr);
    return NULL;
}

new_ptr = (char *)realloc(ptr, new_size);
if (new_ptr == NULL) {
    free(ptr);
    return NULL;
}

if (new_size > old_size) {
    new_ptr[old_size] = '\0';
}

return new_ptr;
}

void _puts(const char *s)
{
size_t i;
 for (i = 0; s[i] != '\0'; i++) {
    _putchar(s[i]);
}
}

void _putchar(char c)
{
putchar(c);
}
