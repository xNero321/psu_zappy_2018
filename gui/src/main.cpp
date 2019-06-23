/*
** EPITECH PROJECT, 2019
** gui
** File description:
** main
*/

#include "Core.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 3)
        return 84;
    Core *core = new Core(argv[1], argv[2]);
    core->init();
    return 0;
}
