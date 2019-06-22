/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(char const *host, char const *port): _host(host), _port(port)
{
    _network = new NetworkManager();
}

Core::~Core()
{
}

void Core::gameloop()
{
    _network->init(_host, _port);
    _network->receiveData();
    _network->fct_init();
    _network->receiveData();
}