/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** send_map
*/

#include "server.h"

char *map_to_array(mapcell_t *map)
{
    char *ar_map = "";
    int x = 0;
    int y = 0;

    for (mapcell_t *line = map; line; line = line->dir[3], y++) {
        x = 0;
        for (mapcell_t *cell = line; cell; cell = cell->dir[2], x++) {
            asprintf(&ar_map, "%s[", ar_map);
            for (int i = 0; i < 7; i++)
                asprintf(&ar_map, "%s%d,", ar_map, cell->obj[i]);
            asprintf(&ar_map, "%s%d]", ar_map, cell->character);
        }
        asprintf(&ar_map, "%s\n", ar_map);
    }
    return(ar_map);
}

void destroy_map(mapcell_t *map, options_serv_t opt)
{
    mapcell_t *nextline = map;
    mapcell_t *nextcell = map;

    for (int y = 0; y < opt.height; y++) {
        nextline = map->dir[DOWN];
        for (int x = 0; x < opt.width; x++) {
            nextcell = map->dir[RIGHT];
            free(map);
            map = nextcell;
        }
        map = nextline;
    }
    for (int y = 0; opt.nameX[y]; y++)
        free(opt.nameX[y]);
    free(opt.nameX);
}

void loop_packet(int sockfd, mapcell_t *map)
{
    struct sockaddr_in newAddr;
    int newSocket;
    socklen_t addr_size;
    char buffer[1024];
    char *buff_s;

    while (1) {
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if(newSocket < 0)
            exit(1);
        close(sockfd);
        buff_s = map_to_array(map);
        while (1) {
            sendto(newSocket, buff_s, sizeof(buff_s), 0, (struct sockaddr*)&newAddr, addr_size);
            recv(newSocket, buffer, 1024, 0);
            send(newSocket, buffer, strlen(buffer), 0);
            bzero(buffer, sizeof(buffer));
        }
    }
    close(newSocket);
}

struct sockaddr_in init_socket(void)
{
    struct sockaddr_in serverAddr;

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    return (serverAddr);
}

int send_map(mapcell_t *map) {

    int sockfd;
    int ret;
    struct sockaddr_in serverAddr = init_socket();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        perror_exit("[-]Error in connection.\n", 1);
    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
        perror_exit("[-]Error in binding.\n", 1);
    if (listen(sockfd, 10) != 0)
        printf("[-]Error in binding.\n");
    loop_packet(sockfd, map);
	return 0;
}