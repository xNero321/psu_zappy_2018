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
    #include "map.h"

    typedef struct client_s client_t;
    typedef struct linked_buffer_s linked_buffer_t;
    typedef struct server_s server_t;
    typedef struct team_s team_t;    

    struct linked_buffer_s {
        char buffer[2048];
        char *head;
        char *tail;
    };
    
    typedef enum {
        LEFT,
        UP,
        RIGHT,
        DOWN
    } dir_e;

    struct team_s
	{
		char *name;
		unsigned int free_slots;
	};

    struct server_s {
        int sockfd;
        struct sockaddr_in sin;
        struct epoll_event evt;
        struct epoll_event event[1024];
        unsigned int port;
        int epollfd;
        options_serv_t args;
        client_t *clients;
        int nb_players;
        int real_freq;
    };

    struct client_s {
        int id;
        int sockfd;
        mapcell_t *pos;
        struct sockaddr_in cin;
        team_t *team;
        dir_e dir;
        socklen_t size;
        int level;
        unsigned int inv[7];
        bool on_graph;
        bool is_connected;
        unsigned int ttl;
        linked_buffer_t buff;
    };
    
    void init_server(server_t *server);
    void init_server_socket(server_t *server, struct protoent *pe);
    void start_epoll(server_t *server);
    char *right(client_t *);
    char *forward(client_t *);
    char *left(client_t *);
    char *look(client_t *);
    char *inventory(client_t *);
    
#endif /* !__SERVER_H_ */
