/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "my_zappy.h"

    typedef enum item {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    } item_t;

    typedef struct mapcell_s mapcell_t;

    struct mapcell_s {
        item_t obj[7];
        int x;
        int y;
        mapcell_t *right;
        mapcell_t *left;
        mapcell_t *up;
        mapcell_t *down;
    };

    mapcell_t *create_map(int size);

#endif /* !MAP_H_ */
