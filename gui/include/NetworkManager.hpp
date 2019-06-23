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
#include <map>
#include <functional>
#include <iostream>
#include <vector>
#include "Core.hpp"

class Core;

class NetworkManager {
	public:
        NetworkManager(Core *core);
        ~NetworkManager();
        void init(const char *host, const char *port);
        void isDataAvailable();
        void readSocket();
        void getNextLine(int socket, unsigned int x, void *buffer);
        void parser(const std::string &command);

    private :
        bool fct_init();
        bool fct_msz();
        bool fct_bct();
        bool fct_tna();
        bool fct_pnw();
        bool fct_ppo();
        bool fct_plv();
        bool fct_sgt();
        Core *_core;
        std::map<std::string, std::function<bool(void)>> _protocolfunc;
        int _sockfd;
        std::string _command;
        std::vector<std::string> _parameters;
        fd_set _read;
        fd_set _write;
};

#endif /* !NETWORKMANAGER_HPP_ */
