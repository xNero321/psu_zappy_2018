/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** message.c
*/

#include <fcntl.h>
#include <stdarg.h>
#include "server.h"

int send_message(int fd, const char *format, ...)
{
    va_list strs;

    if (fcntl(fd, F_GETFD) != 0)
        return (0);
    va_start(strs, format);
    if (vdprintf(fd, format, strs) <= 0) {
        fprintf(stderr, "Error: Message cannot be sent to fd #%d\n", fd);
        return (0);
    }
    va_end(strs);
    return (1);
}
