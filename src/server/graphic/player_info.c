/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** player_info
*/

#include "server.h"

char *pnw(client_t *client, char *cmd, server_t *serv)
{
    char *response = "pnw ";

    asprintf(&response, "%s #%d %d %d %d %d %s\n", response, client->id,
    client->pos->x, client->pos->y, (client->dir + 1) % 4, client->level,
    client->team);
    return (response);
}