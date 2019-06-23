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
    sf::Vector2i position;
    while (_renderWindow->isOpen())
    {
        sf::Event event;
        while (_renderWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _renderWindow->close();
            if (event.type == sf::Event::MouseLeft) {
                position = sf::Mouse::getPosition();
                displayInfoTails(position)
            }
        }
        _renderWindow->clear();
        displayMap();
        displayItems();
        displayPlayers();
        _renderWindow->display();
        _network->isDataAvailable();
    }
}

void Core::displayInfoTails(sf::Vector2i pos)
{
    std::vector<MapCell *> &entities = _map->getCells();
    int y = 0;
    for (const auto &i : entities) {
        if ((i->getPos().x - 1) * 90) + 90 <= pos.x  && (i->getPos().x * 90) + 90 >= pos.x  && ((i->getPos().y - 1) * 90) + 90 >= pos.y && (i->getPos().y * 90) + 90 <= pos.y) {
                std::cout << i->getPos().x << ", " << i->getPos().y << std::endl;
        }
        y++;
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
            sprite.setPosition(sf::Vector2f(i->getPos().x * 90, i->getPos().y * 90));
            sprite.setScale(
                90 / sprite.getLocalBounds().width,
                90 / sprite.getLocalBounds().height);
            y++;
            _renderWindow->draw(sprite);
    }


}

void Core::displayItems()
{
    std::vector<MapCell *> &entities = _map->getCells();

    for (int y = 0; y < _map->getH(); ++y) {
		for (int x = 0; x < _map->getW(); ++x) {
			std::vector<Item *> &items = _map->getACell(x, y)->getItems();
            for (const auto &y : items) {
                sf::Texture texture;
                sf::Sprite sprite;
                if (y->getQuantity() > 0) {
                    texture.loadFromFile(y->getTexturePath().c_str());
                    texture.setSmooth(true);
                    sprite.setTexture(texture);
                    sprite.setPosition(sf::Vector2f(y->getPos().x * 90, y->getPos().y * 90));
                    sprite.setScale(
                        30 / sprite.getLocalBounds().width,
                        30 / sprite.getLocalBounds().height);
                    _renderWindow->draw(sprite);
                }
            }
		}
    }
}

void Core::displayPlayers()
{
    std::vector<Player *> &entities = _map->getPlayers();
    for (const auto &i : entities)
    {
        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile(i->getTextureToDisplay());
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(i->getPosition().x * 90, i->getPosition().y * 90));
        sprite.setScale(
            90 / sprite.getLocalBounds().width,
            90 / sprite.getLocalBounds().height);
        _renderWindow->draw(sprite);
    }
}