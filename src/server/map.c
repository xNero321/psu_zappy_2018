/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map
*/

#include "my_zappy.h"

mapcell_t *new_line(mapcell_t *map, int y)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp = map;

    new->down = NULL;
    new->left = NULL;
    new->right = NULL;
    new->x = 0;
    new->y = y;
    for (; tmp && tmp->down; tmp = tmp->down);
    new->up = tmp;
    if (!map)
        return (new);
    else {
        tmp->down = new;
        return (map);
    } 
}

void fill_map(mapcell_t *map)
{
    srand(time(NULL));
    item_t item;

    for (mapcell_t *line = map; line; line = line->down)
        for (mapcell_t *cell = line; cell; cell = cell->right)
            for (int i = 0; i < 7; i++)
                cell->obj[i] = (rand() % 10 > i + 2) ? i + 1 : 0;
}

void new_cell(mapcell_t *map, int y, int x)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp_cell = map;

    new->down = NULL;
    new->right = NULL;
    new->x = x;
    new->y = y;
    for (; tmp_cell && tmp_cell->down; tmp_cell = tmp_cell->down);
    for (; tmp_cell && tmp_cell->right; tmp_cell = tmp_cell->right);
    if (tmp_cell)
        tmp_cell->right = new;
    new->left = tmp_cell;
}

void link_map(mapcell_t *map)
{
    mapcell_t *save = NULL;
    mapcell_t *last = NULL;

    for (mapcell_t *prev = map; prev; prev = prev->down) {
        save = prev;
        for (mapcell_t *line = prev->down; line; line = line->right) {
            prev->down = line;
            line->up = prev;
            prev = prev->right;
        }
        prev->right = save;
        save->left = prev;
        prev = save;
    }
    for (last = map; last->down; last = last->down);
    for (save = map; save; save = save->right, last = save->right) {
        save->up = last;
        last->down = save;
    }
}
mapcell_t *create_map(options_serv_t *opt)
{
    mapcell_t *map = NULL;

    for (int y = 0; y < opt->width; y++) {
        map = new_line(map, y);
        for (int x = 1; x < opt->height; x++) {
            new_cell(map, y, x);
        }
    }
    fill_map(map);
    return (map);
}