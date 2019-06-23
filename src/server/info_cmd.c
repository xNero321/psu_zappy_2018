/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** info_cmd
*/

#include "server.h"

char *get_cellcontent(mapcell_t *cell, char *look)
{
    char *tmp = (cell->character) ? "player" : "";
    char item[8][10] = {"", "food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame"};

    for (int it = 0; it < 7; it++) {
        if (tmp[strlen(tmp) - 1] && tmp[strlen(tmp) - 1] != ','
        && cell->obj[it] != 0)
            asprintf(&tmp, "%s ", tmp);
        if (cell->obj[it] != 0)
            asprintf(&tmp, "%s%s", tmp, item[it]);
    }
    asprintf(&look, "%s%s", look, tmp);
    free(tmp);
    return (look);
}

char *get_line(char *look, int i, mapcell_t *cell, client_t *player)
{
    int left = (player->dir == LEFT) ? DOWN : player->dir - 1;
    int right = (left + 2) % 4;

    for (int x = 0; x < i; cell = cell->dir[left], x++);
    for (int x = 0; x <= i * 2; cell = cell->dir[right], x++) {
        look = get_cellcontent(cell, look);
        if (x < i * 2)
            asprintf(&look, "%s,", look);
    }
    return (look);
}

char *look(client_t *player, char *cmd, server_t *serv)
{
    char *look = "[";
    mapcell_t *line = player->pos;
    char endchar = 0;

    for (int i = 0; i <= player->level; i++, line = line->dir[player->dir]) {
        look = get_line(look, i, line, player);
        endchar = (i < player->level) ? ',' : ']';
        asprintf(&look, "%s%c", look, endchar);
        if (i == player->level)
            asprintf(&look, "%s%c", look, '\n');
    }
    return (look);
}

char *inventory(client_t *player, char *cmd, server_t *serv)
{
    char *items = "[";
    char item[7][10] = {"food", "linemate", "deraumere", "sibur", "mendiane",
    "phiras", "thystame"};

    for (int i = 0; i < 7; i++) {
        asprintf(&items, "%s%s %d", items, item[i], player->inv[i]);
        if (i < 6)
            asprintf(&items, "%s,", items);
        else
            asprintf(&items, "%s]\n", items);
    }
    return (items);
}

char *connect_nbr(client_t *player, char *cmd, server_t *serv)
{
    char *slots = "";

    asprintf(&slots, "%d\n", serv->args.clientsNb - serv->nb_players);
    return (slots);
}
