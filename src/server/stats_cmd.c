/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** stats_cmd
*/

#include "server.h"

char *my_fork(client_t *player, char *cmd, server_t *serv)
{
    return ("ko");
}

char *incantation(client_t *player, char *cmd, server_t *serv)
{
    char *response = "Elevation underway\nCurrent level: ";
    int requirements[7][7] = {{1, 1, 0, 0, 0, 0, 0}, {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0}, {4, 1, 1, 2, 0, 1, 0}, {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0}, {6, 2, 2, 2, 2, 2, 1}};

    for (int i = 1; i < 8; i++) {
        if (player->inv[i - 1] < requirements[player->level - 1][i])
            return ("ko");
    }
    for (int i = 0; i < player->pos->character; i++) {
        if (player->pos->players[i]->level == player->level)
            requirements[player->level - 1][0]--;
        if (requirements[player->level - 1][0] == 0) {
            player->level++;
            asprintf(&response, "%s%d", response, player->level);
            return (response);
        }
    }
    return ("ko");
}

char *broadcast(client_t *player, char *cmd, server_t *serv)
{
    return ("ko");
}