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

typedef struct options_serv_s {
    uint16_t port;
    int width;
    int height;
    char **nameX;
    int clientsNb;
    int freq;
} options_serv_t;

bool parse_args_serv(int ac, char *av[], options_serv_t *opts);
bool check_opts_serv(options_serv_t opts);
bool str_to_uint16(const char *str, uint16_t *res);
char **find_name(char **av);
void print_usage_serv();
void serv(int ac, char **av, options_serv_t *opts);
bool check_opts_serv(options_serv_t opts);
#endif /* !MY_ZAPPY_H_ */
