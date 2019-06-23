/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Multiplexing.c
*/

#include <stddef.h>
#include <sys/time.h>
#include "list.h"
#include "read_cmds.h"
#include "server.h"

long long get_time(void)
{
    long long ms;
    struct timeval e_time;

    gettimeofday(&e_time, NULL);
    ms = e_time.tv_sec * 1000LL + e_time.tv_usec / 1000;
    return (ms);
}

void multiplexing_loop(server_t *server)
{
    int fd = 0;
    long long t_b = get_time();
    static long long t_e = 0;
    const long long to = (t_e) ? (t_b + (server->args.freq - (t_e - t_b)))
    : (t_b + server->args.freq);

    while (get_time() < to) {
        fd = epoll_wait(server->epollfd, server->event, 1024,
            (int)to - get_time());
        if (fd == -1) {
            fprintf(stderr, "%s\n", "Error: epool_wait");
            exit(84);
        }
        for (int i = 0; i < fd; ++i) {
            usleep(10000);
            events_distribution(server, i);
        }
    }
    t_e = get_time();
}

void start_multiplexing(server_t *server)
{
    float f = (float) 1 / (float) server->args.freq * 1000;

    while (1)
        multiplexing_loop(server);
}

void events_distribution(server_t *server, int i)
{
    client_t client;
    if (server->event[i].data.fd == server->sockfd) {
        get_user(&client, server);
        client.sockfd = accept(server->sockfd,
            (struct sockaddr *)&(client.cin), &(client.size));
        if (client.sockfd == -1) {
            perror("Accept: ");
            exit(84);
        }
        server->evt.events = EPOLLIN | EPOLLET;
        server->evt.data.fd = client.sockfd;
        if (epoll_ctl(server->epollfd, EPOLL_CTL_ADD, client.sockfd,
        &(server->evt)) == -1) {
            perror("epoll_ctl: ");
            exit(84);
        }
        list_push(&(server->clients), &client);
        send_message(client.sockfd, "WELCOME\n");
    } else {
        manage_buffer(server, server->event[i].data.fd);
        return;
    }
}

void manage_buffer(server_t *server, int fd)
{
    client_t *client = client_fd(server, fd);
    char *str = NULL;
    int i = 0;
    if (client == NULL)
        return;
    if (read_cmd(&client->buff, fd) == false)
        //disconnect_client;
        return;
    while (1) {
        str = read_cmd_where(&client->buff, "\n");
        if (str == NULL || (strcmp(str, "-1") == 0) == -1)
            return;
        if (!client->is_connected) {
            join_team(server, client, str);
        } else if (strcmp(str, "-1") == 0) {
            send_message(client->sockfd, "ko\n");
            return;
        } else {
            printf("------ COMMAND EXECUTION ------\n");
            printf("CLIENT n°%d from team [%s]\n",
            client->id, client->team->name);
            printf("COMMAND: [%s]\n", str);
            printf("OUTPUT: %s", exec_cmd(server, client, str));
            printf("-------------------------------\n\n\n");
            send_message(client->sockfd, exec_cmd(server, client, str));
            return;
        }
    }
}
