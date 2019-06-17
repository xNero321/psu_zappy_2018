/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** parsing
*/

#include <getopt.h>
#include "my_zappy.h"

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
    int i;
    for (j = 0; strcmp(av[j], "-n") != 0; j++);
    for (; av[j] != NULL; j++)
        i++;
    return (i);
}

char** find_name(char** av)
{
    char** toto = malloc(sizeof(char*) * size_tab(av));
    int j;
    for (j = 0; strcmp(av[j], "-n") != 0; j++);
    j = j + 1;
    int i = 0;
    for (; av[j][0] != '-'; j++) {
        toto[i] = malloc(sizeof(char) * strlen(av[j]));
        strcpy(toto[i], av[j]);
        i++;
    }
    return (toto);
}

bool parse_args_serv(int ac, char* av[], options_serv_t* opts)
{
    int32_t long_index = 0;
    for (int8_t opt = 0; opt != -1;
         opt = getopt_long(ac, av, "p:n:x:y:c:f:", long_options, &long_index)) {
        switch (opt) {
        case 'p':
            if (!str_to_uint16(optarg, &(opts->port)))
                return false;
            break;
        case 'n':
            opts->nameX = find_name(av);
            break;
        case 'x':
            opts->width = atoi(optarg);
            break;
        case 'y':
            opts->height = atoi(optarg);
            break;
        case 'c':
            opts->clientsNb = atoi(optarg);
            break;
        case 'f':
            opts->freq = atoi(optarg);
            break;
        default:
            break;
        }
    }
    return true;
}

bool check_opts_serv(options_serv_t opts)
{
    if (opts.nameX != NULL && opts.width != 0 && opts.height != 0 &&
        opts.clientsNb != 0 && opts.freq != 0 && opts.port != 0) {
        return (true);
    }
    return (false);
}

void print_usage_serv()
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 name2 "
           "... -c clientsNb -f freq\n");
    printf(
        "\tport\t\tis the port number\n\twidth\t\tis the width of the "
        "world\n\theight\t\tis the height of the world\n\tnameX\t\tis the name "
        "of the team X\n\tclientsNb\tis the number of authorized clients "
        "per team\n\tfreq\t\tis the reciprocal of time unit for execution of "
        "actions\n");
    exit(84);
}

void serv(int ac, char** av)
{
    options_serv_t opts = {0, 0, 0, NULL, 0, 0};

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_usage_serv();
    else {
        if (!parse_args_serv(ac, av, &opts) || !check_opts_serv(opts))
            exit(84);
    }
}