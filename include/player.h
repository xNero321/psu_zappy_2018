/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "map.h"

    typedef struct player_s player_t;
    struct player_s {
        mapcell_t *pos;
        char dir;
        char items[6];
        int level;
        player_t *next;
    };

    char *right(player_t *);
    char *forward(player_t *);
    char *left(player_t *);
    char *look(player_t *);
    char *inventory(player_t *);
#endif /* !PLAYER_H_ */
