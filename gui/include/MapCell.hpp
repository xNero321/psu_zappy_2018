/*
** EPITECH PROJECT, 2019
** gui
** File description:
** MapTiles
*/

#ifndef MAPTILES_HPP_
#define MAPTILES_HPP_

#include "Core.hpp"
#include "Item.hpp"

class Item;

class MapCell {
	public:
		MapCell(sf::Vector2f pos);
		~MapCell();
		sf::Vector2f getPos() {return _pos;};
		std::vector<Item*> &getItems() {return _items;};
		void toString();
		std::string getItemName(int type);
	protected:
	private:
		sf::Vector2f _pos;
		std::vector<Item*> _items;
};

#endif /* !MAPTILES_HPP_ */
