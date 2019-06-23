/*
** EPITECH PROJECT, 2019
** Tech2
** File description:
** main
*/

#include "server.h"

server_t server;

int main(int ac, char **av)
{
    mapcell_t *map = NULL;

    serv(ac, av, &server.args);
    map = create_map(&server.args);
    // send_map(map);
    // init_server(&server);
    // start_multiplexing(&server);
    destroy_map(map, server.args);
    return (0);
}
