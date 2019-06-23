/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** items_cmd
*/

#include "server.h"

char *take(client_t *player, char *cmd, server_t *serv)
{
    char item[7][10] = {"food", "linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame"};

    cmd[strlen(cmd) - 1] = 0;
    for (int i = 0; i < 7; i++) {
        if (strcmp(&cmd[5], item[i]) == 0 && player->pos->obj[i] != 0) {
            player->inv[i]++;
            return ("ok\n");
        }
    }
    return ("ko\n");
}

char *set(client_t *player, char *cmd, server_t *serv)
{
    char item[7][10] = {"food", "linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame"};

    cmd[strlen(cmd) - 1] = 0;
    for (int i = 0; i < 7; i++) {
        if (strcmp(&cmd[4], item[i]) == 0 && player->inv[i] > 0) {
            player->pos->obj[i] = i + 1;
            return ("ok\n");
        }
    }
    return ("ko\n");
}