/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** get_user.c
*/

#include "server.h"

void get_user(client_t *clt, server_t *server)
{
    memset(clt, 0, sizeof(client_t));
    init_buffer(&clt->buff);
    clt->team = NULL;
    clt->size = sizeof(clt->cin);
    clt->id = server->nb_players++;
    clt->on_graph = false;
    clt->level = 1;
    clt->is_connected = false;
    for (int i = 0; i < 7; i++)
        clt->inv[i] = 0;
    clt->inv[FOOD] = 10;
    clt->ttl = 126;
}

void init_buffer(linked_buffer_t *buff)
{
    memset(buff, 0, sizeof(buff));
}
