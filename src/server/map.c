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

    new->dir[0] = NULL;
    new->dir[2] = NULL;
    new->dir[3] = NULL;
    new->x = 0;
    new->y = y;
    for (; tmp && tmp->dir[3]; tmp = tmp->dir[3]);
    new->dir[1] = tmp;
    if (!map)
        return (new);
    else {
        tmp->dir[3] = new;
        return (map);
    }
}

void fill_map(mapcell_t *map, options_serv_t *opt)
{
    srand(time(NULL));
    mapcell_t *line = map;
    mapcell_t *cell = line;
    item_t item;

    for (int y = 0;  y < opt->height; line = line->dir[3], y++, cell = line)
        for (int x = 0; x < opt->width; cell = cell->dir[2], x++)
            for (int i = 0; i < 7; i++)
                cell->obj[i] = (rand() % 10 > i + 2) ? i + 1 : 0;
}

void new_cell(mapcell_t *map, int y, int x)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp_cell = map;

    new->dir[2] = NULL;
    new->dir[3] = NULL;
    new->x = x;
    new->y = y;
    for (; tmp_cell && tmp_cell->dir[3]; tmp_cell = tmp_cell->dir[3]);
    for (; tmp_cell && tmp_cell->dir[2]; tmp_cell = tmp_cell->dir[2]);
    if (tmp_cell)
        tmp_cell->dir[2] = new;
    new->dir[0] = tmp_cell;
}

void link_map(mapcell_t *map, options_serv_t *opt)
{
    mapcell_t *save = NULL;
    mapcell_t *last = NULL;

    for (mapcell_t *prev = map; prev; prev = prev->dir[3]) {
        save = prev;
        for (mapcell_t *line = prev->dir[3]; line; line = line->dir[2]) {
            prev->dir[3] = line;
            line->dir[1] = prev;
            prev = (prev->dir[2]) ? prev->dir[2] : prev;
        }
        prev->dir[2] = save;
        save->dir[0] = prev;
        prev = save;
    }
    for (last = map; last->dir[3]; last = last->dir[3]);
    save = map;
    for (int x = 0; x < opt->width; save = save->dir[2], last = save->dir[2]) {
        save->dir[1] = last;
        last->dir[3] = save;
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