/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "NetworkManager.hpp"
#include <iostream>
#include "Teams.hpp"
#include "Item.hpp"

class NetworkManager;
class Map;
class Teams;
class Items;

class Core {
	public:
        Core(char const *host, char const *port);
        ~Core();
        void init();
        void gameloop();
        void displayMap();
        void displayItems();
        void displayInfoTails(sf::Vector2f pos);
        bool displayInfoPlayer(sf::Vector2f pos);
        void displayPlayers();
        const char *getHost() const {return _host;};
        const char *getPort() const { return _port; };
        NetworkManager *getNetworkManager() const { return _network; };
        sf::RenderWindow *getRenderWindow() const {return _renderWindow;};
        Map *_map;
        Teams * _teams;
        NetworkManager *_network;

    protected:
	private:
        sf::RenderWindow *_renderWindow;
        char const *_host;
        char const *_port;
};

#endif /* !CORE_HPP_ */
