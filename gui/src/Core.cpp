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
    delete _map;
    delete _teams;
}

void Core::init()
{
    _network->init(_host, _port);
    gameloop();
}

void Core::gameloop()
{
    sf::Vector2i position;

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
                    sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
                    sf::Vector2f worldPos = _renderWindow->mapPixelToCoords(pixelPos);
                    if (!displayInfoPlayer(worldPos))
                        displayInfoTails(worldPos);
                }
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

void Core::displayInfoTails(sf::Vector2f pos)
{
    for (int y = 0; y < _map->getH(); ++y) {
        for (int x = 0; x < _map->getW(); ++x) {
            if (((_map->getACell(x, y)->getPos().x - 1) * 90) + 90 <= pos.x &&
                (_map->getACell(x, y)->getPos().x * 90) + 90 >= pos.x &&
                ((_map->getACell(x, y)->getPos().y - 1) * 90) + 90 <= pos.y &&
                (_map->getACell(x, y)->getPos().y * 90) + 90 >= pos.y)
                _map->getACell(x, y)->toString();
        }
    }
}


bool Core::displayInfoPlayer(sf::Vector2f pos)
{
    std::vector<Player *> &entities = _map->getPlayers();
    for (const auto &i : entities)
    {
        if (((i->getPosition().x - 1) * 90) + 90 <= pos.x &&
            (i->getPosition().x * 90) + 90 >= pos.x &&
            ((i->getPosition().y - 1) * 90) + 90 <= pos.y &&
            (i->getPosition().y * 90) + 90 >= pos.y) {
                i->toString();
                return true;
            }
    }
    return false;
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