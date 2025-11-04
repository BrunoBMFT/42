#include "../includes/Server.hpp"
#include "../includes/Client.hpp"

//*GETTERS FROM LINE
std::string getUsername(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 1; ++i)
        pos = line.find(' ', pos + 1);
	std::string username = line.substr(pos + 1, line.find(' ', pos + 2) - pos - 1);
	while (!username.empty() && (username[username.size() - 1] == '\r' || username[username.size() - 1] == '\n'))
		username.erase(username.size() - 1);
    return (username);
}
std::string getRealname(const std::string &line) {
    size_t pos = 0;
    for (int i = 0; i < 4; ++i)
        pos = line.find(' ', pos + 1);
	std::string realname = line.substr(pos + 1);
	while (!realname.empty() && (realname[realname.size() - 1] == '\r' || realname[realname.size() - 1] == '\n'))
		realname.erase(realname.size() - 1);
    return (realname);
}
std::string getNick(const std::string &line) {
    size_t pos = 0;
	std::string nickname;
    for (int i = 0; i < 1; ++i)
        pos = line.find(' ', pos + 1);
	nickname = line.substr(pos + 1, line.find(' ', pos + 2) - pos - 1);
	if (nickname[0] == ':' || nickname == "#" || !strncmp(nickname.c_str(), "#&", 2) || !strncmp(nickname.c_str(), "&#", 2) || nickname.empty())
		return ("");
	for (size_t i = 0; i < nickname.size(); i++)
	{
		if (nickname[i] == ' ')
			return ("");
	}

	while (!nickname.empty() && (nickname[nickname.size() - 1] == '\r' || nickname[nickname.size() - 1] == '\n'))
		nickname.erase(nickname.size() - 1);
	return (nickname);
}

//*Authing
void	Server::tryPass(int i, char *bufPass)
{
	std::string line(bufPass);
	size_t pos = 0;
	for (int i = 0; i < 1; ++i)
		pos = line.find(' ', pos + 1);
	if (strcmp(line.substr(pos + 1).c_str(), _pass.c_str()) != 0) {
		sendToClient(_clients[i], ERR_PASSWDMISMATCH);
		throw std::runtime_error(" guessed the password wrong");
	}

	_clients[i].setAuthenticated(true);
	sendToClient(_clients[i], PASSACCEPT);//irc servers usually wait silently here
	throw std::runtime_error(" has authenticated, needs to register");//not runtime_error
}
void	Server::tryAuthClient(int i, int bytesRecv)
{
	char *bufPass = _clients[i].getBuf();
	bufPass[bytesRecv - 1] = '\0'; 
	if (strncmp(_clients[i].getBuf(), "PASS ", 5) != 0) {
		sendToClient(_clients[i], NOTAUTH);
		throw std::runtime_error(" is not authenticated, cannot talk");
	}
	tryPass(i, bufPass);
}


void	Server::welcomeClient(int i)
{
	std::string welcome = "Welcome to the " + _name + " Network, "
		+ _clients[i].getNick() + "[!" + _clients[i].getUsername() 
		+ "@"+ "host" + "]";//hardcoded
	sendToClient(_clients[i], welcome);
	//RPL_YOURHOST 
	//RPL_CREATED 
	//RPL_MYINFO
	//RPL_ISUPPORT (prob not needed)
	//LUSERS?
	//MOTD
}

void	Server::checkRegistration(int i)
{
	if (!_clients[i].getNick().empty() && !_clients[i].getUsername().empty() && !_clients[i].getRealname().empty() && _clients[i].getNick() != "*")
	{
		_clients[i].setRegistered(true);
		welcomeClient(i);
	}
}


void	Server::registerUser(int i)
{
	_clients[i].setUsername(getUsername(_clients[i].getBuf()));
	_clients[i].setRealname(getRealname(_clients[i].getBuf()));
	std::cout << "Username set to: " << _clients[i].getUsername() << " || " << _clients[i].getRealname() << std::endl;
	checkRegistration(i);
}
void	Server::registerNick(int i)
{
	_clients[i].setNick(getNick(_clients[i].getBuf()));
	std::cout << "Nick set to: " << _clients[i].getNick() << std::endl;
	checkRegistration(i);
}
