/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int number, sf::Vector2f pos, int orientation, int lvl, std::string team):
_number(number), _pos(pos), _orientation(orientation), _lvl(lvl), _team(team), _incantation(false)
{
}

std::string Player::getTextureToDisplay()
{
    if (_incantation) {
        return ("./assets/player_inc.png");
    } else {
        switch (_orientation)
        {
        case 1:
            return("./assets/player_n.png");
        case 2:
            return("./assets/player_e.png");
        case 3:
            return("./assets/player_s.png");
        case 4:
            return("./assets/player_w.png");
        }
    }
    return("");
}

void Player::toString()
{
    std::cout << "\n\nPlayer " << _number << ":" << std::endl;
    std::cout << "Position: " << _pos.x << "," << _pos.y;
    std::cout << "\t Level: " << _lvl;
    std::cout << "\t Team: " << _team << std::endl;
    std::cout << "Inventory: " << std::endl;

    for (auto elem : _inventory)
    {
        std::cout << elem.first << ": " << elem.second << "\n";
    }
    std::cout << "\n";
}