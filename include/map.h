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
        char character;
        int x;
        int y;
        mapcell_t *dir[4];
    };

    mapcell_t *create_map(options_serv_t *opt);
    char *map_to_array(mapcell_t *map);
    void perror_exit(char* str, int error);
    int send_map(mapcell_t *map);

#endif /* !MAP_H_ */
