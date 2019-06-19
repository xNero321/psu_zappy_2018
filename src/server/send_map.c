/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** send_map
*/

#include "map.h"

char *map_to_array(mapcell_t *map)
{
    char *ar_map = "";
    int x = 0;
    int y = 0;

    for (mapcell_t *line = map; line; line = line->down, y++) {
        x = 0;
        for (mapcell_t *cell = line; cell; cell = cell->right, x++) {
            asprintf(&ar_map, "%s[", ar_map);
            for (int i = 0; i < 7; i++)
                asprintf(&ar_map, "%s%d,", ar_map, cell->obj[i]);
            asprintf(&ar_map, "%s%d]", ar_map, cell->character);
        }
        asprintf(&ar_map, "%s\n", ar_map);
    }
    return(ar_map);
}