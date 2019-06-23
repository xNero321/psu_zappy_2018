/*
** EPITECH PROJECT, 2019
** gui
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"
#include "Item.hpp"
#include <sstream>

NetworkManager::NetworkManager(Core * core): _core(core), _protocolfunc(
    {{"WELCOME", [this](void) { return this->fct_init(); }},
    {"msz", [this](void) {return this->fct_msz(); }},
    {"sgt", [this](void) {return this->fct_sgt(); }},
    {"bct", [this](void) {return this->fct_bct(); }},
    {"tna", [this](void) {return this->fct_tna(); }}}
) {
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::isDataAvailable()
{

	_command.clear();
	_parameters.clear();
    FD_ZERO(&_read);
    FD_ZERO(&_write);
    FD_SET(_sockfd, &_read);
    FD_SET(_sockfd, &_write);
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = 50000;
    if (select(_sockfd + 1, &_read, &_write, nullptr, &tv) == -1)
        exit(84);
    if (FD_ISSET(_sockfd, &_read)) {
        readSocket();
    }
}

void NetworkManager::readSocket()
{
    char *buffer = new char[4056];
    std::stringstream readStream;
    bool readData = true;

    while (readData)
    {
        std::cout << "Receiving chunk... ";
        bzero(buffer, 4056);
        read(_sockfd, buffer, 4056);
        readStream << buffer;
        readData = readStream.str().find("\0") == std::string::npos;

        std::cout << "Done (length: " << readStream.str().length() << ")" << std::endl;
    }
    std::istringstream stream(readStream.str());
    std::string line;

    if (readStream.str().length() > 0)
    {
        while (std::getline(readStream, line, '\n'))
        {
            parser(line);
        }
    }
}

void NetworkManager::parser(const std::string &command)
{
    std::istringstream stream(command.c_str());
    std::string temp;

    _parameters.clear();
    for ( int i = 0; getline(stream, temp, ' '); i++) {
        if (i == 0)
            _command = temp;
        else
            _parameters.push_back(temp);
    }
    this->_protocolfunc[_command]();
}

bool NetworkManager::fct_init()
{
    std::cout << "Sending GRAPHIC to server" << std::endl;
    write(_sockfd, "GRAPHIC\n", 8);
    return true;
}

bool NetworkManager::fct_msz()
{
    int w = atoi(_parameters[0].c_str());
	int h = atoi(_parameters[1].c_str());
    std::cout << "Creating a map of " << w<< "," << h <<std::endl;
	_core->_map->create(w, h, _core->getRenderWindow());
    return true;
}

bool NetworkManager::fct_bct()
{
	int x = atoi(_parameters[0].c_str());
	int y = atoi(_parameters[1].c_str());
	MapCell *cell = _core->_map->getACell(x, y);
    std::cout << "Filling cell at " << x<< "," << y <<std::endl;
    cell->getItems().push_back(new Item(Item::ItemType::food, atoi(_parameters[2].c_str()), sf::Vector2f(x, y), "./assets/food.png"));
    cell->getItems().push_back(new Item(Item::ItemType::linemate, atoi(_parameters[3].c_str()), sf::Vector2f(x + 0.33, y), "./assets/linemate.png"));
    cell->getItems().push_back(new Item(Item::ItemType::deraumere, atoi(_parameters[4].c_str()), sf::Vector2f(x + 0.66, y), "./assets/deraumere.png"));
    cell->getItems().push_back(new Item(Item::ItemType::sibur, atoi(_parameters[5].c_str()), sf::Vector2f(x, y + 0.33), "./assets/sibur.png"));
    cell->getItems().push_back(new Item(Item::ItemType::mendiane, atoi(_parameters[6].c_str()), sf::Vector2f(x + 0.33, y + 0.33), "./assets/mendiane.png"));
    cell->getItems().push_back(new Item(Item::ItemType::phiras, atoi(_parameters[7].c_str()), sf::Vector2f(x + 0.33, y + 0.66), "./assets/phiras.png"));
    cell->getItems().push_back(new Item(Item::ItemType::thystame, atoi(_parameters[8].c_str()), sf::Vector2f(x + 0.66, y), "./assets/thystame.png"));
    _core->_map->getACell(9, 7)->toString();

	return true;}

bool NetworkManager::fct_sgt()
{
    return true;
}

bool NetworkManager::fct_tna()
{
    std::cout << "Adding team named " << _parameters[0] <<std::endl;
    _core->_teams->add(_parameters[0]);
    return true;
}

void NetworkManager::init(const char *host, const char *port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd == -1)
        exit(84);

    server = gethostbyname(host);
    if (server == NULL)
        exit(84);
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(atoi(port));
    if (connect(_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Failed to connect to " << host << ":" << port << std::endl;
    }
}