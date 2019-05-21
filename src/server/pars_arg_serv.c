/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** parsing
*/

#include "my_zappy.h"

static struct option long_options[] = {
    {"port", required_argument, 0, 'p'},
    {"name", required_argument, 0, 'n'},
    {"width", required_argument, 0, 'x'},
    {"height", required_argument, 0, 'y'},
    {"clientsNb", required_argument, 0, 'c'},
    {"freq", required_argument, 0, 'f'},
};

bool parse_args_serv(int ac, char* av[], options_serv_t* opts)
{
    for (int32_t option_index = 0;; option_index = 0) {
        int8_t c =
            getopt_long(ac, av, "p:n:x:y:c:f:", long_options, &option_index);
        if (c == -1)
            break;
        switch (c) {
        case 'p':
            if (!str_to_uint16(optarg, &(opts->port)))
                return false;
            break;
        case 'n':
            opts->nameX = strdup(optarg);
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
        case '?':
        default:
            return false;
        }
    }
    return true;
}

bool check_opts_serv(options_serv_t opts)
{
    return !(opts.nameX && opts.width && opts.height && opts.clientsNb &&
             opts.freq && opts.port == 0);
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
            return (84);
    }
}