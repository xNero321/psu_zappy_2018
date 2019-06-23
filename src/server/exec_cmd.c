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
        if (strncmp(cmd_name[i], cmd, strlen(cmd_name[i])) == 0)
            return (cmd_func[i](player, cmd, serv));
    }
    return ("ko\n");
}

void send_to_client(server_t *server, client_t *client, char *str)
{
    printf("------ COMMAND EXECUTION ------\n");
    printf("CLIENT n°%d from team [%s]\n",
    client->id, client->team->name);
    printf("COMMAND: [%s]\n", str);
    printf("OUTPUT: %s", exec_cmd(server, client, str));
    printf("-------------------------------\n\n\n");
    send_message(client->sockfd, exec_cmd(server, client, str));
}
