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
    _renderWindow = new sf::RenderWindow(sf::VideoMode(1600, 900), "SFML window");
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
            if (event.type == sf::Event::MouseButtonPressed)
            {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "the right button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                for (const auto &tile : _map->getCells()) {
			    if (_mouseManager->intersects(tile->getRectangle())) {
				std::cout << "Clicked on tile at position : x=" << tile->getPosition().x << " y=" << tile->getPosition().y << std::endl;
				_graphicManager->showRessourcesOnTile(tile);
				return ;
			}
		}
            }
}
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
                75 / sprite.getLocalBounds().width,
                75 / sprite.getLocalBounds().height);
            y++;
            _renderWindow->draw(sprite);
    }


}