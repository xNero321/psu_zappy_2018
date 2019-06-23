/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Core.hpp"
#include "MapCell.hpp"
#include "Player.hpp"

class MapCell;
class Core;
class Player;

class Map {
	public:
		Map(): _w(0), _h(0){};
		~Map(){};
        void create(int w, int h);
        int	getW() const { return _w; };
	    int	getH() const { return _h; };
		std::vector<Player *> &getPlayers() {return _player;};
        std::vector<MapCell *> &getCells() {
			return _cell;
		};
		MapCell *getACell(int x, int y) {
		if (static_cast<size_t>(y * _w + x) < _cell.size())
			return _cell[y * _w + x];
		else
			return nullptr;
		};



	protected:
	private:
        int _w, _h;
        std::vector<MapCell *>	_cell;
		std::vector<Player *>	_player;
};

#endif /* !MAP_HPP_ */
