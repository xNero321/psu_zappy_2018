/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map
*/

#ifndef MAP_H_
    #define MAP_H_

    #include "my_zappy.h"

    typedef struct mapcell_s mapcell_t;

    struct mapcell_s {
        char *objects;
        int x;
        int y;
        mapcell_t *right;
        mapcell_t *left;
        mapcell_t *up;
        mapcell_t *down;
    };

#endif /* !MAP_H_ */
