/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** move_cmd
*/

#include "server.h"

char *forward(client_t *player, char *cmd, server_t *serv)
{
    int i = 0;

    player->pos->character--;
    for (; player->pos->players[i] != player; i++);
    for (; i < player->pos->character; i++)
        player->pos->players[i] = player->pos->players[i + 1];
    player->pos->players = realloc(player->pos->players,
    player->pos->character * sizeof(client_t *));
    player->pos = player->pos->dir[player->dir];
    player->pos->character++;
    player->pos->players = realloc(player->pos->players,
    player->pos->character * sizeof(client_t *));
    player->pos->players[player->pos->character - 1] = player;
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