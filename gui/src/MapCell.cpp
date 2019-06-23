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
    std::cout << "\n\nCell at " << _pos.x << "," << _pos.y << std::endl;
    std::cout << "Items in the cell:\n";
    for (const auto &i : _items) {
        std::cout << "Type: " << getItemName(i->getType());
        std::cout << "\t\tQuantity: " << i->getQuantity() << std::endl;
    }
    std::cout << "\n";
}

std::string MapCell::getItemName(int type)
{
    switch (type) {
        case 0:
            return("FOOD");
        case 1:
            return("LINEMATE");
        case 2:
            return("DERAUMERE");
        case 3:
            return("SIBUR");
        case 4:
            return("MENDIANE");
        case 5:
            return("PHIRAS");
        case 6:
            return("THYSTAME");
    }
    return ("");
}