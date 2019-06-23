/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** read_cmds.h
*/

#ifndef READ_CMDS_H
    #define READ_CMDS_H

    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "server.h"

    void init_read_cmd(linked_buffer_t *buffer);
    bool read_cmd(linked_buffer_t *buffer, int fd);
    char *read_cmd_where(linked_buffer_t *buffer, char *to);

#endif /* !CIRCULAR_BUFFER_H_ */
