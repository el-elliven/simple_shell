#include "shell.h"

char *get_history_file(info_t *info)
{
    char *buf, *dir;

    dir = getenv("HOME");
    if (!dir)
        return NULL;

    buf = malloc(sizeof(char) * (strlen(dir) + strlen(HIST_FILE) + 2));
    if (!buf)
        return NULL;

    strcpy(buf, dir);
    strcat(buf, "/");
    strcat(buf, HIST_FILE);

    return buf;
}

int write_history(info_t *info)
{
    int fd;
    char *filename = get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        write(fd, node->str, strlen(node->str));
        write(fd, "\n", 1);
    }

    close(fd);
    return 1;
}

int read_history(info_t *info)
{
    int i, last = 0, linecount = 0;
    int fd, rdlen;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));
    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = '\0';

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = '\0';
            build_history_list(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        build_history_list(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HIST_MAX)
        delete_node_at_index(&(info->history), 0);

    renumber_history(info);

    return info->histcount;
}

int build_history_list(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    add_node_end(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

int renumber_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}
