/*
** EPITECH PROJECT, 2019
** gui
** File description:
** NetworkManager
*/

#include "NetworkManager.hpp"
#include "Item.hpp"
#include <sstream>

NetworkManager::NetworkManager(Core *core) : _core(core), _protocolfunc(
        {{"WELCOME", [this](void) { return this->fct_init(); }},
        {"msz", [this](void) { return this->fct_msz(); }},
        {"sgt", [this](void) { return this->fct_sgt(); }},
        {"bct", [this](void) { return this->fct_bct(); }},
        {"tna", [this](void) { return this->fct_tna(); }},
        {"pnw", [this](void) { return this->fct_pnw(); }},
        {"pin", [this](void) { return this->fct_pin(); }},
        {"ppo", [this](void) { return this->fct_ppo(); }},
        {"plv", [this](void) { return this->fct_plv(); }},
        {"pex", [this](void) { return this->fct_pex(); }},
        {"pbc", [this](void) { return this->fct_pbc(); }},
        {"pic", [this](void) { return this->fct_pic(); }},
        {"pie", [this](void) { return this->fct_pie(); }},
        {"pfk", [this](void) { return this->fct_pfk(); }},
        {"pdr", [this](void) { return this->fct_pdr(); }},
        {"pgt", [this](void) { return this->fct_pgt(); }},
        {"pdi", [this](void) { return this->fct_pdi(); }},
        {"enw", [this](void) { return this->fct_enw(); }},
        {"eht", [this](void) { return this->fct_eht(); }},
        {"ebo", [this](void) { return this->fct_ebo(); }},
        {"edi", [this](void) { return this->fct_edi(); }},
        {"sst", [this](void) { return this->fct_sst(); }},
        {"seg", [this](void) { return this->fct_seg(); }},
        {"smg", [this](void) { return this->fct_smg(); }},
        {"suc", [this](void) { return this->fct_suc(); }},
        {"sbp", [this](void) { return this->fct_sbp(); }}})
{
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
        int r = read(_sockfd, buffer, 4056);
        if (r < 0)
            exit(84);
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
	_core->_map->create(w, h);
    return true;
}

bool NetworkManager::fct_bct()
{
	int x = atoi(_parameters[0].c_str());
	int y = atoi(_parameters[1].c_str());
	MapCell *cell = _core->_map->getACell(x, y);
    cell->getItems().clear();
    std::cout << "Filling cell at " << x<< "," << y <<std::endl;
    cell->getItems().push_back(new Item(Item::ItemType::food, atoi(_parameters[2].c_str()), sf::Vector2f(x, y), "./assets/food.png"));
    cell->getItems().push_back(new Item(Item::ItemType::linemate, atoi(_parameters[3].c_str()), sf::Vector2f(x + 0.33, y), "./assets/linemate.png"));
    cell->getItems().push_back(new Item(Item::ItemType::deraumere, atoi(_parameters[4].c_str()), sf::Vector2f(x + 0.66, y), "./assets/deraumere.png"));
    cell->getItems().push_back(new Item(Item::ItemType::sibur, atoi(_parameters[5].c_str()), sf::Vector2f(x, y + 0.33), "./assets/sibur.png"));
    cell->getItems().push_back(new Item(Item::ItemType::mendiane, atoi(_parameters[6].c_str()), sf::Vector2f(x + 0.33, y + 0.33), "./assets/mendiane.png"));
    cell->getItems().push_back(new Item(Item::ItemType::phiras, atoi(_parameters[7].c_str()), sf::Vector2f(x + 0.33, y + 0.66), "./assets/phiras.png"));
    cell->getItems().push_back(new Item(Item::ItemType::thystame, atoi(_parameters[8].c_str()), sf::Vector2f(x + 0.66, y), "./assets/thystame.png"));
	return true;
}

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

bool NetworkManager::fct_pnw()
{
    std::cout << "New Player as join the server!" << std::endl;
    std::cout << _parameters[0] << std::endl;
    sf::Vector2f pos(atoi(_parameters[1].c_str()), atoi(_parameters[2].c_str()));
    Player *player = new Player(atoi(_parameters[0].c_str()), pos, atoi(_parameters[3].c_str()), atoi(_parameters[4].c_str()), _parameters[5]);
    _core->_map->getPlayers().push_back(player);
    return true;
}

bool NetworkManager::fct_pin()
{
    std::cout << "Fill Player " << _parameters[0] << "'s inventory!"<< std::endl;
    for (const auto &player : _core->_map->getPlayers())
    {
        if (player->getNumber() == atoi(_parameters[0].c_str()))
        {
            std::map<std::string, int> temp = {
                {"FOOD", atoi(_parameters[3].c_str())},
                {"LINEMATE", atoi(_parameters[4].c_str())},
                {"DERAUMERE", atoi(_parameters[5].c_str())},
                {"SIBUR", atoi(_parameters[6].c_str())},
                {"MENDIANE", atoi(_parameters[7].c_str())},
                {"PHIRAS", atoi(_parameters[8].c_str())},
                {"THYSTAME", atoi(_parameters[9].c_str())},
            };
            player->setInventory(temp);
        }
    }
    return true;
}

bool NetworkManager::fct_ppo()
{
    std::cout << "Update Player " << _parameters[0] << "'s position!" << std::endl;
    for (const auto &player : _core->_map->getPlayers()) {
        if (player->getNumber() == atoi(_parameters[0].c_str())) {
            player->setOrientation(atoi(_parameters[3].c_str()));
            player->setPosition(sf::Vector2f(atoi(_parameters[1].c_str()), atoi(_parameters[2].c_str())));
        }
    }
    return true;
}

bool NetworkManager::fct_plv()
{
    std::cout << "Update Player " << _parameters[3] << "'s lvl!" << std::endl;
    for (const auto &player : _core->_map->getPlayers())
        if (player->getNumber() == atoi(_parameters[3].c_str()))
            player->setLvl(atoi(_parameters[1].c_str()));
    return true;
}

bool NetworkManager::fct_pex()
{
    return true;
}

bool NetworkManager::fct_pbc()
{
    return true;
}

bool NetworkManager::fct_pic()
{
    std::cout << "start Player " << _parameters[3] << "'s incantation!" << std::endl;
    for (const auto &player : _core->_map->getPlayers())
    {
        if (player->getPosition() == sf::Vector2f(atoi(_parameters[0].c_str()), atoi(_parameters[1].c_str())))
        {
            player->setIncantation(true);
        }
    }
    return true;
}

bool NetworkManager::fct_pie()
{
    std::cout << "End Player " << _parameters[3] << "'s incantation!" << std::endl;
    for (const auto &player : _core->_map->getPlayers())
    {
        if (player->getPosition() == sf::Vector2f(atoi(_parameters[0].c_str()), atoi(_parameters[1].c_str())))
        {
            player->setIncantation(false);
        }
    }
    return true;
}

bool NetworkManager::fct_pfk()
{
    return true;
}

bool NetworkManager::fct_pdr()
{
    return true;
}

bool NetworkManager::fct_pgt()
{
    return true;
}

bool NetworkManager::fct_pdi()
{
    std::vector<Player *> &players = _core->_map->getPlayers();
    for (size_t i = 0; i < players.size(); ++i) {
		if (players[i]->getNumber() == atoi(_parameters[0].c_str())) {
			players.erase(players.begin() + i);
			return true;
		}
	}
    return true;
}

bool NetworkManager::fct_enw()
{
    return true;
}

bool NetworkManager::fct_eht()
{
    return true;
}

bool NetworkManager::fct_ebo()
{
    return true;
}

bool NetworkManager::fct_edi()
{
    return true;
}

bool NetworkManager::fct_sst()
{
    return true;
}

bool NetworkManager::fct_seg()
{
    exit(0);
    return true;
}

bool NetworkManager::fct_smg()
{
    std::cout << "Server's message: " << _parameters[0] << std::endl;
    return true;
}

bool NetworkManager::fct_suc()
{
    std::cout << "Unknown command." << std::endl;
    return true;
}

bool NetworkManager::fct_sbp()
{
    std::cout << "Bad command parameter." << std::endl;
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