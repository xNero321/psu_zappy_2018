/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Item
*/

#include "Item.hpp"

Item::Item(ItemType type, int quantity, sf::Vector2f pos): _type(type), _quantity(quantity), _pos(pos)
{
}

Item::~Item()
{
}
