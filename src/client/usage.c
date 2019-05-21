/*
** EPITECH PROJECT, 2018
** PSU_zappy_2018
** File description:
** PSU_zappy_2018 usage.c
*/
#include "my_zappy.h"

void print_usage_ai()
{
    printf("USAGE: ./zappy_ai -p port -n name -h machine\n");
    printf(
        "\tport\tis the port number\n\tname\tis the name of the "
        "team\n\tmachine\tis the name of the machine; localhost by default\n");
    exit(84);
}
