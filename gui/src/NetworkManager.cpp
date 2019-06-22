/*
** EPITECH PROJECT, 2019
** gui
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"

NetworkManager::NetworkManager() : _protocolfunc(
    {{"WELCOME", [this](void) { return this->fct_init(); }},
    {"msz", [this](void) {return this->fct_init(); }},
    {"bct", [this](void) {return this->fct_init(); }}}
) {
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::init(const char *host, const char *port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1)
        exit(84);

    server = gethostbyname(host);
    if (server == NULL) {
        exit(84);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);

    serv_addr.sin_port = htons(atoi(port));
    if (connect(_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Failed to connect to server " << host << ":" << port << std::endl;
    }
}

void NetworkManager::receiveData()
{
    char buffer[4056];
    read(_sockfd, buffer, 4055);
    std::cout << buffer;
}

bool NetworkManager::fct_init()
{
    write(_sockfd, "GRAPHIC\n", 8);
    return true;
}