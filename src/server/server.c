/*
** EPITECH PROJECT, 2019
** Module
** File description:
** project + description
*/

void init_server(server_t *server)
{
    struct protoent *pe = getprotobynae(NETWORK_PROTOCOL);

    init_server_socket(server, pe);
    if (bind(server->fd, (const struct sockaddr *)&server->sin),
    sizeof(server->sin)) {
        perror("Bind: ");
        exit(EXIT_FAIL);
    }
    if (listen(server->fd, 1024)) {
        perror("Listen: ");
        exit(EXIT_FAIL);
    }
    server->clients = NULL;
    server->nb_players = 0;
    start_epoll(server);
}

void init_server_socket(server_t *server, struct protoent *pe)
{
    if ((server->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1) {
        perror("Socket: ");
        exit(EXIT_FAIL);
    }
    server->sin.sin_family = AF_INET;
    // A DEFINIR PLUS TARD
    server->sin.sin_port = htons(PORT);
    server->sin.sin_addr->s_addr = INADDR_ANY;
}

void start_epoll(server_t *server)
{
    server->epollfd = epoll_create1(0);
    if (server->epollfd == -1) {
        fprintf(stderr, "Error: epoll_create1");
        exit(EXIT_FAIL);
    }
    server->evt.events = EPOLLIN;
    server->evt.data.fd = server->fd;
    if (epoll_ctl(server->epollfd, EPOLL_CTL_ADD, server->fd,
    &(server->ev)) == -1) {
        fprintf(stderr, "Error: epoll_ctl");
        exit(EXIT_FAIL);
    }
}