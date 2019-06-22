/*
** EPITECH PROJECT, 2019
** gui
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <vector>

class Core;

class NetworkManager {
	public:
		NetworkManager();
		~NetworkManager();
        void init(const char *host, const char *port);
        void receiveData();
        bool fct_init();

    protected:
	private:
        std::unordered_map<std::string, std::function<bool(void)> > _protocolfunc;
        int _sockfd;
};

#endif /* !NETWORKMANAGER_HPP_ */
