#include "../includes/Server.hpp"
int Channel::_globalChannelId;
int Client::_globalId;

void	Server::setPfds()
{
	_pfds.clear();
	_pfds.push_back(_srvPfd);
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
		_pfds.push_back(it->second.getPfd());
}

int Server::getClientId(std::string name)
{
	for (size_t i = 1; i < _clients.size(); i++)
	{
		if (name == _clients[i].getNick())
			return (i);
	}
	return (-1);
}

int Server::getChannelId(std::string name)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (name == _channels[i].getName())
			return (_channels[i].getId());
	}
	return (-1);
}

bool Server::isUserInChannel(int i, int chId)
{
	if (chId == -1)
		return (false);
	for (std::vector<int>::iterator it = _channels[chId].getClientsInChannel().begin(); 
		it != _channels[chId].getClientsInChannel().end(); it++) {
			if (i == *it)
				return (true);
	}
	return (false);
}

void	serverLog(std::string nick, std::string str) {
	std::cout << YELLOW("Server log: ") << nick << " " << str << std::endl;
}
