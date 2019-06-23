/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** parsing
*/

#include <getopt.h>
#include "server.h"
#include "list.h"

static struct option long_options[] = {
{"port", required_argument, 0, 'p'},
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

void get_team(server_t *server, int argc, char **argv)
{
    team_t team;

    optind--;
    for ( ; optind < argc && *argv[optind] != '-'; optind++){
        team.name = argv[optind];
        list_push(&server->args.teams, &team);
    }
}

bool analyse_opt(char** av, options_serv_t *opts, int8_t opt,
    server_t *server, int ac)
{
    switch (opt) {
        case 'p': if (!str_to_uint16(optarg, &(opts->port)))
                    return false;
            break;
        case 'n': get_team(server, ac, av);
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


bool parse_args_serv(int ac, char* av[], options_serv_t* opts,
    server_t *server)
{
    int32_t idx = 0;

    for (int8_t opt = 0; opt != -1; opt =
        getopt_long(ac, av, "p:n:x:y:c:f:", long_options, &idx)) {
        if (!analyse_opt(av, opts, opt, server, ac))
            return (false);
    }
    return (true);
}

void serv(int ac, char** av, options_serv_t *opts, server_t *server)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_usage_serv();
    else
        if (!parse_args_serv(ac, av, opts, server)) {
            printf("%s\n", "mange t mort");
            exit(84);
        }
}
