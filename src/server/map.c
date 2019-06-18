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
    for (; tmp && tmp->down; tmp = tmp->down)
    new->up = tmp;
    if (!map)
        return (new);
    else {
        tmp->down = new;
        return (map);
    } 
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
    tmp_cell = (tmp_cell) ? tmp_cell->down : NULL;
    for (; tmp_cell && tmp_cell->right; tmp_cell = tmp_cell->right)
        tmp_line = tmp_line->right;
    if (tmp_line) {
        tmp_line = tmp_line->right;
        if (tmp_line)
            tmp_line->down = new;
        if(tmp_cell)
            tmp_cell->right = new;
    }
    new->left = tmp_cell;
    new->up = tmp_line;
}

void check_cell(mapcell_t *cell, int x, int y, int size)
{
    if (x > 0 && (!cell->left))
        printf("left\t[%d,%d]\n", x, y);
    if (x < size - 1 && (!cell->right))
        printf("right\t[%d,%d]\n", x, y);
    if (y > 0 && (!cell->up))
        printf("up\t[%d,%d]\n", x, y);
    if (x < size - 1 && (!cell->down))
        printf("down\t[%d,%d]\n", x, y);
}

void check_map(mapcell_t *map, int size)
{
    mapcell_t *tmp = map;
    mapcell_t *line = map;

    for (int y = 0; line; line = line->down, y++) {
        tmp = line;
        for (int x = 0; tmp; tmp = tmp->left, x++) {
            check_cell(tmp, x, y, size);
        }
    }
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