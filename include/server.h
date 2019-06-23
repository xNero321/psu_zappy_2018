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
        mapcell_t *map;
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
    void serv(int ac, char **av, options_serv_t *opts, server_t *server);
    void init_server(server_t *server);
    bool parse_args_serv(int ac, char *av[], options_serv_t *opts,
    server_t *server);
    bool analyse_opt(char **av, options_serv_t *opts, int8_t opt,
    server_t *server, int ac);
    void get_team(server_t *server, int argc, char **argv);
    void init_server_socket(server_t *server, struct protoent *pe);
    void start_epoll(server_t *server);
    void send_to_client(server_t *server, client_t *client, char *cmd);
    void get_user(client_t *clt, server_t *server);
    void manage_buffer(server_t *server, int fd);
    void init_buffer(linked_buffer_t *buff);
    client_t *client_fd(server_t *srv, int fd);
    int send_message(int fd, const char *format, ...);
    void events_distribution(server_t *server, int i);
    void place_player(server_t *srv, client_t *client, team_t *team);
    void add_to_team(server_t *srv, client_t *client, char *str);
    char *right(client_t *, char *, server_t *);
    char *forward(client_t *, char *, server_t *);
    char *left(client_t *, char *, server_t *);
    char *look(client_t *, char *, server_t *);
    char *inventory(client_t *, char *, server_t *);
    char *take(client_t *, char *, server_t *);
    char *set(client_t *, char *, server_t *);
    char *connect_nbr(client_t *, char *, server_t *);
    char *eject(client_t *, char *, server_t *);
    char *my_fork(client_t *, char *, server_t *);
    char *incantation(client_t *, char *, server_t *);
    char *broadcast(client_t *, char *, server_t *);
    char *exec_cmd(server_t *, client_t *, char *);

#endif /* !__SERVER_H_ */
