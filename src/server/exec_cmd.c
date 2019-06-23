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
    char cmd_name[12][12] = {"Forward", "Left", "Right", "Look", "Inventory",
    "Take", "Set", "Connect_nbr", "Eject", "Fork", "Incantation", "Broadcast"};

    for (int i = 0; i < 12; i++) {
        printf("%d %s\n", i, cmd_name[i]);
        if (strncmp(cmd_name[i], cmd, strlen(cmd_name[i])) == 0)
            return (cmd_func[i](player, cmd, serv));
    }
    return ("ko\n");
}
