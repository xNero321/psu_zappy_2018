/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** auth.c
*/
#include "server.h"
#include "list.h"

void place_player(server_t *srv, client_t *client, team_t *team)
{
    int x = rand() % srv->args.width;
    int y = rand() % srv->args.height;
    mapcell_t *tile = srv->map;

    if (team->free_slots > 0) {
        client->dir = (dir_e) rand() % 4;
        for (int j = 0; j < y; j++, tile = tile->dir[DOWN]);
        for (int i = 0; i < x; i++, tile = tile->dir[RIGHT]);
        client->pos = tile;
        printf("Client n°%d is connected in team: [%s]\n", client->id, team->name);
        client->pos->character++;
        client->pos->players = realloc(client->pos->players,
        client->pos->character * sizeof(client_t *));
        client->pos->players[client->pos->character - 1] = client;
        send_message(client->sockfd, "%d %d\n", x, y);
        team->free_slots--;
        return ;
    }
    send_message(client->sockfd, "ko\n");
}

void add_to_team(server_t *srv, client_t *client, char *str)
{
    team_t *list = srv->args.teams;
    if (!strcmp(str, "GRAPHIC\n")) {
        client->is_connected = true;
        client->on_graph = true;
        return ;
    }
    do {
        if (list != NULL && !strcmp(list->name, str)) {
            client->team = list;
            client->is_connected = true;
            printf("client_num%d\n", client->team->free_slots);
            send_message(client->sockfd, "%d\n", \
            client->team->free_slots - 1);
            place_player(srv, client, list);
            return ;
        }
    } while (list_next(&list));
    send_message(client->sockfd, "ko\n");
}

bool register_command(client_t *client, char *cmd)
{
    for (int i = 0; i < 1024; i++) {
        if (client->cmd_queue[i] == NULL) {
            client->cmd_queue[i] = cmd;
            printf("Command registered [placement = %d]: %s\n", i, cmd);
            return (true);
        }
    }
    return (false);
}
