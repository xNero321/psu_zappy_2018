/*
** EPITECH PROJECT, 2018
** psu_zappy_2018
** File description:
** read_cmds.c
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "read_cmds.h"

char *sstrstr(char *buffer, char *find, size_t length)
{
    size_t find_length = strlen(find);
    size_t i;

    for (i = 0; i < length; i++) {
        if (strncmp(&buffer[i], find, find_length) == 0)
            return (&buffer[i]);
    }
    return (NULL);
}

static char *get_end_cmd(linked_buffer_t *buffer, char *to, \
const char *buff_end, char *str)
{
    char *ret = malloc((size_t)(buff_end - buffer->tail + \
        (size_t)((buff_end - buffer->tail) + str - \
        (((char *)&buffer->buffer)) + 1)));

    if (ret == NULL)
        return (NULL);
    memcpy(ret, buffer->tail, (buff_end - buffer->tail));
    memcpy(ret + (buff_end - buffer->tail), \
    &buffer->buffer, str - ((char *)&buffer->buffer));
    ret[((size_t)((buff_end - buffer->tail) + str - \
    (((char *)&buffer->buffer))))] = '\0';
    buffer->tail = str + strlen(to);
    memset(buffer->tail - strlen(to), 0, strlen(to));
    return (ret);
}

char *read_cmd2(linked_buffer_t *buffer, char *to, \
char *str)
{
    char *ret = strndup(buffer->tail, str - buffer->tail);

    if (ret == NULL)
        return (NULL);
    buffer->tail = (char *)(str + strlen(to));
    memset(buffer->tail - strlen(to), 0, strlen(to));
    return (ret);
}


char *read_cmd_where(linked_buffer_t *buffer, char *to)
{
    char *str;
    const char *buff_end = (((char *)&buffer->buffer) + 2048);

    if (buffer->head == NULL) {
        return ("-1");
    }
    if ((buffer->head > buffer->tail || \
        buffer->head == (char *)&buffer->buffer) && \
        (str = sstrstr(buffer->tail, to, ((int)(((buffer->head == \
        (char *)&buffer->buffer) ? buff_end : buffer->head) - \
        buffer->tail)))) != NULL)
        return (read_cmd2(buffer, to, str));
    if (buffer->head <= buffer->tail && (str = sstrstr(\
        (char *)&buffer->buffer, to, buffer->head - \
        (char *)&buffer->buffer)))
        return (get_end_cmd(buffer, to, buff_end, str));
    return ("-1");
}

bool read_cmd(linked_buffer_t *buffer, int fd)
{
    const char *buff_end = (((char *)&buffer->buffer) + 2048);
    int readed = 0;

    if (buffer->head == NULL)
        buffer->head = (char *)&buffer->buffer;
    if (buffer->tail == NULL)
        buffer->tail = (char *)&buffer->buffer;
    if (buffer->tail <= buffer->head) {
        readed = read(fd, buffer->head, buff_end - buffer->head);
        if (readed == 0 || (readed == -1 && errno != EAGAIN))
        return (false);
    } else {
        readed = read(fd, buffer->buffer, buffer->tail - buffer->head);
        if (readed == 0 || (readed == -1 && errno != EAGAIN))
            return (false);
    }
    buffer->head += readed;
    if (buffer->head == buff_end) {
        buffer->head = (char *)&buffer->buffer;
        read_cmd(buffer, fd);
    }
    return (true);
}
