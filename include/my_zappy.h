/*
** EPITECH PROJECT, 2019
** Tech2
** File description:
** my_zappy
*/

#ifndef MY_ZAPPY_H_
#define MY_ZAPPY_H_

#include <errno.h>
#include <getopt.h>
#include <inttypes.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct options_ai_s {
    char* name;
    uint16_t port;
    char* machine;
} options_ai_t;

typedef struct options_serv_s {
    uint16_t port;
    int width;
    int height;
    char* nameX;
    int clientsNb;
    int freq;
} options_serv_t;

bool parse_args_ai(int ac, char* av[], options_ai_t* opts);
bool parse_args_serv(int ac, char* av[], options_serv_t* opts);
bool check_opts_ai(options_ai_t opts);
bool check_opts_serv(options_serv_t opts);
bool str_to_uint16(const char* str, uint16_t* res);
#endif /* !MY_ZAPPY_H_ */
