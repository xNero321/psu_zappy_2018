/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** parsing
*/

#include "my_zappy.h"

static struct option long_options[] = {
    {"name", required_argument, 0, 'n'},
    {"port", required_argument, 0, 'p'},
    {"machine", required_argument, 0, 'h'},
};

bool parse_args_ai(int ac, char* av[], options_ai_t* opts)
{
    for (int32_t option_index = 0;; option_index = 0) {
        int8_t c = getopt_long(ac, av, "n:p:h:", long_options, &option_index);
        if (c == -1)
            break;
        switch (c) {
        case 'n':
            opts->name = strdup(optarg);
            break;
        case 'p':
            if (!str_to_uint16(optarg, &(opts->port)))
                return false;
            break;
        case 'h':
            opts->machine = strdup(optarg);
            break;
        case '?':
        default:
            return false;
        }
    }
    return true;
}

bool check_opts_ai(options_ai_t opts)
{
    return !(opts.name && opts.machine && opts.port == 0);
}

void ai(int ac, char** av)
{
    options_ai_t opts = {NULL, 0, NULL};

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        print_usage_ai();
    else {
        if (!parse_args_ai(ac, av, &opts) || !check_opts_ai(opts))
            return (84);
    }
}
