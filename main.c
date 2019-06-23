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

    if (ac < 13) {
        print_usage_serv();
        exit(84);
    }
    serv(ac, av, &server.args, &server);
    server.map = create_map(&server.args);
    init_server(&server);
    start_multiplexing(&server);
    destroy_map(map, server.args);
    return (0);
}
