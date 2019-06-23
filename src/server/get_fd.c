/*
** EPITECH PROJECT, 2017
** psu_zappy_2018
** File description:
** get_fd.c
*/

#include "server.h"
#include "list.h"

client_t *client_fd(server_t *server, int fd)
{
    client_t *client = server->clients;

    if (!client)
        return (NULL);
    do {
        if (client->sockfd == fd)
            return (client);
    } while (list_next(&client));
    return (NULL);
}
