/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "Core.hpp"


class Item {
	public:
        enum ItemType {
            food,
            linemate,
            deraumere,
            sibur,
            mendiane,
            phiras,
            thystame,
        };
		Item(ItemType type, int quantity, sf::Vector2f pos);
		~Item();



	protected:
	private:
        ItemType _type;
        int _quantity;
        sf::Texture *_texture;
        sf::Vector2f _pos;
};

#endif /* !ITEM_HPP_ */
