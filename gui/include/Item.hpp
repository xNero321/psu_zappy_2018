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
		Item(ItemType type, int quantity, sf::Vector2f pos, std::string);
		~Item();
        ItemType getType() const {return _type;};
        std::string getTexturePath() const {return _path;};
        int getQuantity() const {return _quantity;};
        sf::Vector2f getPos() const {return _pos;};




	protected:
	private:
        ItemType _type;
        int _quantity;
        sf::Vector2f _pos;
        std::string _path;
};

#endif /* !ITEM_HPP_ */
