/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** server.h
*/

#ifndef __SERVER_H_
    #define __SERVER_H_
    #define EXIT_FAIL (84)
    #define NETWORK_PROTOCOL "TCP"
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/epoll.h>
    #include <sys/stat.h>
    #include <signal.h>
    #include "my_zappy.h"
    typedef struct client_s
    {
        int id;
        int sockfd;
        struct sockaddr_in cin;
        team_t *team;
        dir_t dir;
        socklen_t size;
        bool on_graph;
        bool is_connected;
    } client_t;
    
    typedef enum
    {
        UP,
        EAST,
        SOUTH,
        WEST
    } dir_e;
    
    typedef struct server_s
    {
        int sockfd;
        struct sockaddr_in sin;
        struct epoll_even evt;
        struct epoll_event event[1024];
        uint port;
        int epollfd;
        options_serv_t args;
        client_t *cliets;
        int nb_players;
        int real_freq;
    } server_t;
    void init_server(server_t *server);
    void init_server_socket(server_t *server, struct protoent *pe);
    void start_epoll(server_t *server);
    
#endif /* !__SERVER_H_ */
