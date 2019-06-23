/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** exec_cmd
*/

#include "server.h"

char *exec_cmd(server_t *serv, client_t *player, char *cmd)
{
    char *(*cmd_func[12])(client_t *, char *, server_t *) = {forward, left,
    right, look, inventory, take, set, connect_nbr, eject, my_fork,
    incantation, broadcast};
    char cmd_name[12][12] = {"forward", "left", "right", "look", "inventory",
    "take", "set", "connect_nbr", "eject", "fork", "incantation", "broadcast"};

    for (int i = 0; i < 8; i++) {
        if (strncmp(cmd_name[i], cmd, strlen(cmd_name) == 0))
            return (cmd_func[i](player, cmd, serv));
    }
    return ("ko");
}