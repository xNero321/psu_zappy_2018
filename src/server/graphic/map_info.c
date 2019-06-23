/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** map_info
*/

#include "server.h"

char *msz(client_t *client, char *cmd, server_t *serv)
{
    char *response = "msz ";

    asprintf(&response, "%s%d %d\n", serv->args.width, serv->args.height);
    return (response);
}

char *bct(client_t *client, char *cmd, server_t *serv)
{
    char *response = "bct";
    int x = atoi(&cmd[4]);
    int y = atoi(&cmd[6]);
    mapcell_t *cell = serv->map;

    for (int i = 0; i < y; i++, cell = cell->dir[DOWN]);
    for (int i = 0; i < x; i++, cell = cell->dir[RIGHT]);
    for (int i = 0; i < 7; i++)
        asprintf(&response, "%s %d", response, cell->obj[i]);
    asprintf(&response, "%s\n", response);
    return (response);
}

char *mct(client_t *client, char *cmd, server_t *serv)
{
    mapcell_t *cell = serv->map;
    mapcell_t *line = serv->map;
    char *response = "";

    for (int y = 0; y < serv->args.height; y++, line = line->dir[DOWN]) {
        cell = line;
        asprintf(&response, "%sbct", response);
        for (int x = 0; x < serv->args.width; x++, cell = cell->dir[RIGHT]) {
            for (int i = 0; i < 7; i++)
                asprintf(&response, "%s %d", response, cell->obj[i]);
            asprintf(&response, "%s\n", response);
        }
    }
    return (response);
}
