/*
** EPITECH PROJECT, 2019
** NWP_mychap_2018
** File description:
** utils
*/

#include "my_zappy.h"

bool str_to_uint16(const char *str, uint16_t *res)
{
    char *end;
    errno = 0;
    intmax_t val = strtoimax(str, &end, 10);
    if (errno == ERANGE || val < 0 || val > UINT16_MAX || end == str ||
        *end != '\0')
        return false;
    *res = (uint16_t) val;
    return true;
}

void print_usage_serv(void)
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

bool check_opts_serv(options_serv_t opts)
{
    if (opts.nameX != NULL && opts.width != 0 && opts.height != 0
        && opts.freq != 0 && opts.port != 0) {
        return (true);
    }
    return (false);
}

void perror_exit(char *str, int error)
{
    perror(str);
    exit(error);
}
