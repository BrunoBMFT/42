#include "../includes/Server.hpp"

void	serverLog(std::string nick, std::string str)
{
	std::cout << YELLOW("Server log: ") << nick << " " << str << std::endl;
}

void	Server::debugMessage(int i)
{
	std::cout << YELLOW("Client ") << _clients[i].getNick()<< " said: " << _clients[i].getBuf();
}