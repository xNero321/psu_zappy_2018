/*
** EPITECH PROJECT, 2019
** Tech2
** File description:
** main
*/

#include "server.h"

int main(int ac, char**av)
{
    options_serv_t opts = {0, 0, 0, NULL, 0, 0};
    mapcell_t *map = NULL;
    client_t player;

    serv(ac, av, &opts);
    map = create_map(&opts);
    player.pos = map;
    player.dir = LEFT;
    player.level = 2;
    for (int i = 0; i < 7; i++)
        player.inv[i] = 0;
    map->character = 1;
    printf("%s", inventory(&player));
    // send_map(map);
    destroy_map(map, opts);
    return (0);
}