/*
** EPITECH PROJECT, 2019
** gui
** File description:
** Team
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include "Core.hpp"

class Core;

class Teams {
	public:
		Teams() {};
		~Teams() {};
        std::vector<std::string> 	&getTeams() {return _teams;};
        void	add(const std::string &t) {	_teams.push_back(t);};
	    void 	remove(const std::string &);

	protected:
	private:
    	std::vector<std::string> _teams;
};

#endif /* !TEAM_HPP_ */
