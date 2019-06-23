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

    player->pos->character -= 1;
    for (; player->pos->players[i] != player; i++);
    for (; i < player->pos->character; i++)
        player->pos->players[i] = player->pos->players[i + 1];
    player->pos->players = realloc(player->pos->players,
    player->pos->character * sizeof(client_t *));
    player->pos = player->pos->dir[player->dir];
    player->pos->character += 1;
    player->pos->players = realloc(player->pos->players,
    player->pos->character * sizeof(client_t *));
    player->pos->players[player->pos->character - 1] = player;
    return ("ok\n");
}

char *right(client_t *player, char *cmd, server_t *serv)
{
    player->dir = (player->dir == DOWN) ? LEFT : player->dir + 1;
    return ("ok\n");
}

char *left(client_t *player, char *cmd, server_t *serv)
{
    player->dir = (player->dir == LEFT) ? DOWN : player->dir - 1;
    return ("ok\n");
}

char *eject(client_t *player, char *cmd, server_t *serv)
{
    if (player->pos->character == 1)
        return ("ko\n");
    for (int i = 0; i < player->pos->character; i++) {
        if (player->pos->players[i] != player) {
            player->pos->players[i]->dir = player->dir;
            forward(player->pos->players[i], "forward", serv);
            send_message(player->sockfd, "eject: \n");
        }
    }
    return ("ok\n");
}