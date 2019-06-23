/*
** EPITECH PROJECT, 2019
** Tech2
** File description:
** my_zappy
*/

#ifndef MY_ZAPPY_H_
#define MY_ZAPPY_H_

#include <errno.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4242

typedef struct team_s team_t;

typedef struct options_serv_s {
    uint16_t port;
    int width;
    int height;
    char **nameX;
    int clientsNb;
    team_t *teams;
    int freq;
} options_serv_t;

bool check_opts_serv(options_serv_t opts);
bool str_to_uint16(const char *str, uint16_t *res);
void print_usage_serv();
bool check_opts_serv(options_serv_t opts);
#endif /* !MY_ZAPPY_H_ */
