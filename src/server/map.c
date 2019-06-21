/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map
*/

#include "map.h"

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

void fill_map(mapcell_t *map, options_serv_t *opt)
{
    srand(time(NULL));
    mapcell_t *line = map;
    mapcell_t *cell = line;
    item_t item;

    for (int y = 0;  y < opt->height; line = line->down, y++, cell = line)
        for (int x = 0; x < opt->width; cell = cell->right, x++)
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

void link_map(mapcell_t *map, options_serv_t *opt)
{
    mapcell_t *save = NULL;
    mapcell_t *last = NULL;

    for (mapcell_t *prev = map; prev; prev = prev->down) {
        save = prev;
        for (mapcell_t *line = prev->down; line; line = line->right) {
            prev->down = line;
            line->up = prev;
            prev = (prev->right) ? prev->right : prev;
        }
        prev->right = save;
        save->left = prev;
        prev = save;
    }
    for (last = map; last->down; last = last->down);
    save = map;
    for (int x = 0; x < opt->width; save = save->right, last = save->right) {
        save->up = last;
        last->down = save;
        x++;
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
    link_map(map, opt);
    fill_map(map, opt);
    return (map);
}