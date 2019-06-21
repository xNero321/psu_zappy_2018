/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** move_cmd
*/

#include "player.h"

char *forward(player_t *player)
{
    mapcell_t *dir[4] = {
        player->pos->left, player->pos->up,
        player->pos->right, player->pos->down
    };

    player->pos = dir[player->dir];
    return ("ok");
}

char *right(player_t *player)
{
    player->dir = (player->dir == 3) ? 0 : player->dir + 1;
    return ("ok");
}

char *left(player_t *player)
{
    player->dir = (player->dir == 0) ? 3 : player->dir - 1;
    return ("ok");
}