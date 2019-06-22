/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** Multiplexing.c
*/

#include "list.h"

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
    long long t_e = 0;
    const long long to = (t_e) ? (t_b + (server->args.freq - (t_e - t_b)))
    : (t_b + server->args.freq)

    while (get_time() < to) {
        fd = epoll_wait(server->epollfd, server->event, 1024,
            int(to) - get_time());
        if (fd == -1) {
            fprintf(stderr, "%s\n", "Error: epool_wait");
            exit(84);
        }
        for (int i = 0; i < fd; ++i)
            events_distribution(server, i);
    }
    t_e = get_time();
    // client_cmd_exec() ?
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
        user.sockfd = accept(server->sockfd,
            (struct sockaddr *)&(client.cin), &(client.size));
        if (client.sockfd == -1) {
            perror("Accept: ");
            exit(84);
        }
        server->evt = EPOLLIN | EPOLLET;
        server->evt.data.fd = client.sockfd;
        if (epoll_ctl(server->epollfd, EPOLL_CTL_ADD, client.sockfd,
        &(server->evt)) == -1) {
            perror("epoll_ctl: ");
            exit(84);
        }
        list_push(&(server->clients), &client);
        send_message(client.sockfd, "WELCOME\n");
    } else {
        //call worker ?
        ;
    }
}
