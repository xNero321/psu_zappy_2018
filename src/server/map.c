/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map
*/

#include "server.h"

mapcell_t *new_line(mapcell_t *map, int y)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp = map;

    new->dir[LEFT] = NULL;
    new->dir[RIGHT] = NULL;
    new->dir[DOWN] = NULL;
    new->x = 0;
    new->y = y;
    for (; tmp && tmp->dir[DOWN]; tmp = tmp->dir[DOWN]);
    new->dir[UP] = tmp;
    if (!map)
        return (new);
    else {
        tmp->dir[DOWN] = new;
        return (map);
    }
}

void fill_map(mapcell_t *map, options_serv_t *opt)
{
    srand(time(NULL));
    mapcell_t *line = map;
    mapcell_t *cell = line;
    item_t item;

    for (int y = 0;  y < opt->height; line = line->dir[DOWN], y++, cell = line)
        for (int x = 0; x < opt->width; cell = cell->dir[RIGHT], x++)
            for (int i = 0; i < 7; i++)
                cell->obj[i] = (rand() % 10 > i + 2) ? 1 : 0;
}

void new_cell(mapcell_t *map, int y, int x)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp_cell = map;

    new->dir[RIGHT] = NULL;
    new->dir[DOWN] = NULL;
    new->x = x;
    new->y = y;
    new->character = 0;
    new->players = NULL;
    for (; tmp_cell && tmp_cell->dir[DOWN]; tmp_cell = tmp_cell->dir[DOWN]);
    for (; tmp_cell && tmp_cell->dir[RIGHT]; tmp_cell = tmp_cell->dir[RIGHT]);
    if (tmp_cell)
        tmp_cell->dir[RIGHT] = new;
    new->dir[LEFT] = tmp_cell;
}

void link_map(mapcell_t *map, options_serv_t *opt)
{
    mapcell_t *save = NULL;
    mapcell_t *last = NULL;

    for (mapcell_t *prev = map; prev; prev = prev->dir[DOWN]) {
        save = prev;
        for (mapcell_t *line = prev->dir[DOWN]; line; line = line->dir[RIGHT]) {
            prev->dir[DOWN] = line;
            line->dir[UP] = prev;
            prev = (prev->dir[RIGHT]) ? prev->dir[RIGHT] : prev;
        }
        for (; prev && prev->dir[RIGHT]; prev = prev->dir[RIGHT]);
        prev->dir[RIGHT] = save;
        save->dir[LEFT] = prev;
        prev = save;
    }
}

mapcell_t *create_map(options_serv_t *opt)
{
    mapcell_t *map = NULL;
    mapcell_t *save = NULL;
    mapcell_t *last = NULL;

    for (int y = 0; y < opt->height; y++) {
        map = new_line(map, y);
        for (int x = 1; x < opt->width; x++)
            new_cell(map, y, x);
    }
    link_map(map, opt);
    for (last = map; last->dir[DOWN]; last = last->dir[DOWN], save = map);
    for (int x = 0; x < opt->width;
    save = save->dir[RIGHT], last = last->dir[RIGHT]) {
        save->dir[UP] = last;
        last->dir[DOWN] = save;
        x++;
    }
    fill_map(map, opt);
    return (map);
}