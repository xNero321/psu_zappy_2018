/*
** EPITECH PROJECT, 2019
** gui
** File description:
** MapCell
*/

#include "MapCell.hpp"

MapCell::MapCell(sf::Vector2f pos)
{
    _pos = pos;
}

MapCell::~MapCell()
{
}

void MapCell::toString()
{
    std::cout << "Cell at " << _pos.x << "," << _pos.y << std::endl;
    for (const auto &i : _items) {
        std::cout << "Type: " << i->getType() << std::endl;
        std::cout << "Quantity: " << i->getQuantity() << std::endl;
    }
}