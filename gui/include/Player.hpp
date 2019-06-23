/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Core.hpp"
#include "Item.hpp"
#include <map>
class Core;
class Item;
class Player {
	public:
		Player(int number, sf::Vector2f, int orientation, int lvl, std::string team);
		~Player(){};
        std::string getTextureToDisplay();
        int getNumber() {return _number;};
        sf::Vector2f getPosition() { return _pos; };

        std::map<std::string, int> getInventory(){return _inventory;};
        void setInventory(std::map<std::string, int> map) { _inventory = map; };
        void setOrientation(int orientation) {_orientation = orientation;};
        void setPosition(sf::Vector2f pos) {_pos = pos;};
        void setLvl(int lvl) { _lvl = lvl; };
        void setIncantation(bool inc) {_incantation = inc;};

    protected:
	private:
        int _number;
        sf::Vector2f _pos;
        int _orientation;
        int _lvl;
        std::string _team;
        std::map<std::string, int> _inventory;
        bool _incantation;
};

#endif /* !PLAYER_HPP_ */
