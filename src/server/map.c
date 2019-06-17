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
    for (; tmp && tmp->down; tmp = tmp->down)
    new->up = tmp;
    if (!map)
        return (tmp);
    else
        return (map);    
}

void new_cell(mapcell_t *map, int y, int x)
{
    mapcell_t *new = malloc(sizeof(mapcell_t));
    mapcell_t *tmp_line = map;
    mapcell_t *tmp_cell = map;

    new->down = NULL;
    new->right = NULL;
    new->x = x;
    new->y = y;
    for (; tmp_line && tmp_line->down; tmp_line = tmp_line->down)
        tmp_cell = tmp_cell->down;
    tmp_cell = tmp_cell->down;
    for (; tmp_cell && tmp_cell->left; tmp_cell = tmp_cell->left)
        tmp_line = tmp_line->left;
    tmp_line = tmp_line->left;
    new->left = tmp_cell;
    new->up = tmp_line;
}

mapcell_t *create_map(int size)
{
    mapcell_t *map = NULL;

    for (int y = 0; y < size; y++) {
        map = new_line(map, y);
        for (int x = 1; x < size; x++) {
            new_cell(map, y, x);
        }
    }
    return (map);
}