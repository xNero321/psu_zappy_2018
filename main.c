/*
** EPITECH PROJECT, 2019
** Tech2
** File description:
** main
*/

#include "my_zappy.h"

int main(int ac, char**av)
{
    mapcell_t *map = create_map(10);

    //serv(ac, av);
    check_map(map, 10);
    return (0);
}