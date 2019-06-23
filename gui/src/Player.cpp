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