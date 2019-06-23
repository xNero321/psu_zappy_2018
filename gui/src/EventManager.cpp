/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** ugo.milhes@epitech.eu
*/

#include "EventManager.hpp"
#include "Core.hpp"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

EventManager::clickOnTails()
{
    std::vector<MapCell *> &entities = _map->getCells();
    int y = 0;
    for (const auto &i : entities) 
}
