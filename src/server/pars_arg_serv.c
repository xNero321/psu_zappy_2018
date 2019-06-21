/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** parsing
*/

#include <getopt.h>
#include "map.h"
#include "player.h"

static struct option long_options[] = {{"port", required_argument, 0, 'p'},
                                       {"name", required_argument, 0, 'n'},
                                       {"width", required_argument, 0, 'x'},
                                       {"height", required_argument, 0, 'y'},
                                       {"clientsNb", required_argument, 0, 'c'},
                                       {"freq", required_argument, 0, 'f'},
                                       {0, 0, 0, 0}};

int size_tab(char **av)
{
    int j;
    int i = 0;
    for (j = 0; strcmp(av[j], "-n") != 0; j++);
    for (; av[j] != NULL; j++)
        i++;
    return (i);
}

char** find_name(char** av)
{
    char** toto = calloc(size_tab(av), sizeof(char*));
    int j;
    for (j = 0; strcmp(av[j], "-n") != 0; j++);
    j = j + 1;
    int i = 0;
    for (; av[j][0] != '-'; j++) {
        toto[i] = calloc(strlen(av[j]), sizeof(char));
        strcpy(toto[i], av[j]);
        i++;
    }
    return (toto);
}

bool analyse_opt(char** av, options_serv_t *opts, int8_t opt)
{
    switch (opt) {
        case 'p': if (!str_to_uint16(optarg, &(opts->port)))
                    return false;
            break;
        case 'n': opts->nameX = find_name(av);
            break;
        case 'x': opts->width = atoi(optarg);
            break;
        case 'y': opts->height = atoi(optarg);
            break;
        case 'c': opts->clientsNb = atoi(optarg);
            break;
        case 'f': opts->freq = atoi(optarg);
            break;
        default: break;
    }
    return (true);
}

bool parse_args_serv(int ac, char* av[], options_serv_t* opts)
{
    int32_t idx = 0;

    for (int8_t opt = 0; opt != -1; opt = 
        getopt_long(ac, av, "p:n:x:y:c:f:", long_options, &idx)) {
        if (!analyse_opt(av, opts, opt))
            return (false);
    }
    return (true);
}

void serv(int ac, char** av)
{
    options_serv_t opts = {0, 0, 0, NULL, 0, 0};
    mapcell_t *map = NULL;
    player_t player;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_usage_serv();
    else
        if (!parse_args_serv(ac, av, &opts) || !check_opts_serv(opts))
            exit(84);
    map = create_map(&opts);
    player.pos = map;
    player.dir = 0;
    player.level = 2;
    map->character = 1;
    printf("\n%s\n", look(&player));
    //send_map(map);
}