/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** info_cmd
*/

#include "player.h"

char *get_cellcontent(mapcell_t *cell, char *look)
{
    char *tmp = (cell->character) ? "player" : "";
    char item[8][9] = {"", "food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame"};

    for (int it = 0; it < 7; it++) {
        if (tmp[strlen(tmp) - 1] && tmp[strlen(tmp) - 1] != ','
        && item[cell->obj[it]])
            asprintf(&tmp, "%s ", tmp);
        asprintf(&tmp, "%s%s", tmp, item[cell->obj[it]]);
    }
    asprintf(&look, "%s%s|", look, tmp);
    free(tmp);
    return (look);
}

void refresh_dirarray(mapcell_t **dir, mapcell_t *cell)
{
    dir[0] = cell->left;
    dir[1] = cell->up;
    dir[2] = cell->right;
    dir[3] = cell->down;
}

char *get_line(char *look, int i, mapcell_t *cell, player_t *player)
{
    int left = (player->dir == 0) ? 3 : player->dir - 1;
    int right = (left + 2) % 4;
    mapcell_t **dir = malloc(sizeof(mapcell_t *) * 4);

    refresh_dirarray(dir, cell);
    for (int x = 0; x < i; cell = dir[left], x++) {
        refresh_dirarray(dir, cell);
        printf("!![%d,%d][%d,%d]\n", left, right, cell->x, cell->y);
    }
    refresh_dirarray(dir, cell);
    for (int x = 0; x <= i * 2; cell = dir[right], x++) {
        look = get_cellcontent(cell, look);
        printf("[%d,%d][%d,%d]\n", left, right, cell->x, cell->y);
        refresh_dirarray(dir, cell);
    }
    free(dir);
    return (look);
}

char *look(player_t *player)
{
    char *look = "[";
    mapcell_t *line = player->pos;
    mapcell_t **dir = malloc(sizeof(mapcell_t *) * 4);
    char endchar = 0;

    for (int i = 0; i <= player->level; i++, line = dir[player->dir]) {
        refresh_dirarray(dir, line);
        look = get_line(look, i, line, player);
        endchar = (i < player->level) ? ',' : ']';
        asprintf(&look, "%s%c\n", look, endchar);
        refresh_dirarray(dir, line);
    }
    free(dir);
    return (look);
}