/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** move_cmd
*/

#include "server.h"

char *forward(client_t *player, char *cmd, server_t *serv)
{
    player->pos = player->pos->dir[player->dir];
    return ("ok");
}

char *right(client_t *player, char *cmd, server_t *serv)
{
    player->dir = (player->dir == DOWN) ? LEFT : player->dir + 1;
    return ("ok");
}

char *left(client_t *player, char *cmd, server_t *serv)
{
    player->dir = (player->dir == LEFT) ? DOWN : player->dir - 1;
    return ("ok");
}

char *eject(client_t *player, char *cmd, server_t *serv)
{
    return ("ko");
}