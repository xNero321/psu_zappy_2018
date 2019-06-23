/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Map
*/

#include "Map.hpp"

void Map::create(int w, int h, sf::RenderWindow *renderWindow)
{
    _w = w;
	_h = h;

	_cell.clear();
	for (int y = 0; y < _h; ++y) {
		for (int x = 0; x < _w; ++x) {
			MapCell *mapCell = new MapCell(sf::Vector2f(x * 75, y * 75));
			_cell.push_back(mapCell);
		}
	}
}
