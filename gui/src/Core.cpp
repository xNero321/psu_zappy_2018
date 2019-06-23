/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(char const *host, char const *port): _host(host), _port(port)
{
    _network = new NetworkManager(this);
    _map = new Map();
    _renderWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML window");
    _renderWindow->setFramerateLimit(60);
    _teams = new Teams();
}

Core::~Core()
{
}

void Core::init()
{
    _network->init(_host, _port);
    gameloop();
}

void Core::gameloop()
{    // Limit the framerate to 60 frames per second (this step is optional)
    // The main loop - ends as soon as the window is closed

    while (_renderWindow->isOpen())
    {
        sf::Event event;
        while (_renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _renderWindow->close();
        }
        _renderWindow->clear();
        displayMap();
        _renderWindow->display();
        _network->isDataAvailable();
    }
}

void Core::displayMap()
{
    std::vector<MapCell *> &entities = _map->getCells();
    int y = 0;
    for (const auto &i : entities)
    {
            sf::Texture texture;
            sf::Sprite sprite;
            texture.loadFromFile("./assets/grass.png");
            texture.setSmooth(true);
            sprite.setTexture(texture);
            sprite.setPosition(i->getPos());
            sprite.setScale(
                24 / sprite.getLocalBounds().width,
                24 / sprite.getLocalBounds().height);
            y++;
            _renderWindow->draw(sprite);
    }


}