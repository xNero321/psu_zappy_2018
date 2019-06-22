/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <SFML/Graphics.hpp>
#include "NetworkManager.hpp"
#include <iostream>

class Core {
	public:
        Core(char const *host, char const *port);
        ~Core();
        void gameloop();
        const char *getHost() const {return _host;};
        const char *getPort() const { return _port; };
        NetworkManager *getNetworkManager() const { return _network; };

    protected:
	private:
        NetworkManager *_network;
        char const *_host;
        char const *_port;
};

#endif /* !CORE_HPP_ */
